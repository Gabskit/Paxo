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
    | matchStatement
    | ifElseStatement
    | loopStatement
    | tryCatchStatement
    | functionDeclaration
    | pkgDeclaration
    | expression ';'
    | INCLUDE '<' IDENTIFIER ('.' IDENTIFIER)? '>'
    ;

varDeclaration
    : type IDENTIFIER '=' expression
    | type IDENTIFIER '[' INT_LITERAL? ']' '=' arrayLiteral
    | type IDENTIFIER
    ;

type: BOOL_TYPE | NUMBER_TYPE | COMPLEX_TYPE | CHAR_TYPE ;

assignment
    : IDENTIFIER '=' expression
    | IDENTIFIER '++'
    | IDENTIFIER '--'
    ;

ifElseStatement
    : '(' expression ')' block (ARROW '(' expression ')' block)*? (ARROW block)?
    ;

matchStatement
    : '(' IDENTIFIER ')' '{' matchCase+ '}'
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
    : 'fx' IDENTIFIER '(' parameterList? ')' block
    ;

pkgDeclaration
    : PKG IDENTIFIER '=' '{' (varDeclaration | functionDeclaration)* '}'
    ;

block
    : '{' statement* '}'
    ;

parameterList
    : type IDENTIFIER (',' type IDENTIFIER)*
    ;

argumentList
    : expression (',' expression)*
    ;

expression
    : IDENTIFIER '(' argumentList? ')' # callExpr
    | IDENTIFIER '[' expression ']'                         # arrayAccessExpr
    | expression ( '÷' | '×' ) expression       # multDivExpr
    | expression ( '+' | '-' ) expression                   # addSubExpr
    | expression ( '•«' | '»•' ) expression                 # shiftExpr
    | expression ( '<'|'>'|'≤'|'≥'|'=='|'≠' ) expression   # relationalExpr
    | expression ( '&' | '|' | '.&' | '.|' ) expression     # bitwiseExpr
    | ( '!' | '.!' ) expression # notgateExpr
    | INT_LITERAL
    | DECIMAL_LITERAL
    | COMPLEX_LITERAL
    | CHAR_LITERAL
    | STRING_LITERAL
    | BOOLEAN_BIT
    | BOOLEAN_TRIT
    | arrayLiteral
    | arrayAccess
    | IDENTIFIER
    ;

arrayLiteral
    : '«' expression (',' expression)* '»'
    ;

arrayAccess
    : IDENTIFIER '[' expression ']'
    ;

// ==========================================
// 2. REGLAS DEL LEXER (Tokens con Aliases Móvil/ASCII)
// ==========================================

NUMBER_TYPE: 'n8' | 'n16' | 'n32' | 'n64' ;
COMPLEX_TYPE: 'ni8' | 'ni16' | 'ni32' | 'ni64' ;
CHAR_TYPE  : 'abc8' | 'abc16' | 'abc32' ;
BOOL_TYPE  : 'bit';

PKG        : '📦' | 'pkg' ;
TRY        : '↻' | 'try' ;
CATCH      : '🪤' | 'catch' ;
ARROW      : '→' ;
INCLUDE    : '+📚' | 'add' ;

PAUSE_MODE : '⏸️' | 'stop' ;
PLAY_MODE  : '▶️' | 'go' ;

// Literales
INT_LITERAL     : [+-]? [0-9]+ ;
DECIMAL_LITERAL : [+-]? [0-9]+ '.' [0-9]+ ;
BOOLEAN_BIT     : '×' | '✓' ;
BOOLEAN_TRIT    : '×' | '•' | '✓' ;
COMPLEX_LITERAL : [+-]? [0-9]+ ('.' [0-9]+)? [+-] [0-9]+ ('.' [0-9]+)? 'i'
| [+-]? [0-9]+ ('.' [0-9]+) 'i' ;
IDENTIFIER      : [a-zA-Z_\p{L}\p{Emoji}][a-zA-Z0-9_\p{L}\p{Emoji}]* ;
STRING_LITERAL  : '"' (~["\r\n])* '"' ;
CHAR_LITERAL    : '\'' . '\'' ;
LINE_COMMENT    : '//' ~[\r\n]* -> skip ;
BLOCK_COMMENT   : '/*' .*? '*/' -> skip ;
WS              : [ \t\r\n]+ -> skip ;