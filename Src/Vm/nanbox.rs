/// Representación de los tipos de datos BIV según tamaño de variable en Paxo
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PaxoValue {
    /// Valor numérico legacy usado por el VM inicial.
    Normal(u64),
    /// 8 bits: entero pequeño / payload base.
    Xxs(u8),
    /// 16 bits: valor extendido.
    Xs(u16),
    /// 32 bits: valor standard.
    S(u32),
    /// 64 bits: valor medio.
    M(u64),
    /// 128 bits: valor largo.
    L(u128),
    /// 256 bits: valor extra largo.
    Xl([u64; 4]),
    /// Bit / trit / crit: representación mínima de valores boolean-like.
    Bit(u8),
    Trit(u8),
    Crit(u8),
    /// Caracteres codificados por ancho.
    Utf8(u8),
    Utf16(u16),
    Utf32(u32),
    Utf64(u64),
    /// Vectores 2D y 4D.
    Vec2D { x: i64, y: i64, polar: bool, width: u8 },
    Vec4D { x: i64, y: i64, z: i64, w: i64, width: u8 },
    /// Número complejo.
    Complex { re: i64, im: i64, width: u8 },
    /// IP y red.
    Ipv4(u32),
    Ipv6([u64; 2]),
    /// Slice / nano-time / lista embebida.
    Slice { ptr: u64, len: u64 },
    NanoTime { sec: u64, nsec: u64 },
    EmbeddedList(u64),
    /// Rango reservado para uso futuro.
    Future(u128),
}

impl PaxoValue {
    // Vectores 2d 
    // Empaquetado 
    pub fn pack_vec2d_xs(x: i8, y: i8) -> Self {
        let exp_mask: u16 = 0b11111 << 10; // 5 bits exponente en 1
        let tag: u16 = 0b10 << 8;           // Payload Tag 10 para Vec2D
        let x_bits = ((x as u8 & 0x0F) as u16) << 4;
        let y_bits = (y as u8 & 0x0F) as u16;
        PaxoValue::Xs(exp_mask | tag | x_bits | y_bits)
    }

    pub fn pack_vec2d_xl(x: i128, y: i128, is_polar: bool) -> Self {
        let exp_mask: u64 = 0x1FFFFFF; // 25 bits exponent en 1
        let tag: u64 = 0b0010 << 25;
        let polar_bit: u64 = if is_polar { 1 << 31 } else { 0 };
        let meta = exp_mask | tag | polar_bit;

        let mut words = [0u64; 4];
        let mask = (1u128 << 112) - 1;
        let y_bits = (y as u128) & mask;
        let x_bits = (x as u128) & mask;

        for i in 0..112u32 {
            let bit = ((y_bits >> i) & 1) as u64;
            words[(i / 64) as usize] |= bit << (i % 64);
        }

        for i in 0..112u32 {
            let bit = ((x_bits >> i) & 1) as u64;
            words[((112 + i) / 64) as usize] |= bit << ((112 + i) % 64);
        }

        words[3] |= (meta as u64) << 32;

        PaxoValue::Xl(words)
    }

    pub fn pack_vec2d_s(x: i16, y: i16, is_polar: bool) -> Self {
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b010 << 17;              // Payload Tag 010 para Vec2D
        let polar_bit: u32 = if is_polar { 1 << 16 } else { 0 }; // *i bit
        let x_bits = (x as u16 as u32) << 8;
        let y_bits = y as u16 as u32;

        PaxoValue::S(exp_mask | tag | polar_bit | x_bits | y_bits)
    }

    pub fn pack_vec2d_m(x: i32, y: i32, is_polar: bool) -> Self {
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b010 << 47;                 // Payload Tag 010 para Vec2D
        let polar_bit: u64 = if is_polar { 1 << 46 } else { 0 }; // *i bit
        let x_bits = ((x as i32 as u64) & 0x7FFFFF) << 23;
        let y_bits = (y as i32 as u64) & 0x7FFFFF;

        PaxoValue::M(exp_mask | tag | polar_bit | x_bits | y_bits)
    }

    pub fn pack_vec2d_l(x: i64, y: i64, is_polar: bool) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b010 << 107;                    // Payload Tag 010 para Vec2D
        let polar_bit: u128 = if is_polar { 1 << 106 } else { 0 }; // *i bit
        let x_bits = ((x as i64 as u128) & 0x1FFFFFFFFFFFFF) << 53;
        let y_bits = (y as i64 as u128) & 0x1FFFFFFFFFFFFF;

        PaxoValue::L(exp_mask | tag | polar_bit | x_bits | y_bits)
    }
    pub fn pack_vec2d_xl(x: i128, y: i128, is_polar: bool) -> Self {
        let exp_mask: u64 = 0x1FFFFFF; // 25 bits exponent en 1
        let tag: u64 = 0b0010 << 25;
        let polar_bit: u64 = if is_polar { 1 << 31 } else { 0 };
        let meta = exp_mask | tag | polar_bit;

        let mut words = [0u64; 4];
        let mask = (1u128 << 112) - 1;
        let y_bits = (y as u128) & mask;
        let x_bits = (x as u128) & mask;

        for i in 0..112u32 {
            let bit = ((y_bits >> i) & 1) as u64;
            words[(i / 64) as usize] |= bit << (i % 64);
        }

        for i in 0..112u32 {
            let bit = ((x_bits >> i) & 1) as u64;
            words[((112 + i) / 64) as usize] |= bit << ((112 + i) % 64);
        }

        words[3] |= (meta as u64) << 32;

        PaxoValue::Xl(words)
    }

    /// Desempaqueta un Vector 2D de 32 bits en sus componentes (X, Y)
    pub fn unpack_vec2d_xs(val: u16) -> (i8, i8) {
        let x = ((val >> 4) & 0x0F) as u8;
        let y = (val & 0x0F) as u8;
        let x = ((x as i8) << 4) >> 4;
        let y = ((y as i8) << 4) >> 4;
        (x, y)}

    pub fn unpack_vec2d_s(val: u32) -> (i16, i16, bool) {
        let is_polar = (val & (1 << 16)) != 0;
        let x = ((val >> 8) & 0xFF) as u8 as i16;
        let y = (val & 0xFF) as u8 as i16;
        (x, y, is_polar)
    }

    pub fn unpack_vec2d_m(val: u64) -> (i32, i32, bool) {
        let is_polar = (val & (1 << 46)) != 0;
        let x = (((val >> 23) & 0x7FFFFF) as i64 << 41) >> 41;
        let y = (((val & 0x7FFFFF) as i64) << 41) >> 41;
        (x as i32, y as i32, is_polar)
    }

    pub fn unpack_vec2d_l(val: u128) -> (i64, i64, bool) {
        let is_polar = (val & (1 << 106)) != 0;
        let x = (((val >> 53) & 0x1FFFFFFFFFFFFF) as i128 << 75) >> 75;
        let y = (((val & 0x1FFFFFFFFFFFFF) as i128) << 75) >> 75;
        (x as i64, y as i64, is_polar)
    }

    pub fn unpack_vec2d_xl(val: [u64; 4]) -> (i128, i128, bool) {
        let meta = val[3] >> 32;
        let is_polar = (meta & (1 << 31)) != 0;

        let mut y = 0u128;
        let mut x = 0u128;

        for i in 0..112u32 {
            let bit = ((val[(i / 64) as usize] >> (i % 64)) & 1) as u128;
            y |= bit << i;
        }

        for i in 0..112u32 {
            let pos = 112 + i;
            let bit = ((val[(pos / 64) as usize] >> (pos % 64)) & 1) as u128;
            x |= bit << i;
        }

        let x = (((x as i128) << 16) >> 16);
        let y = (((y as i128) << 16) >> 16);

        (x, y, is_polar)
    }
}