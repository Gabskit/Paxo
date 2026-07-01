grammar Axolang;

// Regla raíz del programa
program
    : statement* EOF
    ;

// Un statement puede ser una declaración de variable
statement
    : varDeclaration ';'
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
    
    // Tipos decimales corregidos
    | 'sdec' | 'dec' | 'ldec'
    
    // Números complejos de rango extendido
    | 'xscom' | 'scom' | 'com' | 'lcom' | 'xlcom'
    ;

// Expresión matemática o literal simple por ahora
expression
    : INT_LITERAL
    | FLOAT_LITERAL
    | IDENTIFIER
    ;

// --- TOKENS LÉXICOS ---
IDENTIFIER    : [a-zA-Z_][a-zA-Z0-9_]* ;
INT_LITERAL   : [0-9]+ ;
FLOAT_LITERAL : [0-9]+ '.' [0-9]+ ;
WS            : [ \t\r\n]+ -> skip ;