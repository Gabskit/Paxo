// Src/Bcgen/abytec.js
import fs from "fs/promises";
import antlr4 from "antlr4";
import PaxoLexer from "./PaxoLexer.js";
import PaxoParser from "./PaxoParser.js";

function getTextSafe(x) {
  if (x == null) return "";

  if (typeof x === "string") {
    return x;
  }

  if (typeof x.getText === "function") {
    return x.getText();
  }

  if (typeof x.text === "string") {
    return x.text;
  }

  if (typeof x.symbol?.text === "string") {
    return x.symbol.text;
  }

  if (typeof x.symbol?.textContent === "string") {
    return x.symbol.textContent;
  }

  return String(x);
}

function tokenTextSafe(ctx) {
  return getTextSafe(ctx);
}


/*
 * ============================================================
 * Paxo -> LEP Bytecode Compiler
 * ============================================================
 *
 * Compatible con ANTLR NG / antlr4ng.
 *
 * Los opcodes y formatos de operandos se corresponden con Vm.c.
 * ============================================================
 */

const OP = Object.freeze({
  WRITE: 0,
  READ: 1,
  EXPAND: 2,
  COLLAPSE: 3,

  ADD: 4,
  SUB: 5,
  MUL: 6,
  DIV: 7,
  CAST: 8,

  LOAD_VAR: 9,
  STORE_VAR: 10,
  PRINT: 11,

  JUMP: 12,
  JUMP_IF_FALSE: 13,
  JUMP_IF_TRUE: 14,
  HALT: 15,

  CALL: 16,
  CALL_NATIVE: 17,

  EQ: 18,
  NEQ: 19,
  LT: 20,
  GT: 21,
  LTE: 22,
  GTE: 23,

  AND: 24,
  OR: 25,
  NOT: 26,

  BIT_AND: 27,
  BIT_OR: 28,
  BIT_NOT: 29,
  BIT_XOR: 30,
  BIT_SHL: 31,
  BIT_SHR: 32,

  INC: 33,
  DEC: 34,

  RETURN: 35,
  CALL_VAR: 36,

  ARRAY_NEW: 37,
  ARRAY_GET: 38,
  ARRAY_SET: 39,

  PKG_NEW: 40,
  PKG_GET: 41,
  PKG_SET: 42,

  TRY_SETUP: 43,
  TRY_END: 44,
  THROW: 45,

  STORE_LOCAL: 46,
  LOAD_LOCAL: 47,

  CALL_METHOD: 48,

  THIS_GET: 49,
  THIS_SET: 50,
});


/*
 * Tipos usados por OP_WRITE.
 *
 * Estos valores deben coincidir con el enum de Vm.c.
 */
const TYPE = Object.freeze({
  NUM: 0,
  CHAR: 1,
  TRIT: 2,
  BOOL: 3,
  POINT: 4,
  FUNC: 5,
  STRING: 6,
  ARRAY: 7,
  PACKAGE: 8,
  COLOR: 9,
  COMPLEX: 10,
});


/*
 * IDs de natives.
 *
 * IMPORTANTE:
 * Estos IDs deben mantenerse sincronizados con Functions.c.
 */
const NATIVE = Object.freeze({
  print: 0,
  println: 1,
  typeof: 2,

  setColorText: 3,
  setTextColor: 3,

  setTypeText: 4,

  setColorBack: 5,
  resetColor: 6,

  scan: 7,

  arrayLen: 8,
  arrayPush: 9,

  initWindow: 10,
  clearScreen: 11,
  drawRect: 12,

  fileRead: 13,
  fileWrite: 14,
  fileAppend: 15,
  fileExists: 16,
  fileDelete: 17,

  imgLoad: 18,
  imgInfo: 19,
  imgSavePng: 20,
  imgSaveJpg: 21,
  imgSaveBmp: 22,
  imgResize: 23,

  fontLoad: 24,
  fontGlyph: 25,
  fontMetrics: 26,
  fontFree: 27,

  audioInit: 28,
  audioQuit: 29,
  audioPlay: 30,
  audioPause: 31,
  audioResume: 32,
  audioStop: 33,
  audioVolume: 34,
  audioPlaying: 35,

  physSpace: 36,
  physGravity: 37,
  physStep: 38,
  physBody: 39,
  physBodyStatic: 40,
  physPos: 41,
  physVel: 42,
  physSetPos: 43,
  physSetVel: 44,
  physAngle: 45,
  physSetAngle: 46,
  physForce: 47,
  physImpulse: 48,
  physCircle: 49,
  physBox: 50,
  physSegment: 51,
  physElasticity: 52,
  physFriction: 53,
  physCollide: 54,
  physFreeShape: 55,
  physFreeBody: 56,
  physFreeSpace: 57,

  winOpen: 58,
  winClose: 59,
  winColor: 60,
  winClear: 61,
  winRect: 62,
  winLine: 63,
  winCircle: 64,
  winText: 65,

  texLoad: 66,
  texDraw: 67,
  texFree: 68,

  winShow: 69,
  winPoll: 70,
  winKey: 71,
  winMouse: 72,
  winMousedown: 73,
  winTime: 74,
  winDelay: 75,

  sokolInit: 76,
  sokolShutdown: 77,
  sokolClear: 78,
  sokolColor: 79,
  sokolShow: 80,
  sokolPoll: 81,
  sokolKey: 82,
  sokolMouse: 83,
  sokolMousedown: 84,
  sokolTime: 85,
  sokolDelay: 86,

  nvgCreate: 87,
  nvgCancelFrame: 88,
  nvgBeginFrame: 89,
  nvgEndFrame: 90,
  nvgRect: 91,
  nvgLine: 92,
  nvgCircle: 93,
  nvgText: 94,
  nvgFillColor: 95,
  nvgStrokeColor: 96,
  nvgStrokeWidth: 97,
  nvgFill: 98,
  nvgStroke: 99,

  // Extensible FFI: ffiCall("module_function", ...args)
  ffiCall: 100,
  ffiLoad: 101,
});


const TYPE_NAME = {
	"📥": TYPE.NUM,
  var: TYPE.NUM,
  n: TYPE.NUM,
  abc: TYPE.CHAR,
  pin: TYPE.POINT,
  trit: TYPE.TRIT,
  bool: TYPE.BOOL,
  fx: TYPE.FUNC,
  pkg: TYPE.PACKAGE,
  "📦": TYPE.PACKAGE,
  col: TYPE.COLOR,
  ni: TYPE.COMPLEX,
};


/*
 * ============================================================
 * Helpers
 * ============================================================
 */

function text(ctx) {
  if (!ctx) return "";
  if (typeof ctx.getText === "function") return ctx.getText();
  if (ctx.text !== undefined) return ctx.text;
  return "";
}

function tokenText(ctx) {
  return ctx?.symbol?.text ?? text(ctx);
}



function u16(n) {
  const b = Buffer.alloc(2);
  b.writeUInt16LE(n >>> 0, 0);
  return [...b];
}


function i16(n) {
  const b = Buffer.alloc(2);
  b.writeInt16LE(n, 0);
  return [...b];
}


function u32(n) {
  const b = Buffer.alloc(4);
  b.writeUInt32LE(n >>> 0, 0);
  return [...b];
}


function u64(n) {
  const b = Buffer.alloc(8);

  b.writeBigUInt64LE(
    BigInt.asUintN(64, BigInt(n)),
    0
  );

  return [...b];
}


function utf8(s) {
  return [...Buffer.from(s, "utf8")];
}


/*
 * Convierte un número Paxo a la representación utilizada
 * por la VM.
 */
function numberParts(raw, maxDigits = 16) {
  let s = raw.trim();

  let sign = 0;

  if (s[0] === "+" || s[0] === "-") {
    sign = s[0] === "-" ? 1 : 0;
    s = s.slice(1);
  }

  const parts = s.split(".");

  const integerPart = parts[0] || "0";
  const fractionPart = parts[1] || "";

  let digits = integerPart + fractionPart;

  digits = digits.replace(/^0+(?=\d)/, "");

  if (!digits) {
    digits = "0";
  }

  let frac = fractionPart.length;

  while (
    digits.length > 1 &&
    digits.endsWith("0")
  ) {
    digits = digits.slice(0, -1);
    frac--;
  }

  if (digits.length > maxDigits) {
    throw new Error(
      `Literal numerico fuera de rango: ${raw}`
    );
  }

  let mant = BigInt(digits);

  let exp = 15 - frac;

  while (
    mant > 0n &&
    mant % 10n === 0n &&
    exp < 31
  ) {
    mant /= 10n;
    exp++;
  }

  if (exp < 0 || exp > 31) {
    throw new Error(
      `Exponente fuera de rango: ${raw}`
    );
  }

  return {
    sign,
    exp,
    mant,
  };
}


function complexParts(raw) {
  let s = raw.trim();

  if (!s.endsWith("i")) {
    throw new Error(
      `Complejo invalido: ${raw}`
    );
  }

  s = s.slice(0, -1);

  let split = -1;

  for (let i = 1; i < s.length; i++) {
    if (
      (s[i] === "+" || s[i] === "-") &&
      s[i - 1] !== "e"
    ) {
      split = i;
      break;
    }
  }

  if (split < 0) {
    throw new Error(
      `Complejo invalido: ${raw}`
    );
  }

  const re = s.slice(0, split) || "0";
  const im = s.slice(split);

  const r = numberParts(re, 7);
  const m = numberParts(im, 7);

  if (
    r.exp > 31 ||
    m.exp > 31 ||
    r.mant > 0xffffffn ||
    m.mant > 0xffffffn
  ) {
    throw new Error(
      `Complejo fuera de rango: ${raw}`
    );
  }

  return {
    r,
    m,
  };
}


/*
 * ============================================================
 * Bytecode emitter
 * ============================================================
 */

class Emitter {
  constructor() {
    this.bytes = [];
  }

  get ip() {
    return this.bytes.length;
  }

  emit(...xs) {
    this.bytes.push(
      ...xs.map(x => x & 0xff)
    );

    return this.ip - xs.length;
  }

  op(opcode) {
    this.emit(opcode);
  }

  reg(n) {
    this.emit(...u16(n));
  }

  patchI16(pos, target, baseAfter) {
    const offset = target - baseAfter;

    if (
      offset < -32768 ||
      offset > 32767
    ) {
      throw new Error(
        "Salto demasiado grande para i16"
      );
    }

    const b = i16(offset);

    this.bytes[pos] = b[0];
    this.bytes[pos + 1] = b[1];
  }

  jump(opcode) {
    this.op(opcode);

    const p = this.ip;

    this.emit(0, 0);

    return {
      p,
      base: () => this.ip,
    };
  }
  
  condJump(opcode, conditionReg) {
  this.op(opcode);
  this.reg(conditionReg);

  const p = this.ip;
  this.emit(0, 0);

  return {
    p,
    base: () => this.ip,
  };
}

  patchJump(jump, target) {
    this.patchI16(
      jump.p,
      target,
      jump.p + 2
    );
  }

  toBuffer() {
    return Buffer.from(this.bytes);
  }
}


/*
 * ============================================================
 * Compiler
 * ============================================================
 */

class Compiler {
  constructor(source, file = "<input>") {
    this.source = source;
    this.file = file;

    this.e = new Emitter();

    this.globals = new Map();

    this.nextReg = 0;

    this.functions = [];

    this.currentFunction = null;

    this.errors = [];

    this.nativeNames =
      new Set(Object.keys(NATIVE));
  }


  error(ctx, message) {
    const line =
      ctx?.start?.line ?? "?";

    this.errors.push(
      `${this.file}:${line}: ${message}`
    );
  }


  reg() {
    if (this.nextReg > 65534) {
      throw new Error(
        "Demasiados registros temporales"
      );
    }

    return this.nextReg++;
  }


  resetTemps(n = 0) {
    this.nextReg = n;
  }


  addGlobal(name) {
    if (this.globals.has(name)) {
      return this.globals.get(name);
    }

    const index = this.globals.size;

    if (index > 65535) {
      throw new Error(
        "Demasiadas variables globales"
      );
    }

    this.globals.set(name, index);

    return index;
  }


  lookup(name) {
    if (
      this.currentFunction?.locals.has(name)
    ) {
      return {
        kind: "local",
        index:
          this.currentFunction.locals.get(name),
      };
    }

    if (this.globals.has(name)) {
      return {
        kind: "global",
        index: this.globals.get(name),
      };
    }

    return null;
  }


  /*
   * ----------------------------------------------------------
   * Literales
   * ----------------------------------------------------------
   */

  emitWriteNumber(reg, raw) {
    const p = numberParts(raw);

    this.e.op(OP.WRITE);

    this.e.emit(TYPE.NUM);

    this.e.reg(reg);

    const payload =
      (BigInt(p.sign) << 59n) |
      (BigInt(p.exp) << 54n) |
      p.mant;

    this.e.emit(...u64(payload));
  }


  emitWriteString(reg, value) {
    const bytes = utf8(value);

    if (bytes.length > 65535) {
      throw new Error(
        "String demasiado larga"
      );
    }

    this.e.op(OP.WRITE);

    this.e.emit(TYPE.STRING);

    this.e.reg(reg);

    this.e.emit(
      ...u16(bytes.length),
      ...bytes
    );
  }


  emitWriteChar(reg, value) {
    const codePoint =
      [...value][0]?.codePointAt(0) ?? 0;

    this.e.op(OP.WRITE);

    this.e.emit(TYPE.CHAR);

    this.e.reg(reg);

    this.e.emit(
      ...u32(codePoint)
    );
  }


  emitWriteBool(reg, value) {
    this.e.op(OP.WRITE);

    this.e.emit(TYPE.BOOL);

    this.e.reg(reg);

    this.e.emit(
      value ? 1 : 0
    );
  }


  emitWriteTrit(reg, value) {
    this.e.op(OP.WRITE);

    this.e.emit(TYPE.TRIT);

    this.e.reg(reg);

    this.e.emit(value & 3);
  }


  emitWriteColor(reg, raw) {
    const value =
      parseInt(raw.slice(1), 16) >>> 0;

    this.e.op(OP.WRITE);

    this.e.emit(TYPE.COLOR);

    this.e.reg(reg);

    this.e.emit(
      ...u32(value)
    );
  }


  emitWriteComplex(reg, raw) {
    const {
      r: re,
      m: im,
    } = complexParts(raw);

    const payload =
      (BigInt(re.sign) << 59n) |
      (BigInt(re.exp) << 57n) |
      (re.mant << 30n) |
      (BigInt(im.sign) << 29n) |
      (BigInt(im.exp) << 27n) |
      im.mant;

    this.e.op(OP.WRITE);

    this.e.emit(TYPE.COMPLEX);

    this.e.reg(reg);

    this.e.emit(
      ...u64(payload)
    );
  }


  /*
   * ----------------------------------------------------------
   * Identificadores
   * ----------------------------------------------------------
   */

  loadIdentifier(name, ctx) {
    const symbol = this.lookup(name);

    if (!symbol) {
      throw new Error(
        `Variable no declarada: ${name}`
      );
    }

    const dest = this.reg();

    if (symbol.kind === "global") {
      this.e.op(OP.LOAD_VAR);

      this.e.reg(symbol.index);

      this.e.reg(dest);
    } else {
      this.e.op(OP.LOAD_LOCAL);

      this.e.reg(symbol.index);

      this.e.reg(dest);
    }

    return dest;
  }


  /*
   * ----------------------------------------------------------
   * Expressions
   * ----------------------------------------------------------
   */

  compileExpression(ctx) {
    if (!ctx) {
      const r = this.reg();

      this.emitWriteNumber(r, "0");

      return r;
    }

    const name =
      ctx.constructor?.name || "";
      
      const s = text(ctx);

/*console.error(
  "DEBUG EXPR:",
  JSON.stringify(name),
  "TEXT:",
  JSON.stringify(s)
);*/

    /*
     * INT
     */
    if (name.includes("IntLitExpr")) {
      const r = this.reg();

      this.emitWriteNumber(r, s);

      return r;
    }


    /*
     * DECIMAL
     */
    if (name.includes("DecLitExpr")) {
      const r = this.reg();

      this.emitWriteNumber(r, s);

      return r;
    }


    /*
     * CHAR
     */
    if (name.includes("CharLitExpr")) {
      const r = this.reg();

      const value =
        s.slice(1, -1);

      this.emitWriteChar(r, value);

      return r;
    }


    /*
     * STRING
     */
    if (name.includes("StringLitExpr")) {
      const r = this.reg();

      let value =
        s.slice(1, -1);

      value = value
        .replace(/\\n/g, "\n")
        .replace(/\\r/g, "\r")
        .replace(/\\t/g, "\t")
        .replace(/\\"/g, '"')
        .replace(/\\\\/g, "\\");

      this.emitWriteString(
        r,
        value
      );

      return r;
    }


    /*
     * BOOLEAN BIT
     */
    if (name.includes("BoolBitExpr")) {
      const r = this.reg();

      this.emitWriteBool(
        r,
        s === ".✓"
      );

      return r;
    }


    /*
     * TRIT
     */
    if (name.includes("BoolTritExpr")) {
      const r = this.reg();

      let value = 0;

      if (s === "✓") {
        value = 1;
      } else if (s === "•") {
        value = 2;
      }

      this.emitWriteTrit(
        r,
        value
      );

      return r;
    }


    /*
     * COLOR
     */
    if (name.includes("ColLitExpr")) {
      const r = this.reg();

      this.emitWriteColor(
        r,
        s
      );

      return r;
    }


    /*
     * COMPLEX
     */
    if (name.includes("ComLitExpr")) {
      const r = this.reg();

      this.emitWriteComplex(
        r,
        s
      );

      return r;
    }


    /*
     * POINTER
     *
     * Vm.c no tiene un opcode específico
     * para construir un pointer literal.
     */
    if (name.includes("PtrLitExpr")) {
      throw new Error(
        `Los pointer literals (${s}) ` +
        `no tienen opcode de construccion en Vm.c`
      );
    }


    /*
     * IDENTIFIER
     */
    if (name.includes("IdentExpr")) {
      return this.loadIdentifier(
        s,
        ctx
      );
    }


    /*
     * this.field
     */
    if (name.includes("ThisScopeExpr")) {
      const r = this.reg();

      const id =
        s.split(".")
          .slice(1)
          .join(".");

      const nameBytes =
        utf8(id);

      this.e.op(OP.THIS_GET);

      this.e.emit(
        ...u16(nameBytes.length),
        ...nameBytes
      );

      this.e.reg(r);

      return r;
    }


    /*
     * FUNCTION EXPRESSION
     */
    if (name.includes("FuncExpr")) {
      return this.compileFunctionExpr(
        ctx.functionDeclaration()
      );
    }


    /*
     * PACKAGE
     */
    if (name.includes("PkgExpr")) {
      return this.compilePackage(
        ctx.pkgDeclaration()
      );
    }


    /*
     * ARRAY
     */
    if (name.includes("ArrayLitExpr")) {
      return this.compileArray(
        ctx.arrayLiteral()
      );
    }


    /*
     * ARRAY ACCESS
     */
    if (name.includes("IndexedAccessExpr")) {
      const expressions =
        ctx.expression();

      const array =
        this.compileExpression(
          expressions[0]
        );

      const index =
        this.compileExpression(
          expressions[1]
        );

      const dest = this.reg();

      this.e.op(OP.ARRAY_GET);

      this.e.reg(array);
      this.e.reg(index);
      this.e.reg(dest);

      return dest;
    }


    /*
     * INDEXED CALL
     */
    if (name.includes("IndexedCallExpr")) {
      const expressions =
        ctx.expression();

      const base =
        this.compileExpression(
          expressions[0]
        );

      const index =
        this.compileExpression(
          expressions[1]
        );

      const args =
        this.compileArgs(
          ctx.argumentList()
        );

      const dest = this.reg();

      this.emitIndexedCall(
        base,
        index,
        args,
        dest
      );

      return dest;
    }


    /*
     * METHOD CALL
     */
    if (name.includes("MethodCallExpr")) {
      return this.compileMethodCall(ctx);
    }


    /*
     * PACKAGE FIELD ACCESS
     */
    if (name.includes("DotAccessExpr")) {
      const expressions =
        ctx.expression();

      const base =
        this.compileExpression(
          expressions[0]
        );

      const id =
        getTextSafe(ctx.IDENTIFIER());

      const dest = this.reg();

      const bytes =
        utf8(id);

      this.e.op(OP.PKG_GET);

      this.e.emit(
        ...u16(bytes.length),
        ...bytes
      );

      this.e.reg(base);
      this.e.reg(dest);

      return dest;
    }
    
    /* 
 * PARENTHESES
 */
if (name.includes("ParenExpr")) {
  return this.compileExpression(ctx.expression());
}



    /*
     * CALL
     */
    if (name.includes("CallExpr")) {
      return this.compileCall(ctx);
    }


    /*
     * BINARY OPERATORS
     */
    if (
      name.includes("MultDivExpr") ||
      name.includes("AddSubExpr") ||
      name.includes("ShiftExpr") ||
      name.includes("RelationalExpr") ||
      name.includes("BitwiseExpr")
    ) {
      return this.compileBinary(
        ctx,
        name
      );
    }


    /*
     * LOGICAL NOT
     */
if (
  name.includes("NotExpr") ||
  name.includes("UnaryNotExpr") ||
  name.includes("NotgateExpr")
) {
  //console.error(">>> ENTRÓ A NOT:", name);

  const expressions = ctx.expression();

  /*console.error(
    ">>> OPERAND:",
    Array.isArray(expressions)
      ? expressions.map(x => x.constructor?.name)
      : expressions?.constructor?.name
  );*/

  const operand = this.compileExpression(
    Array.isArray(expressions)
      ? expressions[0]
      : expressions
  );

  const dest = this.reg();

  this.e.op(OP.NOT);
  this.e.reg(operand);
  this.e.reg(dest);

  return dest;
}
  }


  /*
   * ----------------------------------------------------------
   * Arguments
   * ----------------------------------------------------------
   */

  compileArgs(ctx) {
    if (!ctx) {
      return [];
    }

    const expressions =
      ctx.expression?.();

    if (Array.isArray(expressions)) {
      return expressions.map(
        e => this.compileExpression(e)
      );
    }

    if (expressions) {
      return [
        this.compileExpression(
          expressions
        ),
      ];
    }

    return [];
  }


  /*
   * Hace que los registros de argumentos sean contiguos.
   */
   
  packArgs(args) {
  if (args.length === 0) {
    return 0;
  }

  const base = Math.min(...args);
  let contiguous = true;

  for (let i = 0; i < args.length; i++) {
    if (args[i] !== base + i) {
      contiguous = false;
      break;
    }
  }

  if (contiguous) {
    return base;
  }

  const baseReg = this.nextReg;

  for (let i = 0; i < args.length; i++) {
    const targetReg = this.reg(); // Avanza nextReg por cada argumento
    this.e.op(OP.READ);
    this.e.reg(args[i]);
    this.e.reg(targetReg);
  }

  return baseReg;
}

  /*
   * ----------------------------------------------------------
   * Calls
   * ----------------------------------------------------------
   */

  compileCall(ctx) {
  const name = getTextSafe(ctx.IDENTIFIER());
  const args = this.compileArgs(ctx.argumentList());

  /*
   * Native
   */
  if (Object.prototype.hasOwnProperty.call(NATIVE, name)) {
    const base = this.packArgs(args); // Empaquetar argumentos PRIMERO
    const dest = this.reg();          // Reservar dest DESPUÉS

    this.e.op(OP.CALL_NATIVE);
    this.e.emit(...u16(NATIVE[name]));
    this.e.emit(args.length);
    this.e.reg(base);
    this.e.reg(dest);

    return dest;
  }

  /*
   * Paxo function
   */
  const functionReg = this.loadIdentifier(name, ctx);
  const base = this.packArgs(args);

  this.e.op(OP.CALL);
  this.e.reg(functionReg);
  this.e.emit(args.length);
  this.e.reg(base);

  const dest = this.reg();
  this.e.op(OP.READ);
  this.e.reg(65535);
  this.e.reg(dest);

  return dest;
}

  /*
   * ----------------------------------------------------------
   * Binary operators
   * ----------------------------------------------------------
   */

  compileBinary(ctx, name) {
    const expressions =
      ctx.expression();

    const left =
      this.compileExpression(
        expressions[0]
      );

    const right =
      this.compileExpression(
        expressions[1]
      );

    const dest = this.reg();

    let operator =
      null;

    const full =
      text(ctx);

    const leftText =
      text(expressions[0]);

    const rightText =
      text(expressions[1]);

    let opText =
      full.slice(
        leftText.length,
        full.length - rightText.length
      ).trim();


    if (
      name.includes("MultDivExpr")
    ) {
      operator =
        opText === "÷"
          ? OP.DIV
          : OP.MUL;
    }

    else if (
      name.includes("AddSubExpr")
    ) {
      operator =
        opText === "-"
          ? OP.SUB
          : OP.ADD;
    }

    else if (
      name.includes("ShiftExpr")
    ) {
      operator =
        opText === "»•"
          ? OP.BIT_SHR
          : OP.BIT_SHL;
    }

    else if (
      name.includes("RelationalExpr")
    ) {
      const relational = {
        "<": OP.LT,
        ">": OP.GT,
        "≤": OP.LTE,
        "<=": OP.LTE,
        "≥": OP.GTE,
        ">=": OP.GTE,
        "==": OP.EQ,
        "!=": OP.NEQ,
        "≠": OP.NEQ,
      };

      operator =
        relational[opText];
    }

    else {
      const bitwise = {
        "&": OP.BIT_AND,
        "|": OP.BIT_OR,
        ".&": OP.BIT_AND,
        ".|": OP.BIT_OR,
        "^": OP.BIT_XOR,
      };

      operator =
        bitwise[opText];
    }


    if (operator == null) {
      throw new Error(
        `Operador no soportado: ${opText}`
      );
    }


    this.e.op(operator);

    this.e.reg(left);
    this.e.reg(right);
    this.e.reg(dest);

    return dest;
  }


  /*
   * ----------------------------------------------------------
   * Arrays
   * ----------------------------------------------------------
   */

  compileArray(ctx) {
    const expressions =
      ctx.expression();

    const regs =
      Array.isArray(expressions)
        ? expressions.map(
            e => this.compileExpression(e)
          )
        : [];

    const dest = this.reg();

    const base =
      this.packArgs(regs);

    this.e.op(OP.ARRAY_NEW);

    this.e.emit(
      ...u16(regs.length)
    );

    this.e.reg(base);
    this.e.reg(dest);

    return dest;
  }


  /*
   * ----------------------------------------------------------
   * Packages
   * ----------------------------------------------------------
   */

  compilePackage(ctx) {
    const vars =
      ctx.varDeclaration?.() || [];

    const regs = [];

    for (const variable of vars) {
      const id =
        variable.IDENTIFIER().getText();

      let value;

      if (variable.expression()) {
        value =
          this.compileExpression(
            variable.expression()
          );
      }

      else if (variable.arrayLiteral()) {
        value =
          this.compileArray(
            variable.arrayLiteral()
          );
      }

      else {
        value = this.reg();

        this.emitWriteNumber(
          value,
          "0"
        );
      }

      const key = this.reg();

      this.emitWriteString(
        key,
        id
      );

      regs.push(
        key,
        value
      );
    }

    const dest = this.reg();

    const base =
      this.packArgs(regs);

    this.e.op(OP.PKG_NEW);

    this.e.emit(
      ...u16(vars.length)
    );

    this.e.reg(base);

    this.e.reg(dest);

    return dest;
  }


  /*
   * ----------------------------------------------------------
   * Method call
   * ----------------------------------------------------------
   */

  compileMethodCall(ctx) {
    const expressions =
      ctx.expression();

    const receiver =
      this.compileExpression(
        expressions[0]
      );

    const name =
      getTextSafe(ctx.IDENTIFIER());

    const functionReg =
      this.compilePackageMethodRef(
        receiver,
        name
      );

    const args =
      this.compileArgs(
        ctx.argumentList()
      );

    const base =
      this.packArgs(args);

    const dest = this.reg();


    this.e.op(OP.CALL_METHOD);

    this.e.reg(functionReg);

    this.e.emit(
      args.length
    );

    this.e.reg(base);

    this.e.reg(receiver);


    /*
     * Resultado de CALL_METHOD
     */
    this.e.op(OP.READ);

    this.e.reg(65535);

    this.e.reg(dest);

    return dest;
  }


  compilePackageMethodRef(receiver, name) {
    const dest = this.reg();

    const bytes =
      utf8(name);

    this.e.op(OP.PKG_GET);

    this.e.emit(
      ...u16(bytes.length),
      ...bytes
    );

    this.e.reg(receiver);

    this.e.reg(dest);

    return dest;
  }


  /*
   * array[index](...)
   */
  emitIndexedCall(
    base,
    index,
    args,
    dest
  ) {
    const functionReg = this.reg();

    this.e.op(OP.ARRAY_GET);

    this.e.reg(base);
    this.e.reg(index);
    this.e.reg(functionReg);

    const argsBase =
      this.packArgs(args);

    this.e.op(OP.CALL);

    this.e.reg(functionReg);

    this.e.emit(
      args.length
    );

    this.e.reg(argsBase);

    this.e.op(OP.READ);

    this.e.reg(65535);

    this.e.reg(dest);
  }


  /*
   * ----------------------------------------------------------
   * Statements
   * ----------------------------------------------------------
   */

  compileStatement(ctx) {
    /*
     * Variable declaration
     */
    if (ctx.varDeclaration?.()) {
      return this.compileVar(
        ctx.varDeclaration()
      );
    }


    /*
     * Assignment
     */
    if (ctx.assignment?.()) {
      return this.compileAssignment(
        ctx.assignment()
      );
    }


    /*
     * Conditional
     */
    if (ctx.condStatement?.()) {
      return this.compileCond(
        ctx.condStatement()
      );
    }


    /*
     * Loop
     */
    if (ctx.loopStatement?.()) {
      return this.compileLoop(
        ctx.loopStatement()
      );
    }


    /*
     * try/catch
     */
    if (ctx.tryCatchStatement?.()) {
      return this.compileTry(
        ctx.tryCatchStatement()
      );
    }


    /*
     * throw
     */
    if (ctx.throwStatement?.()) {
      const errorReg =
        this.compileExpression(
          ctx.throwStatement().expression()
        );

      const destination = this.reg();

      this.e.op(OP.THROW);

      this.e.reg(errorReg);
      this.e.reg(destination);

      return;
    }


    /*
     * return
     */
    if (ctx.returnStatement?.()) {
      return this.compileReturn(
        ctx.returnStatement()
      );
    }


    /*
     * expression statement
     */
    if (ctx.expression?.()) {
      const r =
        this.compileExpression(
          ctx.expression()
        );

      /*
       * Actualmente no imprimimos automáticamente
       * expresiones normales.
       */
      if (
        this.currentFunction
          ?.discardExpressionPrint
      ) {
        this.e.op(OP.PRINT);
        this.e.reg(r);
      }

      return;
    }
  }


  /*
   * ----------------------------------------------------------
   * Variables
   * ----------------------------------------------------------
   */

  compileVar(v) {
    const id =
      getTextSafe(v.IDENTIFIER());

    const isLocal =
      !!v.scope?.()?.LOCAL?.();


    /*
     * Local variable
     */
    if (
      this.currentFunction &&
      isLocal
    ) {
      const index =
        this.currentFunction.locals.size;

      this.currentFunction.locals.set(
        id,
        index
      );


      if (v.expression()) {
        const value =
          this.compileExpression(
            v.expression()
          );

        this.e.op(
          OP.STORE_LOCAL
        );

        this.e.reg(value);
        this.e.reg(index);
      }

      else if (v.arrayLiteral()) {
        const value =
          this.compileArray(
            v.arrayLiteral()
          );

        this.e.op(
          OP.STORE_LOCAL
        );

        this.e.reg(value);
        this.e.reg(index);
      }

      return;
    }


    /*
     * Global variable
     */
    const globalIndex =
      this.addGlobal(id);


    if (v.expression()) {
      const value =
        this.compileExpression(
          v.expression()
        );

      this.e.op(
        OP.STORE_VAR
      );

      this.e.reg(value);
      this.e.reg(globalIndex);
    }

    else if (v.arrayLiteral()) {
      const value =
        this.compileArray(
          v.arrayLiteral()
        );

      this.e.op(
        OP.STORE_VAR
      );

      this.e.reg(value);
      this.e.reg(globalIndex);
    }
  }


  /*
   * ----------------------------------------------------------
   * Assignment
   * ----------------------------------------------------------
   */

compileAssignment(a) {
  const rawText = getTextSafe(a);
  const text = rawText.replace(/;+$/, "");

  /*
   * La gramática es:
   *
   *   IDENTIFIER '=' expression ';'?
   *   IDENTIFIER '[' expression ']' '=' expression ';'?
   *   IDENTIFIER '++' ';'?
   *   IDENTIFIER '--' ';'?
   *   expression '.' IDENTIFIER '=' expression ';'?
   *   THIS_SCOPE '.' IDENTIFIER '=' expression ';'?
   *
   * IMPORTANTE:
   *
   * NO inspeccionar "." o "[" sobre todo el texto de la asignación,
   * porque el RHS puede contener:
   *
   *   .✓
   *   .!
   *   funciones
   *   accesos
   *   expresiones con "."
   *
   * Primero separamos el LHS del RHS.
   */

  const identifiersRaw = a.IDENTIFIER?.() ?? [];
  const expressionsRaw = a.expression?.() ?? [];

  const identifiers = Array.isArray(identifiersRaw)
    ? identifiersRaw
    : identifiersRaw
      ? [identifiersRaw]
      : [];

  const expressions = Array.isArray(expressionsRaw)
    ? expressionsRaw
    : expressionsRaw
      ? [expressionsRaw]
      : [];

  /*
   * ------------------------------------------------------------
   * 1. ++
   * ------------------------------------------------------------
   *
   * Normalizamos el ";" arriba, por lo que:
   *
   *   fidx++;
   *
   * se convierte en:
   *
   *   fidx++
   */
  if (text.endsWith("++")) {
    const id = identifiers.length > 0
      ? getTextSafe(identifiers[0])
      : null;

    if (!id) {
      throw new Error(`Asignación inválida: ${rawText}`);
    }

    const symbol = this.lookup(id);

    if (!symbol) {
      throw new Error(`Variable no declarada: ${id}`);
    }

    const current = this.loadIdentifier(id, a);

    const one = this.reg();
    this.emitWriteNumber(one, "1");

    const dest = this.reg();

    this.e.op(OP.ADD);
    this.e.reg(current);
    this.e.reg(one);
    this.e.reg(dest);

    if (symbol.kind === "global") {
      this.e.op(OP.STORE_VAR);
      this.e.reg(dest);
      this.e.reg(symbol.index);
    } else {
      this.e.op(OP.STORE_LOCAL);
      this.e.reg(dest);
      this.e.reg(symbol.index);
    }

    return;
  }


  /*
   * ------------------------------------------------------------
   * 2. --
   * ------------------------------------------------------------
   */
  if (text.endsWith("--")) {
    const id = identifiers.length > 0
      ? getTextSafe(identifiers[0])
      : null;

    if (!id) {
      throw new Error(`Asignación inválida: ${rawText}`);
    }

    const symbol = this.lookup(id);

    if (!symbol) {
      throw new Error(`Variable no declarada: ${id}`);
    }

    const current = this.loadIdentifier(id, a);

    const one = this.reg();
    this.emitWriteNumber(one, "1");

    const dest = this.reg();

    this.e.op(OP.SUB);
    this.e.reg(current);
    this.e.reg(one);
    this.e.reg(dest);

    if (symbol.kind === "global") {
      this.e.op(OP.STORE_VAR);
      this.e.reg(dest);
      this.e.reg(symbol.index);
    } else {
      this.e.op(OP.STORE_LOCAL);
      this.e.reg(dest);
      this.e.reg(symbol.index);
    }

    return;
  }


  /*
   * ------------------------------------------------------------
   * 3. Encontrar el "=" de asignación
   * ------------------------------------------------------------
   *
   * Como estamos dentro de assignment(), el primer "=" separa
   * LHS y RHS.
   *
   * Ejemplo:
   *
   *   fib = (n k) : n { ... .✓ ... }
   *
   * lhs = "fib"
   *
   * mientras que:
   *
   *   obj.campo = valor
   *
   * lhs = "obj.campo"
   *
   * y:
   *
   *   array[i] = valor
   *
   * lhs = "array[i]"
   */
  const eqPos = text.indexOf("=");

  if (eqPos < 0) {
    throw new Error(`Asignación no reconocida: ${rawText}`);
  }

  const lhs = text.slice(0, eqPos).trim();


  /*
   * ------------------------------------------------------------
   * 4. this.campo = value
   * ------------------------------------------------------------
   */
  if (
    typeof a.THIS_SCOPE === "function" &&
    a.THIS_SCOPE()
  ) {
    const field =
      identifiers.length > 0
        ? getTextSafe(identifiers[0])
        : null;

    if (!field) {
      throw new Error(
        `Asignación inválida a this: ${rawText}`
      );
    }

    if (expressions.length < 1) {
      throw new Error(
        `Asignación inválida a this.${field}: falta el valor`
      );
    }

    const value =
      this.compileExpression(
        expressions[expressions.length - 1]
      );

    /*
     * THIS_SCOPE representa el objeto actual.
     */
    const base =
      this.compileExpression(
        a.THIS_SCOPE()
      );

    const fieldReg = this.reg();
    this.emitWriteString(fieldReg, field);

    this.e.op(OP.PKG_SET);
    this.e.reg(base);
    this.e.reg(fieldReg);
    this.e.reg(value);

    return;
  }


  /*
   * ------------------------------------------------------------
   * 5. array[index] = value
   * ------------------------------------------------------------
   *
   * Aquí miramos SOLO el LHS.
   *
   * Por ejemplo:
   *
   *   a[i] = fib(k - 1)
   *
   * lhs = "a[i]"
   *
   * Esto no se confunde con un "." o "[" que aparezca en el RHS.
   */
  if (lhs.includes("[") && lhs.includes("]")) {
    const id =
      identifiers.length > 0
        ? getTextSafe(identifiers[0])
        : null;

    if (!id) {
      throw new Error(
        `Asignación de array inválida: ${rawText}`
      );
    }

    if (expressions.length < 2) {
      throw new Error(
        `Asignación de array inválida: ${rawText}`
      );
    }

    const symbol = this.lookup(id);

    if (!symbol) {
      throw new Error(`Variable no declarada: ${id}`);
    }

    const index =
      this.compileExpression(
        expressions[0]
      );

    const value =
      this.compileExpression(
        expressions[expressions.length - 1]
      );

    const arrayReg =
      this.loadIdentifier(id, a);

    this.e.op(OP.ARRAY_SET);
    this.e.reg(arrayReg);
    this.e.reg(index);
    this.e.reg(value);

    return;
  }


  /*
   * ------------------------------------------------------------
   * 6. objeto.campo = value
   * ------------------------------------------------------------
   *
   * Otra vez, "." se busca SOLO en el LHS.
   *
   * Esto es lo que evita romper:
   *
   *   fib = (n k) : n {
   *       (k < 2) ? .✓ -> ...
   *   }
   *
   * porque ahí:
   *
   *   lhs = "fib"
   *
   * aunque el RHS tenga ".✓".
   */
  if (lhs.includes(".")) {
    if (identifiers.length < 1) {
      throw new Error(
        `Asignación de campo inválida: ${rawText}`
      );
    }

    if (expressions.length < 2) {
      throw new Error(
        `Asignación de campo inválida: ${rawText}`
      );
    }

    const field =
      getTextSafe(
        identifiers[identifiers.length - 1]
      );

    const base =
      this.compileExpression(
        expressions[0]
      );

    const value =
      this.compileExpression(
        expressions[expressions.length - 1]
      );

    const fieldReg = this.reg();
    this.emitWriteString(fieldReg, field);

    this.e.op(OP.PKG_SET);
    this.e.reg(base);
    this.e.reg(fieldReg);
    this.e.reg(value);

    return;
  }


  /*
   * ------------------------------------------------------------
   * 7. Asignación simple
   * ------------------------------------------------------------
   *
   *   fib = function(...)
   *
   *   fidx = 0
   *
   *   x = a + b
   *
   * El RHS puede contener absolutamente cualquier expresión.
   */
  if (
    identifiers.length >= 1 &&
    expressions.length >= 1
  ) {
    const id =
      getTextSafe(identifiers[0]);

    const symbol =
      this.lookup(id);

    if (!symbol) {
      throw new Error(
        `Variable no declarada: ${id}`
      );
    }

    const value =
      this.compileExpression(
        expressions[0]
      );

    if (symbol.kind === "global") {
      this.e.op(OP.STORE_VAR);
      this.e.reg(value);
      this.e.reg(symbol.index);
    } else {
      this.e.op(OP.STORE_LOCAL);
      this.e.reg(value);
      this.e.reg(symbol.index);
    }

    return;
  }


  /*
   * ------------------------------------------------------------
   * 8. Nada reconocido
   * ------------------------------------------------------------
   */
  throw new Error(
    `Asignación no reconocida: ${rawText}`
  );
}


  /*
   * ----------------------------------------------------------
   * Conditional
   * ----------------------------------------------------------
   */

  compileCond(c) {
    const value =
      this.compileExpression(
        c.expression()
      );

    const cases =
      c.matchCase?.() || [];

    const endJumps = [];


    for (const matchCase of cases) {
      const isDefault =
        matchCase.getText()
          .startsWith("_");

      let skip = null;


      if (!isDefault) {
        const caseValue =
          this.compileExpression(
            matchCase.expression()
          );

        const equal = this.reg();

        this.e.op(OP.EQ);

        this.e.reg(value);
        this.e.reg(caseValue);
        this.e.reg(equal);


        skip =
  this.e.condJump(
    OP.JUMP_IF_FALSE,
    equal
  );
      }


      this.compileBlock(
        matchCase.block()
      );


      const end =
        this.e.jump(
          OP.JUMP
        );

      endJumps.push(end);


      if (skip) {
        this.e.patchJump(
          skip,
          this.e.ip
        );
      }
    }


    for (const jump of endJumps) {
      this.e.patchJump(
        jump,
        this.e.ip
      );
    }
  }


  /*
   * ----------------------------------------------------------
   * Loop
   * ----------------------------------------------------------
   */

  compileLoop(l) {
    const start =
      this.e.ip;

    const condition =
      this.compileExpression(
        l.expression()
      );

    const jumpFalse =
  this.e.condJump(
    OP.JUMP_IF_FALSE,
    condition
  );


    this.compileBlock(
      l.block()
    );


    const back =
      this.e.jump(
        OP.JUMP
      );

    this.e.patchJump(
      back,
      start
    );

    this.e.patchJump(
      jumpFalse,
      this.e.ip
    );
  }


  /*
   * ----------------------------------------------------------
   * try/catch
   * ----------------------------------------------------------
   */

  compileTry(t) {
    /*
     * TRY_SETUP recibe un offset relativo
     * hacia el catch.
     */
    const setup =
      this.e.jump(
        OP.TRY_SETUP
      );


    this.compileBlock(
      t.block()
    );

    this.e.op(
      OP.TRY_END
    );


    const after =
      this.e.jump(
        OP.JUMP
      );


    /*
     * El catch empieza aquí.
     */
    this.e.patchJump(
      setup,
      this.e.ip
    );


    const catchId =
      getTextSafe(t.IDENTIFIER());

    const destination =
      this.reg();


    if (this.currentFunction) {
      const localIndex =
        this.currentFunction.locals.size;

      this.currentFunction.locals.set(
        catchId,
        localIndex
      );

      this.e.op(
        OP.STORE_LOCAL
      );

      this.e.reg(destination);
      this.e.reg(localIndex);
    }

    else {
      const globalIndex =
        this.addGlobal(catchId);

      this.e.op(
        OP.STORE_VAR
      );

      this.e.reg(destination);
      this.e.reg(globalIndex);
    }


    this.compileBlock(
      t.block(1)
    );


    this.e.patchJump(
      after,
      this.e.ip
    );
  }


  /*
   * ----------------------------------------------------------
   * Return
   * ----------------------------------------------------------
   */

  compileReturn(r) {
    let value;

    if (r.expression()) {
      value =
        this.compileExpression(
          r.expression()
        );
    }

    else {
      value = this.reg();

      this.emitWriteNumber(
        value,
        "0"
      );
    }


    const destination =
      this.currentFunction?.returnDest ?? 0;


    this.e.op(
      OP.RETURN
    );

    this.e.reg(value);

    this.e.reg(destination);
  }


  /*
   * ----------------------------------------------------------
   * Block
   * ----------------------------------------------------------
   */

  compileBlock(block) {
    const statements =
      block.statement?.() || [];

    for (const statement of statements) {
      this.compileStatement(
        statement
      );
    }
  }


  /*
   * ----------------------------------------------------------
   * Function expression
   * ----------------------------------------------------------
   */

  compileFunctionExpr(fd) {
    /*
     * Saltamos por encima del cuerpo
     * de la función para que no se ejecute
     * durante la creación del valor función.
     */
    const skip =
      this.e.jump(
        OP.JUMP
      );

    const bodyIp =
      this.e.ip;


    const parent =
  this.currentFunction;

const parentNextReg =
  this.nextReg;

const fn = {
      locals: new Map(),
      returnDest: 65535,
      params: [],
      discardExpressionPrint: false,
    };


this.currentFunction =
  fn;

this.nextReg =
  0;


    const parameterList =
      fd.parameterList?.();


    const identifiers =
      parameterList?.IDENTIFIER
        ? parameterList.IDENTIFIER()
        : [];


    for (
      let i = 0;
      i < identifiers.length;
      i++
    ) {
      const name =
        getTextSafe(identifiers[i]);

      fn.locals.set(
        name,
        i
      );

      fn.params.push(
        name
      );
    }


    this.compileBlock(
      fd.block()
    );

this.currentFunction =
  parent;

this.nextReg =
  parentNextReg;

    /*
     * Return implícito.
     */
    const zero = this.reg();

    this.emitWriteNumber(
      zero,
      "0"
    );

    this.e.op(
      OP.RETURN
    );

    this.e.reg(zero);

    this.e.reg(65535);

    /*
     * Continuamos después del cuerpo.
     */
    this.e.patchJump(
      skip,
      this.e.ip
    );


    /*
     * Creamos el valor de función.
     *
     * En Vm.c FUNCTION almacena:
     *
     *   u32 instruction pointer
     *   u8  parameter count
     */
    const functionValue =
      this.reg();

    this.e.op(
      OP.WRITE
    );

    this.e.emit(
      TYPE.POINT
    );

    this.e.reg(
      functionValue
    );

    this.e.emit(
      ...u32(bodyIp),
      identifiers.length & 0xff
    );


    return functionValue;
  }


  /*
   * ----------------------------------------------------------
   * Program
   * ----------------------------------------------------------
   */

  compileProgram(tree) {
    const statements =
      tree.statement?.() || [];

    for (const statement of statements) {
      this.compileStatement(
        statement
      );
    }

    this.e.op(
      OP.HALT
    );


    if (this.errors.length) {
      throw new Error(
        this.errors.join("\n")
      );
    }

    return this.e.toBuffer();
  }
}


/*
 * ============================================================
 * Compile()
 * ============================================================
 */

export async function Compile(
  inputFile,
  outputFile,
  dump = false
) {
  const source =
    await fs.readFile(
      inputFile,
      "utf8"
    );


  /*
   * ANTLR NG
   */
  const chars = new antlr4.InputStream(source);
const lexer = new PaxoLexer(chars);
const tokens = new antlr4.CommonTokenStream(lexer);
const parser = new PaxoParser(tokens);

parser.buildParseTrees = true;

const tree = parser.program();
  /*
   * Revisar errores sintácticos.
   */
  const syntaxErrors =
    parser.numberOfSyntaxErrors ??
    parser._syntaxErrors ??
    0;


  if (syntaxErrors) {
    throw new Error(
      `${inputFile}: ` +
      `${syntaxErrors} error(es) de sintaxis`
    );
  }


  /*
   * Compilar.
   */
  const compiler =
    new Compiler(
      source,
      inputFile
    );


  const bytecode =
    compiler.compileProgram(
      tree
    );


  /*
   * Escribir .pbc
   */
  await fs.writeFile(
    outputFile,
    bytecode
  );


  /*
   * Dump hexadecimal opcional.
   */
  if (dump) {
    const lines = [];

    for (
      let i = 0;
      i < bytecode.length;
      i += 16
    ) {
      const bytes =
        [
          ...bytecode.slice(
            i,
            i + 16
          ),
        ]
          .map(
            x =>
              x
                .toString(16)
                .padStart(2, "0")
          )
          .join(" ");

      lines.push(
        `${i
          .toString(16)
          .padStart(6, "0")}  ${bytes}`
      );
    }

    console.log(
      lines.join("\n")
    );
  }


  return bytecode;
}


export {
  Compiler,
  OP,
  TYPE,
  NATIVE,
};