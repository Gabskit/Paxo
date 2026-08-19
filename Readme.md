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
│       ├── Calc.c      # Tipos y estructuras de datos
│       ├── Deque.c     #Deque (pila doble)
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
var foo = 6.7          // número (inferido)
n foo = 6.7

var foo = •            // trit (ternario: •, ↑, ↓)
trit foo = •

var foo = 'C'          // caracter
abc foo = 'C'

var foo = "Texto"      // string
abc foo = "Texto"

var goo = @foo          // puntero
pin goo = @foo

var foo = .×            // booleano bit (.× = false, .• = true)
bool foo = .×

var foo[] = «4, 5.08, •, "arreglos", «6 + 8.0, 7»»  // arreglo (anidado)
```

### Paquetes

```
var foo = {
  var goo = "Paquetes"   // contiene variables y funciones
}
```

### Funciones

```
var foo = (){
  var goo = "Esto es una función"
  return goo;
}
```

## Tamaños de variable

```
n8    8 bits
n16   16 bits
n32   32 bits
n64   64 bits
```

## Acceso de variables

```
local var    // local al scope actual
pub var      // global
🌎 var       // global (alias)
```

## Funciones

```
📥 var name = (){
  //codigo
}
```

Las funciones también pueden estar en paquetes para generar clases:

```
pub var hi = {
  local var i1 = 8
  local var metodo = (){
    //codigo
  }
}
```

## Condicionales

```
(expresión | variable)?
    //caso default
  : 'a' ->
    //caso a
  : (expresión) ->
    //caso
  : _ ->
    //caso por defecto
  ;
```

## Bucles

```
(condicion): ⏸️ | ▶️ |:
  //codigo
:|
```

- `⏸️` | `||`: ejecuta hasta que la condición sea verdadera (while not)
- `▶️` | `>`: ejecuta mientras la condición sea verdadera (while)

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
| `<`, `>` | menor, mayor |
| `≤`, `≥` | menor o igual, mayor o igual |
| `≠` | distinto |
| `+`, `-` | suma, resta |
| `×`, `÷` | multiplicación, división |
| `√` | raíz cuadrada |
| `•«`, `»•` | desplazamiento de bits izq/der |
| `&`, `\|`, `!` | and, or, not lógico |
| `.&`, `.\|`, `.!` | and, or, not bit a bit |
| `^` | xor |

## Funciones nativas

### Entrada/Salida

```
print(valor, ...)       // imprime sin salto de línea
println(valor, ...)     // imprime con salto de línea
scan(@var1, @var2, ...) // lee entrada del usuario (punteros)
```

Soportan múltiples argumentos:

```
println("hola mundo");
println("nota: ", 8.5);
print("suma: ", 2 + 3);
scan(@goo, @foo);
```

### Información de tipos

```
typeof(valor)   // retorna el tipo del valor como char
```

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
local var entero = •
local var i = 0
pub var main = (){
  entero = 9
  (i > 50): || |:
  i++
  :|
  ↻{
    (i ≠ 1000) ?
      i = "completado"
    : _ →
      i = "en progreso"
    ;
  } 🪤 (paxo.vartype) {
    print(i)
  }
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

## Licencia

ISC
