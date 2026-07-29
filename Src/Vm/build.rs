use std::env;
use std::path::Path;
use std::process::Command;

fn main() {
    let out_dir = env::var("OUT_DIR").expect("OUT_DIR not set");
    let manifest_dir = env::var("CARGO_MANIFEST_DIR").expect("CARGO_MANIFEST_DIR not set");
    let src = Path::new(&manifest_dir).join("csrc").join("nanbox.c");
    let out_obj = Path::new(&out_dir).join("nanbox.o");
    let out_lib = Path::new(&out_dir).join("libnanbox.a");

    println!("cargo:rerun-if-changed={}", src.display());

    let cc = env::var("CC").unwrap_or_else(|_| String::from("clang"));

    // Compile C source to object with C23
    let status = Command::new(&cc)
        .arg("-c")
        .arg("-std=c23")
        .arg("-O2")
        .arg("-fPIC")
        .arg(src.to_str().unwrap())
        .arg("-o")
        .arg(out_obj.to_str().unwrap())
        .status()
        .expect("failed to spawn C compiler");

    if !status.success() {
        panic!("C compilation failed");
    }

    // Create static archive libnanbox.a
    let ar = env::var("AR").unwrap_or_else(|_| String::from("ar"));
    let status = Command::new(&ar)
        .arg("crs")
        .arg(out_lib.to_str().unwrap())
        .arg(out_obj.to_str().unwrap())
        .status()
        .expect("failed to run ar");

    if !status.success() {
        panic!("creating static archive failed");
    }

    println!("cargo:rustc-link-search=native={}", out_dir);
    println!("cargo:rustc-link-lib=static=nanbox");
}
