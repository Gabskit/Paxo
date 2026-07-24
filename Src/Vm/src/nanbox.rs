/// Representación de los tipos de datos BIV según tamaño de variable en Paxo
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PaxoValue {
    /// 16 bits: valor extendido.
    Xs(u16),
    /// 32 bits: valor standard.
    S(u32),
    /// 64 bits: valor medio.
    M(u64),
    /// 128 bits: valor largo.
    L(u128)}

impl PaxoValue {
    /// Bit
    // Empaquetado
    pub fn pack_bit_xs(bit: bool) -> Self {
        let exp_mask: u16 = 0b11111 << 10; // 5 bits exponente en 1
        let tag: u16 = 0b00 << 8; // Payload Tag 00 para Bit
        let payload: u16 = bit as u16;
        PaxoValue::Xs(exp_mask | tag | payload )}

    pub fn pack_bit_s(bit: bool) -> Self {
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b00 << 17; // Payload Tag 00 para Bit
        let payload: u32 = bit as u32;
        PaxoValue::S(exp_mask | tag | payload )}

    pub fn pack_bit_m(bit: bool) -> Self {
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b00 << 47; // Payload Tag 00 para Bit
        let payload: u64 = bit as u64;
        PaxoValue::M(exp_mask | tag | payload )}

    pub fn pack_bit_l(bit: bool) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b00 << 107;                    // Payload Tag 00 para Bit
        let payload: u128 = bit as u128;
        PaxoValue::L(exp_mask | tag | payload )}

    // Desempaquetado
    pub fn unpack_bit_xs(val: u16) -> bool {
        (val & 1) != 0}

    pub fn unpack_bit_s(val: u32) -> bool {
        (val & 1) != 0}

    pub fn unpack_bit_m(val: u64) -> bool {
        (val & 1) != 0}

    pub fn unpack_bit_l(val: u128) -> bool {
        (val & 1) != 0}

    /// Caracter
    // Empaquetado
    pub fn pack_char_xs(c: char) -> Self {
        let exp_mask: u16 = 0b11111 << 10; // 5 bits exponente en 1
        let tag: u16 = 0b01 << 8;           // Payload Tag 01 para Char
        let payload: u16 = c as u16;
        PaxoValue::Xs(exp_mask | tag | payload)}

    pub fn pack_char_s(c: char) -> Self {
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b01 << 17;              // Payload Tag 01 para Char
        let payload: u32 = c as u32;
        PaxoValue::S(exp_mask | tag | payload)}

    pub fn pack_char_m(c: char) -> Self {
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b01 << 47;                 // Payload Tag 01 para Char
        let payload: u64 = c as u64;
        PaxoValue::M(exp_mask | tag | payload)}

    pub fn pack_char_l(c: char) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b01 << 107;                    // Payload Tag 01 para Char
        let payload: u128 = c as u128;
        PaxoValue::L(exp_mask | tag | payload)}

    // Desempaquetado 
    pub fn unpack_char_xs(val: u16) -> char {
        (val as u8) as char}

    pub fn unpack_char_s(val: u32) -> char {
        (val as u16 as u8) as char}

    pub fn unpack_char_m(val: u64) -> char {
        (val as u32 as u8) as char}

    pub fn unpack_char_l(val: u128) -> char {
        (val as u32 as u8) as char}

    /// Vectores 2d 
    // Empaquetado 
    pub fn pack_vec2d_xs(x: i8, y: i8) -> Self {
        let exp_mask: u16 = 0b11111 << 10; // 5 bits exponente en 1
        let tag: u16 = 0b10 << 8;           // Payload Tag 10 para Vec2D
        let x_bits = ((x as u8 as u16) & 0x0F) << 4;
        let y_bits = (y as u8 as u16) & 0x0F;
        PaxoValue::Xs(exp_mask | tag | x_bits | y_bits)}

    pub fn pack_vec2d_s(x: i8, y: i8, is_polar: bool) -> Self {
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b10 << 17;              // Payload Tag 10 para Vec2D
        let polar_bit: u32 = if is_polar { 1 << 16 } else { 0 }; // *i bit
        let x_bits = ((x as u8 as u32) & 0xFF) << 8;
        let y_bits = (y as u8 as u32) & 0xFF;

        PaxoValue::S(exp_mask | tag | polar_bit | x_bits | y_bits)}

    pub fn pack_vec2d_m(x: i32, y: i32, is_polar: bool) -> Self {
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b10 << 47;                 // Payload Tag 10 para Vec2D
        let polar_bit: u64 = if is_polar { 1 << 46 } else { 0 }; // *i bit
        let x_bits = ((x as i32 as u64) & 0x7FFFFF) << 23;
        let y_bits = (y as i32 as u64) & 0x7FFFFF;

        PaxoValue::M(exp_mask | tag | polar_bit | x_bits | y_bits)}

    pub fn pack_vec2d_l(x: i64, y: i64, is_polar: bool) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b10 << 107;                    // Payload Tag 10 para Vec2D
        let polar_bit: u128 = if is_polar { 1 << 106 } else { 0 }; // *i bit
        let x_bits = ((x as i64 as u128) & 0x1FFFFFFFFFFFFF) << 53;
        let y_bits = (y as i64 as u128) & 0x1FFFFFFFFFFFFF;

        PaxoValue::L(exp_mask | tag | polar_bit | x_bits | y_bits)}

    // Desempaquetado
    pub fn unpack_vec2d_xs(val: u16) -> (i8, i8) {
        let x = ((val >> 4) & 0x0F) as u8 as i8;
        let y = (val & 0x0F) as u8 as i8;
        (x, y)}

    pub fn unpack_vec2d_s(val: u32) -> (i8, i8, bool) {
        let is_polar = (val & (1 << 16)) != 0;
        let x = ((val >> 8) & 0xFF) as u8 as i8;
        let y = (val & 0xFF) as u8 as i8;
        (x, y, is_polar)}

    pub fn unpack_vec2d_m(val: u64) -> (i16, i16, bool) {
        let is_polar = (val & (1 << 46)) != 0;
        let x = ((((val >> 23) & 0x7FFFFF) as i64) << 41) >> 41;
        let y = ((((val & 0x7FFFFF) as i64) << 41) >> 41);
        (x as i16, y as i16, is_polar) }

    pub fn unpack_vec2d_l(val: u128) -> (i32, i32, bool) {
        let is_polar = (val & (1 << 106)) != 0;
        let x = ((((val >> 53) & 0x1FFFFFFFFFFFFF) as i128) << 75) >> 75;
        let y = ((((val & 0x1FFFFFFFFFFFFF) as i128) << 75) >> 75);
        (x as i32, y as i32, is_polar)}

    /// Vector 4d 
    // Empaquetado
    pub fn pack_vec4d_xs(x: i8, y: i8, z: i8, w: i8) -> Self {
        let exp_mask: u16 = 0b11111 << 10; // 5 bits exponente en 1
        let tag: u16 = 0b11 << 8;           // Payload Tag 11 para Vec4D
        let x_bits = ((x as u8 & 0x0F) as u16) << 6;
        let y_bits = ((y as u8 & 0x0F) as u16) << 4;
        let z_bits = ((z as u8 & 0x0F) as u16) << 2;
        let w_bits = (w as u8 & 0x0F) as u16;
        PaxoValue::Xs(exp_mask | tag | x_bits | y_bits | z_bits | w_bits)}
    
    pub fn pack_vec4d_s(x: i8, y: i8, z: i8, w: i8, is_polar: bool) -> Self {
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b11 << 17;              // Payload Tag 11 para Vec4D
        let polar_bit: u32 = if is_polar { 1 << 16 } else { 0 }; // *i bit
        let x_bits = ((x as u8 as u32) & 0xFF) << 12;
        let y_bits = ((y as u8 as u32) & 0xFF) << 8;
        let z_bits = ((z as u8 as u32) & 0xFF) << 4;
        let w_bits = (w as u8 as u32) & 0xFF;
        PaxoValue::S(exp_mask | tag | polar_bit | x_bits | y_bits | z_bits | w_bits)}

    pub fn pack_vec4d_m(x: i16, y: i16, z: i16, w: i16, is_polar: bool) -> Self {
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b11 << 47;                 // Payload Tag 11 para Vec4D
        let polar_bit: u64 = if is_polar { 1 << 46 } else { 0 }; // *i bit
        let x_bits = ((x as i32 as u64) & 0x7FFFFF) << 33;
        let y_bits = (y as i32 as u64) & 0x7FFFFF << 22;
        let z_bits = (z as i32 as u64) & 0x7FFFFF << 11;
        let w_bits = (w as i32 as u64) & 0x7FFFFF;
        PaxoValue::M(exp_mask | tag | polar_bit | x_bits | y_bits | z_bits | w_bits)}
    
    pub fn pack_vec4d_l(x: i32, y: i32, z: i32, w: i32, is_polar: bool) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b11 << 107;                    // Payload Tag 11 para Vec4D
        let polar_bit: u128 = if is_polar { 1 << 106 } else { 0 }; // *i bit
        let x_bits = ((x as i64 as u128) & 0x1FFFFFFFFFFFFF) << 78;
        let y_bits = ((y as i64 as u128) & 0x1FFFFFFFFFFFFF) << 52;
        let z_bits = ((z as i64 as u128) & 0x1FFFFFFFFFFFFF) << 26;
        let w_bits = (w as i64 as u128) & 0x1FFFFFFFFFFFFF;
        PaxoValue::L(exp_mask | tag | polar_bit | x_bits | y_bits | z_bits | w_bits)}

    // Desempaquetado
    pub fn unpack_vec4d_xs(val: u16) -> (i8, i8, i8, i8) {
        let x = ((val >> 6) & 0x0F) as u8 as i8;
        let y = ((val >> 4) & 0x0F) as u8 as i8;
        let z = ((val >> 2) & 0x0F) as u8 as i8;
        let w = (val & 0x0F) as u8 as i8;
        (x, y, z, w)}
    
    pub fn unpack_vec4d_s(val: u32) -> (i8, i8, i8, i8, bool) {
        let is_polar = (val & (1 << 16)) != 0;
        let x = ((val >> 12) & 0xFF) as u8 as i8;
        let y = ((val >> 8) & 0xFF) as u8 as i8;
        let z = ((val >> 4) & 0xFF) as u8 as i8;
        let w = (val & 0xFF) as u8 as i8;
        (x, y, z, w, is_polar)}

    pub fn unpack_vec4d_m(val: u64) -> (i32, i32, i32, i32, bool) {
        let is_polar = (val & (1 << 46)) != 0;
        let x = ((val >> 33) & 0x7FFFFF) as u64 as i32;
        let y = ((val >> 22) & 0x7FFFFF) as i64 as i32;
        let z = ((val >> 11) & 0x7FFFFF) as i64 as i32;
        let w = (val & 0x7FFFFF) as i64 as i32;
        (x, y, z, w, is_polar)}
    
    pub fn unpack_vec4d_l(val: u128) -> (i64, i64, i64, i64, bool) {
        let is_polar = (val & (1 << 106)) != 0;
        let x = ((val >> 78) & 0x1FFFFFFFFFFFFF) as u128 as i64;
        let y = ((val >> 52) & 0x1FFFFFFFFFFFFF) as u128 as i64;
        let z = ((val >> 26) & 0x1FFFFFFFFFFFFF) as u128 as i64;
        let w = (val & 0x1FFFFFFFFFFFFF) as u128 as i64;
        (x, y, z, w, is_polar)}

    /// Trit
    // Empaquetado
    pub fn pack_trit_xs(val: u8) -> Self {
        let tag_set: u16 = 0b1 << 15; // Signo 1 para segundo tag set
        let exp_mask: u16 = 0b11111 << 10; // 5 bits exponente en 1
        let tag: u16 = 0b00 << 8;           // Payload Tag 00 para Trit
        let val_bits = val as u16;
        PaxoValue::Xs(tag_set | exp_mask | tag | val_bits)}

    pub fn pack_trit_s(val: u8) -> Self {
        let tag_set: u32 = 0b1 << 31; // Signo 1 para segundo tag set
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b00 << 17;              // Payload Tag 00 para Trit
        let val_bits = val as u32;
        PaxoValue::S(tag_set | exp_mask | tag | val_bits)}

    pub fn pack_trit_m(val: u8) -> Self {
        let tag_set: u64 = 0b1 << 63; // Signo 1 para segundo tag set
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b00 << 47;                 // Payload Tag 00 para Trit
        let val_bits = val as u64;
        PaxoValue::M(tag_set | exp_mask | tag | val_bits)}
    
    pub fn pack_trit_l(val: u8) -> Self {
        let tag_set: u128 = 0b1 << 127; // Signo 1 para segundo tag set
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b00 << 107;                    // Payload Tag 00 para Trit
        let val_bits = val as u128;
        PaxoValue::L(tag_set | exp_mask | tag | val_bits)}

    // Desempaquetado
    pub fn unpack_trit_xs(val: u16) -> u8 {
        val as u8}

    pub fn unpack_trit_s(val: u32) -> u8 {
        val as u8}

    pub fn unpack_trit_m(val: u64) -> u8 {
        val as u8}

    pub fn unpack_trit_l(val: u128) -> u8 {
        val as u8}

    /// Numero complejo
    // Empaquetado
    pub fn pack_complex_xs(real: f32, imag: f32) -> Self {
        let tag_set: u16 = 0b1 << 15;        // Signo 1 para segundo tag set
        let exp_mask: u16 = 0b11111 << 10; // 5 bits exponente en 1
        let tag: u16 = 0b01 << 8;           // Payload Tag 01 para Complex

        let re_bits = ((real as i8) as u16 & 0x0F) << 4;
        let im_bits = (imag as i8) as u16 & 0x0F;

        PaxoValue::Xs(tag_set | exp_mask | tag | re_bits | im_bits)}
    
    pub fn pack_complex_s(real: f32, imag: f32) -> Self {
        let tag_set: u32 = 0b1 << 31;         // Signo 1 para segundo tag set
        let exp_mask: u32 = 0x7FF << 20;    // 11 bits exponente en 1
        let tag: u32 = 0b01 << 18;          // Payload Tag 01 para Complex

        let re_bits = ((real as i16) as u32 & 0xFF) << 8;
        let im_bits = (imag as i16) as u32 & 0xFF;

        PaxoValue::S(tag_set | exp_mask | tag | re_bits | im_bits)}

    pub fn pack_complex_m(real: f32, imag: f32) -> Self {
        let tag_set: u64 = 0b1 << 63;         // Signo 1 para segundo tag set
        let exp_mask: u64 = 0x1FFF << 50;   // 13 bits exponente en 1
        let tag: u64 = 0b01 << 48;          // Payload Tag 01 para Complex

        let mask_24 = (1u64 << 24) - 1;     // 0xFFFFFF
        let re_bits = ((real as i32 as u64) & mask_24) << 24;
        let im_bits = (imag as i32 as u64) & mask_24;

        PaxoValue::M(tag_set | exp_mask | tag | re_bits | im_bits)}
    
    pub fn pack_complex_l(real: f64, imag: f64) -> Self {
        let tag_set: u128 = 0b1 << 127;       // Signo 1 para segundo tag set
        let exp_mask: u128 = 0x1FFFF << 110; // 17 bits exponente en 1
        let tag: u128 = 0b01 << 108;        // Payload Tag 01 para Complex

        let mask_54: u128 = (1u128 << 54) - 1;
        let re_bits = ((real as i64 as u128) & mask_54) << 54;
        let im_bits = (imag as i64 as u128) & mask_54;

        PaxoValue::L(tag_set | exp_mask | tag | re_bits | im_bits)}
    
    // Desempaquetado 
    pub fn unpack_complex_xs(val: u16) -> (f32, f32) {
        let x = ((((val >> 4) & 0x0F) << 4) >> 4) as u8 as f32;
        let y = (((val & 0x0F) << 4) >> 4) as u8 as f32;
        (x, y)}

    pub fn unpack_complex_s(val: u32) -> (f32, f32) {
        let x = ((val >> 8) & 0xFF) as u8 as f32;
        let y = (val & 0xFF) as u8 as f32;
        (x, y)}

    pub fn unpack_complex_m(val: u64) -> (f32, f32) {
        let x = ((((val >> 24) & 0x7FFFFF) << 8) >> 8) as u8 as f32;
        let y = (((val & 0x7FFFFF) << 8) >> 8) as u8 as f32;
        (x, y)}

    pub fn unpack_complex_l(val: u128) -> (f64, f64) {
        let x = ((((val >> 54) & 0x1FFFFFFFFFFFFF) << 10) >> 10) as u64 as f64;
        let y = (((val & 0x1FFFFFFFFFFFFF) << 10) >> 10) as u64 as f64;
        (x, y)}
    
    /// Tiempo
    // Empaquetado
    pub fn pack_time_s(h: u8, m: u8, s: u8) -> Self {
        let tag_set: u32 = 0b1 << 31;         // Bit 31 = 1
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b10<< 17;              // Payload Tag 10 para Tiempo
        let h_bits = (h as u32) << 12;
        let m_bits = (m as u32) << 6;
        let s_bits = s as u32;
        PaxoValue::S(tag_set | exp_mask | tag | h_bits | m_bits | s_bits)}

    pub fn pack_time_m(d: u8, h: u8, m: u8, s: u8, ms: u16, ns: u16) -> Self {
        let tag_set: u64 = 0b1 << 63;         // Bit 63 = 1
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b10 << 47;                 // Payload Tag 10 para Tiempo
        let d_bits = (d as u64) << 37;
        let h_bits = (h as u64) << 32;
        let m_bits = (m as u64) << 26;
        let s_bits = (s as u64) << 20;
        let ms_bits = (ms as u64) << 10;
        let ns_bits = ns as u64;
        PaxoValue::M(tag_set | exp_mask | tag | d_bits | h_bits | m_bits | s_bits | ms_bits | ns_bits)}

    pub fn pack_time_l(d: u8, h: u8, m: u8, s: u8, ms: u16, ns: u16) -> Self {
        let tag_set: u128 = 0b1 << 127;       // Bit 127 = 1
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b10 << 107;        // Payload Tag 10 para Tiempo
        let d_bits = (d as u128) << 37;
        let h_bits = (h as u128) << 32;
        let m_bits = (m as u128) << 26;
        let s_bits = (s as u128) << 20;
        let ms_bits = (ms as u128) << 10;
        let ns_bits = ns as u128;
        PaxoValue::L(tag_set | exp_mask | tag | d_bits | h_bits | m_bits | s_bits | ms_bits | ns_bits)}

    // Desempaquetado 
    pub fn unpack_time_s(val: u32) -> (u8, u8, u8) {
        let h = (val >> 12) as u8;
        let m = (val >> 6) as u8;
        let s = val as u8;
        (h, m, s)}

    pub fn unpack_time_m(val: u64) -> (u8, u8, u8, u8, u16, u16) {
        let d = (val >> 37) as u8;
        let h = (val >> 32) as u8;
        let m = (val >> 26) as u8;
        let s = (val >> 20) as u8;
        let ms = (val >> 10) as u16;
        let ns = val as u16;
        (d, h, m, s, ms, ns)}

    pub fn unpack_time_l(val: u128) -> (u8, u8, u8, u8, u16, u16) {
        let d = (val >> 37) as u8;
        let h = (val >> 32) as u8;
        let m = (val >> 26) as u8;
        let s = (val >> 20) as u8;
        let ms = (val >> 10) as u16;
        let ns = val as u16;
        (d, h, m, s, ms, ns)}

    /// Puntero
    // Empaquetado
    pub fn pack_pointer_l(ptr: u64) -> Self {
        let tag_set: u128 = 0b1 << 127;       // Signo 1 para segudo tag set
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b11 << 107; // Payload Tag 11 para Puntero
        PaxoValue::L(tag_set | exp_mask | tag | (ptr as u128))}
    
    // Desempaquetado
    pub fn unpack_pointer_l(val: u128) -> u64 {
        val as u64}

    /// Interpretación IEEE 754 como Base 20 (Binary Integer Vigesimal)
    /// Extrae componentes IEEE 754 e interpreta exponente como base 20
    
    // Xs: 1 signo | 5 exponente | 10 mantisa
    pub fn ieee754_to_base20_xs(val: u16) -> f64 {
        let signo = ((val >> 15) & 1) as f64;
        let exp_raw = ((val >> 10) & 0x1F) as i32;
        let mant_bits = (val & 0x3FF) as f64;
        
        let signo_mult = if signo == 0.0 { 1.0 } else { -1.0 };
        let mantisa = 1.0 + (mant_bits / 1024.0); // 2^10 = 1024
        
        signo_mult * mantisa * (20.0_f64.powi(exp_raw - 15))
    }

    // S: 1 signo | 8 exponente | 23 mantisa
    pub fn ieee754_to_base20_s(val: u32) -> f64 {
        let signo = ((val >> 31) & 1) as f64;
        let exp_raw = ((val >> 23) & 0xFF) as i32;
        let mant_bits = (val & 0x7FFFFF) as f64;
        
        let signo_mult = if signo == 0.0 { 1.0 } else { -1.0 };
        let mantisa = 1.0 + (mant_bits / 8388608.0); // 2^23
        
        signo_mult * mantisa * (20.0_f64.powi(exp_raw - 127))
    }

    // M: 1 signo | 11 exponente | 52 mantisa
    pub fn ieee754_to_base20_m(val: u64) -> f64 {
        let signo = ((val >> 63) & 1) as f64;
        let exp_raw = ((val >> 52) & 0x7FF) as i32;
        let mant_bits = (val & 0xFFFFFFFFFFFFF) as f64;
        
        let signo_mult = if signo == 0.0 { 1.0 } else { -1.0 };
        let mantisa = 1.0 + (mant_bits / 4503599627370496.0); // 2^52
        
        signo_mult * mantisa * (20.0_f64.powi(exp_raw - 1023))
    }

    // L: 1 signo | 15 exponente | 112 mantisa
    pub fn ieee754_to_base20_l(val: u128) -> f64 {
        let signo = ((val >> 127) & 1) as f64;
        let exp_raw = ((val >> 112) & 0x7FFF) as i32;
        let mant_bits = (val & ((1u128 << 112) - 1)) as f64;
        
        let signo_mult = if signo == 0.0 { 1.0 } else { -1.0 };
        let mantisa = 1.0 + (mant_bits / 5192296858534827628530496329220096.0); // 2^112
        
        signo_mult * mantisa * (20.0_f64.powi(exp_raw - 16383))
    }

    /// Convertir valor decimal a IEEE 754 interpretado como base 20
    pub fn base20_to_ieee754_xs(valor: f64) -> u16 {
        if valor == 0.0 {
            return 0;
        }
        
        let signo = if valor < 0.0 { 1u16 } else { 0u16 };
        let abs_val = valor.abs();
        
        let exp_f = abs_val.log(20.0).floor() as i32 + 15;
        let exp = (exp_f.max(0).min(31)) as u16;
        
        let mantisa_f = abs_val / (20.0_f64.powi(exp_f - 15));
        let mant_bits = ((mantisa_f - 1.0) * 1024.0) as u16 & 0x3FF;
        
        (signo << 15) | (exp << 10) | mant_bits
    }

    pub fn base20_to_ieee754_s(valor: f64) -> u32 {
        if valor == 0.0 {
            return 0;
        }
        
        let signo = if valor < 0.0 { 1u32 } else { 0u32 };
        let abs_val = valor.abs();
        
        let exp_f = abs_val.log(20.0).floor() as i32 + 127;
        let exp = (exp_f.max(0).min(255)) as u32;
        
        let mantisa_f = abs_val / (20.0_f64.powi(exp_f - 127));
        let mant_bits = ((mantisa_f - 1.0) * 8388608.0) as u32 & 0x7FFFFF;
        
        (signo << 31) | (exp << 23) | mant_bits
    }

    pub fn base20_to_ieee754_m(valor: f64) -> u64 {
        if valor == 0.0 {
            return 0;
        }
        
        let signo = if valor < 0.0 { 1u64 } else { 0u64 };
        let abs_val = valor.abs();
        
        let exp_f = abs_val.log(20.0).floor() as i32 + 1023;
        let exp = (exp_f.max(0).min(2047)) as u64;
        
        let mantisa_f = abs_val / (20.0_f64.powi(exp_f - 1023));
        let mant_bits = ((mantisa_f - 1.0) * 4503599627370496.0) as u64 & 0xFFFFFFFFFFFFF;
        
        (signo << 63) | (exp << 52) | mant_bits
    }

    pub fn base20_to_ieee754_l(valor: f64) -> u128 {
        if valor == 0.0 {
            return 0;
        }
        
        let signo = if valor < 0.0 { 1u128 } else { 0u128 };
        let abs_val = valor.abs();
        
        let exp_f = abs_val.log(20.0).floor() as i32 + 16383;
        let exp = (exp_f.max(0).min(32767)) as u128;
        
        let mantisa_f = abs_val / (20.0_f64.powi(exp_f - 16383));
        let mant_bits = ((mantisa_f - 1.0) * 5192296858534827628530496329220096.0) as u128 & ((1u128 << 112) - 1);
        
        (signo << 127) | (exp << 112) | mant_bits
    }
}

#[cfg(test)]
mod tests {
    use super::PaxoValue;

    #[test]
    fn vec2d_xs_roundtrip() {
        let packed = PaxoValue::pack_vec2d_xs(10, 5);
        let (x, y) = match packed {
            PaxoValue::Xs(bits) => PaxoValue::unpack_vec2d_xs(bits),
            other => panic!("unexpected variant: {:?}", other),};

        assert_eq!((x, y), (10, 5));}

    #[test]
    fn vec2d_s_roundtrip() {
        let packed = PaxoValue::pack_vec2d_s(10, -5, false);
        let (x, y, polar) = match packed {
            PaxoValue::S(bits) => PaxoValue::unpack_vec2d_s(bits),
            other => panic!("unexpected variant: {:?}", other),};

        assert_eq!((x, y, polar), (10, -5, false));}}