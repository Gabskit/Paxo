import fs from 'fs';
import antlr4 from 'antlr4';
import PaxoLexer from './PaxoLexer.js';
import PaxoParser from './PaxoParser.js';
import PaxoListener from './PaxoListener.js';

// ==========================================
// OPCODES — deben coincidir con Vm.c
// ==========================================
export const OP_PUSH          = 0;
export const OP_POP           = 1;
export const OP_ADD           = 2;
export const OP_SUB           = 3;
export const OP_MUL           = 4;
export const OP_DIV           = 5;
export const OP_CAST          = 6;
export const OP_LOAD_VAR      = 7;
export const OP_STORE_VAR     = 8;
export const OP_PRINT         = 9;
export const OP_JUMP          = 10;
export const OP_JUMP_IF_FALSE = 11;
export const OP_JUMP_IF_TRUE  = 12;
export const OP_HALT          = 13;
export const OP_CALL          = 14;
export const OP_CALL_NATIVE   = 15;
export const OP_EQ            = 16;
export const OP_NEQ           = 17;
export const OP_LT            = 18;
export const OP_GT            = 19;
export const OP_LTE           = 20;
export const OP_GTE           = 21;
export const OP_AND           = 22;
export const OP_OR            = 23;
export const OP_NOT           = 24;
export const OP_BIT_AND       = 25;
export const OP_BIT_OR        = 26;
export const OP_BIT_NOT       = 27;
export const OP_BIT_XOR       = 28;
export const OP_BIT_SHL       = 29;
export const OP_BIT_SHR       = 30;
export const OP_INC           = 31;
export const OP_DEC           = 32;
export const OP_RETURN        = 33;
export const OP_CALL_VAR      = 34;
export const OP_ARRAY_NEW     = 35;
export const OP_ARRAY_GET     = 36;
export const OP_ARRAY_SET     = 37;
export const OP_PKG_NEW       = 38;
export const OP_PKG_GET       = 39;
export const OP_PKG_SET       = 40;
export const OP_TRY_SETUP     = 41;
export const OP_TRY_END       = 42;
export const OP_THROW         = 43;
export const OP_STORE_LOCAL   = 44;
export const OP_LOAD_LOCAL    = 45;
export const OP_CALL_METHOD   = 46;
export const OP_THIS_GET      = 47;
export const OP_THIS_SET      = 48;

export const TYPE_NUM16     = 0;
export const TYPE_NUM64     = 1;
export const TYPE_CHAR      = 2;
export const TYPE_TRIT      = 3;
export const TYPE_BOOL      = 4;
export const TYPE_POINT     = 5;
export const TYPE_FUNC      = 6;
export const TYPE_STRING    = 7;
export const TYPE_ARRAY     = 8;
export const TYPE_PKG       = 9;
export const TYPE_INT       = 10;
export const TYPE_PKDEC     = 11;
export const TYPE_COLOR     = 12;
export const TYPE_COMPLEX   = 13;
export const TYPE_COMPLEX16 = 14;

export const NATIVE_PRINT          = 0;
export const NATIVE_PRINTLN        = 1;
export const NATIVE_TYPEOF         = 2;
export const NATIVE_SET_COLOR_TEXT = 3;
export const NATIVE_SET_TYPE_TEXT  = 4;
export const NATIVE_SET_COLOR_BACK = 5;
export const NATIVE_RESET_COLOR    = 6;
export const NATIVE_SCAN           = 7;
export const NATIVE_ARRAY_LEN      = 8;
export const NATIVE_ARRAY_PUSH     = 9;

export const NATIVE_INIT_WINDOW  = 10;
export const NATIVE_CLEAR_SCREEN = 11;
export const NATIVE_DRAW_RECT    = 12;

export const NATIVE_FILE_READ   = 13;
export const NATIVE_FILE_WRITE  = 14;
export const NATIVE_FILE_APPEND = 15;
export const NATIVE_FILE_EXISTS = 16;
export const NATIVE_FILE_DELETE = 17;

export const NATIVE_IMG_LOAD     = 18;
export const NATIVE_IMG_INFO     = 19;
export const NATIVE_IMG_SAVE_PNG = 20;
export const NATIVE_IMG_SAVE_JPG = 21;
export const NATIVE_IMG_SAVE_BMP = 22;
export const NATIVE_IMG_RESIZE   = 23;

export const NATIVE_FONT_LOAD    = 24;
export const NATIVE_FONT_GLYPH   = 25;
export const NATIVE_FONT_METRICS = 26;
export const NATIVE_FONT_FREE    = 27;

export const NATIVE_AUDIO_INIT    = 28;
export const NATIVE_AUDIO_QUIT    = 29;
export const NATIVE_AUDIO_PLAY    = 30;
export const NATIVE_AUDIO_PAUSE   = 31;
export const NATIVE_AUDIO_RESUME  = 32;
export const NATIVE_AUDIO_STOP    = 33;
export const NATIVE_AUDIO_VOLUME  = 34;
export const NATIVE_AUDIO_PLAYING = 35;

export const NATIVE_PHYS_SPACE       = 36;
export const NATIVE_PHYS_GRAVITY     = 37;
export const NATIVE_PHYS_STEP        = 38;
export const NATIVE_PHYS_BODY        = 39;
export const NATIVE_PHYS_BODY_STATIC = 40;
export const NATIVE_PHYS_POS         = 41;
export const NATIVE_PHYS_VEL         = 42;
export const NATIVE_PHYS_SET_POS     = 43;
export const NATIVE_PHYS_SET_VEL     = 44;
export const NATIVE_PHYS_ANGLE       = 45;
export const NATIVE_PHYS_SET_ANGLE   = 46;
export const NATIVE_PHYS_FORCE       = 47;
export const NATIVE_PHYS_IMPULSE     = 48;
export const NATIVE_PHYS_CIRCLE      = 49;
export const NATIVE_PHYS_BOX         = 50;
export const NATIVE_PHYS_SEGMENT     = 51;
export const NATIVE_PHYS_ELASTICITY  = 52;
export const NATIVE_PHYS_FRICTION    = 53;
export const NATIVE_PHYS_COLLIDE     = 54;
export const NATIVE_PHYS_FREE_SHAPE  = 55;
export const NATIVE_PHYS_FREE_BODY   = 56;
export const NATIVE_PHYS_FREE_SPACE  = 57;

export const NATIVE_WIN_OPEN      = 58;
export const NATIVE_WIN_CLOSE     = 59;
export const NATIVE_WIN_COLOR     = 60;
export const NATIVE_WIN_CLEAR     = 61;
export const NATIVE_WIN_RECT      = 62;
export const NATIVE_WIN_LINE      = 63;
export const NATIVE_WIN_CIRCLE    = 64;
export const NATIVE_WIN_TEXT      = 65;
export const NATIVE_TEX_LOAD      = 66;
export const NATIVE_TEX_DRAW      = 67;
export const NATIVE_TEX_FREE      = 68;
export const NATIVE_WIN_SHOW      = 69;
export const NATIVE_WIN_POLL      = 70;
export const NATIVE_WIN_KEY       = 71;
export const NATIVE_WIN_MOUSE     = 72;
export const NATIVE_WIN_MOUSEDOWN = 73;
export const NATIVE_WIN_TIME      = 74;
export const NATIVE_WIN_DELAY     = 75;

export const NATIVE_PDF_OPEN       = 76;
export const NATIVE_PDF_NEW        = 77;
export const NATIVE_PDF_PAGES      = 78;
export const NATIVE_PDF_PAGE_SIZE  = 79;
export const NATIVE_PDF_TEXT       = 80;
export const NATIVE_PDF_FONT       = 81;
export const NATIVE_PDF_PAGE_BEGIN = 82;
export const NATIVE_PDF_COLOR      = 83;
export const NATIVE_PDF_WRITE_RECT = 84;
export const NATIVE_PDF_WRITE_LINE = 85;
export const NATIVE_PDF_WRITE_TEXT = 86;
export const NATIVE_PDF_CLOSE      = 87;

const nativeNames = new Map([
	["print", NATIVE_PRINT],
	["println", NATIVE_PRINTLN],
	["typeof", NATIVE_TYPEOF],
	["text_color", NATIVE_SET_COLOR_TEXT],
	["text_type", NATIVE_SET_TYPE_TEXT],
	["bg_color", NATIVE_SET_COLOR_BACK],
	["reset_color", NATIVE_RESET_COLOR],
	["scan", NATIVE_SCAN],
	["array_len", NATIVE_ARRAY_LEN],
	["array_push", NATIVE_ARRAY_PUSH],
	["init_window", NATIVE_INIT_WINDOW],
	["clear_screen", NATIVE_CLEAR_SCREEN],
	["draw_rect", NATIVE_DRAW_RECT],
	["file_read", NATIVE_FILE_READ],
	["file_write", NATIVE_FILE_WRITE],
	["file_append", NATIVE_FILE_APPEND],
	["file_exists", NATIVE_FILE_EXISTS],
	["file_delete", NATIVE_FILE_DELETE],
	["img_load", NATIVE_IMG_LOAD],
	["img_info", NATIVE_IMG_INFO],
	["img_save_png", NATIVE_IMG_SAVE_PNG],
	["img_save_jpg", NATIVE_IMG_SAVE_JPG],
	["img_save_bmp", NATIVE_IMG_SAVE_BMP],
	["img_resize", NATIVE_IMG_RESIZE],
	["font_load", NATIVE_FONT_LOAD],
	["font_glyph", NATIVE_FONT_GLYPH],
	["font_metrics", NATIVE_FONT_METRICS],
	["font_free", NATIVE_FONT_FREE],
	["audio_init", NATIVE_AUDIO_INIT],
	["audio_quit", NATIVE_AUDIO_QUIT],
	["audio_play", NATIVE_AUDIO_PLAY],
	["audio_pause", NATIVE_AUDIO_PAUSE],
	["audio_resume", NATIVE_AUDIO_RESUME],
	["audio_stop", NATIVE_AUDIO_STOP],
	["audio_volume", NATIVE_AUDIO_VOLUME],
	["audio_playing", NATIVE_AUDIO_PLAYING],
	["phys_space", NATIVE_PHYS_SPACE],
	["phys_gravity", NATIVE_PHYS_GRAVITY],
	["phys_step", NATIVE_PHYS_STEP],
	["phys_body", NATIVE_PHYS_BODY],
	["phys_body_static", NATIVE_PHYS_BODY_STATIC],
	["phys_pos", NATIVE_PHYS_POS],
	["phys_vel", NATIVE_PHYS_VEL],
	["phys_set_pos", NATIVE_PHYS_SET_POS],
	["phys_set_vel", NATIVE_PHYS_SET_VEL],
	["phys_angle", NATIVE_PHYS_ANGLE],
	["phys_set_angle", NATIVE_PHYS_SET_ANGLE],
	["phys_force", NATIVE_PHYS_FORCE],
	["phys_impulse", NATIVE_PHYS_IMPULSE],
	["phys_circle", NATIVE_PHYS_CIRCLE],
	["phys_box", NATIVE_PHYS_BOX],
	["phys_segment", NATIVE_PHYS_SEGMENT],
	["phys_elasticity", NATIVE_PHYS_ELASTICITY],
	["phys_friction", NATIVE_PHYS_FRICTION],
	["phys_collide", NATIVE_PHYS_COLLIDE],
	["phys_free_shape", NATIVE_PHYS_FREE_SHAPE],
	["phys_free_body", NATIVE_PHYS_FREE_BODY],
	["phys_free_space", NATIVE_PHYS_FREE_SPACE],
	["win_open", NATIVE_WIN_OPEN],
	["win_close", NATIVE_WIN_CLOSE],
	["win_color", NATIVE_WIN_COLOR],
	["win_clear", NATIVE_WIN_CLEAR],
	["win_rect", NATIVE_WIN_RECT],
	["win_line", NATIVE_WIN_LINE],
	["win_circle", NATIVE_WIN_CIRCLE],
	["win_text", NATIVE_WIN_TEXT],
	["tex_load", NATIVE_TEX_LOAD],
	["tex_draw", NATIVE_TEX_DRAW],
	["tex_free", NATIVE_TEX_FREE],
	["win_show", NATIVE_WIN_SHOW],
	["win_poll", NATIVE_WIN_POLL],
	["win_key", NATIVE_WIN_KEY],
	["win_mouse", NATIVE_WIN_MOUSE],
	["win_mousedown", NATIVE_WIN_MOUSEDOWN],
	["win_time", NATIVE_WIN_TIME],
	["win_delay", NATIVE_WIN_DELAY],
	["pdf_open", NATIVE_PDF_OPEN],
	["pdf_new", NATIVE_PDF_NEW],
	["pdf_pages", NATIVE_PDF_PAGES],
	["pdf_page_size", NATIVE_PDF_PAGE_SIZE],
	["pdf_text", NATIVE_PDF_TEXT],
	["pdf_font", NATIVE_PDF_FONT],
	["pdf_page_begin", NATIVE_PDF_PAGE_BEGIN],
	["pdf_color", NATIVE_PDF_COLOR],
	["pdf_write_rect", NATIVE_PDF_WRITE_RECT],
	["pdf_write_line", NATIVE_PDF_WRITE_LINE],
	["pdf_write_text", NATIVE_PDF_WRITE_TEXT],
	["pdf_close", NATIVE_PDF_CLOSE]
]);

// ==========================================
// EMITTER
// ==========================================
export class Emitter {
	constructor() {
		this.code = [];
		this.caps = [];
	}

	cur() {
		if (this.caps.length > 0) {
			return this.caps[this.caps.length - 1];
		}
		return this.code;
	}

	emit(b) {
		this.cur().push(b & 0xFF);
	}

	emit16(v) {
		this.emit(v & 0xFF);
		this.emit((v >> 8) & 0xFF);
	}

	emitName(name) {
		const buf = Buffer.from(name, 'utf8');
		this.emit16(buf.length);
		for (let b of buf) {
			this.emit(b);
		}
	}

	emitI16(v) {
		this.emit(v & 0xFF);
		this.emit((v >> 8) & 0xFF);
	}

	patchI16(off, val) {
		const buf = this.cur();
		buf[off] = val & 0xFF;
		buf[off + 1] = (val >> 8) & 0xFF;
	}

	pos() {
		return this.cur().length;
	}

	pushBool(val) {
		this.emit(OP_PUSH);
		this.emit(TYPE_BOOL);
		this.emit(val ? 1 : 0);
	}

	pushChar(val) {
		this.emit(OP_PUSH);
		this.emit(TYPE_CHAR);
		this.emit(val);
	}

	pushFunc(offset, paramCount) {
		this.emit(OP_PUSH);
		this.emit(TYPE_FUNC);
		this.emit16(offset);
		this.emit(paramCount);
	}

	pushString(val) {
		this.emit(OP_PUSH);
		this.emit(TYPE_STRING);
		const inner = val.slice(1, -1);
		const buf = Buffer.from(inner, 'utf8');
		this.emit16(buf.length);
		for (let b of buf) {
			this.emit(b);
		}
		this.emit(0);
	}

	pushScaled(typ, val) {
		let neg = false;
		let s = val;
		if (s.startsWith("+")) {
			s = s.slice(1);
		} else if (s.startsWith("-")) {
			neg = true;
			s = s.slice(1);
		}

		const parts = s.split(".", 2);
		const intPart = parts[0];
		const fracPart = parts.length > 1 ? parts[1] : "";

		let digits = intPart + fracPart;
		if (!digits) digits = "0";

		let num = BigInt(digits);
		if (neg) num = -num;

		this.emit(OP_PUSH);
		this.emit(typ);
		this.emit(fracPart.length & 0xFF);
		const v16 = Number(num & 0xFFFFn);
		this.emit(v16 & 0xFF);
		this.emit((v16 >> 8) & 0xFF);
	}

	pushInt(val) { this.pushScaled(TYPE_INT, val); }
	pushDec(val) { this.pushScaled(TYPE_PKDEC, val); }

	pushColor(hex) {
		let r = 0, g = 0, b = 0, a = 255;
		const h = hex.replace(/^#/, "");
		if (h.length >= 6) {
			r = parseInt(h.slice(0, 2), 16) || 0;
			g = parseInt(h.slice(2, 4), 16) || 0;
			b = parseInt(h.slice(4, 6), 16) || 0;
			if (h.length >= 8) {
				a = parseInt(h.slice(6, 8), 16) || 0;
			}
		}
		this.emit(OP_PUSH);
		this.emit(TYPE_COLOR);
		this.emit(r);
		this.emit(g);
		this.emit(b);
		this.emit(a);
	}

	emitRaw16(val, signo) {
		val = BigInt(val);
		signo = BigInt(signo);
		const pow4 = [1n, 4n, 16n, 64n, 256n, 1024n];
		const pow10 = [1n, 10n, 100n];

		let bc = val, p = 0n, s = 0n, ok = false;

		for (let si = 0n; si <= 2n && !ok; si++) {
			for (let pi = 5n; ; pi--) {
				const num = val * pow4[Number(pi)];
				if (num % pow10[Number(si)] === 0n) {
					const b = num / pow10[Number(si)];
					if (b >= 1n && b <= 1023n) {
						bc = b; p = pi; s = si; ok = true;
						break;
					}
				}
				if (pi === 0n) break;
			}
		}

		if (!ok) {
			let bestErr = 1n << 62n;
			for (let si = 0n; si <= 2n; si++) {
				for (let pi = 0n; pi <= 5n; pi++) {
					const num = val * pow4[Number(pi)];
					const den = pow10[Number(si)];
					const q = num / den;
					const r = num % den;
					if (q < 1n || q > 1023n) continue;

					let err = r;
					if (den - r < err) err = den - r;

					const l = err * pow10[Number(s)];
					const rr = bestErr * pow10[Number(si)];
					if (l < rr || (l === rr && q > bc)) {
						bestErr = err; bc = q; p = pi; s = si;
					}
				}
			}
		}

		const raw = Number((p << 13n) | (bc << 3n) | ((s + 1n) << 1n) | signo);
		this.emit(raw & 0xFF);
		this.emit((raw >> 8) & 0xFF);
	}

	pushNum16(val) {
		this.emit(OP_PUSH);
		this.emit(TYPE_NUM16);
		this.emitRaw16(val, 0);
	}

	pushNum16Signed(val) {
		this.emit(OP_PUSH);
		this.emit(TYPE_NUM16);
		let signo = 0;
		if (val < 0) {
			signo = 1;
			val = -val;
		}
		this.emitRaw16(val, signo);
	}

	pushNum64(val) {
		this.emit(OP_PUSH);
		this.emit(TYPE_NUM64);
		const p = 0n, signo = 0n;
		let exp = 127n;
		let bc = BigInt(val);
		while (bc > 1125899906842623n) {
			bc /= 10n;
			exp++;
		}
		const raw = (p << 59n) | (bc << 9n) | (exp << 1n) | signo;
		for (let i = 0n; i < 8n; i++) {
			this.emit(Number((raw >> (i * 8n)) & 0xFFn));
		}
	}

	pushNum64Signed(val) {
		this.emit(OP_PUSH);
		this.emit(TYPE_NUM64);
		const p = 0n;
		let signo = 0n;
		if (val < 0n) {
			signo = 1n;
			val = -val;
		}
		let exp = 127n;
		let bc = BigInt(val);
		while (bc > 1125899906842623n) {
			bc /= 10n;
			exp++;
		}
		const raw = (p << 59n) | (bc << 9n) | (exp << 1n) | signo;
		for (let i = 0n; i < 8n; i++) {
			this.emit(Number((raw >> (i * 8n)) & 0xFFn));
		}
	}

	pushNum64Float(val) {
		this.emit(OP_PUSH);
		this.emit(TYPE_NUM64);
		let signo = 0n;
		if (val < 0) {
			signo = 1n;
			val = -val;
		}
		let exp = 127n;
		const fracDigits = 4;
		let bcFloat = val;
		for (let i = 0; i < fracDigits; i++) {
			bcFloat *= 10.0;
		}
		let bc = BigInt(Math.floor(bcFloat));
		while (bc > 1125899906842623n) {
			bc /= 10n;
			exp++;
		}
		const raw = (BigInt(fracDigits) << 59n) | (bc << 9n) | (exp << 1n) | signo;
		for (let i = 0n; i < 8n; i++) {
			this.emit(Number((raw >> (i * 8n)) & 0xFFn));
		}
	}

	pushComplex(re, im) {
		this.emit(OP_PUSH);
		this.emit(TYPE_COMPLEX);
		const reV = parseFloat(re) || 0;
		const imV = parseFloat(im) || 0;
		for (let b of rawNum64(reV)) this.emit(b);
		for (let b of rawNum64(imV)) this.emit(b);
	}
}

function rawNum64(val) {
	const raw = new Uint8Array(8);
	let signo = 0n;
	if (val < 0) {
		signo = 1n;
		val = -val;
	}
	let exp = 127n;
	const fracDigits = 4;
	let bcFloat = val;
	for (let i = 0; i < fracDigits; i++) bcFloat *= 10.0;
	let bc = BigInt(Math.floor(bcFloat));
	while (bc > 1125899906842623n) {
		bc /= 10n;
		exp++;
	}
	const r = (BigInt(fracDigits) << 59n) | (bc << 9n) | (exp << 1n) | signo;
	for (let i = 0; i < 8; i++) {
		raw[i] = Number((r >> BigInt(i * 8)) & 0xFFn);
	}
	return raw;
}

function parseComplexLiteral(text) {
	const s = text.endsWith("i") ? text.slice(0, -1) : text;
	let lastSign = -1;
	for (let i = s.length - 1; i >= 0; i--) {
		if (s[i] === '+' || s[i] === '-') {
			lastSign = i;
			break;
		}
	}
	if (lastSign < 0) return ["0", "0"];
	let im = s.slice(lastSign);
	if (!im || im === "+" || im === "-") return ["0", "0"];
	let re = s.slice(0, lastSign);
	if (!re) re = "0";
	return [re, im];
}

function childTokText(ctx, idx) {
	if (!ctx || idx >= ctx.getChildCount()) return "";
	const child = ctx.getChild(idx);
	return child ? child.getText() : "";
}

function caseBlockOf(mc) {
	if (mc.block && typeof mc.block === 'function') {
		return mc.block();
	}
	return null;
}

// ==========================================
// CODE GENERATOR
// ==========================================
export class CodeGen extends PaxoListener {
	constructor() {
		super();
		this.emitter = new Emitter();
		this.locals = new Map();
		this.nextLocal = 0;
		this.errors = [];
		this.warnings = [];

		this.varTypes = new Map();
		this.funcVarTypes = new Map();

		this.inFunction = false;
		this.savedCode = null;
		this.funcBodies = [];
		this.funcPatchPositions = [];
		this.funcParamCounts = [];

		this.funcLocals = new Map();
		this.funcNextLocal = 0;
		this.savedFuncLocals = null;
		this.savedFuncNext = 0;

		this.conds = [];
		this.caseOwner = new Map();

		this.loops = [];
		this.pendingLoopBody = false;

		this.inPkg = false;
		this.pkgFields = [];

		this.inTryCatch = false;
		this.tryBlockCount = 0;
		this.tryCatchVarIdx = 0;
		this.catchOffsetPatch = 0;
		this.tryCatchEndPatch = 0;
	}

	reportError(msg) { this.errors.push(msg); }
	reportWarning(msg) { this.warnings.push(msg); }

	resolveIdent(name) {
		if (this.inFunction && this.funcLocals.has(name)) {
			return { idx: this.funcLocals.get(name), isLocal: true, found: true };
		}
		if (this.locals.has(name)) {
			return { idx: this.locals.get(name), isLocal: false, found: true };
		}
		return { idx: 0, isLocal: false, found: false };
	}

	resolveType(token) {
		switch (token) {
			case "var": case "📥": return TYPE_NUM64;
			case "sn": return TYPE_NUM16;
			case "n": return TYPE_NUM64;
			case "abc": return TYPE_CHAR;
			case "trit": return TYPE_TRIT;
			case "bool": return TYPE_BOOL;
			case "pin": return TYPE_POINT;
			case "fx": return TYPE_FUNC;
			case "pkg": case "📦": return TYPE_PKG;
			case "int": return TYPE_INT;
			case "pdec":
				this.reportWarning("el tipo 'pdec' (decimal empaquetado) está deprecado: " +
					"ya no garantiza números únicos sin error y quedará sin soporte. " +
					"Usa 'n' (mobile point) o 'var' en su lugar");
				return TYPE_PKDEC;
			case "col": return TYPE_COLOR;
			case "ni": return TYPE_COMPLEX;
			case "sni": return TYPE_COMPLEX16;
			default:
				this.reportError("tipo desconocido: " + token);
				return TYPE_NUM64;
		}
	}

	walkTree(tree) {
		antlr4.tree.ParseTreeWalker.DEFAULT.walk(this, tree);
	}

	exitProgram(ctx) {
		this.emitter.emit(OP_HALT);

		const funcStart = this.emitter.code.length;
		const offsets = new Array(this.funcBodies.length);
		let running = funcStart;

		for (let i = 0; i < this.funcBodies.length; i++) {
			offsets[i] = running;
			this.emitter.code.push(...this.funcBodies[i]);
			running += this.funcBodies[i].length;
		}

		for (let i = 0; i < this.funcPatchPositions.length; i++) {
			const pos = this.funcPatchPositions[i];
			const offset = offsets[i];
			this.emitter.code[pos] = offset & 0xFF;
			this.emitter.code[pos + 1] = (offset >> 8) & 0xFF;
		}
	}

	exitVarDeclaration(ctx) {
		const name = ctx.IDENTIFIER().getText();

		if (this.inPkg) {
			let privateField = false;
			const sc = ctx.scope ? ctx.scope() : null;
			if (sc && sc.start.text === "local") {
				privateField = true;
			}
			this.pkgFields.push({ name, private: privateField });
			return;
		}

		const sc = ctx.scope ? ctx.scope() : null;
		if (sc) {
			const token = sc.start.text;
			let msg = `línea ${sc.start.line}: el modificador de scope '${token}' está deprecado y se ignora`;
			if (ctx.type_ && ctx.type_()) {
				msg = `línea ${sc.start.line}: el modificador de scope '${token}' está deprecado; escríbelo como '${ctx.type_().getText()} ${name}'`;
			}
			this.reportWarning(msg);
		}

		let varType = TYPE_NUM64;
		let isDynamic = true;
		if (ctx.type_ && ctx.type_()) {
			const token = ctx.type_().start.text;
			varType = this.resolveType(token);
			isDynamic = (token === "var" || token === "📥");
		}

		let idx = 0;
		let storeOp = OP_STORE_VAR;

		if (this.inFunction) {
			idx = this.funcNextLocal++;
			this.funcLocals.set(name, idx);
			storeOp = OP_STORE_LOCAL;
			if (!isDynamic) this.funcVarTypes.set(name, varType);
		} else {
			idx = this.nextLocal++;
			this.locals.set(name, idx);
			storeOp = OP_STORE_VAR;
			if (!isDynamic) this.varTypes.set(name, varType);
		}

		if (ctx.expression && ctx.expression()) {
			if (ctx.type_ && ctx.type_()) {
				const token = ctx.type_().start.text;
				if (token !== "var" && token !== "📥") {
					this.emitter.emit(OP_CAST);
					this.emitter.emit(varType);
				}
			}
			this.emitter.emit(storeOp);
			this.emitter.emit16(idx);
		} else if (ctx.arrayLiteral && ctx.arrayLiteral()) {
			this.emitArrayLiteral(ctx.arrayLiteral());
			this.emitter.emit(storeOp);
			this.emitter.emit16(idx);
		} else {
			switch (varType) {
				case TYPE_NUM16: this.emitter.pushNum16(0); break;
				case TYPE_NUM64: this.emitter.pushNum64(0); break;
				case TYPE_BOOL: this.emitter.pushBool(false); break;
				case TYPE_CHAR: this.emitter.pushChar(0); break;
				case TYPE_FUNC: this.emitter.pushFunc(0, 0); break;
				case TYPE_INT: this.emitter.pushInt("0"); break;
				case TYPE_PKDEC: this.emitter.pushDec("0.0"); break;
				case TYPE_COLOR: this.emitter.pushColor("#00000000"); break;
				case TYPE_COMPLEX: this.emitter.pushComplex("0", "0"); break;
				case TYPE_COMPLEX16:
					this.emitter.emit(OP_PUSH);
					this.emitter.emit(TYPE_COMPLEX16);
					this.emitter.emit16(0);
					this.emitter.emit16(0);
					break;
				default: this.emitter.pushNum64(0); break;
			}
			this.emitter.emit(storeOp);
			this.emitter.emit16(idx);
		}
	}

	enterAssignment(ctx) {
		if (childTokText(ctx, 1) === ".") {
			if (ctx.THIS_SCOPE && ctx.THIS_SCOPE()) {
				if (!this.funcLocals.has("this")) {
					this.reportError("this solo está disponible dentro de un método de package");
					return;
				}
				const idx = this.funcLocals.get("this");
				this.emitter.emit(OP_LOAD_LOCAL);
				this.emitter.emit16(idx);
			}
			return;
		}
		const exprs = ctx.expression ? ctx.expression() : [];
		if (exprs.length === 2) {
			const name = ctx.IDENTIFIER().getText();
			const { idx, isLocal, found } = this.resolveIdent(name);
			if (!found) {
				this.reportError("variable no declarada: " + name);
				return;
			}
			this.emitter.emit(isLocal ? OP_LOAD_LOCAL : OP_LOAD_VAR);
			this.emitter.emit16(idx);
		}
	}

	exitAssignment(ctx) {
		if (childTokText(ctx, 1) === ".") {
			const fieldName = ctx.IDENTIFIER().getText();
			if (ctx.THIS_SCOPE && ctx.THIS_SCOPE()) {
				this.emitter.emit(OP_THIS_SET);
			} else {
				this.emitter.emit(OP_PKG_SET);
			}
			this.emitter.emitName(fieldName);
			return;
		}

		const name = ctx.IDENTIFIER().getText();
		const { idx, isLocal, found } = this.resolveIdent(name);
		if (!found) {
			this.reportError("variable no declarada: " + name);
			return;
		}

		const storeOp = isLocal ? OP_STORE_LOCAL : OP_STORE_VAR;
		const loadOp = isLocal ? OP_LOAD_LOCAL : OP_LOAD_VAR;
		const exprs = ctx.expression ? (Array.isArray(ctx.expression()) ? ctx.expression() : [ctx.expression()]) : [];

		if (exprs.length === 2) {
			this.emitter.emit(OP_ARRAY_SET);
		} else if (exprs.length === 1) {
			const typeMap = isLocal ? this.funcVarTypes : this.varTypes;
			if (typeMap.has(name)) {
				this.emitter.emit(OP_CAST);
				this.emitter.emit(typeMap.get(name));
			}
			this.emitter.emit(storeOp);
			this.emitter.emit16(idx);
		} else {
			this.emitter.emit(loadOp);
			this.emitter.emit16(idx);
			if (childTokText(ctx, 1) === "++") {
				this.emitter.emit(OP_INC);
			} else {
				this.emitter.emit(OP_DEC);
			}
			this.emitter.emit(storeOp);
			this.emitter.emit16(idx);
		}
	}

	enterCondStatement(ctx) {
		const f = { start: this.emitter.pos(), tmpVar: 0, localTmp: false, blocks: [] };
		if (this.inFunction) {
			f.tmpVar = this.funcNextLocal++;
			f.localTmp = true;
		} else {
			f.tmpVar = this.nextLocal++;
		}

		const cases = ctx.matchCase ? ctx.matchCase() : [];
		for (let mc of cases) {
			const blk = caseBlockOf(mc);
			if (blk) this.caseOwner.set(blk, f);
		}
		this.conds.push(f);
	}

	exitCondStatement(ctx) {
		if (this.conds.length === 0) return;
		const f = this.conds.pop();
		const cases = ctx.matchCase ? ctx.matchCase() : [];
		for (let mc of cases) {
			const blk = caseBlockOf(mc);
			if (blk) this.caseOwner.delete(blk);
		}

		const out = this.emitter.cur();
		out.length = f.start;

		this.walkTree(ctx.expression());
		this.emitter.emit(f.localTmp ? OP_STORE_LOCAL : OP_STORE_VAR);
		this.emitter.emit16(f.tmpVar);

		const endPatches = [];

		for (let i = 0; i < cases.length; i++) {
			if (i >= f.blocks.length) break;
			const mc = cases[i];
			if (childTokText(mc, 0) === "_") {
				this.emitter.cur().push(...f.blocks[i]);
				continue;
			}
			this.emitter.emit(f.localTmp ? OP_LOAD_LOCAL : OP_LOAD_VAR);
			this.emitter.emit16(f.tmpVar);
			this.walkTree(mc.expression());
			this.emitter.emit(OP_EQ);
			this.emitter.emit(OP_JUMP_IF_FALSE);
			const skipPatch = this.emitter.pos();
			this.emitter.emitI16(0);

			this.emitter.cur().push(...f.blocks[i]);
			this.emitter.emit(OP_JUMP);
			const endPatch = this.emitter.pos();
			this.emitter.emitI16(0);

			this.emitter.patchI16(skipPatch, this.emitter.pos() - skipPatch - 2);
			endPatches.push(endPatch);
		}

		for (let ep of endPatches) {
			this.emitter.patchI16(ep, this.emitter.pos() - ep - 2);
		}

		if (f.localTmp) this.funcNextLocal--;
		else this.nextLocal--;
	}

	enterLoopStatement(ctx) {
		if (ctx.loopDelimiter && ctx.loopDelimiter()) {
			const tok = ctx.loopDelimiter().start;
			this.reportWarning(`línea ${tok.line}: el delimitador de bucle '${tok.text}' está deprecado; usa el nuevo formato de bloque`);
		}
		this.loops.push({ condStart: this.emitter.pos(), jifEnd: 0, bodyBlock: null });
		this.pendingLoopBody = true;
	}

	exitLoopStatement(ctx) {
		if (this.loops.length > 0 && !this.pendingLoopBody) return;
		if (this.loops.length > 0) this.loops.pop();
		this.pendingLoopBody = false;
	}

	exitEveryRule(ctx) {
		if (ctx instanceof PaxoParser.ExpressionContext) {
			this.handleBaseExpression(ctx);
		}
	}

	handleBaseExpression(ctx) {
		if (ctx instanceof PaxoParser.IntLitExprContext) {
			const text = ctx.INT_LITERAL().getText();
			const val = BigInt(text);
			if (val < 0n) this.emitter.pushNum64Signed(val);
			else this.emitter.pushNum64(val);
		} else if (ctx instanceof PaxoParser.DecLitExprContext) {
			const text = ctx.DECIMAL_LITERAL().getText();
			const val = parseFloat(text);
			this.emitter.pushNum64Float(isNaN(val) ? 0 : val);
		} else if (ctx instanceof PaxoParser.CharLitExprContext) {
			const text = ctx.CHAR_LITERAL().getText();
			this.emitter.pushChar(text.length >= 3 ? text.charCodeAt(1) : 0);
		} else if (ctx instanceof PaxoParser.BoolBitExprContext) {
			this.emitter.pushBool(ctx.BOOLEAN_BIT().getText() === ".✓");
		} else if (ctx instanceof PaxoParser.BoolTritExprContext) {
			const text = ctx.BOOLEAN_TRIT().getText();
			this.emitter.emit(OP_PUSH);
			this.emitter.emit(TYPE_TRIT);
			if (text === "•") this.emitter.emit(1);
			else if (text === "✓") this.emitter.emit(2);
			else this.emitter.emit(0);
		} else if (ctx instanceof PaxoParser.ColLitExprContext) {
			this.emitter.pushColor(ctx.COLOR_LITERAL().getText());
		} else if (ctx instanceof PaxoParser.ComLitExprContext) {
			const [re, im] = parseComplexLiteral(ctx.COMPLEX_LITERAL().getText());
			this.emitter.pushComplex(re, im);
		} else if (ctx instanceof PaxoParser.StringLitExprContext) {
			this.emitter.pushString(ctx.STRING_LITERAL().getText());
		} else if (ctx instanceof PaxoParser.IdentExprContext) {
			const name = ctx.IDENTIFIER().getText();
			const { idx, isLocal, found } = this.resolveIdent(name);
			if (!found) {
				this.reportError("variable no declarada: " + name);
				return;
			}
			this.emitter.emit(isLocal ? OP_LOAD_LOCAL : OP_LOAD_VAR);
			this.emitter.emit16(idx);
		} else if (ctx instanceof PaxoParser.PtrLitExprContext) {
			const text = ctx.POINTER_LITERAL().getText();
			const name = text.slice(1);
			const { idx, found } = this.resolveIdent(name);
			if (!found) {
				this.reportError("variable no declarada para puntero: " + name);
				return;
			}
			this.emitter.emit(OP_PUSH);
			this.emitter.emit(TYPE_POINT);
			const ptr = BigInt(idx);
			for (let i = 0n; i < 8n; i++) {
				this.emitter.emit(Number((ptr >> (i * 8n)) & 0xFFn));
			}
		} else if (ctx instanceof PaxoParser.ArrayLitExprContext) {
			this.emitArrayLiteral(ctx.arrayLiteral());
		} else if (ctx instanceof PaxoParser.IndexedAccessExprContext) {
			this.emitter.emit(OP_ARRAY_GET);
		} else if (ctx instanceof PaxoParser.DotAccessExprContext) {
			this.emitter.emitDotAccess(ctx);
		} else if (ctx instanceof PaxoParser.PkgExprContext) {
			this.emitPackage(ctx.pkgDeclaration());
		} else if (ctx instanceof PaxoParser.ThisScopeExprContext) {
			if (!this.funcLocals.has("this")) {
				this.reportError("this solo está disponible dentro de un método de package");
				return;
			}
			const fieldName = ctx.IDENTIFIER().getText();
			this.emitter.emit(OP_THIS_GET);
			this.emitter.emitName(fieldName);
		} else if (ctx instanceof PaxoParser.IndexedCallExprContext) {
			const al = ctx.argumentList ? ctx.argumentList() : null;
			const argc = al ? (al.expression ? al.expression().length : 0) : 0;
			this.emitter.emit(OP_CALL_VAR);
			this.emitter.emit(argc & 0xFF);
		} else if (ctx instanceof PaxoParser.MethodCallExprContext) {
			const al = ctx.argumentList ? ctx.argumentList() : null;
			const argc = al ? (al.expression ? al.expression().length : 0) : 0;
			this.emitter.emit(OP_CALL_METHOD);
			this.emitter.emit(argc & 0xFF);
		}
	}

	enterArgumentList(ctx) {
		const parent = ctx.parentCtx;
		if (parent instanceof PaxoParser.IndexedCallExprContext) {
			this.emitter.emit(OP_ARRAY_GET);
		} else if (parent instanceof PaxoParser.MethodCallExprContext) {
			const fieldName = parent.IDENTIFIER().getText();
			this.emitter.emit(OP_PKG_GET);
			this.emitter.emitName(fieldName);
		}
	}

	exitAddSubExpr(ctx) {
		const op = childTokText(ctx, 1);
		if (op === "+") this.emitter.emit(OP_ADD);
		else if (op === "-") this.emitter.emit(OP_SUB);
	}

	exitMultDivExpr(ctx) {
		const op = childTokText(ctx, 1);
		if (op === "×") this.emitter.emit(OP_MUL);
		else if (op === "÷") this.emitter.emit(OP_DIV);
	}

	exitRelationalExpr(ctx) {
		switch (childTokText(ctx, 1)) {
			case "==": this.emitter.emit(OP_EQ); break;
			case "≠": case "!=": this.emitter.emit(OP_NEQ); break;
			case "<": this.emitter.emit(OP_LT); break;
			case ">": this.emitter.emit(OP_GT); break;
			case "≤": case "<=": this.emitter.emit(OP_LTE); break;
			case "≥": case ">=": this.emitter.emit(OP_GTE); break;
		}
	}

	exitBitwiseExpr(ctx) {
		switch (childTokText(ctx, 1)) {
			case "&": this.emitter.emit(OP_BIT_AND); break;
			case "|": this.emitter.emit(OP_BIT_OR); break;
			case ".&": this.emitter.emit(OP_AND); break;
			case ".|": this.emitter.emit(OP_OR); break;
		}
	}

	exitShiftExpr(ctx) {
		const op = childTokText(ctx, 1);
		if (op === "•«") this.emitter.emit(OP_BIT_SHL);
		else if (op === "»•") this.emitter.emit(OP_BIT_SHR);
	}

	exitNotgateExpr(ctx) {
		const op = childTokText(ctx, 0);
		if (op === ".!" || op === "!.!") this.emitter.emit(OP_BIT_NOT);
		else this.emitter.emit(OP_NOT);
	}

	exitCallExpr(ctx) {
		const name = ctx.IDENTIFIER().getText();
		const al = ctx.argumentList ? ctx.argumentList() : null;
		const argCount = al ? (al.expression ? al.expression().length : 0) : 0;

		if (nativeNames.has(name)) {
			this.emitter.emit(OP_CALL_NATIVE);
			this.emitter.emit16(nativeNames.get(name));
			this.emitter.emit(argCount & 0xFF);
			return;
		}

		if (!this.locals.has(name)) {
			this.reportError("función no definida: " + name);
			return;
		}

		const idx = this.locals.get(name);
		this.emitter.emit(OP_LOAD_VAR);
		this.emitter.emit16(idx);
		this.emitter.emit(OP_CALL_VAR);
		this.emitter.emit(argCount & 0xFF);
	}

	enterBlock(ctx) {
		if (this.inTryCatch) {
			if (this.tryBlockCount === 1) {
				this.emitter.emit(OP_TRY_END);
				this.tryCatchEndPatch = this.emitter.pos();
				this.emitter.emitI16(0);
				this.emitter.emit(OP_STORE_VAR);
				this.emitter.emit16(this.tryCatchVarIdx);
			}
			return;
		}

		if (this.caseOwner.has(ctx)) {
			this.emitter.caps.push([]);
			return;
		}

		if (this.pendingLoopBody) {
			const f = this.loops[this.loops.length - 1];
			this.emitter.emit(OP_JUMP_IF_FALSE);
			f.jifEnd = this.emitter.pos();
			this.emitter.emitI16(0);
			f.bodyBlock = ctx;
			this.pendingLoopBody = false;
		}
	}

	exitBlock(ctx) {
		if (this.inTryCatch) {
			this.tryBlockCount++;
			return;
		}

		if (this.caseOwner.has(ctx)) {
			const f = this.caseOwner.get(ctx);
			f.blocks.push(this.emitter.caps.pop());
			return;
		}

		if (this.loops.length > 0 && this.loops[this.loops.length - 1].bodyBlock === ctx) {
			const f = this.loops.pop();
			this.emitter.emit(OP_JUMP);
			const back = f.condStart - (this.emitter.pos() + 2);
			this.emitter.emitI16(back);
			this.emitter.patchI16(f.jifEnd, this.emitter.pos() - f.jifEnd - 2);
		}
	}

	enterParameterList(ctx) {
		if (!this.inFunction) return;
		const ids = ctx.IDENTIFIER ? ctx.IDENTIFIER() : [];
		for (let id of ids) {
			this.funcLocals.set(id.getText(), this.funcNextLocal++);
		}
	}

	exitReturnStatement(ctx) {
		this.emitter.emit(OP_RETURN);
	}

	enterTryCatchStatement(ctx) {
		const catchVarName = ctx.IDENTIFIER(0).getText();
		const idx = this.nextLocal++;
		this.tryCatchVarIdx = idx;
		this.locals.set(catchVarName, idx);

		this.inTryCatch = true;
		this.tryBlockCount = 0;

		this.emitter.emit(OP_TRY_SETUP);
		this.catchOffsetPatch = this.emitter.pos();
		this.emitter.emitI16(0);
	}

	exitTryCatchStatement(ctx) {
		const catchTarget = this.tryCatchEndPatch + 2;
		this.emitter.patchI16(this.catchOffsetPatch, catchTarget - this.catchOffsetPatch - 2);
		this.emitter.patchI16(this.tryCatchEndPatch, this.emitter.pos() - this.tryCatchEndPatch - 2);

		this.inTryCatch = false;
		this.tryBlockCount = 0;
	}

	exitThrowStatement(ctx) {
		this.emitter.emit(OP_THROW);
	}

	enterFuncExpr(ctx) {
		this.savedCode = this.emitter.code;
		this.emitter.code = [];
		this.inFunction = true;

		this.savedFuncLocals = this.funcLocals;
		this.savedFuncNext = this.funcNextLocal;
		this.funcLocals = new Map();
		this.funcNextLocal = 0;

		if (this.inPkg) {
			this.funcLocals.set("this", 0);
			this.funcNextLocal = 1;
		}
	}

	exitFuncExpr(ctx) {
		this.emitter.emit(OP_RETURN);

		const funcBody = this.emitter.code;
		let paramCount = 0;
		if (ctx.functionDeclaration && ctx.functionDeclaration()) {
			const pl = ctx.functionDeclaration().parameterList ? ctx.functionDeclaration().parameterList() : null;
			if (pl && pl.IDENTIFIER) paramCount = pl.IDENTIFIER().length;
		}

		this.funcBodies.push(funcBody);
		this.funcParamCounts.push(paramCount);

		this.emitter.code = this.savedCode;
		this.inFunction = false;

		this.funcLocals = this.savedFuncLocals;
		this.funcNextLocal = this.savedFuncNext;

		this.emitter.emit(OP_PUSH);
		this.emitter.emit(TYPE_FUNC);
		this.funcPatchPositions.push(this.emitter.code.length);
		this.emitter.emit16(0);
		this.emitter.emit(paramCount & 0xFF);
	}

	emitArrayLiteral(ctx) {
		const exprs = ctx.expression ? ctx.expression() : [];
		this.emitter.emit(OP_ARRAY_NEW);
		this.emitter.emit16(exprs.length);
	}

	emitDotAccess(ctx) {
		const fieldName = ctx.IDENTIFIER().getText();
		this.emitter.emit(OP_PKG_GET);
		this.emitter.emitName(fieldName);
	}

	enterPkgExpr(ctx) {
		this.inPkg = true;
		this.pkgFields = [];
	}

	emitPackage(ctx) {
		this.inPkg = false;
		const fields = this.pkgFields;
		this.pkgFields = [];

		this.emitter.emit(OP_PKG_NEW);
		this.emitter.emit16(fields.length);

		for (let i = fields.length - 1; i >= 0; i--) {
			const f = fields[i];
			const buf = Buffer.from(f.name, 'utf8');
			this.emitter.emit16(buf.length);
			for (let b of buf) this.emitter.emit(b);
			this.emitter.emit(f.private ? 1 : 0);
		}
	}
}

export async function Compile(inputFile, outputFile, dump = false) {
	const content = fs.readFileSync(inputFile, 'utf8');
	const chars = new antlr4.InputStream(content);
	const lexer = new PaxoLexer(chars);
	const tokens = new antlr4.CommonTokenStream(lexer);
	const parser = new PaxoParser(tokens);
	const tree = parser.program();

	const cg = new CodeGen();
	antlr4.tree.ParseTreeWalker.DEFAULT.walk(cg, tree);

	for (let w of cg.warnings) {
		console.error(`Warning: ${w}`);
	}

	if (cg.errors.length > 0) {
		for (let e of cg.errors) {
			console.error(`Error: ${e}`);
		}
		throw new Error(`${cg.errors.length} errores de compilación`);
	}

	const codeBuf = Buffer.from(cg.emitter.code);
	fs.writeFileSync(outputFile, codeBuf);

	console.log(`Compilado: ${inputFile} → ${outputFile} (${codeBuf.length} bytes)`);

	if (dump) {
		console.log("\nBytecode hex dump:");
		for (let i = 0; i < codeBuf.length; i += 16) {
			const hex = [];
			const end = Math.min(i + 16, codeBuf.length);
			for (let j = i; j < end; j++) {
				hex.push(codeBuf[j].toString(16).padStart(2, '0').toUpperCase());
			}
			console.log(`  ${i.toString(16).padStart(4, '0').toUpperCase()}: ${hex.join(' ')}`);
		}
	}
}
