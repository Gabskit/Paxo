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

#define dec_complex(type) _dec_complex_##type

// Estructuras de arrays contiguos bajo el capó
typedef _Decimal32  _dec_complex__Decimal32[2];
typedef _Decimal64  _dec_complex__Decimal64[2];

typedef struct {
  int64_t value;
  bool has_error;
  int32_t error_code;
} paxo_result_t;

typedef union {
  int16_t paxo_int;
  uint16_t paxo_intu;
  _Float16 paxo_flt;
  char16_t paxo_chara;
  bool paxo_boo;
} xsvar;

typedef union {
  char32_t paxo_chara;
  bool paxo_boo;
  int32_t paxo_int;
  uint32_t paxo_intu;
  _Float16 complex paxo_com;
  _Float32 paxo_flt;
  _Decimal32 paxo_dec;
} svar;

typedef union {
  char32_t paxo_chara;
  bool paxo_boo;
  int64_t paxo_int;
  uint64_t paxo_intu;
  _Float64 paxo_flt;
  _Float32 complex paxo_com;
  dec_complex(_Decimal32) complex paxo_comdec;
  _Decimal64 paxo_dec;
  void* paxo_other;
} var;

typedef union {
  char32_t paxo_chara;
  bool paxo_boo;
  _BitInt(128) paxo_int;
  unsigned _BitInt(128) paxo_intu;
  _Float128 paxo_flt;
  _Float64 complex paxo_com;
  dec_complex(_Decimal64) complex paxo_comdec;
  _Decimal128 paxo_dec;
  void* paxo_other;
} lvar;

`;
class AxolangToCListener extends AxolangListener {
  constructor() {
    super();
    this.varAndFun = "";
    this.scriptLines = "";
    this.isComplexMatch = false;
    this.matchExpr = "";
    this.caseCount = 0;
    this.tablaSimbolos = new Map();}

  enterVarDeclaration(ctx) {
    const id = ctx.IDENTIFIER().getText();
    let type = ctx.getChild(0).getText();
    let cp = ctx.parentCtx;
    while (cp) {
      if (
        cp.constructor.name === "PkgContext" ||
        cp.constructor.name === "Pkg") {
        return;}
      cp = cp.parentCtx;}

    let chkmrk = ["DD", "U", "* I"];
    if (type.startsWith("xs")) {
      chkmrk = ["f16", "u", ""];
    } else if (type.startsWith("s")) {
      chkmrk = ["DF", "U", "* I"];
    } else if (type.startsWith("l")) {
      chkmrk = ["DL", "U", "* I"];
    } else {
      chkmrk = ["DD", "U", "* I"];}

    if (type == "pkg"){
  let pkgvars = ctx.expression().pkg().varDeclaration()
  let pvdec = []
  for(let p = 0; p < pkgvars.length;p++){
    let pvid = pkgvars[p].IDENTIFIER().getText()
    let pvtp = pkgvars[p].getChild(0).getText()
    pvdec.push(`${pvtp} ${pvid};`)
  }
      this.varAndFun += `\ntypedef struct{\n ${pvdec.join("\n")}}${id};`}
      else if (ctx.arrayLiteral()) {
      const values = ctx.arrayLiteral().expression();
      const numval = values.length;
      let vars = [];
      for (let a = 0; a < numval; a++) {
        let thisval = values[a].getText();
        if (thisval.endsWith("u") && ((!thisval.startsWith("'") || !thisval.startsWith('"')) || !values[a].IDENTIFIER())) {
          thisval = thisval.replace(/u$/, "");
          vars.push(`{ .axo_intu = ${thisval} }`);
        } else if (thisval.endsWith("i") && ((!thisval.startsWith("'") || !thisval.startsWith('"')) || !values[a].IDENTIFIER())) {
          thisval = thisval.replace(/i$/, chkmrk[2]);
          vars.push(`{ .axo_com = ${thisval} }`);
        } else if (thisval.includes(".") && ((!thisval.startsWith("'") || !thisval.startsWith('"')) || !values[a].IDENTIFIER())) {
          thisval += chkmrk[0];
          vars.push(`{ .axo_dec= ${thisval} }`);
        } else if (
          (thisval.includes("true") || thisval.includes("false")) &&
          (!(thisval.includes('"') || thisval.includes("'")) ||
            values[a].IDENTIFIER())) {
          vars.push(`{ .axo_boo = ${thisval} }`);
        } else if (thisval.startsWith("'")) {
          vars.push(`{ .axo_chara= ${chkmrk[1]}${thisval} }`);
        } else if (thisval.startsWith('"')) {
          vars.push(`{ .axo_other = ${chkmrk[1]}${thisval} }`);
        } else if (thisval.startsWith("&") && ((!thisval.startsWith("'") || !thisval.startsWith('"')) || !values[a].IDENTIFIER())) {
          vars.push(`{ .axo_other = ${thisval} }`);
        } else if (values[a].IDENTIFIER()) {
          vars.push(`{ .axo_other = ${thisval} }`);
        } /*else if (values[a].arrayLiteral()) {
          al(values[a]);
        //  vars.push(`{ .axo_other = ${thisval} }`);
        }*/ else {
          vars.push(`{ .axo_int = ${thisval} }`);}}
      this.varAndFun += `\n${type} ${id}[${numval}] = { ${vars.join(",")} };`;
    } else {
      this.varAndFun += `\n${type} ${id};`;
      let thisvar = ctx.expression();
      let value = thisvar.getText();
      if (value.endsWith("u") && ((!value.startsWith("'") || !value.startsWith('"')) || !thisvar.IDENTIFIER())) {
        value = value.replace(/u$/, "");
        this.varAndFun += `\n${id}.axo_intu = ${value};`;
      } else if (value.endsWith("i") && ((!value.startsWith("'") || !value.startsWith('"')) || !thisvar.IDENTIFIER())) {
        value = value.replace(/i$/, chkmrk[2]);
        this.varAndFun += `\n${id}.axo_com = ${value};`;
      } else if (value.includes(".") && ((!value.startsWith("'") || !value.startsWith('"')) || !thisvar.IDENTIFIER())) {
        value += chkmrk[0];
        this.varAndFun += `\n${id}.axo_dec = ${value};`;
      } else if (
        (value.includes("true") || value.includes("false")) &&
        (!(value.includes('"') || value.includes("'")) || thisvar.IDENTIFIER())) {
        this.varAndFun += `\n${id}.axo_boo = ${value};`;
      } else if (value.startsWith("'")) {
        this.varAndFun += `\n${id}.axo_chara= ${chkmrk[1]}${value};`;
      } else if (value.startsWith('"')) {
        this.varAndFun += `\n${id}.axo_other = ${chkmrk[1]}${value}";`;
      } else if (value.startsWith("&") && ((!value.startsWith("'") || !value.startsWith('"')) || !thisvar.IDENTIFIER())) {
        this.varAndFun += `\n${id}.axo_other = ${value};`;
      } else if (thisvar.IDENTIFIER()) {
        this.varAndFun += `\n${id} = ${value};`;}}}

  exitMatchStatement(ctx) {
    if (!this.isComplexMatch) {
      this.varAndFun += `    }\n`;}
    this.isComplexMatch = false;}}

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
  finalCode += listener.varAndFun;
  finalCode += `\nint main(int argc, char* argv[]){`
  finalCode += listener.scriptLines;
  finalCode += `}`
  return finalCode;}

const test = `
var hi[] = «5, 'i', 5.5-6i, "hi"»
var go = "Hola"
var text = go
lvar hi2 = 7 - 8i
xsvar oh = 'i'
pkg hola = {
  var numero
  xsvar id}
`;

console.log(transpile(test));
