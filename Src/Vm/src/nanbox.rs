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
                    let exp: i8 = ((v >> 10) & 0x1f) as i8;
                    let mantissa: f64 = (v & 0x03FF) as f64;
                    let bias: u8 = 15;
                    let result: f64 = if exp == 0 && mantissa == 0.0 {
                        0.0;
                    } else {
                        mantissa * 10.0f64.powi(exp - bias);}

                    DecodedPaxo::Float(result);
                } else {
                    let tag: u16 = v & 0xff00;
                    match tag {
                        0x7c00 => DecodedPaxo::Boolean((v & 0x1) as bool), // Bit
                        0x7d00 => DecodedPaxo::Utfchar((v & 0xFF) as char), // UTF-8
                        0x7E00 => DecodedPaxo::Vector2d(((v >> 4) & 0xF) as i64, (payload & 0xF) as i64), // Vector 2D
                        0x7F00 => DecodedPaxo::Vector4d(
                        ((v >> 6) & 0x3) as i32,
                        ((v >> 4) & 0x3) as i32,
                        ((v >> 2) & 0x3) as i32,
                        (v & 0x3) as i32), // Vector 4D
                        0xFC00 => DecodedPaxo::Trit((v & 0x3) as u8), // Trit
                        0xFD00 => {
                            let expr: i8 = ((v >> 5) & 0x6) as i8;
                            let expi: i8 = ((v >> 1) & 0x6) as i8;
                            let mantissar: f64 = ((v >> 4) & 0x1) as f64;
                            let mantissai: f64 = (v & 0x1) as f64;
                            let bias: u8 = 1;
                            let resultr: f64 = if expr == 0 && mantissar == 0.0 {
                                0.0;
                            } else {
                                mantissar * 10.0f64.powi(expr - bias);}

                            let resulti: f64 = if expi == 0 && mantissai == 0.0 {
                                0.0;
                            } else {
                                mantissai * 10.0f64.powi(expi - bias);}

                            DecodedPaxo::Complex(resultr, resulti);}, // Número complejo

                        _ => DecodedPaxo::Float(v as f64)}}}

            PaxoValue::S(v) => {
                if (v & 0x7fe0_0000) != 0x7fe0_0000 {
                    let exp: i16 = ((v >> 20) & 0x7ff) as i16;
                    let mantissa: f64 = (v & 0xf_ffff) as f64;
                    let bias: u16 = 1023;
                    let result: f64 = if exp == 0 && mantissa == 0.0 {
                        0.0;
                    } else {
                        mantissa * 10.0f64.powi(exp - bias);}
                    
                    DecodedPaxo::Float(result);
                } else {
                    let tag: u32 = v & 0xfffc_0000;
                    match tag {
                        0x7ff0_0000 => DecodedPaxo::Boolean((v & 0x1) as bool),
                        0x7ff4_0000 => DecodedPaxo::Utfchar((v & 0xffff) as char),
                        0x7ff8_0000 => DecodedPaxo::Vector2d(((v >> 9) & 0x1ff) as i64, (v & 0x1ff) as i64),
                        0x7ffc_0000 => DecodedPaxo::Vector4d(
                            ((v >> 12) & 0xf) as i32,
                            ((v >> 8) & 0xf) as i32,
                            ((v >> 4) & 0xf) as i32,
                            (v & 0xf) as i32),
                        0xfff0_0000 => DecodedPaxo::Trit((v & 0x3) as u8),
                        0xfff4_0000 => {
                            let expr: i8 = ((v >> 13) & 0xf) as i8;
                            let expi: i8 = ((v >> 4) & 0xf) as i8;
                            let mantissar: f64 = ((v >> 9) & 0xf) as f64;
                            let mantissai: f64 = (v & 0xf) as f64;
                            let bias: u8 = 7;
                            let resultr: f64 = if expr == 0 & mantissar == 0.0 {
                                0.0;
                            } else {
                                mantissar * 10.0f64.powi(expr - bias);}

                            let resulti: f64 = if expi == 0 & mantissai == 0.0 {
                                0.0;
                            } else {
                                mantissai * 10.0f64.powi(expi - bias);}

                            DecodedPaxo::Complex(resultr, resulti);},

                        0xfff8_0000 => DecodedPaxo::Time(
                            0, ((v >> 12) & 0x1f) as u8,
                            ((v >> 6) & 0x3f) as u8,
                            (v & 0x3f) as u8, 0, 0),
                        _ => DecodedPaxo::Float(v as f64),}}}

            PaxoValue::M(v) => {
                if (v & 0x7ffc_0000_0000_0000) != 0x7ffc_0000_0000_0000 {
                    let exp: i8 = ((v >> 50) & 0x1fff) as i16;
                    let mantissa: f64 = (v & 0x3_ffff_ffff_ffff) as f64;
                    let bias: u16 = 4095;
                    let result: f64 = if exp == 0 && mantissa == 0.0 {
                        0.0;
                    } else {
                        mantissa * 10.0f64.powi(exp - bias);}

                    DecodedPaxo::Float(result);
                } else {
                    let tag: u64 = v & 0xffff_0000_0000_0000;
                    match tag {
                        0x7ffc_0000_0000_0000 => DecodedPaxo::Boolean((v & 0x1) as bool),
                        0x7ffd_0000_0000_0000 => DecodedPaxo::Utfchar((v & 0xffff_ffff) as char),
                        0x7ffe_0000_0000_0000 => DecodedPaxo::Vector2d(((v >> 24) & 0xff_ffff) as i64, (v & 0xff_ffff) as i64),
                        0x7fff_0000_0000_0000 => DecodedPaxo::Vector4d(
                            ((v >> 36) & 0xfff) as i32,
                            ((v >> 24) & 0xfff) as i32,
                            ((v >> 12) & 0xfff) as i32,
                            (v & 0xfff) as i32),
                        0xfffc_0000_0000_0000 => DecodedPaxo::Trit((v & 0x3) as u8),
                        0xfffd_0000_0000_0000 => {
                            let expr: i8 = ((v >> 40) & 0x7f) as i8;
                            let expi: i8 = ((v >> 16) & 0x7f) as i8;
                            let mantissar: f64 = ((v >> 24) & 0xff_ffff) as f64;
                            let mantissai: f64 = (v & 0xff_ffff) as f64;
                            let bias: u16 = 63;
                            let resultr: f64 = if expr == 0 && mantissar == 0.0 {
                                0.0;
                            } else {
                                mantissar * 10.0f64.powi(expr - bias):}

                            let resulti: f64 = if expi == 0 && mantissai == 0.0 {
                                0.0;
                            } else {
                                mantissai * 10.0f64.powi(expi - bias);}
                            
                            DecodedPaxo::Complex(resultr, resulti);},

                        0xfffe_0000_0000_0000 => DecodedPaxo::Time(
                            ((v >> 37) & 0x1ff) as u16,
                            ((v >> 32) & 0x1f) as u8,
                            ((v >> 26) & 0x3f) as u8,
                            ((v >> 20) & 0x3f) as u8,
                            ((v >> 10) & 0x3ff) as u16,
                            (v & 0x3ff) as u16),
                        _ => DecodedPaxo::Float(v as f64),}}}

            PaxoValue::L(v) => {
                
            }
        }
    }
}
