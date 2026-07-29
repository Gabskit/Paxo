// TF helpers (19-bit tagging)
pub const TF_BITS: u32 = 19;
pub const TF_MASK: u32 = (1u32 << TF_BITS) - 1u32; // 0x7FFFF

#[inline]
pub fn pack_tf_le(tf: u32) -> [u8; 3] {
    let v = tf & TF_MASK;
    [ (v & 0xFF) as u8, ((v >> 8) & 0xFF) as u8, ((v >> 16) & 0x07) as u8 ]
}

#[inline]
pub fn unpack_tf_le(bytes: [u8;3]) -> u32 {
    (bytes[0] as u32) | ((bytes[1] as u32) << 8) | (((bytes[2] as u32) & 0x07) << 16)
}

#[inline]
pub fn tf_to_signed(tf: u32) -> i32 {
    let v = tf & TF_MASK;
    if (v & (1u32 << (TF_BITS - 1))) != 0 {
        (v as i32) | (!((TF_MASK) as i32))
    } else {
        v as i32
    }
}
/// Representación de los tipos de datos BIV según tamaño de variable en Paxo
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PaxoValue {
    Xxs(u8),
    Xxsm3(u8),
    /// 16 bits: valor extendido.
    Xs(u16),
    Xsb(u16),
    Tf(u32),
    /// 32 bits: valor standard.
    S(u32),
    Sst(u32),
    /// 64 bits: valor medio.
    M(u64),
    Mst(u64),
    /// 128 bits: valor largo.
    L(u128),
    Lst(u128)}

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
            PaxoValue::Xs(packed)}
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
                // Stub implementation for migration: return Float(0.0)
                DecodedPaxo::Float(0.0)
            }
}
