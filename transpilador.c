/* =============================================================
   TRANSPILADOR OFICIAL DE AXOLANG A C23 (axoc) - REVISIÓN ULTRA
   Compilado y ejecutado bajo el estándar estricto -std=c23
   =============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <ctype.h>

#define MAX_LINE_LEN 65536
#define MAX_BUFFER_FUNCTIONS 65536
#define MAX_METHODS 655

// --- Variables globales de control de estado (C23 bool nativo) ---
char funciones_paquetes[MAX_BUFFER_FUNCTIONS] = {};
char buffer_structs[MAX_BUFFER_FUNCTIONS] = {};
char buffer_globales[MAX_BUFFER_FUNCTIONS] = {};
bool in_pkg = false;
bool in_func_inside_pkg = false;
char current_pkg[655] = {};

// Control de retornos de arreglos y contextos de función
bool inside_any_function = false;
bool actual_func_retorna_int_array = false;
bool actual_func_retorna_dec_array = false;

// Estructura para registrar métodos dinámicamente
char lista_metodos[MAX_METHODS][1024];
int total_metodos = 0;

typedef struct {
  char items[512][1024];
  int count;
} Includes;

void add_include(Includes *inc, const char *lib) {
  for (int i = 0; i < inc->count; i++) {
    if (strcmp(inc->items[i], lib) == 0) return;
  }
  strcpy(inc->items[inc->count++], lib);
}

// Verifica si un carácter es un delimitador válido de variables/palabras clave
[[nodiscard]] bool es_delimitador(char c) {
  return c == '\0' || isspace((unsigned char)c) ||
  c == '(' || c == ')' || c == '{' || c == '}' ||
  c == '[' || c == ']' || c == ';' || c == ',' ||
  c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '&';
}

// Reemplaza palabras clave de modo inteligente evitando colisiones destructivas
void replace_keyword_safe(char *orig, const char *rep, const char *with, char *output) {
  char buffer[MAX_LINE_LEN] = {};
  char *insert_point = orig;
  char *tmp = buffer;
  int rep_len = strlen(rep);
  int with_len = strlen(with);

  while (true) {
    char *p = strstr(insert_point, rep);
    if (p == nullptr) {
      strcpy(tmp, insert_point);
      break;
    }

    bool es_inicio_valido = (p == orig) || es_delimitador(*(p - 1));
    bool es_fin_valido = es_delimitador(*(p + rep_len));

    if (es_inicio_valido && es_fin_valido) {
      memcpy(tmp, insert_point, p - insert_point);
      tmp += p - insert_point;
      memcpy(tmp, with, with_len);
      tmp += with_len;
      insert_point = p + rep_len;
    } else {
      size_t bytes_a_copiar = (p - insert_point) + rep_len;
      memcpy(tmp, insert_point, bytes_a_copiar);
      tmp += bytes_a_copiar;
      insert_point = p + rep_len;
    }
  }
  strcpy(output, buffer);
}

// Función auxiliar estándar para reemplazos simples (Operadores)
void replace_string(char *orig, const char *rep, const char *with, char *output) {
  char buffer[MAX_LINE_LEN] = {};
  char *insert_point = orig;
  char *tmp = buffer;
  int rep_len = strlen(rep);
  int with_len = strlen(with);

  while (true) {
    char *p = strstr(insert_point, rep);
    if (p == nullptr) {
      strcpy(tmp, insert_point);
      break;
    }
    memcpy(tmp, insert_point, p - insert_point);
    tmp += p - insert_point;
    memcpy(tmp, with, with_len);
    tmp += with_len;
    insert_point = p + rep_len;
  }
  strcpy(output, buffer);
}

void transpile_line(char *line, Includes *inc, char *out_line) {
  char src[MAX_LINE_LEN];
  strcpy(src, line);

  // 1. Trim inicial e izquierdo
  char *start = src;
  while (isspace((unsigned char)*start)) start++;
  if (strlen(start) == 0) {
    strcpy(out_line, "");
    return;
  }
  char *end = start + strlen(start) - 1;
  while (end > start && isspace((unsigned char)*end)) end--;
  *(end + 1) = '\0';

  if (strlen(start) == 0) {
    strcpy(out_line, "");
    return;
  }

  // 2. Directivas de inclusión del ecosistema Axolang (add <...>)
  if (strncmp(start, "add", 3) == 0) {
    if (strstr(start, "<Basic.axo>")) {
      add_include(inc, "#include <stdio.h>");
      add_include(inc, "#include <stdlib.h>");
      add_include(inc, "#include <stddef.h>");
    }
    if (strstr(start, "<Math.axo>")) {
      add_include(inc, "#include <math.h>");
      add_include(inc, "#include <tgmath.h>");
    }
    if (strstr(start, "<Text.axo>")) {
      add_include(inc, "#include <string.h>");
      add_include(inc, "#include <ctype.h>");
    }
    strcpy(out_line, "");
    return;
  }

  // Ignorar llamadas directas de main() al final del script
  if (strcmp(start, "main()") == 0 || strcmp(start, "main") == 0) {
    strcpy(out_line, "");
    return;
  }

  char buffer[MAX_LINE_LEN];
  strcpy(buffer, start);

  // Control estricto de cierre de llaves en funciones globales
  if (strcmp(buffer, "}") == 0 && !in_pkg) {
    inside_any_function = false;
    actual_func_retorna_int_array = false;
    actual_func_retorna_dec_array = false;
    strcpy(out_line, "}");
    return;
  }

  // Interceptor del Return para estructuras dinámicas de arreglos Axolang
  if (strncmp(buffer, "return ", 7) == 0) {
    if (inside_any_function && (actual_func_retorna_int_array || actual_func_retorna_dec_array)) {
      char var_name[50] = {};
      sscanf(buffer, "return %[^=\n ;]", var_name);
      char temp_ret[1024];
      if (actual_func_retorna_int_array) {
        sprintf(temp_ret, "AxoArray_int _ret = { .data = %s, .length = sizeof(%s)/sizeof(%s[0]) };\n    return _ret;", var_name, var_name, var_name);
      }
      else if (actual_func_retorna_dec_array) {
        sprintf(temp_ret, "AxoArray_dec _ret = { .data = %s, .length = sizeof(%s)/sizeof(%s[0]) };\n    return _ret;", var_name, var_name, var_name);
      }

      if (in_pkg && in_func_inside_pkg) {
        strcat(funciones_paquetes, "    ");
        strcat(funciones_paquetes, temp_ret);
        strcat(funciones_paquetes, "\n");
        strcpy(out_line, "");
      } else {
        strcpy(out_line, temp_ret);
      }
      return;
    }
  }

  // =============================================================
  // ESTADO: DENTRO DE UN PAQUETE (pkg)
  // =============================================================
  if (in_pkg) {
    // CASO A: Inicio de un método del paquete (func nombre = ...)
    if (!in_func_inside_pkg && (strncmp(buffer, "func ", 5) == 0 || strncmp(buffer, "Func ", 5) == 0)) {
      in_func_inside_pkg = true;
      inside_any_function = true;
      char func_name[50] = {};
      sscanf(buffer, "%*s %[^= \t]", func_name);

      int len_fn = strlen(func_name);
      while(len_fn > 0 && isspace((unsigned char)func_name[len_fn - 1])) {
        func_name[len_fn - 1] = '\0';
        len_fn--;
      }

      if (total_metodos < MAX_METHODS && strlen(func_name) > 0) {
        strcpy(lista_metodos[total_metodos++], func_name);
      }

      char argumentos[256] = "";
      char *open_p = strchr(buffer, '(');
      char *close_p = strchr(buffer, ')');
      if (open_p && close_p && (close_p > open_p + 1)) {
        size_t arg_len = close_p - (open_p + 1);
        strncpy(argumentos, open_p + 1, arg_len);
        argumentos[arg_len] = '\0';
      }

      // Corrección de tipos en argumentos internos
      replace_keyword_safe(argumentos, "Int", "int", argumentos);
      replace_keyword_safe(argumentos, "Dec", "double", argumentos);
      replace_keyword_safe(argumentos, "Bool", "bool", argumentos);

      char ret_type[30] = "void";
      if (strstr(buffer, ":[]int") || strstr(buffer, ":[]Int")) {
        actual_func_retorna_int_array = true;
        strcpy(ret_type, "AxoArray_int");
      }
      else if (strstr(buffer, ":[]dec") || strstr(buffer, ":[]Dec")) {
        actual_func_retorna_dec_array = true;
        strcpy(ret_type, "AxoArray_dec");
      }
      else if (strstr(buffer, ":int") || strstr(buffer, ":Int")) strcpy(ret_type, "int");
      else if (strstr(buffer, ":dec") || strstr(buffer, ":Dec")) strcpy(ret_type, "double");
      else if (strstr(buffer, ":char") || strstr(buffer, ":Char")) strcpy(ret_type, "char*");
      else if (strstr(buffer, ":[]char") || strstr(buffer, ":[]Char")) strcpy(ret_type, "char*");
      else if (strstr(buffer, ":bool") || strstr(buffer, ":Bool")) strcpy(ret_type, "bool");
      else if (strstr(buffer, ":any") || strstr(buffer, ":any")) strcpy(ret_type, "void*");

      char cabecera[512];
      sprintf(cabecera, "%s _%s_%s(%s) {\n", ret_type, current_pkg, func_name, argumentos);
      strcat(funciones_paquetes, cabecera);

      sprintf(buffer, "    %s (*%s)(%s);", ret_type, func_name, argumentos);
      strcat(buffer_structs, buffer);
      strcat(buffer_structs, "\n");

      strcpy(out_line, "");
      return;
    }

    // CASO B: Código interno del método del paquete
    if (in_func_inside_pkg) {
      if (strcmp(buffer, "}") == 0) {
        strcat(funciones_paquetes, "}\n\n");
        in_func_inside_pkg = false;
        inside_any_function = false;
        actual_func_retorna_int_array = false;
        actual_func_retorna_dec_array = false;
        strcpy(out_line, "");
        return;
      }

      // Reemplazos de tipos seguros
      replace_keyword_safe(buffer, "Int", "int", buffer);
      replace_keyword_safe(buffer, "Dec", "double", buffer);
      replace_keyword_safe(buffer, "Bool", "bool", buffer);
      replace_keyword_safe(buffer, "Char", "char", buffer);
      replace_keyword_safe(buffer, "Punt", "auto", buffer);
      replace_keyword_safe(buffer, "any", "void*", buffer);

      // Parseo de arreglos « » locales
      bool is_array_loc = (strstr(buffer, "[]") != nullptr && strchr(buffer, '=') != nullptr);
      bool is_char_array_loc = (strstr(buffer, "char") != nullptr);
      if (is_array_loc && !is_char_array_loc) {
        char *open_quote = strstr(buffer, "«");
        char *close_quote = strstr(buffer, "»");
        if (open_quote && close_quote && (close_quote > open_quote)) {
          char parte_izq[MAX_LINE_LEN] = {}; char parte_der[MAX_LINE_LEN] = {}; char contenido[MAX_LINE_LEN] = {};
          size_t izq_len = open_quote - buffer;
          strncpy(parte_izq, buffer, izq_len);
          strcpy(parte_der, close_quote + 2);
          size_t cont_len = close_quote - (open_quote + 2);
          strncpy(contenido, open_quote + 2, cont_len);
          for (size_t i = 0; i < strlen(contenido); i++) {
            if (contenido[i] == ' ' || contenido[i] == ',') contenido[i] = ',';
          }
          sprintf(buffer, "%s{%s}%s", parte_izq, contenido, parte_der);
        }
      } else {
        replace_string(buffer, "«", "\"", buffer);
        replace_string(buffer, "»", "\"", buffer);
      }

      replace_keyword_safe(buffer, "Printf", "printf", buffer);
      replace_string(buffer, "=>", "&", buffer);

      int len_int = strlen(buffer);
      if (len_int > 0 && buffer[len_int - 1] != '{' && buffer[len_int - 1] != '}' && buffer[len_int - 1] != ';' && buffer[len_int - 1] != "/") {
        strcat(buffer, ";");
      }

      strcat(funciones_paquetes, "    ");
      strcat(funciones_paquetes, buffer);
      strcat(funciones_paquetes, "\n");

      strcpy(out_line, "");
      return;
    }

    // CASO C: Fin de toda la estructura del paquete
    if (strcmp(buffer, "}") == 0 && !in_func_inside_pkg) {
      sprintf(buffer, "} %s;\n", current_pkg);
      strcat(buffer_structs, buffer);
      in_pkg = false;
      strcpy(out_line, "");
      return;
    }

    // CASO D: Miembros / Propiedades estándar del struct
    if (strchr(buffer, '=')) {
      char *has_equal = strchr(buffer, '=');
      if (has_equal) *has_equal = '\0';
      int len_c = strlen(buffer);
      while (len_c > 0 && isspace((unsigned char)buffer[len_c - 1])) {
        buffer[len_c - 1] = '\0';
        len_c--;
      }
    }

    replace_keyword_safe(buffer, "Int", "int", buffer);
    replace_keyword_safe(buffer, "Dec", "double", buffer);
    replace_keyword_safe(buffer, "Char", "char", buffer);
    replace_keyword_safe(buffer, "Bool", "bool", buffer);

    int len_p = strlen(buffer);
    if (len_p > 0 && buffer[len_p - 1] != ';') strcat(buffer, ";");

    strcat(buffer_structs, "    ");
    strcat(buffer_structs, buffer);
    strcat(buffer_structs, "\n");
    strcpy(out_line, "");
    return;
  }

  // =============================================================
  // ESTADO: ÁMBITO GLOBAL / FUERA DE PAQUETES
  // =============================================================
  if (strncmp(buffer, "pkg ", 4) == 0) {
    in_pkg = true;
    total_metodos = 0;
    char name[50] = {};
    sscanf(buffer, "pkg %s", name);
    char *bracket = strchr(name, '{'); if (bracket) *bracket = '\0';
    strcpy(current_pkg, name);

    sprintf(buffer, "typedef struct {\n");
    strcat(buffer_structs, buffer);
    strcpy(out_line, "");
    return;
  }

  // Procesamiento global de variables y tipos
  replace_keyword_safe(buffer, "Int", "int", buffer);
  replace_keyword_safe(buffer, "Dec", "double", buffer);
  replace_keyword_safe(buffer, "Bool", "bool", buffer);
  replace_keyword_safe(buffer, "Char", "char", buffer);
  replace_keyword_safe(buffer, "Void", "void", buffer);
  replace_keyword_safe(buffer, "Auto", "auto", buffer);
  replace_keyword_safe(buffer, "any", "void*", buffer);

  // Números complejos Axolang (2.1i -> 2.1 * I)
  if (strstr(buffer, "Com ") || strncmp(buffer, "Com", 3) == 0) {
    add_include(inc, "#include <complex.h>");
    replace_keyword_safe(buffer, "Com", "double complex", buffer);
    char *pos_i = strrchr(buffer, 'i');
    if (pos_i && (pos_i == buffer + strlen(buffer) - 1 || *(pos_i + 1) == ';')) {
      char temp[MAX_LINE_LEN] = {};
      strncpy(temp, buffer, pos_i - buffer);
      strcat(temp, " * I");
      if (*(pos_i + 1) == ';') strcat(temp, ";");
      strcpy(buffer, temp);
    }
  }

  // Punteros (*variable -> &variable)
  if (strstr(buffer, "Punt ") || strncmp(buffer, "Punt", 4) == 0) {
    replace_keyword_safe(buffer, "Punt", "auto", buffer);
    replace_string(buffer, "= *", "= &", buffer);
  }

  // Inicialización de Arreglos Globales o Locales « »
  bool is_array_glob = (strstr(buffer, "[]") != nullptr && strchr(buffer, '=') != nullptr);
  bool is_char_array_glob = (strstr(buffer, "char") != nullptr);
  if (is_array_glob && !is_char_array_glob) {
    char *open_quote = strstr(buffer, "«");
    char *close_quote = strstr(buffer, "»");
    if (open_quote && close_quote && (close_quote > open_quote)) {
      char parte_izq[MAX_LINE_LEN] = {}; char parte_der[MAX_LINE_LEN] = {}; char contenido[MAX_LINE_LEN] = {};
      size_t izq_len = open_quote - buffer;
      strncpy(parte_izq, buffer, izq_len);
      strcpy(parte_der, close_quote + 2);
      size_t cont_len = close_quote - (open_quote + 2);
      strncpy(contenido, open_quote + 2, cont_len);
      for (size_t i = 0; i < strlen(contenido); i++) {
        if (contenido[i] == ' ' || contenido[i] == ',') contenido[i] = ',';
      }
      sprintf(buffer, "%s{%s}%s", parte_izq, contenido, parte_der);
    }
  } else {
    replace_string(buffer, "«", "\"", buffer);
    replace_string(buffer, "»", "\"", buffer);
  }

  // Detección y parseo de Funciones Globales
  if (strncmp(buffer, "func ", 5) == 0) {
    inside_any_function = true;
    char func_name[50] = {};

    if (sscanf(buffer, "%*s %[^= ]", func_name) == 1) {
      char argumentos[256] = "";
      char *open_p = strchr(buffer, '(');
      char *close_p = strchr(buffer, ')');
      if (open_p && close_p && (close_p > open_p + 1)) {
        size_t arg_len = close_p - (open_p + 1);
        strncpy(argumentos, open_p + 1, arg_len);
        argumentos[arg_len] = '\0';
      }

      replace_keyword_safe(argumentos, "Int", "int", argumentos);
      replace_keyword_safe(argumentos, "Dec", "double", argumentos);
      replace_keyword_safe(argumentos, "Bool", "bool", argumentos);

      if (strcmp(func_name, "main") == 0) {
        sprintf(buffer, "int main() {");
      } else {
        char ret_type[30] = "void";
        if (strstr(buffer, ":[]int") || strstr(buffer, ":[]Int")) {
          actual_func_retorna_int_array = true;
          strcpy(ret_type, "AxoArray_int");
        }
        else if (strstr(buffer, ":[]dec") || strstr(buffer, ":[]Dec")) {
          actual_func_retorna_dec_array = true;
          strcpy(ret_type, "AxoArray_dec");
        }
        else if (strstr(buffer, ":int") || strstr(buffer, ":Int")) strcpy(ret_type, "int");
        else if (strstr(buffer, ":dec") || strstr(buffer, ":Dec")) strcpy(ret_type, "double");
        else if (strstr(buffer, ":char") || strstr(buffer, ":Char")) strcpy(ret_type, "char*");
        else if (strstr(buffer, ":bool") || strstr(buffer, ":Bool")) strcpy(ret_type, "bool");
        else if (strstr(buffer, ":any") || strstr(buffer, ":any")) strcpy(ret_type, "void*");

        sprintf(buffer, "%s %s(%s) {", ret_type, func_name, argumentos);
      }
      strcpy(out_line, buffer);
      return;
    }
  }

  // Enlace y enlace vtable dinámico para instanciar structs
  if (isalpha((unsigned char)buffer[0]) && !strchr(buffer, '=') && !strchr(buffer, '(') && !strchr(buffer, '}')) {
    char tipo_posible[50] = {}; char var_posible[50] = {};
    if (sscanf(buffer, "%s %s", tipo_posible, var_posible) == 2) {
      if (strcmp(tipo_posible, "int") != 0 && strcmp(tipo_posible, "double") != 0 &&
        strcmp(tipo_posible, "bool") != 0 && strcmp(tipo_posible, "char") != 0 &&
        strcmp(tipo_posible, "void") != 0 && strcmp(tipo_posible, "return") != 0 &&
        strcmp(tipo_posible, "auto") != 0) {

        char buffer_instancia[4096];
        sprintf(buffer_instancia, "%s %s;", tipo_posible, var_posible);
        for (int m = 0; m < total_metodos; m++) {
          if (strlen(lista_metodos[m]) == 0) continue;
          char linea_enlace[256];
          sprintf(linea_enlace, "\n    %s.%s = _%s_%s;", var_posible, lista_metodos[m], tipo_posible, lista_metodos[m]);
          strcat(buffer_instancia, linea_enlace);
        }
        strcpy(out_line, buffer_instancia);
        return;
      }
    }
  }

  // Ajustes de operadores de Axolang y funciones IO
  replace_keyword_safe(buffer, "Printf", "printf", buffer);
  replace_string(buffer, ",system", "", buffer);
  replace_string(buffer, ", system", "", buffer);
  replace_string(buffer, "=>", "&", buffer);
  if (strstr(buffer, "Stop(system)")) strcpy(buffer, "return 0;");

  replace_string(buffer, "≠", "!=", buffer);
  replace_string(buffer, "≤", "<=", buffer);
  replace_string(buffer, "≥", ">=", buffer);
  replace_string(buffer, "X|", "^", buffer);

  // Regla estricta de punto y coma al final
  int len = strlen(buffer);
  if (len > 0) {
    char last_char = buffer[len - 1];
    if (last_char != '{' && last_char != ';' && last_char != ',' &&
      strncmp(buffer, "if", 2) != 0 && strncmp(buffer, "for", 3) != 0 && strncmp(buffer, "while", 5) != 0) {
      strcat(buffer, ";");
    }
  }

  // CRÍTICO: Si no estamos dentro de una función, la instrucción es una asignación global
  if (!inside_any_function) {
    strcat(buffer_globales, buffer);
    strcat(buffer_globales, "\n");
    strcpy(out_line, "");
  } else {
    //strcpy(out_line, buffer);
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Uso: %s <archivo.axo> [-o <nombre_ejecutable>]\n", argv[0]);
    return 1;
  }

  auto input_filename = argv[1];
  char output_executable[256] = "a.out";
  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "-o") == 0 && (i + 1) < argc) {
      strcpy(output_executable, argv[i + 1]);
      break;
    }
  }

  FILE *input = fopen(input_filename, "r");
  if (input == nullptr) {
    perror("Error al abrir el archivo Axolang");
    return 1;
  }

  char temp_c_file[] = "_temp_axoc_output.c";
  FILE *output = fopen(temp_c_file, "w");
  if (output == nullptr) {
    perror("Error al crear archivo C temporal");
    fclose(input);
    return 1;
  }

  Includes inc = {};

  size_t body_capacity = 32768;
  char *code_body = malloc(body_capacity);
  if (code_body == nullptr) {
    perror("Error crítico: Memoria insuficiente");
    fclose(input); fclose(output); return 1;
  }
  code_body[0] = '\0';
  size_t body_len = 0;

  char line[1024];
  char transpiled_line[1024];

  while (fgets(line, sizeof(line), input)) {
    transpile_line(line, &inc, transpiled_line);
    if (strlen(transpiled_line) > 0) {
      size_t espacio_necesario = body_len + strlen(transpiled_line) + 6;
      if (espacio_necesario >= body_capacity) {
        body_capacity *= 2;
        char *new_ptr = realloc(code_body, body_capacity);
        if (new_ptr == nullptr) {
          free(code_body); fclose(input); fclose(output); return 1;
        }
        code_body = new_ptr;
      }
      strcat(code_body, "    ");
      strcat(code_body, transpiled_line);
      strcat(code_body, "\n");
      body_len = strlen(code_body);
    }
  }
  fclose(input);

  // === ARMADO DE ARQUITECTURA E INYECCIÓN JERÁRQUICA ===
  fprintf(output, "/* Código C23 generado automáticamente por Axolang (axoc) */\n");
  for (int i = 0; i < inc.count; i++) {
    fprintf(output, "%s\n", inc.items[i]);
  }

  fprintf(output, "\n/* Definiciones Base de Arreglos de Axolang */\n");
  fprintf(output, "typedef struct {\n    int* data;\n    size_t length;\n} AxoArray_int;\n");
  fprintf(output, "typedef struct {\n    double* data;\n    size_t length;\n} AxoArray_dec;\n\n");

  if (strlen(buffer_structs) > 0) {
    fprintf(buffer_globales, "\n/* Definición de Estructuras Axolang */\n");
    fprintf(buffer_globales, "%s\n", buffer_structs);
  }

  if (strlen(funciones_paquetes) > 0) {
    fprintf(buffer_globales, "\n/* Métodos Extraídos de Paquetes Axolang */\n");
    fprintf(buffer_globales, "%s\n", funciones_paquetes);
  }

  // SECCIÓN CORRECTA: Variables Globales inyectadas en el Top-Level de C
  if (strlen(buffer_globales) > 0) {
    fprintf(buffer_globales, "\n/* Variables Globales de Axolang */\n");
    fprintf(buffer_globales, "%s\n", buffer_globales);
  }

  fprintf(buffer_globales, "\n%s", code_body);
  fclose(buffer_globales);
  free(code_body);

  char compile_command[512];
  sprintf(compile_command, "gcc -std=c23 %s -lm -o %s", temp_c_file, output_executable);
  printf("[axoc] Transpilando %s...\n", input_filename);
  printf("[axoc] Compilando en modo C23 nativo puro mediante GCC...\n");

  int result = system(compile_command);
  if (result == 0) {
    printf("[axoc] ¡Éxito! Ejecutable nativo C23 generado con éxito: '%s'\n", output_executable);
  } else {
    printf("[axoc] Error: Falló la compilación nativa en GCC.\n");
    return 1;
  }

  return 0;
}