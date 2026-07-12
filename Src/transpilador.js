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

typedef union {
  int16_t axo_int;
  uint16_t axo_intu;
  _Float16 axo_dec;
  char16_t axo_chara;
  bool axo_boo;
} xsvar;

typedef union {
  char32_t axo_chara;
  bool axo_boo;
  int32_t axo_int;
  uint32_t axo_intu;
  _Float16 complex axo_com;
  _Decimal32 axo_dec;
} svar;

typedef union {
  char32_t axo_chara;
  bool axo_boo;
  int64_t axo_int;
  uint64_t axo_intu;
  float complex axo_com;
  _Decimal64 axo_dec;
  void* axo_other;
} var;

typedef union {
  char32_t axo_chara;
  bool axo_boo;
  _BitInt(128) axo_int;
  unsigned _BitInt(128) axo_intu;
  double complex axo_com;
  _Decimal128 axo_dec;
  void* axo_other;
} lvar;

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
    let chkmrk = ["DD", "U", "* I"];
    if (type.startsWith("xs")) {
      chkmrk = ["f16", "u", ""];
    } else if (type.startsWith("s")) {
      chkmrk = ["DF", "U", "* I"];
    } else if (type.startsWith("l")) {
      chkmrk = ["DL", "U", "* I"];
    } else {
      chkmrk = ["DD", "U", "* I"];
    }
if (type == "pkg"){
  let pkgvars = ctx.expression().pkg().varDeclaration()
  let pvdec = []
  for(let p = 0; p < pkgvars.length;p++){
    let pvid = pkgvars[p].IDENTIFIER().getText()
    let pvtp = pkgvars[p].getChild(0).getText()
    pvdec.push(`${pvtp} ${pvid};`)
  }
  this.outputC += `\ntypedef struct{ ${pvdec.join("\n")} }${id};`
}
    else if (ctx.arrayLiteral()) {
      const values = ctx.arrayLiteral().expression();
      const numval = values.length;
      let vars = [];

      for (let a = 0; a < numval; a++) {
        let thisval = values[a].getText();
        if (thisval.endsWith("u")) {
          thisval = thisval.replace(/u$/, "");
          vars.push(`{ .axo_intu = ${thisval} }`);
        } else if (thisval.endsWith("i")) {
          thisval = thisval.replace(/i$/, chkmrk[2]);

          vars.push(`{ .axo_com = ${thisval} }`);
        } else if (thisval.includes(".")) {
          thisval += chkmrk[0];
          vars.push(`{ .axo_dec= ${thisval} }`);
        } else if (
          (thisval.includes("true") || thisval.includes("false")) &&
          (!(thisval.includes('"') || thisval.includes("'")) ||
            values[a].IDENTIFIER())
        ) {
          vars.push(`{ .axo_boo = ${thisval} }`);
        } else if (thisval.startsWith("'")) {
          vars.push(`{ .axo_chara= ${chkmrk[1]}${thisval} }`);
        } else if (thisval.startsWith('"')) {
          vars.push(`{ .axo_other = ${chkmrk[1]}${thisval} }`);
        } else if (thisval.startsWith("&")) {
          vars.push(`{ .axo_other = ${thisval} }`);
        } else if (values[a].IDENTIFIER()) {
          vars.push(`{ .axo_other = ${thisval} }`);
        } else if (values[a].arrayLiteral()) {
          
          this.enterVarDeclaration(values[a]);
          vars.push(`{ .axo_other = ${thisval} }`);
        } else {
          vars.push(`{ .axo_int = ${thisval} }`);
        }
      }
      this.outputC += `\n${type} ${id}[${numval}] = { ${vars.join(",")} };`;
    } else {
      this.outputC += `\n${type} ${id};`;
      let thisvar = ctx.expression();
      let value = thisvar.getText();
      if (value.endsWith("u")) {
        value = value.replace(/u$/, "");
        this.outputC += `\n${id}.axo_intu = ${value};`;
      } else if (value.endsWith("i")) {
        value = value.replace(/i$/, chkmrk[2]);

        this.outputC += `\n${id}.axo_com = ${value};`;
      } else if (value.includes(".")) {
        value += chkmrk[0];
        this.outputC += `\n${id}.axo_dec = ${value};`;
      } else if (
        (value.includes("true") || value.includes("false")) &&
        (!(value.includes('"') || value.includes("'")) || thisvar.IDENTIFIER())
      ) {
        this.outputC += `\n${id}.axo_boo = ${value};`;
      } else if (value.startsWith("'")) {
        this.outputC += `\n${id}.axo_chara= ${chkmrk[1]}${value};`;
      } else if (value.startsWith('"')) {
        this.outputC += `\n${id}.axo_other = ${chkmrk[1]}${value}";`;
      } else if (value.startsWith("&")) {
        this.outputC += `\n${id}.axo_other = ${value};`;
      } else if (thisvar.IDENTIFIER()) {
        this.outputC += `\n${id} = ${value};`;
      }
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

  let finalCode = HEADER_C;
  finalCode += listener.outputC;
  return finalCode;
}
const test = `
var hi[] = «5, 6u, 5.5-6i, «7, 7.8»»
var go = "Hola"
var text = go
lvar hi2 = 7 - 8i
xsvar oh = 8.7
pkg hola = {
  var numero
}
`;
console.log(transpile(test));
