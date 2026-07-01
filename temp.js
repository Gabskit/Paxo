const HEADER_C = `
#include <stdint.h>
#include <complex.h>

// === Nivel 1: xsany (Unión pura de 16 bits / 2 Bytes) ===
typedef union {
    int8_t    axo_xxsint;   // Entero ultra-corto con signo
    uint8_t   axo_xxsintu;  // Entero ultra-corto sin signo
    int16_t   axo_xsint;    // Entero corto con signo
    uint16_t  axo_xsintu;   // Entero corto sin signo
    _Float16  axo_xsflt;
} axo_xsany_t;

// === Nivel 2: sany (Unión pura de 32 bits / 4 Bytes) ===
typedef union {
    // Hereda/incluye la capacidad de los tipos de 16 bits y añade:
    int32_t   axo_sint;     // Entero estándar de 32 bits
    uint32_t  axo_sintu;    // Entero de 32 bits sin signo
    float     axo_sflt;     // Decimal corto (punto flotante de precisión simple)
} axo_sany_t;

// === Nivel 3: any / lany (Unión pura de 64 bits / 8 Bytes) ===
typedef union {
    // Escala para soportar enteros y decimales masivos de alta precisión:
    int64_t   axo_int;      // Entero largo de 64 bits
    uint64_t  axo_intu;     // Entero largo de 64 bits sin signo
    double    axo_flt;      // Decimal estándar de doble precisión
    float complex axo_scom; // Número complejo corto (2x float de 32 bits)
} axo_any_t;

`;
