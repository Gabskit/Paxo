use std::collections::VecDeque;
use crate::nanbox::PaxoValue;

// LEP VM: Light Environment Processing Virtual Machine
pub struct LEPVM {
    pub fifo_queue: VecDeque<PaxoValue>, // Cola FIFO principal
    pub registers: Vec<PaxoValue>,/*Registros locales*/}

impl LEPVM {
    pub fn new(num_registers: usize) -> Self {
        Self {
            fifo_queue: VecDeque::with_capacity(256),
            registers: vec![PaxoValue::Xs(0); num_registers],}}

    fn register_index(arg: PaxoValue) -> Option<usize> {
        match arg {
            PaxoValue::Xs(v) => Some(v as usize),
            PaxoValue::S(v) => Some(v as usize),
            PaxoValue::M(v) => Some(v as usize),
            PaxoValue::L(v) => Some(v as usize),
            _ => None,}}

    fn add_numeric(a: PaxoValue, b: PaxoValue) -> Option<PaxoValue> {
        match (a, b) {
            (PaxoValue::Xs(v1), PaxoValue::Xs(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_xs(v1);
                let val2 = PaxoValue::ieee754_to_base20_xs(v2);
                Some(PaxoValue::Xs(PaxoValue::base20_to_ieee754_xs(val1 + val2)))
            },
            (PaxoValue::S(v1), PaxoValue::S(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_s(v1);
                let val2 = PaxoValue::ieee754_to_base20_s(v2);
                Some(PaxoValue::S(PaxoValue::base20_to_ieee754_s(val1 + val2)))
            },
            (PaxoValue::M(v1), PaxoValue::M(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_m(v1);
                let val2 = PaxoValue::ieee754_to_base20_m(v2);
                Some(PaxoValue::M(PaxoValue::base20_to_ieee754_m(val1 + val2)))
            },
            (PaxoValue::L(v1), PaxoValue::L(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_l(v1);
                let val2 = PaxoValue::ieee754_to_base20_l(v2);
                Some(PaxoValue::L(PaxoValue::base20_to_ieee754_l(val1 + val2)))
            },
            _ => None,}}

    fn sub_numeric(a: PaxoValue, b: PaxoValue) -> Option<PaxoValue> {
        match (a, b) {
            (PaxoValue::Xs(v1), PaxoValue::Xs(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_xs(v1);
                let val2 = PaxoValue::ieee754_to_base20_xs(v2);
                Some(PaxoValue::Xs(PaxoValue::base20_to_ieee754_xs(val1 - val2)))
            },
            (PaxoValue::S(v1), PaxoValue::S(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_s(v1);
                let val2 = PaxoValue::ieee754_to_base20_s(v2);
                Some(PaxoValue::S(PaxoValue::base20_to_ieee754_s(val1 - val2)))
            },
            (PaxoValue::M(v1), PaxoValue::M(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_m(v1);
                let val2 = PaxoValue::ieee754_to_base20_m(v2);
                Some(PaxoValue::M(PaxoValue::base20_to_ieee754_m(val1 - val2)))
            },
            (PaxoValue::L(v1), PaxoValue::L(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_l(v1);
                let val2 = PaxoValue::ieee754_to_base20_l(v2);
                Some(PaxoValue::L(PaxoValue::base20_to_ieee754_l(val1 - val2)))
            },
            _ => None,}}

    fn mul_numeric(a: PaxoValue, b: PaxoValue) -> Option<PaxoValue> {
        match (a, b) {
            (PaxoValue::Xs(v1), PaxoValue::Xs(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_xs(v1);
                let val2 = PaxoValue::ieee754_to_base20_xs(v2);
                Some(PaxoValue::Xs(PaxoValue::base20_to_ieee754_xs(val1 * val2)))
            },
            (PaxoValue::S(v1), PaxoValue::S(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_s(v1);
                let val2 = PaxoValue::ieee754_to_base20_s(v2);
                Some(PaxoValue::S(PaxoValue::base20_to_ieee754_s(val1 * val2)))
            },
            (PaxoValue::M(v1), PaxoValue::M(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_m(v1);
                let val2 = PaxoValue::ieee754_to_base20_m(v2);
                Some(PaxoValue::M(PaxoValue::base20_to_ieee754_m(val1 * val2)))
            },
            (PaxoValue::L(v1), PaxoValue::L(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_l(v1);
                let val2 = PaxoValue::ieee754_to_base20_l(v2);
                Some(PaxoValue::L(PaxoValue::base20_to_ieee754_l(val1 * val2)))
            },
            _ => None,}}
    
    fn div_numeric(a: PaxoValue, b: PaxoValue) -> Option<PaxoValue> {
        match (a, b) {
            (PaxoValue::Xs(v1), PaxoValue::Xs(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_xs(v1);
                let val2 = PaxoValue::ieee754_to_base20_xs(v2);
                if val2 == 0.0 { return None; }
                Some(PaxoValue::Xs(PaxoValue::base20_to_ieee754_xs(val1 / val2)))
            },
            (PaxoValue::S(v1), PaxoValue::S(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_s(v1);
                let val2 = PaxoValue::ieee754_to_base20_s(v2);
                if val2 == 0.0 { return None; }
                Some(PaxoValue::S(PaxoValue::base20_to_ieee754_s(val1 / val2)))
            },
            (PaxoValue::M(v1), PaxoValue::M(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_m(v1);
                let val2 = PaxoValue::ieee754_to_base20_m(v2);
                if val2 == 0.0 { return None; }
                Some(PaxoValue::M(PaxoValue::base20_to_ieee754_m(val1 / val2)))
            },
            (PaxoValue::L(v1), PaxoValue::L(v2)) => {
                let val1 = PaxoValue::ieee754_to_base20_l(v1);
                let val2 = PaxoValue::ieee754_to_base20_l(v2);
                if val2 == 0.0 { return None; }
                Some(PaxoValue::L(PaxoValue::base20_to_ieee754_l(val1 / val2)))
            },
            _ => None,}}

    fn bitshift_R(a: PaxoValue, b: PaxoValue) -> Option<PaxoValue> {
        let shift = match b {
            PaxoValue::Xs(v) => (v & 0xF) as u32,
            PaxoValue::S(v) => (v & 0xFF) as u32,
            PaxoValue::M(v) => (v & 0xFFFF) as u32,
            PaxoValue::L(v) => (v & 0xFFFFFFFF) as u32,
        };
        match a {
            PaxoValue::Xs(v1) => Some(PaxoValue::Xs(v1 >> shift)),
            PaxoValue::S(v1) => Some(PaxoValue::S(v1 >> shift)),
            PaxoValue::M(v1) => Some(PaxoValue::M(v1 >> shift)),
            PaxoValue::L(v1) => Some(PaxoValue::L(v1 >> shift)),
        }
    }

    fn bitshift_L(a: PaxoValue, b: PaxoValue) -> Option<PaxoValue> {
        let shift = match b {
            PaxoValue::Xs(v) => (v & 0xF) as u32,
            PaxoValue::S(v) => (v & 0xFF) as u32,
            PaxoValue::M(v) => (v & 0xFFFF) as u32,
            PaxoValue::L(v) => (v & 0xFFFFFFFF) as u32,
        };
        match a {
            PaxoValue::Xs(v1) => Some(PaxoValue::Xs(v1 << shift)),
            PaxoValue::S(v1) => Some(PaxoValue::S(v1 << shift)),
            PaxoValue::M(v1) => Some(PaxoValue::M(v1 << shift)),
            PaxoValue::L(v1) => Some(PaxoValue::L(v1 << shift)),
        }
    }

    /// Ejecuta una instrucción en la Cola FIFO
    pub fn step(&mut self, opcode: u8, arg: Option<PaxoValue>) {
        match opcode {
            // Operaciones de la Cola FIFO 0x01 a 0x0F
            0x01 => { // PUSH: Encola al final de la cola FIFO
                if let Some(val) = arg {
                    self.fifo_queue.push_back(val);}}

            0x02 => { // LOAD vX: Lee registro local y encola
                if let Some(idx) = arg.and_then(Self::register_index) {
                    let val = self.registers[idx];
                    self.fifo_queue.push_back(val);}}

            0x03 => { // STORE vX: Desencola del frente y guarda en registro local
                if let Some(idx) = arg.and_then(Self::register_index) {
                    if let Some(val) = self.fifo_queue.pop_front() {
                        self.registers[idx] = val;}}}

            0x04 => { // POP: Desencola del frente y descarta el valor
                self.fifo_queue.pop_front();}

            // Operaciones Aritméticas y Lógicas 0x10 a 0x1F
            0x10 => { // ADD: Desencola 2 operandos del frente y encola la suma al final
                if let (Some(a), Some(b)) = (self.fifo_queue.pop_front(), self.fifo_queue.pop_front()) {
                    if let Some(res) = Self::add_numeric(a, b) {
                        self.fifo_queue.push_back(res);
                    } else {
                        panic!("Tipos incompatibles para suma en VM");}}}

            0x11 => { // SUB: Desencola 2 operandos del frente y encola la resta al final
                if let (Some(a), Some(b)) = (self.fifo_queue.pop_front(), self.fifo_queue.pop_front()) {
                    if let Some(res) = Self::sub_numeric(a, b) {
                        self.fifo_queue.push_back(res);
                    } else {
                        panic!("Tipos incompatibles para resta en VM");}}}

            0x12 => { // MUL: Desencola 2 operandos del frente y encola el producto al final
                if let (Some(a), Some(b)) = (self.fifo_queue.pop_front(), self.fifo_queue.pop_front()) {
                    if let Some(res) = Self::mul_numeric(a, b) {
                        self.fifo_queue.push_back(res);
                    } else {
                        panic!("Tipos incompatibles para multiplicación en VM");}}}


            _ => todo!("Opcode 0x{:02X} aún no implementada", opcode),}}}