import antlr4 from "antlr4";
import AxolangLexer from "./AxolangLexer.js";
import AxolangParser from "./AxolangParser.js";
import AxolangListener from "./AxolangListener.js";

const HEADER_C = `
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <uchar.h>
#include <wchar.h>
#include <inttypes.h>

// Parche de compatibilidad Unicode para consolas Windows
#ifdef _WIN32
#include <windows.h>
#define AXO_INIT_CONSOLE() SetConsoleOutputCP(CP_UTF8)
#else
#define AXO_INIT_CONSOLE() (void)0
#endif

// --- FUNCIONES HELPER DE IMPRESIÓN (Para evitar Type Aliasing en _Generic) ---
static inline void _axo_print_char8(char8_t c) {
  printf("%c\t", (char)c);
}

static inline void _axo_print_char16(char16_t c) {
  printf("%lc\t", (wint_t)c);
}

static inline void _axo_print_char32(char32_t c) {
  char buf[5] = {
    0
  };
  mbstate_t st = {
    0
  };
  c32rtomb(buf, c, &st);
  printf("%s\t", buf);
}

static inline void _axo_print_float16_complex(_Float16 complex c) {
  printf("%f + %fi\t", crealf(c), cimagf(c));
}

static inline void _axo_print_float_complex(float complex c) {
  printf("%f + %fi\t", crealf(c), cimagf(c));
}

static inline void _axo_print_double_complex(double complex c) {
  printf("%lf + %lfi\t", creal(c), cimag(c));
}

static inline void _axo_print_ldouble_complex(long double complex c) {
  printf("%Lf + %Lfi\t", creall(c), cimagl(c));
}

// Helpers para enteros gigantes de lvar y xlvar (Conversión segura a texto para printf)
static inline void _axo_print_int128(_BitInt(128) n) {
  if (n == 0) {
    printf("0\t"); return;
  }
  if (n < 0) {
    printf("-"); n = -n;
  }
  char buf[40]; int i = 39; buf[i--] = '\0';
  while (n > 0) {
    buf[i--] = '0' + (int)(n % 10); n /= 10;
  }
  printf("%s\t", &buf[i + 1]);
}

static inline void _axo_print_uint128(unsigned _BitInt(128) n) {
  if (n == 0) {
    printf("0\t"); return;
  }
  char buf[40]; int i = 39; buf[i--] = '\0';
  while (n > 0) {
    buf[i--] = '0' + (int)(n % 10); n /= 10;
  }
  printf("%s\t", &buf[i + 1]);
}

static inline void _axo_print_int256(_BitInt(256) n) {
  if (n == 0) {
    printf("0\t"); return;
  }
  if (n < 0) {
    printf("-"); n = -n;
  }
  char buf[80]; int i = 79; buf[i--] = '\0';
  while (n > 0) {
    buf[i--] = '0' + (int)(n % 10); n /= 10;
  }
  printf("%s\t", &buf[i + 1]);
}

static inline void _axo_print_uint256(unsigned _BitInt(256) n) {
  if (n == 0) {
    printf("0\t"); return;
  }
  char buf[80]; int i = 79; buf[i--] = '\0';
  while (n > 0) {
    buf[i--] = '0' + (int)(n % 10); n /= 10;
  }
  printf("%s\t", &buf[i + 1]);
}

// --- MACRO SOBRECARGADO SEGURO ESTÁTICO DE C23 ---
#define axo_print_single(X) _Generic((X), \
bool:                      printf((X) ? "true\t" : "false\t"), \
int8_t:                    printf("%" PRId8 "\t", (int8_t)(X)), \
uint8_t:                   printf("%" PRIu8 "\t", (uint8_t)(X)), \
int16_t:                   printf("%" PRId16 "\t", (int16_t)(X)), \
uint16_t:                  printf("%" PRIu16 "\t", (uint16_t)(X)), \
int32_t:                   printf("%" PRId32 "\t", (int32_t)(X)), \
uint32_t:                  printf("%" PRIu32 "\t", (uint32_t)(X)), \
int64_t:                   printf("%" PRId64 "\t", (int64_t)(X)), \
uint64_t:                  printf("%" PRIu64 "\t", (uint64_t)(X)), \
_BitInt(128):              _axo_print_int128(X), \
unsigned _BitInt(128):     _axo_print_uint128(X), \
_BitInt(256):              _axo_print_int256(X), \
unsigned _BitInt(256):     _axo_print_uint256(X), \
_Float16:                  printf("%f\t", (float)(X)), \
float:                     printf("%f\t", (float)(X)), \
double:                    printf("%lf\t", (double)(X)), \
long double:               printf("%Lf\t", (long double)(X)), \
_Float256:                 printf("%Lf\t", (long double)(X)), \
char8_t:                   _axo_print_char8(X), \
char16_t:                  _axo_print_char16(X), \
char32_t:                  _axo_print_char32(X), \
char*:                     printf("%s\t", (char*)(X)), \
const char*:               printf("%s\t", (const char*)(X)), \
_Float16 complex: _axo_print_float16_complex(X), \
float complex:             _axo_print_float_complex(X), \
double complex:            _axo_print_double_complex(X), \
long double complex:       _axo_print_ldouble_complex(X), \
_Decimal32:                printf("%Hf\t", (_Decimal32)(X)), \
_Decimal64:                printf("%Df\t", (_Decimal64)(X)), \
_Decimal128:               printf("%DDf\t", (_Decimal128)(X)), \
default:                   printf("[Objeto/Bloque void*]\t") \
)
// === COPIAR Y PEGAR DENTRO DE HEADER_C EN TU TRANSPILADOR ===

// 1. FUNCIONES AUXILIARES SEGURAS DE ESCANEO (Soporte Unicode, Complejos y 256-bits)
static inline void _axo_scan_string_safe(char* dest, size_t max_len) {
  char formato[32];
  // Construye de forma segura el límite de caracteres (ej: "%127s")
  snprintf(formato, sizeof(formato), "%%%zds", max_len - 1);
  if (scanf(formato, dest) != 1) {
    // Manejo silencioso o asignación vacía si falla
    dest[0] = '\0';
  }
}

// Helpers para caracteres Unicode nativos por niveles
static inline void _axo_scan_char8(char8_t* ptr) {
  char c;
  if (scanf(" %c", &c) == 1) *ptr = (char8_t)c;
}

static inline void _axo_scan_char16(char16_t* ptr) {
  wchar_t wc;
  if (scanf(" %lc", &wc) == 1) *ptr = (char16_t)wc;
}

static inline void _axo_scan_char32(char32_t* ptr) {
  wchar_t wc;
  if (scanf(" %lc", &wc) == 1) *ptr = (char32_t)wc;
}

// Helper seguro para evitar el desbordamiento de Stack de _Float16
static inline void _axo_scan_float16(_Float16* ptr) {
  float temp;
  if (scanf("%f", &temp) == 1) *ptr = (_Float16)temp;
}

// Helpers para números complejos nativos
static inline void _axo_scan_xscom(_Float16 complex* ptr) {
  float r,
  i;
  if (scanf("%f %f", &r, &i) == 2) *ptr = (_Float16)r + (_Float16)i * I;
}

static inline void _axo_scan_scom(float complex* ptr) {
  float r,
  i;
  if (scanf("%f %f", &r, &i) == 2) *ptr = r + i * I;
}

static inline void _axo_scan_com(double complex* ptr) {
  double r,
  i;
  if (scanf("%lf %lf", &r, &i) == 2) *ptr = r + i * I;
}

static inline void _axo_scan_lcom(long double complex* ptr) {
  long double r,
  i;
  if (scanf("%Lf %Lf", &r, &i) == 2) *ptr = r + i * I;
}

// --- ALGORITMOS DE PARSEO PARA TIPOS MÁXIMOS DE 128 Y 256 BITS ---
static inline void _axo_scan_int128(_BitInt(128)* ptr) {
  char buf[45];
  if (scanf("%44s", buf) == 1) {
    _BitInt(128) res = 0;
    int i = 0,
    sign = 1;
    if (buf[0] == '-') {
      sign = -1; i++;
    }
    else if (buf[0] == '+') {
      i++;
    }
    while (buf[i] >= '0' && buf[i] <= '9') {
      res = res * 10 + (buf[i] - '0');
      i++;
    }
    *ptr = res * sign;
  }
}

static inline void _axo_scan_uint128(unsigned _BitInt(128)* ptr) {
  char buf[45];
  if (scanf("%44s", buf) == 1) {
    unsigned _BitInt(128) res = 0;
    int i = 0;
    if (buf[0] == '+') {
      i++;
    }
    while (buf[i] >= '0' && buf[i] <= '9') {
      res = res * 10 + (buf[i] - '0');
      i++;
    }
    *ptr = res;
  }
}

static inline void _axo_scan_int256(_BitInt(256)* ptr) {
  char buf[85];
  if (scanf("%84s", buf) == 1) {
    _BitInt(256) res = 0;
    int i = 0,
    sign = 1;
    if (buf[0] == '-') {
      sign = -1; i++;
    }
    else if (buf[0] == '+') {
      i++;
    }
    while (buf[i] >= '0' && buf[i] <= '9') {
      res = res * 10 + (buf[i] - '0');
      i++;
    }
    *ptr = res * sign;
  }
}

static inline void _axo_scan_uint256(unsigned _BitInt(256)* ptr) {
  char buf[85];
  if (scanf("%84s", buf) == 1) {
    unsigned _BitInt(256) res = 0;
    int i = 0;
    if (buf[0] == '+') {
      i++;
    }
    while (buf[i] >= '0' && buf[i] <= '9') {
      res = res * 10 + (buf[i] - '0');
      i++;
    }
    *ptr = res;
  }
}

static inline void _axo_scan_float256(_Float256* ptr) {
  long double temp;
  if (scanf("%Lf", &temp) == 1) *ptr = (_Float256)temp;
}


// 2. MACRO EVALUADORA DE PUNTEROS PARA SCAN (Totalmente Blindada en C23)
#define axo_scan_single(X) _Generic((X), \
bool*:                  _Generic((X), bool*: ({ int tmp; int r = scanf("%d", &tmp); if(r==1)*(X)=(bool)tmp; r; })), \
int8_t*:                scanf("%" SCNd8, (int8_t*)(X)), \
uint8_t*:               scanf("%" SCNu8, (uint8_t*)(X)), \
int16_t*:               scanf("%" SCNd16, (int16_t*)(X)), \
uint16_t*:              scanf("%" SCNu16, (uint16_t*)(X)), \
int32_t*:               scanf("%" SCNd32, (int32_t*)(X)), \
uint32_t*:              scanf("%" SCNu32, (uint32_t*)(X)), \
int64_t*:               scanf("%" SCNd64, (int64_t*)(X)), \
uint64_t*:              scanf("%" SCNu64, (uint64_t*)(X)), \
_BitInt(128)*:          _axo_scan_int128((_BitInt(128)*)(X)), \
unsigned _BitInt(128)*: _axo_scan_uint128((unsigned _BitInt(128)*)(X)), \
_BitInt(256)*:          _axo_scan_int256((_BitInt(256)*)(X)), \
unsigned _BitInt(256)*: _axo_scan_uint256((unsigned _BitInt(256)*)(X)), \
_Float16*:              _axo_scan_float16((_Float16*)(X)), \
float*:                 scanf("%f", (float*)(X)), \
double*:                scanf("%lf", (double*)(X)), \
long double*:           scanf("%Lf", (long double*)(X)), \
_Float256*:             _axo_scan_float256((_Float256*)(X)), \
char8_t*:               _axo_scan_char8((char8_t*)(X)), \
char16_t*:              _axo_scan_char16((char16_t*)(X)), \
char32_t*:              _axo_scan_char32((char32_t*)(X)), \
char*:                  _axo_scan_string_safe((char*)(X), 128), \
_Float16 complex*:      _axo_scan_xscom((_Float16 complex*)(X)), \
float complex*:         _axo_scan_scom((float complex*)(X)), \
double complex*:        _axo_scan_com((double complex*)(X)), \
long double complex*:   _axo_scan_lcom((long double complex*)(X)), \
_Decimal32*:            scanf("%Hf", (_Decimal32*)(X)), \
_Decimal64*:            scanf("%Df", (_Decimal64*)(X)), \
_Decimal128*:           scanf("%DDf", (_Decimal128*)(X)), \
default:                printf("[Error: Tipo de puntero no escaneable]\n") \
)
typedef struct {
  int64_t value;
  bool has_error;
  int32_t error_code;
} axo_result_t;

// === Nivel 1: xxsvar y xsvar (Uniones puras de 16 bits / 2 Bytes) ===
typedef union {
  int8_t axo_int;
  uint8_t axo_intu;
  char8_t axo_chara;
  bool axo_boo;
} xxsvar;

typedef union {
  int16_t axo_int;
  uint16_t axo_intu;
  _Float16 axo_flt;
  char16_t axo_chara;
  bool axo_boo;
} xsvar;

// === Nivel 2: svar (Unión pura de 32 bits / 4 Bytes) ===
typedef union {
  char32_t axo_chara;
  bool axo_boo;
  int32_t axo_int;
  uint32_t axo_intu;
  float axo_flt;
  _Float16 complex axo_com;
  _Decimal32 axo_dec;
} svar;

// === Nivel 3: var, lvar y xlvar (Contenedores dinámicos de 64 bits a más) ===
typedef union {
  char32_t axo_chara;
  bool axo_boo;
  int64_t axo_int;
  uint64_t axo_intu;
  double axo_flt;
  float complex axo_com;
  _Decimal64 axo_dec;
  void* axo_other;
} var;

typedef union {
  char32_t axo_chara;
  bool axo_boo;
  _BitInt(128) axo_int;
  unsigned _BitInt(128) axo_intu;
  _Float128 axo_flt;
  double complex axo_com;
  _Decimal128 axo_dec;
  void* axo_other;
} lvar;

typedef union {
  char32_t axo_chara;
  bool axo_boo;
  _BitInt(256) axo_int;
  unsigned _BitInt(256) axo_intu;
  _Float256 axo_flt;
  _Float128 complex axo_com;
  _Decimal128 axo_dec;
  void* axo_other;
} xlvar;
`;
class AxolangToCListener extends AxolangListener {
	constructor() {
		super();
		this.outputC = "";
		this.isComplexMatch = false;
		this.matchExpr = "";
		this.caseCount = 0;
		this.tablaSimbolos = new Map();
	}
	enterVarDeclaration(ctx) {
		const id = ctx.IDENTIFIER().getText();
		let type = ctx.getChild(0).getText();
		if (ctx.arrayLiteral()) {
			this.tablaSimbolos.set(id, "array");
			const items = ctx.arrayLiteral().expression();
			const elementsCount = ctx.INT_LITERAL()
				? ctx.INT_LITERAL().getText
				: items.length;
			let chkmrk = ["", "DD", "U", ""];
			let inititem = [];
			let preout = "";
			if (type.startsWith("xxs")) {
				chkmrk = ["", "", "", ""];
			} else if (type.startsWith("xs")) {
				chkmrk = ["f16", "", "u", ""];
			} else if (type.startsWith("s")) {
				chkmrk = ["f", "DF", "U", "f16i"];
			} else if (type.startsWith("l")) {
				chkmrk = ["f128", "DL", "U", "* I"];
			} else if (type.startsWith("xl")) {
				chkmrk = ["f256", "DL", "U", "f128i"];
			} else {
				chkmrk = ["", "DD", "U", "* I"];
			}
			for (let i = 0; i < elementsCount; i++) {
				let value = items[i].getText();
				if (value.includes(".")) {
					value += chkmrk[0];
					inititem.push(`{ .axo_flt = ${value} }`);
				} else if (value.includes("D") && !value.startsWith("\'")) {
					value = value.replace(/D$/, chkmrk[1]);
					inititem.push(`{ .axo_dec = ${value} }`);
				} else if (value.includes("i") && !value.startsWith("\'")) {
					value = value.replace(/i$/, chkmrk[3]);
					inititem.push(`{ .axo_com = ${value} }`);
				} else if (value.startsWith("\'")) {
					value = value.replace(/^/, chkmrk[2]);
					inititem.push(`{ .axo_chara = ${value} }`);
				} else if (
					(value.includes("true") || value.includes("false")) &&
					!value.startsWith("\'")
				) {
					inititem.push(`{ .axo_boo = ${value} }`);
				} else if (value.startsWith("{")) {
					let pkgvars = [];
					pkgvars.push(`{ .axo_other = (struct {`);
					const pkgbody = items[i].varDeclaration();
					for (let p = 0; p < pkgbody.length; p++) {
						let pkgvalue = pkgbody[p].getText();
						pkgvars.push(`${pkgvalue};`);
					}
					pkgvars.push(`}){} }`);
					inititem.push(`${pkgvars.join(" ")}`);
				} else if (value.startsWith("&")) {
					inititem.push(`{ .axo_other = ${value} }`);
				} else if (value.includes("u")) {
					inititem.push(`{ .axo_intu = ${value} }`);
				} else {
					inititem.push(`{ .axo_int = ${value} }`);
				}
			}
			inititem.push(`};`);
			this.outputC += `${type} ${id}[${elementsCount}] = { ${inititem.join(", ")}`;
		} else {
			switch (type) {
				case "xxsvar":
					break;

				default:
				// code
			}
		}
	}
	enterAssignmentStatement(ctx) {
		const id = ctx.IDENTIFIER().getText();
		let value = ctx.expression().getText();
		let nuevoTipo = "int"; // Por defecto

		// Detectamos dinámicamente qué tipo de dato le están metiendo a la unión
		if (value.includes(".")) {
			if (value.includes("D")) {
			}
		}

		// !!! EL SECRETO DEL DINAMISMO !!!
		// Actualizamos la tabla de símbolos en tiempo de compilación
		this.tablaSimbolos.set(id, nuevoTipo);

		// Escribimos en C la asignación apuntando al nuevo campo de la unión pura
		const campoC = this.obtenerCampoUnion(nuevoTipo);

		// Tratamiento de booleanos y complejos nativos de Axolang
		value = value
			.replace(/★$/, "true")
			.replace(/†$/, "false")
			.replace(/[iI]$/, " * I");

		this.outputC += `    ${id}.${campoC} = ${value};\n`;
	}
	exitMatchStatement(ctx) {
		if (!this.isComplexMatch) {
			this.outputC += `    }\n`;
		}
		this.isComplexMatch = false;
	}
}

function transpile(inputCode) {
	const chars = new antlr4.InputStream(inputCode);
	const lexer = new AxolangLexer(chars);
	const tokens = new antlr4.CommonTokenStream(lexer);
	const parser = new AxolangParser(tokens);
	const tree = parser.program();

	const listener = new AxolangToCListener();
	antlr4.tree.ParseTreeWalker.DEFAULT.walk(listener, tree);

	let finalCode = HEADER_C + "\nint main() {\n";
	finalCode += listener.outputC;
	finalCode += "    return 0;\n}";

	return finalCode;
}
const test = `
var hi[] = «5, 6 + 7i, 7.5, 5D, 'h', {
  var hola
  var algo
}»

`;
console.log(transpile(test));
