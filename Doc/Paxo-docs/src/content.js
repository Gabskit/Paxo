// Contenido de la documentación de Paxo.
// Cada sección: { id, nav, title, badges, intro, examples:[{caption, code, foot}], notes:[{kind,html}] }

const sections = [
  // =================================================================
  {
    id: "inicio",
    nav: "Inicio",
    title: "Paxo",
    intro: `
      <div class="hero">
        <img src="/src/assets/mascot.png" alt="mascota de Paxo" />
        <div class="blurb">
          Lenguaje de programación de <b>tipado dinámico</b>, multiparadigma,
          con <b>VM propia</b> y empaquetado de valores por <b>nanboxing</b>.
          Diseñado para el ahorro de memoria con variables de diferentes
          tamaños.
          <p>Documentación del compilador (<code class="inline-code">Src/Bcgen</code>),
          la VM (<code class="inline-code">Src/Vm</code>) y la especificación
          <a href="#nanbox">Nanbox</a>.</p>
        </div>
      </div>`,
    examples: [
      {
        caption: "Hola mundo",
        code: `println("hola mundo");`,
      },
      {
        caption: "Bucle con el nuevo formato de bloque",
        code: `n i = 0
(i < 3): ▶️ :
    i++
    println("ciclo ", i)
🏁`,
      },
    ],
  },

  // =================================================================
  {
    id: "build",
    nav: "Build y uso",
    title: "Estructura, build y uso",
    intro: `
      <p class="lead">El proyecto se compila con npm/antlr (generador de parser),
      Go (compilador a bytecode) y C (VM).</p>`,
    examples: [
      {
        caption: "Scripts disponibles",
        code: `npm run build        # build completo (antlr + bcg + vm + lep.h)
npm run build:bcg    # compilar compilador a bytecode (Go)
npm run build:vm     # compilar la VM (C → Build/Lepvm)
npm run gen:lep      # generar lep.h (single-header library)
npm run antlr        # regenerar el parser desde Paxo.g4
npm run test:vm      # ejecutar la batería de pruebas de la VM
npm run test:bcg     # ejecutar las pruebas del compilador`,
      },
      {
        caption: "Compilar y ejecutar",
        code: `# compilar un archivo .paxo a bytecode
./Build/Bcg programa.paxo programa.pbc

# ejecutar el bytecode con la VM
./Build/Lepvm programa.pbc`,
      },
    ],
    notes: [
      { kind: "info", html: `La VM se compila a <b>-O3</b>. Al construir las
        dependencias de terceros (chipmunk/pdfio/zlib, etc.) el build puede
        tardar varios minutos; se recomienda un timeout amplio.` },
    ],
  },

  // =================================================================
  {
    id: "tipos",
    nav: "Tipos",
    title: "Tipos",
    badges: ["new: int, pdec, col"],
    intro: `
      <p class="lead">Paxo es de tipado dinámico: cada valor lleva su tipo en el
      nanbox de 64 bits. El tipo se puede declarar o inferir con
      <code class="inline-code">var</code>.</p>`,
    examples: [
      {
        caption: "Tipos básicos",
        code: `n foo = 6.7            // número (inferido como num64)
sn foo = 3.14           // número compacto (MP16)

trit foo = •            // trit (ternario: •, ↑, ↓)
bool foo = .×           // booleano bit (.× = falso, .✓ = true)

abc foo = 'C'           // caracter (UTF-32)
abc foo = "Texto"       // string
pin goo = @foo          // puntero / referencia

int foo = 45            // entero / punto fijo      (nanbox 11011, t=0)
pdec foo = 6.50         // decimal empaquetado      (nanbox 11011, t=1)
col foo = #FF8000       // color RGBA #RRGGBB o #RRGGBBAA (nanbox 11010)`,
      },
      {
        caption: "Inspeccionar el tipo con typeof",
        code: `n x = 6.7
int i = 5
pdec d = 0
col c = #A1B2C3DD

println(x, typeof(x));   // 6.7000 num64
println(i, typeof(i));   // 5 int
println(c, typeof(c));   // #A1B2C3DD col`,
      },
    ],
    notes: [
      { kind: "info", html: `Los literales numéricos se empaquetan como
        <b>num64</b> por defecto. Los tipos <code class="inline-code">int</code>,
        <code class="inline-code">pdec</code> y <code class="inline-code">col</code> usan
        marcadores nanbox propios y no califican como "num relajado" para
        aritmética directa; comprueba con <code class="inline-code">typeof</code>.` },
      { kind: "warn", html: `El modificador de scope <code class="inline-code">local</code>
        está <b>deprecado</b>; el compilador avisa y recomienda declarar
        directamente el tipo (<code class="inline-code">n i = 0</code>).` },
    ],
  },

  // =================================================================
  {
    id: "arrays",
    nav: "Arrays",
    title: "Arrays",
    intro: `
      <p class="lead">Los arrays almacenan <b>tipos mixtos</b> y se crean con
      <code class="inline-code">«»</code>.</p>`,
    examples: [
      {
        caption: "Creación y acceso por índice",
        code: `var mixed = «"hola", .✓, 42»   // mixto: string, bool, num
arr[0]                     // "hola"
arr[1]                     // .✓
arr[1] = 99;               // asignación por índice`,
      },
      {
        caption: "Funciones nativas de arrays",
        code: `array_push(arr, val)      // agrega un elemento al final
array_contains(arr, val)   // ¿contiene al valor? → .✓ / .×`,
      },
    ],
  },

  // =================================================================
  {
    id: "paquetes",
    nav: "Paquetes",
    title: "Paquetes (clases)",
    intro: `
      <p class="lead">Los bloques <code class="inline-code">{}</code> declaran
      paquetes con campos propios. Se accede con notación de punto
      (<code class="inline-code">pkg.campo</code>).</p>`,
    examples: [
      {
        caption: "Declaración y acceso",
        code: `perro {
    var nombre = "Rex"
    var patas = 4
}   // asignación al bloque

// acceso
println(perro.nombre)   // Rex`,
      },
      {
        caption: "Campos de distintos tipos",
        code: `app {
    var nombre = "Paxo"
    var version = 2
    var colores = «#FF0000, #00FF00, #0000FF»
}`,
      },
    ],
  },

  // =================================================================
  {
    id: "funciones",
    nav: "Funciones",
    title: "Funciones",
    intro: `
      <p class="lead">Las funciones se declaran como paquetes que reciben
      parámetros. Pueden declarar el tipo de retorno con
      <code class="inline-code">: tipo</code>.</p>`,
    examples: [
      {
        caption: "Función simple",
        code: `sumar = (n a, n b) {
    return a + b
}`,
      },
      {
        caption: "Función con tipo de retorno",
        code: `sumar = (n a, n b) : n {
    return a + b
}`,
      },
      {
        caption: "Return y condicionales",
        code: `buscar = (n x) : bool {
    cond (x > 10) {
        .✓ => return .✓
        _   => return .×
    }
}`,
      },
      {
        caption: "Función tipada",
        code: `📥 sumar = (n a, n b) : n {
    return a + b
}`,
      },
    ],
  },

  // =================================================================
  {
    id: "bucles",
    nav: "Bucles",
    title: "Bucles",
    badges: ["dep: |: :|"],
    intro: `
      <p class="lead">Un bucle abre con condición y modo, seguido de un bloque.
      El cuerpo es un <b>bloque</b>: llaves <code class="inline-code">{ ... }</code>
      o el formato alternativo <code class="inline-code">: ... 🏁</code>.</p>`,
    examples: [
      {
        caption: "Con llaves",
        code: `(condicion): ▶️ {
    // código
}`,
      },
      {
        caption: "Con el formato de bloque : … 🏁 (recomendado)",
        code: `n i = 0
(i < 3): ▶️ :
    i++
    println("ciclo ", i)
🏁
// imprime: ciclo 1, ciclo 2, ciclo 3`,
      },
    ],
    notes: [
      { kind: "info", html: `Modos de bucle:
        <ul>
          <li><code class="inline-code">⏸️</code> | <code class="inline-code">||</code>:
          ejecuta hasta que la condición sea verdadera (while not).</li>
          <li><code class="inline-code">▶️</code> | <code class="inline-code">|&gt;</code>:
          ejecuta mientras la condición sea verdadera (while).</li>
        </ul>` },
      { kind: "warn", html: `Los delimitadores <code class="inline-code">|:</code> /
        <code class="inline-code">:|</code> (o <code class="inline-code">𝄆</code> /
        <code class="inline-code">𝄇</code>) están <b>deprecados</b>. Siguen
        aceptándose por retrocompatibilidad pero el compilador emite: <i>
        "el delimitador de bucle '|:' está deprecado; usa el nuevo formato de
        bloque"</i>. Usa <code class="inline-code">{ ... }</code> o
        <code class="inline-code">: ... 🏁</code> en código nuevo.` },
    ],
  },

  // =================================================================
  {
    id: "condicionales",
    nav: "Condicionales",
    title: "Condicionales",
    intro: `
      <p class="lead">El condicional compara la condición con cada valor usando
      igualdad (<code class="inline-code">==</code>). El caso
      <code class="inline-code">_</code> es el wildcard (siempre ejecuta).</p>`,
    examples: [
      {
        caption: "cond / switch",
        code: `n x = 5
cond (x) {
    1 => println("lunes")
    2 => println("martes")
    _ => println("otro día")
}`,
      },
      {
        caption: "Condicional con rango / umbral",
        code: `n dia = 6
cond (dia) {
    6 => println("casi fin de semana")
    7 => println("fin de semana!")
    _ => println("entre semana")
}`,
      },
    ],
  },

  // =================================================================
  {
    id: "operadores",
    nav: "Operadores",
    title: "Operadores",
    intro: `<p class="lead">Operadores disponibles:</p>`,
    examples: [
      {
        caption: "Tabla de operadores",
        code: `==    igual
=     asignación
++ -- incremento, decremento
<  >  menor, mayor
≤  ≥  menor o igual, mayor o igual
+  -  suma, resta
×  ÷  multiplicación, división`,
      },
    ],
  },

  // =================================================================
  {
    id: "errores",
    nav: "Errores",
    title: "Manejo de errores",
    intro: `<p class="lead">Bloques try/catch con sintaxis de flecha.</p>`,
    examples: [
      {
        caption: "try / catch",
        code: `↻ {
    // código que puede fallar
} 🪤 | /] (error) {
    // manejo del error
}`,
      },
      {
        caption: "throw y return",
        code: `throw expresión;   // lanza un error
return;            // retorna sin valor`,
      },
    ],
  },

  // =================================================================
  {
    id: "nativas",
    nav: "Funciones nativas",
    title: "Funciones nativas",
    intro: `<p class="lead">Funciones integradas en la VM, agrupadas por dominio.
    </p>`,
    examples: [
      {
        caption: "Entrada / Salida",
        code: `print(valor, ...)      // imprime sin salto de línea
println(valor, ...)    // imprime con salto de línea
// soportan múltiples argumentos`,
      },
      {
        caption: "Archivos",
        code: `file_open(ruta, modo)
file_read(archivo)
file_write(archivo, contenido)
file_close(archivo)
// las rutas son relativas al directorio desde donde se ejecuta la VM`,
      },
      {
        caption: "Gráficos en terminal (ANSI)",
        code: `init_window(ancho, alto)
draw_rect(x, y, ancho, alto)
draw_circle(x, y, radio)
draw_text(x, y, texto)
draw_line(x1, y1, x2, y2)`,
      },
      {
        caption: "Imágenes (stb_image)",
        code: `img_info(ruta)                 // → [w, h, canales]
img_load(ruta)                 // → [píxeles...] 0..255
img_save(ruta, píxeles, w, h)`,
      },
      {
        caption: "Audio (miniaudio)",
        code: `audio_play(ruta, .✓)
audio_loop(ruta)
audio_volume(handle, vol)   // volumen 0..1+, .✓ / .×`,
      },
      {
        caption: "Física 2D (Chipmunk2D)",
        code: `phys_new_space()
phys_new_body(masa, inercia)
phys_add_body(space, body)
phys_step(space, dt)
phys_box(space, body, w, h)
phys_collide(shape_a, shape_b)   // → .✓ / .×`,
      },
    ],
  },

  // =================================================================
  {
    id: "nanbox",
    nav: "Nanbox",
    title: "Nanbox",
    intro: `
      <p class="lead">Cada valor es una palabra de 64 bits
      (<code class="inline-code">PaxoVar</code>) que autocontiene su tipo mediante
      <b>marcadores</b>: no hay metadatos separados por variable. La especificación
      completa vive en <a href="/Nanbox.md">Nanbox.md</a>.</p>`,
    examples: [
      {
        caption: "Marcadores (bits 4..0)",
        code: `11010 (0x1A)  BOX       → bit, trit, char, color, referencia
11011 (0x1B)  FXPKD     → int / punto fijo (t=0), pdec (t=1)
11100 (0x1C)  MP16      → número MP16 embebido
otro                    → número MP64 directo`,
      },
      {
        caption: "Color: BOX + tag char + flag",
        code: `bits 63..62    bit 37   bits 36..5 (RGBA)      bits 4..0
   10         f=1       8r 8g 8b 8a          11010
// PAXO_COLOR_FLAG = 1<<37 distingue color de char`,
      },
      {
        caption: "int / pdec: marcador FXPKD",
        code: `bit 63    bits 62..59  bit 56   bits 55..43   bits 4..0
 t        pppp        s        xxxx(13)    11011
t = 0 → int / punto fijo     t = 1 → pdec
valor = magnitud · 10^(-escala)  (con signo)`,
      },
      {
        caption: "MP16 embebido",
        code: `bits 63..21      bits 20..5        bits 4..0
 padding (43)    raw MP16 (16)    11100`,
      },
    ],
    notes: [
      { kind: "info", html: `Los constructores (<code class="inline-code">var_*</code>)
        y accesores (<code class="inline-code">var_*_get</code>) viven en
        <code class="inline-code">Src/Vm/Src/Calc.c</code>. El bytecode lleva un byte
        <code class="inline-code">TYPE_*</code> por literal que la VM reconstruye en
        <code class="inline-code">OP_PUSH</code>.` },
      { kind: "warn", html: `Cambio reciente: MP16 pasó del marcador
        <code class="inline-code">11011</code> al <code class="inline-code">11100</code>
        (0x1C) para dejar <code class="inline-code">11011</code> a los nuevos tipos
        <code class="inline-code">int</code> y <code class="inline-code">pdec</code>.` },
    ],
  },

  // =================================================================
  {
    id: "changelog",
    nav: "Cambios",
    title: "Changelog reciente",
    intro: `<p class="lead">Últimos cambios de la documentación y el código.</p>`,
    examples: [
      {
        caption: "Nuevos tipos: int, pdec, col",
        code: `int : entero / punto fijo        (nanbox 11011, t=0)
pdec: decimal empaquetado         (nanbox 11011, t=1)
col : color RGBA                  (nanbox 11010 + flag de color)
// literal de color: #RRGGBB o #RRGGBBAA`,
      },
      {
        caption: "Deprecación de |: :|",
        code: `// ANTES (deprecado, con aviso del compilador)
(cond): ▶️ |: ... :|

// AHORA (recomendado)
(cond): ▶️ { ... }
// o
(cond): ▶️ : ... 🏁`,
      },
    ],
  },
];

const navLabels = sections.map((s) => ({ id: s.id, nav: s.nav }));

export { sections, navLabels };
