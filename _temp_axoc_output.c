/* Código C23 generado automáticamente por Axolang (axoc) */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <complex.h>

/* Definiciones Base de Arreglos de Axolang */
typedef struct {
    int* data;
    size_t length;
} AxoArray_int;
typedef struct {
    double* data;
    size_t length;
} AxoArray_dec;


/* Definición de Estructuras Axolang */
typedef struct {
    char letra;
    double gd;
    char* (*saludar)();
    int (*suma)(int a, int b);
} algo;


/* Métodos Extraídos de Paquetes Axolang */
char* _algo_saludar() {
    return "Hola desde variable";
}

int _algo_suma(int a, int b) {
    // Al transpilearse, interceptamos esto para usar malloc dinámico;
    int sum[] = {0,0}
    sum[0] = a + b;
    sum[1] = a + a + b;
    return 0;
}



/* Variables Globales de Axolang */
int num[] = {0,3,5,7,3};
char saludo[] = "hola";
double complex miComplejo = 2.1 * I;
int edad = 25;
double pi = 3.1416;
bool activo = true;
auto miCopia = &edad;
void* variableComodin = "adios";
hola2();
printf("%.1f %.1fi\n", creal(miComplejo), cimag(miComplejo));
printf("%p\n", miCopia);
// CAPTURA INTELIGENTE DEL ARREGLO RETORNADO;
auto resultado = p1.suma(2, 4);
printf("Resultado 1: %d\n", resultado.data[0]);
printf("Resultado 2: %d\n", resultado.data[1]);
printf("Elementos devueltos: %zu\n", resultado.length);
return 0;


    void hola2() {
    void hola2() {
    }
    int main() {
    algo p1;
    p1.saludar = _algo_saludar;
    p1.suma = _algo_suma;
    algo p1;
    p1.saludar = _algo_saludar;
    p1.suma = _algo_suma;
    algo p1;
    p1.saludar = _algo_saludar;
    p1.suma = _algo_suma;
    algo p1;
    p1.saludar = _algo_saludar;
    p1.suma = _algo_suma;
    algo p1;
    p1.saludar = _algo_saludar;
    p1.suma = _algo_suma;
    algo p1;
    p1.saludar = _algo_saludar;
    p1.suma = _algo_suma;
    }
    }
