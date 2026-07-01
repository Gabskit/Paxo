import antlr4 from "antlr4";
import AxolangLexer from "./AxolangLexer.js";
import AxolangParser from "./AxolangParser.js";
import AxolangListener from "./AxolangListener.js";

// Estructura fija de C que definimos en el Paso 2
const HEADER_C = `
#include <stdint.h>
#include <complex.h>
// Estructura universal de costo cero para simular excepciones
typedef struct {
    int64_t value;       // El valor de retorno real si todo sale bien
    bool has_error;      // Bandera estática de error (0 o 1)
    int32_t error_code;  // ID del tipo de error
} axo_result_t;

// === Nivel 1: xsany (Unión pura de 16 bits / 2 Bytes) ===
typedef union {
    int8_t    axo_xxsint;   // Entero ultra-corto con signo
    uint8_t   axo_xxsintu;  // Entero ultra-corto sin signo
    int16_t   axo_xsint;    // Entero corto con signo
    uint16_t  axo_xsintu;   // Entero corto sin signo
    _Float16  axo_xsflt;
    char axo_chara;
    bool axo_boo;
} axo_xsany_t;

// === Nivel 2: sany (Unión pura de 32 bits / 4 Bytes) ===
typedef union {
    int8_t    axo_xxsint;   // Entero ultra-corto con signo
    uint8_t   axo_xxsintu;  // Entero ultra-corto sin signo
    int16_t   axo_xsint;    // Entero corto con signo
    uint16_t  axo_xsintu;   // Entero corto sin signo
    _Float16  axo_xsflt;
    char axo_chara;
    bool axo_boo;
    // Hereda/incluye la capacidad de los tipos de 16 bits y añade:
    int32_t   axo_sint;     // Entero estándar de 32 bits
    uint32_t  axo_sintu;    // Entero de 32 bits sin signo
    float     axo_sflt;     // Decimal corto (punto flotante de precisión simple)
    _Float16 axo_xscom;
    _Decimal32 axo_dec;
} axo_sany_t;

// === Nivel 3: any / lany (Unión pura de 64 bits / 8 Bytes) ===
typedef union {
  
    int8_t    axo_xxsint;   // Entero ultra-corto con signo
    uint8_t   axo_xxsintu;  // Entero ultra-corto sin signo
    int16_t   axo_xsint;    // Entero corto con signo
    uint16_t  axo_xsintu;   // Entero corto sin signo
    _Float16  axo_xsflt;
    char axo_chara;
    bool axo_boo;
    // Hereda/incluye la capacidad de los tipos de 16 bits y añade:
    int32_t   axo_sint;     // Entero estándar de 32 bits
    uint32_t  axo_sintu;    // Entero de 32 bits sin signo
    float     axo_sflt;     // Decimal corto (punto flotante de precisión simple)
    _Float16 axo_xscom;
    _Decimal32 axo_dec;
    // Escala para soportar enteros y decimales masivos de alta precisión:
    int64_t   axo_int;      // Entero largo de 64 bits
    uint64_t  axo_intu;     // Entero largo de 64 bits sin signo
    double    axo_flt;      // Decimal estándar de doble precisión
    float complex axo_scom; // Número complejo corto (2x float de 32 bits)
    _Decimal64 axo_dec;
    void* axo_other;
} axo_any_t;

`;

class AxolangToCListener extends AxolangListener {
    constructor() {
        super();
        this.outputC = "";
    }

    // Se ejecuta al leer una declaración de variable (ej: auto x = 10;)
    enterVarDeclaration(ctx) {
        const id = ctx.IDENTIFIER().getText();
        let value = ctx.expression().getText();
        let type = ctx.getChild(0).getText(); // Puede ser 'auto' o un tipo explícito

        // INFERENCIA AUTOMÁTICA (Carga cognitiva asumida por tu compilador)
        if (type === "auto") {
            // Si el valor tiene un punto, inferimos 'dec' (double en C), si no, 'int' (int64_t)
            if (value.includes(".")) {
                if (value.includes("D")) {
                    type = "dec";
                } else {
                    type = "flt";
                }
            } else if (value.includes("i")) {
                type = "com";
            } else if (value.includes("true") || value.includes("false")) {
                type = "boo";
            } else {
                type = "int";
            }
        }
        let preval;
        // Traducir los tipos de Axolang a tipos primitivos de C
        switch (type) {
            case "xxsint":
                this.outputC += "int8_t " + id + " = " + value + ";\n";
                break;
            case "xsint":
                this.outputC += "int16_t " + id + " = " + value + ";\n";
                break;
            case "sint":
                this.outputC += "int32_t " + id + " = " + value + ";\n";
                break;
            case "int":
                this.outputC += "int64_t " + id + " = " + value + ";\n";
                break;
            case "lint":
                this.outputC += "_BitInt(128) " + id + " = " + value + ";\n";
                break;
            case "xlint":
                this.outputC += "_BitInt(256) " + id + " = " + value + ";\n";
                break;
            case "xxsintu":
                this.outputC += "uint8_t " + id + " = " + value + ";\n";
                break;
            case "xsintu":
                this.outputC += "uint16_t " + id + " = " + value + ";\n";
                break;
            case "sintu":
                this.outputC += "uint32_t " + id + " = " + value + ";\n";
                break;
            case "intu":
                this.outputC += "uint64_t " + id + " = " + value + ";\n";
                break;
            case "lintu":
                this.outputC +=
                    "unsigned _BitInt(128) " + id + " = " + value + ";\n";
                break;
            case "xlintu":
                this.outputC +=
                    "unsigned _BitInt(256) " + id + " = " + value + ";\n";
                break;
            case "xsflt":
                this.outputC += "_Float16 " + id + " = " + value + ";\n";
                break;
            case "sflt":
                this.outputC += "float " + id + " = " + value + ";\n";
                break;
            case "flt":
                this.outputC += "double " + id + " = " + value + ";\n";
                break;
            case "lflt":
                this.outputC += "long double " + id + " = " + value + ";\n";
                break;
            case "xlflt":
                this.outputC += "_Float256 " + id + " = " + value + ";\n";
                break;
            case "xscom":
                value = value.replace(/i$/, " * I");
                this.outputC +=
                    "_Float16 complex " + id + " = " + value + " ;\n";
                break;
            case "scom":
                value = value.replace(/i$/, " * I");
                this.outputC += "float complex " + id + " = " + value + " ;\n";
                break;
            case "com":
                value = value.replace(/i$/, " * I");
                this.outputC += "double complex " + id + " = " + value + " ;\n";
                break;
            case "lcom":
                value = value.replace(/i$/, " * I");
                this.outputC +=
                    "long double complex " + id + " = " + value + " ;\n";
                break;
            case "sdec":
                value = value.replace(/D$/, "DF");
                this.outputC += "_Decimal32 " + id + " = " + value + ";\n";
                break;
            case "dec":
                value = value.replace(/D$/, "DD");
                this.outputC += "_Decimal64 " + id + " = " + value + ";\n";
                break;
            case "ldec":
                value = value.replace(/D$/, "DL");
                this.outputC += "_Decimal128 " + id + " = " + value + ";\n";
                break;
            case "chara":
                this.outputC += "char " + id + " = " + value + ";\n";
                break;
            case "boo":
                this.outputC += "bool " + id + " = " + value + ";\n";
                break;
            default:
            // code
        }
    }
    enterMatchStatement(ctx) {
        const exprText = ctx.IDENTIFIER().getText();

        // Detectamos si es un número complejo (contiene una 'i') o una estructura
        const esComplejo = exprText.includes("i") || exprText.includes("+");

        if (!esComplejo) {
            // Generamos un switch/case rígido de C de alta velocidad
            this.outputC += `    switch (${exprText}) {\n`;
        } else {
            // Marcamos que iniciaremos una cascada if-else para tipos complejos
            this.outputC += `    // Cascada lógica para tipo complejo\n`;
            this.isComplexMatch = true;
            this.matchExpr = exprText;
            this.caseCount = 0;
        }
    }

    enterMatchCase(ctx) {
        const caseExpr = ctx.expression(0).getText();
        const actionExpr = ctx.declaration(0).getText();

        if (!this.isComplexMatch) {
            // Modo Switch Rígido
            if (ctx.getChild(0).getText() === "_") {
                this.outputC += `        default:\n            // Acción del caso por defecto\n            break;\n`;
            } else {
                this.outputC += `        case ${caseExpr}:\n \n
                break;\n`;
            }
        } else {
            // Modo Cascada If-Else para complejos (usa <complex.h>)
            if (ctx.getChild(0).getText() === "_") {
                this.outputC += `    else {\n        // Defecto complejo\n    }\n`;
            } else {
                let prefix = this.caseCount === 0 ? "    if" : "    else if";
                // En C, los complejos no se comparan con ==, se usa creal() y cimag()
                this.outputC += `${prefix} (creal(${this.matchExpr}) == creal(${caseExpr}) && cimag(${this.matchExpr}) == cimag(${caseExpr})) {\n        // Acción\n    }\n`;
                this.caseCount++;
            }
        }
    }

    exitMatchStatement(ctx) {
        if (!this.isComplexMatch) {
            this.outputC += `    }\n`;
        }
        this.isComplexMatch = false; // Resetear estado
    }
}

// Función principal del Transpilador
function transpile(inputCode) {
    const chars = new antlr4.InputStream(inputCode);
    const lexer = new AxolangLexer(chars);
    const tokens = new antlr4.CommonTokenStream(lexer);
    const parser = new AxolangParser(tokens);
    const tree = parser.program();

    const listener = new AxolangToCListener();
    antlr4.tree.ParseTreeWalker.DEFAULT.walk(listener, tree);

    // Construimos el archivo de C final
    let finalCode = HEADER_C + "\nint main() {\n";
    finalCode += listener.outputC;
    finalCode += "    return 0;\n}";

    return finalCode;
}

// --- PRUEBA DEL TRANSPILADOR ---
const codigoAxolang = `
auto inferido = 6.7D
chara letra = 'a'
boo onoff = true
dec dinero = 4.6D
flt decimal = 8.7
int entero = 69
com micomplejo = -6 + 9i
match(entero){
  1 -> {
    micomplejo = -6 - 7i
  }
  2 -> dinero = 5D ;
}
`;

console.log(transpile(codigoAxolang));
