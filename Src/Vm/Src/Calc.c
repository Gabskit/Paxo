#include <stdint.h>

typedef struct {
	unsigned _BitInt(1) signo;
	unsigned _BitInt(2) exponente;
	unsigned _BitInt(4) entero;
	unsigned _BitInt(1) fraccion;
} __attribute__((packed)) PaxoNum8;

typedef struct {
	unsigned _BitInt(1) signo;
	unsigned _BitInt(4) exponente;
	unsigned _BitInt(5) entero;
	unsigned _BitInt(6) fraccion;
} __attribute__((packed)) PaxoNum16;

typedef struct {
	unsigned _BitInt(1) signo;
	unsigned _BitInt(7) exponente;
	unsigned _BitInt(11) entero;
	unsigned _BitInt(13) fraccion;
} __attribute__((packed)) PaxoNum32;

typedef struct {
	unsigned _BitInt(1) signo;
	unsigned _BitInt(11) exponente;
	unsigned _BitInt(25) entero;
	unsigned _BitInt(27) fraccion;
} __attribute__((packed)) PaxoNum64;

typedef struct {
	PaxoNum8 real;
	PaxoNum8 imaginario;
} __attribute__((packed)) PaxoCom8;

typedef struct {
	PaxoNum16 real;
	PaxoNum16 imaginario;
} __attribute__((packed)) PaxoCom16;

typedef struct {
	PaxoNum32 real;
	PaxoNum32 imaginario;
} __attribute__((packed)) PaxoCom32;

typedef struct {
	PaxoNum64 real;
	PaxoNum64 imaginario;
} __attribute__((packed)) PaxoCom64;

typedef struct {
	unsigned _BitInt(2) valor;
} __attribute__((packed)) PaxoBool;

typedef struct {
	uint8_t valor;
} __attribute__((packed)) PaxoChar8;

typedef struct {
	uint16_t valor;
} __attribute__((packed)) PaxoChar16;

typedef struct {
	uint32_t valor;
} __attribute__((packed)) PaxoChar32;

//Tabla LUT
const uint32_t LUT_exp[] = {
	1,//0
	10,//1
	100,//2
	1000,//3
	10000,//4
	100000,//5
	1000000,//6
	10000000,//7
	100000000,//8
	1000000000,//9
	10000000000,//10
	100000000000,//11
};

//Funciones de zig

//Funciones numericas
PaxoNum8 add_num8(PaxoNum8 a, PaxoNum8 b) {
	uint8_t sesgo = 1;
	
	int8_t int_zone_a = (a.signo ? -1 : 1) * (int8_t)a.entero;
	int8_t int_zone_b = (b.signo ? -1 : 1) * (int8_t)b.entero;
	int8_t int_r = (int_zone_a & 0xf) + (int_zone_b & 0xf);
	bool r_sign = (bool)(int_r & 0x80) >> 7;
	
}