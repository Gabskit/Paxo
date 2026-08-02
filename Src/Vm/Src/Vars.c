# include <stdio.h>

typedef struct {
    unsigned _BitInt(1) signo;
    unsigned _BitInt(1) exponente;
    unsigned _BitInt(4) entero;
    unsigned _BitInt(2) fraccion;
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