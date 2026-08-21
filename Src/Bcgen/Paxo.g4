grammar Paxo;

// ==========================================
// 1. REGLAS DEL PARSER (Sintaxis)
// ==========================================

program
    : statement* EOF
    ;

statement
    : varDeclaration
    | assignment
    | condStatement
    | loopStatement
    | tryCatchStatement
    | throwStatement
    | returnStatement
    | expression ';'
    | INCLUDE '<' IDENTIFIER ('.' IDENTIFIER)? '>'
    ;

varDeclaration
    : scope type IDENTIFIER '=' expression
    | scope type IDENTIFIER '[' INT_LITERAL? ']' '=' arrayLiteral
    | scope type IDENTIFIER
    ;

type
		: VAR_TYPE | NUM_TYPE | CHARA_TYPE | POINTER_TYPE | TRIT_TYPE | BOOLEAN_TYPE ;

scope
	: GLOBAL | LOCAL ;

assignment
    : IDENTIFIER '=' expression ';'
    | IDENTIFIER '[' expression ']' '=' expression ';'
    | IDENTIFIER '++' ';'
    | IDENTIFIER '--' ';'
    ;

condStatement
    : '(' expression ')' '?' matchCase ( ':' matchCase )*? ';'
    ;

matchCase
    : expression '->' block
    | '_' '->' block
    ;

loopStatement
    : '(' expression ')' ':' loopMode loopDelimiter block loopEndDelimiter
    ;

loopMode
    : PAUSE_MODE // ⏸️
    | PLAY_MODE  // ▶️
    ;

loopDelimiter    : '|:' | '𝄆' ;
loopEndDelimiter : ':|' | '𝄇' ;

tryCatchStatement
    : TRY block CATCH '(' IDENTIFIER ('.' IDENTIFIER)? ')' block
    ;

functionDeclaration
    : '(' parameterList? ')' (':' type)? block
    ;

pkgDeclaration
    : '{' varDeclaration* '}'
    ;

block
    : '{' statement* '}'
    ;

parameterList
    : type IDENTIFIER (',' type IDENTIFIER)*
    ;

returnStatement
    : RETURN expression? ';'
    ;

throwStatement
    : THROW expression ';'
    ;

argumentList
    : expression (',' expression)*
    ;

expression
    : IDENTIFIER '(' argumentList? ')' # callExpr
    | expression '[' expression ']'                        # indexedAccessExpr
    | expression '.' IDENTIFIER                             # dotAccessExpr
    | expression ( '÷' | '×' ) expression       # multDivExpr
    | expression ( '+' | '-' ) expression                   # addSubExpr
    | expression ( '•«' | '»•' ) expression                 # shiftExpr
    | expression ( '<'|'>'|'≤'|'<='|'≥'|'>='|'=='|'!='|'≠' ) expression   # relationalExpr
    | expression ( '&' | '|' | '.&' | '.|' ) expression     # bitwiseExpr
    | ( '!' | '.!' ) expression # notgateExpr
    | INT_LITERAL # intLitExpr
    | DECIMAL_LITERAL # decLitExpr
    | CHAR_LITERAL # charLitExpr
    | STRING_LITERAL # stringLitExpr
    | BOOLEAN_BIT # boolBitExpr
    | BOOLEAN_TRIT # boolTritExpr
		| POINTER_LITERAL # ptrLitExpr
    | arrayLiteral # arrayLitExpr
    | IDENTIFIER # identExpr
		| pkgDeclaration # pkgExpr
		| functionDeclaration # funcExpr
    ;

arrayLiteral
    : '«' expression (',' expression)* '»'
    ;

// ==========================================
// 2. REGLAS DEL LEXER (Tokens con Aliases Móvil/ASCII)
// ==========================================

VAR_TYPE: 'var' | '📥' ;
NUM_TYPE: 'n' | 'sn' ;
CHARA_TYPE: 'abc' ;
TRIT_TYPE: 'trit' ;
BOOLEAN_TYPE: 'bool' ;
POINTER_TYPE: 'pin' ;

GLOBAL: 'pub' | '🌎' ;
LOCAL: 'local';

TRY        : '↻' | 'try' ;
CATCH      : '🪤' | 'catch' | '/]' ;
ARROW      : '→' | '->';
INCLUDE    : '+📚' | 'add' ;
RETURN     : 'return' ;
THROW      : 'throw' | '⚡' ;

PAUSE_MODE : '⏸️' | 'stop' | '||' ;
PLAY_MODE  : '▶️' | 'go' | '|>' ;

// Literales
INT_LITERAL     : [+-]? [0-9]+ ;
DECIMAL_LITERAL : [+-]? [0-9]+ '.' [0-9]+ ;
BOOLEAN_BIT			: '.×' | '.✓' ;
BOOLEAN_TRIT    : '×' | '•' | '✓' ;
POINTER_LITERAL : '@' IDENTIFIER ;

IDENTIFIER      : [a-zA-Z_\p{L}\p{Emoji}][a-zA-Z0-9_\p{L}\p{Emoji}]* ;
STRING_LITERAL  : '"' (~["\r\n])* '"' ;
CHAR_LITERAL    : '\'' . '\'' ;
LINE_COMMENT    : '//' ~[\r\n]* -> skip ;
BLOCK_COMMENT   : '/*' .*? '*/' -> skip ;
WS              : [ \t\r\n]+ -> skip ;