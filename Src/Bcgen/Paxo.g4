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
    | expression ';'
    | INCLUDE '<' IDENTIFIER ('.' IDENTIFIER)? '>'
    ;

varDeclaration
    : VAR_TYPE SIZE_POSFIX? IDENTIFIER '=' expression
    | VAR_TYPE SIZE_POSFIX? IDENTIFIER '[' INT_LITERAL? ']' '=' arrayLiteral
    | VAR_TYPE SIZE_POSFIX? IDENTIFIER
    ;

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
    : '(' parameterList? ')' block
    ;

pkgDeclaration
    : '{' varDeclaration* '}'
    ;

block
    : '{' statement* '}'
    ;

parameterList
    : VAR_TYPE SIZE_POSFIX? IDENTIFIER (',' VAR_TYPE SIZE_POSFIX? IDENTIFIER)*
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
		| MONEY_LITERAL
    | COMPLEX_LITERAL
    | CHAR_LITERAL
    | STRING_LITERAL
    | BOOLEAN_BIT
    | BOOLEAN_TRIT
		| POINTER_LITERAL
    | arrayLiteral
    | arrayAccess
    | IDENTIFIER
		| pkgDeclaration
		| functionDeclaration
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

VAR_TYPE: 'var' | '📥' ;

TRY        : '↻' | 'try' ;
CATCH      : '🪤' | 'catch' | '/]' ;
ARROW      : '→' | '->';
INCLUDE    : '+📚' | 'add' ;

PAUSE_MODE : '⏸️' | 'stop' | '||' ;
PLAY_MODE  : '▶️' | 'go' | '>' ;

// Literales
INT_LITERAL     : [+-]? [0-9]+ ;
DECIMAL_LITERAL : [+-]? [0-9]+ '.' [0-9]+ ;
MONEY_LITERAL   : '§' [+-]? [0-9]+ '.' [0-9]+ ;
BOOLEAN_BIT			: '.×' | '.✓' ;
BOOLEAN_TRIT    : '×' | '•' | '✓' ;
COMPLEX_LITERAL : [+-]? [0-9]+ ('.' [0-9]+)? [+-] [0-9]+ ('.' [0-9]+)? 'i'
| [+-]? [0-9]+ ('.' [0-9]+) 'i' ;
POINTER_LITERAL : '@' IDENTIFIER ;

IDENTIFIER      : [a-zA-Z_\p{L}\p{Emoji}][a-zA-Z0-9_\p{L}\p{Emoji}]* ;
STRING_LITERAL  : '"' (~["\r\n])* '"' ;
CHAR_LITERAL    : '\'' . '\'' ;
SIZE_POSFIX			: '.8' | '.16' | '.32' | '.64' ;
LINE_COMMENT    : '//' ~[\r\n]* -> skip ;
BLOCK_COMMENT   : '/*' .*? '*/' -> skip ;
WS              : [ \t\r\n]+ -> skip ;