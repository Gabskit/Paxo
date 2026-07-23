mod nanbox;
mod vm;

use nanbox::PaxoValue;
use vm::PaxoVM;
use std::fs;

fn main() {
    println!("========================================");
    println!("        🚀 PAXO VM ENGINE (FIFO)        ");
    println!("========================================\n");

    // Instanciamos la VM con 16 registros de almacenamiento
    let mut vm = PaxoVM::new(16);

    // Intentar leer el archivo compilado desde el Frontend en Go
    let bytecode_path = "Test/output.paxoc";

    if let Ok(bytes) = fs::read(bytecode_path) {
        println!("📂 Archivo de bytecode detectado: '{}'", bytecode_path);
        println!("⚡ Ejecutando {} bytes de instrucciones...\n", bytes.len());

        for (i, &opcode) in bytes.iter().enumerate() {
            println!("  [Paso {:02}] Ejecutando Opcode: 0x{:02X}", i + 1, opcode);
            vm.step(opcode, None);
        }

        println!("\n✅ Ejecución de Bytecode completada.");
    } else {
        println!("⚠️ No se encontró '{}'. Ejecutando Test Suite Interno...\n", bytecode_path);

        // --- TEST 1: Operaciones en Cola FIFO ---
        println!("--- Test 1: Operación FIFO Add (Suma de 32 bits) ---");
        let val_a = PaxoValue::S(15);
        let val_b = PaxoValue::S(25);

        vm.step(0x01, Some(val_a)); // PUSH 15
        vm.step(0x01, Some(val_b)); // PUSH 25
        println!("   Cola FIFO antes de ADD: {:?}", vm.fifo_queue);

        vm.step(0x10, None);       // ADD (15 + 25 = 40)
        println!("   Cola FIFO después de ADD: {:?}", vm.fifo_queue);

        vm.step(0x03, Some(PaxoValue::S(0))); // STORE en registro v0
        println!("   Registro v0 guardado: {:?}\n", vm.registers[0]);

        // --- TEST 2: Empaquetado y Desempaquetado BIV (Vector 2D) ---
        println!("--- Test 2: BIV Vector 2D (S - 32 bits) ---");
        let vec_packed = PaxoValue::pack_vec2d_s(10, -5, false);
        println!("   Vector empaquetado (Bitmask): {:?}", vec_packed);

        if let PaxoValue::S(bits) = vec_packed {
            let (x, y, is_polar) = PaxoValue::unpack_vec2d_s(bits);
            println!("   Vector desempaquetado -> X: {}, Y: {}, Polar: {}\n", x, y, is_polar);
        }
    }
}