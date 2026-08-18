package main

import (
	"fmt"
	"os"
	"strings"

	parser "paxo/Src/Bcgen"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "Uso: paxocc <archivo.paxo> [output.pbc] [-d]\n")
		os.Exit(1)
	}

	inputFile := os.Args[1]
	outputFile := strings.TrimSuffix(inputFile, ".paxo") + ".pbc"
	dump := false

	for i := 2; i < len(os.Args); i++ {
		if os.Args[i] == "-d" {
			dump = true
		} else {
			outputFile = os.Args[i]
		}
	}

	err := parser.Compile(inputFile, outputFile, dump)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v\n", err)
		os.Exit(1)
	}
}
