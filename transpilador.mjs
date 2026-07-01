import antlr4 from "antlr4";
import AxolangLexer from "./AxolangLexer.js";
import AxolangParser from "./AxolangParser.js";
import AxolangListener from "./AxolangListener.js";

// Estructura fija de C que definimos en el Paso 2
const HEADER_C = `...`; // Aquí pegas el código del Paso 2

class AxolangToCListener extends AxolangListener.AxolangListener {
    constructor() {
        super();
        this.outputC = "";
    }

    // Se ejecuta al leer una declaración de variable (ej: auto x = 10;)
    enterVarDeclaration(ctx) {
        const id = ctx.IDENTIFIER().getText();
        const value = ctx.expression().getText();
        let type = ctx.getChild(0).getText(); // Puede ser 'auto' o un tipo explícito

        // INFERENCIA AUTOMÁTICA (Carga cognitiva asumida por tu compilador)
        if (type === "auto") {
            // Si el valor tiene un punto, inferimos 'dec' (double en C), si no, 'int' (int64_t)
            if (value.includes(".")) {
                type = "flt";
            } else {
                type = "int";
            }
        }

        // Traducir los tipos de Axolang a tipos primitivos de C
        switch (type) {
            case "int":
                this.outputC += "int64_t ${id} = ${value};\n";
                break;
            case "flt":
                this.outputC += "double ${id} = ${value};\n";
                break;
            default:
            // code
        }
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
auto miEntero = 42;
flt miDecimal = 3.14;
int variableDinamica = 100;
`;

console.log(transpile(codigoAxolang));
