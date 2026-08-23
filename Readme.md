# Paxo

Lenguaje de programación de tipado dinámico, multiparadigma, con VM propia. Diseñado para el ahorro de memoria mediante variables de diferentes tamaños.

## Estructura del proyecto

```
Paxo/
├── Src/
│   ├── Bcgen/          # Compilador a bytecode (Go + ANTLR)
│   │   ├── cmd/paxocc/ # Entry point del compilador
│   │   ├── Paxo.g4     # Gramática ANTLR
│   │   └── abytec.go   # Generador de bytecode
│   └── Vm/Src/         # Virtual Machine (C)
│       ├── Main.c      # Entry point de la VM (lepvm)
│       ├── Vm.c        # Intérprete de bytecode
│       ├── Functions.c # Funciones nativas (print, colores, etc.)
│       ├── Calc.c      # Tipos y estructuras de datos (incluye arrays, packages)
│       ├── Deque.c     # Deque (pila doble)
│       ├── Typecast_and_read.c # Conversión de tipos
│       └── termcolor-c.h       # Colores ANSI en terminal
├── sh/
│   └── gen_lep.sh      # Genera lep.h (single-header)
├── Build/              # Binarios generados
├── go.mod
├── package.json
└── Readme.md
```

## Requisitos

- [Go](https://go.dev/) >= 1.23
- [Clang](https://clang.llvm.org/) (con soporte `-std=gnu23`)
- [Node.js](https://nodejs.org/) (para ANTLR y scripts de build)
- [ANTLR](https://www.antlr.org/) (`npm install` instala `antlr-ng`)

## Build

```bash
npm install          # Instalar dependencias (antlr-ng)
npm run build        # Build completo (antlr + bcg + vm + lep.h)
```

Scripts individuales:

```bash
npm run build:bcg    # Compilar compilador a bytecode (Go)
npm run build:vm     # Compilar VM (C → Build/Lepvm)
npm run gen:lep      # Generar lep.h (single-header library)
npm run antlr        # Regenerar parser desde Paxo.g4
```

## Uso

```bash
# Compilar un archivo .paxo a bytecode
./Build/Bcg archivo.paxo archivo.pbc

# Ejecutar bytecode con la VM
./Build/Lepvm archivo.pbc
```

## Tipos

```
var foo = 6.7          // número (inferido, siempre num64)
n foo = 6.7
sn foo = 3.14

var foo = •            // trit (ternario: •, ↑, ↓)
trit foo = •

var foo = 'C'          // caracter
abc foo = 'C'

var foo = "Texto"      // string
abc foo = "Texto"

var goo = @foo          // puntero
pin goo = @foo

var foo = .×            // booleano bit (.× = false, .✓ = true)
bool foo = .×
```

Los literales numéricos se empaquetan como **num64** por defecto. Los tamaños se removieron al no dar ahorro de memoria por el funcionamiento de la vm propiamente

## Arrays

Los arrays almacenan **tipos mixtos** y se crean con la sintaxis `«»`:

```
var arr = «1, 2, 3»                        // array de números
var mixed = «"hola", .✓, 42»               // mixto: string, bool, num
var nested = ««1, 2», «3, 4, 5»»          // arrays anidados
var vacio = «»                              // array vacío
```

### Acceso por índice

```
var arr = «10, 20, 30»
println(arr[0]);    // 10
println(arr[2]);    // 30
arr[1] = 99;        // asignación por índice
println(arr);        // «10, 99, 30»
```

Las expresiones también funcionan:

```
arr[2] = arr[0] + arr[1];
arr[0] = 100;
```

### Funciones nativas de arrays

```
array_len(arr)        // retorna longitud del array
array_push(arr, val)  // agrega un elemento al final
```

**Ejemplo completo:**

```
var arr = «1, 2, 3»
println(array_len(arr));    // 3

array_push(arr, 99)
println(arr);               // «1, 2, 3, 99»
println(array_len(arr));    // 4

println(arr[1]);            // 2
```

### Nota sobre tipos mixtos

Los arrays pueden contener cualquier tipo:

```
var datos = «"Paxo", 42, .✓, •, 'X'»
println(datos[0]);    // Paxo
println(datos[1]);    // 42
println(datos[2]);    // true
```

## Paquetes (clases)

Los bloques `{}` declaran paquetes con campos propios. Se accede a los campos con notación de punto (`pkg.campo`):

```
var persona = {
    var nombre = "Paxo";
    var edad = 25;
    var activo = .✓;
}

println(persona.nombre);    // Paxo
println(persona.edad);      // 25
println(persona.activo);    // true
println(typeof(persona));   // package
```

Los campos pueden contener arrays u otros tipos:

```
var config = {
    var lang = "paxo";
    var version = 2;
    var debug = .✓;
}

println(config.lang);       // paxo
println(config.version);    // 2
```

El acceso encadenado funciona: `obj.tags[0]`, `obj.tags[1]`, etc.

## Funciones

```
var foo = () {
    var goo = "Esto es una función"
    return goo;
}
```

Las funciones pueden declarar tipo de retorno con `: tipo` después de los paréntesis:

```
📥 sumar = (n a, n b) : n {
    return a + b;
}
```

### Return

```
return expresión;    // retorna un valor
return;              // retorna sin valor
```

**Ejemplo con cond:**

```
📥 buscar = (n x) : bool {
    (x) ? 42 -> {
        return .✓;
    } : _ -> {
        return .×;
    };
}
```

## Acceso de variables

```
local var    // local al scope actual
pub var      // global
🌎 var       // global (alias)
```

> **Nota:** Actualmente `local` y `pub` no separan scopes reales. Todas las variables se almacenan en un array flat de globals. Las variables dentro de funciones o bloques `{}` son accesibles desde afuera.

## Condicionales

```
(condición) ? valor -> {
    // caso: condición == valor
} : valor2 -> {
    // caso: condición == valor2
} : _ -> {
    // caso por defecto (wildcard)
} ;
```

El condicional compara la condición con cada valor usando igualdad (`==`). El caso `_` es el wildcard (siempre ejecuta). Se usan temp variables internamente para re-evaluar la condición en cada caso.

**Ejemplo:**

```
local n x = 5
(x) ? 5 -> {
    println("x es 5");
} : _ -> {
    println("x no es 5");
};
```

**Múltiples casos:**

```
local 📥 dia = "lunes"
(dia) ? "lunes" -> {
    println("Inicio de semana");
} : "viernes" -> {
    println("Casi fin de semana");
} : _ -> {
    println("Otro día");
};
```

## Bucles

```
(condicion): ⏸️ | ▶️ |:
    //codigo
:|
```

- `⏸️` | `||`: ejecuta hasta que la condición sea verdadera (while not)
- `▶️` | `|>`: ejecuta mientras la condición sea verdadera (while)

## Manejo de errores

```
↻ {
    //codigo
} 🪤 | /] (error){
    //manejo del error
}
```

## Operadores

| Operador | Descripción |
|----------|-------------|
| `==` | igual |
| `=` | asignación |
| `++`, `--` | incremento, decremento |
| `<`, `>` | menor, mayor |
| `≤`, `≥` | menor o igual, mayor o igual |
| `≠` | distinto |
| `+`, `-` | suma, resta |
| `×`, `÷` | multiplicación, división |
| `√` | raíz cuadrada |
| `•«`, `»•` | desplazamiento de bits izq/der |
| `&`, `\|` | and, or bit a bit |
| `.&`, `.\|` | and, or lógico |
| `!`, `.!` | not lógico, not bit a bit |

## Funciones nativas

### Entrada/Salida

```
print(valor, ...)       // imprime sin salto de línea
println(valor, ...)     // imprime con salto de línea
scan()                  // lee una línea de stdin, retorna string
```

Soportan múltiples argumentos:

```
println("hola mundo");
println("nota: ", 8.5);
print("suma: ", 2 + 3);

local 📥 nombre = ""
nombre = scan()
println("Hola ", nombre);
```

### Arrays

```
array_len(arr)          // retorna la cantidad de elementos
array_push(arr, valor)  // agrega un elemento al final del array
```

### Archivos

```
file_read(ruta)              // lee todo el archivo como string ("" si falla)
file_write(ruta, texto)      // escribe/sobrescribe, retorna .✓/.×
file_append(ruta, texto)     // agrega al final del archivo, retorna .✓/.×
file_exists(ruta)            // retorna .✓ si el archivo existe
file_delete(ruta)            // borra el archivo, retorna .✓/.×
```

**Ejemplo:**

```
file_write("datos.txt", "línea 1");
file_append("datos.txt", "línea 2");
println(file_read("datos.txt"));     // línea 1línea 2
println(file_exists("datos.txt"));   // true
file_delete("datos.txt");
```

> Las rutas son relativas al directorio desde donde se ejecuta la VM.

### Gráficos (terminal ANSI)

El lienzo se define con `init_window(ancho, alto)` y se dibuja con caracteres de bloque. Coordenadas **0-based** desde la esquina superior izquierda; lo que sale del lienzo se recorta.

```
init_window(ancho, alto)      // define el tamaño del lienzo, retorna .✓/.×
clear_screen()                // limpia la terminal
draw_rect(x, y, ancho, alto)  // rectángulo relleno con el color de texto actual
```

**Ejemplo:**

```
init_window(40, 12)
clear_screen()
text_color("red")
draw_rect(2, 1, 10, 4);
text_color("blue")
draw_rect(8, 3, 10, 4);
reset_color()
```

> Estas funciones dibujan en la terminal con códigos de escape ANSI (no requieren SDL ni OpenGL).

### Imágenes (stb_image)

Siempre disponibles (header-only, sin dependencias). Los píxeles son arrays de números 0..255.

```
img_load(ruta)                          // -> [w, h, canales, byte0, byte1, ...] ([] si falla)
img_info(ruta)                          // -> [w, h, canales] sin decodificar ([] si falla)
img_save_png(ruta, w, h, ch, datos)     // datos = array de píxeles; retorna .✓/.×
img_save_jpg(ruta, w, h, ch, datos)     // calidad fija 90; retorna .✓/.×
img_save_bmp(ruta, w, h, ch, datos)     // retorna .✓/.×
img_resize(datos, w, h, nw, nh, ch)     // -> array de píxeles reescalado ([] si falla)
```

**Ejemplo:**

```
local var px = «255,0,0, 0,255,0, 0,0,255, 255,255,0»;
img_save_png("test.png", 2, 2, 3, px);
local var img = img_load("test.png");
println(img[0], "x", img[1]);           // 2 x 2
local var mini = img_resize(px, 2, 2, 1, 1, 3);
```

### Fuentes (stb_truetype)

Siempre disponibles. Carga archivos `.ttf` y rasteriza glifos a bitmaps.

```
font_load(ruta)                     // -> handle (>0) o 0 si falla
font_glyph(font, codigo, tam_px)    // -> [w, h, off_x, off_y, avance, byte0, ...]
font_metrics(font, tam_px)          // -> [ascendente, descendente, linegap]
font_free(font)                     // libera la fuente
```

**Ejemplo:**

```
local var f = font_load("DejaVuSans.ttf");
local var m = font_metrics(f, 32);
local var g = font_glyph(f, 'A', 32);   // bitmap de cobertura 0..255
println(g[0], "x", g[1]);               // ancho x alto del glifo
font_free(f);
```

### Audio (miniaudio)

Siempre disponible. Reproduce MP3/WAV/FLAC/OGG, etc.

```
audio_init()                  // inicializa el motor, .✓/.× (idempotente)
audio_play(ruta, en_loop)     // -> handle (>0) o 0 si falla; inicia sonando
audio_pause(handle)           // pausa, .✓/.×
audio_resume(handle)          // reanuda, .✓/.×
audio_stop(handle)            // detiene y libera, .✓/.×
audio_volume(handle, vol)     // volumen 0..1+ , .✓/.×
audio_playing(handle)         // ¿sigue sonando?, .✓/.×
audio_quit()                  // detiene todo y libera el motor
```

**Ejemplo:**

```
local var s = audio_play("musica.ogg", .✓);
audio_volume(s, 80);
// ...
audio_stop(s);
```

### Física 2D (Chipmunk2D)

Siempre disponible: las fuentes oficiales se venden en
`Src/Vm/Src/third_party/chipmunk` y se compilan junto a la VM.
Espacios, cuerpos y formas se referencian por handles numéricos.

```
phys_space()                        // nuevo espacio -> handle
phys_gravity(space, gx, gy)
phys_step(space, dt)                // avanza la simulación un paso
phys_body(space, masa, inercia)     // cuerpo dinámico -> handle
phys_body_static(space)             // cuerpo estático -> handle
phys_pos(body)                      // -> [x, y]
phys_vel(body)                      // -> [vx, vy]
phys_set_pos(body, x, y)
phys_set_vel(body, vx, vy)
phys_angle(body)                    // ángulo en radianes
phys_set_angle(body, radianes)
phys_force(body, fx, fy)            // fuerza acumulada este paso
phys_impulse(body, ix, iy)          // impulso instantáneo
phys_circle(space, body, ox, oy, r) // forma círculo -> handle
phys_box(space, body, w, h)         // caja centrada en el cuerpo -> handle
phys_segment(space, body, ax, ay, bx, by, r)  // segmento -> handle
phys_elasticity(shape, e)           // rebote
phys_friction(shape, f)             // rozamiento
phys_collide(shape_a, shape_b)      // ¿están colisionando?, .✓/.×
phys_free_shape(shape) / phys_free_body(body)
phys_free_space(space)              // libera espacio + cuerpos + formas
```

**Ejemplo:** ver `Src/Testfiles/libs_phys.paxo`.

### Ventana y gráficos (SDL3, opcional)

Requieren SDL3 instalada en el sistema (`pkg-config --exists sdl3`);
el script de build las detecta solas. Si no está, `win_open` retorna `.×`
y el resto no hace nada.

```
win_open(titulo, w, h)      // abre ventana+renderer, .✓/.×
win_close()
win_color(r, g, b)          // color de dibujo 0..255
win_clear()                 // limpia con el color actual
win_rect(x, y, w, h)        // rectángulo relleno
win_line(x1, y1, x2, y2)
win_circle(cx, cy, radio)   // círculo relleno
win_text(x, y, texto)       // texto rápido (fuente interna 8x8)
tex_load(datos, w, h, ch)   // textura desde píxeles RGB/RGBA -> handle
tex_draw(tex, x, y [,w, h])
tex_free(tex)
win_show()                  // presenta el frame
win_poll()                  // procesa eventos -> array de strings:
                            //   "quit", "keydown:<tecla>", "keyup:<tecla>",
                            //   "mousedown", "mouseup"
win_key("A" | "Space" | ...)  // ¿tecla presionada?, .✓/.×
win_mouse()                 // -> [x, y]
win_mousedown()             // ¿botón izquierdo?, .✓/.×
win_time()                  // ms desde el inicio
win_delay(ms)
```

**Ejemplo:** ver `Src/Testfiles/libs_win.paxo`.

### PDF (pdfio)

Siempre disponible: las fuentes oficiales se venden en
`Src/Vm/Src/third_party/pdfio` (+ zlib en `third_party/zlib`) y se
compilan junto a la VM. Coordenadas en puntos desde la esquina
inferior izquierda.

```
pdf_open(ruta)                    // abre para lectura -> handle o 0
pdf_new(ruta [, ancho, alto])     // crea para escritura -> handle o 0
                                  // (tamaño por defecto: carta 612x792)
pdf_pages(doc)                    // cantidad de páginas (lectura)
pdf_page_size(doc, pagina)        // -> [ancho, alto]
pdf_text(doc, pagina)             // extrae el texto plano de una página
pdf_font(doc, "Helvetica")        // registra fuente base14 ("Courier",
                                  //  "Times-Roman", ...); retorna índice
pdf_page_begin(doc)               // comienza una página (escritura)
pdf_color(doc, r, g, b)           // color relleno/trazo 0..255
pdf_write_rect(doc, x, y, w, h)   // rectángulo relleno
pdf_write_line(doc, x1, y1, x2, y2)
pdf_write_text(doc, x, y, tam, texto)
pdf_close(doc)                    // guarda (escritura) o libera (lectura)
```

**Ejemplo:** ver `Src/Testfiles/libs_pdf.paxo`.

> Los handles retornados por física/audio/fuentes/texturas/PDF son números;
> usar un handle inválido (0 o liberado) hace que la función retorne `.×`,
> 0 o un array vacío según corresponda, sin romper la VM.

### Información de tipos

```
typeof(valor)   // retorna el tipo del valor como string
```

Valores posibles: `"num"`, `"bool"`, `"trit"`, `"char"`, `"pin"`, `"func"`, `"string"`, `"array"`, `"package"`

### Colores y formato

```
text_color(color)   // cambia el color del texto
bg_color(color)     // cambia el color del fondo
text_type(tipo)     // cambia el formato del texto
reset_color()       // resetea color y formato al default
```

**Colores disponibles:**

```
"red"     "green"    "blue"     "yellow"   "cyan"
"magenta" "white"    "gray"     "grey"
"dark red"     "dark green"    "dark blue"
"dark yellow"  "dark cyan"     "dark magenta"
"dark white"   "dark gray"
```

**Formatos disponibles:**

```
"bold"       // negrita
"dark"       // oscuro/dim
"underline"  // subrayado
"blink"      // parpadeo
"reverse"    // invertido
"concealed"  // oculto
```

**Ejemplo:**

```
text_color("red")
bg_color("blue")
text_type("bold")
println("texto rojo en negrita sobre fondo azul")
reset_color()
println("color normal")
```

## Ejemplo completo

```
// Arrays mixtos
local var arr = «1, 2, 3»
array_push(arr, 4);
println("Array: ", arr);
println("Len: ", array_len(arr));

// Asignación por índice
arr[0] = 100
println("arr[0]=100: ", arr);

// Nested arrays
local var nested = ««1, 2», «3, 4»»
println("nested[0]: ", nested[0]);

// Paquetes con dot-access
local var persona = {
    local var nombre = "Paxo"
    local var edad = 25
}
println("nombre: ", persona.nombre);

// Funciones con return
local 📥 sumar = (n a, n b) : n {
    return a + b
}
println("Suma: ", sumar(3, 4));

// Scan + cond
local 📥 entrada = ""
entrada = scan()
(entrada) ? entrada == "si" -> {
    println("Aceptado");
} : _ -> {
    println("Rechazado");
}
```

## Generación de lep.h

El script `sh/gen_lep.sh` genera un single-header (`Build/lep.h`) que empaqueta toda la VM como librería C para uso externo:

```bash
npm run gen:lep
```

## Test

```bash
npm run test        # Ejecuta todos los tests
npm run test:vm     # Tests de la VM
npm run test:bcg    # Tests del compilador (Go)
```

## Changelog reciente

### Funciones nativas de librerías (nuevo)
- Nuevas familias de funciones nativas: imágenes (`img_*`), fuentes
  (`font_*`), audio (`audio_*`), física 2D (`phys_*`), ventana/gráficos
  SDL3 (`win_*`, `tex_*`) y PDF (`pdf_*`). Ver sección "Funciones nativas"
- Chipmunk2D, pdfio y zlib se venden como **fuentes completas** en
  `Src/Vm/Src/third_party/` y se compilan junto a la VM (`sh/build_vm.sh`);
  no requieren instalación
- stb_image / stb_truetype / miniaudio siguen siendo header-only
- SDL3 es opcional: si `pkg-config` la detecta, el build habilita las
  funciones de ventana con `-DPAXO_ENABLE_SDL3`; si no, degradan sin romper

### Condicionales anidados (corregido)
- `(x) ? caso -> {...}` comparaba mal: saltaba según la veracidad del
  valor del caso en vez de compararlo con la condición; ahora emite
  `LOAD tmp; valor; EQ; JIF` correctamente
- Los condicionales son reentrantes: cada instancia usa su propio frame
  (variable temporal y bloques capturados), así que anidarlos dentro de
  otros condicionales o bucles ya no corrompe el bytecode

### Bucles anidados (corregido)
- El cierre del cuerpo del bucle se identifica por bloque exacto
  (no por profundidad), evitando cierres prematuros con bloques anidados

### Paquetes con dot-access (nuevo)
- `{ var campo = valor; }` crea objetos PACKAGE con campos propios
- `pkg.campo` accede a campos via notación de punto
- `typeof(pkg)` retorna `"package"`

### Asignación por índice (nuevo)
- `arr[i] = expr;` asigna valores en índices específicos
- Soporta expresiones: `arr[i] = arr[0] + arr[1]`

### Arrays (nuevo)
- Tipos `«»` para crear arrays con elementos mixtos
- Acceso por índice: `arr[i]`
- Nativas: `array_len()`, `array_push()`
- Soporte para arrays anidados: `««1,2», «3,4»»`
- Opcodes: `OP_ARRAY_NEW`, `OP_ARRAY_GET`, `OP_ARRAY_SET`

### Return (nuevo)
- Palabra clave `return` para retornar valores de funciones
- Funciona dentro de condicionales y bucles anidados

### typeof (corregido)
- Ahora retorna un string completo (`"num"`, `"bool"`, etc.) en vez de solo el primer carácter

### scan (nuevo)
- `scan()` lee una línea de stdin y la retorna como string

### Literales numéricos (corregido)
- Los literales enteros siempre se empaquetan como num64 para evitar pérdida de precisión del formato base-20

### NaN-boxing (nuevo)
- Los valores de la VM ahora son palabras de 64 bits NaN-boxed (`PaxoVar = uint64_t`)
- Formato num64 según especificación: `[s | 8e | 25bc(50b) | p5]`, bias 127
- Marcador `11010` en los 5 bits bajos para valores boxeados; tags en bits [63:62]: bit, trit, char utf32, ref
- num16 embebido via marcador reservado `11011`: `(raw16 << 5) | 27`
- Referencias (string/array/package/func/pin) con subtag en aux16 y tabla global de objetos para punteros reales

### Dark backgrounds (nuevo)
- `bg_color()` soporta variantes oscuras: `"dark red"`, `"dark cyan"`, etc.

### Dependencias vendidas (nuevo)
- Headers de Chipmunk2D (`chipmunk*.h`, `cp*.h`), NanoVG (`nanovg.h`) y SDL3
  (`SDL3/`, `SDL3_image/`, `SDL3_mixer/`, `SDL3_ttf/`) ahora viven en `Src/Vm/Src/`
- Los includes de librerías externas se activan solos con `__has_include`
  cuando sus dependencias están disponibles; la VM compila con o sin ellas
- Para usar las funciones reales de estas libs hace falta linkear los `.so`
  (p. ej. `-lSDL3 -lchipmunk -lnanovg`); hoy solo se usan sus declaraciones

## Licencia

ISC

## dependencias usadas

Vendidas como headers en `Src/Vm/Src/`:

[termcolor] [https://github.com/ararslan/termcolor-c.git]
[NanoVG] [https://github.com/memononen/nanovg.git]
[stb image, truetype, image_write, image_resize2] [https://github.com/nothings/stb.git]
[miniaudio] [https://miniaud.io/]
[Chipmunk2D headers] [https://codeberg.org/slembcke/Chipmunk2D]
[SDL3 / SDL3_image / SDL3_mixer / SDL3_ttf headers] [https://github.com/libsdl-org]
[PDF io header] [https://github.com/michaelrsweet/pdfio.git]

Externa (opcional, requiere SDL3 instalada para linkear):

[simple2d] [https://github.com/simple2d/simple2d.git]
