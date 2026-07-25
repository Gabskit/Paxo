package parser

import (
	"fmt"
	"os"
	"strings"
	"github.com/antlr4-go/antlr/v4")

type BytecodeGenerator struct {
	*BasePaxoListener
	Bytecode []byte}

// Ejemplo de captura de declaración de variables.
func (g *BytecodeGenerator) EnterVarDeclaration(ctx *VarDeclarationContext) {
	// Opcode 0x01 = PUSH / STORE
	g.Bytecode = append(g.Bytecode, 0x01)}

func (g *BytecodeGenerator) EnterAddSubExpression(ctx *AddSubExprContext) {
	if strings.Contains(ctx.GetText(), "+") {
		// Opcode 0x10 = Add
		g.Bytecode = append(g.Bytecode, 0x10)
	} else if strings.Contains(ctx.GetText(), "-") {
		// Opcode 0x11 = Sub
		g.Bytecode = append(g.Bytecode, 0x11)}}

func (g *BytecodeGenerator) EnterMulDivExpression(ctx *MultDivExprContext) {
	if strings.Contains(ctx.GetText(), "×") {
		// Opcode 0x12 = Mul
		g.Bytecode = append(g.Bytecode, 0x12)
	} else if strings.Contains(ctx.GetText(), "÷") {
		// Opcode 0x13 = Div
		g.Bytecode = append(g.Bytecode, 0x13)}}

func (g *BytecodeGenerator) EnterShiftExpression(ctx *ShiftExprContext) {
	if strings.Contains(ctx.GetText(), "<<") {
		// Opcode 0x14 = LShift
		g.Bytecode = append(g.Bytecode, 0x14)
	} else if strings.Contains(ctx.GetText(), ">>") {
		// Opcode 0x15 = RShift
		g.Bytecode = append(g.Bytecode, 0x15)}}

func GenerateBytecode(inputPath string, outputPath string) error {
	input, err := antlr.NewFileStream(inputPath)
	if err != nil {
		return err}

	lexer := NewPaxoLexer(input)
	stream := antlr.NewCommonTokenStream(lexer, 0)
	p := NewPaxoParser(stream)

	tree := p.Program()
	generator := &BytecodeGenerator{BasePaxoListener: &BasePaxoListener{}}
	antlr.ParseTreeWalkerDefault.Walk(generator, tree)

	if err := os.WriteFile(outputPath, generator.Bytecode, 0644); err != nil {
		return err}

	fmt.Printf("¡Bytecode %q generado con éxito!\n", outputPath)
	return nil}