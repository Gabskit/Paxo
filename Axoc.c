// --- HABILITAR EXTENSIONES POSIX PARA FMEMOPEN ---
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Enumeración de Tokens para Axolang (Actualizada a Tipado Estático C23)
typedef enum {
  TOKEN_EOF,
  TOKEN_NEWLINE,
  TOKEN_UNKNOWN,
  TOKEN_INT,
  TOKEN_DEC,
  TOKEN_COM,
  TOKEN_CHAR,
  TOKEN_BOOL,
  TOKEN_PKG,
  TOKEN_FUNC,
  TOKEN_AUTO,
  TOKEN_VOID,

  // Nuevos Punteros Estáticos de Axolang
  TOKEN_PINT,
  TOKEN_PDEC,
  TOKEN_PBOOL,
  TOKEN_PCOM,
  TOKEN_PCHAR,
  TOKEN_PPKG,
  TOKEN_PFUNC,
  TOKEN_PAUTO,
  TOKEN_PVOID,

  TOKEN_ADD,
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_CHAR_LITERAL,
  TOKEN_ASSIGN,
  TOKEN_REF_ARROW,
  // =>
  TOKEN_COLON,
  TOKEN_COMMA,
  TOKEN_SEMICOLON,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_LARRAY,
  // «
  TOKEN_RARRAY,
  // »

  // Operadores
  TOKEN_OP_MULT,
  // × o *
  TOKEN_OP_DIV,
  // ÷ o /
  TOKEN_OP_SQRT,
  // √
  TOKEN_OP_EXP,
  // ^
  TOKEN_OP_AND,
  // & o &&
  TOKEN_OP_OR,
  // | o ||
  TOKEN_OP_XOR,
  // §
  TOKEN_OP_BITAND,
  // .&
  TOKEN_OP_BITOR,
  // .|
  TOKEN_OP_BITXOR,
  // .§
  TOKEN_OP_EQUAL,
  TOKEN_OP_GE,
  TOKEN_OP_LE,
  TOKEN_OP_NOTEQUAL // ≠ o !=
} TokenType;

typedef struct {
  TokenType type;
  char lexeme[512];
} Token;

typedef struct {
  char type[32]; // Ajustado para tipos como "_Complex double" o punteros
  char* name;
  char* otros;
} Var;
char *codigo_base = NULL;

// Pila global para emparejar correctamente si un « » cierra con } o con "
char p_llaves[512];
int p_top = 0;
// Función auxiliar para avanzar los espacios en blanco modificando el puntero real
void saltar_espacios(char **src) {
  while (**src && (**src == '\t' || **src == '\r')) {
    (*src)++;
  }
}
bool es_arreglo(const char* s) {
  bool tiene_letras = false;
  bool tiene_comas = false;
  while (*s && strncmp(s, "»", 2) != 0) {
    if (*s == ',') tiene_comas = true;
    if (isalpha((unsigned char)*s)) tiene_letras = true;
    s++;
  }
  if (tiene_comas) return true; // Si tiene comas, es un inicializador de arreglo: «0,3,5» -> {0,3,5}
  if (tiene_letras) return false; // Si tiene letras y no comas, es un string literal: «hola» -> "hola"
  return true; // Por defecto (números puros sin comas como «5») es un arreglo
}
char buscar_ultimo_origen_linea(char *base, char *actual) {
  char *p = actual - 1;
  while (p >= base && *p != '\n') {
    if (*p != ' ' && *p != '\t' && *p != '\r') {
      return *p;
    }
    p--;
  }
  return '\n'; // Retorna salto de línea si la línea estaba vacía
}
// Analizador de caracteres multibyte UTF-8 y operadores especiales
void special_chars(char **src, FILE* output) {
  if (strncmp(*src, "«", 2) == 0) {
    if (es_arreglo(*src + 2)) {
      fprintf(output, "{");
      if (p_top < 512) p_llaves[p_top++] = '}';
    } else {
      fprintf(output, "\"");
      if (p_top < 512) p_llaves[p_top++] = '"';
    }(*src) += 2;
  } else if (strncmp(*src, "»", 2) == 0) {
    if (p_top > 0) {
      char c = p_llaves[--p_top];
      fputc(c, output);
    } else {
      fputc('}', output); // Fallback de seguridad
    }(*src) += 2;
  } else if (strncmp(*src, "=>", 2) == 0) {
    fprintf(output, "&"); // Referencia a dirección en C
    (*src) += 2;
  } else if (strncmp(*src, "×", 2) == 0) {
    fprintf(output, "*");
    (*src) += 2;
  } else if (strncmp(*src, "÷", 2) == 0) {
    fprintf(output, "/");
    (*src) += 2;
  } else if (strncmp(*src, "≠", 3) == 0) {
    // Símbolo UTF-8 de 3 bytes
    fprintf(output, "!=");
    (*src) += 3;
  } else if (strncmp(*src, "§", 2) == 0) {
    // Nota: El XOR lógico requiere un formateo ((!A) != (!B)), aquí dejamos la marca base
    fprintf(output, " != ");
    (*src) += 2;
  } else if (**src == '^') {
    fprintf(output, "pow"); // Mapeo matemático preliminar
    (*src)++;
  } else {
    // Si no es un operador especial, pasar el carácter normal
    fputc(**src, output);
    (*src)++;
  }
}

// Obtiene y transpila declaraciones de variables simples de forma segura
void get_var(char **src, FILE* output) {
  saltar_espacios(src);

  if (strncmp(*src, "int ", 4) == 0) {
    Var new_var;
    strcpy(new_var.type, "int");
    fprintf(output, "%s ", new_var.type);
    (*src) += 4;

    // Medimos el identificador de la variable de forma segura
    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
  }
  else if (strncmp(*src, "dec ", 4) == 0) {
    // Transpilación de Dec -> double
    Var new_var;
    strcpy(new_var.type, "double");
    fprintf(output, "%s ", new_var.type);
    (*src) += 4;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
    //(*src) += 4;
  } else if(strncmp(*src, "com ", 4) == 0) {
    Var new_var;
    strcpy(new_var.type, "double complex");
    fprintf(output, "%s ", new_var.type);
    (*src) += 4;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
  } else if(strncmp(*src, "char ", 5) == 0) {
    Var new_var;
    strcpy(new_var.type, "char");
    fprintf(output, "%s ", new_var.type);
    (*src) += 5;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
  } else if (strncmp(*src, "bool ", 5) == 0) {
    Var new_var;
    strcpy(new_var.type, "bool");
    fprintf(output, "%s ", new_var.type);
    (*src) += 5;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
  } else if(strncmp(*src, "pint ", 5) == 0) {
    Var new_var;
    strcpy(new_var.type, "int*");
    fprintf(output, "%s ", new_var.type);
    (*src) += 5;
    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
  } else if(strncmp(*src, "pdec ", 5) == 0) {
    Var new_var;
    strcpy(new_var.type, "double*");
    fprintf(output, "%s ", new_var.type);
    (*src) += 5;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
  } else if(strncmp(*src, "pcom ", 5) == 0) {
    Var new_var;
    strcpy(new_var.type, "double complex*");
    fprintf(output, "%s ", new_var.type);
    (*src) += 5;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
  } else if(strncmp(*src, "pchar ", 6) == 0) {
    Var new_var;
    strcpy(new_var.type, "char*");
    fprintf(output, "%s ", new_var.type);
    (*src) += 6;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
  } else if(strncmp(*src, "pbool ", 6) == 0) {
    Var new_var;
    strcpy(new_var.type, "bool*");
    fprintf(output, "%s ", new_var.type);
    (*src) += 6;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
  }else if(strncmp(*src, "pauto ", 6) == 0) {
    Var new_var;
    strcpy(new_var.type, "auto*");
    fprintf(output, "%s ", new_var.type);
    (*src) += 6;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
  } else if(strncmp(*src, "pvoid ", 6) == 0) {
    Var new_var;
    strcpy(new_var.type, "void*");
    fprintf(output, "%s ", new_var.type);
    (*src) += 6;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    fprintf(output, "%s", new_var.name);
    free(new_var.name);
  }
  else if (strncmp(*src, "func ", 5) == 0) {
    Var new_var;
    strcpy(new_var.type, "void"); // Retorno void por defecto si no hay ':'
    (*src) += 5;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    char *temporal = *src;
    while (*temporal && *temporal != '(') {
      if (*temporal == '=') *temporal = ' ';
      temporal++;
    }

    char *inicio_arg = *src;
    size_t lenarg = 0;

    while(*src && ((**src != ')') && (isalnum((unsigned char) **src) || **src == '_'))) {
      lenarg++;
      (*src)++;
    }

    new_var.otros = malloc(lenarg + 1);
    memcpy(new_var.otros, inicio_arg, lenarg);
    new_var.otros[lenarg] = '\0';

    char *buscar_retorno = *src;
    while (*buscar_retorno && *buscar_retorno != '{' && *buscar_retorno != '\n') {
      if (*buscar_retorno == ':') {
        *buscar_retorno = ' ';
        buscar_retorno++;
        //saltar_espacios(&buscar_retorno);
        if (strncmp(buscar_retorno, "int", 3) == 0) {
          strcpy(new_var.type, "int");
          memset(buscar_retorno, ' ', 3);
        }else if (strncmp(buscar_retorno, "dec", 3) == 0) {
          strcpy(new_var.type, "double");
          memset(buscar_retorno, ' ', 3);
        }else if (strncmp(buscar_retorno, "[]char", 6) == 0) {
          strcpy(new_var.type, "char*");
          memset(buscar_retorno, ' ', 6);
        } else if (strncmp(buscar_retorno, "[]dec", 5) == 0) {
          strcpy(new_var.type, "double*");
          memset(buscar_retorno, ' ', 5);
        } else {
          strcpy(new_var.type, "void");
          memset(buscar_retorno, ' ', 4);
        }
        break;
      }
      /*else {
        strcpy(new_var.type, "void");
        fprintf(output, "%s ", new_var.type);
        (*src) += 4;
        //memset(buscar_retorno, ' ', 4);
      }*/
      buscar_retorno++;
    }
    // 4. Escribir en el orden estricto de C: Tipo Nombre Argumentos
    fprintf(output, "%s %s%s", new_var.type, new_var.name, new_var.otros);

    // Liberar memoria local de la función
    free(new_var.name);
    free(new_var.otros);
    return;
  }else if (strncmp(*src, "pkg ", 4) == 0) {
    Var new_var;
    strcpy(new_var.type, "typedef struct");
    (*src) += 4;

    char *inicio_nombre = *src;
    size_t len = 0;
    while (**src && (isalnum((unsigned char)**src) || **src == '_')) {
      len++;
      (*src)++;
    }

    new_var.name = malloc(len + 1);
    memcpy(new_var.name, inicio_nombre, len);
    new_var.name[len] = '\0';

    char *temporal = *src;
    while (*temporal && *temporal != '{') {
      if (*temporal == '=') *temporal = ' ';
      temporal++;
    }
    // Almacenamos struct estructurado de C con su Alias final: typedef struct nombre { ... } nombre;
    fprintf(output, "%s", new_var.type);

    // Avanzamos hasta encontrar la llave de apertura del bloque struct
    while (**src && **src != '{') {
      (*src)++;
    }
    fprintf(output, " {\n");
    (*src)++; // Brincamos el '{'

    // Procesamos el interior del struct de forma anidada
    int llaves = 1;
    while (**src && llaves > 0) {
      if (**src == '{') llaves++;
      if (**src == '}') {
        llaves--;
        if (llaves == 0) {
          (*src)++;
          break;
        }
      }
      get_var(src, output);
    }

    fprintf(output, "} %s;\n", new_var.name);
    free(new_var.name);
    return;
  }
  if (strncmp(*src, "inline_c", 8) == 0) {
    (*src) += 8; // Brincamos la palabra clave
    saltar_espacios(src);

    if (**src == '{') {
      (*src)++; // Brincamos la llave de apertura del bloque C

      // Capturamos TODO el código C puro que está dentro de las llaves (nuestro Valor)
      // considerando que puede haber llaves internas anidadas.
      int llaves_anidadas = 1;
      while (**src && llaves_anidadas > 0) {
        if (**src == '{') llaves_anidadas++;
        if (**src == '}') {
          llaves_anidadas--;
          if (llaves_anidadas == 0) {
            (*src)++; // Brincamos la última llave de cierre
            break;
          }
        }
        // Escribimos el código C nativo directamente en el archivo de salida
        // sin que pase por special_chars (así conservamos corchetes [], etc.)
        fputc(**src, output);
        (*src)++;
      }
      fprintf(output, "\n");
    }
    return;
  }

  if (strncmp(*src, "add <Basic.axo>", 15) == 0) {
    fprintf(output, "#include <stddef.h>\n");
    (*src) += 15;
  }
  if (strncmp(*src, "Stop(system)", 12) == 0) {
    fprintf(output, "return 0;\n");
    (*src) += 12;
    return;
  }
  if (**src == '\n' || **src == '\0') {
    char antes = buscar_ultimo_origen_linea(codigo_base, *src);
    // Si el último elemento de la línea no es estructural, ponemos punto y coma
    if (antes != ';' && antes != '{' && antes != '}' && antes != '\n') {
      fprintf(output, ";");
    }
    fputc(**src, output);
    if (**src == '\n') (*src)++;
    return;
  }

  // Si es un carácter común u operador especial, procesar normalmente
  special_chars(src, output);
}

void transpilar(char *src, FILE* output) {
  char *buffer = src;

  // Ahora 'buffer' avanza correctamente evitando bucles infinitos
  while(*buffer != '\0') {
    get_var(&buffer, output);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Uso: %s <archivo.axo> <salida_base>\n", argv[0]);
    return 1;
  }

  FILE* origen = fopen(argv[1], "r");
  if (!origen) {
    printf("Error: No se pudo abrir el archivo fuente '%s'\n", argv[1]);
    return 1;
  }

  fseek(origen, 0, SEEK_END);
  long tamano = ftell(origen);
  fseek(origen, 0, SEEK_SET);

  char* codigo_axolang = malloc(tamano + 1);
  if (!codigo_axolang) {
    printf("Error: Memoria insuficiente.\n");
    fclose(origen);
    return 1;
  }

  size_t leidos = fread(codigo_axolang, 1, tamano, origen);
  codigo_axolang[leidos] = '\0';
  fclose(origen);

  // Crear de forma segura el nombre del archivo de salida sin alterar argv[2]
  char archivo_salida_c[256];
  snprintf(archivo_salida_c, sizeof(archivo_salida_c), "%s.c", argv[2]);

  FILE* salida_c = fopen(archivo_salida_c, "w");
  if (!salida_c) {
    printf("Error: No se pudo crear el archivo de salida '%s'\n", archivo_salida_c);
    free(codigo_axolang);
    return 1;
  }

  // Estructuras de soporte Estáticas C23 (Limpiadas de la sobrecarga del antiguo 'any')
  fprintf(salida_c, "// --- C23 AUTO-GENERATED CODE FROM AXOLANG ---\n");
  fprintf(salida_c, "#include <complex.h>\n#include <math.h>\n#include <tgmath.h>\n");
  fprintf(salida_c, "#include <string.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n");

  transpilar(codigo_axolang, salida_c);
  fclose(salida_c);
  free(codigo_axolang);

  printf("[Axolang] Código intermedio '%s' generado con éxito.\n", archivo_salida_c);
  printf("[Axolang] Compilando binario nativo en estándar C23...\n");

  // El comando compila 'archivo_salida_c' (-std=c23) de manera limpia
  char comando[512];
  snprintf(comando, sizeof(comando), "clang %s -o %s -std=c23 -lm", archivo_salida_c, argv[2]);

  int resultado_compilacion = system(comando);

  if (resultado_compilacion == 0) {
    printf("[Axolang] ¡Compilación exitosa! Ejecutable creado como './%s'\n", argv[2]);
  } else {
    printf("[Axolang] Error durante la compilación nativa de C.\n");
  }

  return resultado_compilacion;
}