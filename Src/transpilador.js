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
		let cp = ctx.parentCtx;
		while (cp) {
			if (
				cp.constructor.name === "PkgContext" ||
				cp.constructor.name === "Pkg"
			) {
				return;
			}
			cp = cp.parentCtx;
		}
		const id = ctx.IDENTIFIER().getText();
		let type = ctx.getChild(0).getText();

		}
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
	//console.log(tree);

	const listener = new AxolangToCListener();
	antlr4.tree.ParseTreeWalker.DEFAULT.walk(listener, tree);

	let finalCode = HEADER_C + "\nint main() {\n";
	finalCode += listener.outputC;
	finalCode += "    return 0;\n}";
	return finalCode;
}
const test = `
var hi[] = «5, 6u, «7.5, {
  var uno = 6
  var dod = 9i
}»»
var go = {
  var algo = "Hola desde pkg"
}
var text = go
`;
console.log(transpile(test));
