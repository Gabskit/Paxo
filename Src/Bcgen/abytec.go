package parser

import (
	"fmt"
	"os"
	"strings"

	"github.com/antlr4-go/antlr/v4"
)

type CraneliftIRGenerator struct {
	*BasePaxoListener
	CLIFBuilder strings.Builder
	VarIndex    int
}

func NewCraneliftIRGenerator() *CraneliftIRGenerator {
	g := &CraneliftIRGenerator{}
	// Firma de función principal en Cranelift IR
	g.CLIFBuilder.WriteString("function %main() -> i32 {\n")
	g.CLIFBuilder.WriteString("block0:\n")
	return g
}

func (g *CraneliftIRGenerator) EnterVarDeclaration(ctx *VarDeclarationContext) {
	varName := ctx.IDENTIFIER().GetText()
	g.CLIFBuilder.WriteString(fmt.Sprintf("    ; Declaracion de variable %s\n", varName))
}

func (g *CraneliftIRGenerator) EnterAddSubExpression(ctx *AddSubExprContext) {
	if strings.Contains(ctx.GetText(), "+") {
		// En lugar del opcode 0x10, emitimos una llamada al runtime C (add_num8)
		g.CLIFBuilder.WriteString("    %res = call %add_num8(%valA, %valB)\n")
	} else if strings.Contains(ctx.GetText(), "-") {
		g.CLIFBuilder.WriteString("    %res = call %sub_num8(%valA, %valB)\n")
	}
}

func (g *CraneliftIRGenerator) EnterMulDivExpression(ctx *MultDivExprContext) {
	if strings.Contains(ctx.GetText(), "×") {
		g.CLIFBuilder.WriteString("    %res = call %mul_num8(%valA, %valB)\n")
	} else if strings.Contains(ctx.GetText(), "÷") {
		g.CLIFBuilder.WriteString("    %res = call %div_num8(%valA, %valB)\n")
	}
}

func (g *CraneliftIRGenerator) GenerateCLIF() string {
	g.CLIFBuilder.WriteString("    v0 = iconst.i32 0\n")
	g.CLIFBuilder.WriteString("    return v0\n")
	g.CLIFBuilder.WriteString("}\n")
	return g.CLIFBuilder.String()
}

func GenerateCraneliftIR(inputPath string, outputPath string) error {
	input, err := antlr.NewFileStream(inputPath)
	if err != nil {
		return err
	}

	lexer := NewPaxoLexer(input)
	stream := antlr.NewCommonTokenStream(lexer, 0)
	p := NewPaxoParser(stream)

	tree := p.Program()
	generator := NewCraneliftIRGenerator()
	antlr.ParseTreeWalkerDefault.Walk(generator, tree)

	clifCode := generator.GenerateCLIF()
	return os.WriteFile(outputPath, []byte(clifCode), 0644)
}
