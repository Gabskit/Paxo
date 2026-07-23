package parser

import (
	"fmt"
	"os"

	"github.com/antlr4-go/antlr/v4"
)

type BytecodeGenerator struct {
	*BasePaxoListener
	Bytecode []byte
}

// Ejemplo de captura de declaración de variables.
func (g *BytecodeGenerator) EnterVarDeclaration(ctx *VarDeclarationContext) {
	fmt.Println("Generando Opcode para Variable:", ctx.GetText())
	// Opcode 0x01 = PUSH / STORE
	g.Bytecode = append(g.Bytecode, 0x01)
}

func GenerateBytecode(inputPath string, outputPath string) error {
	input, err := antlr.NewFileStream(inputPath)
	if err != nil {
		return err
	}

	lexer := NewPaxoLexer(input)
	stream := antlr.NewCommonTokenStream(lexer, 0)
	p := NewPaxoParser(stream)

	tree := p.Program()
	generator := &BytecodeGenerator{BasePaxoListener: &BasePaxoListener{}}
	antlr.ParseTreeWalkerDefault.Walk(generator, tree)

	if err := os.WriteFile(outputPath, generator.Bytecode, 0644); err != nil {
		return err
	}

	fmt.Printf("¡Bytecode %q generado con éxito!\n", outputPath)
	return nil
}