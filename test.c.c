// --- C23 AUTO-GENERATED CODE FROM AXOLANG ---
#include <complex.h>
#include <math.h>
#include <tgmath.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <stddef.h>
;
int num[] = {0,3,5,7,3};
char saludo[] = "hola";
double complex miComplejo = 2 + 2.1i;
int edad = 25;
double pi = 3.1416;
bool activo = true;
auto varauto = 3;
int* miCopia = &edad;
typedef struct {

  char letra;
  double gd;
  char* saludar   ()       {
    return "Hola desde variable";
  }
  double* suma   (double a, double b)       {
    // Al transpilearse, interceptamos esto para usar malloc dinámico;
    double sum[] = {0,0};
    sum[0] = a + b ;
    sum[1] = a * b;
    return sum;
  }
  void prueba   (){
  scanf("%s", &saludo);
  }
} algo;

void hola2   (){
  printf("Hola desde funcion globql\n");
}
int main   ()     {
  algo p1;
  p1.letra = 'a';
  printf("%s\n", saludo);
  printf("%s\n", p1.saludar());
  printf("%c\n", p1.letra);
  for (int i = 0; i < 5; i++){
    printf("%d\n", num[i]);
  }
  hola2();
  printf("%.1f %.1fi\n", creal(miComplejo), cimag(miComplejo));
  printf("%p\n", miCopia);
  // CAPTURA INTELIGENTE DEL ARREGLO RETORNADO;
  auto resultado = p1.suma(2.5, pi);
  printf("Resultado 1: %f\n", resultado.data[0]);
  printf("Resultado 2: %f\n", resultado.data[1]);
  printf("Elementos devueltos: %zu\n", resultado.length);
  return 0;
;
}