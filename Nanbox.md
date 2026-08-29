# Nanbox de Paxo

Especificación completa del empaquetado de valores (NaN-boxing) usado por el
compilador (`Src/Bcgen`) y la VM (`Src/Vm/Src`). Un valor en la máquina es una
palabra de 64 bits (`PaxoVar = uint64_t`) que autocontiene el tipo: **no hay
metadatos separados por cada variable**, lo que ahorra memoria y simplifica el
stack y los arreglos.

> Este documento describe tanto el diseño de 16 bits como el de 64 bits. La VM
> actual implementa el formato **64 bits** (`PaxoVar`); el formato de 16 bits es
> el diseño objetivo para variables compactas futuras.

---

## 1. Números Mobile Point (MP)

Los números se guardan con **radix mixto** y punto flotante móvil: la mantisa
es binaria pura pero el exponente cuenta décadas.

```
v = bc · 2^(-2·p) · 10^(exp - BIAS)
```

- `bc` mantisa (bit-chunks de a 2 bits).
- `p` cuán "dividida" está la celda (cuántas posiciones del punto, 0..max).
- `exp` exponente decimal con sesgo (`BIAS`).

### MP16 (16 bits)

```
[s | 2e | 5bc | p3]
```

| Campo | Bits | Detalle |
|-------|------|---------|
| `signo` | 1 | signo |
| `exp` | 2 | exponente + `BIAS16 = 1` |
| `bc` | 10 | mantisa (5 chunks de 2 bits), 0..1023 |
| `p` | 3 | posición del punto, 0..5 |

### MP64 (64 bits)

```
[s | 8e | 25bc | p5]
```

| Campo | Bits | Detalle |
|-------|------|---------|
| `signo` | 1 | signo |
| `exp` | 8 | exponente + `BIAS64 = 127` |
| `bc` | 50 | mantisa (25 chunks de 2 bits), 0..(2^50 − 1) |
| `p` | 5 | posición del punto, 0..25 |

En el nanbox de 64 bits, un **número MP64** se guarda **directo** en la palabra
(sin marcador): basta que los 5 bits bajos no coincidan con ningún marcador
reservado. Esto permite representar números con precisión total de MP64 sin
indirección.

---

## 2. Marcadores

Los 5 bits menos significativos (`bits 4..0`) son el **marcador** (`mark`) que
distingue las familias de valores. Los números MP64 se identifican por *no*
coincidir con ningún marcador reservado.

| `bits 4..0` | Marcador  | Familia |
|-------------|-----------|---------|
| `11010` (0x1A) | `PAXO_MARK_BOX` | bit, trit, char utf32, color, referencia (puntero/array/pkg/función/string) |
| `11011` (0x1B) | `PAXO_MARK_FXPKD` | punto fijo / entero (`int`) y decimal empaquetado (`pdec`) |
| `11100` (0x1C) | `PAXO_MARK_N16` | MP16 embebido |
| otro | — | número MP64 directo |

> `PAXO_MARK_MASK = 0x1F` (5 bits). `PAXO_VAL_SHIFT = 5` es el corrimiento de
> los campos de valor que viven por encima del marcador.

---

## 3. Formato de 64 bits (implementado)

### 3.1 bit (booleano) — marcador `11010`, tag `00`

```
 bits 63..62  bits 61..6      bit 5      bits 4..0
  ┌───────┐ ┌──────────────┐ ┌───────┐ ┌──────────┐
  │  00   │ │  padding (0) │ │ 0 / 1 │ │  11010   │
  └───────┘ └──────────────┘ └───────┘ └──────────┘
     tag bit           val
```

- `.×` → 0, `.✓` → 1.
- `PAXO_TAG_BIT = 0x0`.

### 3.2 trit (lógico ternario) — marcador `11010`, tag `01`

```
 bits 63..62    │  bits 6..5  │  bits 4..0
  ┌─────────┐   ┌────────────┐ ┌──────────┐
  │   01    │   │     t      │ │  11010   │
  └─────────┘   └────────────┘ └──────────┘
    tag trit          trit
```

Valores: `×` = 0, `•` = 1, `✓` = 2. `PAXO_TAG_TRIT = 0x1`.

### 3.3 char (UTF-32) — marcador `11010`, tag `10`

```
 bits 63..62   bits 61..37  bits 36..5   bits 4..0
  ┌─────────┐  ┌──────────┐ ┌──────────┐ ┌──────────┐
  │   10    │  │  padding │ │ char32   │ │  11010   │
  └─────────┘  └──────────┘ └──────────┘ └──────────┘
   tag char
```

Un solo código Unicode (hasta 4 × UTF-8). `PAXO_TAG_CHAR = 0x2`. El bit 37
siempre queda en 0, lo que lo distingue de color (ver 3.4).

### 3.4 color — marcador `11010`, tag `10` + flag

```
 bits 63..62   bit 37   bits 36..5 (RGBA: r·g·b·a)   bits 4..0
  ┌─────────┐ ┌──────┐ ┌───────────────────────────┐ ┌──────────┐
  │   10    │ │  f=1 │ │  8r │ 8g │ 8b │ 8a         │ │  11010   │
  └─────────┘ └──────┘ └───────────────────────────┘ └──────────┘
   tag char     flag
```

- `PAXO_COLOR_FLAG = (1ULL << 37)`. El flag en el bit 37 distingue **color** de
  **char** (los codepoints UTF-32 ≤ 0x1FFFFF nunca activan ese bit).
- Los 32 bits de valor = `(r<<24) | (g<<16) | (b<<8) | a`, cada canal 0..255.
- Literal fuente: `#RRGGBB` o `#RRGGBBAA`.

### 3.5 referencia (pin / array / package / función / string) — marcador `11010`, tag `11`

```
 bits 63..62   bits 26..23  bits 22..21   bits 20..5   bits 4..0
  ┌─────────┐  ┌──────────┐ ┌───────────┐ ┌──────────┐ ┌──────────┐
  │   11    │  │  sub(4)  │ │ aux13(13) │ │ punt32   │ │  11010   │
  └─────────┘  └──────────┘ └───────────┘ └──────────┘ └──────────┘
   tag ref
```

- `sub` (4 bits, bits 22..19 efectivos según implementación `sub & 0x7` +
  desplazamientos) — sub-tipo dentro de referencia.
- `punt` (32 bits) — índice en la tabla global de objetos (`paxo_objects`), que
  guarda los punteros reales (`void*`). Así, las referencias son índices, no
  punteros crudos.
- `aux` (13 bits) — información auxiliar (p. ej. número de parámetros de una
  función, offset relativo).

Sub-tipos de referencia:

| sub | Valor |
|-----|-------|
| `REF_SUB_ARRAY` | 0 |
| `REF_SUB_PKG` | 1 |
| `REF_SUB_STRING` | 2 |
| `REF_SUB_FUNC` | 3 |
| `REF_SUB_PIN` | 4 |

Esto cubre: `pin` (puntero), arrays, packages, funciones y strings.

### 3.6 punto fijo / entero y decimal empaquetado — marcador `11011`

Dos formatos con el mismo marcador bajo, distinguidos por `t` (bit 63).

**Entero escalado (`int`, tipo `INT_FP`) — `t = 0`:**

```
 bits 63    bits 62..59  bits 58..57  bit 56    bits 55..43   bits 42..5   bits 4..0
 ┌────────┐ ┌───────────┐ ┌──────────┐ ┌───────┐ ┌────────────┐ ┌──────────┐ ┌────────┐
 │   0    │ │   pppp    │ │ padding  │ │  s    │ │  xxxx(13)  │ │ padding  │ │ 11011  │
 └────────┘ └───────────┘ └──────────┘ └───────┘ └────────────┘ └──────────┘ └────────┘
 └──tó 1──┘     escala                                        valor escalado (con signo)
```

- `pppp` (4 bits, 0..15): escala = cantidad de dígitos fraccionarios.
- `s` (1 bit): signo.
- `xxxx` (13 bits): **magnitud entera escalada** con signo. Valor real =
  `±magnitud · 10^(-escala)`. Rango de magnitud `0..8191` (limita la precisión
  entera, no decimal).

**Decimal empaquetado BCD (`pdec`, tipo `PKDEC`) — `t = 1`:**

```
 bits 63    bits 62..59  bit 58   bit 57   bits 56..5 (13 nibbles, dígito d12 en los bits 53..56 … unidades d0 en los bits 5..8)   bits 4..0
 ┌────────┐ ┌───────────┐ ┌──────┐ ┌──────┐ ┌───────────────────────────────────────────────────────────────────────────────────────┐ ┌────────┐
 │   1    │ │   pppp    │ │  s   │ │ pad. │ │  d12 ··· d1 d0           (13 dígitos decimales, un nibble cada uno, d0 = unidades)    │ │ 11011  │
 └────────┘ └───────────┘ └──────┘ └──────┘ └───────────────────────────────────────────────────────────────────────────────────────┘ └────────┘
 └──tó 1──┘    escala      signo
```

- `pppp` (4 bits, 0..15): escala = dígitos fraccionarios (`pdec(6.50)` → 2).
- `s` (1 bit): signo.
- `d0..d12` (52 bits = 13 nibbles): **mantisa BCD genuina**, cada nibble es un
  dígito decimal. El valor real es `(-1)^s · (Σ d_i·10^i) · 10^(-escala)` con
  `i` desde las unidades (`d0`, bits 5..8) hasta `d12` (bits 53..56).
- El cálculo suma/resta/compara alineando las magnitudes en `__int128`
  (acarreo/borrow decimal real, portando entre nibbles); no hay saturación a
  13 bits sino a 13 dígitos (`9999999999999`).

Constructores: `var_int_fp(valor, escala)` (entero) y
`var_pkdec(valor, escala)` (BCD). `int` y `pdec` son tipos distintos:
`sac(int)→pdec` re-encodifica a BCD (exacto, conserva escala) y
`sac(pdec)→int` redondea; las operaciones mixtas operan en el dominio `pdec`
(si hay algún operando `pdec`) o en el dominio entero escalado.

### 3.7 MP16 embebido — marcador `11100`

```
 bits 63..21            bits 20..5         bits 4..0
 ┌────────────────────┐ ┌─────────────────┐ ┌──────────┐
 │     padding (43)   │ │  raw MP16 (16)  │ │  11100   │
 └────────────────────┘ └─────────────────┘ └──────────┘
```

- El `Num16` empaquetado (`num16_pack`) se desplaza `PAXO_VAL_SHIFT` bits y se
  le OR `PAXO_MARK_N16`.
- `PAXO_ZERO` es `var_num16((Num16){0})` — el cero de la máquina.
- Un MP16 embebido permite números compactos dentro de una palabra de 64 bits
  sin indirección.

### 3.8 Número MP64 directo

```
 bits 63..5                  bits 4..0
 ┌──────────────────────────┐ ┌──────────┐
 │  s │ exp(8) │ bc(50) │p(5)│ │ != marc. │
 └──────────────────────────┘ └──────────┘
```

`NP64` se guarda con `[signo | exp<<1 | bc<<9 | p<<59]`; es un número MP64
siempre que el marcador bajo no coincida con `11010`/`11011`/`11100`.

---

## 4. Formato de 16 bits (diseño)

Una celda de 16 bits con los bits 0..1 candidatos a marcador `Bc` (2 bits).

```
S ee 5bc ppp        Número MP16
00 ············· x   bit
01 ············ xx   trit
10 000 xxxxxxxx      char UTF-8 (un byte)
```

| bits 15..2 | bits 1..0 | Tipo |
|-----------|-----------|------|
| `Bc = 00` + padding + valor (1 bit) | `10` | bit |
| `Bc = 01` + padding + valor (2 bits) | `10` | trit |
| `Bc = 10` + `000` + char (8 bits) | `10` | char UTF-8 |

> No implementado aún en la VM; es el objetivo para variables compactas.

---

## 5. Detección de tipo

`var_type(v)`:

1. Lee `mark = v & 0x1F`.
2. Si `mark == 11010`: mira los 2 bits altos (`v >> 62`):
   - `00` → BOOL, `01` → TRIT, `10` → CHAR o COLOR (según flag bit 37),
     `11` → REF (según sub-tipo: ARRAY/PKG/STRING/FUNC/POINT).
3. Si `mark == 11011`: `v>>63` → `PKDEC` (1) o `INT_FP` (0).
4. Si `mark == 11100`: NUM16.
5. Otro → NUM64.

`var_is_num(v)` es verdadero solo si el marcador **no** es `11010`, `11011` ni
`11100` — es decir, solo para números MP64. MP16 (`var_num16`) y los tipos
nuevos no califican como "num relajado" para aritmética directa.

---

## 6. Ejemplos

| Valor | Representación conceptual |
|-------|---------------------------|
| `.✓` (true) | `[01 pad] [1] 11010` → bits `00…1 11010` |
| `.×` (false) | `[01 pad] [0] 11010` |
| `'A'` | tag `10`, `000…65 << 5`, `11010` |
| `#FF8000` | tag `10`, flag=1, `r=FF g=80 b=00 a=FF`, `11010` |
| `int 45` (escala 1) | `t=0 pppp=0001 s=0 x=45` `11011` |
| `pdec $6.50` | `t=1 pppp=0010 s=0 x=650` `11011` |
| `4.5` (MP64) | número MP64 directo |

Nota: los valores mp64 se interpretan siempre como **num64** al imprimir; por
eso `6.7000` sale con la precisión del MP64.

---

## 7. Constantes en `Calc.c`

| Constante | Valor | Uso |
|-----------|-------|-----|
| `PAXO_MARK_MASK` | `0x1F` | máscara de marcador |
| `PAXO_MARK_BOX` | `0x1A` | `11010` bit/trit/char/color/ref |
| `PAXO_MARK_FXPKD` | `0x1B` | `11011` int-fixed / packed decimal |
| `PAXO_MARK_N16` | `0x1C` | `11100` MP16 |
| `PAXO_VAL_SHIFT` | `5` | corrimiento de los campos de valor |
| `PAXO_COLOR_FLAG` | `1<<37` | distingue color de char |
| `PAXO_TAG_BIT` | `0x0` | tag booleano |
| `PAXO_TAG_TRIT` | `0x1` | tag trit |
| `PAXO_TAG_CHAR` | `0x2` | tag char/color |
| `PAXO_TAG_REF` | `0x3` | tag referencia |

El layout vive en `Src/Vm/Src/Calc.c` (constructores `var_*` y accesores
`var_*_get`). El bytecode lleva un byte de tipo por literal (`TYPE_*`) que la
VM reconstruye con los constructores correspondientes en `OP_PUSH`.
