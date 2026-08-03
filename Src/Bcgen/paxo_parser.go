
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
    "'('", "')'", "'{'", "'}'", "'->'", "'_'", "':'", "'|:'", "'\\U0001D106'", 
    "':|'", "'\\U0001D107'", "'fx'", "','", "'\\u00F7'", "'\\u00D7'", "'+'", 
    "'-'", "'\\u2022\\u00AB'", "'\\u00BB\\u2022'", "'\\u2264'", "'\\u2265'", 
    "'=='", "'\\u2260'", "'&'", "'|'", "'.&'", "'.|'", "'!'", "'.!'", "'\\u00AB'", 
    "'\\u00BB'", "", "", "", "'bit'", "", "", "", "'\\u2192'",
  }
  staticData.SymbolicNames = []string{
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
    "", "", "", "", "", "", "", "NUMBER_TYPE", "COMPLEX_TYPE", "CHAR_TYPE", 
    "BOOL_TYPE", "PKG", "TRY", "CATCH", "ARROW", "INCLUDE", "PAUSE_MODE", 
    "PLAY_MODE", "INT_LITERAL", "DECIMAL_LITERAL", "BOOLEAN_BIT", "BOOLEAN_TRIT", 
    "COMPLEX_LITERAL", "IDENTIFIER", "STRING_LITERAL", "CHAR_LITERAL", "LINE_COMMENT", 
    "BLOCK_COMMENT", "WS",
  }
  staticData.RuleNames = []string{
    "program", "statement", "varDeclaration", "type", "assignment", "ifElseStatement", 
    "matchStatement", "matchCase", "loopStatement", "loopMode", "loopDelimiter", 
    "loopEndDelimiter", "tryCatchStatement", "functionDeclaration", "pkgDeclaration", 
    "block", "parameterList", "argumentList", "expression", "arrayLiteral", 
    "arrayAccess",
  }
  staticData.PredictionContextCache = antlr.NewPredictionContextCache()
  staticData.serializedATN = []int32{
	4, 1, 62, 281, 2, 0, 7, 0, 2, 1, 7, 1, 2, 2, 7, 2, 2, 3, 7, 3, 2, 4, 7, 
	4, 2, 5, 7, 5, 2, 6, 7, 6, 2, 7, 7, 7, 2, 8, 7, 8, 2, 9, 7, 9, 2, 10, 7, 
	10, 2, 11, 7, 11, 2, 12, 7, 12, 2, 13, 7, 13, 2, 14, 7, 14, 2, 15, 7, 15, 
	2, 16, 7, 16, 2, 17, 7, 17, 2, 18, 7, 18, 2, 19, 7, 19, 2, 20, 7, 20, 1, 
	0, 5, 0, 44, 8, 0, 10, 0, 12, 0, 47, 9, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 3, 1, 67, 8, 1, 1, 1, 3, 1, 70, 8, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 
	2, 1, 2, 1, 2, 1, 2, 1, 2, 3, 2, 81, 8, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 
	1, 2, 1, 2, 3, 2, 90, 8, 2, 1, 3, 1, 3, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 
	4, 1, 4, 3, 4, 101, 8, 4, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 
	5, 1, 5, 1, 5, 5, 5, 113, 8, 5, 10, 5, 12, 5, 116, 9, 5, 1, 5, 1, 5, 3, 
	5, 120, 8, 5, 1, 6, 1, 6, 1, 6, 1, 6, 1, 6, 4, 6, 127, 8, 6, 11, 6, 12, 
	6, 128, 1, 6, 1, 6, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 3, 7, 140, 
	8, 7, 1, 8, 1, 8, 1, 8, 1, 8, 1, 8, 1, 8, 1, 8, 1, 8, 1, 8, 1, 9, 1, 9, 
	1, 10, 1, 10, 1, 11, 1, 11, 1, 12, 1, 12, 1, 12, 1, 12, 1, 12, 1, 12, 1, 
	12, 3, 12, 164, 8, 12, 1, 12, 1, 12, 1, 12, 1, 13, 1, 13, 1, 13, 1, 13, 
	3, 13, 173, 8, 13, 1, 13, 1, 13, 1, 13, 1, 14, 1, 14, 1, 14, 1, 14, 1, 
	14, 1, 14, 5, 14, 184, 8, 14, 10, 14, 12, 14, 187, 9, 14, 1, 14, 1, 14, 
	1, 15, 1, 15, 5, 15, 193, 8, 15, 10, 15, 12, 15, 196, 9, 15, 1, 15, 1, 
	15, 1, 16, 1, 16, 1, 16, 1, 16, 1, 16, 1, 16, 5, 16, 206, 8, 16, 10, 16, 
	12, 16, 209, 9, 16, 1, 17, 1, 17, 1, 17, 5, 17, 214, 8, 17, 10, 17, 12, 
	17, 217, 9, 17, 1, 18, 1, 18, 1, 18, 1, 18, 3, 18, 223, 8, 18, 1, 18, 1, 
	18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 
	1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 3, 18, 243, 8, 18, 1, 18, 1, 
	18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 1, 18, 
	1, 18, 1, 18, 1, 18, 5, 18, 260, 8, 18, 10, 18, 12, 18, 263, 9, 18, 1, 
	19, 1, 19, 1, 19, 1, 19, 5, 19, 269, 8, 19, 10, 19, 12, 19, 272, 9, 19, 
	1, 19, 1, 19, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 20, 1, 114, 1, 36, 
	21, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 
	36, 38, 40, 0, 10, 1, 0, 41, 44, 1, 0, 50, 51, 1, 0, 17, 18, 1, 0, 19, 
	20, 1, 0, 37, 38, 1, 0, 23, 24, 1, 0, 25, 26, 1, 0, 27, 28, 3, 0, 2, 2, 
	4, 4, 29, 32, 1, 0, 33, 36, 305, 0, 45, 1, 0, 0, 0, 2, 69, 1, 0, 0, 0, 
	4, 89, 1, 0, 0, 0, 6, 91, 1, 0, 0, 0, 8, 100, 1, 0, 0, 0, 10, 102, 1, 0, 
	0, 0, 12, 121, 1, 0, 0, 0, 14, 139, 1, 0, 0, 0, 16, 141, 1, 0, 0, 0, 18, 
	150, 1, 0, 0, 0, 20, 152, 1, 0, 0, 0, 22, 154, 1, 0, 0, 0, 24, 156, 1, 
	0, 0, 0, 26, 168, 1, 0, 0, 0, 28, 177, 1, 0, 0, 0, 30, 190, 1, 0, 0, 0, 
	32, 199, 1, 0, 0, 0, 34, 210, 1, 0, 0, 0, 36, 242, 1, 0, 0, 0, 38, 264, 
	1, 0, 0, 0, 40, 275, 1, 0, 0, 0, 42, 44, 3, 2, 1, 0, 43, 42, 1, 0, 0, 0, 
	44, 47, 1, 0, 0, 0, 45, 43, 1, 0, 0, 0, 45, 46, 1, 0, 0, 0, 46, 48, 1, 
	0, 0, 0, 47, 45, 1, 0, 0, 0, 48, 49, 5, 0, 0, 1, 49, 1, 1, 0, 0, 0, 50, 
	70, 3, 4, 2, 0, 51, 70, 3, 8, 4, 0, 52, 70, 3, 12, 6, 0, 53, 70, 3, 10, 
	5, 0, 54, 70, 3, 16, 8, 0, 55, 70, 3, 24, 12, 0, 56, 70, 3, 26, 13, 0, 
	57, 70, 3, 28, 14, 0, 58, 59, 3, 36, 18, 0, 59, 60, 5, 1, 0, 0, 60, 70, 
	1, 0, 0, 0, 61, 62, 5, 49, 0, 0, 62, 63, 5, 2, 0, 0, 63, 66, 5, 57, 0, 
	0, 64, 65, 5, 3, 0, 0, 65, 67, 5, 57, 0, 0, 66, 64, 1, 0, 0, 0, 66, 67, 
	1, 0, 0, 0, 67, 68, 1, 0, 0, 0, 68, 70, 5, 4, 0, 0, 69, 50, 1, 0, 0, 0, 
	69, 51, 1, 0, 0, 0, 69, 52, 1, 0, 0, 0, 69, 53, 1, 0, 0, 0, 69, 54, 1, 
	0, 0, 0, 69, 55, 1, 0, 0, 0, 69, 56, 1, 0, 0, 0, 69, 57, 1, 0, 0, 0, 69, 
	58, 1, 0, 0, 0, 69, 61, 1, 0, 0, 0, 70, 3, 1, 0, 0, 0, 71, 72, 3, 6, 3, 
	0, 72, 73, 5, 57, 0, 0, 73, 74, 5, 5, 0, 0, 74, 75, 3, 36, 18, 0, 75, 90, 
	1, 0, 0, 0, 76, 77, 3, 6, 3, 0, 77, 78, 5, 57, 0, 0, 78, 80, 5, 6, 0, 0, 
	79, 81, 5, 52, 0, 0, 80, 79, 1, 0, 0, 0, 80, 81, 1, 0, 0, 0, 81, 82, 1, 
	0, 0, 0, 82, 83, 5, 7, 0, 0, 83, 84, 5, 5, 0, 0, 84, 85, 3, 38, 19, 0, 
	85, 90, 1, 0, 0, 0, 86, 87, 3, 6, 3, 0, 87, 88, 5, 57, 0, 0, 88, 90, 1, 
	0, 0, 0, 89, 71, 1, 0, 0, 0, 89, 76, 1, 0, 0, 0, 89, 86, 1, 0, 0, 0, 90, 
	5, 1, 0, 0, 0, 91, 92, 7, 0, 0, 0, 92, 7, 1, 0, 0, 0, 93, 94, 5, 57, 0, 
	0, 94, 95, 5, 5, 0, 0, 95, 101, 3, 36, 18, 0, 96, 97, 5, 57, 0, 0, 97, 
	101, 5, 8, 0, 0, 98, 99, 5, 57, 0, 0, 99, 101, 5, 9, 0, 0, 100, 93, 1, 
	0, 0, 0, 100, 96, 1, 0, 0, 0, 100, 98, 1, 0, 0, 0, 101, 9, 1, 0, 0, 0, 
	102, 103, 5, 10, 0, 0, 103, 104, 3, 36, 18, 0, 104, 105, 5, 11, 0, 0, 105, 
	114, 3, 30, 15, 0, 106, 107, 5, 48, 0, 0, 107, 108, 5, 10, 0, 0, 108, 109, 
	3, 36, 18, 0, 109, 110, 5, 11, 0, 0, 110, 111, 3, 30, 15, 0, 111, 113, 
	1, 0, 0, 0, 112, 106, 1, 0, 0, 0, 113, 116, 1, 0, 0, 0, 114, 115, 1, 0, 
	0, 0, 114, 112, 1, 0, 0, 0, 115, 119, 1, 0, 0, 0, 116, 114, 1, 0, 0, 0, 
	117, 118, 5, 48, 0, 0, 118, 120, 3, 30, 15, 0, 119, 117, 1, 0, 0, 0, 119, 
	120, 1, 0, 0, 0, 120, 11, 1, 0, 0, 0, 121, 122, 5, 10, 0, 0, 122, 123, 
	5, 57, 0, 0, 123, 124, 5, 11, 0, 0, 124, 126, 5, 12, 0, 0, 125, 127, 3, 
	14, 7, 0, 126, 125, 1, 0, 0, 0, 127, 128, 1, 0, 0, 0, 128, 126, 1, 0, 0, 
	0, 128, 129, 1, 0, 0, 0, 129, 130, 1, 0, 0, 0, 130, 131, 5, 13, 0, 0, 131, 
	13, 1, 0, 0, 0, 132, 133, 3, 36, 18, 0, 133, 134, 5, 14, 0, 0, 134, 135, 
	3, 30, 15, 0, 135, 140, 1, 0, 0, 0, 136, 137, 5, 15, 0, 0, 137, 138, 5, 
	14, 0, 0, 138, 140, 3, 30, 15, 0, 139, 132, 1, 0, 0, 0, 139, 136, 1, 0, 
	0, 0, 140, 15, 1, 0, 0, 0, 141, 142, 5, 10, 0, 0, 142, 143, 3, 36, 18, 
	0, 143, 144, 5, 11, 0, 0, 144, 145, 5, 16, 0, 0, 145, 146, 3, 18, 9, 0, 
	146, 147, 3, 20, 10, 0, 147, 148, 3, 30, 15, 0, 148, 149, 3, 22, 11, 0, 
	149, 17, 1, 0, 0, 0, 150, 151, 7, 1, 0, 0, 151, 19, 1, 0, 0, 0, 152, 153, 
	7, 2, 0, 0, 153, 21, 1, 0, 0, 0, 154, 155, 7, 3, 0, 0, 155, 23, 1, 0, 0, 
	0, 156, 157, 5, 46, 0, 0, 157, 158, 3, 30, 15, 0, 158, 159, 5, 47, 0, 0, 
	159, 160, 5, 10, 0, 0, 160, 163, 5, 57, 0, 0, 161, 162, 5, 3, 0, 0, 162, 
	164, 5, 57, 0, 0, 163, 161, 1, 0, 0, 0, 163, 164, 1, 0, 0, 0, 164, 165, 
	1, 0, 0, 0, 165, 166, 5, 11, 0, 0, 166, 167, 3, 30, 15, 0, 167, 25, 1, 
	0, 0, 0, 168, 169, 5, 21, 0, 0, 169, 170, 5, 57, 0, 0, 170, 172, 5, 10, 
	0, 0, 171, 173, 3, 32, 16, 0, 172, 171, 1, 0, 0, 0, 172, 173, 1, 0, 0, 
	0, 173, 174, 1, 0, 0, 0, 174, 175, 5, 11, 0, 0, 175, 176, 3, 30, 15, 0, 
	176, 27, 1, 0, 0, 0, 177, 178, 5, 45, 0, 0, 178, 179, 5, 57, 0, 0, 179, 
	180, 5, 5, 0, 0, 180, 185, 5, 12, 0, 0, 181, 184, 3, 4, 2, 0, 182, 184, 
	3, 26, 13, 0, 183, 181, 1, 0, 0, 0, 183, 182, 1, 0, 0, 0, 184, 187, 1, 
	0, 0, 0, 185, 183, 1, 0, 0, 0, 185, 186, 1, 0, 0, 0, 186, 188, 1, 0, 0, 
	0, 187, 185, 1, 0, 0, 0, 188, 189, 5, 13, 0, 0, 189, 29, 1, 0, 0, 0, 190, 
	194, 5, 12, 0, 0, 191, 193, 3, 2, 1, 0, 192, 191, 1, 0, 0, 0, 193, 196, 
	1, 0, 0, 0, 194, 192, 1, 0, 0, 0, 194, 195, 1, 0, 0, 0, 195, 197, 1, 0, 
	0, 0, 196, 194, 1, 0, 0, 0, 197, 198, 5, 13, 0, 0, 198, 31, 1, 0, 0, 0, 
	199, 200, 3, 6, 3, 0, 200, 207, 5, 57, 0, 0, 201, 202, 5, 22, 0, 0, 202, 
	203, 3, 6, 3, 0, 203, 204, 5, 57, 0, 0, 204, 206, 1, 0, 0, 0, 205, 201, 
	1, 0, 0, 0, 206, 209, 1, 0, 0, 0, 207, 205, 1, 0, 0, 0, 207, 208, 1, 0, 
	0, 0, 208, 33, 1, 0, 0, 0, 209, 207, 1, 0, 0, 0, 210, 215, 3, 36, 18, 0, 
	211, 212, 5, 22, 0, 0, 212, 214, 3, 36, 18, 0, 213, 211, 1, 0, 0, 0, 214, 
	217, 1, 0, 0, 0, 215, 213, 1, 0, 0, 0, 215, 216, 1, 0, 0, 0, 216, 35, 1, 
	0, 0, 0, 217, 215, 1, 0, 0, 0, 218, 219, 6, 18, -1, 0, 219, 220, 5, 57, 
	0, 0, 220, 222, 5, 10, 0, 0, 221, 223, 3, 34, 17, 0, 222, 221, 1, 0, 0, 
	0, 222, 223, 1, 0, 0, 0, 223, 224, 1, 0, 0, 0, 224, 243, 5, 11, 0, 0, 225, 
	226, 5, 57, 0, 0, 226, 227, 5, 6, 0, 0, 227, 228, 3, 36, 18, 0, 228, 229, 
	5, 7, 0, 0, 229, 243, 1, 0, 0, 0, 230, 231, 7, 4, 0, 0, 231, 243, 3, 36, 
	18, 11, 232, 243, 5, 52, 0, 0, 233, 243, 5, 53, 0, 0, 234, 243, 5, 56, 
	0, 0, 235, 243, 5, 59, 0, 0, 236, 243, 5, 58, 0, 0, 237, 243, 5, 54, 0, 
	0, 238, 243, 5, 55, 0, 0, 239, 243, 3, 38, 19, 0, 240, 243, 3, 40, 20, 
	0, 241, 243, 5, 57, 0, 0, 242, 218, 1, 0, 0, 0, 242, 225, 1, 0, 0, 0, 242, 
	230, 1, 0, 0, 0, 242, 232, 1, 0, 0, 0, 242, 233, 1, 0, 0, 0, 242, 234, 
	1, 0, 0, 0, 242, 235, 1, 0, 0, 0, 242, 236, 1, 0, 0, 0, 242, 237, 1, 0, 
	0, 0, 242, 238, 1, 0, 0, 0, 242, 239, 1, 0, 0, 0, 242, 240, 1, 0, 0, 0, 
	242, 241, 1, 0, 0, 0, 243, 261, 1, 0, 0, 0, 244, 245, 10, 16, 0, 0, 245, 
	246, 7, 5, 0, 0, 246, 260, 3, 36, 18, 17, 247, 248, 10, 15, 0, 0, 248, 
	249, 7, 6, 0, 0, 249, 260, 3, 36, 18, 16, 250, 251, 10, 14, 0, 0, 251, 
	252, 7, 7, 0, 0, 252, 260, 3, 36, 18, 15, 253, 254, 10, 13, 0, 0, 254, 
	255, 7, 8, 0, 0, 255, 260, 3, 36, 18, 14, 256, 257, 10, 12, 0, 0, 257, 
	258, 7, 9, 0, 0, 258, 260, 3, 36, 18, 13, 259, 244, 1, 0, 0, 0, 259, 247, 
	1, 0, 0, 0, 259, 250, 1, 0, 0, 0, 259, 253, 1, 0, 0, 0, 259, 256, 1, 0, 
	0, 0, 260, 263, 1, 0, 0, 0, 261, 259, 1, 0, 0, 0, 261, 262, 1, 0, 0, 0, 
	262, 37, 1, 0, 0, 0, 263, 261, 1, 0, 0, 0, 264, 265, 5, 39, 0, 0, 265, 
	270, 3, 36, 18, 0, 266, 267, 5, 22, 0, 0, 267, 269, 3, 36, 18, 0, 268, 
	266, 1, 0, 0, 0, 269, 272, 1, 0, 0, 0, 270, 268, 1, 0, 0, 0, 270, 271, 
	1, 0, 0, 0, 271, 273, 1, 0, 0, 0, 272, 270, 1, 0, 0, 0, 273, 274, 5, 40, 
	0, 0, 274, 39, 1, 0, 0, 0, 275, 276, 5, 57, 0, 0, 276, 277, 5, 6, 0, 0, 
	277, 278, 3, 36, 18, 0, 278, 279, 5, 7, 0, 0, 279, 41, 1, 0, 0, 0, 22, 
	45, 66, 69, 80, 89, 100, 114, 119, 128, 139, 163, 172, 183, 185, 194, 207, 
	215, 222, 242, 259, 261, 270,
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
	PaxoParserNUMBER_TYPE = 41
	PaxoParserCOMPLEX_TYPE = 42
	PaxoParserCHAR_TYPE = 43
	PaxoParserBOOL_TYPE = 44
	PaxoParserPKG = 45
	PaxoParserTRY = 46
	PaxoParserCATCH = 47
	PaxoParserARROW = 48
	PaxoParserINCLUDE = 49
	PaxoParserPAUSE_MODE = 50
	PaxoParserPLAY_MODE = 51
	PaxoParserINT_LITERAL = 52
	PaxoParserDECIMAL_LITERAL = 53
	PaxoParserBOOLEAN_BIT = 54
	PaxoParserBOOLEAN_TRIT = 55
	PaxoParserCOMPLEX_LITERAL = 56
	PaxoParserIDENTIFIER = 57
	PaxoParserSTRING_LITERAL = 58
	PaxoParserCHAR_LITERAL = 59
	PaxoParserLINE_COMMENT = 60
	PaxoParserBLOCK_COMMENT = 61
	PaxoParserWS = 62
)

// PaxoParser rules.
const (
	PaxoParserRULE_program = 0
	PaxoParserRULE_statement = 1
	PaxoParserRULE_varDeclaration = 2
	PaxoParserRULE_type = 3
	PaxoParserRULE_assignment = 4
	PaxoParserRULE_ifElseStatement = 5
	PaxoParserRULE_matchStatement = 6
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


	for ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 1149120355472770048) != 0) {
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
	MatchStatement() IMatchStatementContext
	IfElseStatement() IIfElseStatementContext
	LoopStatement() ILoopStatementContext
	TryCatchStatement() ITryCatchStatementContext
	FunctionDeclaration() IFunctionDeclarationContext
	PkgDeclaration() IPkgDeclarationContext
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

func (s *StatementContext) MatchStatement() IMatchStatementContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IMatchStatementContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IMatchStatementContext)
}

func (s *StatementContext) IfElseStatement() IIfElseStatementContext {
	var t antlr.RuleContext;
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IIfElseStatementContext); ok {
			t = ctx.(antlr.RuleContext);
			break
		}
	}

	if t == nil {
		return nil
	}

	return t.(IIfElseStatementContext)
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

func (s *StatementContext) FunctionDeclaration() IFunctionDeclarationContext {
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

func (s *StatementContext) PkgDeclaration() IPkgDeclarationContext {
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

	p.SetState(69)
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
			p.MatchStatement()
		}


	case 4:
		p.EnterOuterAlt(localctx, 4)
		{
			p.SetState(53)
			p.IfElseStatement()
		}


	case 5:
		p.EnterOuterAlt(localctx, 5)
		{
			p.SetState(54)
			p.LoopStatement()
		}


	case 6:
		p.EnterOuterAlt(localctx, 6)
		{
			p.SetState(55)
			p.TryCatchStatement()
		}


	case 7:
		p.EnterOuterAlt(localctx, 7)
		{
			p.SetState(56)
			p.FunctionDeclaration()
		}


	case 8:
		p.EnterOuterAlt(localctx, 8)
		{
			p.SetState(57)
			p.PkgDeclaration()
		}


	case 9:
		p.EnterOuterAlt(localctx, 9)
		{
			p.SetState(58)
			p.expression(0)
		}
		{
			p.SetState(59)
			p.Match(PaxoParserT__0)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 10:
		p.EnterOuterAlt(localctx, 10)
		{
			p.SetState(61)
			p.Match(PaxoParserINCLUDE)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(62)
			p.Match(PaxoParserT__1)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(63)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(66)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		if _la == PaxoParserT__2 {
			{
				p.SetState(64)
				p.Match(PaxoParserT__2)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(65)
				p.Match(PaxoParserIDENTIFIER)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

		}
		{
			p.SetState(68)
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
			p.SetState(71)
			p.Type_()
		}
		{
			p.SetState(72)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(73)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(74)
			p.expression(0)
		}


	case 2:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(76)
			p.Type_()
		}
		{
			p.SetState(77)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(78)
			p.Match(PaxoParserT__5)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		p.SetState(80)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}
		_la = p.GetTokenStream().LA(1)


		if _la == PaxoParserINT_LITERAL {
			{
				p.SetState(79)
				p.Match(PaxoParserINT_LITERAL)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}

		}
		{
			p.SetState(82)
			p.Match(PaxoParserT__6)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(83)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(84)
			p.ArrayLiteral()
		}


	case 3:
		p.EnterOuterAlt(localctx, 3)
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
	BOOL_TYPE() antlr.TerminalNode
	NUMBER_TYPE() antlr.TerminalNode
	COMPLEX_TYPE() antlr.TerminalNode
	CHAR_TYPE() antlr.TerminalNode

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

func (s *TypeContext) BOOL_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserBOOL_TYPE, 0)
}

func (s *TypeContext) NUMBER_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserNUMBER_TYPE, 0)
}

func (s *TypeContext) COMPLEX_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserCOMPLEX_TYPE, 0)
}

func (s *TypeContext) CHAR_TYPE() antlr.TerminalNode {
	return s.GetToken(PaxoParserCHAR_TYPE, 0)
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

		if !(((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 32985348833280) != 0)) {
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
	p.EnterRule(localctx, 8, PaxoParserRULE_assignment)
	p.SetState(100)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 5, p.GetParserRuleContext()) {
	case 1:
		p.EnterOuterAlt(localctx, 1)
		{
			p.SetState(93)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(94)
			p.Match(PaxoParserT__4)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(95)
			p.expression(0)
		}


	case 2:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(96)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(97)
			p.Match(PaxoParserT__7)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 3:
		p.EnterOuterAlt(localctx, 3)
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


// IIfElseStatementContext is an interface to support dynamic dispatch.
type IIfElseStatementContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	AllExpression() []IExpressionContext
	Expression(i int) IExpressionContext
	AllBlock() []IBlockContext
	Block(i int) IBlockContext
	AllARROW() []antlr.TerminalNode
	ARROW(i int) antlr.TerminalNode

	// IsIfElseStatementContext differentiates from other interfaces.
	IsIfElseStatementContext()
}

type IfElseStatementContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyIfElseStatementContext() *IfElseStatementContext {
	var p = new(IfElseStatementContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_ifElseStatement
	return p
}

func InitEmptyIfElseStatementContext(p *IfElseStatementContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_ifElseStatement
}

func (*IfElseStatementContext) IsIfElseStatementContext() {}

func NewIfElseStatementContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *IfElseStatementContext {
	var p = new(IfElseStatementContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_ifElseStatement

	return p
}

func (s *IfElseStatementContext) GetParser() antlr.Parser { return s.parser }

func (s *IfElseStatementContext) AllExpression() []IExpressionContext {
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

func (s *IfElseStatementContext) Expression(i int) IExpressionContext {
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

func (s *IfElseStatementContext) AllBlock() []IBlockContext {
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

func (s *IfElseStatementContext) Block(i int) IBlockContext {
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

func (s *IfElseStatementContext) AllARROW() []antlr.TerminalNode {
	return s.GetTokens(PaxoParserARROW)
}

func (s *IfElseStatementContext) ARROW(i int) antlr.TerminalNode {
	return s.GetToken(PaxoParserARROW, i)
}

func (s *IfElseStatementContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *IfElseStatementContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *IfElseStatementContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterIfElseStatement(s)
	}
}

func (s *IfElseStatementContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitIfElseStatement(s)
	}
}




func (p *PaxoParser) IfElseStatement() (localctx IIfElseStatementContext) {
	localctx = NewIfElseStatementContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 10, PaxoParserRULE_ifElseStatement)
	var _la int

	var _alt int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(102)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(103)
		p.expression(0)
	}
	{
		p.SetState(104)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(105)
		p.Block()
	}
	p.SetState(114)
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
				p.SetState(106)
				p.Match(PaxoParserARROW)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(107)
				p.Match(PaxoParserT__9)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(108)
				p.expression(0)
			}
			{
				p.SetState(109)
				p.Match(PaxoParserT__10)
				if p.HasError() {
						// Recognition error - abort rule
						goto errorExit
				}
			}
			{
				p.SetState(110)
				p.Block()
			}


		}
		p.SetState(116)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 6, p.GetParserRuleContext())
		if p.HasError() {
			goto errorExit
		}
	}
	p.SetState(119)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	if _la == PaxoParserARROW {
		{
			p.SetState(117)
			p.Match(PaxoParserARROW)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(118)
			p.Block()
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


// IMatchStatementContext is an interface to support dynamic dispatch.
type IMatchStatementContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Getter signatures
	IDENTIFIER() antlr.TerminalNode
	AllMatchCase() []IMatchCaseContext
	MatchCase(i int) IMatchCaseContext

	// IsMatchStatementContext differentiates from other interfaces.
	IsMatchStatementContext()
}

type MatchStatementContext struct {
	antlr.BaseParserRuleContext
	parser antlr.Parser
}

func NewEmptyMatchStatementContext() *MatchStatementContext {
	var p = new(MatchStatementContext)
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_matchStatement
	return p
}

func InitEmptyMatchStatementContext(p *MatchStatementContext)  {
	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, nil, -1)
	p.RuleIndex = PaxoParserRULE_matchStatement
}

func (*MatchStatementContext) IsMatchStatementContext() {}

func NewMatchStatementContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *MatchStatementContext {
	var p = new(MatchStatementContext)

	antlr.InitBaseParserRuleContext(&p.BaseParserRuleContext, parent, invokingState)

	p.parser = parser
	p.RuleIndex = PaxoParserRULE_matchStatement

	return p
}

func (s *MatchStatementContext) GetParser() antlr.Parser { return s.parser }

func (s *MatchStatementContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}

func (s *MatchStatementContext) AllMatchCase() []IMatchCaseContext {
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

func (s *MatchStatementContext) MatchCase(i int) IMatchCaseContext {
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

func (s *MatchStatementContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *MatchStatementContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}


func (s *MatchStatementContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.EnterMatchStatement(s)
	}
}

func (s *MatchStatementContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(PaxoListener); ok {
		listenerT.ExitMatchStatement(s)
	}
}




func (p *PaxoParser) MatchStatement() (localctx IMatchStatementContext) {
	localctx = NewMatchStatementContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 12, PaxoParserRULE_matchStatement)
	var _la int

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(121)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
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
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(124)
		p.Match(PaxoParserT__11)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(126)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for ok := true; ok; ok = ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 1148418867052183552) != 0) {
		{
			p.SetState(125)
			p.MatchCase()
		}


		p.SetState(128)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_la = p.GetTokenStream().LA(1)
	}
	{
		p.SetState(130)
		p.Match(PaxoParserT__12)
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
	p.SetState(139)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetTokenStream().LA(1) {
	case PaxoParserT__36, PaxoParserT__37, PaxoParserT__38, PaxoParserINT_LITERAL, PaxoParserDECIMAL_LITERAL, PaxoParserBOOLEAN_BIT, PaxoParserBOOLEAN_TRIT, PaxoParserCOMPLEX_LITERAL, PaxoParserIDENTIFIER, PaxoParserSTRING_LITERAL, PaxoParserCHAR_LITERAL:
		p.EnterOuterAlt(localctx, 1)
		{
			p.SetState(132)
			p.expression(0)
		}
		{
			p.SetState(133)
			p.Match(PaxoParserT__13)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(134)
			p.Block()
		}


	case PaxoParserT__14:
		p.EnterOuterAlt(localctx, 2)
		{
			p.SetState(136)
			p.Match(PaxoParserT__14)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(137)
			p.Match(PaxoParserT__13)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(138)
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
		p.SetState(141)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(142)
		p.expression(0)
	}
	{
		p.SetState(143)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(144)
		p.Match(PaxoParserT__15)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(145)
		p.LoopMode()
	}
	{
		p.SetState(146)
		p.LoopDelimiter()
	}
	{
		p.SetState(147)
		p.Block()
	}
	{
		p.SetState(148)
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
		p.SetState(150)
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
		p.SetState(152)
		_la = p.GetTokenStream().LA(1)

		if !(_la == PaxoParserT__16 || _la == PaxoParserT__17) {
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
		p.SetState(154)
		_la = p.GetTokenStream().LA(1)

		if !(_la == PaxoParserT__18 || _la == PaxoParserT__19) {
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
		p.SetState(156)
		p.Match(PaxoParserTRY)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(157)
		p.Block()
	}
	{
		p.SetState(158)
		p.Match(PaxoParserCATCH)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(159)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(160)
		p.Match(PaxoParserIDENTIFIER)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(163)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	if _la == PaxoParserT__2 {
		{
			p.SetState(161)
			p.Match(PaxoParserT__2)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(162)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}

	}
	{
		p.SetState(165)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(166)
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
	IDENTIFIER() antlr.TerminalNode
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

func (s *FunctionDeclarationContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
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
		p.SetState(168)
		p.Match(PaxoParserT__20)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(169)
		p.Match(PaxoParserIDENTIFIER)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(170)
		p.Match(PaxoParserT__9)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(172)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	if ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 32985348833280) != 0) {
		{
			p.SetState(171)
			p.ParameterList()
		}

	}
	{
		p.SetState(174)
		p.Match(PaxoParserT__10)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(175)
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
	PKG() antlr.TerminalNode
	IDENTIFIER() antlr.TerminalNode
	AllVarDeclaration() []IVarDeclarationContext
	VarDeclaration(i int) IVarDeclarationContext
	AllFunctionDeclaration() []IFunctionDeclarationContext
	FunctionDeclaration(i int) IFunctionDeclarationContext

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

func (s *PkgDeclarationContext) PKG() antlr.TerminalNode {
	return s.GetToken(PaxoParserPKG, 0)
}

func (s *PkgDeclarationContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}

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

func (s *PkgDeclarationContext) AllFunctionDeclaration() []IFunctionDeclarationContext {
	children := s.GetChildren()
	len := 0
	for _, ctx := range children {
		if _, ok := ctx.(IFunctionDeclarationContext); ok {
			len++
		}
	}

	tst := make([]IFunctionDeclarationContext, len)
	i := 0
	for _, ctx := range children {
		if t, ok := ctx.(IFunctionDeclarationContext); ok {
			tst[i] = t.(IFunctionDeclarationContext)
			i++
		}
	}

	return tst
}

func (s *PkgDeclarationContext) FunctionDeclaration(i int) IFunctionDeclarationContext {
	var t antlr.RuleContext;
	j := 0
	for _, ctx := range s.GetChildren() {
		if _, ok := ctx.(IFunctionDeclarationContext); ok {
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

	return t.(IFunctionDeclarationContext)
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
		p.SetState(177)
		p.Match(PaxoParserPKG)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(178)
		p.Match(PaxoParserIDENTIFIER)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(179)
		p.Match(PaxoParserT__4)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(180)
		p.Match(PaxoParserT__11)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(185)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 32985350930432) != 0) {
		p.SetState(183)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
			goto errorExit
		}

		switch p.GetTokenStream().LA(1) {
		case PaxoParserNUMBER_TYPE, PaxoParserCOMPLEX_TYPE, PaxoParserCHAR_TYPE, PaxoParserBOOL_TYPE:
			{
				p.SetState(181)
				p.VarDeclaration()
			}


		case PaxoParserT__20:
			{
				p.SetState(182)
				p.FunctionDeclaration()
			}



		default:
			p.SetError(antlr.NewNoViableAltException(p, nil, nil, nil, nil, nil))
			goto errorExit
		}

		p.SetState(187)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_la = p.GetTokenStream().LA(1)
	}
	{
		p.SetState(188)
		p.Match(PaxoParserT__12)
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
		p.SetState(190)
		p.Match(PaxoParserT__11)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(194)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 1149120355472770048) != 0) {
		{
			p.SetState(191)
			p.Statement()
		}


		p.SetState(196)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_la = p.GetTokenStream().LA(1)
	}
	{
		p.SetState(197)
		p.Match(PaxoParserT__12)
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
		p.SetState(199)
		p.Type_()
	}
	{
		p.SetState(200)
		p.Match(PaxoParserIDENTIFIER)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	p.SetState(207)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for _la == PaxoParserT__21 {
		{
			p.SetState(201)
			p.Match(PaxoParserT__21)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(202)
			p.Type_()
		}
		{
			p.SetState(203)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


		p.SetState(209)
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
		p.SetState(210)
		p.expression(0)
	}
	p.SetState(215)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for _la == PaxoParserT__21 {
		{
			p.SetState(211)
			p.Match(PaxoParserT__21)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(212)
			p.expression(0)
		}


		p.SetState(217)
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

	// Getter signatures
	INT_LITERAL() antlr.TerminalNode
	DECIMAL_LITERAL() antlr.TerminalNode
	COMPLEX_LITERAL() antlr.TerminalNode
	CHAR_LITERAL() antlr.TerminalNode
	STRING_LITERAL() antlr.TerminalNode
	BOOLEAN_BIT() antlr.TerminalNode
	BOOLEAN_TRIT() antlr.TerminalNode
	ArrayLiteral() IArrayLiteralContext
	ArrayAccess() IArrayAccessContext
	IDENTIFIER() antlr.TerminalNode

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

func (s *ExpressionContext) INT_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserINT_LITERAL, 0)
}

func (s *ExpressionContext) DECIMAL_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserDECIMAL_LITERAL, 0)
}

func (s *ExpressionContext) COMPLEX_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserCOMPLEX_LITERAL, 0)
}

func (s *ExpressionContext) CHAR_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserCHAR_LITERAL, 0)
}

func (s *ExpressionContext) STRING_LITERAL() antlr.TerminalNode {
	return s.GetToken(PaxoParserSTRING_LITERAL, 0)
}

func (s *ExpressionContext) BOOLEAN_BIT() antlr.TerminalNode {
	return s.GetToken(PaxoParserBOOLEAN_BIT, 0)
}

func (s *ExpressionContext) BOOLEAN_TRIT() antlr.TerminalNode {
	return s.GetToken(PaxoParserBOOLEAN_TRIT, 0)
}

func (s *ExpressionContext) ArrayLiteral() IArrayLiteralContext {
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

func (s *ExpressionContext) ArrayAccess() IArrayAccessContext {
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

func (s *ExpressionContext) IDENTIFIER() antlr.TerminalNode {
	return s.GetToken(PaxoParserIDENTIFIER, 0)
}


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
	p.SetState(242)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}

	switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 18, p.GetParserRuleContext()) {
	case 1:
		localctx = NewCallExprContext(p, localctx)
		p.SetParserRuleContext(localctx)
		_prevctx = localctx

		{
			p.SetState(219)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(220)
			p.Match(PaxoParserT__9)
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
		_la = p.GetTokenStream().LA(1)


		if ((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 1148418867052150784) != 0) {
			{
				p.SetState(221)
				p.ArgumentList()
			}

		}
		{
			p.SetState(224)
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
			p.SetState(225)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(226)
			p.Match(PaxoParserT__5)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(227)
			p.expression(0)
		}
		{
			p.SetState(228)
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
			p.SetState(230)
			_la = p.GetTokenStream().LA(1)

			if !(_la == PaxoParserT__36 || _la == PaxoParserT__37) {
				p.GetErrorHandler().RecoverInline(p)
			} else {
				p.GetErrorHandler().ReportMatch(p)
				p.Consume()
			}
		}
		{
			p.SetState(231)
			p.expression(11)
		}


	case 4:
		{
			p.SetState(232)
			p.Match(PaxoParserINT_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 5:
		{
			p.SetState(233)
			p.Match(PaxoParserDECIMAL_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 6:
		{
			p.SetState(234)
			p.Match(PaxoParserCOMPLEX_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 7:
		{
			p.SetState(235)
			p.Match(PaxoParserCHAR_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 8:
		{
			p.SetState(236)
			p.Match(PaxoParserSTRING_LITERAL)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 9:
		{
			p.SetState(237)
			p.Match(PaxoParserBOOLEAN_BIT)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 10:
		{
			p.SetState(238)
			p.Match(PaxoParserBOOLEAN_TRIT)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}


	case 11:
		{
			p.SetState(239)
			p.ArrayLiteral()
		}


	case 12:
		{
			p.SetState(240)
			p.ArrayAccess()
		}


	case 13:
		{
			p.SetState(241)
			p.Match(PaxoParserIDENTIFIER)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}

	case antlr.ATNInvalidAltNumber:
		goto errorExit
	}
	p.GetParserRuleContext().SetStop(p.GetTokenStream().LT(-1))
	p.SetState(261)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 20, p.GetParserRuleContext())
	if p.HasError() {
		goto errorExit
	}
	for _alt != 2 && _alt != antlr.ATNInvalidAltNumber {
		if _alt == 1 {
			if p.GetParseListeners() != nil {
				p.TriggerExitRuleEvent()
			}
			_prevctx = localctx
			p.SetState(259)
			p.GetErrorHandler().Sync(p)
			if p.HasError() {
				goto errorExit
			}

			switch p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 19, p.GetParserRuleContext()) {
			case 1:
				localctx = NewMultDivExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(244)

				if !(p.Precpred(p.GetParserRuleContext(), 16)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 16)", ""))
					goto errorExit
				}
				{
					p.SetState(245)
					_la = p.GetTokenStream().LA(1)

					if !(_la == PaxoParserT__22 || _la == PaxoParserT__23) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(246)
					p.expression(17)
				}


			case 2:
				localctx = NewAddSubExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(247)

				if !(p.Precpred(p.GetParserRuleContext(), 15)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 15)", ""))
					goto errorExit
				}
				{
					p.SetState(248)
					_la = p.GetTokenStream().LA(1)

					if !(_la == PaxoParserT__24 || _la == PaxoParserT__25) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(249)
					p.expression(16)
				}


			case 3:
				localctx = NewShiftExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(250)

				if !(p.Precpred(p.GetParserRuleContext(), 14)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 14)", ""))
					goto errorExit
				}
				{
					p.SetState(251)
					_la = p.GetTokenStream().LA(1)

					if !(_la == PaxoParserT__26 || _la == PaxoParserT__27) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(252)
					p.expression(15)
				}


			case 4:
				localctx = NewRelationalExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(253)

				if !(p.Precpred(p.GetParserRuleContext(), 13)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 13)", ""))
					goto errorExit
				}
				{
					p.SetState(254)
					_la = p.GetTokenStream().LA(1)

					if !(((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 8053063700) != 0)) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(255)
					p.expression(14)
				}


			case 5:
				localctx = NewBitwiseExprContext(p, NewExpressionContext(p, _parentctx, _parentState))
				p.PushNewRecursionContext(localctx, _startState, PaxoParserRULE_expression)
				p.SetState(256)

				if !(p.Precpred(p.GetParserRuleContext(), 12)) {
					p.SetError(antlr.NewFailedPredicateException(p, "p.Precpred(p.GetParserRuleContext(), 12)", ""))
					goto errorExit
				}
				{
					p.SetState(257)
					_la = p.GetTokenStream().LA(1)

					if !(((int64(_la) & ^0x3f) == 0 && ((int64(1) << _la) & 128849018880) != 0)) {
						p.GetErrorHandler().RecoverInline(p)
					} else {
						p.GetErrorHandler().ReportMatch(p)
						p.Consume()
					}
				}
				{
					p.SetState(258)
					p.expression(13)
				}

			case antlr.ATNInvalidAltNumber:
				goto errorExit
			}

		}
		p.SetState(263)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_alt = p.GetInterpreter().AdaptivePredict(p.BaseParser, p.GetTokenStream(), 20, p.GetParserRuleContext())
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
		p.SetState(264)
		p.Match(PaxoParserT__38)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(265)
		p.expression(0)
	}
	p.SetState(270)
	p.GetErrorHandler().Sync(p)
	if p.HasError() {
		goto errorExit
	}
	_la = p.GetTokenStream().LA(1)


	for _la == PaxoParserT__21 {
		{
			p.SetState(266)
			p.Match(PaxoParserT__21)
			if p.HasError() {
					// Recognition error - abort rule
					goto errorExit
			}
		}
		{
			p.SetState(267)
			p.expression(0)
		}


		p.SetState(272)
		p.GetErrorHandler().Sync(p)
		if p.HasError() {
	    	goto errorExit
	    }
		_la = p.GetTokenStream().LA(1)
	}
	{
		p.SetState(273)
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
		p.SetState(275)
		p.Match(PaxoParserIDENTIFIER)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(276)
		p.Match(PaxoParserT__5)
		if p.HasError() {
				// Recognition error - abort rule
				goto errorExit
		}
	}
	{
		p.SetState(277)
		p.expression(0)
	}
	{
		p.SetState(278)
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
			return p.Precpred(p.GetParserRuleContext(), 16)

	case 1:
			return p.Precpred(p.GetParserRuleContext(), 15)

	case 2:
			return p.Precpred(p.GetParserRuleContext(), 14)

	case 3:
			return p.Precpred(p.GetParserRuleContext(), 13)

	case 4:
			return p.Precpred(p.GetParserRuleContext(), 12)

	default:
		panic("No predicate with index: " + fmt.Sprint(predIndex))
	}
}

