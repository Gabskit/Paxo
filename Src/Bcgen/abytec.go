package parser

import (
	"fmt"
	"os"
	"strconv"

	"github.com/antlr4-go/antlr/v4"
)

// ==========================================
// OPCODES — deben coincidir con Vm.c
// ==========================================
const (
	OP_PUSH          byte = 0
	OP_POP           byte = 1
	OP_ADD           byte = 2
	OP_SUB           byte = 3
	OP_MUL           byte = 4
	OP_DIV           byte = 5
	OP_CAST          byte = 6
	OP_LOAD_VAR      byte = 7
	OP_STORE_VAR     byte = 8
	OP_PRINT         byte = 9
	OP_JUMP          byte = 10
	OP_JUMP_IF_FALSE byte = 11
	OP_JUMP_IF_TRUE  byte = 12
	OP_HALT          byte = 13
	OP_CALL          byte = 14
	OP_CALL_NATIVE   byte = 15
	OP_EQ            byte = 16
	OP_NEQ           byte = 17
	OP_LT            byte = 18
	OP_GT            byte = 19
	OP_LTE           byte = 20
	OP_GTE           byte = 21
	OP_AND           byte = 22
	OP_OR            byte = 23
	OP_NOT           byte = 24
	OP_BIT_AND       byte = 25
	OP_BIT_OR        byte = 26
	OP_BIT_NOT       byte = 27
	OP_BIT_XOR       byte = 28
	OP_BIT_SHL       byte = 29
	OP_BIT_SHR       byte = 30
	OP_INC           byte = 31
	OP_DEC           byte = 32
	OP_RETURN        byte = 33
	OP_CALL_VAR      byte = 34
	OP_ARRAY_NEW     byte = 35
	OP_ARRAY_GET     byte = 36
	OP_ARRAY_SET     byte = 37
	OP_PKG_NEW       byte = 38
	OP_PKG_GET       byte = 39
	OP_PKG_SET       byte = 40
	OP_TRY_SETUP     byte = 41
	OP_TRY_END       byte = 42
	OP_THROW         byte = 43
	OP_STORE_LOCAL   byte = 44
	OP_LOAD_LOCAL    byte = 45
)

const (
	TYPE_NUM16  byte = 0
	TYPE_NUM64  byte = 1
	TYPE_CHAR   byte = 2
	TYPE_TRIT   byte = 3
	TYPE_BOOL   byte = 4
	TYPE_POINT  byte = 5
	TYPE_FUNC   byte = 6
	TYPE_STRING byte = 7
	TYPE_ARRAY  byte = 8
	TYPE_PKG    byte = 9
)

const (
	NATIVE_PRINT          uint16 = 0
	NATIVE_PRINTLN        uint16 = 1
	NATIVE_TYPEOF         uint16 = 2
	NATIVE_SET_COLOR_TEXT uint16 = 3
	NATIVE_SET_TYPE_TEXT  uint16 = 4
	NATIVE_SET_COLOR_BACK uint16 = 5
	NATIVE_RESET_COLOR    uint16 = 6
	NATIVE_SCAN           uint16 = 7
	NATIVE_ARRAY_LEN      uint16 = 8
	NATIVE_ARRAY_PUSH     uint16 = 9
)

// ==========================================
// EMITTER
// ==========================================
type Emitter struct {
	code         []byte
	deferred     bool
	deferredBuf  []byte
	deferredList [][]byte
	condStart    int
	inControl    bool
}

func (e *Emitter) emit(b byte) {
	if e.deferred {
		e.deferredBuf = append(e.deferredBuf, b)
	} else {
		e.code = append(e.code, b)
	}
}
func (e *Emitter) emit16(v uint16) { e.emit(byte(v)); e.emit(byte(v >> 8)) }
func (e *Emitter) emitI16(v int16) { e.emit(byte(v)); e.emit(byte(v >> 8)) }
func (e *Emitter) patchI16(off int, val int16) {
	e.code[off] = byte(val)
	e.code[off+1] = byte(val >> 8)
}
func (e *Emitter) pos() int { return len(e.code) }

func (e *Emitter) pushBool(val bool) {
	e.emit(OP_PUSH)
	e.emit(TYPE_BOOL)
	if val {
		e.emit(1)
	} else {
		e.emit(0)
	}
}
func (e *Emitter) pushChar(val uint8) { e.emit(OP_PUSH); e.emit(TYPE_CHAR); e.emit(val) }

func (e *Emitter) pushFunc(offset uint16, paramCount uint8) {
	e.emit(OP_PUSH)
	e.emit(TYPE_FUNC)
	e.emit16(offset)
	e.emit(paramCount)
}

func (e *Emitter) pushString(val string) {
	e.emit(OP_PUSH)
	e.emit(TYPE_STRING)
	inner := val[1 : len(val)-1] // strip quotes
	e.emit16(uint16(len(inner)))
	for i := 0; i < len(inner); i++ {
		e.emit(byte(inner[i]))
	}
	e.emit(0) // null terminator
}

// Codifica un valor en el formato MP16 radix mixto: v = bc·2^(-2p)·10^(s)
// con s = exp-BIAS. Busca ajuste EXACTO probando la década menor y dentro
// de ella la celda más dividida (p desc); si no existe toma el más
// cercano (menor error por comparación cruzada, empate lejos de cero).
func (e *Emitter) emitRaw16(val uint64, signo uint16) {
	pow4 := [6]uint64{1, 4, 16, 64, 256, 1024}
	pow10 := [3]uint64{1, 10, 100}

	bc, p, s := val, uint64(0), uint64(0)
	ok := false
	for si := uint64(0); si <= 2 && !ok; si++ {
		for pi := uint64(5); ; pi-- {
			num := val * pow4[pi]
			if num%pow10[si] == 0 {
				b := num / pow10[si]
				if b >= 1 && b <= 1023 {
					bc, p, s, ok = b, pi, si, true
					break
				}
			}
			if pi == 0 {
				break
			}
		}
	}
	if !ok {
		// el más cercano: mínimo error relativo a su década
		bestErr := uint64(1) << 62
		for si := uint64(0); si <= 2; si++ {
			for pi := uint64(0); pi <= 5; pi++ {
				num := val * pow4[pi]
				den := pow10[si]
				q := num / den
				r := num % den
				if q < 1 || q > 1023 {
					continue
				}
				err := r
				if den-r < err {
					err = den - r
				}
				l, rr := err*pow10[s], bestErr*pow10[si]
				if l < rr || (l == rr && q > bc) {
					bestErr, bc, p, s = err, q, pi, si
				}
			}
		}
	}
	raw := (uint16(p) << 13) | (uint16(bc) << 3) | (uint16(s+1) << 1) | signo
	e.emit(byte(raw))
	e.emit(byte(raw >> 8))
}

func (e *Emitter) pushNum16(val uint16) {
	e.emit(OP_PUSH)
	e.emit(TYPE_NUM16)
	e.emitRaw16(uint64(val), 0)
}

func (e *Emitter) pushNum16Signed(val int64) {
	e.emit(OP_PUSH)
	e.emit(TYPE_NUM16)
	signo := uint16(0)
	if val < 0 {
		signo = 1
		val = -val
	}
	e.emitRaw16(uint64(uint16(val)), signo)
}

func (e *Emitter) pushNum64(val uint64) {
	e.emit(OP_PUSH)
	e.emit(TYPE_NUM64)
	var p uint64
	var signo uint64
	exp := uint64(127) // bias de Num64 = 127
	bc := val
	for bc > 1125899906842623 { // 2^50 - 1
		bc /= 10
		exp++
	}
	raw := (p << 59) | (bc << 9) | (exp << 1) | signo
	e.emit(byte(raw))
	e.emit(byte(raw >> 8))
	e.emit(byte(raw >> 16))
	e.emit(byte(raw >> 24))
	e.emit(byte(raw >> 32))
	e.emit(byte(raw >> 40))
	e.emit(byte(raw >> 48))
	e.emit(byte(raw >> 56))
}

func (e *Emitter) pushNum64Signed(val int64) {
	e.emit(OP_PUSH)
	e.emit(TYPE_NUM64)
	var p uint64
	signo := uint64(0)
	if val < 0 {
		signo = 1
		val = -val
	}
	exp := uint64(127) // bias de Num64 = 127
	bc := uint64(val)
	for bc > 1125899906842623 { // 2^50 - 1
		bc /= 10
		exp++
	}
	raw := (p << 59) | (bc << 9) | (exp << 1) | signo
	e.emit(byte(raw))
	e.emit(byte(raw >> 8))
	e.emit(byte(raw >> 16))
	e.emit(byte(raw >> 24))
	e.emit(byte(raw >> 32))
	e.emit(byte(raw >> 40))
	e.emit(byte(raw >> 48))
	e.emit(byte(raw >> 56))
}

func (e *Emitter) pushNum64Float(val float64) {
	e.emit(OP_PUSH)
	e.emit(TYPE_NUM64)
	signo := uint64(0)
	if val < 0 {
		signo = 1
		val = -val
	}
	exp := uint64(127) // bias de Num64 = 127
	// Convertir a representación base-10: val = bc × 10^(exp - bias - p)
	// Usamos p=4 como precisión fraccionaria para decimales
	const fracDigits = 4
	bcFloat := val
	for i := 0; i < fracDigits; i++ {
		bcFloat *= 10.0
	}
	bc := uint64(bcFloat)
	for bc > 1125899906842623 { // 2^50 - 1
		bc /= 10
		exp++
	}
	raw := (uint64(fracDigits) << 59) | (bc << 9) | (exp << 1) | signo
	e.emit(byte(raw))
	e.emit(byte(raw >> 8))
	e.emit(byte(raw >> 16))
	e.emit(byte(raw >> 24))
	e.emit(byte(raw >> 32))
	e.emit(byte(raw >> 40))
	e.emit(byte(raw >> 48))
	e.emit(byte(raw >> 56))
}

// ==========================================
// HELPERS
// ==========================================
func tokText(node antlr.ParseTree) string {
	if tn, ok := node.(antlr.TerminalNode); ok {
		return tn.GetText()
	}
	return ""
}

func childTokText(ctx antlr.ParserRuleContext, idx int) string {
	if idx >= ctx.GetChildCount() {
		return ""
	}
	child := ctx.GetChild(idx)
	if tn, ok := child.(antlr.TerminalNode); ok {
		return tn.GetText()
	}
	return ""
}

// ==========================================
// CODE GENERATOR
// ==========================================
type CodeGen struct {
	*BasePaxoListener
	Emitter
	locals    map[string]uint16
	nextLocal uint16
	errors    []string

	varTypes      map[string]byte
	funcVarTypes  map[string]byte

	inFunction         bool
	savedCode          []byte
	funcBodies         [][]byte
	funcPatchPositions []int
	funcParamCounts    []int

	funcLocals      map[string]uint16
	funcNextLocal   uint16
	savedFuncLocals map[string]uint16
	savedFuncNext   uint16

	inCond        bool
	condCodeStart int

	inPkg     bool
	pkgFields []string

	inTryCatch       bool
	tryBlockCount    int
	tryCatchVarIdx   uint16
	catchOffsetPatch int
	tryCatchEndPatch int
}

func NewCodeGen() *CodeGen {
	return &CodeGen{
		BasePaxoListener: &BasePaxoListener{},
		Emitter:          Emitter{code: make([]byte, 0)},
		locals:           make(map[string]uint16),
		varTypes:         make(map[string]byte),
		funcVarTypes:     make(map[string]byte),
	}
}

func (cg *CodeGen) reportError(msg string) { cg.errors = append(cg.errors, msg) }
func (cg *CodeGen) Code() []byte           { return cg.code }
func (cg *CodeGen) Errors() []string       { return cg.errors }

func (cg *CodeGen) resolveIdent(name string) (idx uint16, isLocal bool, found bool) {
	if cg.inFunction {
		if i, ok := cg.funcLocals[name]; ok {
			return i, true, true
		}
	}
	if i, ok := cg.locals[name]; ok {
		return i, false, true
	}
	return 0, false, false
}

func (cg *CodeGen) resolveType(token string) byte {
	switch token {
	case "var", "📥":
		return TYPE_NUM64
	case "sn":
		return TYPE_NUM16
	case "n":
		return TYPE_NUM64
	case "abc":
		return TYPE_CHAR
	case "trit":
		return TYPE_TRIT
	case "bool":
		return TYPE_BOOL
	case "pin":
		return TYPE_POINT
	case "func":
		return TYPE_FUNC
	default:
		cg.reportError("tipo desconocido: " + token)
		return TYPE_NUM64
	}
}

func (cg *CodeGen) walkTree(tree antlr.ParseTree) {
	antlr.ParseTreeWalkerDefault.Walk(cg, tree)
}

// ==========================================
// Program
// ==========================================
func (cg *CodeGen) ExitProgram(ctx *ProgramContext) {
	cg.emit(OP_HALT)

	funcStart := len(cg.code)
	offsets := make([]int, len(cg.funcBodies))
	running := funcStart
	for i, body := range cg.funcBodies {
		offsets[i] = running
		cg.code = append(cg.code, body...)
		running += len(body)
	}

	for i, pos := range cg.funcPatchPositions {
		offset := uint16(offsets[i])
		cg.code[pos] = byte(offset)
		cg.code[pos+1] = byte(offset >> 8)
	}
}

// ==========================================
// VarDeclaration
// ==========================================
func (cg *CodeGen) ExitVarDeclaration(ctx *VarDeclarationContext) {
	name := ctx.IDENTIFIER().GetText()

	var varType byte = TYPE_NUM64
	var isDynamic bool
	if ctx.Type_() != nil {
		token := ctx.Type_().GetStart().GetText()
		varType = cg.resolveType(token)
		isDynamic = (token == "var" || token == "📥")
	} else {
		isDynamic = true
	}

	if cg.inPkg {
		cg.pkgFields = append(cg.pkgFields, name)
		return
	}

	var idx uint16
	var storeOp byte
	if cg.inFunction {
		idx = cg.funcNextLocal
		cg.funcLocals[name] = idx
		cg.funcNextLocal++
		storeOp = OP_STORE_LOCAL
		if !isDynamic {
			cg.funcVarTypes[name] = varType
		}
	} else {
		idx = cg.nextLocal
		cg.locals[name] = idx
		cg.nextLocal++
		storeOp = OP_STORE_VAR
		if !isDynamic {
			cg.varTypes[name] = varType
		}
	}

	if ctx.Expression() != nil {
		if ctx.Type_() != nil {
			token := ctx.Type_().GetStart().GetText()
			if token != "var" && token != "📥" {
				cg.emit(OP_CAST)
				cg.emit(varType)
			}
		}
		cg.emit(storeOp)
		cg.emit16(idx)
	} else if ctx.ArrayLiteral() != nil {
		cg.emitArrayLiteral(ctx.ArrayLiteral())
		cg.emit(storeOp)
		cg.emit16(idx)
	} else {
		switch varType {
		case TYPE_NUM16:
			cg.pushNum16(0)
		case TYPE_NUM64:
			cg.pushNum64(0)
		case TYPE_BOOL:
			cg.pushBool(false)
		case TYPE_CHAR:
			cg.pushChar(0)
		case TYPE_FUNC:
			cg.pushFunc(0, 0)
		default:
			cg.pushNum64(0)
		}
		cg.emit(storeOp)
		cg.emit16(idx)
	}
}

// ==========================================
// Assignment
// ==========================================
func (cg *CodeGen) EnterAssignment(ctx *AssignmentContext) {
	exprs := ctx.AllExpression()
	if len(exprs) == 2 {
		name := ctx.IDENTIFIER().GetText()
		idx, isLocal, ok := cg.resolveIdent(name)
		if !ok {
			cg.reportError("variable no declarada: " + name)
			return
		}
		if isLocal {
			cg.emit(OP_LOAD_LOCAL)
		} else {
			cg.emit(OP_LOAD_VAR)
		}
		cg.emit16(idx)
	}
}

func (cg *CodeGen) ExitAssignment(ctx *AssignmentContext) {
	name := ctx.IDENTIFIER().GetText()
	idx, isLocal, ok := cg.resolveIdent(name)
	if !ok {
		cg.reportError("variable no declarada: " + name)
		return
	}

	storeOp := OP_STORE_VAR
	loadOp := OP_LOAD_VAR
	if isLocal {
		storeOp = OP_STORE_LOCAL
		loadOp = OP_LOAD_LOCAL
	}

	exprs := ctx.AllExpression()
	if len(exprs) == 2 {
		cg.emit(OP_ARRAY_SET)
	} else if len(exprs) == 1 {
		var varType byte
		found := false
		if isLocal {
			varType, found = cg.funcVarTypes[name]
		} else {
			varType, found = cg.varTypes[name]
		}
		if found {
			cg.emit(OP_CAST)
			cg.emit(varType)
		}
		cg.emit(storeOp)
		cg.emit16(idx)
	} else {
		cg.emit(loadOp)
		cg.emit16(idx)
		if childTokText(ctx, 1) == "++" {
			cg.emit(OP_INC)
		} else {
			cg.emit(OP_DEC)
		}
		cg.emit(storeOp)
		cg.emit16(idx)
	}
}

// ==========================================
// CondStatement
// ==========================================
func (cg *CodeGen) EnterCondStatement(ctx *CondStatementContext) {
	cg.inCond = true
	cg.condCodeStart = len(cg.code)
}

func (cg *CodeGen) ExitCondStatement(ctx *CondStatementContext) {
	cg.inCond = false

	if len(cg.deferredBuf) > 0 {
		cg.deferredList = append(cg.deferredList, cg.deferredBuf)
	}
	cg.deferredBuf = nil

	blocks := cg.deferredList
	cg.deferredList = nil

	cases := ctx.AllMatchCase()
	if len(cases) == 0 {
		return
	}

	cg.code = cg.code[:cg.condCodeStart]

	condVar := cg.nextLocal
	cg.nextLocal++

	cg.walkTree(ctx.Expression())
	cg.emit(OP_STORE_VAR)
	cg.emit16(condVar)

	var endPatches []int

	for i, mc := range cases {
		isWildcard := childTokText(mc, 0) == "_"

		if isWildcard {
			if i < len(blocks) {
				cg.code = append(cg.code, blocks[i]...)
			}
		} else {
			cg.walkTree(mc.Expression())
			cg.emit(OP_JUMP_IF_FALSE)
			skipPatch := cg.pos()
			cg.emitI16(0)
			if i < len(blocks) {
				cg.code = append(cg.code, blocks[i]...)
			}
			cg.emit(OP_JUMP)
			endPatch := cg.pos()
			cg.emitI16(0)
			cg.patchI16(skipPatch, int16(cg.pos()-skipPatch-2))
			endPatches = append(endPatches, endPatch)
		}
	}

	for _, ep := range endPatches {
		cg.patchI16(ep, int16(cg.pos()-ep-2))
	}

	cg.nextLocal--
}

// ==========================================
// LoopStatement
// ==========================================
func (cg *CodeGen) EnterLoopStatement(ctx *LoopStatementContext) {
	cg.condStart = cg.pos()
	cg.inControl = true
}

func (cg *CodeGen) ExitLoopStatement(ctx *LoopStatementContext) {
	blockCode := cg.deferredBuf
	cg.deferredBuf = nil
	condStart := cg.condStart
	cg.inControl = false

	cg.emit(OP_JUMP_IF_FALSE)
	jumpEndPatch := cg.pos()
	cg.emitI16(0)
	cg.code = append(cg.code, blockCode...)
	cg.emit(OP_JUMP)
	jumpBackPatch := cg.pos()
	cg.emitI16(int16(condStart - cg.pos()))
	cg.patchI16(jumpBackPatch, int16(condStart-cg.pos()))
	cg.patchI16(jumpEndPatch, int16(cg.pos()-jumpEndPatch-2))
}

// ==========================================
// Expression — literals + identifiers
// ==========================================
func (cg *CodeGen) EnterEveryRule(ctx antlr.ParserRuleContext) {}

func (cg *CodeGen) ExitEveryRule(ctx antlr.ParserRuleContext) {
	if _, ok := ctx.(IExpressionContext); ok {
		cg.handleBaseExpression(ctx)
	}
}

func (cg *CodeGen) handleBaseExpression(ctx antlr.ParserRuleContext) {
	switch expr := ctx.(type) {
	case *IntLitExprContext:
		text := expr.INT_LITERAL().GetText()
		val, err := strconv.ParseInt(text, 10, 64)
		if err != nil {
			cg.reportError("literal entero inválido: " + text)
			cg.pushNum64(0)
		} else if val < 0 {
			cg.pushNum64Signed(val)
		} else {
			cg.pushNum64(uint64(val))
		}
	case *DecLitExprContext:
		text := expr.DECIMAL_LITERAL().GetText()
		val, err := strconv.ParseFloat(text, 64)
		if err != nil {
			cg.reportError("literal decimal inválido: " + text)
			cg.pushNum64(0)
		} else {
			cg.pushNum64Float(val)
		}
	case *CharLitExprContext:
		text := expr.CHAR_LITERAL().GetText()
		if len(text) >= 3 {
			cg.pushChar(uint8(text[1]))
		} else {
			cg.pushChar(0)
		}
	case *BoolBitExprContext:
		cg.pushBool(expr.BOOLEAN_BIT().GetText() == ".✓")
	case *BoolTritExprContext:
		text := expr.BOOLEAN_TRIT().GetText()
		cg.emit(OP_PUSH)
		cg.emit(TYPE_TRIT)
		if text == "•" {
			cg.emit(1)
		} else if text == "✓" {
			cg.emit(2)
		} else {
			cg.emit(0)
		}
	case *StringLitExprContext:
		cg.pushString(expr.STRING_LITERAL().GetText())
	case *IdentExprContext:
		name := expr.IDENTIFIER().GetText()
		idx, isLocal, found := cg.resolveIdent(name)
		if !found {
			cg.reportError("variable no declarada: " + name)
			return
		}
		if isLocal {
			cg.emit(OP_LOAD_LOCAL)
		} else {
			cg.emit(OP_LOAD_VAR)
		}
		cg.emit16(idx)
	case *PtrLitExprContext:
		text := expr.POINTER_LITERAL().GetText()
		name := text[1:]
		idx, _, found := cg.resolveIdent(name)
		if !found {
			cg.reportError("variable no declarada para puntero: " + name)
			return
		}
		cg.emit(OP_PUSH)
		cg.emit(TYPE_POINT)
		ptr := uintptr(idx)
		for i := 0; i < 8; i++ {
			cg.emit(byte(ptr >> (i * 8)))
		}
	case *ArrayLitExprContext:
		cg.emitArrayLiteral(expr.ArrayLiteral())
	case *IndexedAccessExprContext:
		cg.emit(OP_ARRAY_GET)
	case *DotAccessExprContext:
		cg.emitDotAccess(expr)
	case *PkgExprContext:
		cg.emitPackage(expr.PkgDeclaration())
	}
}

// ==========================================
// Binary Expressions
// ==========================================
func (cg *CodeGen) ExitAddSubExpr(ctx *AddSubExprContext) {
	switch childTokText(ctx, 1) {
	case "+":
		cg.emit(OP_ADD)
	case "-":
		cg.emit(OP_SUB)
	}
}

func (cg *CodeGen) ExitMultDivExpr(ctx *MultDivExprContext) {
	switch childTokText(ctx, 1) {
	case "×":
		cg.emit(OP_MUL)
	case "÷":
		cg.emit(OP_DIV)
	}
}

func (cg *CodeGen) ExitRelationalExpr(ctx *RelationalExprContext) {
	switch childTokText(ctx, 1) {
	case "==":
		cg.emit(OP_EQ)
	case "≠", "!=":
		cg.emit(OP_NEQ)
	case "<":
		cg.emit(OP_LT)
	case ">":
		cg.emit(OP_GT)
	case "≤", "<=":
		cg.emit(OP_LTE)
	case "≥", ">=":
		cg.emit(OP_GTE)
	}
}

func (cg *CodeGen) ExitBitwiseExpr(ctx *BitwiseExprContext) {
	switch childTokText(ctx, 1) {
	case "&":
		cg.emit(OP_BIT_AND)
	case "|":
		cg.emit(OP_BIT_OR)
	case ".&":
		cg.emit(OP_AND)
	case ".|":
		cg.emit(OP_OR)
	}
}

func (cg *CodeGen) ExitShiftExpr(ctx *ShiftExprContext) {
	switch childTokText(ctx, 1) {
	case "•«":
		cg.emit(OP_BIT_SHL)
	case "»•":
		cg.emit(OP_BIT_SHR)
	}
}

func (cg *CodeGen) ExitNotgateExpr(ctx *NotgateExprContext) {
	switch childTokText(ctx, 0) {
	case ".!", "!.!":
		cg.emit(OP_BIT_NOT)
	default:
		cg.emit(OP_NOT)
	}
}

// ==========================================
// CallExpr
// ==========================================
func (cg *CodeGen) ExitCallExpr(ctx *CallExprContext) {
	name := ctx.IDENTIFIER().GetText()
	argCount := 0
	if ctx.ArgumentList() != nil {
		for range ctx.ArgumentList().AllExpression() {
			argCount++
		}
	}

	switch name {
	case "print":
		cg.emit(OP_CALL_NATIVE)
		cg.emit16(NATIVE_PRINT)
		cg.emit(byte(argCount))
	case "println":
		cg.emit(OP_CALL_NATIVE)
		cg.emit16(NATIVE_PRINTLN)
		cg.emit(byte(argCount))
	case "typeof":
		cg.emit(OP_CALL_NATIVE)
		cg.emit16(NATIVE_TYPEOF)
		cg.emit(byte(argCount))
	case "text_color":
		cg.emit(OP_CALL_NATIVE)
		cg.emit16(NATIVE_SET_COLOR_TEXT)
		cg.emit(byte(argCount))
	case "text_type":
		cg.emit(OP_CALL_NATIVE)
		cg.emit16(NATIVE_SET_TYPE_TEXT)
		cg.emit(byte(argCount))
	case "bg_color":
		cg.emit(OP_CALL_NATIVE)
		cg.emit16(NATIVE_SET_COLOR_BACK)
		cg.emit(byte(argCount))
	case "reset_color":
		cg.emit(OP_CALL_NATIVE)
		cg.emit16(NATIVE_RESET_COLOR)
		cg.emit(byte(argCount))
	case "scan":
		cg.emit(OP_CALL_NATIVE)
		cg.emit16(NATIVE_SCAN)
		cg.emit(byte(argCount))
	case "array_len":
		cg.emit(OP_CALL_NATIVE)
		cg.emit16(NATIVE_ARRAY_LEN)
		cg.emit(byte(argCount))
	case "array_push":
		cg.emit(OP_CALL_NATIVE)
		cg.emit16(NATIVE_ARRAY_PUSH)
		cg.emit(byte(argCount))
	default:
		idx, ok := cg.locals[name]
		if !ok {
			cg.reportError("función no definida: " + name)
			return
		}
		cg.emit(OP_LOAD_VAR)
		cg.emit16(idx)
		cg.emit(OP_CALL_VAR)
		cg.emit(byte(argCount))
	}
}

func (cg *CodeGen) EnterBlock(ctx *BlockContext) {
	if cg.inTryCatch {
		if cg.tryBlockCount == 1 {
			// Second block (catch): emit OP_TRY_END + STORE_VAR for catch variable
			cg.emit(OP_TRY_END)
			cg.tryCatchEndPatch = cg.pos()
			cg.emitI16(0) // placeholder — end_offset
			cg.emit(OP_STORE_VAR)
			cg.emit16(cg.tryCatchVarIdx)
		}
		return
	}
	if cg.inControl || cg.inCond {
		if cg.deferred && len(cg.deferredBuf) > 0 {
			cg.deferredList = append(cg.deferredList, cg.deferredBuf)
		}
		cg.deferred = true
		cg.deferredBuf = make([]byte, 0)
	}
}

func (cg *CodeGen) ExitBlock(ctx *BlockContext) {
	if cg.inTryCatch {
		cg.tryBlockCount++
		return
	}
	if cg.deferred {
		if cg.inCond {
			cg.deferredList = append(cg.deferredList, cg.deferredBuf)
			cg.deferredBuf = nil
		}
		cg.deferred = false
	}
}
func (cg *CodeGen) ExitMatchCase(ctx *MatchCaseContext) {}

// ==========================================
// ParameterList
// ==========================================
func (cg *CodeGen) EnterParameterList(ctx *ParameterListContext) {
	if !cg.inFunction {
		return
	}
	identifiers := ctx.AllIDENTIFIER()
	for _, id := range identifiers {
		name := id.GetText()
		cg.funcLocals[name] = cg.funcNextLocal
		cg.funcNextLocal++
	}
}

// ==========================================
// ReturnStatement
// ==========================================
func (cg *CodeGen) ExitReturnStatement(ctx *ReturnStatementContext) {
	cg.emit(OP_RETURN)
}

// ==========================================
// TryCatchStatement
// ==========================================
func (cg *CodeGen) EnterTryCatchStatement(ctx *TryCatchStatementContext) {
	catchVarName := ctx.AllIDENTIFIER()[0].GetText()
	idx := cg.nextLocal
	cg.nextLocal++
	cg.tryCatchVarIdx = idx
	cg.locals[catchVarName] = idx

	cg.inTryCatch = true
	cg.tryBlockCount = 0

	cg.emit(OP_TRY_SETUP)
	cg.catchOffsetPatch = cg.pos()
	cg.emitI16(0) // placeholder — catch_offset
}

func (cg *CodeGen) ExitTryCatchStatement(ctx *TryCatchStatementContext) {
	// Patch catch_offset to point to STORE_VAR (right after OP_TRY_END operand)
	catchTarget := cg.tryCatchEndPatch + 2
	cg.patchI16(cg.catchOffsetPatch, int16(catchTarget-cg.catchOffsetPatch-2))

	// Patch end_offset to jump past catch block
	cg.patchI16(cg.tryCatchEndPatch, int16(cg.pos()-cg.tryCatchEndPatch-2))

	cg.inTryCatch = false
	cg.tryBlockCount = 0
}

// ==========================================
// ThrowStatement
// ==========================================
func (cg *CodeGen) ExitThrowStatement(ctx *ThrowStatementContext) {
	cg.emit(OP_THROW)
}

// ==========================================
// FuncExpr
// ==========================================
func (cg *CodeGen) EnterFuncExpr(ctx *FuncExprContext) {
	cg.savedCode = cg.code
	cg.code = make([]byte, 0)
	cg.inFunction = true

	cg.savedFuncLocals = cg.funcLocals
	cg.savedFuncNext = cg.funcNextLocal
	cg.funcLocals = make(map[string]uint16)
	cg.funcNextLocal = 0
}

func (cg *CodeGen) ExitFuncExpr(ctx *FuncExprContext) {
	cg.emit(OP_RETURN)

	funcBody := cg.code
	paramCount := 0
	if fd := ctx.FunctionDeclaration(); fd != nil {
		if pl := fd.ParameterList(); pl != nil {
			paramCount = len(pl.AllIDENTIFIER())
		}
	}
	cg.funcBodies = append(cg.funcBodies, funcBody)
	cg.funcParamCounts = append(cg.funcParamCounts, paramCount)

	cg.code = cg.savedCode
	cg.inFunction = false

	cg.funcLocals = cg.savedFuncLocals
	cg.funcNextLocal = cg.savedFuncNext

	cg.emit(OP_PUSH)
	cg.emit(TYPE_FUNC)
	cg.funcPatchPositions = append(cg.funcPatchPositions, len(cg.code))
	cg.emit16(0)
	cg.emit(byte(paramCount))
}

// ==========================================
// Array Literals
// ==========================================
func (cg *CodeGen) emitArrayLiteral(ctx IArrayLiteralContext) {
	exprs := ctx.AllExpression()
	count := uint16(len(exprs))
	cg.emit(OP_ARRAY_NEW)
	cg.emit16(count)
}

// ==========================================
// Dot Access (pkg.field) — expression already on stack from walker
// ==========================================
func (cg *CodeGen) emitDotAccess(ctx *DotAccessExprContext) {
	fieldName := ctx.IDENTIFIER().GetText()
	cg.emit(OP_PKG_GET)
	cg.emit16(uint16(len(fieldName)))
	for _, b := range []byte(fieldName) {
		cg.emit(b)
	}
}

// ==========================================
// Package Declaration
// ==========================================
func (cg *CodeGen) EnterPkgExpr(ctx *PkgExprContext) {
	cg.inPkg = true
	cg.pkgFields = nil
}

func (cg *CodeGen) emitPackage(ctx IPkgDeclarationContext) {
	cg.inPkg = false
	fields := cg.pkgFields
	cg.pkgFields = nil

	count := uint16(len(fields))
	cg.emit(OP_PKG_NEW)
	cg.emit16(count)
	for i := len(fields) - 1; i >= 0; i-- {
		name := fields[i]
		cg.emit16(uint16(len(name)))
		for _, b := range []byte(name) {
			cg.emit(b)
		}
	}
}

// ==========================================
// Array native functions (len, push)
// ==========================================
func Compile(inputFile, outputFile string, dump bool) error {
	input, err := antlr.NewFileStream(inputFile)
	if err != nil {
		return fmt.Errorf("error leyendo %s: %v", inputFile, err)
	}

	lexer := NewPaxoLexer(input)
	stream := antlr.NewCommonTokenStream(lexer, 0)
	p := NewPaxoParser(stream)
	tree := p.Program()

	cg := NewCodeGen()
	antlr.ParseTreeWalkerDefault.Walk(cg, tree)

	if len(cg.errors) > 0 {
		for _, e := range cg.errors {
			fmt.Fprintf(os.Stderr, "Error: %s\n", e)
		}
		return fmt.Errorf("%d errores de compilación", len(cg.errors))
	}

	err = os.WriteFile(outputFile, cg.code, 0o644)
	if err != nil {
		return fmt.Errorf("error escribiendo %s: %v", outputFile, err)
	}

	fmt.Printf("Compilado: %s → %s (%d bytes)\n", inputFile, outputFile, len(cg.code))

	if dump {
		fmt.Println("\nBytecode hex dump:")
		for i := 0; i < len(cg.code); i += 16 {
			fmt.Printf("  %04X: ", i)
			end := i + 16
			if end > len(cg.code) {
				end = len(cg.code)
			}
			for j := i; j < end; j++ {
				fmt.Printf("%02X ", cg.code[j])
			}
			fmt.Println()
		}
	}
	return nil
}
