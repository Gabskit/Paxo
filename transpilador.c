
// Catálogo interno para registrar los tipos PKG válidos y evitar falsos positivos
char catalogo_paquetes[32][64];
int conteo_paquetes = 0;
// Catálogo interno para registrar variables declaradas como 'any'
char catalogo_comodines[128][64];
int conteo_comodines = 0;

void registrar_comodit(const char* nombre) {
  for (int i = 0; i < conteo_comodines; i++) {
    if (strcmp(catalogo_comodines[i], nombre) == 0) return;
  }
  strcpy(catalogo_comodines[conteo_comodines++], nombre);
}

bool es_comodin_registrado(const char* nombre) {
  for (int i = 0; i < conteo_comodines; i++) {
    if (strcmp(catalogo_comodines[i], nombre) == 0) return true;
  }
  return false;
}
void registrar_paquete(const char* nombre) {
  for (int i = 0; i < conteo_paquetes; i++) {
    if (strcmp(catalogo_paquetes[i], nombre) == 0) return;
  }
  strcpy(catalogo_paquetes[conteo_paquetes++], nombre);
}

bool es_paquete_registrado(const char* nombre) {
  for (int i = 0; i < conteo_paquetes; i++) {
    if (strcmp(catalogo_paquetes[i], nombre) == 0) return true;
  }
  return false;
}

// Búferes globales para almacenar código extraído
char funciones_extraidas[65536] = "";
char constructores_inicializadores[16384] = "";
char prototipos_lambdas[16384] = "";

// Forward declaration del motor léxico
Token get_next_token(const char **src);

// =====================================================================
// ANALIZADOR LÉXICO (LEXER)
// =====================================================================
Token get_next_token(const char **src) {
  Token token = {
    TOKEN_EOF,
    ""
  };

  while (**src == ' ' || **src == '\t') (*src)++;

  if (strncmp(*src, "//", 2) == 0) {
    while (**src != '\n' && **src != '\r' && **src != '\0') (*src)++;
  }

  if (**src == '\n' || **src == '\r') {
    token.type = TOKEN_NEWLINE;
    token.lexeme[0] = **src; token.lexeme[1] = '\0';
    (*src)++; return token;
  }

  if (**src == '\0') return token;

  if (strncmp(*src, "=>", 2) == 0) {
    token.type = TOKEN_REF_ARROW; strcpy(token.lexeme, "=>"); *src += 2; return token;
  }
  if (strncmp(*src, "++", 2) == 0) {
    token.type = TOKEN_UNKNOWN; strcpy(token.lexeme, "++"); *src += 2; return token;
  }
  if (strncmp(*src, "×", 2) == 0) {
    token.type = TOKEN_OP_MULT; strcpy(token.lexeme, "×"); *src += 2; return token;
  }
  if (strncmp(*src, "÷", 2) == 0) {
    token.type = TOKEN_OP_DIV; strcpy(token.lexeme, "÷"); *src += 2; return token;
  }
  if (strncmp(*src, "§", 2) == 0) {
    token.type = TOKEN_OP_XOR; strcpy(token.lexeme, "§"); *src += 2; return token;
  }
  if (strncmp(*src, "≥", 3) == 0) {
    token.type = TOKEN_OP_GE; strcpy(token.lexeme, "≥"); *src += 3; return token;
  }
  if (strncmp(*src, "≤", 3) == 0) {
    token.type = TOKEN_OP_LE; strcpy(token.lexeme, "≤"); *src += 3; return token;
  }
  if (strncmp(*src, "≠", 3) == 0) {
    token.type = TOKEN_OP_NOTEQUAL; strcpy(token.lexeme, "≠"); *src += 3; return token;
  }
  if (strncmp(*src, "√", 3) == 0) {
    token.type = TOKEN_OP_SQRT; strcpy(token.lexeme, "√"); *src += 3; return token;
  }

  if (strncmp(*src, "«", 2) == 0) {
    const char *lookahead = *src + 2;
    bool has_comma = false;
    while (*lookahead != '\0' && strncmp(lookahead, "»", 2) != 0) {
      if (*lookahead == ',') {
        has_comma = true; break;
      }
      lookahead++;
    }
    if (has_comma) {
      token.type = TOKEN_LARRAY; strcpy(token.lexeme, "«"); *src += 2; return token;
    } else {
      *src += 2; int i = 0;
      while (**src != '\0' && strncmp(*src, "»", 2) != 0) {
        token.lexeme[i++] = **src; (*src)++;
      }
      if (strncmp(*src, "»", 2) == 0) *src += 2;
      token.lexeme[i] = '\0'; token.type = TOKEN_STRING; return token;
    }
  }
  if (strncmp(*src, "»", 2) == 0) {
    token.type = TOKEN_RARRAY; strcpy(token.lexeme, "»"); *src += 2; return token;
  }

  if (strncmp(*src, "==", 2) == 0) {
    token.type = TOKEN_OP_EQUAL; strcpy(token.lexeme, "=="); *src += 2; return token;
  }
  if (**src == '=') {
    token.type = TOKEN_ASSIGN; strcpy(token.lexeme, "="); (*src)++; return token;
  }
  if (**src == '(') {
    token.type = TOKEN_LPAREN; strcpy(token.lexeme, "("); (*src)++; return token;
  }
  if (**src == ')') {
    token.type = TOKEN_RPAREN; strcpy(token.lexeme, ")"); (*src)++; return token;
  }
  if (**src == '{') {
    token.type = TOKEN_LBRACE; strcpy(token.lexeme, "{"); (*src)++; return token;
  }
  if (**src == '}') {
    token.type = TOKEN_RBRACE; strcpy(token.lexeme, "}"); (*src)++; return token;
  }
  if (**src == ':') {
    token.type = TOKEN_COLON; strcpy(token.lexeme, ":"); (*src)++; return token;
  }
  if (**src == ',') {
    token.type = TOKEN_COMMA; strcpy(token.lexeme, ","); (*src)++; return token;
  }
  if (**src == ';') {
    token.type = TOKEN_SEMICOLON; strcpy(token.lexeme, ";"); (*src)++; return token;
  }

  if (**src == '\'') {
    int i = 0; token.lexeme[i++] = **src; (*src)++;
    while (**src != '\0' && **src != '\'') {
      token.lexeme[i++] = **src; (*src)++;
    }
    if (**src == '\'') {
      token.lexeme[i++] = **src; (*src)++;
    }
    token.lexeme[i] = '\0'; token.type = TOKEN_CHAR_LITERAL; return token;
  }

  if (**src == '"') {
    int i = 0; (*src)++;
    while (**src != '\0' && **src != '"') {
      token.lexeme[i++] = **src; (*src)++;
    }
    if (**src == '"') (*src)++;
    token.lexeme[i] = '\0'; token.type = TOKEN_STRING; return token;
  }

  if ((**src >= 'a' && **src <= 'z') || (**src >= 'A' && **src <= 'Z') || **src == '_' || **src == '*' || **src == '[' || **src == ']') {
    int i = 0;
    while ((**src >= 'a' && **src <= 'z') || (**src >= 'A' && **src <= 'Z') || (**src >= '0' && **src <= '9') || **src == '_' || **src == '.' || **src == '*' || **src == '[' || **src == ']') {
      token.lexeme[i++] = **src; (*src)++;
    }
    token.lexeme[i] = '\0';

    if (strcmp(token.lexeme, "int") == 0) token.type = TOKEN_INT;
    else if (strcmp(token.lexeme, "dec") == 0) token.type = TOKEN_DEC;
    else if (strcmp(token.lexeme, "com") == 0) token.type = TOKEN_COM;
    else if (strcmp(token.lexeme, "char") == 0) token.type = TOKEN_CHAR;
    else if (strcmp(token.lexeme, "bool") == 0) token.type = TOKEN_BOOL;
    else if (strcmp(token.lexeme, "pkg") == 0) token.type = TOKEN_PKG;
    else if (strcmp(token.lexeme, "func") == 0) token.type = TOKEN_FUNC;
    else if (strcmp(token.lexeme, "punt") == 0) token.type = TOKEN_PUNT;
    else if (strcmp(token.lexeme, "any") == 0) token.type = TOKEN_ANY;
    else if (strcmp(token.lexeme, "auto") == 0) token.type = TOKEN_AUTO;
    else if (strcmp(token.lexeme, "void") == 0) token.type = TOKEN_VOID;
    else if (strcmp(token.lexeme, "add") == 0) token.type = TOKEN_ADD;
    else token.type = TOKEN_IDENTIFIER;
    return token;
  }

  if ((**src >= '0' && **src <= '9')) {
    int i = 0;
    while ((**src >= '0' && **src <= '9') || **src == '.' || **src == 'i') {
      token.lexeme[i++] = **src; (*src)++;
    }
    token.lexeme[i] = '\0'; token.type = TOKEN_NUMBER; return token;
  }

  token.type = TOKEN_UNKNOWN; token.lexeme[0] = **src; token.lexeme[1] = '\0'; (*src)++; return token;
}

// =====================================================================
// MOTOR DE TRANSPILACIÓN SEMÁNTICA RECURSIVA
// =====================================================================
void transpilar_bloque(const char **src_ptr, FILE *destino, bool in_pkg, const char* current_pkg_name, char* temp_constructor, bool *needs_semicolon, bool context_any) {
  Token token = get_next_token(src_ptr);
  bool asignando_a_any = context_any; // Heredar estado del contexto superior si existe
  bool ignorar_hasta_nueva_linea_pkg = false;
  char tipo_retorno_actual[64] = "void";
  bool mapeando_arreglo_literal = false;
  int conteo_elementos_arreglo = 0;
  char nombre_arreglo_actual[64] = "";
  while (token.type != TOKEN_EOF) {
    if (token.type == TOKEN_NEWLINE) {
      if (*needs_semicolon) {
        fprintf(destino, ";"); *needs_semicolon = false;
      }
      fprintf(destino, "\n");
      asignando_a_any = false; // Resetear contexto al cambiar de línea
      token = get_next_token(src_ptr);
      continue;
    }

    switch (token.type) {
      case TOKEN_ADD: {
        token = get_next_token(src_ptr);
        if (strstr(token.lexeme, "Basic.axo")) fprintf(destino, "#include <stdio.h>\n#include <stdlib.h>\n#include <stddef.h>\n");
        while (token.type != TOKEN_NEWLINE && token.type != TOKEN_EOF) token = get_next_token(src_ptr);
        *needs_semicolon = false;
        continue;
      }

      case TOKEN_INT: fprintf(destino, "int "); *needs_semicolon = false; break;
      case TOKEN_DEC: fprintf(destino, "double "); *needs_semicolon = false; break;
      case TOKEN_CHAR: fprintf(destino, "char "); *needs_semicolon = false; break;
      case TOKEN_BOOL: fprintf(destino, "bool "); *needs_semicolon = false; break;
      case TOKEN_VOID: fprintf(destino, "void "); *needs_semicolon = false; break;
      case TOKEN_AUTO: fprintf(destino, "auto "); *needs_semicolon = false; break;
      case TOKEN_COM: fprintf(destino, "double _Complex "); *needs_semicolon = false; break;
      case TOKEN_PUNT: fprintf(destino, "auto "); *needs_semicolon = false; break;

      case TOKEN_ANY:
      fprintf(destino, "Axoany_Struct ");
      asignando_a_any = true; // El siguiente identificador y asignación pertenecen a un comodín
      *needs_semicolon = false;

      // Mirar hacia adelante para registrar el nombre de la variable comodín
      const char *look_name = *src_ptr;
      Token name_tok = get_next_token(&look_name);
      if (name_tok.type == TOKEN_IDENTIFIER) {
        registrar_comodit(name_tok.lexeme);
      }

      break;

      case TOKEN_PKG: {
        token = get_next_token(src_ptr);
        char nuevo_pkg[128]; strcpy(nuevo_pkg, token.lexeme);
        registrar_paquete(nuevo_pkg);

        fprintf(destino, "typedef struct {\n");
        char sub_constructor[4096];
        sprintf(sub_constructor, "%s init_%s() {\n    %s instancia;\n", nuevo_pkg, nuevo_pkg, nuevo_pkg);

        while (token.type != TOKEN_LBRACE && token.type != TOKEN_EOF) token = get_next_token(src_ptr);

        bool sub_needs_semi = false;
        transpilar_bloque(src_ptr, destino, true, nuevo_pkg, sub_constructor, &sub_needs_semi, false);
        *needs_semicolon = false;
        break;
      }

      case TOKEN_FUNC: {
        token = get_next_token(src_ptr);
        char func_name[128]; strcpy(func_name, token.lexeme);

        get_next_token(src_ptr); // '='
        get_next_token(src_ptr); // '('

        char argumentos[256] = "";
        char argumentos_cuerpo[256] = "";
        Token arg_token = get_next_token(src_ptr);

        while (arg_token.type != TOKEN_RPAREN && arg_token.type != TOKEN_EOF) {
          if (arg_token.type == TOKEN_COMMA) {
            strcat(argumentos, ", "); strcat(argumentos_cuerpo, ", ");
            arg_token = get_next_token(src_ptr); continue;
          }
          char tipo_arg[64] = "";
          if (strcmp(arg_token.lexeme, "dec") == 0) strcpy(tipo_arg, "double");
          else if (strcmp(arg_token.lexeme, "int") == 0) strcpy(tipo_arg, "int");
          else if (strcmp(arg_token.lexeme, "char") == 0) strcpy(tipo_arg, "char");
          else if (strcmp(arg_token.lexeme, "bool") == 0) strcpy(tipo_arg, "bool");
          else strcpy(tipo_arg, arg_token.lexeme);

          Token name_arg = get_next_token(src_ptr);
          char arg_completo[128];
          sprintf(arg_completo, "%s %s", tipo_arg, name_arg.lexeme);
          strcat(argumentos, arg_completo); strcat(argumentos_cuerpo, arg_completo);
          arg_token = get_next_token(src_ptr);
        }

        char ret_type[64] = "void";
        Token next_tok = get_next_token(src_ptr);

        // ... dentro de la detección del tipo de retorno en TOKEN_FUNC ...
        if (next_tok.type == TOKEN_COLON) {
          char raw_ret[128] = "";
          next_tok = get_next_token(src_ptr);
          while (next_tok.type != TOKEN_LBRACE && next_tok.type != TOKEN_NEWLINE && next_tok.type != TOKEN_EOF) {
            strcat(raw_ret, next_tok.lexeme);
            next_tok = get_next_token(src_ptr);
          }

          // Guardamos el tipo de retorno para usarlo en los returns internos
          strcpy(tipo_retorno_actual, raw_ret);

          if (strcmp(raw_ret, "int") == 0) strcpy(ret_type, "int");
          else if (strcmp(raw_ret, "dec") == 0) strcpy(ret_type, "double");
          else if (strcmp(raw_ret, "char") == 0) strcpy(ret_type, "char");
          else if (strcmp(raw_ret, "[]int") == 0) strcpy(ret_type, "Axoarray_int");
          else if (strcmp(raw_ret, "[]dec") == 0) strcpy(ret_type, "Axoarray_dec");
          else if (strcmp(raw_ret, "[]char") == 0) strcpy(ret_type, "Axoarray_char");
          else if (strcmp(raw_ret, "[]any") == 0) strcpy(ret_type, "Axoarray_any");
        }

        while (next_tok.type != TOKEN_LBRACE && next_tok.type != TOKEN_EOF) next_tok = get_next_token(src_ptr);

        if (in_pkg) {
          fprintf(destino, "    %s (*%s)(%s);\n", ret_type, func_name, argumentos);

          char buffer_vinc[256];
          sprintf(buffer_vinc, "    instancia.%s = &%s_%s;\n", func_name, current_pkg_name, func_name);
          strcat(temp_constructor, buffer_vinc);

          char buf_func[8192] = "";
          FILE *f_mem = fmemopen(buf_func, sizeof(buf_func), "w");
          fprintf(f_mem, "%s %s_%s(%s) {\n", ret_type, current_pkg_name, func_name, argumentos_cuerpo);

          bool sub_needs_semi = false;
          transpilar_bloque(src_ptr, f_mem, false, NULL, NULL, &sub_needs_semi, false);
          fclose(f_mem);

          strcat(funciones_extraidas, buf_func);
          strcat(funciones_extraidas, "\n");
          *needs_semicolon = false;
        }
        else {
          if (strcmp(func_name, "main") == 0) {
            fprintf(destino, "\n// --- PROTOTIPOS DE LAMBDAS EXTRAÍDAS ---\n%s\n", prototipos_lambdas);
            fprintf(destino, "\n// --- METODOS DE COMPORTAMIENTO EXTRAIDOS ---\n%s", funciones_extraidas);
            fprintf(destino, "// --- CONSTRUCTORES DE INICIALIZACION ---\n%s\n", constructores_inicializadores);
            funciones_extraidas[0] = '\0';
            constructores_inicializadores[0] = '\0';
            prototipos_lambdas[0] = '\0';
          }
          fprintf(destino, "%s %s(%s) {\n", ret_type, func_name, argumentos);
          *needs_semicolon = false;
          transpilar_bloque(src_ptr, destino, false, NULL, NULL, needs_semicolon, false);
        }
        break;
      }

      case TOKEN_IDENTIFIER: {
        // 1. Validaciones previas de inicialización de miembros en PKG
        if (in_pkg) {
          char var_member[128]; strcpy(var_member, token.lexeme);
          const char *look = *src_ptr;
          while (*look == ' ' || *look == '\t') look++;

          if (*look == '=') {
            get_next_token(src_ptr);
            Token val_tok = get_next_token(src_ptr);
            char buffer_init[256];
            sprintf(buffer_init, "    instancia.%s = %s;\n", var_member, val_tok.lexeme);
            strcat(temp_constructor, buffer_init);
            fprintf(destino, "%s", var_member);
            *needs_semicolon = true;
            ignorar_hasta_nueva_linea_pkg = true;
            break;
          }
        }

        // 2. Validación de instanciación de paquetes
        if (es_paquete_registrado(token.lexeme)) {
          char pkg_type[128]; strcpy(pkg_type, token.lexeme);
          Token obj_tok = get_next_token(src_ptr);
          fprintf(destino, "%s %s = init_%s()", pkg_type, obj_tok.lexeme, pkg_type);
          *needs_semicolon = true; break;
        }

        // 3. DINÁMICO (Sin Hardcoding): Invocación de función guardada en un 'any'
        if (es_comodin_registrado(token.lexeme)) {
          const char *look_call = *src_ptr;
          while (*look_call == ' ' || *look_call == '\t') look_call++;

          if (*look_call == '(') {
            // Se castea dinámicamente solo si está registrado en la tabla de símbolos comodín
            fprintf(destino, "((void(*)())%s.func_val) ", token.lexeme);
            *needs_semicolon = true;
            break;
          }
        }

        // 4. Palabra reservada Stop del sistema
        if (strcmp(token.lexeme, "Stop") == 0) {
          const char *look = *src_ptr;
          while (*look == ' ' || *look == '\t') look++;
          if (*look == '(') {
            const char *look2 = look + 1;
            while (*look2 == ' ' || *look2 == '\t') look2++;
            if (strncmp(look2, "system", 6) == 0) {
              const char *look3 = look2 + 6;
              while (*look3 == ' ' || *look3 == '\t') look3++;
              if (*look3 == ')') {
                *src_ptr = look3 + 1; fprintf(destino, "exit(0)"); *needs_semicolon = true; break;
              }
            }
          }
        }
        // Si vemos "double sum[] =" o "int sum[] ="
        if ((strcmp(token.lexeme, "double") == 0 || strcmp(token.lexeme, "int") == 0 || strcmp(token.lexeme, "char") == 0) && strncmp(tipo_retorno_actual, "[]", 2) == 0) {
          char tipo_base[32];
          strcpy(tipo_base, strcmp(token.lexeme, "double") == 0 ? "double": (strcmp(token.lexeme, "int") == 0 ? "int": "char"));

          Token name_tok = get_next_token(src_ptr); // Nombre del arreglo (ej: "sum")
          strcpy(nombre_arreglo_actual, name_tok.lexeme);

          Token bracket_tok = get_next_token(src_ptr); // El "["
          Token close_bracket = get_next_token(src_ptr); // El "]"
          Token assign_tok = get_next_token(src_ptr); // El "="
          Token open_brace = get_next_token(src_ptr); // El "{"

          // Contamos cuántos elementos hay dentro de las llaves para el malloc
          const char *look_elements = *src_ptr;
          conteo_elementos_arreglo = 1; // Mínimo uno si no está vacío
          Token elem = get_next_token(&look_elements);
          while (elem.type != TOKEN_RBRACE && elem.type != TOKEN_EOF) {
            if (elem.type == TOKEN_COMMA) conteo_elementos_arreglo++;
            elem = get_next_token(&look_elements);
          }

          // Escribimos la inicialización dinámica en el Heap en C
          fprintf(destino, "%s* %s = malloc(%d * sizeof(%s));\n", tipo_base, nombre_arreglo_actual, conteo_elementos_arreglo, tipo_base);

          // Ahora inicializamos cada índice posicional mapeando el literal
          int indice = 0;
          Token val_elem = get_next_token(src_ptr);
          while (val_elem.type != TOKEN_RBRACE && val_elem.type != TOKEN_EOF) {
            if (val_elem.type != TOKEN_COMMA && val_elem.type != TOKEN_NEWLINE) {
              fprintf(destino, "    %s[%d] = %s;\n", nombre_arreglo_actual, indice++, val_elem.lexeme);
            }
            val_elem = get_next_token(src_ptr);
          }

          *needs_semicolon = false;
          continue;
        }
        // Identificador estándar o función global normal (printf, funciones de usuario, etc.)
        fprintf(destino, "%s ", token.lexeme);
        *needs_semicolon = true;
        break;
      }

      case TOKEN_CHAR_LITERAL:
      if (asignando_a_any) {
        fprintf(destino, "(Axoany_Struct){ .type = TYPE_CHAR, .c_val = %s } ", token.lexeme);
      } else {
        fprintf(destino, "%s ", token.lexeme);
      }
      *needs_semicolon = true;
      break;

      case TOKEN_ASSIGN: {
        fprintf(destino, "= ");
        *needs_semicolon = false;

        const char *look_lambda = *src_ptr;
        while (*look_lambda == ' ' || *look_lambda == '\t') look_lambda++;

        // Si lo que sigue es una Lambda Dinámica asignada a la variable
        if (*look_lambda == '(') {
          static int lambda_counter = 0;
          char lambda_name[64]; sprintf(lambda_name, "__axo_lambda_%d", ++lambda_counter);
          char buf_lambda[4096] = ""; char ret_type[64] = "void";

          Token l_tok = get_next_token(src_ptr);
          while (l_tok.type != TOKEN_LBRACE && l_tok.type != TOKEN_EOF) {
            if (l_tok.type == TOKEN_COLON) {
              l_tok = get_next_token(src_ptr);
              if (strcmp(l_tok.lexeme, "[]any") == 0) strcpy(ret_type, "Axoarray_any");
              else if (strcmp(l_tok.lexeme, "int") == 0) strcpy(ret_type, "int");
              else if (strcmp(l_tok.lexeme, "dec") == 0) strcpy(ret_type, "double");
            }
            l_tok = get_next_token(src_ptr);
          }

          FILE *f_lam = fmemopen(buf_lambda, sizeof(buf_lambda), "w");
          fprintf(f_lam, "%s %s() {\n    ", ret_type, lambda_name);

          bool sub_needs_semi = false;
          transpilar_bloque(src_ptr, f_lam, false, NULL, NULL, &sub_needs_semi, false);
          fclose(f_lam);

          strcat(funciones_extraidas, buf_lambda); strcat(funciones_extraidas, "\n");

          char prototipo[128]; sprintf(prototipo, "%s %s();\n", ret_type, lambda_name);
          strcat(prototipos_lambdas, prototipo);

          fprintf(destino, "(Axoany_Struct){ .type = TYPE_FUNC, .func_val = &__axo_lambda_%d }", lambda_counter);
          asignando_a_any = false; // Se resolvió el comodín
          *needs_semicolon = true;
        }
        break;
      }

      case TOKEN_REF_ARROW: fprintf(destino, "&"); *needs_semicolon = false; break;

      case TOKEN_NUMBER: {
        size_t len = strlen(token.lexeme);
        bool es_imaginario = (len > 0 && token.lexeme[len - 1] == 'i');
        char lexeme_limpio[256]; strcpy(lexeme_limpio, token.lexeme);
        if (es_imaginario) lexeme_limpio[len - 1] = '\0';

        if (asignando_a_any) {
          if (es_imaginario) {
            if (strlen(lexeme_limpio) == 0 || strcmp(lexeme_limpio, "1") == 0)
            fprintf(destino, "(Axoany_Struct){ .type = TYPE_COMPLEX, .cmplx_val = _Complex_I } ");
            else
            fprintf(destino, "(Axoany_Struct){ .type = TYPE_COMPLEX, .cmplx_val = %s * _Complex_I } ", lexeme_limpio);
          } else {
            if (strchr(lexeme_limpio, '.') != NULL)
            fprintf(destino, "(Axoany_Struct){ .type = TYPE_DEC, .d_val = %s } ", lexeme_limpio);
            else
            fprintf(destino, "(Axoany_Struct){ .type = TYPE_INT, .i_val = %s } ", lexeme_limpio);
          }
        } else {
          // Expresión numérica común fuera de comodín
          if (es_imaginario) {
            if (strlen(lexeme_limpio) == 0) fprintf(destino, "_Complex_I ");
            else fprintf(destino, "%s * _Complex_I ", lexeme_limpio);
          } else {
            fprintf(destino, "%s ", token.lexeme);
          }
        }
        *needs_semicolon = true;
        break;
      }

      case TOKEN_STRING:
      if (asignando_a_any) {
        fprintf(destino, "(Axoany_Struct){ .type = TYPE_STRING, .s_val = \"%s\" } ", token.lexeme);
      } else {
        fprintf(destino, "\"%s\" ", token.lexeme);
      }
      *needs_semicolon = true;
      break;

      case TOKEN_LARRAY: fprintf(destino, "{ "); *needs_semicolon = false; break;
      case TOKEN_RARRAY: fprintf(destino, " }"); *needs_semicolon = true; break;

      case TOKEN_SEMICOLON:
      fprintf(destino, "; ");
      asignando_a_any = false; // Finaliza la expresión comodín
      *needs_semicolon = false;
      break;

      case TOKEN_OP_MULT:
      // Si estamos asignando a un comodín y aparece una operación, la mantenemos dentro del contexto
      fprintf(destino, "* "); *needs_semicolon = false;
      break;
      case TOKEN_OP_DIV: fprintf(destino, "/ "); *needs_semicolon = false; break;
      case TOKEN_OP_SQRT: fprintf(destino, "sqrt"); *needs_semicolon = false; break;
      case TOKEN_OP_EXP: fprintf(destino, "exp"); *needs_semicolon = false; break;
      case TOKEN_OP_XOR: fprintf(destino, "^ "); *needs_semicolon = false; break;
      case TOKEN_OP_AND: fprintf(destino, "&& "); *needs_semicolon = false; break;
      case TOKEN_OP_OR: fprintf(destino, "|| "); *needs_semicolon = false; break;
      case TOKEN_OP_NOT: fprintf(destino, "! "); *needs_semicolon = false; break;
      case TOKEN_OP_GE: fprintf(destino, ">= "); *needs_semicolon = false; break;
      case TOKEN_OP_LE: fprintf(destino, "<= "); *needs_semicolon = false; break;
      case TOKEN_OP_NOTEQUAL: fprintf(destino, "!= "); *needs_semicolon = false; break;

      case TOKEN_LBRACE: fprintf(destino, "{ "); *needs_semicolon = false; break;
      case TOKEN_RBRACE: {
        if (in_pkg) {
          fprintf(destino, "} %s;\n\n", current_pkg_name);
          strcat(temp_constructor, "    return instancia;\n}\n\n");
          strcat(constructores_inicializadores, temp_constructor);
        } else {
          fprintf(destino, "}\n");
        }
        asignando_a_any = false;
        *needs_semicolon = false;
        return;
      }
      // ==========================================
      // ¡AQUÍ AÑADES ESTE NUEVO CASE PARA EL RETURN!
      // ==========================================
      default:
        // Si el identificador que cayó en default resulta ser la palabra "return"
        if (strcmp(token.lexeme, "return") == 0) {
          if (strncmp(tipo_retorno_actual, "[]", 2) == 0) {
            Token var_ret = get_next_token(src_ptr); // Lee el nombre del arreglo (ej: "sum")
            
            char struct_type[64];
            if (strcmp(tipo_retorno_actual, "[]int") == 0) strcpy(struct_type, "Axoarray_int");
            else if (strcmp(tipo_retorno_actual, "[]dec") == 0) strcpy(struct_type, "Axoarray_dec");
            else if (strcmp(tipo_retorno_actual, "[]char") == 0) strcpy(struct_type, "Axoarray_char");
            else strcpy(struct_type, "Axoarray_any");
            
            fprintf(destino, "return (%s){ .data = %s, .length = %d }", struct_type, var_ret.lexeme, conteo_elementos_arreglo);
            *needs_semicolon = true;
            continue;
          }
        }

        // Comportamiento por defecto para cualquier otro token desconocido
        fprintf(destino, "%s ", token.lexeme);
        if (strcmp(token.lexeme, ")") == 0 || strcmp(token.lexeme, "]") == 0) *needs_semicolon = true;
        break;
    }
    token = get_next_token(src_ptr);
  }
}

void transpilar(const char *codigo_axolang, FILE *f_salida) {
  const char *ptr = codigo_axolang;
  bool needs_semicolon = false;
  transpilar_bloque(&ptr, f_salida, false, NULL, NULL, &needs_semicolon, false);
}

// =====================================================================
// FLUJO PRINCIPAL DE COMPILACIÓN NATIVA
// =====================================================================
int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Uso: %s <archivo.axo> <salida.c>\n", argv[0]);
    return 1;
  }

  FILE* origen = fopen(argv[1], "r");
  if (!origen) {
    printf("Error: No se pudo abrir el archivo fuente '%s'\n", argv[1]);
    return 1;
  }

  fseek(origen, 0, SEEK_END); long tamano = ftell(origen); fseek(origen, 0, SEEK_SET);

  char* codigo_axolang = malloc(tamano + 1);
  if (!codigo_axolang) {
    printf("Error: Memoria insuficiente.\n"); fclose(origen); return 1;
  }

  size_t leidos = fread(codigo_axolang, 1, tamano, origen);
  codigo_axolang[leidos] = '\0'; fclose(origen);

  FILE* salida_c = fopen(argv[2], "w");
  if (!salida_c) {
    printf("Error: No se pudo crear el archivo de salida '%s'\n", argv[2]); free(codigo_axolang); return 1;
  }

  fprintf(salida_c, "// --- C23 AUTO-GENERATED CODE FROM AXOLANG ---\n");
  fprintf(salida_c, "#include <complex.h>\n#include <math.h>\n#include <tgmath.h>\n");
  fprintf(salida_c, "#include <string.h>\n#include <stdbool.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n");

  fprintf(salida_c, "typedef enum { TYPE_INT, TYPE_DEC, TYPE_COMPLEX, TYPE_CHAR, TYPE_STRING, TYPE_FUNC, TYPE_PKG } AxoType;\n");
  fprintf(salida_c, "typedef struct {\n    AxoType type;\n    union {\n        int i_val;\n        double d_val;\n        double _Complex cmplx_val;\n        char c_val;\n        char* s_val;\n        void (*func_val)();\n        void* pkg_val;\n    };\n} Axoany_Struct;\n\n");

  fprintf(salida_c, "typedef struct { int* data; size_t length; } Axoarray_int;\n");
  fprintf(salida_c, "typedef struct { double* data; size_t length; } Axoarray_dec;\n");
  fprintf(salida_c, "typedef struct { char* data; size_t length; } Axoarray_char;\n");
  fprintf(salida_c, "typedef struct { Axoany_Struct* data; size_t length; } Axoarray_any;\n\n");

  transpilar(codigo_axolang, salida_c);
  fclose(salida_c); free(codigo_axolang);

  printf("[Axolang] Código intermedio '%s' generado con éxito.\n", argv[2]);
  printf("[Axolang] Compilando binario nativo en estándar C23...\n");

  char comando[512];
  sprintf(comando, "gcc %s -o programa_ejecutable -std=c23 -lm", argv[2]);
  int resultado_compilacion = system(comando);

  if (resultado_compilacion == 0) {
    printf("[Axolang] ¡Compilación exitosa! Ejecutable creado como './programa_ejecutable'\n");
  } else {
    printf("[Axolang] Error durante la compilación nativa de C.\n");
  }

  return resultado_compilacion;
}