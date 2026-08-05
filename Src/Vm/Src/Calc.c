#include <stdint.h>

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
	const uint8_t sesgo = 0;
	int16_t val_a = a.fraccion + (a.entero * 4);
	val_a = (a.signo >= 1) ? -val_a : val_a;
	int16_t val_b = b.fraccion + (b.entero * 4);
	val_b = (b.signo >= 1) ? -val_b : val_b;
	
	int8_t exp_a = a.exponente - sesgo;
	int8_t exp_b = b.exponente - sesgo;
	int8_t exp;

	uint8_t diff;
	if (exp_a > exp_b) {
		diff = exp_a - exp_b;
		for (int i = 0; i < diff; i++) {
			val_b /= 10;
			exp_b++;}
		
		exp = exp_b;
	} else if (exp_b > exp_a) {
		diff = exp_b - exp_a;
		for (int i = 0; i < diff; i++) {
			val_a /= 10;
			exp_a++;}
		
		exp = exp_a;
	} else {
		exp = exp_a;}

	int16_t suma = val_a + val_b;
	uint16_t abs_suma = (suma < 0) ? -suma : suma;
	
	PaxoNum8 result;
	result.signo = (suma < 0)? 1 : 0;
	
	while (abs_suma > (1 << 6)) {
    abs_suma /= 10;
    exp++;}

	if (exp < 0) exp = 0;
	if (exp > 1) exp = 1;

	result.exponente = (unsigned _BitInt(1))exp + sesgo;
	result.entero = (unsigned _BitInt(4))(abs_suma >> 2) & 0xf;
	result.fraccion = (unsigned _BitInt(2))abs_suma & 0x3;
	return result;}

PaxoNum8 sub_num8(PaxoNum8 a, PaxoNum8 b) {
	const uint8_t sesgo = 0;
	int16_t val_a = a.fraccion + (a.entero * 4);
	val_a = (a.signo >= 1) ? -val_a : val_a;
	int16_t val_b = b.fraccion + (b.entero * 4);
	val_b = (b.signo >= 1) ? -val_b : val_b;
	
	int8_t exp_a = a.exponente - sesgo;
	int8_t exp_b = b.exponente - sesgo;
	int8_t exp;

	uint8_t diff;
	if (exp_a > exp_b) {
		diff = exp_a - exp_b;
		for (int i = 0; i < diff; i++) {
			val_b /= 10;
			exp_b++;}
		
		exp = exp_b;
	} else if (exp_b > exp_a) {
		diff = exp_b - exp_a;
		for (int i = 0; i < diff; i++) {
			val_a /= 10;
			exp_a++;}
		
		exp = exp_a;
	} else {
		exp = exp_a;}

	int16_t suma = val_a - val_b;
	uint16_t abs_suma = (suma < 0) ? -suma : suma;
	
	PaxoNum8 result;
	result.signo = (suma < 0)? 1 : 0;
	
	while (abs_suma > (1 << 6)) {
    abs_suma /= 10;
    exp++;}

	if (exp < 0) exp = 0;
	if (exp > 1) exp = 1;

	result.exponente = (unsigned _BitInt(1))exp + sesgo;
	result.entero = (unsigned _BitInt(4))(abs_suma >> 2) & 0xf;
	result.fraccion = (unsigned _BitInt(2))abs_suma & 0x3;
	return result;}

PaxoNum8 mul_num8(PaxoNum8 a, PaxoNum8 b) {
	const uint8_t sesgo = 0;
	int32_t val_a = a.fraccion + (a.entero * 4);
  int32_t val_b = b.fraccion + (b.entero * 4);

	uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
	int32_t mult = (val_a * val_b) >> 2;
	int16_t exp_final = (int16_t)a.exponente + (int16_t)b.exponente - sesgo;

	while (mult > (1 << 6)) {
    mult /= 10;
    exp_final++;}

	if (exp_final < 0) exp_final = 0;
  if (exp_final > 1) exp_final = 1;

	PaxoNum16 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(1))exp_final;
  result.entero = (unsigned _BitInt(4))(mult >> 2) & 0xf;
	result.fraccion = (unsigned _BitInt(2))mult & 0x3;
	return result;}

PaxoNum8 div_num8(PaxoNum8 a, PaxoNum8 b) {
	const uint8_t sesgo = 0;
	int32_t val_a = a.fraccion + (a.entero * 4);
  int32_t val_b = b.fraccion + (b.entero * 4);

	if (val_b == 0) {
    PaxoNum8 error = {0, 0, 0, 0};
    return error;
	}

	uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
	int32_t mult = (val_a << 2) / val_b; 

	int16_t exp_final = (int16_t)a.exponente - (int16_t)b.exponente + sesgo;

	while (mult > (1 << 6)) {
    mult /= 10;
    exp_final++;}

	if (exp_final < 0) exp_final = 0;
  if (exp_final > 1) exp_final = 1;

  PaxoNum16 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(1))exp_final;
  result.entero = (unsigned _BitInt(4))(mult >> 6) & 0xf;
  result.fraccion = (unsigned _BitInt(2))mult & 0x3;
  return result;}

//16 bits
PaxoNum16 add_num16(PaxoNum16 a, PaxoNum16 b) {
	const uint8_t sesgo = 7;
	int32_t val_a = a.fraccion + (a.entero * 64);
	val_a = (a.signo >= 1) ? -val_a : val_a;
	int32_t val_b = b.fraccion + (b.entero * 64);
	val_b = (b.signo >= 1) ? -val_b : val_b;
	
	int8_t exp_a = a.exponente - sesgo;
	int8_t exp_b = b.exponente - sesgo;
	int8_t exp;

	uint8_t diff;
	if (exp_a > exp_b) {
		diff = exp_a - exp_b;
		for (int i = 0; i < diff; i++) {
			val_b /= 10;
			exp_b++;}
		
		exp = exp_b;
	} else if (exp_b > exp_a) {
		diff = exp_b - exp_a;
		for (int i = 0; i < diff; i++) {
			val_a /= 10;
			exp_a++;}
		
		exp = exp_a;
	} else {
		exp = exp_a;}

	int32_t suma = val_a + val_b;
	uint32_t abs_suma = (suma < 0) ? -suma : suma;
	
	PaxoNum16 result;
	result.signo = (suma < 0)? 1 : 0;
	
	while (abs_suma > (1 << 11)) {
    abs_suma /= 10;
    exp++;}

	if (exp < 0) exp = 0;
	if (exp > 15) exp = 15;

	result.exponente = (unsigned _BitInt(4))exp + sesgo;
	result.entero = (unsigned _BitInt(5))(abs_suma >> 6) & 0x1f;
	result.fraccion = (unsigned _BitInt(6))abs_suma & 0x3f;
	return result;}

PaxoNum16 sub_num16(PaxoNum16 a, PaxoNum16 b) {
	const uint8_t sesgo = 7;
	int32_t val_a = a.fraccion + (a.entero * 64);
	val_a = (a.signo >= 1) ? -val_a : val_a;
	int32_t val_b = b.fraccion + (b.entero * 64);
	val_b = (b.signo >= 1) ? -val_b : val_b;
	
	int8_t exp_a = a.exponente - sesgo;
	int8_t exp_b = b.exponente - sesgo;
	int8_t exp;

	uint8_t diff;
	if (exp_a > exp_b) {
		diff = exp_a - exp_b;
		for (int i = 0; i < diff; i++) {
			val_b /= 10;
			exp_b++;}
		
		exp = exp_b;
	} else if (exp_b > exp_a) {
		diff = exp_b - exp_a;
		for (int i = 0; i < diff; i++) {
			val_a /= 10;
			exp_a++;}
		
		exp = exp_a;
	} else {
		exp = exp_a;}

	int32_t suma = val_a - val_b;
	uint32_t abs_suma = (suma < 0) ? -suma : suma;
	
	PaxoNum16 result;
	result.signo = (suma < 0)? 1 : 0;
	
	while (abs_suma > (1 << 11)) {
    abs_suma /= 10;
    exp++;}

	if (exp < 0) exp = 0;
	if (exp > 15) exp = 15;


	result.exponente = (unsigned _BitInt(4))exp + sesgo;
	result.entero = (unsigned _BitInt(5))(abs_suma >> 6) & 0x1f;
	result.fraccion = (unsigned _BitInt(6))abs_suma & 0x3f;
	return result;}

PaxoNum16 mul_num16(PaxoNum16 a, PaxoNum16 b) {
	const uint8_t sesgo = 7;
	int32_t val_a = a.fraccion + (a.entero * 64);
  int32_t val_b = b.fraccion + (b.entero * 64);

	uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
	int32_t mult = (val_a * val_b) >> 6;
	int16_t exp_final = (int16_t)a.exponente + (int16_t)b.exponente - sesgo;

	while (mult > (1 << 11)) {
    mult /= 10;
    exp_final++;}

	if (exp_final < 0) exp_final = 0;
  if (exp_final > 15) exp_final = 15;

	PaxoNum16 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(4))exp_final;
  result.entero = (unsigned _BitInt(5))(mult >> 6) & 0x1f;
	result.fraccion = (unsigned _BitInt(6))mult & 0x3f;
	return result;}

PaxoNum16 div_num16(PaxoNum16 a, PaxoNum16 b) {
	const uint8_t sesgo = 7;
	int32_t val_a = a.fraccion + (a.entero * 64);
  int32_t val_b = b.fraccion + (b.entero * 64);

	if (val_b == 0) {
    PaxoNum16 error = {0, 0, 0, 0};
    return error;
	}

	uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
	int32_t mult = (val_a << 6) / val_b; 

	int16_t exp_final = (int16_t)a.exponente - (int16_t)b.exponente + sesgo;

	while (mult > (1 << 11)) {
    mult /= 10;
    exp_final++;}

	if (exp_final < 0) exp_final = 0;
  if (exp_final > 15) exp_final = 15;

  PaxoNum16 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(4))exp_final;
  result.entero = (unsigned _BitInt(5))(mult >> 6) & 0x1f;
  result.fraccion = (unsigned _BitInt(6))mult & 0x3f;
  return result;}

//32 bits
PaxoNum32 add_num32(PaxoNum32 a, PaxoNum32 b) {
	const uint8_t sesgo = 31;
	int64_t val_a = a.fraccion + (a.entero * 8192);
	val_a = (a.signo >= 1) ? -val_a : val_a;
	int64_t val_b = b.fraccion + (b.entero * 8192);
	val_b = (b.signo >= 1) ? -val_b : val_b;
	
	int16_t exp_a = a.exponente - sesgo;
	int16_t exp_b = b.exponente - sesgo;
	int16_t exp;

	uint8_t diff;
	if (exp_a > exp_b) {
		diff = exp_a - exp_b;
		for (int i = 0; i < diff; i++) {
			val_b /= 10;
			exp_b++;}
		
		exp = exp_b;
	} else if (exp_b > exp_a) {
		diff = exp_b - exp_a;
		for (int i = 0; i < diff; i++) {
			val_a /= 10;
			exp_a++;}
		
		exp = exp_a;
	} else {
		exp = exp_a;}

	int64_t suma = val_a + val_b;
	uint64_t abs_suma = (suma < 0) ? -suma : suma;
	
	PaxoNum32 result;
	result.signo = (suma < 0)? 1 : 0;
	
	while (abs_suma > (1 << 25)) {
    abs_suma /= 10;
    exp++;}

	if (exp < 0) exp = 0;
	if (exp > 63) exp = 63;

	result.exponente = (unsigned _BitInt(6))exp + sesgo;
	result.entero = (unsigned _BitInt(12))(abs_suma >> 13) & 0xfff;
	result.fraccion = (unsigned _BitInt(13))abs_suma & 0x1fff;
	return result;}

PaxoNum32 sub_num32(PaxoNum32 a, PaxoNum32 b) {
	const uint8_t sesgo = 31;
	int64_t val_a = a.fraccion + (a.entero * 8192);
	val_a = (a.signo >= 1) ? -val_a : val_a;
	int64_t val_b = b.fraccion + (b.entero * 8192);
	val_b = (b.signo >= 1) ? -val_b : val_b;
	
	int16_t exp_a = a.exponente - sesgo;
	int16_t exp_b = b.exponente - sesgo;
	int16_t exp;

	uint8_t diff;
	if (exp_a > exp_b) {
		diff = exp_a - exp_b;
		for (int i = 0; i < diff; i++) {
			val_b /= 10;
			exp_b++;}
		
		exp = exp_b;
	} else if (exp_b > exp_a) {
		diff = exp_b - exp_a;
		for (int i = 0; i < diff; i++) {
			val_a /= 10;
			exp_a++;}
		
		exp = exp_a;
	} else {
		exp = exp_a;}

	int64_t suma = val_a - val_b;
	uint64_t abs_suma = (suma < 0) ? -suma : suma;
	
	PaxoNum32 result;
	result.signo = (suma < 0)? 1 : 0;
	
	while (abs_suma > (1 << 25)) {
    abs_suma /= 10;
    exp++;}

	if (exp < 0) exp = 0;
	if (exp > 63) exp = 63;

	result.exponente = (unsigned _BitInt(6))exp + sesgo;
	result.entero = (unsigned _BitInt(12))(abs_suma >> 13) & 0xfff;
	result.fraccion = (unsigned _BitInt(13))abs_suma & 0x1fff;
	return result;}

PaxoNum32 mul_num32(PaxoNum32 a, PaxoNum32 b) {
	const uint8_t sesgo = 31;
	int32_t val_a = a.fraccion + (a.entero * 8192);
  int32_t val_b = b.fraccion + (b.entero * 8192);

	uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
	int32_t mult = (val_a * val_b) >> 13;
	int16_t exp_final = (int16_t)a.exponente + (int16_t)b.exponente - sesgo;

	while (mult > (1 << 25)) {
    mult /= 10;
    exp_final++;}

	if (exp_final < 0) exp_final = 0;
  if (exp_final > 63) exp_final = 63;

	PaxoNum16 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(6))exp_final;
  result.entero = (unsigned _BitInt(12))(mult >> 13) & 0xfff;
	result.fraccion = (unsigned _BitInt(13))mult & 0x1fff;
	return result;}

PaxoNum32 div_num32(PaxoNum32 a, PaxoNum32 b) {
	const uint8_t sesgo = 31;
	int32_t val_a = a.fraccion + (a.entero * 8192);
  int32_t val_b = b.fraccion + (b.entero * 8192);

	if (val_b == 0) {
    PaxoNum16 error = {0, 0, 0, 0};
    return error;
	}

	uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
	int32_t mult = (val_a << 13) / val_b; 

	int16_t exp_final = (int16_t)a.exponente - (int16_t)b.exponente + sesgo;

	while (mult > (1 << 25)) {
    mult /= 10;
    exp_final++;}

	if (exp_final < 0) exp_final = 0;
  if (exp_final > 63) exp_final = 63;

  PaxoNum16 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(6))exp_final;
  result.entero = (unsigned _BitInt(12))(mult >> 6) & 0xfff;
  result.fraccion = (unsigned _BitInt(13))mult & 0x1fff;
  return result;}