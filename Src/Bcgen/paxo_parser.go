
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
    "':|'", "'\\U0001D107'", "'{'", "','", "'}'", "'\\U0001F3C1'", "'end'", 
    "'\\u00F7'", "'\\u00D7'", "'+'", "'-'", "'\\u2022\\u00AB'", "'\\u00BB\\u2022'", 
    "'\\u2264'", "'<='", "'\\u2265'", "'>='", "'=='", "'!='", "'\\u2260'", 
    "'&'", "'|'", "'.&'", "'.|'", "'!'", "'.!'", "'\\u00AB'", "'\\u00BB'", 
    "", "", "", "'abc'", "'trit'", "'bool'", "'pin'", "'fx'", "", "'int'", 
    "'pdec'", "'col'", "", "'local'", "", "", "", "", "'return'",
  }
  staticData.SymbolicNames = []string{
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
    "", "", "", "", "", "", "", "", "", "", "", "", "VAR_TYPE", "NUM_TYPE", 
    "COMPLEX_TYPE", "CHARA_TYPE", "TRIT_TYPE", "BOOLEAN_TYPE", "POINTER_TYPE", 
    "FUNC_TYPE", "PKG_TYPE", "INT_TYPE", "PKDEC_TYPE", "COLOR_TYPE", "GLOBAL", 
    "LOCAL", "TRY", "CATCH", "ARROW", "INCLUDE", "RETURN", "THROW", "PAUSE_MODE", 
    "PLAY_MODE", "INT_LITERAL", "DECIMAL_LITERAL", "COMPLEX_LITERAL", "BOOLEAN_BIT", 
    "BOOLEAN_TRIT", "POINTER_LITERAL", "COLOR_LITERAL", "THIS_SCOPE", "IDENTIFIER", 
    "STRING_LITERAL", "CHAR_LITERAL", "LINE_COMMENT", "BLOCK_COMMENT", "WS",
  }
  staticData.RuleNames = []string{
    "program", "statement", "varDeclaration", "type", "scope", "assignment", 
    "condStatement", "matchCase", "loopStatement", "loopMode", "loopDelimiter", 
    "loopEndDelimiter", "tryCatchStatement", "functionDeclaration", "pkgDeclaration", 
    "block", "parameterList", "returnStatement", "throwStatement", "argumentList", 
    "expression", "arrayLiteral",
  }
  staticData.PredictionContextCache = antlr.NewPredictionContextCache()
  staticData.serializedATN = []int32{
	4, 1, 81, 402, 2, 0, 7, 0, 2, 1, 7, 1, 2, 2, 7, 2, 2, 3, 7, 3, 2, 4, 7, 
	4, 2, 5, 7, 5, 2, 6, 7, 6, 2, 7, 7, 7, 2, 8, 7, 8, 2, 9, 7, 9, 2, 10, 7, 
	10, 2, 11, 7, 11, 2, 12, 7, 12, 2, 13, 7, 13, 2, 14, 7, 14, 2, 15, 7, 15, 
	2, 16, 7, 16, 2, 17, 7, 17, 2, 18, 7, 18, 2, 19, 7, 19, 2, 20, 7, 20, 2, 
	21, 7, 21, 1, 0, 5, 0, 46, 8, 0, 10, 0, 12, 0, 49, 9, 0, 1, 0, 1, 0, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 63, 8, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 70, 8, 1, 1, 1, 3, 1, 73, 8, 1, 1, 
	2, 3, 2, 76, 8, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3, 2, 84, 8, 2, 
	1, 2, 1, 2, 1, 2, 1, 2, 3, 2, 90, 8, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3, 
	2, 97, 8, 2, 1, 2, 1, 2, 1, 2, 3, 2, 102, 8, 2, 1, 3, 1, 3, 1, 4, 1, 4, 
	1, 5, 1, 5, 1, 5, 1, 5, 3, 5, 112, 8, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 
	1, 5, 1, 5, 3, 5, 121, 8, 5, 1, 5, 1, 5, 1, 5, 3, 5, 126, 8, 5, 1, 5, 1, 
	5, 1, 5, 3, 5, 131, 8, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 3, 5, 139, 
	8, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 3, 5, 147, 8, 5, 3, 5, 149, 8, 
	5, 1, 6, 1, 6, 1, 6, 1, 6, 1, 6, 1, 6, 1, 6, 5, 6, 158, 8, 6, 10, 6, 12, 
	6, 161, 9, 6, 1, 6, 3, 6, 164, 8, 6, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 
	1, 7, 3, 7, 173, 8, 7, 1, 8, 1, 8, 1, 8, 1, 8, 1, 8, 1, 8, 3, 8, 181, 8, 
	8, 1, 8, 1, 8, 3, 8, 185, 8, 8, 1, 9, 1, 9, 1, 10, 1, 10, 1, 11, 1, 11, 
	1, 12, 1, 12, 1, 12, 1, 12, 1, 12, 1, 12, 1, 12, 3, 12, 200, 8, 12, 1, 
	12, 1, 12, 1, 12, 1, 13, 1, 13, 3, 13, 207, 8, 13, 1, 13, 1, 13, 1, 13, 
	3, 13, 212, 8, 13, 1, 13, 1, 13, 1, 14, 1, 14, 3, 14, 218, 8, 14, 1, 14, 
	5, 14, 221, 8, 14, 10, 14, 12, 14, 224, 9, 14, 1, 14, 3, 14, 227, 8, 14, 
	1, 14, 1, 14, 1, 15, 1, 15, 5, 15, 233, 8, 15, 10, 15, 12, 15, 236, 9, 
	15, 1, 15, 1, 15, 1, 15, 5, 15, 241, 8, 15, 10, 15, 12, 15, 244, 9, 15, 
	1, 15, 1, 15, 5, 15, 248, 8, 15, 10, 15, 12, 15, 251, 9, 15, 1, 15, 1, 
	15, 1, 15, 5, 15, 256, 8, 15, 10, 15, 12, 15, 259, 9, 15, 1, 15, 3, 15, 
	262, 8, 15, 1, 16, 1, 16, 1, 16, 1, 16, 1, 16, 1, 16, 5, 16, 270, 8, 16, 
	10, 16, 12, 16, 273, 9, 16, 1, 17, 1, 17, 3, 17, 277, 8, 17, 1, 17, 3, 
	17, 280, 8, 17, 1, 18, 1, 18, 1, 18, 3, 18, 285, 8, 18, 1, 19, 1, 19, 1, 
	19, 5, 19, 290, 8, 19, 10, 19, 12, 19, 293, 9, 19, 3, 19, 295, 8, 19, 1, 
	20, 1, 20, 1, 20, 1, 20, 3, 20, 301, 8, 20, 1, 20, 1, 20, 1, 20, 1, 20, 
	1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 
	20, 1, 20, 1, 20, 1, 20, 1, 20, 3, 20, 322, 8, 20, 1, 20, 1, 20, 1, 20, 
	1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 
	20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 
	1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 
	20, 1, 20, 1, 20, 1, 20, 5, 20, 362, 8, 20, 10, 20, 12, 20, 365, 9, 20, 
	1, 21, 1, 21, 1, 21, 1, 21, 5, 21, 371, 8, 21, 10, 21, 12, 21, 374, 9, 
	21, 1, 21, 1, 21, 1, 21, 1, 21, 1, 21, 1, 21, 5, 21, 382, 8, 21, 10, 21, 
	12, 21, 385, 9, 21, 1, 21, 1, 21, 1, 21, 1, 21, 1, 21, 1, 21, 5, 21, 393, 
	8, 21, 10, 21, 12, 21, 396, 9, 21, 1, 21, 1, 21, 3, 21, 400, 8, 21, 1, 
	21, 1, 159, 1, 40, 22, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 
	28, 30, 32, 34, 36, 38, 40, 42, 0, 11, 1, 0, 46, 57, 1, 0, 58, 59, 1, 0, 
	66, 67, 1, 0, 16, 17, 1, 0, 18, 19, 1, 0, 42, 43, 1, 0, 25, 26, 1, 0, 27, 
	28, 1, 0, 29, 30, 3, 0, 2, 2, 4, 4, 31, 37, 1, 0, 38, 41, 462, 0, 47, 1, 
	0, 0, 0, 2, 72, 1, 0, 0, 0, 4, 101, 1, 0, 0, 0, 6, 103, 1, 0, 0, 0, 8, 
	105, 1, 0, 0, 0, 10, 148, 1, 0, 0, 0, 12, 150, 1, 0, 0, 0, 14, 172, 1, 
	0, 0, 0, 16, 174, 1, 0, 0, 0, 18, 186, 1, 0, 0, 0, 20, 188, 1, 0, 0, 0, 
	22, 190, 1, 0, 0, 0, 24, 192, 1, 0, 0, 0, 26, 204, 1, 0, 0, 0, 28, 215, 
	1, 0, 0, 0, 30, 261, 1, 0, 0, 0, 32, 263, 1, 0, 0, 0, 34, 274, 1, 0, 0, 
	0, 36, 281, 1, 0, 0, 0, 38, 294, 1, 0, 0, 0, 40, 321, 1, 0, 0, 0, 42, 399, 
	1, 0, 0, 0, 44, 46, 3, 2, 1, 0, 45, 44, 1, 0, 0, 0, 46, 49, 1, 0, 0, 0, 
	47, 45, 1, 0, 0, 0, 47, 48, 1, 0, 0, 0, 48, 50, 1, 0, 0, 0, 49, 47, 1, 
	0, 0, 0, 50, 51, 5, 0, 0, 1, 51, 1, 1, 0, 0, 0, 52, 73, 5, 1, 0, 0, 53, 
	73, 3, 4, 2, 0, 54, 73, 3, 10, 5, 0, 55, 73, 3, 12, 6, 0, 56, 73, 3, 16, 
	8, 0, 57, 73, 3, 24, 12, 0, 58, 73, 3, 36, 18, 0, 59, 73, 3, 34, 17, 0, 
	60, 62, 3, 40, 20, 0, 61, 63, 5, 1, 0, 0, 62, 61, 1, 0, 0, 0, 62, 63, 1, 
	0, 0, 0, 63, 73, 1, 0, 0, 0, 64, 65, 5, 63, 0, 0, 65, 66, 5, 2, 0, 0, 66, 
	69, 5, 76, 0, 0, 67, 68, 5, 3, 0, 0, 68, 70, 5, 76, 0, 0, 69, 67, 1, 0, 
	0, 0, 69, 70, 1, 0, 0, 0, 70, 71, 1, 0, 0, 0, 71, 73, 5, 4, 0, 0, 72, 52, 
	1, 0, 0, 0, 72, 53, 1, 0, 0, 0, 72, 54, 1, 0, 0, 0, 72, 55, 1, 0, 0, 0, 
	72, 56, 1, 0, 0, 0, 72, 57, 1, 0, 0, 0, 72, 58, 1, 0, 0, 0, 72, 59, 1, 
	0, 0, 0, 72, 60, 1, 0, 0, 0, 72, 64, 1, 0, 0, 0, 73, 3, 1, 0, 0, 0, 74, 
	76, 3, 8, 4, 0, 75, 74, 1, 0, 0, 0, 75, 76, 1, 0, 0, 0, 76, 77, 1, 0, 0, 
	0, 77, 78, 3, 6, 3, 0, 78, 79, 5, 76, 0, 0, 79, 80, 5, 5, 0, 0, 80, 81, 
	3, 40, 20, 0, 81, 102, 1, 0, 0, 0, 82, 84, 3, 8, 4, 0, 83, 82, 1, 0, 0, 
	0, 83, 84, 1, 0, 0, 0, 84, 85, 1, 0, 0, 0, 85, 86, 3, 6, 3, 0, 86, 87, 
	5, 76, 0, 0, 87, 89, 5, 6, 0, 0, 88, 90, 5, 68, 0, 0, 89, 88, 1, 0, 0, 
	0, 89, 90, 1, 0, 0, 0, 90, 91, 1, 0, 0, 0, 91, 92, 5, 7, 0, 0, 92, 93, 
	5, 5, 0, 0, 93, 94, 3, 42, 21, 0, 94, 102, 1, 0, 0, 0, 95, 97, 3, 8, 4, 
	0, 96, 95, 1, 0, 0, 0, 96, 97, 1, 0, 0, 0, 97, 98, 1, 0, 0, 0, 98, 99, 
	3, 6, 3, 0, 99, 100, 5, 76, 0, 0, 100, 102, 1, 0, 0, 0, 101, 75, 1, 0, 
	0, 0, 101, 83, 1, 0, 0, 0, 101, 96, 1, 0, 0, 0, 102, 5, 1, 0, 0, 0, 103, 
	104, 7, 0, 0, 0, 104, 7, 1, 0, 0, 0, 105, 106, 7, 1, 0, 0, 106, 9, 1, 0, 
	0, 0, 107, 108, 5, 76, 0, 0, 108, 109, 5, 5, 0, 0, 109, 111, 3, 40, 20, 
	0, 110, 112, 5, 1, 0, 0, 111, 110, 1, 0, 0, 0, 111, 112, 1, 0, 0, 0, 112, 
	149, 1, 0, 0, 0, 113, 114, 5, 76, 0, 0, 114, 115, 5, 6, 0, 0, 115, 116, 
	3, 40, 20, 0, 116, 117, 5, 7, 0, 0, 117, 118, 5, 5, 0, 0, 118, 120, 3, 
	40, 20, 0, 119, 121, 5, 1, 0, 0, 120, 119, 1, 0, 0, 0, 120, 121, 1, 0, 
	0, 0, 121, 149, 1, 0, 0, 0, 122, 123, 5, 76, 0, 0, 123, 125, 5, 8, 0, 0, 
	124, 126, 5, 1, 0, 0, 125, 124, 1, 0, 0, 0, 125, 126, 1, 0, 0, 0, 126, 
	149, 1, 0, 0, 0, 127, 128, 5, 76, 0, 0, 128, 130, 5, 9, 0, 0, 129, 131, 
	5, 1, 0, 0, 130, 129, 1, 0, 0, 0, 130, 131, 1, 0, 0, 0, 131, 149, 1, 0, 
	0, 0, 132, 133, 3, 40, 20, 0, 133, 134, 5, 3, 0, 0, 134, 135, 5, 76, 0, 
	0, 135, 136, 5, 5, 0, 0, 136, 138, 3, 40, 20, 0, 137, 139, 5, 1, 0, 0, 
	138, 137, 1, 0, 0, 0, 138, 139, 1, 0, 0, 0, 139, 149, 1, 0, 0, 0, 140, 
	141, 5, 75, 0, 0, 141, 142, 5, 3, 0, 0, 142, 143, 5, 76, 0, 0, 143, 144, 
	5, 5, 0, 0, 144, 146, 3, 40, 20, 0, 145, 147, 5, 1, 0, 0, 146, 145, 1, 
	0, 0, 0, 146, 147, 1, 0, 0, 0, 147, 149, 1, 0, 0, 0, 148, 107, 1, 0, 0, 
	0, 148, 113, 1, 0, 0, 0, 148, 122, 1, 0, 0, 0, 148, 127, 1, 0, 0, 0, 148, 
	132, 1, 0, 0, 0, 148, 140, 1, 0, 0, 0, 149, 11, 1, 0, 0, 0, 150, 151, 5, 
	10, 0, 0, 151, 152, 3, 40, 20, 0, 152, 153, 5, 11, 0, 0, 153, 154, 5, 12, 
	0, 0, 154, 159, 3, 14, 7, 0, 155, 156, 5, 13, 0, 0, 156, 158, 3, 14, 7, 
	0, 157, 155, 1, 0, 0, 0, 158, 161, 1, 0, 0, 0, 159, 160, 1, 0, 0, 0, 159, 
	157, 1, 0, 0, 0, 160, 163, 1, 0, 0, 0, 161, 159, 1, 0, 0, 0, 162, 164, 
	5, 1, 0, 0, 163, 162, 1, 0, 0, 0, 163, 164, 1, 0, 0, 0, 164, 13, 1, 0, 
	0, 0, 165, 166, 3, 40, 20, 0, 166, 167, 5, 14, 0, 0, 167, 168, 3, 30, 15, 
	0, 168, 173, 1, 0, 0, 0, 169, 170, 5, 15, 0, 0, 170, 171, 5, 14, 0, 0, 
	171, 173, 3, 30, 15, 0, 172, 165, 1, 0, 0, 0, 172, 169, 1, 0, 0, 0, 173, 
	15, 1, 0, 0, 0, 174, 175, 5, 10, 0, 0, 175, 176, 3, 40, 20, 0, 176, 177, 
	5, 11, 0, 0, 177, 178, 5, 13, 0, 0, 178, 180, 3, 18, 9, 0, 179, 181, 3, 
	20, 10, 0, 180, 179, 1, 0, 0, 0, 180, 181, 1, 0, 0, 0, 181, 182, 1, 0, 
	0, 0, 182, 184, 3, 30, 15, 0, 183, 185, 3, 22, 11, 0, 184, 183, 1, 0, 0, 
	0, 184, 185, 1, 0, 0, 0, 185, 17, 1, 0, 0, 0, 186, 187, 7, 2, 0, 0, 187, 
	19, 1, 0, 0, 0, 188, 189, 7, 3, 0, 0, 189, 21, 1, 0, 0, 0, 190, 191, 7, 
	4, 0, 0, 191, 23, 1, 0, 0, 0, 192, 193, 5, 60, 0, 0, 193, 194, 3, 30, 15, 
	0, 194, 195, 5, 61, 0, 0, 195, 196, 5, 10, 0, 0, 196, 199, 5, 76, 0, 0, 
	197, 198, 5, 3, 0, 0, 198, 200, 5, 76, 0, 0, 199, 197, 1, 0, 0, 0, 199, 
	200, 1, 0, 0, 0, 200, 201, 1, 0, 0, 0, 201, 202, 5, 11, 0, 0, 202, 203, 
	3, 30, 15, 0, 203, 25, 1, 0, 0, 0, 204, 206, 5, 10, 0, 0, 205, 207, 3, 
	32, 16, 0, 206, 205, 1, 0, 0, 0, 206, 207, 1, 0, 0, 0, 207, 208, 1, 0, 
	0, 0, 208, 211, 5, 11, 0, 0, 209, 210, 5, 13, 0, 0, 210, 212, 3, 6, 3, 
	0, 211, 209, 1, 0, 0, 0, 211, 212, 1, 0, 0, 0, 212, 213, 1, 0, 0, 0, 213, 
	214, 3, 30, 15, 0, 214, 27, 1, 0, 0, 0, 215, 222, 5, 20, 0, 0, 216, 218, 
	5, 21, 0, 0, 217, 216, 1, 0, 0, 0, 217, 218, 1, 0, 0, 0, 218, 219, 1, 0, 
	0, 0, 219, 221, 3, 4, 2, 0, 220, 217, 1, 0, 0, 0, 221, 224, 1, 0, 0, 0, 
	222, 220, 1, 0, 0, 0, 222, 223, 1, 0, 0, 0, 223, 226, 1, 0, 0, 0, 224, 
	222, 1, 0, 0, 0, 225, 227, 5, 21, 0, 0, 226, 225, 1, 0, 0, 0, 226, 227, 
	1, 0, 0, 0, 227, 228, 1, 0, 0, 0, 228, 229, 5, 22, 0, 0, 229, 29, 1, 0, 
	0, 0, 230, 234, 5, 20, 0, 0, 231, 233, 3, 2, 1, 0, 232, 231, 1, 0, 0, 0, 
	233, 236, 1, 0, 0, 0, 234, 232, 1, 0, 0, 0, 234, 235, 1, 0, 0, 0, 235, 
	237, 1, 0, 0, 0, 236, 234, 1, 0, 0, 0, 237, 262, 5, 22, 0, 0, 238, 242, 
	5, 13, 0, 0, 239, 241, 3, 2, 1, 0, 240, 239, 1, 0, 0, 0, 241, 244, 1, 0, 
	0, 0, 242, 240, 1, 0, 0, 0, 242, 243, 1, 0, 0, 0, 243, 245, 1, 0, 0, 0, 
	244, 242, 1, 0, 0, 0, 245, 262, 5, 23, 0, 0, 246, 248, 3, 2, 1, 0, 247, 
	246, 1, 0, 0, 0, 248, 251, 1, 0, 0, 0, 249, 247, 1, 0, 0, 0, 249, 250, 
	1, 0, 0, 0, 250, 252, 1, 0, 0, 0, 251, 249, 1, 0, 0, 0, 252, 262, 5, 24, 
	0, 0, 253, 257, 5, 13, 0, 0, 254, 256, 3, 2, 1, 0, 255, 254, 1, 0, 0, 0, 
	256, 259, 1, 0, 0, 0, 257, 255, 1, 0, 0, 0, 257, 258, 1, 0, 0, 0, 258, 
	260, 1, 0, 0, 0, 259, 257, 1, 0, 0, 0, 260, 262, 5, 1, 0, 0, 261, 230, 
	1, 0, 0, 0, 261, 238, 1, 0, 0, 0, 261, 249, 1, 0, 0, 0, 261, 253, 1, 0, 
	0, 0, 262, 31, 1, 0, 0, 0, 263, 264, 3, 6, 3, 0, 264, 271, 5, 76, 0, 0, 
	265, 266, 5, 21, 0, 0, 266, 267, 3, 6, 3, 0, 267, 268, 5, 76, 0, 0, 268, 
	270, 1, 0, 0, 0, 269, 265, 1, 0, 0, 0, 270, 273, 1, 0, 0, 0, 271, 269, 
	1, 0, 0, 0, 271, 272, 1, 0, 0, 0, 272, 33, 1, 0, 0, 0, 273, 271, 1, 0, 
	0, 0, 274, 276, 5, 64, 0, 0, 275, 277, 3, 40, 20, 0, 276, 275, 1, 0, 0, 
	0, 276, 277, 1, 0, 0, 0, 277, 279, 1, 0, 0, 0, 278, 280, 5, 1, 0, 0, 279, 
	278, 1, 0, 0, 0, 279, 280, 1, 0, 0, 0, 280, 35, 1, 0, 0, 0, 281, 282, 5, 
	65, 0, 0, 282, 284, 3, 40, 20, 0, 283, 285, 5, 1, 0, 0, 284, 283, 1, 0, 
	0, 0, 284, 285, 1, 0, 0, 0, 285, 37, 1, 0, 0, 0, 286, 291, 3, 40, 20, 0, 
	287, 288, 5, 21, 0, 0, 288, 290, 3, 40, 20, 0, 289, 287, 1, 0, 0, 0, 290, 
	293, 1, 0, 0, 0, 291, 289, 1, 0, 0, 0, 291, 292, 1, 0, 0, 0, 292, 295, 
	1, 0, 0, 0, 293, 291, 1, 0, 0, 0, 294, 286, 1, 0, 0, 0, 294, 295, 1, 0, 
	0, 0, 295, 39, 1, 0, 0, 0, 296, 297, 6, 20, -1, 0, 297, 298, 5, 76, 0, 
	0, 298, 300, 5, 10, 0, 0, 299, 301, 3, 38, 19, 0, 300, 299, 1, 0, 0, 0, 
	300, 301, 1, 0, 0, 0, 301, 302, 1, 0, 0, 0, 302, 322, 5, 11, 0, 0, 303, 
	304, 7, 5, 0, 0, 304, 322, 3, 40, 20, 15, 305, 306, 5, 75, 0, 0, 306, 307, 
	5, 3, 0, 0, 307, 322, 5, 76, 0, 0, 308, 322, 5, 68, 0, 0, 309, 322, 5, 
	69, 0, 0, 310, 322, 5, 78, 0, 0, 311, 322, 5, 77, 0, 0, 312, 322, 5, 71, 
	0, 0, 313, 322, 5, 72, 0, 0, 314, 322, 5, 73, 0, 0, 315, 322, 5, 74, 0, 
	0, 316, 322, 5, 70, 0, 0, 317, 322, 3, 42, 21, 0, 318, 322, 5, 76, 0, 0, 
	319, 322, 3, 28, 14, 0, 320, 322, 3, 26, 13, 0, 321, 296, 1, 0, 0, 0, 321, 
	303, 1, 0, 0, 0, 321, 305, 1, 0, 0, 0, 321, 308, 1, 0, 0, 0, 321, 309, 
	1, 0, 0, 0, 321, 310, 1, 0, 0, 0, 321, 311, 1, 0, 0, 0, 321, 312, 1, 0, 
	0, 0, 321, 313, 1, 0, 0, 0, 321, 314, 1, 0, 0, 0, 321, 315, 1, 0, 0, 0, 
	321, 316, 1, 0, 0, 0, 321, 317, 1, 0, 0, 0, 321, 318, 1, 0, 0, 0, 321, 
	319, 1, 0, 0, 0, 321, 320, 1, 0, 0, 0, 322, 363, 1, 0, 0, 0, 323, 324, 
	10, 20, 0, 0, 324, 325, 7, 6, 0, 0, 325, 362, 3, 40, 20, 21, 326, 327, 
	10, 19, 0, 0, 327, 328, 7, 7, 0, 0, 328, 362, 3, 40, 20, 20, 329, 330, 
	10, 18, 0, 0, 330, 331, 7, 8, 0, 0, 331, 362, 3, 40, 20, 19, 332, 333, 
	10, 17, 0, 0, 333, 334, 7, 9, 0, 0, 334, 362, 3, 40, 20, 18, 335, 336, 
	10, 16, 0, 0, 336, 337, 7, 10, 0, 0, 337, 362, 3, 40, 20, 17, 338, 339, 
	10, 24, 0, 0, 339, 340, 5, 6, 0, 0, 340, 341, 3, 40, 20, 0, 341, 342, 5, 
	7, 0, 0, 342, 343, 5, 10, 0, 0, 343, 344, 3, 38, 19, 0, 344, 345, 5, 11, 
	0, 0, 345, 362, 1, 0, 0, 0, 346, 347, 10, 23, 0, 0, 347, 348, 5, 6, 0, 
	0, 348, 349, 3, 40, 20, 0, 349, 350, 5, 7, 0, 0, 350, 362, 1, 0, 0, 0, 
	351, 352, 10, 22, 0, 0, 352, 353, 5, 3, 0, 0, 353, 354, 5, 76, 0, 0, 354, 
	355, 5, 10, 0, 0, 355, 356, 3, 38, 19, 0, 356, 357, 5, 11, 0, 0, 357, 362, 
	1, 0, 0, 0, 358, 359, 10, 21, 0, 0, 359, 360, 5, 3, 0, 0, 360, 362, 5, 
	76, 0, 0, 361, 323, 1, 0, 0, 0, 361, 326, 1, 0, 0, 0, 361, 329, 1, 0, 0, 
	0, 361, 332, 1, 0, 0, 0, 361, 335, 1, 0, 0, 0, 361, 338, 1, 0, 0, 0, 361, 
	346, 1, 0, 0, 0, 361, 351, 1, 0, 0, 0, 361, 358, 1, 0, 0, 0, 362, 365, 
	1, 0, 0, 0, 363, 361, 1, 0, 0, 0, 363, 364, 1, 0, 0, 0, 364, 41, 1, 0, 
	0, 0, 365, 363, 1, 0, 0, 0, 366, 367, 5, 44, 0, 0, 367, 372, 3, 40, 20, 
	0, 368, 369, 5, 21, 0, 0, 369, 371, 3, 40, 20, 0, 370, 368, 1, 0, 0, 0, 
	371, 374, 1, 0, 0, 0, 372, 370, 1, 0, 0, 0, 372, 373, 1, 0, 0, 0, 373, 
	375, 1, 0, 0, 0, 374, 372, 1, 0, 0, 0, 375, 376, 5, 45, 0, 0, 376, 400, 
	1, 0, 0, 0, 377, 378, 5, 20, 0, 0, 378, 383, 3, 40, 20, 0, 379, 380, 5, 
	21, 0, 0, 380, 382, 3, 40, 20, 0, 381, 379, 1, 0, 0, 0, 382, 385, 1, 0, 
	0, 0, 383, 381, 1, 0, 0, 0, 383, 384, 1, 0, 0, 0, 384, 386, 1, 0, 0, 0, 
	385, 383, 1, 0, 0, 0, 386, 387, 5, 22, 0, 0, 387, 400, 1, 0, 0, 0, 388, 
	389, 5, 6, 0, 0, 389, 394, 3, 40, 20, 0, 390, 391, 5, 21, 0, 0, 391, 393, 
	3, 40, 20, 0, 392, 390, 1, 0, 0, 0, 393, 396, 1, 0, 0, 0, 394, 392, 1, 
	0, 0, 0, 394, 395, 1, 0, 0, 0, 395, 397, 1, 0, 0, 0, 396, 394, 1, 0, 0, 
	0, 397, 398, 5, 7, 0, 0, 398, 400, 1, 0, 0, 0, 399, 366, 1, 0, 0, 0, 399, 
	377, 1, 0, 0, 0, 399, 388, 1, 0, 0, 0, 400, 43, 1, 0, 0, 0, 46, 47, 62, 
	69, 72, 75, 83, 89, 96, 101, 111, 120, 125, 130, 138, 146, 148, 159, 163, 
	172, 180, 184, 199, 206, 211, 217, 222, 226, 234, 242, 249, 257, 261, 271, 
	276, 279, 284, 291, 294, 300, 321, 361, 363, 372, 383, 394, 399,
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
	PaxoParserT__40 = 41
	PaxoParserT__41 = 42
	PaxoParserT__42 = 43
	PaxoParserT__43 = 44
	PaxoParserT__44 = 45
	PaxoParserVAR_TYPE = 46
	PaxoParserNUM_TYPE = 47
	PaxoParserCOMPLEX_TYPE = 48
	PaxoParserCHARA_TYPE = 49
	PaxoParserTRIT_TYPE = 50
	PaxoParserBOOLEAN_TYPE = 51
	PaxoParserPOINTER_TYPE = 52
	PaxoParserFUNC_TYPE = 53
	PaxoParserPKG_TYPE = 54
	PaxoParserINT_TYPE = 55
	PaxoParserPKDEC_TYPE = 56
	PaxoParserCOLOR_TYPE = 57
	PaxoParserGLOBAL = 58
	PaxoParserLOCAL = 59
	PaxoParserTRY = 60
	PaxoParserCATCH = 61
	PaxoParserARROW = 62
	PaxoParserINCLUDE = 63
	PaxoParserRETURN = 64
	PaxoParserTHROW = 65
	PaxoParserPAUSE_MODE = 66
	PaxoParserPLAY_MODE = 67
	PaxoParserINT_LITERAL = 68
	PaxoParserDECIMAL_LITERAL = 69
	PaxoParserCOMPLEX_LITERAL = 70
	PaxoParserBOOLEAN_BIT = 71
	PaxoParserBOOLEAN_TRIT = 72
	PaxoParserPOINTER_LITERAL = 73
	PaxoParserCOLOR_LITERAL = 74
	PaxoParserTHIS_SCOPE = 75
	PaxoParserIDENTIFIER = 76
	PaxoParserSTRING_LITERAL = 77
	PaxoParserCHAR_LITERAL = 78
	PaxoParserLINE_COMMENT = 79
	PaxoParserBLOCK_COMMENT = 80
	PaxoParserWS = 81
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
	PaxoParserRULE_returnStatement = 17
	PaxoParserRULE_throwStatement = 18
	PaxoParserRULE_argumentList = 19
	PaxoParserRULE_expression = 20
	PaxoParserRULE_arrayLiteral = 21
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
	p.SetState(47)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & -6917568610058632126) != 0) || ((int64((_la - 64)) & ^0x3f) == 0 && ((int64(1) << (_la - 64)) & 32755) != 0) {
		{
			p.SetState(44)
			p.Statement()
		}


		p.SetState(49)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_la = p.GetTokenStream().LA(1)
	}
	{
		p.SetState(50)
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
	ThrowStatement() IThrowStatementContext
	ReturnStatement() IReturnStatementContext
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

func (s *StatementContext) ThrowStatement() IThrowStatementContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IThrowStatementContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IThrowStatementContext)
}

func (s *StatementContext) ReturnStatement() IReturnStatementContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IReturnStatementContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IReturnStatementContext)
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

	p.SetState(72)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 3, p.GetParserRuleContext()) {
	case 1:
		p.EnterOuterAlt(localctx, 1)
		{
			p.SetState(52)
			p.Match(PaxoParserT__0)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 2:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(53)
			p.VarDeclaration()
		}


	case 3:
		p.EnterOuterAlt(localctx, 3)
		{
			p.SetState(54)
			p.Assignment()
		}


	case 4:
		p.EnterOuterAlt(localctx, 4)
		{
			p.SetState(55)
			p.CondStatement()
		}


	case 5:
		p.EnterOuterAlt(localctx, 5)
		{
			p.SetState(56)
			p.LoopStatement()
		}


	case 6:
		p.EnterOuterAlt(localctx, 6)
		{
			p.SetState(57)
			p.TryCatchStatement()
		}


	case 7:
		p.EnterOuterAlt(localctx, 7)
		{
			p.SetState(58)
			p.ThrowStatement()
		}


	case 8:
		p.EnterOuterAlt(localctx, 8)
		{
			p.SetState(59)
			p.ReturnStatement()
		}


	case 9:
		p.EnterOuterAlt(localctx, 9)
		{
			p.SetState(60)
			p.expression(0)
		}
		p.SetState(62)
		p.GetErrorHandler().Sync(p)


		if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 1, p.GetParserRuleContext()) == 1 {
			{
				p.SetState(61)
				p.Match(PaxoParserT__0)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

			} else if p.HasError() { // JIM
				goto errorExit
		}


	case 10:
		p.EnterOuterAlt(localctx, 10)
		{
			p.SetState(64)
			p.Match(PaxoParserINCLUDE)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(65)
			p.Match(PaxoParserT__1)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(66)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(69)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		if _la == PaxoParserT__2 {
			{
				p.SetState(67)
				p.Match(PaxoParserT__2)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(68)
				p.Match(PaxoParserIDENTIFIER)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

		}
		{
			p.SetState(71)
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
	Type_() ITypeContext
	IDENTIFIER() antlr.TerminalNode
	Expression() IExpressionContext
	Scope() IScopeContext
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

	p.SetState(101)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 8, p.GetParserRuleContext()) {
	case 1:
		p.EnterOuterAlt(localctx, 1)
		p.SetState(75)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		if _la == PaxoParserGLOBAL || _la == PaxoParserLOCAL {
			{
				p.SetState(74)
				p.Scope()
			}

		}
		{
			p.SetState(77)
			p.Type_()
		}
		{
			p.SetState(78)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(79)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(80)
			p.expression(0)
		}


	case 2:
		p.EnterOuterAlt(localctx, 2)
		p.SetState(83)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		if _la == PaxoParserGLOBAL || _la == PaxoParserLOCAL {
			{
				p.SetState(82)
				p.Scope()
			}

		}
		{
			p.SetState(85)
			p.Type_()
		}
		{
			p.SetState(86)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(87)
			p.Match(PaxoParserT__5)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(89)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		if _la == PaxoParserINT_LITERAL {
			{
				p.SetState(88)
				p.Match(PaxoParserINT_LITERAL)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

		}
		{
			p.SetState(91)
			p.Match(PaxoParserT__6)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(92)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(93)
			p.ArrayLiteral()
		}


	case 3:
		p.EnterOuterAlt(localctx, 3)
		p.SetState(96)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		if _la == PaxoParserGLOBAL || _la == PaxoParserLOCAL {
			{
				p.SetState(95)
				p.Scope()
			}

		}
		{
			p.SetState(98)
			p.Type_()
		}
		{
			p.SetState(99)
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
	FUNC_TYPE() antlr.TerminalNode
	PKG_TYPE() antlr.TerminalNode
	INT_TYPE() antlr.TerminalNode
	PKDEC_TYPE() antlr.TerminalNode
	COLOR_TYPE() antlr.TerminalNode
	COMPLEX_TYPE() antlr.TerminalNode

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

func (s *TypeContext) FUNC_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserFUNC_TYPE, 0)
}

func (s *TypeContext) PKG_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserPKG_TYPE, 0)
}

func (s *TypeContext) INT_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserINT_TYPE, 0)
}

func (s *TypeContext) PKDEC_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserPKDEC_TYPE, 0)
}

func (s *TypeContext) COLOR_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserCOLOR_TYPE, 0)
}

func (s *TypeContext) COMPLEX_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserCOMPLEX_TYPE, 0)
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
		p.SetState(103)
		_la = p.GetTokenStream().LA(1)

		if !(((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 288160007407534080) != 0)) {
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
		p.SetState(105)
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
	AllExpression() []IExpressionContext
	Expression(i int) IExpressionContext
	THIS_SCOPE() antlr.TerminalNode

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

func (s *AssignmentContext) AllExpression() []IExpressionContext {
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

func (s *AssignmentContext) Expression(i int) IExpressionContext {
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

func (s *AssignmentContext) THIS_SCOPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserTHIS_SCOPE, 0)
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
	p.SetState(148)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 15, p.GetParserRuleContext()) {
	case 1:
		p.EnterOuterAlt(localctx, 1)
		{
			p.SetState(107)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(108)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(109)
			p.expression(0)
		}
		p.SetState(111)
		p.GetErrorHandler().Sync(p)


		if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 9, p.GetParserRuleContext()) == 1 {
			{
				p.SetState(110)
				p.Match(PaxoParserT__0)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

			} else if p.HasError() { // JIM
				goto errorExit
		}


	case 2:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(113)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(114)
			p.Match(PaxoParserT__5)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(115)
			p.expression(0)
		}
		{
			p.SetState(116)
			p.Match(PaxoParserT__6)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(117)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(118)
			p.expression(0)
		}
		p.SetState(120)
		p.GetErrorHandler().Sync(p)


		if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 10, p.GetParserRuleContext()) == 1 {
			{
				p.SetState(119)
				p.Match(PaxoParserT__0)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

			} else if p.HasError() { // JIM
				goto errorExit
		}


	case 3:
		p.EnterOuterAlt(localctx, 3)
		{
			p.SetState(122)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(123)
			p.Match(PaxoParserT__7)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(125)
		p.GetErrorHandler().Sync(p)


		if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 11, p.GetParserRuleContext()) == 1 {
			{
				p.SetState(124)
				p.Match(PaxoParserT__0)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

			} else if p.HasError() { // JIM
				goto errorExit
		}


	case 4:
		p.EnterOuterAlt(localctx, 4)
		{
			p.SetState(127)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(128)
			p.Match(PaxoParserT__8)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(130)
		p.GetErrorHandler().Sync(p)


		if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 12, p.GetParserRuleContext()) == 1 {
			{
				p.SetState(129)
				p.Match(PaxoParserT__0)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

			} else if p.HasError() { // JIM
				goto errorExit
		}


	case 5:
		p.EnterOuterAlt(localctx, 5)
		{
			p.SetState(132)
			p.expression(0)
		}
		{
			p.SetState(133)
			p.Match(PaxoParserT__2)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(134)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(135)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(136)
			p.expression(0)
		}
		p.SetState(138)
		p.GetErrorHandler().Sync(p)


		if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 13, p.GetParserRuleContext()) == 1 {
			{
				p.SetState(137)
				p.Match(PaxoParserT__0)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

			} else if p.HasError() { // JIM
				goto errorExit
		}


	case 6:
		p.EnterOuterAlt(localctx, 6)
		{
			p.SetState(140)
			p.Match(PaxoParserTHIS_SCOPE)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(141)
			p.Match(PaxoParserT__2)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(142)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(143)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(144)
			p.expression(0)
		}
		p.SetState(146)
		p.GetErrorHandler().Sync(p)


		if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 14, p.GetParserRuleContext()) == 1 {
			{
				p.SetState(145)
				p.Match(PaxoParserT__0)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

			} else if p.HasError() { // JIM
				goto errorExit
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
		p.SetState(150)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(151)
		p.expression(0)
	}
	{
		p.SetState(152)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(153)
		p.Match(PaxoParserT__11)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(154)
		p.MatchCase()
	}
	p.SetState(159)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 16, p.GetParserRuleContext())
	if p.HasError() {
		goto errorExit
	}
	for _alt != 1 && _alt != antlr.ATNInvalidAltNumber {
		if _alt == 1+1 {
			{
				p.SetState(155)
				p.Match(PaxoParserT__12)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(156)
				p.MatchCase()
			}


		}
		p.SetState(161)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 16, p.GetParserRuleContext())
		if p.HasError() {
			goto errorExit
		}
	}
	p.SetState(163)
	p.GetErrorHandler().Sync(p)


	if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 17, p.GetParserRuleContext()) == 1 {
		{
			p.SetState(162)
			p.Match(PaxoParserT__0)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}

		} else if p.HasError() { // JIM
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
	p.SetState(172)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetTokenStream().LA(1) {
	case PaxoParserT__5, PaxoParserT__9, PaxoParserT__19, PaxoParserT__41, PaxoParserT__42, PaxoParserT__43, PaxoParserINT_LITERAL, PaxoParserDECIMAL_LITERAL, PaxoParserCOMPLEX_LITERAL, PaxoParserBOOLEAN_BIT, PaxoParserBOOLEAN_TRIT, PaxoParserPOINTER_LITERAL, PaxoParserCOLOR_LITERAL, PaxoParserTHIS_SCOPE, PaxoParserIDENTIFIER, PaxoParserSTRING_LITERAL, PaxoParserCHAR_LITERAL:
		p.EnterOuterAlt(localctx, 1)
		{
			p.SetState(165)
			p.expression(0)
		}
		{
			p.SetState(166)
			p.Match(PaxoParserT__13)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(167)
			p.Block()
		}


	case PaxoParserT__14:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(169)
			p.Match(PaxoParserT__14)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(170)
			p.Match(PaxoParserT__13)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(171)
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
	Block() IBlockContext
	LoopDelimiter() ILoopDelimiterContext
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
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(174)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(175)
		p.expression(0)
	}
	{
		p.SetState(176)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(177)
		p.Match(PaxoParserT__12)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(178)
		p.LoopMode()
	}
	p.SetState(180)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	if _la == PaxoParserT__15 || _la == PaxoParserT__16 {
		{
			p.SetState(179)
			p.LoopDelimiter()
		}

	}
	{
		p.SetState(182)
		p.Block()
	}
	p.SetState(184)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	if _la == PaxoParserT__17 || _la == PaxoParserT__18 {
		{
			p.SetState(183)
			p.LoopEndDelimiter()
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
		p.SetState(186)
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
		p.SetState(188)
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
		p.SetState(190)
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
		p.SetState(192)
		p.Match(PaxoParserTRY)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(193)
		p.Block()
	}
	{
		p.SetState(194)
		p.Match(PaxoParserCATCH)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(195)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(196)
		p.Match(PaxoParserIDENTIFIER)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(199)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	if _la == PaxoParserT__2 {
		{
			p.SetState(197)
			p.Match(PaxoParserT__2)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(198)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}

	}
	{
		p.SetState(201)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(202)
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
	Block() IBlockContext
	ParameterList() IParameterListContext
	Type_() ITypeContext

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
		p.SetState(204)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(206)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	if ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 288160007407534080) != 0) {
		{
			p.SetState(205)
			p.ParameterList()
		}

	}
	{
		p.SetState(208)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(211)
	p.GetErrorHandler().Sync(p)


	if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 23, p.GetParserRuleContext()) == 1 {
		{
			p.SetState(209)
			p.Match(PaxoParserT__12)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(210)
			p.Type_()
		}

		} else if p.HasError() { // JIM
			goto errorExit
	}
	{
		p.SetState(213)
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

	var _alt int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(215)
		p.Match(PaxoParserT__19)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(222)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 25, p.GetParserRuleContext())
	if p.HasError() {
		goto errorExit
	}
	for _alt != 2 && _alt != antlr.ATNInvalidAltNumber {
		if _alt == 1 {
			p.SetState(217)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
				goto errorExit
			}
			_la = p.GetTokenStream().LA(1)


			if _la == PaxoParserT__20 {
				{
					p.SetState(216)
					p.Match(PaxoParserT__20)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}

			}
			{
				p.SetState(219)
				p.VarDeclaration()
			}


		}
		p.SetState(224)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 25, p.GetParserRuleContext())
		if p.HasError() {
			goto errorExit
		}
	}
	p.SetState(226)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	if _la == PaxoParserT__20 {
		{
			p.SetState(225)
			p.Match(PaxoParserT__20)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}

	}
	{
		p.SetState(228)
		p.Match(PaxoParserT__21)
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

	var _alt int

	p.SetState(261)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 31, p.GetParserRuleContext()) {
	case 1:
		p.EnterOuterAlt(localctx, 1)
		{
			p.SetState(230)
			p.Match(PaxoParserT__19)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(234)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		for ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & -6917568610058632126) != 0) || ((int64((_la - 64)) & ^0x3f) == 0 && ((int64(1) << (_la - 64)) & 32755) != 0) {
			{
				p.SetState(231)
				p.Statement()
			}


			p.SetState(236)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
		    	goto errorExit
		    }
			_la = p.GetTokenStream().LA(1)
		}
		{
			p.SetState(237)
			p.Match(PaxoParserT__21)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 2:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(238)
			p.Match(PaxoParserT__12)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(242)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		for ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & -6917568610058632126) != 0) || ((int64((_la - 64)) & ^0x3f) == 0 && ((int64(1) << (_la - 64)) & 32755) != 0) {
			{
				p.SetState(239)
				p.Statement()
			}


			p.SetState(244)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
		    	goto errorExit
		    }
			_la = p.GetTokenStream().LA(1)
		}
		{
			p.SetState(245)
			p.Match(PaxoParserT__22)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 3:
		p.EnterOuterAlt(localctx, 3)
		p.SetState(249)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		for ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & -6917568610058632126) != 0) || ((int64((_la - 64)) & ^0x3f) == 0 && ((int64(1) << (_la - 64)) & 32755) != 0) {
			{
				p.SetState(246)
				p.Statement()
			}


			p.SetState(251)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
		    	goto errorExit
		    }
			_la = p.GetTokenStream().LA(1)
		}
		{
			p.SetState(252)
			p.Match(PaxoParserT__23)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 4:
		p.EnterOuterAlt(localctx, 4)
		{
			p.SetState(253)
			p.Match(PaxoParserT__12)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(257)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 30, p.GetParserRuleContext())
		if p.HasError() {
			goto errorExit
		}
		for _alt != 2 && _alt != antlr.ATNInvalidAltNumber {
			if _alt == 1 {
				{
					p.SetState(254)
					p.Statement()
				}


			}
			p.SetState(259)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
		    	goto errorExit
		    }
			_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 30, p.GetParserRuleContext())
			if p.HasError() {
				goto errorExit
			}
		}
		{
			p.SetState(260)
			p.Match(PaxoParserT__0)
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
		p.SetState(263)
		p.Type_()
	}
	{
		p.SetState(264)
		p.Match(PaxoParserIDENTIFIER)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(271)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for _la == PaxoParserT__20 {
		{
			p.SetState(265)
			p.Match(PaxoParserT__20)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(266)
			p.Type_()
		}
		{
			p.SetState(267)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


		p.SetState(273)
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


// IReturnStatementContext is an interface to support dynamic dispatch.
type IReturnStatementContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	RETURN() antlr.TerminalNode
	Expression() IExpressionContext

	// IsReturnStatementContext differentiates from other interfaces.
	IsReturnStatementContext()
}

type ReturnStatementContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyReturnStatementContext() *ReturnStatementContext {
	var p = new(ReturnStatementContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_returnStatement
	return p
}

func InitEmptyReturnStatementContext(p *ReturnStatementContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_returnStatement
}

func (*ReturnStatementContext) IsReturnStatementContext() {}

func NewReturnStatementContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *ReturnStatementContext {
	var p = new(ReturnStatementContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_returnStatement

	return p
}

func (s *ReturnStatementContext) GetParser() antlr.Parser { return s.parser }

func (s *ReturnStatementContext) RETURN() antlr.TerminalNode {
	return s.GetToken(PaxoParserRETURN, 0)
}

func (s *ReturnStatementContext) Expression() IExpressionContext {
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

func (s *ReturnStatementContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ReturnStatementContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *ReturnStatementContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterReturnStatement(s)
	}
}

func (s *ReturnStatementContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitReturnStatement(s)
	}
}




func (p *PaxoParser) ReturnStatement() (localctx IReturnStatementContext) {
	localctx = NewReturnStatementContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 34, PaxoParserRULE_returnStatement)
	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(274)
		p.Match(PaxoParserRETURN)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(276)
	p.GetErrorHandler().Sync(p)


	if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 33, p.GetParserRuleContext()) == 1 {
		{
			p.SetState(275)
			p.expression(0)
		}

		} else if p.HasError() { // JIM
			goto errorExit
	}
	p.SetState(279)
	p.GetErrorHandler().Sync(p)


	if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 34, p.GetParserRuleContext()) == 1 {
		{
			p.SetState(278)
			p.Match(PaxoParserT__0)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}

		} else if p.HasError() { // JIM
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


// IThrowStatementContext is an interface to support dynamic dispatch.
type IThrowStatementContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	THROW() antlr.TerminalNode
	Expression() IExpressionContext

	// IsThrowStatementContext differentiates from other interfaces.
	IsThrowStatementContext()
}

type ThrowStatementContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyThrowStatementContext() *ThrowStatementContext {
	var p = new(ThrowStatementContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_throwStatement
	return p
}

func InitEmptyThrowStatementContext(p *ThrowStatementContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_throwStatement
}

func (*ThrowStatementContext) IsThrowStatementContext() {}

func NewThrowStatementContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *ThrowStatementContext {
	var p = new(ThrowStatementContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_throwStatement

	return p
}

func (s *ThrowStatementContext) GetParser() antlr.Parser { return s.parser }

func (s *ThrowStatementContext) THROW() antlr.TerminalNode {
	return s.GetToken(PaxoParserTHROW, 0)
}

func (s *ThrowStatementContext) Expression() IExpressionContext {
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

func (s *ThrowStatementContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ThrowStatementContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *ThrowStatementContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterThrowStatement(s)
	}
}

func (s *ThrowStatementContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitThrowStatement(s)
	}
}




func (p *PaxoParser) ThrowStatement() (localctx IThrowStatementContext) {
	localctx = NewThrowStatementContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 36, PaxoParserRULE_throwStatement)
	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(281)
		p.Match(PaxoParserTHROW)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(282)
		p.expression(0)
	}
	p.SetState(284)
	p.GetErrorHandler().Sync(p)


	if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 35, p.GetParserRuleContext()) == 1 {
		{
			p.SetState(283)
			p.Match(PaxoParserT__0)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}

		} else if p.HasError() { // JIM
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
	p.EnterRule(localctx, 38, PaxoParserRULE_argumentList)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	p.SetState(294)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	if ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 30786326627392) != 0) || ((int64((_la - 68)) & ^0x3f) == 0 && ((int64(1) << (_la - 68)) & 2047) != 0) {
		{
			p.SetState(286)
			p.expression(0)
		}
		p.SetState(291)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		for _la == PaxoParserT__20 {
			{
				p.SetState(287)
				p.Match(PaxoParserT__20)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(288)
				p.expression(0)
			}


			p.SetState(293)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
		    	goto errorExit
		    }
			_la = p.GetTokenStream().LA(1)
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


type ThisScopeExprContext struct {
	ExpressionContext
}

func NewThisScopeExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *ThisScopeExprContext {
	var p = new(ThisScopeExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *ThisScopeExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ThisScopeExprContext) THIS_SCOPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserTHIS_SCOPE, 0)
}

func (s *ThisScopeExprContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}


func (s *ThisScopeExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterThisScopeExpr(s)
	}
}

func (s *ThisScopeExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitThisScopeExpr(s)
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


type ColLitExprContext struct {
	ExpressionContext
}

func NewColLitExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *ColLitExprContext {
	var p = new(ColLitExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *ColLitExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ColLitExprContext) COLOR_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserCOLOR_LITERAL, 0)
}


func (s *ColLitExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterColLitExpr(s)
	}
}

func (s *ColLitExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitColLitExpr(s)
	}
}


type ComLitExprContext struct {
	ExpressionContext
}

func NewComLitExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *ComLitExprContext {
	var p = new(ComLitExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *ComLitExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *ComLitExprContext) COMPLEX_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserCOMPLEX_LITERAL, 0)
}


func (s *ComLitExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterComLitExpr(s)
	}
}

func (s *ComLitExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitComLitExpr(s)
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


type IndexedCallExprContext struct {
	ExpressionContext
}

func NewIndexedCallExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *IndexedCallExprContext {
	var p = new(IndexedCallExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *IndexedCallExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *IndexedCallExprContext) AllExpression() []IExpressionContext {
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

func (s *IndexedCallExprContext) Expression(i int) IExpressionContext {
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

func (s *IndexedCallExprContext) ArgumentList() IArgumentListContext {
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


func (s *IndexedCallExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterIndexedCallExpr(s)
	}
}

func (s *IndexedCallExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitIndexedCallExpr(s)
	}
}


type IndexedAccessExprContext struct {
	ExpressionContext
}

func NewIndexedAccessExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *IndexedAccessExprContext {
	var p = new(IndexedAccessExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *IndexedAccessExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *IndexedAccessExprContext) AllExpression() []IExpressionContext {
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

func (s *IndexedAccessExprContext) Expression(i int) IExpressionContext {
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


func (s *IndexedAccessExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterIndexedAccessExpr(s)
	}
}

func (s *IndexedAccessExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitIndexedAccessExpr(s)
	}
}


type MethodCallExprContext struct {
	ExpressionContext
}

func NewMethodCallExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *MethodCallExprContext {
	var p = new(MethodCallExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *MethodCallExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *MethodCallExprContext) Expression() IExpressionContext {
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

func (s *MethodCallExprContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}

func (s *MethodCallExprContext) ArgumentList() IArgumentListContext {
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


func (s *MethodCallExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterMethodCallExpr(s)
	}
}

func (s *MethodCallExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitMethodCallExpr(s)
	}
}


type DotAccessExprContext struct {
	ExpressionContext
}

func NewDotAccessExprContext(parser antlr.Parser, ctx antlr.ParserRuleContext) *DotAccessExprContext {
	var p = new(DotAccessExprContext)

	InitEmptyExpressionContext(&p.ExpressionContext)
	p.parser = parser
	p.CopyAll(ctx.(*ExpressionContext))

	return p
}

func (s *DotAccessExprContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *DotAccessExprContext) Expression() IExpressionContext {
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

func (s *DotAccessExprContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}


func (s *DotAccessExprContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterDotAccessExpr(s)
	}
}

func (s *DotAccessExprContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitDotAccessExpr(s)
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
	_startState := 40
	p.EnterRecursionRule(localctx, 40, PaxoParserRULE_expression, _p)
	var _la int

	var _alt int

	p.EnterOuterAlt(localctx, 1)
	p.SetState(321)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 39, p.GetParserRuleContext()) {
	case 1:
		localctx = NewCallExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx

		{
			p.SetState(297)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(298)
			p.Match(PaxoParserT__9)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(300)
		p.GetErrorHandler().Sync(p)


		if p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 38, p.GetParserRuleContext()) == 1 {
			{
				p.SetState(299)
				p.ArgumentList()
			}

			} else if p.HasError() { // JIM
				goto errorExit
		}
		{
			p.SetState(302)
			p.Match(PaxoParserT__10)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 2:
		localctx = NewNotgateExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(303)
			_la = p.GetTokenStream().LA(1)

			if !(_la == PaxoParserT__41 || _la == PaxoParserT__42) {
				p.GetErrorHandler().RecoverInline(p)
			} else {
				p.GetErrorHandler().ReportMatch(p)
				p.Consume()
			}
		}
		{
			p.SetState(304)
			p.expression(15)
		}


	case 3:
		localctx = NewThisScopeExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(305)
			p.Match(PaxoParserTHIS_SCOPE)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(306)
			p.Match(PaxoParserT__2)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(307)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 4:
		localctx = NewIntLitExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(308)
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
			p.SetState(309)
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
			p.SetState(310)
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
			p.SetState(311)
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
			p.SetState(312)
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
			p.SetState(313)
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
			p.SetState(314)
			p.Match(PaxoParserPOINTER_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 11:
		localctx = NewColLitExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(315)
			p.Match(PaxoParserCOLOR_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 12:
		localctx = NewComLitExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(316)
			p.Match(PaxoParserCOMPLEX_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 13:
		localctx = NewArrayLitExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(317)
			p.ArrayLiteral()
		}


	case 14:
		localctx = NewIdentExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(318)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 15:
		localctx = NewPkgExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(319)
			p.PkgDeclaration()
		}


	case 16:
		localctx = NewFuncExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx
		{
			p.SetState(320)
			p.FunctionDeclaration()
		}

	case antlr.ATNInvalidAltNumber:
		goto errorExit
	}
	p.GetParserRuleContext().SetStop(p.GetTokenStream().LT(-1))
	p.SetState(363)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 41, p.GetParserRuleContext())
	if p.HasError() {
		goto errorExit
	}
	for _alt != 2 && _alt != antlr.ATNInvalidAltNumber {
		if _alt == 1 {
			if p.GetParseListeners() != nil {
				p.TriggerExitRuleEvent()
			}
			_prevctx = localctx
			p.SetState(361)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
				goto errorExit
			}

			switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 40, p.GetParserRuleContext()) {
			case 1:
				localctx = NewMultDivExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(323)

				if !(p.Precpred(p.GetParserRuleContext(), 20)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 20)", ""))
					goto errorExit
				}
				{
					p.SetState(324)
					_la = p.GetTokenStream().LA(1)

					if !(_la == PaxoParserT__24 || _la == PaxoParserT__25) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(325)
					p.expression(21)
				}


			case 2:
				localctx = NewAddSubExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(326)

				if !(p.Precpred(p.GetParserRuleContext(), 19)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 19)", ""))
					goto errorExit
				}
				{
					p.SetState(327)
					_la = p.GetTokenStream().LA(1)

					if !(_la == PaxoParserT__26 || _la == PaxoParserT__27) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(328)
					p.expression(20)
				}


			case 3:
				localctx = NewShiftExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(329)

				if !(p.Precpred(p.GetParserRuleContext(), 18)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 18)", ""))
					goto errorExit
				}
				{
					p.SetState(330)
					_la = p.GetTokenStream().LA(1)

					if !(_la == PaxoParserT__28 || _la == PaxoParserT__29) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(331)
					p.expression(19)
				}


			case 4:
				localctx = NewRelationalExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(332)

				if !(p.Precpred(p.GetParserRuleContext(), 17)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 17)", ""))
					goto errorExit
				}
				{
					p.SetState(333)
					_la = p.GetTokenStream().LA(1)

					if !(((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 272730423316) != 0)) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(334)
					p.expression(18)
				}


			case 5:
				localctx = NewBitwiseExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(335)

				if !(p.Precpred(p.GetParserRuleContext(), 16)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 16)", ""))
					goto errorExit
				}
				{
					p.SetState(336)
					_la = p.GetTokenStream().LA(1)

					if !(((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 4123168604160) != 0)) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(337)
					p.expression(17)
				}


			case 6:
				localctx = NewIndexedCallExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(338)

				if !(p.Precpred(p.GetParserRuleContext(), 24)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 24)", ""))
					goto errorExit
				}
				{
					p.SetState(339)
					p.Match(PaxoParserT__5)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}
				{
					p.SetState(340)
					p.expression(0)
				}
				{
					p.SetState(341)
					p.Match(PaxoParserT__6)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}
				{
					p.SetState(342)
					p.Match(PaxoParserT__9)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}
				{
					p.SetState(343)
					p.ArgumentList()
				}
				{
					p.SetState(344)
					p.Match(PaxoParserT__10)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}


			case 7:
				localctx = NewIndexedAccessExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(346)

				if !(p.Precpred(p.GetParserRuleContext(), 23)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 23)", ""))
					goto errorExit
				}
				{
					p.SetState(347)
					p.Match(PaxoParserT__5)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}
				{
					p.SetState(348)
					p.expression(0)
				}
				{
					p.SetState(349)
					p.Match(PaxoParserT__6)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}


			case 8:
				localctx = NewMethodCallExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(351)

				if !(p.Precpred(p.GetParserRuleContext(), 22)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 22)", ""))
					goto errorExit
				}
				{
					p.SetState(352)
					p.Match(PaxoParserT__2)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}
				{
					p.SetState(353)
					p.Match(PaxoParserIDENTIFIER)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}
				{
					p.SetState(354)
					p.Match(PaxoParserT__9)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}
				{
					p.SetState(355)
					p.ArgumentList()
				}
				{
					p.SetState(356)
					p.Match(PaxoParserT__10)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}


			case 9:
				localctx = NewDotAccessExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(358)

				if !(p.Precpred(p.GetParserRuleContext(), 21)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 21)", ""))
					goto errorExit
				}
				{
					p.SetState(359)
					p.Match(PaxoParserT__2)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}
				{
					p.SetState(360)
					p.Match(PaxoParserIDENTIFIER)
					if p.HasError() {
							// Recognition error - abort rule
							goto errorExit
					}
				}

			case antlr.ATNInvalidAltNumber:
				goto errorExit
			}

		}
		p.SetState(365)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 41, p.GetParserRuleContext())
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
	p.EnterRule(localctx, 42, PaxoParserRULE_arrayLiteral)
	var _la int

	p.SetState(399)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetTokenStream().LA(1) {
	case PaxoParserT__43:
		p.EnterOuterAlt(localctx, 1)
		{
			p.SetState(366)
			p.Match(PaxoParserT__43)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(367)
			p.expression(0)
		}
		p.SetState(372)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		for _la == PaxoParserT__20 {
			{
				p.SetState(368)
				p.Match(PaxoParserT__20)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(369)
				p.expression(0)
			}


			p.SetState(374)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
		    	goto errorExit
		    }
			_la = p.GetTokenStream().LA(1)
		}
		{
			p.SetState(375)
			p.Match(PaxoParserT__44)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case PaxoParserT__19:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(377)
			p.Match(PaxoParserT__19)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(378)
			p.expression(0)
		}
		p.SetState(383)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		for _la == PaxoParserT__20 {
			{
				p.SetState(379)
				p.Match(PaxoParserT__20)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(380)
				p.expression(0)
			}


			p.SetState(385)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
		    	goto errorExit
		    }
			_la = p.GetTokenStream().LA(1)
		}
		{
			p.SetState(386)
			p.Match(PaxoParserT__21)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case PaxoParserT__5:
		p.EnterOuterAlt(localctx, 3)
		{
			p.SetState(388)
			p.Match(PaxoParserT__5)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(389)
			p.expression(0)
		}
		p.SetState(394)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		for _la == PaxoParserT__20 {
			{
				p.SetState(390)
				p.Match(PaxoParserT__20)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(391)
				p.expression(0)
			}


			p.SetState(396)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
		    	goto errorExit
		    }
			_la = p.GetTokenStream().LA(1)
		}
		{
			p.SetState(397)
			p.Match(PaxoParserT__6)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
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


func (p *PaxoParser) Sempred(localctx antlr.RuleContext, ruleIndex, predIndex int) bool {
	switch ruleIndex {
	case 20:
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
			return p.Precpred(p.GetParserRuleContext(), 20)

	case 1:
			return p.Precpred(p.GetParserRuleContext(), 19)

	case 2:
			return p.Precpred(p.GetParserRuleContext(), 18)

	case 3:
			return p.Precpred(p.GetParserRuleContext(), 17)

	case 4:
			return p.Precpred(p.GetParserRuleContext(), 16)

	case 5:
			return p.Precpred(p.GetParserRuleContext(), 24)

	case 6:
			return p.Precpred(p.GetParserRuleContext(), 23)

	case 7:
			return p.Precpred(p.GetParserRuleContext(), 22)

	case 8:
			return p.Precpred(p.GetParserRuleContext(), 21)

	default:
		panic("No predicate with index: " + fmt.Sprint(predIndex))
	}
}

