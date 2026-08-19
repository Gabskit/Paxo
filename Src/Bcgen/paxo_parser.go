
package parser // Paxo

import (
	"fmt"
	"strconv"
  	"sync"

	"github.com/antlr4-go/antlr/v4"
)

// Suppress unused import errors
var _ = fmt.Printf
var _ = strconv.Itoa
var _ = sync.Once{}


type PaxoParser struct {
	*antlr.BaseParser
}

var PaxoParserStaticData struct {
  once                   sync.Once
  serializedATN          []int32
  LiteralNames           []string
  SymbolicNames          []string
  RuleNames              []string
  PredictionContextCache *antlr.PredictionContextCache
  atn                    *antlr.ATN
  decisionToDFA          []*antlr.DFA
}

func paxoParserInit() {
  staticData := &PaxoParserStaticData
  staticData.LiteralNames = []string{
    "", "';'", "'<'", "'.'", "'>'", "'='", "'['", "']'", "'++'", "'--'", 
    "'('", "')'", "'?'", "':'", "'->'", "'_'", "'|:'", "'\\U0001D106'", 
    "':|'", "'\\U0001D107'", "'{'", "'}'", "','", "'\\u00F7'", "'\\u00D7'", 
    "'+'", "'-'", "'\\u2022\\u00AB'", "'\\u00BB\\u2022'", "'\\u2264'", "'\\u2265'", 
    "'=='", "'\\u2260'", "'&'", "'|'", "'.&'", "'.|'", "'!'", "'.!'", "'\\u00AB'", 
    "'\\u00BB'", "", "", "'abc'", "'trit'", "'bool'", "'pin'", "", "'local'",
  }
  staticData.SymbolicNames = []string{
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
    "", "", "", "", "", "", "", "VAR_TYPE", "NUM_TYPE", "CHARA_TYPE", "TRIT_TYPE", 
    "BOOLEAN_TYPE", "POINTER_TYPE", "GLOBAL", "LOCAL", "TRY", "CATCH", "ARROW", 
    "INCLUDE", "PAUSE_MODE", "PLAY_MODE", "INT_LITERAL", "DECIMAL_LITERAL", 
    "BOOLEAN_BIT", "BOOLEAN_TRIT", "POINTER_LITERAL", "IDENTIFIER", "STRING_LITERAL", 
    "CHAR_LITERAL", "LINE_COMMENT", "BLOCK_COMMENT", "WS",
  }
  staticData.RuleNames = []string{
    "program", "statement", "varDeclaration", "type", "scope", "assignment", 
    "condStatement", "matchCase", "loopStatement", "loopMode", "loopDelimiter", 
    "loopEndDelimiter", "tryCatchStatement", "functionDeclaration", "pkgDeclaration", 
    "block", "parameterList", "argumentList", "expression", "arrayLiteral", 
    "arrayAccess",
  }
  staticData.PredictionContextCache = antlr.NewPredictionContextCache()
  staticData.serializedATN = []int32{
	4, 1, 65, 265, 2, 0, 7, 0, 2, 1, 7, 1, 2, 2, 7, 2, 2, 3, 7, 3, 2, 4, 7, 
	4, 2, 5, 7, 5, 2, 6, 7, 6, 2, 7, 7, 7, 2, 8, 7, 8, 2, 9, 7, 9, 2, 10, 7, 
	10, 2, 11, 7, 11, 2, 12, 7, 12, 2, 13, 7, 13, 2, 14, 7, 14, 2, 15, 7, 15, 
	2, 16, 7, 16, 2, 17, 7, 17, 2, 18, 7, 18, 2, 19, 7, 19, 2, 20, 7, 20, 1, 
	0, 5, 0, 44, 8, 0, 10, 0, 12, 0, 47, 9, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 64, 8, 
	1, 1, 1, 3, 1, 67, 8, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 
	1, 2, 1, 2, 1, 2, 3, 2, 80, 8, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 
	2, 1, 2, 3, 2, 90, 8, 2, 1, 3, 1, 3, 1, 4, 1, 4, 1, 5, 1, 5, 1, 5, 1, 5, 
	1, 5, 1, 5, 1, 5, 3, 5, 103, 8, 5, 1, 6, 1, 6, 1, 6, 1, 6, 1, 6, 1, 6, 
	1, 6, 5, 6, 112, 8, 6, 10, 6, 12, 6, 115, 9, 6, 1, 6, 1, 6, 1, 7, 1, 7, 
	1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 3, 7, 126, 8, 7, 1, 8, 1, 8, 1, 8, 1, 8, 
	1, 8, 1, 8, 1, 8, 1, 8, 1, 8, 1, 9, 1, 9, 1, 10, 1, 10, 1, 11, 1, 11, 1, 
	12, 1, 12, 1, 12, 1, 12, 1, 12, 1, 12, 1, 12, 3, 12, 150, 8, 12, 1, 12, 
	1, 12, 1, 12, 1, 13, 1, 13, 3, 13, 157, 8, 13, 1, 13, 1, 13, 1, 13, 1, 
	13, 1, 13, 1, 14, 1, 14, 5, 14, 166, 8, 14, 10, 14, 12, 14, 169, 9, 14, 
	1, 14, 1, 14, 1, 15, 1, 15, 5, 15, 175, 8, 15, 10, 15, 12, 15, 178, 9, 
	15, 1, 15, 1, 15, 1, 16, 1, 16, 1, 16, 1, 16, 1, 16, 1, 16, 5, 16, 188, 
	8, 16, 10, 16, 12, 16, 191, 9, 16, 1, 17, 1, 17, 1, 17, 5, 17, 196, 8, 
	17, 10, 17, 12, 17, 199, 9, 17, 1, 18, 1, 18, 1, 18, 1, 18, 3, 18, 205, 
	8, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 
	18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 
	3, 18, 227, 8, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 
	18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 5, 18, 244, 8, 18, 
	10, 18, 12, 18, 247, 9, 18, 1, 19, 1, 19, 1, 19, 1, 19, 5, 19, 253, 8, 
	19, 10, 19, 12, 19, 256, 9, 19, 1, 19, 1, 19, 1, 20, 1, 20, 1, 20, 1, 20, 
	1, 20, 1, 20, 1, 113, 1, 36, 21, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 
	22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 0, 11, 1, 0, 41, 46, 1, 0, 47, 
	48, 1, 0, 53, 54, 1, 0, 16, 17, 1, 0, 18, 19, 1, 0, 37, 38, 1, 0, 23, 24, 
	1, 0, 25, 26, 1, 0, 27, 28, 3, 0, 2, 2, 4, 4, 29, 32, 1, 0, 33, 36, 285, 
	0, 45, 1, 0, 0, 0, 2, 66, 1, 0, 0, 0, 4, 89, 1, 0, 0, 0, 6, 91, 1, 0, 0, 
	0, 8, 93, 1, 0, 0, 0, 10, 102, 1, 0, 0, 0, 12, 104, 1, 0, 0, 0, 14, 125, 
	1, 0, 0, 0, 16, 127, 1, 0, 0, 0, 18, 136, 1, 0, 0, 0, 20, 138, 1, 0, 0, 
	0, 22, 140, 1, 0, 0, 0, 24, 142, 1, 0, 0, 0, 26, 154, 1, 0, 0, 0, 28, 163, 
	1, 0, 0, 0, 30, 172, 1, 0, 0, 0, 32, 181, 1, 0, 0, 0, 34, 192, 1, 0, 0, 
	0, 36, 226, 1, 0, 0, 0, 38, 248, 1, 0, 0, 0, 40, 259, 1, 0, 0, 0, 42, 44, 
	3, 2, 1, 0, 43, 42, 1, 0, 0, 0, 44, 47, 1, 0, 0, 0, 45, 43, 1, 0, 0, 0, 
	45, 46, 1, 0, 0, 0, 46, 48, 1, 0, 0, 0, 47, 45, 1, 0, 0, 0, 48, 49, 5, 
	0, 0, 1, 49, 1, 1, 0, 0, 0, 50, 67, 3, 4, 2, 0, 51, 67, 3, 10, 5, 0, 52, 
	67, 3, 12, 6, 0, 53, 67, 3, 16, 8, 0, 54, 67, 3, 24, 12, 0, 55, 56, 3, 
	36, 18, 0, 56, 57, 5, 1, 0, 0, 57, 67, 1, 0, 0, 0, 58, 59, 5, 52, 0, 0, 
	59, 60, 5, 2, 0, 0, 60, 63, 5, 60, 0, 0, 61, 62, 5, 3, 0, 0, 62, 64, 5, 
	60, 0, 0, 63, 61, 1, 0, 0, 0, 63, 64, 1, 0, 0, 0, 64, 65, 1, 0, 0, 0, 65, 
	67, 5, 4, 0, 0, 66, 50, 1, 0, 0, 0, 66, 51, 1, 0, 0, 0, 66, 52, 1, 0, 0, 
	0, 66, 53, 1, 0, 0, 0, 66, 54, 1, 0, 0, 0, 66, 55, 1, 0, 0, 0, 66, 58, 
	1, 0, 0, 0, 67, 3, 1, 0, 0, 0, 68, 69, 3, 8, 4, 0, 69, 70, 3, 6, 3, 0, 
	70, 71, 5, 60, 0, 0, 71, 72, 5, 5, 0, 0, 72, 73, 3, 36, 18, 0, 73, 90, 
	1, 0, 0, 0, 74, 75, 3, 8, 4, 0, 75, 76, 3, 6, 3, 0, 76, 77, 5, 60, 0, 0, 
	77, 79, 5, 6, 0, 0, 78, 80, 5, 55, 0, 0, 79, 78, 1, 0, 0, 0, 79, 80, 1, 
	0, 0, 0, 80, 81, 1, 0, 0, 0, 81, 82, 5, 7, 0, 0, 82, 83, 5, 5, 0, 0, 83, 
	84, 3, 38, 19, 0, 84, 90, 1, 0, 0, 0, 85, 86, 3, 8, 4, 0, 86, 87, 3, 6, 
	3, 0, 87, 88, 5, 60, 0, 0, 88, 90, 1, 0, 0, 0, 89, 68, 1, 0, 0, 0, 89, 
	74, 1, 0, 0, 0, 89, 85, 1, 0, 0, 0, 90, 5, 1, 0, 0, 0, 91, 92, 7, 0, 0, 
	0, 92, 7, 1, 0, 0, 0, 93, 94, 7, 1, 0, 0, 94, 9, 1, 0, 0, 0, 95, 96, 5, 
	60, 0, 0, 96, 97, 5, 5, 0, 0, 97, 103, 3, 36, 18, 0, 98, 99, 5, 60, 0, 
	0, 99, 103, 5, 8, 0, 0, 100, 101, 5, 60, 0, 0, 101, 103, 5, 9, 0, 0, 102, 
	95, 1, 0, 0, 0, 102, 98, 1, 0, 0, 0, 102, 100, 1, 0, 0, 0, 103, 11, 1, 
	0, 0, 0, 104, 105, 5, 10, 0, 0, 105, 106, 3, 36, 18, 0, 106, 107, 5, 11, 
	0, 0, 107, 108, 5, 12, 0, 0, 108, 113, 3, 14, 7, 0, 109, 110, 5, 13, 0, 
	0, 110, 112, 3, 14, 7, 0, 111, 109, 1, 0, 0, 0, 112, 115, 1, 0, 0, 0, 113, 
	114, 1, 0, 0, 0, 113, 111, 1, 0, 0, 0, 114, 116, 1, 0, 0, 0, 115, 113, 
	1, 0, 0, 0, 116, 117, 5, 1, 0, 0, 117, 13, 1, 0, 0, 0, 118, 119, 3, 36, 
	18, 0, 119, 120, 5, 14, 0, 0, 120, 121, 3, 30, 15, 0, 121, 126, 1, 0, 0, 
	0, 122, 123, 5, 15, 0, 0, 123, 124, 5, 14, 0, 0, 124, 126, 3, 30, 15, 0, 
	125, 118, 1, 0, 0, 0, 125, 122, 1, 0, 0, 0, 126, 15, 1, 0, 0, 0, 127, 128, 
	5, 10, 0, 0, 128, 129, 3, 36, 18, 0, 129, 130, 5, 11, 0, 0, 130, 131, 5, 
	13, 0, 0, 131, 132, 3, 18, 9, 0, 132, 133, 3, 20, 10, 0, 133, 134, 3, 30, 
	15, 0, 134, 135, 3, 22, 11, 0, 135, 17, 1, 0, 0, 0, 136, 137, 7, 2, 0, 
	0, 137, 19, 1, 0, 0, 0, 138, 139, 7, 3, 0, 0, 139, 21, 1, 0, 0, 0, 140, 
	141, 7, 4, 0, 0, 141, 23, 1, 0, 0, 0, 142, 143, 5, 49, 0, 0, 143, 144, 
	3, 30, 15, 0, 144, 145, 5, 50, 0, 0, 145, 146, 5, 10, 0, 0, 146, 149, 5, 
	60, 0, 0, 147, 148, 5, 3, 0, 0, 148, 150, 5, 60, 0, 0, 149, 147, 1, 0, 
	0, 0, 149, 150, 1, 0, 0, 0, 150, 151, 1, 0, 0, 0, 151, 152, 5, 11, 0, 0, 
	152, 153, 3, 30, 15, 0, 153, 25, 1, 0, 0, 0, 154, 156, 5, 10, 0, 0, 155, 
	157, 3, 32, 16, 0, 156, 155, 1, 0, 0, 0, 156, 157, 1, 0, 0, 0, 157, 158, 
	1, 0, 0, 0, 158, 159, 5, 11, 0, 0, 159, 160, 5, 13, 0, 0, 160, 161, 3, 
	6, 3, 0, 161, 162, 3, 30, 15, 0, 162, 27, 1, 0, 0, 0, 163, 167, 5, 20, 
	0, 0, 164, 166, 3, 4, 2, 0, 165, 164, 1, 0, 0, 0, 166, 169, 1, 0, 0, 0, 
	167, 165, 1, 0, 0, 0, 167, 168, 1, 0, 0, 0, 168, 170, 1, 0, 0, 0, 169, 
	167, 1, 0, 0, 0, 170, 171, 5, 21, 0, 0, 171, 29, 1, 0, 0, 0, 172, 176, 
	5, 20, 0, 0, 173, 175, 3, 2, 1, 0, 174, 173, 1, 0, 0, 0, 175, 178, 1, 0, 
	0, 0, 176, 174, 1, 0, 0, 0, 176, 177, 1, 0, 0, 0, 177, 179, 1, 0, 0, 0, 
	178, 176, 1, 0, 0, 0, 179, 180, 5, 21, 0, 0, 180, 31, 1, 0, 0, 0, 181, 
	182, 3, 6, 3, 0, 182, 189, 5, 60, 0, 0, 183, 184, 5, 22, 0, 0, 184, 185, 
	3, 6, 3, 0, 185, 186, 5, 60, 0, 0, 186, 188, 1, 0, 0, 0, 187, 183, 1, 0, 
	0, 0, 188, 191, 1, 0, 0, 0, 189, 187, 1, 0, 0, 0, 189, 190, 1, 0, 0, 0, 
	190, 33, 1, 0, 0, 0, 191, 189, 1, 0, 0, 0, 192, 197, 3, 36, 18, 0, 193, 
	194, 5, 22, 0, 0, 194, 196, 3, 36, 18, 0, 195, 193, 1, 0, 0, 0, 196, 199, 
	1, 0, 0, 0, 197, 195, 1, 0, 0, 0, 197, 198, 1, 0, 0, 0, 198, 35, 1, 0, 
	0, 0, 199, 197, 1, 0, 0, 0, 200, 201, 6, 18, -1, 0, 201, 202, 5, 60, 0, 
	0, 202, 204, 5, 10, 0, 0, 203, 205, 3, 34, 17, 0, 204, 203, 1, 0, 0, 0, 
	204, 205, 1, 0, 0, 0, 205, 206, 1, 0, 0, 0, 206, 227, 5, 11, 0, 0, 207, 
	208, 5, 60, 0, 0, 208, 209, 5, 6, 0, 0, 209, 210, 3, 36, 18, 0, 210, 211, 
	5, 7, 0, 0, 211, 227, 1, 0, 0, 0, 212, 213, 7, 5, 0, 0, 213, 227, 3, 36, 
	18, 13, 214, 227, 5, 55, 0, 0, 215, 227, 5, 56, 0, 0, 216, 227, 5, 62, 
	0, 0, 217, 227, 5, 61, 0, 0, 218, 227, 5, 57, 0, 0, 219, 227, 5, 58, 0, 
	0, 220, 227, 5, 59, 0, 0, 221, 227, 3, 38, 19, 0, 222, 227, 3, 40, 20, 
	0, 223, 227, 5, 60, 0, 0, 224, 227, 3, 28, 14, 0, 225, 227, 3, 26, 13, 
	0, 226, 200, 1, 0, 0, 0, 226, 207, 1, 0, 0, 0, 226, 212, 1, 0, 0, 0, 226, 
	214, 1, 0, 0, 0, 226, 215, 1, 0, 0, 0, 226, 216, 1, 0, 0, 0, 226, 217, 
	1, 0, 0, 0, 226, 218, 1, 0, 0, 0, 226, 219, 1, 0, 0, 0, 226, 220, 1, 0, 
	0, 0, 226, 221, 1, 0, 0, 0, 226, 222, 1, 0, 0, 0, 226, 223, 1, 0, 0, 0, 
	226, 224, 1, 0, 0, 0, 226, 225, 1, 0, 0, 0, 227, 245, 1, 0, 0, 0, 228, 
	229, 10, 18, 0, 0, 229, 230, 7, 6, 0, 0, 230, 244, 3, 36, 18, 19, 231, 
	232, 10, 17, 0, 0, 232, 233, 7, 7, 0, 0, 233, 244, 3, 36, 18, 18, 234, 
	235, 10, 16, 0, 0, 235, 236, 7, 8, 0, 0, 236, 244, 3, 36, 18, 17, 237, 
	238, 10, 15, 0, 0, 238, 239, 7, 9, 0, 0, 239, 244, 3, 36, 18, 16, 240, 
	241, 10, 14, 0, 0, 241, 242, 7, 10, 0, 0, 242, 244, 3, 36, 18, 15, 243, 
	228, 1, 0, 0, 0, 243, 231, 1, 0, 0, 0, 243, 234, 1, 0, 0, 0, 243, 237, 
	1, 0, 0, 0, 243, 240, 1, 0, 0, 0, 244, 247, 1, 0, 0, 0, 245, 243, 1, 0, 
	0, 0, 245, 246, 1, 0, 0, 0, 246, 37, 1, 0, 0, 0, 247, 245, 1, 0, 0, 0, 
	248, 249, 5, 39, 0, 0, 249, 254, 3, 36, 18, 0, 250, 251, 5, 22, 0, 0, 251, 
	253, 3, 36, 18, 0, 252, 250, 1, 0, 0, 0, 253, 256, 1, 0, 0, 0, 254, 252, 
	1, 0, 0, 0, 254, 255, 1, 0, 0, 0, 255, 257, 1, 0, 0, 0, 256, 254, 1, 0, 
	0, 0, 257, 258, 5, 40, 0, 0, 258, 39, 1, 0, 0, 0, 259, 260, 5, 60, 0, 0, 
	260, 261, 5, 6, 0, 0, 261, 262, 3, 36, 18, 0, 262, 263, 5, 7, 0, 0, 263, 
	41, 1, 0, 0, 0, 19, 45, 63, 66, 79, 89, 102, 113, 125, 149, 156, 167, 176, 
	189, 197, 204, 226, 243, 245, 254,
}
  deserializer := antlr.NewATNDeserializer(nil)
  staticData.atn = deserializer.Deserialize(staticData.serializedATN)
  atn := staticData.atn
  staticData.decisionToDFA = make([]*antlr.DFA, len(atn.DecisionToState))
  decisionToDFA := staticData.decisionToDFA
  for index, state := range atn.DecisionToState {
    decisionToDFA[index] = antlr.NewDFA(state, index)
  }
}

// PaxoParserInit initializes any static state used to implement PaxoParser. By default the
// static state used to implement the parser is lazily initialized during the first call to
// NewPaxoParser(). You can call this function if you wish to initialize the static state ahead
// of time.
func PaxoParserInit() {
  staticData := &PaxoParserStaticData
  staticData.once.Do(paxoParserInit)
}

// NewPaxoParser produces a new parser instance for the optional input antlr.TokenStream.
func NewPaxoParser(input antlr.TokenStream) *PaxoParser {
	PaxoParserInit()
	this := new(PaxoParser)
	this.BaseParser = antlr.NewBaseParser(input)
  staticData := &PaxoParserStaticData
	this.Interpreter = antlr.NewParserATNSimulator(this, staticData.atn, staticData.decisionToDFA, staticData.PredictionContextCache)
	this.RuleNames = staticData.RuleNames
	this.LiteralNames = staticData.LiteralNames
	this.SymbolicNames = staticData.SymbolicNames
	this.GrammarFileName = "Paxo.g4"

	return this
}


// PaxoParser tokens.
const (
	PaxoParserEOF = antlr.TokenEOF
	PaxoParserT__0 = 1
	PaxoParserT__1 = 2
	PaxoParserT__2 = 3
	PaxoParserT__3 = 4
	PaxoParserT__4 = 5
	PaxoParserT__5 = 6
	PaxoParserT__6 = 7
	PaxoParserT__7 = 8
	PaxoParserT__8 = 9
	PaxoParserT__9 = 10
	PaxoParserT__10 = 11
	PaxoParserT__11 = 12
	PaxoParserT__12 = 13
	PaxoParserT__13 = 14
	PaxoParserT__14 = 15
	PaxoParserT__15 = 16
	PaxoParserT__16 = 17
	PaxoParserT__17 = 18
	PaxoParserT__18 = 19
	PaxoParserT__19 = 20
	PaxoParserT__20 = 21
	PaxoParserT__21 = 22
	PaxoParserT__22 = 23
	PaxoParserT__23 = 24
	PaxoParserT__24 = 25
	PaxoParserT__25 = 26
	PaxoParserT__26 = 27
	PaxoParserT__27 = 28
	PaxoParserT__28 = 29
	PaxoParserT__29 = 30
	PaxoParserT__30 = 31
	PaxoParserT__31 = 32
	PaxoParserT__32 = 33
	PaxoParserT__33 = 34
	PaxoParserT__34 = 35
	PaxoParserT__35 = 36
	PaxoParserT__36 = 37
	PaxoParserT__37 = 38
	PaxoParserT__38 = 39
	PaxoParserT__39 = 40
	PaxoParserVAR_TYPE = 41
	PaxoParserNUM_TYPE = 42
	PaxoParserCHARA_TYPE = 43
	PaxoParserTRIT_TYPE = 44
	PaxoParserBOOLEAN_TYPE = 45
	PaxoParserPOINTER_TYPE = 46
	PaxoParserGLOBAL = 47
	PaxoParserLOCAL = 48
	PaxoParserTRY = 49
	PaxoParserCATCH = 50
	PaxoParserARROW = 51
	PaxoParserINCLUDE = 52
	PaxoParserPAUSE_MODE = 53
	PaxoParserPLAY_MODE = 54
	PaxoParserINT_LITERAL = 55
	PaxoParserDECIMAL_LITERAL = 56
	PaxoParserBOOLEAN_BIT = 57
	PaxoParserBOOLEAN_TRIT = 58
	PaxoParserPOINTER_LITERAL = 59
	PaxoParserIDENTIFIER = 60
	PaxoParserSTRING_LITERAL = 61
	PaxoParserCHAR_LITERAL = 62
	PaxoParserLINE_COMMENT = 63
	PaxoParserBLOCK_COMMENT = 64
	PaxoParserWS = 65
)

// PaxoParser rules.
const (
	PaxoParserRULE_program = 0
	PaxoParserRULE_statement = 1
	PaxoParserRULE_varDeclaration = 2
	PaxoParserRULE_type = 3
	PaxoParserRULE_scope = 4
	PaxoParserRULE_assignment = 5
	PaxoParserRULE_condStatement = 6
	PaxoParserRULE_matchCase = 7
	PaxoParserRULE_loopStatement = 8
	PaxoParserRULE_loopMode = 9
	PaxoParserRULE_loopDelimiter = 10
	PaxoParserRULE_loopEndDelimiter = 11
	PaxoParserRULE_tryCatchStatement = 12
	PaxoParserRULE_functionDeclaration = 13
	PaxoParserRULE_pkgDeclaration = 14
	PaxoParserRULE_block = 15
	PaxoParserRULE_parameterList = 16
	PaxoParserRULE_argumentList = 17
	PaxoParserRULE_expression = 18
	PaxoParserRULE_arrayLiteral = 19
	PaxoParserRULE_arrayAccess = 20
)

// IProgramContext is an interface to support dynamic dispatch.
type IProgramContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	EOF() antlr.TerminalNode
	AllStatement() []IStatementContext
	Statement(i int) IStatementContext

	// IsProgramContext differentiates from other interfaces.
	IsProgramContext()
}

type ProgramContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyProgramContext() *ProgramContext {
	var p = new(ProgramContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_program
	return p
}

func InitEmptyProgramContext(p *ProgramContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_program
}

func (*ProgramContext) IsProgramContext() {}

func NewProgramContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *ProgramContext {
	var p = new(ProgramContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_program

	return p
}

func (s *ProgramContext) GetParser() antlr.Parser { return s.parser }

func (s *ProgramContext) EOF() antlr.TerminalNode {
	return s.GetToken(PaxoParserEOF, 0)
}

func (s *ProgramContext) AllStatement() []IStatementContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IStatementContext); ok {
			len++
		}
	}

	tst := make([]IStatementContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IStatementContext); ok {
			tst[i] = t.(IStatementContext)
			i++
		}
	}

	return tst
}

func (s *ProgramContext) Statement(i int) IStatementContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IStatementContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IStatementContext)
}

func (s *ProgramContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ProgramContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *ProgramContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterProgram(s)
	}
}

func (s *ProgramContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitProgram(s)
	}
}




func (p *PaxoParser) Program() (localctx IProgramContext) {
	localctx = NewProgramContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 0, PaxoParserRULE_program)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	p.SetState(45)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 9192832963955393536) != 0) {
		{
			p.SetState(42)
			p.Statement()
		}


		p.SetState(47)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_la = p.GetTokenStream().LA(1)
	}
	{
		p.SetState(48)
		p.Match(PaxoParserEOF)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IStatementContext is an interface to support dynamic dispatch.
type IStatementContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	VarDeclaration() IVarDeclarationContext
	Assignment() IAssignmentContext
	CondStatement() ICondStatementContext
	LoopStatement() ILoopStatementContext
	TryCatchStatement() ITryCatchStatementContext
	Expression() IExpressionContext
	INCLUDE() antlr.TerminalNode
	AllIDENTIFIER() []antlr.TerminalNode
	IDENTIFIER(i int) antlr.TerminalNode

	// IsStatementContext differentiates from other interfaces.
	IsStatementContext()
}

type StatementContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyStatementContext() *StatementContext {
	var p = new(StatementContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_statement
	return p
}

func InitEmptyStatementContext(p *StatementContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_statement
}

func (*StatementContext) IsStatementContext() {}

func NewStatementContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *StatementContext {
	var p = new(StatementContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_statement

	return p
}

func (s *StatementContext) GetParser() antlr.Parser { return s.parser }

func (s *StatementContext) VarDeclaration() IVarDeclarationContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IVarDeclarationContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IVarDeclarationContext)
}

func (s *StatementContext) Assignment() IAssignmentContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IAssignmentContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IAssignmentContext)
}

func (s *StatementContext) CondStatement() ICondStatementContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(ICondStatementContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(ICondStatementContext)
}

func (s *StatementContext) LoopStatement() ILoopStatementContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(ILoopStatementContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(ILoopStatementContext)
}

func (s *StatementContext) TryCatchStatement() ITryCatchStatementContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(ITryCatchStatementContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(ITryCatchStatementContext)
}

func (s *StatementContext) Expression() IExpressionContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}

func (s *StatementContext) INCLUDE() antlr.TerminalNode {
	return s.GetToken(PaxoParserINCLUDE, 0)
}

func (s *StatementContext) AllIDENTIFIER() []antlr.TerminalNode {
	return s.GetTokens(PaxoParserIDENTIFIER)
}

func (s *StatementContext) IDENTIFIER(i int) antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, i)
}

func (s *StatementContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *StatementContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *StatementContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterStatement(s)
	}
}

func (s *StatementContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitStatement(s)
	}
}




func (p *PaxoParser) Statement() (localctx IStatementContext) {
	localctx = NewStatementContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 2, PaxoParserRULE_statement)
	var _la int

	p.SetState(66)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 2, p.GetParserRuleContext()) {
	case 1:
		p.EnterOuterAlt(localctx, 1)
		{
			p.SetState(50)
			p.VarDeclaration()
		}


	case 2:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(51)
			p.Assignment()
		}


	case 3:
		p.EnterOuterAlt(localctx, 3)
		{
			p.SetState(52)
			p.CondStatement()
		}


	case 4:
		p.EnterOuterAlt(localctx, 4)
		{
			p.SetState(53)
			p.LoopStatement()
		}


	case 5:
		p.EnterOuterAlt(localctx, 5)
		{
			p.SetState(54)
			p.TryCatchStatement()
		}


	case 6:
		p.EnterOuterAlt(localctx, 6)
		{
			p.SetState(55)
			p.expression(0)
		}
		{
			p.SetState(56)
			p.Match(PaxoParserT__0)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 7:
		p.EnterOuterAlt(localctx, 7)
		{
			p.SetState(58)
			p.Match(PaxoParserINCLUDE)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(59)
			p.Match(PaxoParserT__1)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(60)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(63)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		if _la == PaxoParserT__2 {
			{
				p.SetState(61)
				p.Match(PaxoParserT__2)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(62)
				p.Match(PaxoParserIDENTIFIER)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

		}
		{
			p.SetState(65)
			p.Match(PaxoParserT__3)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}

	case antlr.ATNInvalidAltNumber:
		goto errorExit
	}


errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IVarDeclarationContext is an interface to support dynamic dispatch.
type IVarDeclarationContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	Scope() IScopeContext
	Type_() ITypeContext
	IDENTIFIER() antlr.TerminalNode
	Expression() IExpressionContext
	ArrayLiteral() IArrayLiteralContext
	INT_LITERAL() antlr.TerminalNode

	// IsVarDeclarationContext differentiates from other interfaces.
	IsVarDeclarationContext()
}

type VarDeclarationContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyVarDeclarationContext() *VarDeclarationContext {
	var p = new(VarDeclarationContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_varDeclaration
	return p
}

func InitEmptyVarDeclarationContext(p *VarDeclarationContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_varDeclaration
}

func (*VarDeclarationContext) IsVarDeclarationContext() {}

func NewVarDeclarationContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *VarDeclarationContext {
	var p = new(VarDeclarationContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_varDeclaration

	return p
}

func (s *VarDeclarationContext) GetParser() antlr.Parser { return s.parser }

func (s *VarDeclarationContext) Scope() IScopeContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IScopeContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IScopeContext)
}

func (s *VarDeclarationContext) Type_() ITypeContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(ITypeContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(ITypeContext)
}

func (s *VarDeclarationContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}

func (s *VarDeclarationContext) Expression() IExpressionContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}

func (s *VarDeclarationContext) ArrayLiteral() IArrayLiteralContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IArrayLiteralContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IArrayLiteralContext)
}

func (s *VarDeclarationContext) INT_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserINT_LITERAL, 0)
}

func (s *VarDeclarationContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *VarDeclarationContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *VarDeclarationContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterVarDeclaration(s)
	}
}

func (s *VarDeclarationContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitVarDeclaration(s)
	}
}




func (p *PaxoParser) VarDeclaration() (localctx IVarDeclarationContext) {
	localctx = NewVarDeclarationContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 4, PaxoParserRULE_varDeclaration)
	var _la int

	p.SetState(89)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 4, p.GetParserRuleContext()) {
	case 1:
		p.EnterOuterAlt(localctx, 1)
		{
			p.SetState(68)
			p.Scope()
		}
		{
			p.SetState(69)
			p.Type_()
		}
		{
			p.SetState(70)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(71)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(72)
			p.expression(0)
		}


	case 2:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(74)
			p.Scope()
		}
		{
			p.SetState(75)
			p.Type_()
		}
		{
			p.SetState(76)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(77)
			p.Match(PaxoParserT__5)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(79)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		if _la == PaxoParserINT_LITERAL {
			{
				p.SetState(78)
				p.Match(PaxoParserINT_LITERAL)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

		}
		{
			p.SetState(81)
			p.Match(PaxoParserT__6)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(82)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(83)
			p.ArrayLiteral()
		}


	case 3:
		p.EnterOuterAlt(localctx, 3)
		{
			p.SetState(85)
			p.Scope()
		}
		{
			p.SetState(86)
			p.Type_()
		}
		{
			p.SetState(87)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}

	case antlr.ATNInvalidAltNumber:
		goto errorExit
	}


errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// ITypeContext is an interface to support dynamic dispatch.
type ITypeContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	VAR_TYPE() antlr.TerminalNode
	NUM_TYPE() antlr.TerminalNode
	CHARA_TYPE() antlr.TerminalNode
	POINTER_TYPE() antlr.TerminalNode
	TRIT_TYPE() antlr.TerminalNode
	BOOLEAN_TYPE() antlr.TerminalNode

	// IsTypeContext differentiates from other interfaces.
	IsTypeContext()
}

type TypeContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyTypeContext() *TypeContext {
	var p = new(TypeContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_type
	return p
}

func InitEmptyTypeContext(p *TypeContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_type
}

func (*TypeContext) IsTypeContext() {}

func NewTypeContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *TypeContext {
	var p = new(TypeContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_type

	return p
}

func (s *TypeContext) GetParser() antlr.Parser { return s.parser }

func (s *TypeContext) VAR_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserVAR_TYPE, 0)
}

func (s *TypeContext) NUM_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserNUM_TYPE, 0)
}

func (s *TypeContext) CHARA_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserCHARA_TYPE, 0)
}

func (s *TypeContext) POINTER_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserPOINTER_TYPE, 0)
}

func (s *TypeContext) TRIT_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserTRIT_TYPE, 0)
}

func (s *TypeContext) BOOLEAN_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserBOOLEAN_TYPE, 0)
}

func (s *TypeContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *TypeContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *TypeContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterType(s)
	}
}

func (s *TypeContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitType(s)
	}
}




func (p *PaxoParser) Type_() (localctx ITypeContext) {
	localctx = NewTypeContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 6, PaxoParserRULE_type)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(91)
		_la = p.GetTokenStream().LA(1)

		if !(((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 138538465099776) != 0)) {
			p.GetErrorHandler().RecoverInline(p)
		} else {
			p.GetErrorHandler().ReportMatch(p)
			p.Consume()
		}
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IScopeContext is an interface to support dynamic dispatch.
type IScopeContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	GLOBAL() antlr.TerminalNode
	LOCAL() antlr.TerminalNode

	// IsScopeContext differentiates from other interfaces.
	IsScopeContext()
}

type ScopeContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyScopeContext() *ScopeContext {
	var p = new(ScopeContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_scope
	return p
}

func InitEmptyScopeContext(p *ScopeContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_scope
}

func (*ScopeContext) IsScopeContext() {}

func NewScopeContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *ScopeContext {
	var p = new(ScopeContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_scope

	return p
}

func (s *ScopeContext) GetParser() antlr.Parser { return s.parser }

func (s *ScopeContext) GLOBAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserGLOBAL, 0)
}

func (s *ScopeContext) LOCAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserLOCAL, 0)
}

func (s *ScopeContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ScopeContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *ScopeContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterScope(s)
	}
}

func (s *ScopeContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitScope(s)
	}
}




func (p *PaxoParser) Scope() (localctx IScopeContext) {
	localctx = NewScopeContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 8, PaxoParserRULE_scope)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(93)
		_la = p.GetTokenStream().LA(1)

		if !(_la == PaxoParserGLOBAL || _la == PaxoParserLOCAL) {
			p.GetErrorHandler().RecoverInline(p)
		} else {
			p.GetErrorHandler().ReportMatch(p)
			p.Consume()
		}
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IAssignmentContext is an interface to support dynamic dispatch.
type IAssignmentContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	IDENTIFIER() antlr.TerminalNode
	Expression() IExpressionContext

	// IsAssignmentContext differentiates from other interfaces.
	IsAssignmentContext()
}

type AssignmentContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyAssignmentContext() *AssignmentContext {
	var p = new(AssignmentContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_assignment
	return p
}

func InitEmptyAssignmentContext(p *AssignmentContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_assignment
}

func (*AssignmentContext) IsAssignmentContext() {}

func NewAssignmentContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *AssignmentContext {
	var p = new(AssignmentContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_assignment

	return p
}

func (s *AssignmentContext) GetParser() antlr.Parser { return s.parser }

func (s *AssignmentContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}

func (s *AssignmentContext) Expression() IExpressionContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}

func (s *AssignmentContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *AssignmentContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *AssignmentContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterAssignment(s)
	}
}

func (s *AssignmentContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitAssignment(s)
	}
}




func (p *PaxoParser) Assignment() (localctx IAssignmentContext) {
	localctx = NewAssignmentContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 10, PaxoParserRULE_assignment)
	p.SetState(102)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 5, p.GetParserRuleContext()) {
	case 1:
		p.EnterOuterAlt(localctx, 1)
		{
			p.SetState(95)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(96)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(97)
			p.expression(0)
		}


	case 2:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(98)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(99)
			p.Match(PaxoParserT__7)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 3:
		p.EnterOuterAlt(localctx, 3)
		{
			p.SetState(100)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(101)
			p.Match(PaxoParserT__8)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}

	case antlr.ATNInvalidAltNumber:
		goto errorExit
	}


errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// ICondStatementContext is an interface to support dynamic dispatch.
type ICondStatementContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	Expression() IExpressionContext
	AllMatchCase() []IMatchCaseContext
	MatchCase(i int) IMatchCaseContext

	// IsCondStatementContext differentiates from other interfaces.
	IsCondStatementContext()
}

type CondStatementContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyCondStatementContext() *CondStatementContext {
	var p = new(CondStatementContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_condStatement
	return p
}

func InitEmptyCondStatementContext(p *CondStatementContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_condStatement
}

func (*CondStatementContext) IsCondStatementContext() {}

func NewCondStatementContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *CondStatementContext {
	var p = new(CondStatementContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_condStatement

	return p
}

func (s *CondStatementContext) GetParser() antlr.Parser { return s.parser }

func (s *CondStatementContext) Expression() IExpressionContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}

func (s *CondStatementContext) AllMatchCase() []IMatchCaseContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IMatchCaseContext); ok {
			len++
		}
	}

	tst := make([]IMatchCaseContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IMatchCaseContext); ok {
			tst[i] = t.(IMatchCaseContext)
			i++
		}
	}

	return tst
}

func (s *CondStatementContext) MatchCase(i int) IMatchCaseContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IMatchCaseContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IMatchCaseContext)
}

func (s *CondStatementContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *CondStatementContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *CondStatementContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterCondStatement(s)
	}
}

func (s *CondStatementContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitCondStatement(s)
	}
}




func (p *PaxoParser) CondStatement() (localctx ICondStatementContext) {
	localctx = NewCondStatementContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 12, PaxoParserRULE_condStatement)
	var _alt int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(104)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(105)
		p.expression(0)
	}
	{
		p.SetState(106)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(107)
		p.Match(PaxoParserT__11)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(108)
		p.MatchCase()
	}
	p.SetState(113)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 6, p.GetParserRuleContext())
	if p.HasError() {
		goto errorExit
	}
	for _alt != 1 && _alt != antlr.ATNInvalidAltNumber {
		if _alt == 1+1 {
			{
				p.SetState(109)
				p.Match(PaxoParserT__12)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(110)
				p.MatchCase()
			}


		}
		p.SetState(115)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 6, p.GetParserRuleContext())
		if p.HasError() {
			goto errorExit
		}
	}
	{
		p.SetState(116)
		p.Match(PaxoParserT__0)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IMatchCaseContext is an interface to support dynamic dispatch.
type IMatchCaseContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	Expression() IExpressionContext
	Block() IBlockContext

	// IsMatchCaseContext differentiates from other interfaces.
	IsMatchCaseContext()
}

type MatchCaseContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyMatchCaseContext() *MatchCaseContext {
	var p = new(MatchCaseContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_matchCase
	return p
}

func InitEmptyMatchCaseContext(p *MatchCaseContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_matchCase
}

func (*MatchCaseContext) IsMatchCaseContext() {}

func NewMatchCaseContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *MatchCaseContext {
	var p = new(MatchCaseContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_matchCase

	return p
}

func (s *MatchCaseContext) GetParser() antlr.Parser { return s.parser }

func (s *MatchCaseContext) Expression() IExpressionContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}

func (s *MatchCaseContext) Block() IBlockContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IBlockContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IBlockContext)
}

func (s *MatchCaseContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *MatchCaseContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *MatchCaseContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterMatchCase(s)
	}
}

func (s *MatchCaseContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitMatchCase(s)
	}
}




func (p *PaxoParser) MatchCase() (localctx IMatchCaseContext) {
	localctx = NewMatchCaseContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 14, PaxoParserRULE_matchCase)
	p.SetState(125)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetTokenStream().LA(1) {
	case PaxoParserT__9, PaxoParserT__19, PaxoParserT__36, PaxoParserT__37, PaxoParserT__38, PaxoParserINT_LITERAL, PaxoParserDECIMAL_LITERAL, PaxoParserBOOLEAN_BIT, PaxoParserBOOLEAN_TRIT, PaxoParserPOINTER_LITERAL, PaxoParserIDENTIFIER, PaxoParserSTRING_LITERAL, PaxoParserCHAR_LITERAL:
		p.EnterOuterAlt(localctx, 1)
		{
			p.SetState(118)
			p.expression(0)
		}
		{
			p.SetState(119)
			p.Match(PaxoParserT__13)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(120)
			p.Block()
		}


	case PaxoParserT__14:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(122)
			p.Match(PaxoParserT__14)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(123)
			p.Match(PaxoParserT__13)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(124)
			p.Block()
		}



	default:
		p.SetError(antlr.NewNoViableAltException(p, nil, nil, nil, nil, nil))
		goto errorExit
	}


errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// ILoopStatementContext is an interface to support dynamic dispatch.
type ILoopStatementContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	Expression() IExpressionContext
	LoopMode() ILoopModeContext
	LoopDelimiter() ILoopDelimiterContext
	Block() IBlockContext
	LoopEndDelimiter() ILoopEndDelimiterContext

	// IsLoopStatementContext differentiates from other interfaces.
	IsLoopStatementContext()
}

type LoopStatementContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyLoopStatementContext() *LoopStatementContext {
	var p = new(LoopStatementContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_loopStatement
	return p
}

func InitEmptyLoopStatementContext(p *LoopStatementContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_loopStatement
}

func (*LoopStatementContext) IsLoopStatementContext() {}

func NewLoopStatementContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *LoopStatementContext {
	var p = new(LoopStatementContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_loopStatement

	return p
}

func (s *LoopStatementContext) GetParser() antlr.Parser { return s.parser }

func (s *LoopStatementContext) Expression() IExpressionContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}

func (s *LoopStatementContext) LoopMode() ILoopModeContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(ILoopModeContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(ILoopModeContext)
}

func (s *LoopStatementContext) LoopDelimiter() ILoopDelimiterContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(ILoopDelimiterContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(ILoopDelimiterContext)
}

func (s *LoopStatementContext) Block() IBlockContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IBlockContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IBlockContext)
}

func (s *LoopStatementContext) LoopEndDelimiter() ILoopEndDelimiterContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(ILoopEndDelimiterContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(ILoopEndDelimiterContext)
}

func (s *LoopStatementContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *LoopStatementContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *LoopStatementContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterLoopStatement(s)
	}
}

func (s *LoopStatementContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitLoopStatement(s)
	}
}




func (p *PaxoParser) LoopStatement() (localctx ILoopStatementContext) {
	localctx = NewLoopStatementContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 16, PaxoParserRULE_loopStatement)
	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(127)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(128)
		p.expression(0)
	}
	{
		p.SetState(129)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(130)
		p.Match(PaxoParserT__12)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(131)
		p.LoopMode()
	}
	{
		p.SetState(132)
		p.LoopDelimiter()
	}
	{
		p.SetState(133)
		p.Block()
	}
	{
		p.SetState(134)
		p.LoopEndDelimiter()
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// ILoopModeContext is an interface to support dynamic dispatch.
type ILoopModeContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	PAUSE_MODE() antlr.TerminalNode
	PLAY_MODE() antlr.TerminalNode

	// IsLoopModeContext differentiates from other interfaces.
	IsLoopModeContext()
}

type LoopModeContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyLoopModeContext() *LoopModeContext {
	var p = new(LoopModeContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_loopMode
	return p
}

func InitEmptyLoopModeContext(p *LoopModeContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_loopMode
}

func (*LoopModeContext) IsLoopModeContext() {}

func NewLoopModeContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *LoopModeContext {
	var p = new(LoopModeContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_loopMode

	return p
}

func (s *LoopModeContext) GetParser() antlr.Parser { return s.parser }

func (s *LoopModeContext) PAUSE_MODE() antlr.TerminalNode {
	return s.GetToken(PaxoParserPAUSE_MODE, 0)
}

func (s *LoopModeContext) PLAY_MODE() antlr.TerminalNode {
	return s.GetToken(PaxoParserPLAY_MODE, 0)
}

func (s *LoopModeContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *LoopModeContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *LoopModeContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterLoopMode(s)
	}
}

func (s *LoopModeContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitLoopMode(s)
	}
}




func (p *PaxoParser) LoopMode() (localctx ILoopModeContext) {
	localctx = NewLoopModeContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 18, PaxoParserRULE_loopMode)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(136)
		_la = p.GetTokenStream().LA(1)

		if !(_la == PaxoParserPAUSE_MODE || _la == PaxoParserPLAY_MODE) {
			p.GetErrorHandler().RecoverInline(p)
		} else {
			p.GetErrorHandler().ReportMatch(p)
			p.Consume()
		}
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// ILoopDelimiterContext is an interface to support dynamic dispatch.
type ILoopDelimiterContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser
	// IsLoopDelimiterContext differentiates from other interfaces.
	IsLoopDelimiterContext()
}

type LoopDelimiterContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyLoopDelimiterContext() *LoopDelimiterContext {
	var p = new(LoopDelimiterContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_loopDelimiter
	return p
}

func InitEmptyLoopDelimiterContext(p *LoopDelimiterContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_loopDelimiter
}

func (*LoopDelimiterContext) IsLoopDelimiterContext() {}

func NewLoopDelimiterContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *LoopDelimiterContext {
	var p = new(LoopDelimiterContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_loopDelimiter

	return p
}

func (s *LoopDelimiterContext) GetParser() antlr.Parser { return s.parser }
func (s *LoopDelimiterContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *LoopDelimiterContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *LoopDelimiterContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterLoopDelimiter(s)
	}
}

func (s *LoopDelimiterContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitLoopDelimiter(s)
	}
}




func (p *PaxoParser) LoopDelimiter() (localctx ILoopDelimiterContext) {
	localctx = NewLoopDelimiterContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 20, PaxoParserRULE_loopDelimiter)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(138)
		_la = p.GetTokenStream().LA(1)

		if !(_la == PaxoParserT__15 || _la == PaxoParserT__16) {
			p.GetErrorHandler().RecoverInline(p)
		} else {
			p.GetErrorHandler().ReportMatch(p)
			p.Consume()
		}
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// ILoopEndDelimiterContext is an interface to support dynamic dispatch.
type ILoopEndDelimiterContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser
	// IsLoopEndDelimiterContext differentiates from other interfaces.
	IsLoopEndDelimiterContext()
}

type LoopEndDelimiterContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyLoopEndDelimiterContext() *LoopEndDelimiterContext {
	var p = new(LoopEndDelimiterContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_loopEndDelimiter
	return p
}

func InitEmptyLoopEndDelimiterContext(p *LoopEndDelimiterContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_loopEndDelimiter
}

func (*LoopEndDelimiterContext) IsLoopEndDelimiterContext() {}

func NewLoopEndDelimiterContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *LoopEndDelimiterContext {
	var p = new(LoopEndDelimiterContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_loopEndDelimiter

	return p
}

func (s *LoopEndDelimiterContext) GetParser() antlr.Parser { return s.parser }
func (s *LoopEndDelimiterContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *LoopEndDelimiterContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *LoopEndDelimiterContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterLoopEndDelimiter(s)
	}
}

func (s *LoopEndDelimiterContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitLoopEndDelimiter(s)
	}
}




func (p *PaxoParser) LoopEndDelimiter() (localctx ILoopEndDelimiterContext) {
	localctx = NewLoopEndDelimiterContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 22, PaxoParserRULE_loopEndDelimiter)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(140)
		_la = p.GetTokenStream().LA(1)

		if !(_la == PaxoParserT__17 || _la == PaxoParserT__18) {
			p.GetErrorHandler().RecoverInline(p)
		} else {
			p.GetErrorHandler().ReportMatch(p)
			p.Consume()
		}
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// ITryCatchStatementContext is an interface to support dynamic dispatch.
type ITryCatchStatementContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	TRY() antlr.TerminalNode
	AllBlock() []IBlockContext
	Block(i int) IBlockContext
	CATCH() antlr.TerminalNode
	AllIDENTIFIER() []antlr.TerminalNode
	IDENTIFIER(i int) antlr.TerminalNode

	// IsTryCatchStatementContext differentiates from other interfaces.
	IsTryCatchStatementContext()
}

type TryCatchStatementContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyTryCatchStatementContext() *TryCatchStatementContext {
	var p = new(TryCatchStatementContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_tryCatchStatement
	return p
}

func InitEmptyTryCatchStatementContext(p *TryCatchStatementContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_tryCatchStatement
}

func (*TryCatchStatementContext) IsTryCatchStatementContext() {}

func NewTryCatchStatementContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *TryCatchStatementContext {
	var p = new(TryCatchStatementContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_tryCatchStatement

	return p
}

func (s *TryCatchStatementContext) GetParser() antlr.Parser { return s.parser }

func (s *TryCatchStatementContext) TRY() antlr.TerminalNode {
	return s.GetToken(PaxoParserTRY, 0)
}

func (s *TryCatchStatementContext) AllBlock() []IBlockContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IBlockContext); ok {
			len++
		}
	}

	tst := make([]IBlockContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IBlockContext); ok {
			tst[i] = t.(IBlockContext)
			i++
		}
	}

	return tst
}

func (s *TryCatchStatementContext) Block(i int) IBlockContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IBlockContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IBlockContext)
}

func (s *TryCatchStatementContext) CATCH() antlr.TerminalNode {
	return s.GetToken(PaxoParserCATCH, 0)
}

func (s *TryCatchStatementContext) AllIDENTIFIER() []antlr.TerminalNode {
	return s.GetTokens(PaxoParserIDENTIFIER)
}

func (s *TryCatchStatementContext) IDENTIFIER(i int) antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, i)
}

func (s *TryCatchStatementContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *TryCatchStatementContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *TryCatchStatementContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterTryCatchStatement(s)
	}
}

func (s *TryCatchStatementContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitTryCatchStatement(s)
	}
}




func (p *PaxoParser) TryCatchStatement() (localctx ITryCatchStatementContext) {
	localctx = NewTryCatchStatementContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 24, PaxoParserRULE_tryCatchStatement)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(142)
		p.Match(PaxoParserTRY)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(143)
		p.Block()
	}
	{
		p.SetState(144)
		p.Match(PaxoParserCATCH)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(145)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(146)
		p.Match(PaxoParserIDENTIFIER)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(149)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	if _la == PaxoParserT__2 {
		{
			p.SetState(147)
			p.Match(PaxoParserT__2)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(148)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}

	}
	{
		p.SetState(151)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(152)
		p.Block()
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IFunctionDeclarationContext is an interface to support dynamic dispatch.
type IFunctionDeclarationContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	Type_() ITypeContext
	Block() IBlockContext
	ParameterList() IParameterListContext

	// IsFunctionDeclarationContext differentiates from other interfaces.
	IsFunctionDeclarationContext()
}

type FunctionDeclarationContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyFunctionDeclarationContext() *FunctionDeclarationContext {
	var p = new(FunctionDeclarationContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_functionDeclaration
	return p
}

func InitEmptyFunctionDeclarationContext(p *FunctionDeclarationContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_functionDeclaration
}

func (*FunctionDeclarationContext) IsFunctionDeclarationContext() {}

func NewFunctionDeclarationContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *FunctionDeclarationContext {
	var p = new(FunctionDeclarationContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_functionDeclaration

	return p
}

func (s *FunctionDeclarationContext) GetParser() antlr.Parser { return s.parser }

func (s *FunctionDeclarationContext) Type_() ITypeContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(ITypeContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(ITypeContext)
}

func (s *FunctionDeclarationContext) Block() IBlockContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IBlockContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IBlockContext)
}

func (s *FunctionDeclarationContext) ParameterList() IParameterListContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IParameterListContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IParameterListContext)
}

func (s *FunctionDeclarationContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *FunctionDeclarationContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *FunctionDeclarationContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterFunctionDeclaration(s)
	}
}

func (s *FunctionDeclarationContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitFunctionDeclaration(s)
	}
}




func (p *PaxoParser) FunctionDeclaration() (localctx IFunctionDeclarationContext) {
	localctx = NewFunctionDeclarationContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 26, PaxoParserRULE_functionDeclaration)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(154)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(156)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	if ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 138538465099776) != 0) {
		{
			p.SetState(155)
			p.ParameterList()
		}

	}
	{
		p.SetState(158)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(159)
		p.Match(PaxoParserT__12)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(160)
		p.Type_()
	}
	{
		p.SetState(161)
		p.Block()
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IPkgDeclarationContext is an interface to support dynamic dispatch.
type IPkgDeclarationContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	AllVarDeclaration() []IVarDeclarationContext
	VarDeclaration(i int) IVarDeclarationContext

	// IsPkgDeclarationContext differentiates from other interfaces.
	IsPkgDeclarationContext()
}

type PkgDeclarationContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyPkgDeclarationContext() *PkgDeclarationContext {
	var p = new(PkgDeclarationContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_pkgDeclaration
	return p
}

func InitEmptyPkgDeclarationContext(p *PkgDeclarationContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_pkgDeclaration
}

func (*PkgDeclarationContext) IsPkgDeclarationContext() {}

func NewPkgDeclarationContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *PkgDeclarationContext {
	var p = new(PkgDeclarationContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_pkgDeclaration

	return p
}

func (s *PkgDeclarationContext) GetParser() antlr.Parser { return s.parser }

func (s *PkgDeclarationContext) AllVarDeclaration() []IVarDeclarationContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IVarDeclarationContext); ok {
			len++
		}
	}

	tst := make([]IVarDeclarationContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IVarDeclarationContext); ok {
			tst[i] = t.(IVarDeclarationContext)
			i++
		}
	}

	return tst
}

func (s *PkgDeclarationContext) VarDeclaration(i int) IVarDeclarationContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IVarDeclarationContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IVarDeclarationContext)
}

func (s *PkgDeclarationContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *PkgDeclarationContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *PkgDeclarationContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterPkgDeclaration(s)
	}
}

func (s *PkgDeclarationContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitPkgDeclaration(s)
	}
}




func (p *PaxoParser) PkgDeclaration() (localctx IPkgDeclarationContext) {
	localctx = NewPkgDeclarationContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 28, PaxoParserRULE_pkgDeclaration)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(163)
		p.Match(PaxoParserT__19)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(167)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for _la == PaxoParserGLOBAL || _la == PaxoParserLOCAL {
		{
			p.SetState(164)
			p.VarDeclaration()
		}


		p.SetState(169)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_la = p.GetTokenStream().LA(1)
	}
	{
		p.SetState(170)
		p.Match(PaxoParserT__20)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IBlockContext is an interface to support dynamic dispatch.
type IBlockContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	AllStatement() []IStatementContext
	Statement(i int) IStatementContext

	// IsBlockContext differentiates from other interfaces.
	IsBlockContext()
}

type BlockContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyBlockContext() *BlockContext {
	var p = new(BlockContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_block
	return p
}

func InitEmptyBlockContext(p *BlockContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_block
}

func (*BlockContext) IsBlockContext() {}

func NewBlockContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *BlockContext {
	var p = new(BlockContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_block

	return p
}

func (s *BlockContext) GetParser() antlr.Parser { return s.parser }

func (s *BlockContext) AllStatement() []IStatementContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IStatementContext); ok {
			len++
		}
	}

	tst := make([]IStatementContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IStatementContext); ok {
			tst[i] = t.(IStatementContext)
			i++
		}
	}

	return tst
}

func (s *BlockContext) Statement(i int) IStatementContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IStatementContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IStatementContext)
}

func (s *BlockContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *BlockContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *BlockContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterBlock(s)
	}
}

func (s *BlockContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitBlock(s)
	}
}




func (p *PaxoParser) Block() (localctx IBlockContext) {
	localctx = NewBlockContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 30, PaxoParserRULE_block)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(172)
		p.Match(PaxoParserT__19)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(176)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 9192832963955393536) != 0) {
		{
			p.SetState(173)
			p.Statement()
		}


		p.SetState(178)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_la = p.GetTokenStream().LA(1)
	}
	{
		p.SetState(179)
		p.Match(PaxoParserT__20)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IParameterListContext is an interface to support dynamic dispatch.
type IParameterListContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	AllType_() []ITypeContext
	Type_(i int) ITypeContext
	AllIDENTIFIER() []antlr.TerminalNode
	IDENTIFIER(i int) antlr.TerminalNode

	// IsParameterListContext differentiates from other interfaces.
	IsParameterListContext()
}

type ParameterListContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyParameterListContext() *ParameterListContext {
	var p = new(ParameterListContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_parameterList
	return p
}

func InitEmptyParameterListContext(p *ParameterListContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_parameterList
}

func (*ParameterListContext) IsParameterListContext() {}

func NewParameterListContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *ParameterListContext {
	var p = new(ParameterListContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_parameterList

	return p
}

func (s *ParameterListContext) GetParser() antlr.Parser { return s.parser }

func (s *ParameterListContext) AllType_() []ITypeContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(ITypeContext); ok {
			len++
		}
	}

	tst := make([]ITypeContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(ITypeContext); ok {
			tst[i] = t.(ITypeContext)
			i++
		}
	}

	return tst
}

func (s *ParameterListContext) Type_(i int) ITypeContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(ITypeContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(ITypeContext)
}

func (s *ParameterListContext) AllIDENTIFIER() []antlr.TerminalNode {
	return s.GetTokens(PaxoParserIDENTIFIER)
}

func (s *ParameterListContext) IDENTIFIER(i int) antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, i)
}

func (s *ParameterListContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ParameterListContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *ParameterListContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterParameterList(s)
	}
}

func (s *ParameterListContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitParameterList(s)
	}
}




func (p *PaxoParser) ParameterList() (localctx IParameterListContext) {
	localctx = NewParameterListContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 32, PaxoParserRULE_parameterList)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(181)
		p.Type_()
	}
	{
		p.SetState(182)
		p.Match(PaxoParserIDENTIFIER)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(189)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for _la == PaxoParserT__21 {
		{
			p.SetState(183)
			p.Match(PaxoParserT__21)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(184)
			p.Type_()
		}
		{
			p.SetState(185)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


		p.SetState(191)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_la = p.GetTokenStream().LA(1)
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IArgumentListContext is an interface to support dynamic dispatch.
type IArgumentListContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	AllExpression() []IExpressionContext
	Expression(i int) IExpressionContext

	// IsArgumentListContext differentiates from other interfaces.
	IsArgumentListContext()
}

type ArgumentListContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyArgumentListContext() *ArgumentListContext {
	var p = new(ArgumentListContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_argumentList
	return p
}

func InitEmptyArgumentListContext(p *ArgumentListContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_argumentList
}

func (*ArgumentListContext) IsArgumentListContext() {}

func NewArgumentListContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *ArgumentListContext {
	var p = new(ArgumentListContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_argumentList

	return p
}

func (s *ArgumentListContext) GetParser() antlr.Parser { return s.parser }

func (s *ArgumentListContext) AllExpression() []IExpressionContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IExpressionContext); ok {
			len++
		}
	}

	tst := make([]IExpressionContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IExpressionContext); ok {
			tst[i] = t.(IExpressionContext)
			i++
		}
	}

	return tst
}

func (s *ArgumentListContext) Expression(i int) IExpressionContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}

func (s *ArgumentListContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ArgumentListContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *ArgumentListContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterArgumentList(s)
	}
}

func (s *ArgumentListContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitArgumentList(s)
	}
}




func (p *PaxoParser) ArgumentList() (localctx IArgumentListContext) {
	localctx = NewArgumentListContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 34, PaxoParserRULE_argumentList)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(192)
		p.expression(0)
	}
	p.SetState(197)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for _la == PaxoParserT__21 {
		{
			p.SetState(193)
			p.Match(PaxoParserT__21)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(194)
			p.expression(0)
		}


		p.SetState(199)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_la = p.GetTokenStream().LA(1)
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IExpressionContext is an interface to support dynamic dispatch.
type IExpressionContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser
	// IsExpressionContext differentiates from other interfaces.
	IsExpressionContext()
}

type ExpressionContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyExpressionContext() *ExpressionContext {
	var p = new(ExpressionContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_expression
	return p
}

func InitEmptyExpressionContext(p *ExpressionContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_expression
}

func (*ExpressionContext) IsExpressionContext() {}

func NewExpressionContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *ExpressionContext {
	var p = new(ExpressionContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_expression

	return p
}

func (s *ExpressionContext) GetParser() antlr.Parser { return s.parser }

func (s *ExpressionContext) CopyAll(ctx *ExpressionContext) {
	s.CopyFrom(&ctx.BaseParserRuleContext)
}

func (s *ExpressionContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ExpressionContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}





type CallExprContext struct {
	ExpressionContext
}

func NewCallExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *CallExprContext {
	var p = new(CallExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *CallExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *CallExprContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}

func (s *CallExprContext) ArgumentList() IArgumentListContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IArgumentListContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IArgumentListContext)
}


func (s *CallExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterCallExpr(s)
	}
}

func (s *CallExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitCallExpr(s)
	}
}


type ArrayAccessExprContext struct {
	ExpressionContext
}

func NewArrayAccessExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *ArrayAccessExprContext {
	var p = new(ArrayAccessExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *ArrayAccessExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ArrayAccessExprContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}

func (s *ArrayAccessExprContext) Expression() IExpressionContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}


func (s *ArrayAccessExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterArrayAccessExpr(s)
	}
}

func (s *ArrayAccessExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitArrayAccessExpr(s)
	}
}


type NotgateExprContext struct {
	ExpressionContext
}

func NewNotgateExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *NotgateExprContext {
	var p = new(NotgateExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *NotgateExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *NotgateExprContext) Expression() IExpressionContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}


func (s *NotgateExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterNotgateExpr(s)
	}
}

func (s *NotgateExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitNotgateExpr(s)
	}
}


type IntLitExprContext struct {
	ExpressionContext
}

func NewIntLitExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *IntLitExprContext {
	var p = new(IntLitExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *IntLitExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *IntLitExprContext) INT_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserINT_LITERAL, 0)
}


func (s *IntLitExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterIntLitExpr(s)
	}
}

func (s *IntLitExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitIntLitExpr(s)
	}
}


type DecLitExprContext struct {
	ExpressionContext
}

func NewDecLitExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *DecLitExprContext {
	var p = new(DecLitExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *DecLitExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *DecLitExprContext) DECIMAL_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserDECIMAL_LITERAL, 0)
}


func (s *DecLitExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterDecLitExpr(s)
	}
}

func (s *DecLitExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitDecLitExpr(s)
	}
}


type CharLitExprContext struct {
	ExpressionContext
}

func NewCharLitExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *CharLitExprContext {
	var p = new(CharLitExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *CharLitExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *CharLitExprContext) CHAR_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserCHAR_LITERAL, 0)
}


func (s *CharLitExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterCharLitExpr(s)
	}
}

func (s *CharLitExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitCharLitExpr(s)
	}
}


type StringLitExprContext struct {
	ExpressionContext
}

func NewStringLitExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *StringLitExprContext {
	var p = new(StringLitExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *StringLitExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *StringLitExprContext) STRING_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserSTRING_LITERAL, 0)
}


func (s *StringLitExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterStringLitExpr(s)
	}
}

func (s *StringLitExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitStringLitExpr(s)
	}
}


type BoolBitExprContext struct {
	ExpressionContext
}

func NewBoolBitExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *BoolBitExprContext {
	var p = new(BoolBitExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *BoolBitExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *BoolBitExprContext) BOOLEAN_BIT() antlr.TerminalNode {
	return s.GetToken(PaxoParserBOOLEAN_BIT, 0)
}


func (s *BoolBitExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterBoolBitExpr(s)
	}
}

func (s *BoolBitExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitBoolBitExpr(s)
	}
}


type BoolTritExprContext struct {
	ExpressionContext
}

func NewBoolTritExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *BoolTritExprContext {
	var p = new(BoolTritExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *BoolTritExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *BoolTritExprContext) BOOLEAN_TRIT() antlr.TerminalNode {
	return s.GetToken(PaxoParserBOOLEAN_TRIT, 0)
}


func (s *BoolTritExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterBoolTritExpr(s)
	}
}

func (s *BoolTritExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitBoolTritExpr(s)
	}
}


type PtrLitExprContext struct {
	ExpressionContext
}

func NewPtrLitExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *PtrLitExprContext {
	var p = new(PtrLitExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *PtrLitExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *PtrLitExprContext) POINTER_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserPOINTER_LITERAL, 0)
}


func (s *PtrLitExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterPtrLitExpr(s)
	}
}

func (s *PtrLitExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitPtrLitExpr(s)
	}
}


type ArrayLitExprContext struct {
	ExpressionContext
}

func NewArrayLitExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *ArrayLitExprContext {
	var p = new(ArrayLitExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *ArrayLitExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ArrayLitExprContext) ArrayLiteral() IArrayLiteralContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IArrayLiteralContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IArrayLiteralContext)
}


func (s *ArrayLitExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterArrayLitExpr(s)
	}
}

func (s *ArrayLitExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitArrayLitExpr(s)
	}
}


type ArrayAccExprContext struct {
	ExpressionContext
}

func NewArrayAccExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *ArrayAccExprContext {
	var p = new(ArrayAccExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *ArrayAccExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ArrayAccExprContext) ArrayAccess() IArrayAccessContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IArrayAccessContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IArrayAccessContext)
}


func (s *ArrayAccExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterArrayAccExpr(s)
	}
}

func (s *ArrayAccExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitArrayAccExpr(s)
	}
}


type IdentExprContext struct {
	ExpressionContext
}

func NewIdentExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *IdentExprContext {
	var p = new(IdentExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *IdentExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *IdentExprContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}


func (s *IdentExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterIdentExpr(s)
	}
}

func (s *IdentExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitIdentExpr(s)
	}
}


type PkgExprContext struct {
	ExpressionContext
}

func NewPkgExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *PkgExprContext {
	var p = new(PkgExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *PkgExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *PkgExprContext) PkgDeclaration() IPkgDeclarationContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IPkgDeclarationContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IPkgDeclarationContext)
}


func (s *PkgExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterPkgExpr(s)
	}
}

func (s *PkgExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitPkgExpr(s)
	}
}


type FuncExprContext struct {
	ExpressionContext
}

func NewFuncExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *FuncExprContext {
	var p = new(FuncExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *FuncExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *FuncExprContext) FunctionDeclaration() IFunctionDeclarationContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IFunctionDeclarationContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IFunctionDeclarationContext)
}


func (s *FuncExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterFuncExpr(s)
	}
}

func (s *FuncExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitFuncExpr(s)
	}
}


type MultDivExprContext struct {
	ExpressionContext
}

func NewMultDivExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *MultDivExprContext {
	var p = new(MultDivExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *MultDivExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *MultDivExprContext) AllExpression() []IExpressionContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IExpressionContext); ok {
			len++
		}
	}

	tst := make([]IExpressionContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IExpressionContext); ok {
			tst[i] = t.(IExpressionContext)
			i++
		}
	}

	return tst
}

func (s *MultDivExprContext) Expression(i int) IExpressionContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}


func (s *MultDivExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterMultDivExpr(s)
	}
}

func (s *MultDivExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitMultDivExpr(s)
	}
}


type AddSubExprContext struct {
	ExpressionContext
}

func NewAddSubExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *AddSubExprContext {
	var p = new(AddSubExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *AddSubExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *AddSubExprContext) AllExpression() []IExpressionContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IExpressionContext); ok {
			len++
		}
	}

	tst := make([]IExpressionContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IExpressionContext); ok {
			tst[i] = t.(IExpressionContext)
			i++
		}
	}

	return tst
}

func (s *AddSubExprContext) Expression(i int) IExpressionContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}


func (s *AddSubExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterAddSubExpr(s)
	}
}

func (s *AddSubExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitAddSubExpr(s)
	}
}


type ShiftExprContext struct {
	ExpressionContext
}

func NewShiftExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *ShiftExprContext {
	var p = new(ShiftExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *ShiftExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ShiftExprContext) AllExpression() []IExpressionContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IExpressionContext); ok {
			len++
		}
	}

	tst := make([]IExpressionContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IExpressionContext); ok {
			tst[i] = t.(IExpressionContext)
			i++
		}
	}

	return tst
}

func (s *ShiftExprContext) Expression(i int) IExpressionContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}


func (s *ShiftExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterShiftExpr(s)
	}
}

func (s *ShiftExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitShiftExpr(s)
	}
}


type RelationalExprContext struct {
	ExpressionContext
}

func NewRelationalExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *RelationalExprContext {
	var p = new(RelationalExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *RelationalExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *RelationalExprContext) AllExpression() []IExpressionContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IExpressionContext); ok {
			len++
		}
	}

	tst := make([]IExpressionContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IExpressionContext); ok {
			tst[i] = t.(IExpressionContext)
			i++
		}
	}

	return tst
}

func (s *RelationalExprContext) Expression(i int) IExpressionContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}


func (s *RelationalExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterRelationalExpr(s)
	}
}

func (s *RelationalExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitRelationalExpr(s)
	}
}


type BitwiseExprContext struct {
	ExpressionContext
}

func NewBitwiseExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *BitwiseExprContext {
	var p = new(BitwiseExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *BitwiseExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *BitwiseExprContext) AllExpression() []IExpressionContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IExpressionContext); ok {
			len++
		}
	}

	tst := make([]IExpressionContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IExpressionContext); ok {
			tst[i] = t.(IExpressionContext)
			i++
		}
	}

	return tst
}

func (s *BitwiseExprContext) Expression(i int) IExpressionContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}


func (s *BitwiseExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterBitwiseExpr(s)
	}
}

func (s *BitwiseExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitBitwiseExpr(s)
	}
}



func (p *PaxoParser) Expression() (localctx IExpressionContext) {
	return p.expression(0)
}

func (p *PaxoParser) expression(_p int) (localctx IExpressionContext) {
	var _parentctx antlr.ParserRuleContext = p.GetParserRuleContext()

	_parentState := p.GetState()
	localctx = NewExpressionContext(p, p.GetParserRuleContext(), _parentState)
	var _prevctx IExpressionContext = localctx
	var _ antlr.ParserRuleContext = _prevctx // TODO: To prevent unused variable warning.
	_startState := 36
	p.EnterRecursionRule(localctx, 36, PaxoParserRULE_expression, _p)
	var _la int

	var _alt int

	p.EnterOuterAlt(localctx, 1)
	p.SetState(226)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 15, p.GetParserRuleContext()) {
	case 1:
		localctx = NewCallExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx

		{
			p.SetState(201)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(202)
			p.Match(PaxoParserT__9)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(204)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		if ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 9187344201909535744) != 0) {
			{
				p.SetState(203)
				p.ArgumentList()
			}

		}
		{
			p.SetState(206)
			p.Match(PaxoParserT__10)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 2:
		localctx = NewArrayAccessExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(207)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(208)
			p.Match(PaxoParserT__5)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(209)
			p.expression(0)
		}
		{
			p.SetState(210)
			p.Match(PaxoParserT__6)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 3:
		localctx = NewNotgateExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(212)
			_la = p.GetTokenStream().LA(1)

			if !(_la == PaxoParserT__36 || _la == PaxoParserT__37) {
				p.GetErrorHandler().RecoverInline(p)
			} else {
				p.GetErrorHandler().ReportMatch(p)
				p.Consume()
			}
		}
		{
			p.SetState(213)
			p.expression(13)
		}


	case 4:
		localctx = NewIntLitExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(214)
			p.Match(PaxoParserINT_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 5:
		localctx = NewDecLitExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(215)
			p.Match(PaxoParserDECIMAL_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 6:
		localctx = NewCharLitExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(216)
			p.Match(PaxoParserCHAR_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 7:
		localctx = NewStringLitExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(217)
			p.Match(PaxoParserSTRING_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 8:
		localctx = NewBoolBitExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(218)
			p.Match(PaxoParserBOOLEAN_BIT)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 9:
		localctx = NewBoolTritExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(219)
			p.Match(PaxoParserBOOLEAN_TRIT)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 10:
		localctx = NewPtrLitExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(220)
			p.Match(PaxoParserPOINTER_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 11:
		localctx = NewArrayLitExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(221)
			p.ArrayLiteral()
		}


	case 12:
		localctx = NewArrayAccExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(222)
			p.ArrayAccess()
		}


	case 13:
		localctx = NewIdentExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(223)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 14:
		localctx = NewPkgExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(224)
			p.PkgDeclaration()
		}


	case 15:
		localctx = NewFuncExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(225)
			p.FunctionDeclaration()
		}

	case antlr.ATNInvalidAltNumber:
		goto errorExit
	}
	p.GetParserRuleContext().SetStop(p.GetTokenStream().LT(-1))
	p.SetState(245)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 17, p.GetParserRuleContext())
	if p.HasError() {
		goto errorExit
	}
	for _alt != 2 && _alt != antlr.ATNInvalidAltNumber {
		if _alt == 1 {
			if p.GetParseListeners() != nil {
				p.TriggerExitRuleEvent()
			}
			_prevctx = localctx
			p.SetState(243)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
				goto errorExit
			}

			switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 16, p.GetParserRuleContext()) {
			case 1:
				localctx = NewMultDivExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(228)

				if !(p.Precpred(p.GetParserRuleContext(), 18)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 18)", ""))
					goto errorExit
				}
				{
					p.SetState(229)
					_la = p.GetTokenStream().LA(1)

					if !(_la == PaxoParserT__22 || _la == PaxoParserT__23) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(230)
					p.expression(19)
				}


			case 2:
				localctx = NewAddSubExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(231)

				if !(p.Precpred(p.GetParserRuleContext(), 17)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 17)", ""))
					goto errorExit
				}
				{
					p.SetState(232)
					_la = p.GetTokenStream().LA(1)

					if !(_la == PaxoParserT__24 || _la == PaxoParserT__25) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(233)
					p.expression(18)
				}


			case 3:
				localctx = NewShiftExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(234)

				if !(p.Precpred(p.GetParserRuleContext(), 16)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 16)", ""))
					goto errorExit
				}
				{
					p.SetState(235)
					_la = p.GetTokenStream().LA(1)

					if !(_la == PaxoParserT__26 || _la == PaxoParserT__27) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(236)
					p.expression(17)
				}


			case 4:
				localctx = NewRelationalExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(237)

				if !(p.Precpred(p.GetParserRuleContext(), 15)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 15)", ""))
					goto errorExit
				}
				{
					p.SetState(238)
					_la = p.GetTokenStream().LA(1)

					if !(((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 8053063700) != 0)) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(239)
					p.expression(16)
				}


			case 5:
				localctx = NewBitwiseExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(240)

				if !(p.Precpred(p.GetParserRuleContext(), 14)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 14)", ""))
					goto errorExit
				}
				{
					p.SetState(241)
					_la = p.GetTokenStream().LA(1)

					if !(((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 128849018880) != 0)) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(242)
					p.expression(15)
				}

			case antlr.ATNInvalidAltNumber:
				goto errorExit
			}

		}
		p.SetState(247)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 17, p.GetParserRuleContext())
		if p.HasError() {
			goto errorExit
		}
	}



	errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.UnrollRecursionContexts(_parentctx)
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IArrayLiteralContext is an interface to support dynamic dispatch.
type IArrayLiteralContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	AllExpression() []IExpressionContext
	Expression(i int) IExpressionContext

	// IsArrayLiteralContext differentiates from other interfaces.
	IsArrayLiteralContext()
}

type ArrayLiteralContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyArrayLiteralContext() *ArrayLiteralContext {
	var p = new(ArrayLiteralContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_arrayLiteral
	return p
}

func InitEmptyArrayLiteralContext(p *ArrayLiteralContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_arrayLiteral
}

func (*ArrayLiteralContext) IsArrayLiteralContext() {}

func NewArrayLiteralContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *ArrayLiteralContext {
	var p = new(ArrayLiteralContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_arrayLiteral

	return p
}

func (s *ArrayLiteralContext) GetParser() antlr.Parser { return s.parser }

func (s *ArrayLiteralContext) AllExpression() []IExpressionContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IExpressionContext); ok {
			len++
		}
	}

	tst := make([]IExpressionContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IExpressionContext); ok {
			tst[i] = t.(IExpressionContext)
			i++
		}
	}

	return tst
}

func (s *ArrayLiteralContext) Expression(i int) IExpressionContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			if j == i {
				t = ctx.(antlr.RuleContext);
				break
			}
			j++
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}

func (s *ArrayLiteralContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ArrayLiteralContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *ArrayLiteralContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterArrayLiteral(s)
	}
}

func (s *ArrayLiteralContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitArrayLiteral(s)
	}
}




func (p *PaxoParser) ArrayLiteral() (localctx IArrayLiteralContext) {
	localctx = NewArrayLiteralContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 38, PaxoParserRULE_arrayLiteral)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(248)
		p.Match(PaxoParserT__38)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(249)
		p.expression(0)
	}
	p.SetState(254)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for _la == PaxoParserT__21 {
		{
			p.SetState(250)
			p.Match(PaxoParserT__21)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(251)
			p.expression(0)
		}


		p.SetState(256)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_la = p.GetTokenStream().LA(1)
	}
	{
		p.SetState(257)
		p.Match(PaxoParserT__39)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


// IArrayAccessContext is an interface to support dynamic dispatch.
type IArrayAccessContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	IDENTIFIER() antlr.TerminalNode
	Expression() IExpressionContext

	// IsArrayAccessContext differentiates from other interfaces.
	IsArrayAccessContext()
}

type ArrayAccessContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyArrayAccessContext() *ArrayAccessContext {
	var p = new(ArrayAccessContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_arrayAccess
	return p
}

func InitEmptyArrayAccessContext(p *ArrayAccessContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_arrayAccess
}

func (*ArrayAccessContext) IsArrayAccessContext() {}

func NewArrayAccessContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *ArrayAccessContext {
	var p = new(ArrayAccessContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_arrayAccess

	return p
}

func (s *ArrayAccessContext) GetParser() antlr.Parser { return s.parser }

func (s *ArrayAccessContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}

func (s *ArrayAccessContext) Expression() IExpressionContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IExpressionContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IExpressionContext)
}

func (s *ArrayAccessContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ArrayAccessContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *ArrayAccessContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterArrayAccess(s)
	}
}

func (s *ArrayAccessContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitArrayAccess(s)
	}
}




func (p *PaxoParser) ArrayAccess() (localctx IArrayAccessContext) {
	localctx = NewArrayAccessContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 40, PaxoParserRULE_arrayAccess)
	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(259)
		p.Match(PaxoParserIDENTIFIER)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(260)
		p.Match(PaxoParserT__5)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(261)
		p.expression(0)
	}
	{
		p.SetState(262)
		p.Match(PaxoParserT__6)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}



errorExit:
	if p.HasError() {
		v := p.GetError()
		localctx.SetException(v)
		p.GetErrorHandler().ReportError(p, v)
		p.GetErrorHandler().Recover(p, v)
		p.SetError(nil)
	}
	p.ExitRule()
	return localctx
	goto errorExit // Trick to prevent compiler error if the label is not used
}


func (p *PaxoParser) Sempred(localctx antlr.RuleContext, ruleIndex, predIndex int) bool {
	switch ruleIndex {
	case 18:
			var t *ExpressionContext = nil
			if localctx != nil { t = localctx.(*ExpressionContext) }
			return p.Expression_Sempred(t, predIndex)


	default:
		panic("No predicate with index: " + fmt.Sprint(ruleIndex))
	}
}

func (p *PaxoParser) Expression_Sempred(localctx antlr.RuleContext, predIndex int) bool {
	switch predIndex {
	case 0:
			return p.Precpred(p.GetParserRuleContext(), 18)

	case 1:
			return p.Precpred(p.GetParserRuleContext(), 17)

	case 2:
			return p.Precpred(p.GetParserRuleContext(), 16)

	case 3:
			return p.Precpred(p.GetParserRuleContext(), 15)

	case 4:
			return p.Precpred(p.GetParserRuleContext(), 14)

	default:
		panic("No predicate with index: " + fmt.Sprint(predIndex))
	}
}

