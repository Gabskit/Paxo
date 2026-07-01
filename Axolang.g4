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
// Jerarquía de Uniones Dinámicas (Carga cognitiva asumida por el compilador)
: 'xsany' | 'sany' | 'any' | 'lany' | 'xlany' | 'xxlany'

// Tipos enteros escalados
| 'xxsint' | 'xsint' | 'sint' | 'int' | 'lint' | 'xlint'

| 'xsflt' | 'sflt' | 'flt' | 'lflt' | 'xlflt'

// Tipos decimales corregidos
| 'sdec' | 'dec' | 'ldec'

// Números complejos de rango extendido
| 'xscom' | 'scom' | 'com' | 'lcom' | 'xlcom'

| 'boo' | 'pkg' | 'chara' | 'fun'
;

matchStatement
: 'match' '(' IDENTIFIER ')' '{' matchCase+ '}'
;

matchCase
: expression '->' declaration ';'
| expression '->' '{' declaration '}'
| '_' '->' declaration ';' // Caso por defecto (Gleam style)
;

declaration
: IDENTIFIER '=' expression ;

// Expresión matemática o literal simple por ahora
expression
: INT_LITERAL
| FLOAT_LITERAL
| IDENTIFIER
| COMPLEX_LITERAL
| CHAR_LITERAL
| DECIMAL_LITERAL

;

// --- TOKENS LÉXICOS ---
IDENTIFIER    : [a-zA-Z_][a-zA-Z0-9_]* ;
CHAR_LITERAL  : '\'' [a-zA-Z0-9_]* '\'';
INT_LITERAL   : [+-]? [0-9]+ ;
FLOAT_LITERAL : [+-]? [0-9]+ '.' [0-9]+ | [+-]? [0-9]+ ; //2.2 y 2
DECIMAL_LITERAL: [+-]? [0-9]+ '.' [0-9]+ [dD] | [+-]? [0-9]+ [dD] ;//3.3D y 3D
COMPLEX_LITERAL
: [+-]? [0-9]+ ('.' [0-9]+)? [ \t]* [+-] [ \t]* [0-9]+ ('.' [0-9]+)? [iI]  // Ej: 4+5i, 3.14 - 2.5i, 4 + 2i
| [+-]? [0-9]+ ('.' [0-9]+)? [iI];                                    // Ej: 2i, 0.5i (Imaginarios puros)
//FUN_DECLARATION : '(' [a-zA-Z_][a-zA-Z0-9_]* ')' ':' [a-zA-Z_] '{' '}'
WS            : [ \t\r\n]+ -> skip ;