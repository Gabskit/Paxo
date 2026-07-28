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

pub enum DecodedPaxo {
    Float(f64),
    Vector2d(i64, i64),
    Vector4d(i32, i32, i32, i32),
    Boolean(bool),
    Trit(u8),
    Complex(f64, f64),
    Time(u16, u8, u8, u8, u16, u16),
    Utfchar(char)}
    
#[inline(always)] 
impl PaxoValue{

    pub fn pack_data(datatype: u8, size: u8, payload: u128) -> Self {
    match size {
        16 => {
            let packed: u16 = match datatype {
                // 0: Número float (0 + 5 bits exp + 10 bits mantisa)
                0 => (payload as u16) & 0x7FFF,
                // 1: Bit (0 11111 00 0000000x)
                1 => 0x7C00 | ((payload as u16) & 0x0001),
                // 2: Caracter UTF-8 (0 11111 01 XXXXXXXxx)
                2 => 0x7D00 | ((payload as u16) & 0x00FF),
                // 3: Vector 2D (0 11111 10 xxxxyyyy)
                3 => 0x7E00 | ((payload as u16) & 0x00FF),
                // 4: Vector 4D (0 11111 11 xxyyzzww)
                4 => 0x7F00 | ((payload as u16) & 0x00FF),
                // 5: Trit (1 11111 00 000000xx)
                5 => 0xFC00 | ((payload as u16) & 0x0003),
                // 6: Número Complejo (1 11111 01 rrrriiii)
                6 => 0xFD00 | ((payload as u16) & 0x00FF),
                // USO FUTURO
                _ => 0xFE00 | ((payload as u16) & 0x00FF),};
            PaxoValue::XS(packed)}
        32 => {
            let packed: u32 = match datatype {
                // 0: Número float (0 + 11 bits exp + 20 bits mantisa)
                0 => (payload as u32) & 0x7FFF_FFFF,
                // 1: Bit (0 + 11 bits 1 + 00 + 17 bits 0 + x)
                1 => 0x7FF0_0000 | ((payload as u32) & 0x0000_0001),
                // 2: Caracter UTF-16
                2 => 0x7FF4_0000 | ((payload as u32) & 0x0000_FFFF),
                // 3: Vector 2D
                3 => 0x7FF8_0000 | ((payload as u32) & 0x0003_FFFF),
                // 4: Vector 4D
                4 => 0x7FFC_0000 | ((payload as u32) & 0x0000_FFFF),
                // 5: Trit
                5 => 0xFFF0_0000 | ((payload as u32) & 0x0000_0003),
                // 6: Número complejo
                6 => 0xFFF4_0000 | ((payload as u32) & 0x0003_FFFF),
                // 7: Tiempo
                7 => 0xFFF8_0000 | ((payload as u32) & 0x0003_FFFF),
                _ => 0xFFFC_0000 | ((payload as u32) & 0x0003_FFFF),};
            PaxoValue::S(packed)}
        64 => {
            let packed: u64 = match datatype {
                // 0: Número float (0 + 13 bits exp + 50 bits mantisa)
                0 => (payload as u64) & 0x7FFF_FFFF_FFFF_FFFF,
                // 1: Bit
                1 => 0x7FFC_0000_0000_0000 | ((payload as u64) & 0x0000_0000_0000_0001),
                // 2: UTF-32
                2 => 0x7FFD_0000_0000_0000 | ((payload as u64) & 0x0000_0000_FFFF_FFFF),
                // 3: Vector 2D
                3 => 0x7FFE_0000_0000_0000 | ((payload as u64) & 0x0000_FFFF_FFFF_FFFF),
                // 4: Vector 4D
                4 => 0x7FFF_0000_0000_0000 | ((payload as u64) & 0x0000_FFFF_FFFF_FFFF),
                // 5: Trit
                5 => 0xFFFC_0000_0000_0000 | ((payload as u64) & 0x0000_0000_0000_0003),
                // 6: Numero complejo
                6 => 0xFFFD_0000_0000_0000 | ((payload as u64) & 0x0000_FFFF_FFFF_FFFF),
                // 7: Tiempo
                7 => 0xFFFE_0000_0000_0000 | ((payload as u64) & 0x0000_FFFF_FFFF_FFFF),
                _ => 0xFFFF_0000_0000_0000 | ((payload as u64) & 0x0000_FFFF_FFFF_FFFF),};
            PaxoValue::M(packed)}
        128 => {
            let packed: u128 = match datatype {
                // 0: Número float (0 + 17 bits exp + 110 bits mantisa)
                0 => (payload as u128) & 0x7fff_ffff_ffff_ffff_ffff_ffff_ffff_ffff,
                // 1: Bit
                1 => 0x7fff_c000_0000_0000_0000_0000_0000_0000 | ((payload as u128) & 0x0000_0000_0000_0000_0000_0000_0000_0001),
                // 2: UTF-32
                2 => 0x7fff_d000_0000_0000_0000_0000_0000_0000 | ((payload as u128) & 0x0000_0000_0000_0000_0000_0000_FFFF_FFFF),
                // 3: Vector 2D
                3 => 0x7fff_e000_0000_0000_0000_0000_0000_0000 | ((payload as u128) & 0x0000_0fff_ffff_ffff_ffff_ffff_ffff_ffff),
                // 4: Vector 4D
                4 => 0x7fff_f000_0000_0000_0000_0000_0000_0000 | ((payload as u128) & 0x0000_03ff_ffff_ffff_ffff_ffff_ffff_ffff),
                // 5: Trit
                5 => 0xffff_c000_0000_0000_0000_0000_0000_0000 | ((payload as u128) & 0x0000_0000_0000_0000_0000_0000_0000_0003),
                // 6: Número complejo
                6 => 0xffff_d000_0000_0000_0000_0000_0000_0000 | ((payload as u128) & 0x0000_0fff_ffff_ffff_ffff_ffff_ffff_ffff),
                // 7: tiempo
                7 => 0xffff_e000_0000_0000_0000_0000_0000_0000 | ((payload as u128) & 0x0000_0000_0000_0000_0000_3fff_ffff_ffff),
                // Tipos etiquetados (17 bits de exponente en 1)
                _ => (0x1FFFFu128 << 110) | (payload & ((1u128 << 110) - 1)),};
            PaxoValue::L(packed)}
        _ => panic!("Unsupported size"),}}

    pub fn unpack_data(&self) -> DecodedPaxo {
        match &self {
            PaxoValue::Xs(v) => {
                if (v & 0x7c00) != 0x7c00 {
                    let exp = ((v >> 10) & 0x1F) as i32;
                    let mantissa = (v & 0x03FF) as f64;
                    let bias = 15;
                    let result = if exp == 0 && mantissa == 0.0 {
                        0.0
                    } else {
                        mantissa * 10.0f64.powi(exp - bias)
                    };
                    DecodedPaxo::Float(result)
                } else {
                    let tag = v & 0xFF00;
                    match tag {
                        0x7C00 => DecodedPaxo::Boolean((payload & 0x1) != 0), // Bit
                        0x7D00 => DecodedPaxo::Utfchar((payload & 0xFF) as char), // UTF-8
                        0x7E00 => DecodedPaxo::Vector2d(((payload >> 4) & 0xF) as i64, (payload & 0xF) as i64), // Vector 2D
                        0x7F00 => DecodedPaxo::Vector4d(
                        ((payload >> 6) & 0x3) as i32,
                        ((payload >> 4) & 0x3) as i32,
                        ((payload >> 2) & 0x3) as i32,
                        (payload & 0x3) as i32), // Vector 4D
                        0xFC00 => , // Trit
                        0xFD00 => (6, (v & 0x00FF) as u128), // Número complejo
                        _ => (7, (v & 0x00FF) as u128),      // Uso futuro / reservado
                    }
                }
            }
        }
    }
}
