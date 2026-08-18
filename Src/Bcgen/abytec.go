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
)

const (
	TYPE_NUM8  byte = 0
	TYPE_NUM16 byte = 1
	TYPE_NUM32 byte = 2
	TYPE_NUM64 byte = 3
	TYPE_CHAR  byte = 4
	TYPE_TRIT  byte = 5
	TYPE_BOOL  byte = 6
	TYPE_POINT byte = 7
)

const (
	NATIVE_PRINT   uint16 = 0
	NATIVE_PRINTLN uint16 = 1
	NATIVE_TYPEOF  uint16 = 2
)

// ==========================================
// EMITTER
// ==========================================
type Emitter struct {
	code []byte
}

func (e *Emitter) emit(b byte)                 { e.code = append(e.code, b) }
func (e *Emitter) emit16(v uint16)             { e.code = append(e.code, byte(v), byte(v>>8)) }
func (e *Emitter) emitI16(v int16)             { e.code = append(e.code, byte(v), byte(v>>8)) }
func (e *Emitter) patchI16(off int, val int16)  { e.code[off] = byte(val); e.code[off+1] = byte(val>>8) }
func (e *Emitter) pos() int                    { return len(e.code) }

func (e *Emitter) pushNum8(val uint8) {
	e.emit(OP_PUSH)
	e.emit(TYPE_NUM8)
	var signo, exp, bc, p uint8
	bc = val
	for bc > 15 {
		bc /= 20
		exp++
	}
	e.emit((p << 6) | (bc << 2) | (exp << 1) | signo)
}
func (e *Emitter) pushBool(val bool)   { e.emit(OP_PUSH); e.emit(TYPE_BOOL); if val { e.emit(1) } else { e.emit(0) } }
func (e *Emitter) pushChar(val uint8)  { e.emit(OP_PUSH); e.emit(TYPE_CHAR); e.emit(val) }
func (e *Emitter) pushNum16(val uint16) { e.emit(OP_PUSH); e.emit(TYPE_NUM16); e.emit16(val) }

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
}

func NewCodeGen() *CodeGen {
	return &CodeGen{
		BasePaxoListener: &BasePaxoListener{},
		Emitter:          Emitter{code: make([]byte, 0)},
		locals:           make(map[string]uint16),
	}
}

func (cg *CodeGen) reportError(msg string) { cg.errors = append(cg.errors, msg) }
func (cg *CodeGen) Code() []byte          { return cg.code }
func (cg *CodeGen) Errors() []string      { return cg.errors }

func (cg *CodeGen) resolveType(token string) byte {
	switch token {
	case "var", "📥": return TYPE_NUM8
	case "n": return TYPE_NUM8
	case "abc": return TYPE_CHAR
	case "trit": return TYPE_TRIT
	case "bool": return TYPE_BOOL
	case "pin": return TYPE_POINT
	}
	return TYPE_NUM8
}

func (cg *CodeGen) walkTree(tree antlr.ParseTree) {
	antlr.ParseTreeWalkerDefault.Walk(cg, tree)
}

// ==========================================
// Program
// ==========================================
func (cg *CodeGen) ExitProgram(ctx *ProgramContext) {
	cg.emit(OP_HALT)
}

// ==========================================
// VarDeclaration
// ==========================================
func (cg *CodeGen) ExitVarDeclaration(ctx *VarDeclarationContext) {
	name := ctx.IDENTIFIER().GetText()

	var varType byte = TYPE_NUM8
	if ctx.Type_() != nil {
		varType = cg.resolveType(ctx.Type_().GetStart().GetText())
	}

	idx := cg.nextLocal
	cg.locals[name] = idx
	cg.nextLocal++

	if ctx.Expression() != nil {
		cg.emit(OP_STORE_VAR)
		cg.emit16(idx)
	} else {
		switch varType {
		case TYPE_NUM8:  cg.pushNum8(0)
		case TYPE_BOOL:  cg.pushBool(false)
		case TYPE_CHAR:  cg.pushChar(0)
		default:         cg.pushNum8(0)
		}
		cg.emit(OP_STORE_VAR)
		cg.emit16(idx)
	}
}

// ==========================================
// Assignment
// ==========================================
func (cg *CodeGen) ExitAssignment(ctx *AssignmentContext) {
	name := ctx.IDENTIFIER().GetText()
	idx, ok := cg.locals[name]
	if !ok {
		cg.reportError("variable no declarada: " + name)
		return
	}

	if ctx.Expression() != nil {
		cg.emit(OP_STORE_VAR)
		cg.emit16(idx)
	} else {
		// x++ o x--
		cg.emit(OP_LOAD_VAR)
		cg.emit16(idx)
		if childTokText(ctx, 1) == "++" {
			cg.emit(OP_INC)
		} else {
			cg.emit(OP_DEC)
		}
		cg.emit(OP_STORE_VAR)
		cg.emit16(idx)
	}
}

// ==========================================
// CondStatement
// ==========================================
func (cg *CodeGen) ExitCondStatement(ctx *CondStatementContext) {
	cases := ctx.AllMatchCase()
	jumpEnds := make([]int, 0)

	for i := 0; i < len(cases)-1; i++ {
		mc := cases[i]
		cg.walkTree(mc.Expression())
		cg.emit(OP_EQ)
		cg.emit(OP_JUMP_IF_FALSE)
		skipPatch := cg.pos()
		cg.emitI16(0)
		cg.emit(OP_POP)
		cg.walkTree(mc.Block())
		cg.emit(OP_JUMP)
		jumpEnds = append(jumpEnds, cg.pos())
		cg.emitI16(0)
		cg.patchI16(skipPatch, int16(cg.pos()-skipPatch))
	}

	last := cases[len(cases)-1]
	lastChild := childTokText(last, 0)
	if lastChild == "_" {
		cg.emit(OP_POP)
		cg.walkTree(last.Block())
	} else {
		cg.walkTree(last.Expression())
		cg.emit(OP_EQ)
		cg.emit(OP_JUMP_IF_FALSE)
		skipPatch := cg.pos()
		cg.emitI16(0)
		cg.emit(OP_POP)
		cg.walkTree(last.Block())
		cg.patchI16(skipPatch, int16(cg.pos()-skipPatch))
	}

	for _, jmpPos := range jumpEnds {
		cg.patchI16(jmpPos, int16(cg.pos()-jmpPos))
	}
}

// ==========================================
// LoopStatement
// ==========================================
func (cg *CodeGen) ExitLoopStatement(ctx *LoopStatementContext) {
	loopStart := cg.pos()
	cg.emit(OP_JUMP_IF_FALSE)
	loopEndPatch := cg.pos()
	cg.emitI16(0)

	cg.walkTree(ctx.Block())

	cg.emit(OP_JUMP)
	cg.patchI16(cg.pos()-2, int16(loopStart-(cg.pos()-2)))
	cg.patchI16(loopEndPatch, int16(cg.pos()-loopEndPatch))
}

// ==========================================
// Expression — literals + identifiers
// ==========================================
func (cg *CodeGen) EnterEveryRule(ctx antlr.ParserRuleContext) {}

func (cg *CodeGen) ExitEveryRule(ctx antlr.ParserRuleContext) {
	if expr, ok := ctx.(*ExpressionContext); ok {
		cg.handleBaseExpression(expr)
	}
}

func (cg *CodeGen) handleBaseExpression(ctx *ExpressionContext) {
	if ctx.INT_LITERAL() != nil {
		text := ctx.INT_LITERAL().GetText()
		val, _ := strconv.Atoi(text)
		if val >= 0 && val <= 255 {
			cg.pushNum8(uint8(val))
		} else {
			cg.pushNum16(uint16(val))
		}
		return
	}
	if ctx.DECIMAL_LITERAL() != nil {
		text := ctx.DECIMAL_LITERAL().GetText()
		val, _ := strconv.ParseFloat(text, 64)
		cg.pushNum8(uint8(int(val)))
		return
	}
	if ctx.CHAR_LITERAL() != nil {
		text := ctx.CHAR_LITERAL().GetText()
		if len(text) >= 3 {
			cg.pushChar(uint8(text[1]))
		} else {
			cg.pushChar(0)
		}
		return
	}
	if ctx.BOOLEAN_BIT() != nil {
		cg.pushBool(ctx.BOOLEAN_BIT().GetText() == ".✓")
		return
	}
	if ctx.BOOLEAN_TRIT() != nil {
		text := ctx.BOOLEAN_TRIT().GetText()
		cg.emit(OP_PUSH)
		cg.emit(TYPE_TRIT)
		if text == "•" {
			cg.emit(1)
		} else if text == "✓" {
			cg.emit(2)
		} else {
			cg.emit(0)
		}
		return
	}
	if ctx.STRING_LITERAL() != nil {
		text := ctx.STRING_LITERAL().GetText()
		for i := 1; i < len(text)-1; i++ {
			cg.pushChar(uint8(text[i]))
		}
		return
	}
	if ctx.IDENTIFIER() != nil {
		name := ctx.IDENTIFIER().GetText()
		idx, ok := cg.locals[name]
		if !ok {
			cg.reportError("variable no declarada: " + name)
			return
		}
		cg.emit(OP_LOAD_VAR)
		cg.emit16(idx)
		return
	}
}

// ==========================================
// Binary Expressions
// ==========================================
func (cg *CodeGen) ExitAddSubExpr(ctx *AddSubExprContext) {
	switch childTokText(ctx, 1) {
	case "+": cg.emit(OP_ADD)
	case "-": cg.emit(OP_SUB)
	}
}

func (cg *CodeGen) ExitMultDivExpr(ctx *MultDivExprContext) {
	switch childTokText(ctx, 1) {
	case "×": cg.emit(OP_MUL)
	case "÷": cg.emit(OP_DIV)
	}
}

func (cg *CodeGen) ExitRelationalExpr(ctx *RelationalExprContext) {
	switch childTokText(ctx, 1) {
	case "==": cg.emit(OP_EQ)
	case "≠":  cg.emit(OP_NEQ)
	case "<":  cg.emit(OP_LT)
	case ">":  cg.emit(OP_GT)
	case "≤":  cg.emit(OP_LTE)
	case "≥":  cg.emit(OP_GTE)
	}
}

func (cg *CodeGen) ExitBitwiseExpr(ctx *BitwiseExprContext) {
	switch childTokText(ctx, 1) {
	case "&":  cg.emit(OP_BIT_AND)
	case "|":  cg.emit(OP_BIT_OR)
	case ".&": cg.emit(OP_AND)
	case ".|": cg.emit(OP_OR)
	}
}

func (cg *CodeGen) ExitShiftExpr(ctx *ShiftExprContext) {
	switch childTokText(ctx, 1) {
	case "•«": cg.emit(OP_BIT_SHL)
	case "»•": cg.emit(OP_BIT_SHR)
	}
}

func (cg *CodeGen) ExitNotgateExpr(ctx *NotgateExprContext) {
	switch childTokText(ctx, 0) {
	case ".!", "!.!": cg.emit(OP_BIT_NOT)
	default:         cg.emit(OP_NOT)
	}
}

// ==========================================
// CallExpr
// ==========================================
func (cg *CodeGen) ExitCallExpr(ctx *CallExprContext) {
	name := ctx.IDENTIFIER().GetText()
	argCount := 0
	if ctx.ArgumentList() != nil {
		argCount = len(ctx.ArgumentList().AllExpression())
	}

	switch name {
	case "print":
		cg.emit(OP_CALL_NATIVE); cg.emit16(NATIVE_PRINT); cg.emit(byte(argCount))
	case "println":
		cg.emit(OP_CALL_NATIVE); cg.emit16(NATIVE_PRINTLN); cg.emit(byte(argCount))
	case "typeof":
		cg.emit(OP_CALL_NATIVE); cg.emit16(NATIVE_TYPEOF); cg.emit(byte(argCount))
	default:
		cg.reportError("función no definida: " + name)
	}
}

func (cg *CodeGen) ExitBlock(ctx *BlockContext) {}
func (cg *CodeGen) ExitMatchCase(ctx *MatchCaseContext) {}

// ==========================================
// Compile
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

	err = os.WriteFile(outputFile, cg.code, 0644)
	if err != nil {
		return fmt.Errorf("error escribiendo %s: %v", outputFile, err)
	}

	fmt.Printf("Compilado: %s → %s (%d bytes)\n", inputFile, outputFile, len(cg.code))

	if dump {
		fmt.Println("\nBytecode hex dump:")
		for i := 0; i < len(cg.code); i += 16 {
			fmt.Printf("  %04X: ", i)
			end := i + 16
			if end > len(cg.code) { end = len(cg.code) }
			for j := i; j < end; j++ {
				fmt.Printf("%02X ", cg.code[j])
			}
			fmt.Println()
		}
	}
	return nil
}
