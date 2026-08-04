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
	unsigned _BitInt(6) exponente;
	unsigned _BitInt(12) entero;
	unsigned _BitInt(13) fraccion;
} __attribute__((packed)) PaxoNum32;

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



//Funciones de zig

//Funciones numericas
//8 bits
PaxoNum8 add_num8(PaxoNum8 a, PaxoNum8 b) {
	const uint8_t sesgo = 1;
	int8_t val_a = ((int8_t)a.entero << 1) | a.fraccion;
	if (a.signo) { val_a = -val_a; }
	int8_t val_b = ((int8_t)b.entero << 1) | a.fraccion;
	if (b.signo) { val_b = -val_b; }

	int8_t exp_a = (int8_t)a.exponente - sesgo;
	int8_t exp_b = (int8_t)b.exponente - sesgo;
	int8_t exp;
	
	if (exp_a > exp_b) {
		uint8_t diff = exp_a - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_b *= 10;}
		exp = exp_a;
	} else if (exp_b > exp_a) {
		uint8_t diff = exp_b - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_a *= 10;}
		exp = exp_b;}

	int8_t suma = val_a + val_b;
	PaxoNum8 result;
	result.signo = (suma < 0)? 1 : 0;

	while (suma >= (1 << 5)) {
    suma /= 10;
    exp++;}

	result.exponente = (unsigned _BitInt(2))exp + sesgo;
	result.entero = (unsigned _BitInt(4))(suma >> 1) & 0xf;
	result.fraccion = (unsigned _BitInt(1))suma & 0x1;
	return result;}

PaxoNum8 sub_num8(PaxoNum8 a, PaxoNum8 b) {
	const uint8_t sesgo = 1;
	int8_t val_a = ((int8_t)a.entero << 1) | a.fraccion;
	if (a.signo) { val_a = -val_a; }
	int8_t val_b = ((int8_t)b.entero << 1) | a.fraccion;
	if (b.signo) { val_b = -val_b; }

	int8_t exp_a = (int8_t)a.exponente - sesgo;
	int8_t exp_b = (int8_t)b.exponente - sesgo;
	int8_t exp;
	
	if (exp_a > exp_b) {
		uint8_t diff = exp_a - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_b *= 10;}
		exp = exp_a;
	} else if (exp_b > exp_a) {
		uint8_t diff = exp_b - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_a *= 10;}
		exp = exp_b;}

	int8_t resta = val_a - val_b;
	PaxoNum8 result;
	result.signo = (resta < 0)? 1 : 0;

	while (resta >= (1 << 6)) {
    resta /= 10;
    exp++;}

	result.exponente = (unsigned _BitInt(2))exp + sesgo;
	result.entero = (unsigned _BitInt(4))(resta >> 1) & 0xf;
	result.fraccion = (unsigned _BitInt(1))resta & 0x1;
	return result;}

//16 bits
PaxoNum16 add_num16(PaxoNum16 a, PaxoNum16 b) {
	const uint8_t sesgo = 7;
	int16_t val_a = ((int16_t)a.entero << 6) | a.fraccion;
	if (a.signo) { val_a = -val_a; }
	int16_t val_b = ((int16_t)b.entero << 6) | a.fraccion;
	if (b.signo) { val_b = -val_b; }

	int16_t exp_a = (int16_t)a.exponente - sesgo;
	int16_t exp_b = (int16_t)b.exponente - sesgo;
	int16_t exp;
	
	if (exp_a > exp_b) {
		uint8_t diff = exp_a - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_b *= 10;}
		exp = exp_a;
	} else if (exp_b > exp_a) {
		uint8_t diff = exp_b - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_a *= 10;}
		exp = exp_b;}

	int16_t suma = val_a + val_b;
	PaxoNum16 result;
	result.signo = (suma < 0)? 1 : 0;

	while (suma >= (1 << 11)) {
    suma /= 10;
    exp++;}

	result.exponente = (unsigned _BitInt(4))exp + sesgo;
	result.entero = (unsigned _BitInt(5))(suma >> 6) & 0x1f;
	result.fraccion = (unsigned _BitInt(6))suma & 0x3f;
	return result;}

PaxoNum16 sub_num16(PaxoNum16 a, PaxoNum16 b) {
	const uint8_t sesgo = 7;
	int16_t val_a = ((int16_t)a.entero << 6) | a.fraccion;
	if (a.signo) { val_a = -val_a; }
	int16_t val_b = ((int16_t)b.entero << 6) | a.fraccion;
	if (b.signo) { val_b = -val_b; }

	int16_t exp_a = (int16_t)a.exponente - sesgo;
	int16_t exp_b = (int16_t)b.exponente - sesgo;
	int16_t exp;
	
	if (exp_a > exp_b) {
		uint8_t diff = exp_a - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_b *= 10;}
		exp = exp_a;
	} else if (exp_b > exp_a) {
		uint8_t diff = exp_b - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_a *= 10;}
		exp = exp_b;}

	int16_t resta = val_a - val_b;
	PaxoNum16 result;
	result.signo = (resta < 0)? 1 : 0;

	while (resta >= (1 << 11)) {
    resta /= 10;
    exp++;}

	result.exponente = (unsigned _BitInt(4))exp + sesgo;
	result.entero = (unsigned _BitInt(5))(resta >> 6) & 0x1f;
	result.fraccion = (unsigned _BitInt(6))resta & 0x3f;
	return result;}

//32 bits
PaxoNum32 add_num32(PaxoNum32 a, PaxoNum32 b) {
	const uint8_t sesgo = 31;
	int32_t val_a = ((int32_t)a.entero << 13) | a.fraccion;
	if (a.signo) { val_a = -val_a; }
	int32_t val_b = ((int32_t)b.entero << 13) | a.fraccion;
	if (b.signo) { val_b = -val_b; }

	int8_t exp_a = (int8_t)a.exponente - sesgo;
	int8_t exp_b = (int8_t)b.exponente - sesgo;
	int8_t exp;
	
	if (exp_a > exp_b) {
		uint8_t diff = exp_a - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_b *= 10;}
		exp = exp_a;
	} else if (exp_b > exp_a) {
		uint8_t diff = exp_b - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_a *= 10;}
		exp = exp_b;}

	int32_t suma = val_a + val_b;
	PaxoNum32 result;
	result.signo = (suma < 0)? 1 : 0;

	while (suma >= (1 << 25)) {
    suma /= 10;
    exp++;}

	result.exponente = (unsigned _BitInt(6))exp + sesgo;
	result.entero = (unsigned _BitInt(12))(suma >> 13) & 0xfff;
	result.fraccion = (unsigned _BitInt(13))suma & 0x1fff;
	return result;}

PaxoNum32 sub_num32(PaxoNum32 a, PaxoNum32 b) {
	const uint8_t sesgo = 31;
	int32_t val_a = ((int32_t)a.entero << 13) | a.fraccion;
	if (a.signo) { val_a = -val_a; }
	int32_t val_b = ((int32_t)b.entero << 13) | a.fraccion;
	if (b.signo) { val_b = -val_b; }

	int8_t exp_a = (int8_t)a.exponente - sesgo;
	int8_t exp_b = (int8_t)b.exponente - sesgo;
	int8_t exp;
	
	if (exp_a > exp_b) {
		uint8_t diff = exp_a - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_b *= 10;}
		exp = exp_a;
	} else if (exp_b > exp_a) {
		uint8_t diff = exp_b - exp_b;
		for (int8_t i = 0; i < diff; i++) {
			val_a *= 10;}
		exp = exp_b;}

	int32_t resta = val_a - val_b;
	PaxoNum32 result;
	result.signo = (resta < 0)? 1 : 0;

	while (resta >= (1 << 25)) {
    resta /= 10;
    exp++;}

	result.exponente = (unsigned _BitInt(6))exp + sesgo;
	result.entero = (unsigned _BitInt(12))(resta >> 13) & 0xfff;
	result.fraccion = (unsigned _BitInt(13))resta & 0x1fff;
	return result;}