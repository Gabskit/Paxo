/* Código C23 generado automáticamente por Axolang (axoc) */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

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



    void hola2() {
    printf("Hola desde funcion globql\n");
    int main() {
    algo p1;
    p1.saludar = _algo_saludar;
    p1.suma = _algo_suma;
    p1.letra = 'a';
    printf("%s\n", saludo);
    printf("%s\n", p1.saludar());
    printf("%c\n", p1.letra);
    printf("%s\n", (char*)variableComodin);
    for (int i = 0; i < 5; i++){
    printf("%d\n", num[i]);
