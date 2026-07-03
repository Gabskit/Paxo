grammar Axolang;

// Regla raíz del programa
program
: statement* EOF
;

// Un statement puede ser una declaración de variable
statement
: varDeclaration
| matchStatement
;

// Declaración de variables (Soporta inferencia 'auto' o tipo explícito)
varDeclaration
: ( 'auto' | type ) IDENTIFIER '=' expression
;

// Tipos de datos según la especificación V4
type
: 'xxsvar' | 'xsvar' | 'svar' | 'var' | 'lvar' | 'xlvar' | 'xxlvar' | 'fun'
;

matchStatement
: 'match' '(' IDENTIFIER ')' '{' matchCase+ '}'
;

matchCase
: expression '->' declaration ';'
| expression '->' '{' OTHER '}'
| '_' '->' declaration ';' // Caso por defecto (Gleam style)
;

declaration
: IDENTIFIER '=' expression
| IDENTIFIER '(' OTHER ')'
| statement
;

pkgDeclaration
: '{' OTHER '}'
;
// Expresión matemática o literal simple por ahora
expression
: INT_LITERAL
| UINT_LITERAL
| FLOAT_LITERAL
| IDENTIFIER
| COMPLEX_LITERAL
| CHAR_LITERAL
| DECIMAL_LITERAL
| BOOLEAN
| pkgDeclaration
;

// --- TOKENS LÉXICOS ---
IDENTIFIER    : [\u{1F4A9}\u{1F926}\p{Alpha}\p{General_Category=Other_Letter}] [\u{1F4A9}\u{1F926}\p{Alnum}\p{General_Category=Other_Letter}]* ;
CHAR_LITERAL  : '\'' [\u{1F4A9}\u{1F926}\p{Alnum}\p{General_Category=Other_Letter}] '\'';
INT_LITERAL   : [+-]? [ \t]* [0-9]+ ;
UINT_LITERAL  : [0-9]+ [ \t]* 'u';
FLOAT_LITERAL : [+-]? [ \t]* [0-9]+ ('.' [0-9]+)?;
DECIMAL_LITERAL: [+-]? [ \t]* [0-9]+ ('.' [0-9]+)? 'D';//3.3D y 3D
COMPLEX_LITERAL
: [+-]? [ \t]* [0-9]+ ('.' [0-9]+)? [ \t]* [+-] [ \t]* [0-9]+ ('.' [0-9]+)? [ \t]* 'i'  // Ej: 4+5i, 3.14 - 2.5i, 4 + 2i
| [+-]? [ \t]* [0-9]+ ('.' [0-9]+)? [ \t]* 'i';                                    // Ej: 2i, 0.5i (Imaginarios puros)
BOOLEAN :[★†];
//FUN_DECLARATION : '(' [a-zA-Z_][a-zA-Z0-9_]* ')' ':' [a-zA-Z_] '{' '}'
WS            : [ \t\r\n]+ -> skip ;
OTHER : .?*;