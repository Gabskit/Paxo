use std::collections::VecDeque;
use crate::nanbox::PaxoValue;

pub struct PaxoVM {
    pub fifo_queue: VecDeque<PaxoValue>, // Cola FIFO principal
    pub registers: Vec<PaxoValue>,       // Variables locales / Registros
}

impl PaxoVM {
    pub fn new(num_registers: usize) -> Self {
        Self {
            fifo_queue: VecDeque::with_capacity(256),
            registers: vec![PaxoValue::Normal(0); num_registers],
        }
    }

    fn register_index(arg: PaxoValue) -> Option<usize> {
        match arg {
            PaxoValue::Xxs(v) => Some(v as usize),
            PaxoValue::Xs(v) => Some(v as usize),
            PaxoValue::S(v) => Some(v as usize),
            PaxoValue::M(v) => Some(v as usize),
            PaxoValue::Normal(v) => Some(v as usize),
            _ => None,
        }
    }

    fn add_numeric(a: PaxoValue, b: PaxoValue) -> Option<PaxoValue> {
        match (a, b) {
            (PaxoValue::Xxs(v1), PaxoValue::Xxs(v2)) => Some(PaxoValue::Xxs(v1.wrapping_add(v2))),
            (PaxoValue::Xs(v1), PaxoValue::Xs(v2)) => Some(PaxoValue::Xs(v1.wrapping_add(v2))),
            (PaxoValue::S(v1), PaxoValue::S(v2)) => Some(PaxoValue::S(v1.wrapping_add(v2))),
            (PaxoValue::M(v1), PaxoValue::M(v2)) => Some(PaxoValue::M(v1.wrapping_add(v2))),
            (PaxoValue::Normal(v1), PaxoValue::Normal(v2)) => Some(PaxoValue::Normal(v1.wrapping_add(v2))),
            (PaxoValue::Normal(v1), PaxoValue::S(v2)) => Some(PaxoValue::Normal(v1.wrapping_add(v2 as u64))),
            (PaxoValue::S(v1), PaxoValue::Normal(v2)) => Some(PaxoValue::Normal((v1 as u64).wrapping_add(v2))),
            (PaxoValue::Ipv4(v1), PaxoValue::Ipv4(v2)) => Some(PaxoValue::Ipv4(v1.wrapping_add(v2))),
            (PaxoValue::Vec2D { x: x1, y: y1, polar: p1, width: w1 }, PaxoValue::Vec2D { x: x2, y: y2, polar: p2, width: w2 }) => {
                let width = w1.max(w2);
                let polar = p1 && p2;
                Some(PaxoValue::Vec2D { x: x1.wrapping_add(x2), y: y1.wrapping_add(y2), polar, width })
            }
            (PaxoValue::Vec4D { x: x1, y: y1, z: z1, w: w1, width: width1 }, PaxoValue::Vec4D { x: x2, y: y2, z: z2, w: w2, width: width2 }) => {
                Some(PaxoValue::Vec4D {
                    x: x1.wrapping_add(x2),
                    y: y1.wrapping_add(y2),
                    z: z1.wrapping_add(z2),
                    w: w1.wrapping_add(w2),
                    width: width1.max(width2),
                })
            }
            (PaxoValue::Complex { re: r1, im: i1, width: w1 }, PaxoValue::Complex { re: r2, im: i2, width: w2 }) => {
                Some(PaxoValue::Complex {
                    re: r1.wrapping_add(r2),
                    im: i1.wrapping_add(i2),
                    width: w1.max(w2),
                })
            }
            _ => None,
        }
    }

    /// Ejecuta una instrucción en la Cola FIFO
    pub fn step(&mut self, opcode: u8, arg: Option<PaxoValue>) {
        match opcode {
            0x01 => { // PUSH: Encola al final de la cola FIFO
                if let Some(val) = arg {
                    self.fifo_queue.push_back(val);
                }
            }
            0x02 => { // LOAD vX: Lee registro local y encola
                if let Some(idx) = arg.and_then(Self::register_index) {
                    let val = self.registers[idx];
                    self.fifo_queue.push_back(val);
                }
            }
            0x03 => { // STORE vX: Desencola del frente y guarda en registro local
                if let Some(idx) = arg.and_then(Self::register_index) {
                    if let Some(val) = self.fifo_queue.pop_front() {
                        self.registers[idx] = val;
                    }
                }
            }
            0x10 => { // ADD: Desencola 2 operandos del frente y encola la suma al final
                if let (Some(a), Some(b)) = (self.fifo_queue.pop_front(), self.fifo_queue.pop_front()) {
                    if let Some(res) = Self::add_numeric(a, b) {
                        self.fifo_queue.push_back(res);
                    } else {
                        panic!("Tipos incompatibles para suma en VM");
                    }
                }
            }
            _ => todo!("Opcode 0x{:02X} aún no implementada", opcode),
        }
    }
}