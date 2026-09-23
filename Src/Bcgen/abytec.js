import fs from "fs/promises";
import antlr4 from "antlr4";
import PaxoLexer from "./PaxoLexer.js";
import PaxoParser from "./PaxoParser.js";

function getTextSafe(x) {
  if (x == null) return "";
  if (typeof x === "function") return getTextSafe(x());
  if (Array.isArray(x)) return x.length > 0 ? getTextSafe(x[0]) : "";
  if (typeof x === "string") return x;
  if (typeof x.getText === "function") return x.getText();
  if (typeof x.text === "string") return x.text;
  if (typeof x.symbol?.text === "string") return x.symbol.text;
  if (typeof x.symbol?.textContent === "string") return x.symbol.textContent;
  return String(x);
}

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

  CALL_NATIVE_DYNAMIC: 51,
});

const TYPE = Object.freeze({
  INT: 0, UINT: 1,
  CHAR: 2, TRIT: 3, BOOL: 4,
  FUNC: 5,
  STRING: 6, ARRAY: 7, PACKAGE: 8, COLOR: 9,
  SCOM: 10, COM: 11,
  SFP: 12, FP: 13, DEC: 14, FRAC: 15, ACCUM: 16,
});

// Nativas Core integradas únicamente
const NATIVE = Object.freeze({
  print: 0,
  println: 1,
  typeof: 2,
  scan: 3,
  arrayLen: 4,
  arrayPush: 5,
  ffiLoad: 6,
  ffiCall: 7,
  textColor: 8,
  textType: 9,
  backColor: 10,
  resetColor: 11,
});

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
  b.writeBigUInt64LE(BigInt.asUintN(64, BigInt(n)), 0);
  return [...b];
}

function utf8(s) {
  return [...Buffer.from(s, "utf8")];
}

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

  if (!digits) digits = "0";

  let frac = fractionPart.length;

  while (digits.length > 1 && digits.endsWith("0")) {
    digits = digits.slice(0, -1);
    frac--;
  }

  if (digits.length > maxDigits) {
    const removed = digits.length - maxDigits;
    digits = digits.slice(0, maxDigits);
    frac = Math.max(0, frac - removed);
  }

  let mant = BigInt(digits);
  let exp = 15 - frac;

  while (mant > 0n && mant % 10n === 0n && exp < 31) {
    mant /= 10n;
    exp++;
  }

  if (exp < 0) exp = 0;
  if (exp > 31) exp = 31;

  return { sign, exp, mant };
}

function complexParts(raw) {
  let s = raw.trim();
  if (!s.endsWith("i")) throw new Error(`Complejo invalido: ${raw}`);
  s = s.slice(0, -1);

  let split = -1;
  for (let i = 1; i < s.length; i++) {
    if ((s[i] === "+" || s[i] === "-") && s[i - 1].toLowerCase() !== "e") {
      split = i;
      break;
    }
  }

  let re = "0";
  let im = "0";

  if (split < 0) {
    im = s || "1";
    if (im === "+" || im === "") im = "1";
    else if (im === "-") im = "-1";
  } else {
    re = s.slice(0, split) || "0";
    im = s.slice(split);
    if (im === "+" || im === "") im = "1";
    else if (im === "-") im = "-1";
  }

  const r = numberParts(re, 7);
  const m = numberParts(im, 7);

  if (r.exp > 31 || m.exp > 31 || r.mant > 0xffffffn || m.mant > 0xffffffn) {
    throw new Error(`Complejo fuera de rango: ${raw}`);
  }

  return { r, m };
}

class Emitter {
  constructor() {
    this.bytes = [];
  }

  get ip() {
    return this.bytes.length;
  }

  emit(...xs) {
    this.bytes.push(...xs.map(x => x & 0xff));
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
    if (offset < -32768 || offset > 32767) {
      throw new Error("Salto demasiado grande para i16");
    }
    const b = i16(offset);
    this.bytes[pos] = b[0];
    this.bytes[pos + 1] = b[1];
  }

  jump(opcode) {
    this.op(opcode);
    const p = this.ip;
    this.emit(0, 0);
    return { p, base: () => this.ip };
  }

  condJump(opcode, conditionReg) {
    this.op(opcode);
    this.reg(conditionReg);
    const p = this.ip;
    this.emit(0, 0);
    return { p, base: () => this.ip };
  }

  patchJump(jump, target) {
    this.patchI16(jump.p, target, jump.p + 2);
  }

  toBuffer() {
    return Buffer.from(this.bytes);
  }
}

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
    this.nativeNames = new Set(Object.keys(NATIVE));
  }

  error(ctx, message) {
    const line = ctx?.start?.line ?? "?";
    this.errors.push(`${this.file}:${line}: ${message}`);
  }

  reg() {
    if (this.nextReg > 65534) throw new Error("Demasiados registros temporales");
    return this.nextReg++;
  }

  resetTemps(n = 0) {
    this.nextReg = n;
  }

  addGlobal(name) {
    if (this.globals.has(name)) return this.globals.get(name);
    const index = this.globals.size;
    if (index > 65535) throw new Error("Demasiadas variables globales");
    this.globals.set(name, index);
    return index;
  }

  lookup(name) {
    if (this.currentFunction?.locals.has(name)) {
      return { kind: "local", index: this.currentFunction.locals.get(name) };
    }
    if (this.globals.has(name)) {
      return { kind: "global", index: this.globals.get(name) };
    }
    return null;
  }

  getTypeEnum(typeCtx) {
    if (!typeCtx) return TYPE.INT;
    const t = getTextSafe(typeCtx).toLowerCase();
    if (t === "int" || t === "var" || t === "📥") return TYPE.INT;
    if (t === "uint") return TYPE.UINT;
    if (t === "flt") return TYPE.FP;
    if (t === "sflt") return TYPE.SFP;
    if (t === "dec") return TYPE.DEC;
    if (t === "frac") return TYPE.FRAC;
    if (t === "acc") return TYPE.ACCUM;
    if (t === "abc") return TYPE.CHAR;
    if (t === "trit") return TYPE.TRIT;
    if (t === "bool") return TYPE.BOOL;
    if (t === "fx") return TYPE.FUNC;
    if (t === "pkg" || t === "📦") return TYPE.PACKAGE;
    if (t === "col") return TYPE.COLOR;
    if (t === "com") return TYPE.COM;
    if (t === "scom") return TYPE.SCOM;
    return TYPE.INT;
  }

  emitWriteNumber(reg, raw) {
    const p = numberParts(raw);
    this.e.op(OP.WRITE);
    this.e.emit(TYPE.INT);
    this.e.reg(reg);
    const payload = (BigInt(p.sign) << 59n) | (BigInt(p.exp) << 54n) | p.mant;
    this.e.emit(...u64(payload));
  }

  emitWriteString(reg, value) {
    const bytes = utf8(value);
    if (bytes.length > 65535) throw new Error("String demasiado larga");
    this.e.op(OP.WRITE);
    this.e.emit(TYPE.STRING);
    this.e.reg(reg);
    this.e.emit(...u16(bytes.length), ...bytes);
  }

  emitWriteChar(reg, value) {
    const codePoint = [...value][0]?.codePointAt(0) ?? 0;
    this.e.op(OP.WRITE);
    this.e.emit(TYPE.CHAR);
    this.e.reg(reg);
    this.e.emit(...u32(codePoint));
  }

  emitWriteBool(reg, value) {
    this.e.op(OP.WRITE);
    this.e.emit(TYPE.BOOL);
    this.e.reg(reg);
    this.e.emit(value ? 1 : 0);
  }

  emitWriteTrit(reg, value) {
    this.e.op(OP.WRITE);
    this.e.emit(TYPE.TRIT);
    this.e.reg(reg);
    this.e.emit(value & 3);
  }

  emitWriteColor(reg, raw) {
    const value = parseInt(raw.slice(1), 16) >>> 0;
    this.e.op(OP.WRITE);
    this.e.emit(TYPE.COLOR);
    this.e.reg(reg);
    this.e.emit(...u32(value));
  }

  emitWriteComplex(reg, raw) {
    const { r: re, m: im } = complexParts(raw);
    const payload =
      (BigInt(re.sign) << 59n) |
      (BigInt(re.exp) << 54n) |
      (re.mant << 30n) |
      (BigInt(im.sign) << 29n) |
      (BigInt(im.exp) << 24n) |
      im.mant;

    this.e.op(OP.WRITE);
    this.e.emit(TYPE.COM);
    this.e.reg(reg);
    this.e.emit(...u64(payload));
  }

  loadIdentifier(name, ctx) {
    const symbol = this.lookup(name);
    if (!symbol) throw new Error(`Variable no declarada: ${name}`);

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

  compileExpression(ctx) {
    if (!ctx) {
      const r = this.reg();
      this.emitWriteNumber(r, "0");
      return r;
    }

    if (Array.isArray(ctx)) {
      ctx = ctx[0];
      if (!ctx) {
        const r = this.reg();
        this.emitWriteNumber(r, "0");
        return r;
      }
    }

    const name = ctx.constructor?.name || "";
    const s = getTextSafe(ctx);

    if (name.includes("IntLitExpr") || name.includes("DecLitExpr")) {
      const r = this.reg();
      this.emitWriteNumber(r, s);
      return r;
    }

    if (name.includes("CharLitExpr")) {
      const r = this.reg();
      this.emitWriteChar(r, s.slice(1, -1));
      return r;
    }

    if (name.includes("StringLitExpr")) {
      const r = this.reg();
      let value = s.slice(1, -1)
        .replace(/\\n/g, "\n")
        .replace(/\\r/g, "\r")
        .replace(/\\t/g, "\t")
        .replace(/\\"/g, '"')
        .replace(/\\\\/g, "\\");
      this.emitWriteString(r, value);
      return r;
    }

    if (name.includes("BoolBitExpr")) {
      const r = this.reg();
      this.emitWriteBool(r, s === ".✓" || s === "true");
      return r;
    }

    if (name.includes("BoolTritExpr")) {
      const r = this.reg();
      let value = 0;
      if (s === "✓") value = 1;
      else if (s === "•") value = 2;
      this.emitWriteTrit(r, value);
      return r;
    }

    if (name.includes("ColLitExpr")) {
      const r = this.reg();
      this.emitWriteColor(r, s);
      return r;
    }

    if (name.includes("ComLitExpr")) {
      const r = this.reg();
      this.emitWriteComplex(r, s);
      return r;
    }

    if (name.includes("PtrLitExpr")) {
      const r = this.reg();
      const ptrName = s.replace(/^@/, "");
      const symbol = this.lookup(ptrName);
      if (!symbol) throw new Error(`Variable referenciada no declarada: ${ptrName}`);
      this.emitWriteNumber(r, String(symbol.index));
      return r;
    }

    if (name.includes("IdentExpr")) {
      return this.loadIdentifier(s, ctx);
    }

    if (name.includes("ThisScopeExpr")) {
      const r = this.reg();
      const id = s.split(".").slice(1).join(".") || s.replace(/^📍/, "").replace(/^this\./, "");
      const nameBytes = utf8(id);
      this.e.op(OP.THIS_GET);
      this.e.emit(...u16(nameBytes.length), ...nameBytes);
      this.e.reg(r);
      return r;
    }

    if (name.includes("FuncExpr")) {
      return this.compileFunctionExpr(ctx.functionDeclaration?.() || ctx);
    }

    if (name.includes("PkgExpr")) {
      return this.compilePackage(ctx.pkgDeclaration?.() || ctx);
    }

    if (name.includes("ArrayLitExpr")) {
      return this.compileArray(ctx.arrayLiteral?.() || ctx);
    }

    if (name.includes("IndexedAccessExpr")) {
      const expressions = ctx.expression?.() || [];
      const exprs = Array.isArray(expressions) ? expressions : [expressions];
      const array = this.compileExpression(exprs[0]);
      const index = this.compileExpression(exprs[1]);
      const dest = this.reg();
      this.e.op(OP.ARRAY_GET);
      this.e.reg(array);
      this.e.reg(index);
      this.e.reg(dest);
      return dest;
    }

    if (name.includes("IndexedCallExpr")) {
      const expressions = ctx.expression?.() || [];
      const exprs = Array.isArray(expressions) ? expressions : [expressions];
      const base = this.compileExpression(exprs[0]);
      const index = this.compileExpression(exprs[1]);
      const args = this.compileArgs(ctx.argumentList?.());
      const dest = this.reg();
      this.emitIndexedCall(base, index, args, dest);
      return dest;
    }

    if (name.includes("MethodCallExpr")) {
      return this.compileMethodCall(ctx);
    }

    if (name.includes("DotAccessExpr")) {
      const expressions = ctx.expression?.() || [];
      const exprs = Array.isArray(expressions) ? expressions : [expressions];
      const base = this.compileExpression(exprs[0]);
      const id = getTextSafe(ctx.IDENTIFIER?.());
      const dest = this.reg();
      const bytes = utf8(id);
      this.e.op(OP.PKG_GET);
      this.e.emit(...u16(bytes.length), ...bytes);
      this.e.reg(base);
      this.e.reg(dest);
      return dest;
    }

    if (name.includes("ParenExpr")) {
      const expr = ctx.expression?.();
      return this.compileExpression(Array.isArray(expr) ? expr[0] : expr);
    }

    if (name.includes("CallExpr")) {
      return this.compileCall(ctx);
    }

    if (
      name.includes("MultDivExpr") ||
      name.includes("AddSubExpr") ||
      name.includes("ShiftExpr") ||
      name.includes("RelationalExpr") ||
      name.includes("BitwiseExpr")
    ) {
      return this.compileBinary(ctx, name);
    }

    if (
      name.includes("NotExpr") ||
      name.includes("UnaryNotExpr") ||
      name.includes("NotgateExpr")
    ) {
      const expressions = ctx.expression?.() || [];
      const exprs = Array.isArray(expressions) ? expressions : [expressions];
      const operand = this.compileExpression(exprs[0] || ctx.getChild?.(1));
      const opToken = ctx.getChild?.(0)?.getText?.()?.trim();
      const dest = this.reg();
      const op = (opToken === "!" || opToken === ".~" || opToken === ".!") ? OP.BIT_NOT : OP.NOT;
      this.e.op(op);
      this.e.reg(operand);
      this.e.reg(dest);
      return dest;
    }

    if (typeof ctx.expression === "function" && ctx.expression()) {
      return this.compileExpression(ctx.expression());
    }

    const r = this.reg();
    this.emitWriteNumber(r, "0");
    return r;
  }

  compileArgs(ctx) {
    if (!ctx) return [];
    const exprs = ctx.expression?.() ?? ctx.argument?.();
    if (Array.isArray(exprs)) {
      return exprs.map(e => this.compileExpression(e));
    }
    if (exprs) {
      return [this.compileExpression(exprs)];
    }
    return [];
  }

  packArgs(args) {
    if (args.length === 0) return 0;
    const base = Math.min(...args);
    let contiguous = true;

    for (let i = 0; i < args.length; i++) {
      if (args[i] !== base + i) {
        contiguous = false;
        break;
      }
    }

    if (contiguous) return base;

    const baseReg = this.nextReg;
    for (let i = 0; i < args.length; i++) {
      const targetReg = this.reg();
      this.e.op(OP.READ);
      this.e.reg(args[i]);
      this.e.reg(targetReg);
    }
    return baseReg;
  }

  compileCall(ctx) {
    const name = getTextSafe(ctx.IDENTIFIER?.());
    const args = this.compileArgs(ctx.argumentList?.());

    // 1. Nativas estáticas del core
    if (Object.prototype.hasOwnProperty.call(NATIVE, name)) {
      const base = this.packArgs(args);
      const dest = this.reg();
      this.e.op(OP.CALL_NATIVE);
      this.e.emit(...u16(NATIVE[name]));
      this.e.emit(args.length);
      this.e.reg(base);
      this.e.reg(dest);
      return dest;
    }

    // 2. Funciones/Variables declaradas en el ámbito del script
    const symbol = this.lookup(name);
    if (symbol) {
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

    // 3. Nativas dinámicas / Módulos FFI cargados externamente
    const base = this.packArgs(args);
    const dest = this.reg();
    const nameBytes = utf8(name);

    this.e.op(OP.CALL_NATIVE_DYNAMIC);
    this.e.emit(...u16(nameBytes.length), ...nameBytes);
    this.e.emit(args.length);
    this.e.reg(base);
    this.e.reg(dest);

    return dest;
  }

  compileBinary(ctx, name) {
    const expressions = ctx.expression?.() || [];
    const exprs = Array.isArray(expressions) ? expressions : [expressions];
    const left = this.compileExpression(exprs[0]);
    const right = this.compileExpression(exprs[1]);
    const dest = this.reg();

    let operator = null;
    const opText = ctx.getChild?.(1)?.getText?.()?.trim() || "";

    if (name.includes("MultDivExpr")) {
      operator = (opText === "÷" || opText === "/") ? OP.DIV : OP.MUL;
    } else if (name.includes("AddSubExpr")) {
      operator = opText === "-" ? OP.SUB : OP.ADD;
    } else if (name.includes("ShiftExpr")) {
      operator = (opText === "»•" || opText === ">>") ? OP.BIT_SHR : OP.BIT_SHL;
    } else if (name.includes("RelationalExpr")) {
      const relational = {
        "<": OP.LT, ">": OP.GT, "≤": OP.LTE, "<=": OP.LTE,
        "≥": OP.GTE, ">=": OP.GTE, "==": OP.EQ, "!=": OP.NEQ, "≠": OP.NEQ,
      };
      operator = relational[opText];
    } else {
      const bitwise = {
        "&": OP.BIT_AND, "|": OP.BIT_OR, ".&": OP.AND,
        ".|": OP.OR, "^": OP.BIT_XOR,
      };
      operator = bitwise[opText];
    }

    if (operator == null) throw new Error(`Operador no soportado: ${opText}`);

    this.e.op(operator);
    this.e.reg(left);
    this.e.reg(right);
    this.e.reg(dest);
    return dest;
  }

  compileArray(ctx) {
    const expressionsRaw = ctx.expression?.() || [];
    const expressions = Array.isArray(expressionsRaw)
      ? expressionsRaw
      : (expressionsRaw ? [expressionsRaw] : []);
    const regs = expressions.map(e => this.compileExpression(e));

    const dest = this.reg();
    const base = this.packArgs(regs);
    this.e.op(OP.ARRAY_NEW);
    this.e.emit(...u16(regs.length));
    this.e.reg(base);
    this.e.reg(dest);
    return dest;
  }

  compilePackage(ctx) {
    const varsRaw = ctx.varDeclaration?.() || [];
    const vars = Array.isArray(varsRaw) ? varsRaw : [varsRaw];
    const regs = [];

    for (const variable of vars) {
      const id = getTextSafe(variable.IDENTIFIER?.());
      let value;

      if (variable.expression?.()) {
        value = this.compileExpression(variable.expression());
      } else if (variable.arrayLiteral?.()) {
        value = this.compileArray(variable.arrayLiteral());
      } else {
        value = this.reg();
        this.emitWriteNumber(value, "0");
      }

      const key = this.reg();
      this.emitWriteString(key, id);
      regs.push(key, value);
    }

    const dest = this.reg();
    const base = this.packArgs(regs);
    this.e.op(OP.PKG_NEW);
    this.e.emit(...u16(vars.length));
    this.e.reg(base);
    this.e.reg(dest);
    return dest;
  }

  compileMethodCall(ctx) {
    const expressions = ctx.expression?.() || [];
    const exprs = Array.isArray(expressions) ? expressions : [expressions];
    const receiver = this.compileExpression(exprs[0]);
    const name = getTextSafe(ctx.IDENTIFIER?.());
    const functionReg = this.compilePackageMethodRef(receiver, name);
    const args = this.compileArgs(ctx.argumentList?.());
    const base = this.packArgs(args);
    const dest = this.reg();

    this.e.op(OP.CALL_METHOD);
    this.e.reg(functionReg);
    this.e.emit(args.length);
    this.e.reg(base);
    this.e.reg(receiver);

    this.e.op(OP.READ);
    this.e.reg(65535);
    this.e.reg(dest);
    return dest;
  }

  compilePackageMethodRef(receiver, name) {
    const dest = this.reg();
    const bytes = utf8(name);
    this.e.op(OP.PKG_GET);
    this.e.emit(...u16(bytes.length), ...bytes);
    this.e.reg(receiver);
    this.e.reg(dest);
    return dest;
  }

  emitIndexedCall(base, index, args, dest) {
    const functionReg = this.reg();
    this.e.op(OP.ARRAY_GET);
    this.e.reg(base);
    this.e.reg(index);
    this.e.reg(functionReg);

    const argsBase = this.packArgs(args);
    this.e.op(OP.CALL);
    this.e.reg(functionReg);
    this.e.emit(args.length);
    this.e.reg(argsBase);

    this.e.op(OP.READ);
    this.e.reg(65535);
    this.e.reg(dest);
  }

  compileStatement(ctx) {
    if (!ctx || ctx.getText() === ";") return;

    if (ctx.INCLUDE?.() || getTextSafe(ctx).startsWith("+📚") || getTextSafe(ctx).startsWith("add")) {
      return;
    }
    if (ctx.varDeclaration?.()) {
      const v = ctx.varDeclaration();
      return this.compileVar(Array.isArray(v) ? v[0] : v);
    }
    if (ctx.assignment?.()) {
      const a = ctx.assignment();
      return this.compileAssignment(Array.isArray(a) ? a[0] : a);
    }
    if (ctx.condStatement?.()) {
      const c = ctx.condStatement();
      return this.compileCond(Array.isArray(c) ? c[0] : c);
    }
    if (ctx.loopStatement?.()) {
      const l = ctx.loopStatement();
      return this.compileLoop(Array.isArray(l) ? l[0] : l);
    }
    if (ctx.tryCatchStatement?.()) {
      const t = ctx.tryCatchStatement();
      return this.compileTry(Array.isArray(t) ? t[0] : t);
    }
    if (ctx.throwStatement?.()) {
      const th = ctx.throwStatement();
      const stmt = Array.isArray(th) ? th[0] : th;
      const errorReg = this.compileExpression(stmt.expression?.());
      const destination = this.reg();
      this.e.op(OP.THROW);
      this.e.reg(errorReg);
      this.e.reg(destination);
      return;
    }
    if (ctx.returnStatement?.()) {
      const r = ctx.returnStatement();
      return this.compileReturn(Array.isArray(r) ? r[0] : r);
    }
    if (ctx.expression?.()) {
      const r = this.compileExpression(ctx.expression());
      if (this.currentFunction?.discardExpressionPrint) {
        this.e.op(OP.PRINT);
        this.e.reg(r);
      }
      return;
    }
  }

  compileVar(v) {
    const id = getTextSafe(v.IDENTIFIER?.());
    const scopeCtx = v.scope?.();
    const isExplicitGlobal = !!scopeCtx?.GLOBAL?.() || !!v.GLOBAL?.();
    const isExplicitLocal = !!scopeCtx?.LOCAL?.() || !!v.LOCAL?.();

    const isLocal = isExplicitLocal || (!!this.currentFunction && !isExplicitGlobal);
    const targetType = this.getTypeEnum(v.type?.());

    let value;
    if (v.expression?.()) {
      value = this.compileExpression(v.expression());
    } else if (v.arrayLiteral?.()) {
      value = this.compileArray(v.arrayLiteral());
    } else {
      value = this.reg();
      this.emitWriteNumber(value, "0");
    }

    if (v.type?.()) {
      const casted = this.reg();
      this.e.op(OP.CAST);
      this.e.reg(value);
      this.e.emit(targetType);
      this.e.reg(casted);
      value = casted;
    }

    if (isLocal) {
      let index;
      if (this.currentFunction.locals.has(id)) {
        index = this.currentFunction.locals.get(id);
      } else {
        index = this.currentFunction.locals.size;
        this.currentFunction.locals.set(id, index);
      }

      this.e.op(OP.STORE_LOCAL);
      this.e.reg(value);
      this.e.reg(index);
      return;
    }

    const globalIndex = this.addGlobal(id);
    this.e.op(OP.STORE_VAR);
    this.e.reg(value);
    this.e.reg(globalIndex);
  }

  compileAssignment(a) {
    const fullText = getTextSafe(a);
    const firstChildText = a.getChild?.(0)?.getText?.();
    const secondChildText = a.getChild?.(1)?.getText?.();

    if (secondChildText === "++" || fullText.includes("++")) {
      const id = getTextSafe(a.IDENTIFIER?.());
      const symbol = this.lookup(id);
      if (!symbol) throw new Error(`Variable no declarada: ${id}`);

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

    if (secondChildText === "--" || fullText.includes("--")) {
      const id = getTextSafe(a.IDENTIFIER?.());
      const symbol = this.lookup(id);
      if (!symbol) throw new Error(`Variable no declarada: ${id}`);

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

    if (a.THIS_SCOPE?.() || firstChildText === "this" || firstChildText === "📍") {
      const field = getTextSafe(a.IDENTIFIER?.());
      const expressions = a.expression?.();
      const valueExpr = Array.isArray(expressions) ? expressions[0] : expressions;
      const value = this.compileExpression(valueExpr);

      const fieldReg = this.reg();
      this.emitWriteString(fieldReg, field);

      this.e.op(OP.THIS_SET);
      this.e.reg(fieldReg);
      this.e.reg(value);
      return;
    }

    if (secondChildText === "[") {
      const id = getTextSafe(a.IDENTIFIER?.());
      const symbol = this.lookup(id);
      if (!symbol) throw new Error(`Variable no declarada: ${id}`);

      const expressions = a.expression?.();
      const exprs = Array.isArray(expressions) ? expressions : [expressions];
      const index = this.compileExpression(exprs[0]);
      const value = this.compileExpression(exprs[1]);
      const arrayReg = this.loadIdentifier(id, a);

      this.e.op(OP.ARRAY_SET);
      this.e.reg(arrayReg);
      this.e.reg(index);
      this.e.reg(value);
      return;
    }

    if (secondChildText === ".") {
      const field = getTextSafe(a.IDENTIFIER?.());
      const expressions = a.expression?.();
      const exprs = Array.isArray(expressions) ? expressions : [expressions];
      const base = this.compileExpression(exprs[0]);
      const value = this.compileExpression(exprs[1]);

      const fieldReg = this.reg();
      this.emitWriteString(fieldReg, field);

      this.e.op(OP.PKG_SET);
      this.e.reg(base);
      this.e.reg(fieldReg);
      this.e.reg(value);
      return;
    }

    const id = getTextSafe(a.IDENTIFIER?.());
    if (id) {
      const symbol = this.lookup(id);
      if (!symbol) throw new Error(`Variable no declarada: ${id}`);

      const expressions = a.expression?.();
      const expr = Array.isArray(expressions) ? expressions[0] : expressions;
      const value = this.compileExpression(expr);

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

    throw new Error(`Asignación no reconocida: ${fullText}`);
  }

  compileCond(c) {
    const value = this.compileExpression(c.expression?.());
    const casesRaw = c.matchCase?.() || [];
    const cases = Array.isArray(casesRaw) ? casesRaw : [casesRaw];
    const endJumps = [];

    for (const matchCase of cases) {
      const expr = matchCase.expression?.();
      const isDefault = !expr || matchCase.getChild?.(0)?.getText?.() === "_";

      let skip = null;

      if (!isDefault) {
        const caseValue = this.compileExpression(expr);
        const equal = this.reg();

        this.e.op(OP.EQ);
        this.e.reg(value);
        this.e.reg(caseValue);
        this.e.reg(equal);

        skip = this.e.condJump(OP.JUMP_IF_FALSE, equal);
      }

      this.compileBlock(matchCase.block?.());

      const end = this.e.jump(OP.JUMP);
      endJumps.push(end);

      if (skip) {
        this.e.patchJump(skip, this.e.ip);
      }
    }

    for (const jump of endJumps) {
      this.e.patchJump(jump, this.e.ip);
    }
  }

  compileLoop(l) {
    const start = this.e.ip;
    const condition = this.compileExpression(l.expression?.());

    const modeText = l.loopMode?.()?.getText?.() || "";
    const isPause = modeText === "⏸️" || modeText === "stop" || modeText === "||";

    const jumpExitOp = isPause ? OP.JUMP_IF_TRUE : OP.JUMP_IF_FALSE;
    const jumpExit = this.e.condJump(jumpExitOp, condition);

    this.compileBlock(l.block?.());

    const back = this.e.jump(OP.JUMP);
    this.e.patchJump(back, start);
    this.e.patchJump(jumpExit, this.e.ip);
  }

  compileTry(t) {
    const setup = this.e.jump(OP.TRY_SETUP);

    const tryBlock = t.block?.(0) ?? (Array.isArray(t.block?.()) ? t.block()[0] : null);
    this.compileBlock(tryBlock);
    this.e.op(OP.TRY_END);

    const after = this.e.jump(OP.JUMP);

    this.e.patchJump(setup, this.e.ip);

    const catchId = getTextSafe(t.IDENTIFIER?.());
    const destination = this.reg();

    if (this.currentFunction) {
      const localIndex = this.currentFunction.locals.size;
      this.currentFunction.locals.set(catchId, localIndex);
      this.e.op(OP.STORE_LOCAL);
      this.e.reg(destination);
      this.e.reg(localIndex);
    } else {
      const globalIndex = this.addGlobal(catchId);
      this.e.op(OP.STORE_VAR);
      this.e.reg(destination);
      this.e.reg(globalIndex);
    }

    const catchBlock = t.block?.(1) ?? (Array.isArray(t.block?.()) ? t.block()[1] : null);
    this.compileBlock(catchBlock);
    this.e.patchJump(after, this.e.ip);
  }

  compileReturn(r) {
    let value;
    if (r.expression?.()) {
      value = this.compileExpression(r.expression());
    } else {
      value = this.reg();
      this.emitWriteNumber(value, "0");
    }

    const destination = this.currentFunction?.returnDest ?? 65535;

    this.e.op(OP.RETURN);
    this.e.reg(value);
    this.e.reg(destination);
  }

  compileBlock(block) {
    if (!block) return;
    const statementsRaw = block.statement?.() || [];
    const statements = Array.isArray(statementsRaw) ? statementsRaw : [statementsRaw];
    for (const statement of statements) {
      this.compileStatement(statement);
      const baseReg = this.currentFunction ? this.currentFunction.locals.size : 0;
      this.resetTemps(baseReg);
    }
  }

  compileFunctionExpr(fd) {
    const skip = this.e.jump(OP.JUMP);
    const bodyIp = this.e.ip;

    const parent = this.currentFunction;
    const parentNextReg = this.nextReg;

    const parameterList = fd.parameterList?.();
    const identifiersRaw = parameterList?.IDENTIFIER ? parameterList.IDENTIFIER() : [];
    const identifiers = Array.isArray(identifiersRaw) ? identifiersRaw : (identifiersRaw ? [identifiersRaw] : []);

    const fn = {
      locals: new Map(),
      returnDest: 65535,
      params: [],
      discardExpressionPrint: false,
    };

    this.currentFunction = fn;
    this.nextReg = identifiers.length;

    for (let i = 0; i < identifiers.length; i++) {
      const name = getTextSafe(identifiers[i]);
      fn.locals.set(name, i);
      fn.params.push(name);
    }

    this.compileBlock(fd.block?.());

    const zero = this.reg();
    this.emitWriteNumber(zero, "0");
    this.e.op(OP.RETURN);
    this.e.reg(zero);
    this.e.reg(65535);

    this.currentFunction = parent;
    this.nextReg = parentNextReg;

    this.e.patchJump(skip, this.e.ip);

    const functionValue = this.reg();
    this.e.op(OP.WRITE);
    this.e.emit(TYPE.FUNC);
    this.e.reg(functionValue);
    this.e.emit(...u32(bodyIp), identifiers.length & 0xff);

    return functionValue;
  }

  compileProgram(tree) {
    const statementsRaw = tree.statement?.() || [];
    const statements = Array.isArray(statementsRaw) ? statementsRaw : [statementsRaw];
    for (const statement of statements) {
      this.compileStatement(statement);
      const baseReg = this.currentFunction ? this.currentFunction.locals.size : 0;
      this.resetTemps(baseReg);
    }

    this.e.op(OP.HALT);

    if (this.errors.length) {
      throw new Error(this.errors.join("\n"));
    }

    return this.e.toBuffer();
  }
}

export async function Compile(inputFile, outputFile, dump = false) {
  const source = await fs.readFile(inputFile, "utf8");

  const chars = antlr4.CharStreams
    ? antlr4.CharStreams.fromString(source)
    : new antlr4.InputStream(source);
  const lexer = new PaxoLexer(chars);
  const tokens = new antlr4.CommonTokenStream(lexer);
  const parser = new PaxoParser(tokens);

  parser.buildParseTrees = true;
  const tree = parser.program();

  const syntaxErrors = parser.numberOfSyntaxErrors ?? parser._syntaxErrors ?? 0;

  if (syntaxErrors) {
    throw new Error(`${inputFile}: ${syntaxErrors} error(es) de sintaxis`);
  }

  const compiler = new Compiler(source, inputFile);
  const bytecode = compiler.compileProgram(tree);

  await fs.writeFile(outputFile, bytecode);

  if (dump) {
    const lines = [];
    for (let i = 0; i < bytecode.length; i += 16) {
      const bytes = [...bytecode.slice(i, i + 16)]
        .map(x => x.toString(16).padStart(2, "0"))
        .join(" ");
      lines.push(`${i.toString(16).padStart(6, "0")}  ${bytes}`);
    }
    console.log(lines.join("\n"));
  }

  return bytecode;
}

export { Compiler, OP, TYPE, NATIVE };
