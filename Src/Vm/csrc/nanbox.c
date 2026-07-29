#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t format_tag; // Identificador del tipo de variante (xxs, xs, tf, px_s, etc.)
    union {
        uint8_t xxs;
        uint8_t xxsm3;
        uint16_t xs;
        uint16_t xsb;
        uint32_t tf; // 19-bit field stored in a 32-bit container
        uint32_t s;
        uint32_t sst;
        uint64_t m;
        uint64_t mst;
        unsigned __int128 l; // 128-bit value (using compiler __int128)
        unsigned __int128 lst;
    } data;
} PaxoValue;


#define TF_BITS 19u
#define TF_MASK ((uint32_t)((1u << TF_BITS) - 1u)) /* 0x7FFFF */

static inline uint32_t tf_get(const PaxoValue *p) {
    return p->data.tf & TF_MASK;
}

static inline void tf_set(PaxoValue *p, uint32_t v) {
    p->data.tf = (p->data.tf & ~TF_MASK) | (v & TF_MASK);
}

/* Pack 19-bit value into 3 bytes little-endian */
static inline void pack_tf_le(uint32_t tf, uint8_t out[3]) {
    tf &= TF_MASK;
    out[0] = tf & 0xFF;
    out[1] = (tf >> 8) & 0xFF;
    out[2] = (tf >> 16) & 0x07; /* only 3 bits here (8+8+3=19) */
}

static inline uint32_t unpack_tf_le(const uint8_t in[3]) {
    return (uint32_t)in[0] | ((uint32_t)in[1] << 8) | (((uint32_t)in[2] & 0x07) << 16);
}

/* Interpret 19-bit value as signed (two's complement) */
static inline int32_t tf_to_signed(uint32_t tf) {
    tf &= TF_MASK;
    if (tf & (1u << (TF_BITS - 1)))
        return (int32_t)(tf | ~TF_MASK); /* sign-extend */
    else
        return (int32_t)tf;
}


