grammar Paxo;

// ==========================================
// 1. REGLAS DEL PARSER (Sintaxis Estructural)
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
                                            | expression ';' // Para llamadas a funciones directas
                                                | 'add' '<' IDENTIFIER ('.' IDENTIFIER)? '>' // Inclusión de paquetes como <Basic.paxo>
                                                    ;

                                                    // Declaración de variables soportando inferencia (var) y tamaños explícitos
                                                    varDeclaration
                                                        : type IDENTIFIER '=' expression
                                                            | type IDENTIFIER '[' INT_LITERAL? ']' '=' arrayLiteral
                                                                | type IDENTIFIER
                                                                    | type IDENTIFIER '[' INT_LITERAL ']'
                                                                        ;

                                                                        type
                                                                            : 'var' | 'xxsvar' | 'xsvar' | 'svar' | 'lvar' | 'xlvar'
                                                                                ;

                                                                                assignment
                                                                                    : IDENTIFIER '=' expression
                                                                                        | IDENTIFIER '++'
                                                                                            | IDENTIFIER '--'
                                                                                                ;

                                                                                                ifElseStatement
                                                                                                    : 'if' '(' expression ')' block ('else' block)?
                                                                                                        ;

                                                                                                        matchStatement
                                                                                                            : 'match' '(' IDENTIFIER ')' '{' matchCase+ '}'
                                                                                                                ;

                                                                                                                matchCase
                                                                                                                    : expression '->' block
                                                                                                                        | 'default' '->' block
                                                                                                                            ;

                                                                                                                            loopStatement
                                                                                                                                : 'loop' '(' expression ')' ':' ('stop' | 'go') block
                                                                                                                                    ;

                                                                                                                                    tryCatchStatement
                                                                                                                                        : 'try' block 'catch' '(' IDENTIFIER ('.' IDENTIFIER)? ')' block
                                                                                                                                            ;

                                                                                                                                            functionDeclaration
                                                                                                                                                : 'fun' IDENTIFIER '=' '(' parameterList? ')' block
                                                                                                                                                    ;

                                                                                                                                                    pkgDeclaration
                                                                                                                                                        : 'pkg' IDENTIFIER '=' '{' (varDeclaration | functionDeclaration)* '}'
                                                                                                                                                            ;

                                                                                                                                                            block
                                                                                                                                                                : '{' statement* '}'
                                                                                                                                                                    ;

                                                                                                                                                                    parameterList
                                                                                                                                                                        : IDENTIFIER (',' IDENTIFIER)*
                                                                                                                                                                            ;

                                                                                                                                                                            // Expresiones jerárquicas e inferencia de tipos dinámicos
                                                                                                                                                                            expression
                                                                                                                                                                                : INT_LITERAL
                                                                                                                                                                                    | UINT_LITERAL
                                                                                                                                                                                        | FLOAT_LITERAL
                                                                                                                                                                                            | DECIMAL_LITERAL
                                                                                                                                                                                                | COMPLEX_FLT_LITERAL
                                                                                                                                                                                                    | COMPLEX_DEC_LITERAL
                                                                                                                                                                                                        | CHAR_LITERAL
                                                                                                                                                                                                            | STRING_LITERAL
                                                                                                                                                                                                                | EMSTRING_LITERAL
                                                                                                                                                                                                                    | BOOLEAN
                                                                                                                                                                                                                        | VECTOR2D
                                                                                                                                                                                                                            | VECTOR4D
                                                                                                                                                                                                                                | NANOTIME_LITERAL
                                                                                                                                                                                                                                    | SLICE_LITERAL
                                                                                                                                                                                                                                        | POINTER_LITERAL
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
                                                                                                                                                                                                                                                                        // 2. REGLAS DEL LEXER (Tokens Primitivos)
                                                                                                                                                                                                                                                                        // ==========================================

                                                                                                                                                                                                                                                                        // Literales Numéricos y Matemáticos
                                                                                                                                                                                                                                                                        INT_LITERAL     : [+-]? [0-9]+ ;
                                                                                                                                                                                                                                                                        UINT_LITERAL    : [0-9]+ 'u' ;
                                                                                                                                                                                                                                                                        FLOAT_LITERAL   : [+-]? [0-9]+ '.' [0-9]+ ;
                                                                                                                                                                                                                                                                        DECIMAL_LITERAL : [+-]? [0-9]+ ('.' [0-9]+)? [dD] ;

                                                                                                                                                                                                                                                                        // Complejos (Soporta espacios opcionales antes de la 'i' o 'Di')
                                                                                                                                                                                                                                                                        COMPLEX_FLT_LITERAL : [+-]? [0-9]+ ('.' [0-9]+)? [+-] [0-9]+ ('.' [0-9]+)? [ \t]* 'i'
                                                                                                                                                                                                                                                                                            | [+-]? [0-9]+ ('.' [0-9]+)? [ \t]* 'i'
                                                                                                                                                                                                                                                                                                                ;

                                                                                                                                                                                                                                                                                                                COMPLEX_DEC_LITERAL : [+-]? [0-9]+ ('.' [0-9]+)? [+-] [0-9]+ ('.' [0-9]+)? [ \t]* 'Di'
                                                                                                                                                                                                                                                                                                                                    | [+-]? [0-9]+ ('.' [0-9]+)? [ \t]* 'Di'
                                                                                                                                                                                                                                                                                                                                                        ;

                                                                                                                                                                                                                                                                                                                                                        // Vectores (Se corrigieron los nombres y se permite flexibilidad de espacios en la coma)
                                                                                                                                                                                                                                                                                                                                                        VECTOR2D : '[' [ \t]* [+-]? [0-9]+ ('.' [0-9]+)? [ \t]* ',' [ \t]* [+-]? [0-9]+ ('.' [0-9]+)? [ \t]* ']' ;
                                                                                                                                                                                                                                                                                                                                                        VECTOR4D : '〔' [ \t]* expression_list [ \t]* '〕' ;

                                                                                                                                                                                                                                                                                                                                                        fragment expression_list : [+-]? [0-9]+ ('.' [0-9]+)? ([ \t]* ',' [ \t]* [+-]? [0-9]+ ('.' [0-9]+)?)* ;

                                                                                                                                                                                                                                                                                                                                                        // Estructuras de tiempo y memoria avanzadas de Paxo
                                                                                                                                                                                                                                                                                                                                                        NANOTIME_LITERAL : [0-9]+ ('.' [0-9]+)? ':' [0-9]+ ;
                                                                                                                                                                                                                                                                                                                                                        SLICE_LITERAL    : '&' [a-zA-Z_][a-zA-Z0-9_]* '~' [0-9]+ ;
                                                                                                                                                                                                                                                                                                                                                        POINTER_LITERAL  : '&' [a-zA-Z_][a-zA-Z0-9_]* ;

                                                                                                                                                                                                                                                                                                                                                        // Literales de Texto
                                                                                                                                                                                                                                                                                                                                                        CHAR_LITERAL     : '\'' . '\'' ;
                                                                                                                                                                                                                                                                                                                                                        STRING_LITERAL   : '"' (~["\r\n])* '"' ;
                                                                                                                                                                                                                                                                                                                                                        EMSTRING_LITERAL : '"' (~["\r\n])* '"' [ \t]* 'il' ; // Texto embebido / Inline string

                                                                                                                                                                                                                                                                                                                                                        BOOLEAN : 'true' | 'false' ;

                                                                                                                                                                                                                                                                                                                                                        // Identificadores (Se corrigió de '*' a '+' para evitar tokens vacíos)
                                                                                                                                                                                                                                                                                                                                                        IDENTIFIER : [a-zA-Z_\u{1F4A9}\u{1F926}\p{L}][a-zA-Z0-9_\u{1F4A9}\u{1F926}\p{L}\p{N}]* ;

                                                                                                                                                                                                                                                                                                                                                        // Ignorar espacios en blanco globales
                                                                                                                                                                                                                                                                                                                                                        WS : [ \t\r\n]+ -> skip ;