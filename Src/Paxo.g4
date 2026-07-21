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
    : sizePrefix? VAR_DECL IDENTIFIER '=' expression
    | sizePrefix? VAR_DECL IDENTIFIER '[' INT_LITERAL? ']' '=' arrayLiteral
    | sizePrefix? VAR_DECL IDENTIFIER
    ;

sizePrefix
    : 'xxs' | 'xs' | 's' | 'l' | 'xl'
    ;

assignment
    : IDENTIFIER '=' expression
    | IDENTIFIER '++'
    | IDENTIFIER '--'
    ;

ifElseStatement
    : '(' expression ')' block (ARROW block)?
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
    : PAUSE_MODE // ⏸️ (Do-Until)
    | PLAY_MODE  // ▶️ (While)
    ;

loopDelimiter    : '|:' | '𝄆' ;
loopEndDelimiter : ':|' | '𝄇' ;

tryCatchStatement
    : TRY block CATCH '(' IDENTIFIER ('.' IDENTIFIER)? ')' block
    ;

functionDeclaration
    : VAR_DECL IDENTIFIER '=' '(' parameterList? ')' block
    ;

pkgDeclaration
    : PKG IDENTIFIER '=' '{' (varDeclaration | functionDeclaration)* '}'
    ;

block
    : '{' statement* '}'
    ;

parameterList
    : sizePrefix? VAR_DECL IDENTIFIER (',' sizePrefix? VAR_DECL IDENTIFIER)*
    ;

argumentList
    : expression (',' expression)*
    ;

expression
    : expression ('<'|'>'|'≤'|'≥'|'=='|'≠') expression
    | IDENTIFIER '(' argumentList? ')'
    | INT_LITERAL
    | UINT_LITERAL
    | DECIMAL_LITERAL
    | COMPLEX_LITERAL
    | CHAR_LITERAL
    | STRING_LITERAL
    | EMSTRING_LITERAL
    | BOOLEAN
    | VECTOR
    | NANOTIME_LITERAL
    | SLICE_LITERAL
    | POINTER_LITERAL
    | IPV4_LITERAL
    | IPV6_LITERAL
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

VAR_DECL   : '📥' | 'var' ;
PKG        : '📦' | 'pkg' ;
TRY        : '↻' | 'try' ;
CATCH      : '🪤' | 'catch' ;
ARROW      : '→' | 'else' ;
INCLUDE    : '+📚' | 'add' ;

PAUSE_MODE : '⏸️' | 'stop' ;
PLAY_MODE  : '▶️' | 'go' ;

// Literales
INT_LITERAL     : [+-]? [0-9]+ ;
UINT_LITERAL    : [0-9]+ 'u' ;
DECIMAL_LITERAL : [+-]? [0-9]+ '.' [0-9]+ ;
BOOLEAN         : '×' | '✓' ;
COMPLEX_LITERAL : [+-]? [0-9]+ ('.' [0-9]+)? [+-] [0-9]+ ('.' [0-9]+)? 'i'
| [+-]? [0-9]+ ('.' [0-9]+) 'i' ;
IDENTIFIER      : [a-zA-Z_\p{L}\p{Emoji}][a-zA-Z0-9_\p{L}\p{Emoji}]* ;
STRING_LITERAL  : '"' (~["\r\n])* '"' ;
CHAR_LITERAL    : '\'' . '\'' ;
EMSTRING_LITERAL: '"' (~["\r\n])* '"' 'il' ;
VECTOR          : '[' [+-]? [0-9]+ ('.' [0-9]+) (',' [+-]? [0-9]+ ('.' [0-9]+)?)* ']' ;
NANOTIME_LITERAL: [0-9]+ ':' [0-9]+ ;
SLICE_LITERAL   : '&' [a-zA-Z_\p{L}\p{Emoji}][a-zA-Z0-9_\p{L}\p{Emoji}]* '~' [0-9]+ ;
POINTER_LITERAL : '&' [a-zA-Z_\p{L}\p{Emoji}][a-zA-Z0-9_\p{L}\p{Emoji}]* ;
IPV4_LITERAL    : [0-9]+ ('.' [0-9]+)* ;
IPV6_LITERAL    : [0-9a_fA-F]+ (':' [0-9a-fA-F]+)* ;
LINE_COMMENT    : '//' ~[\r\n]* -> skip ;
BLOCK_COMMENT   : '/*' .*? '*/' -> skip ;
WS              : [ \t\r\n]+ -> skip ;