package parser

import (
	"os"
	"path/filepath"
	"testing"
)

func TestEmitterPushBool(t *testing.T) {
	e := Emitter{code: make([]byte, 0)}
	e.pushBool(true)
	if len(e.code) != 3 {
		t.Fatalf("pushBool(true): expected 3 bytes, got %d", len(e.code))
	}
	if e.code[0] != OP_PUSH {
		t.Errorf("byte 0: expected OP_PUSH, got %d", e.code[0])
	}
	if e.code[1] != TYPE_BOOL {
		t.Errorf("byte 1: expected TYPE_BOOL, got %d", e.code[1])
	}
	if e.code[2] != 1 {
		t.Errorf("byte 2: expected 1 (true), got %d", e.code[2])
	}
}

func TestEmitterPushChar(t *testing.T) {
	e := Emitter{code: make([]byte, 0)}
	e.pushChar(uint8('A'))
	if len(e.code) != 3 {
		t.Fatalf("pushChar('A'): expected 3 bytes, got %d", len(e.code))
	}
	if e.code[2] != 'A' {
		t.Errorf("byte 2: expected 'A'(%d), got %d", 'A', e.code[2])
	}
}

func TestEmitterPushNum16(t *testing.T) {
	e := Emitter{code: make([]byte, 0)}
	e.pushNum16(300)
	if len(e.code) != 4 {
		t.Fatalf("pushNum16(300): expected 4 bytes, got %d", len(e.code))
	}
	if e.code[0] != OP_PUSH {
		t.Errorf("byte 0: expected OP_PUSH, got %d", e.code[0])
	}
	if e.code[1] != TYPE_NUM16 {
		t.Errorf("byte 1: expected TYPE_NUM16, got %d", e.code[1])
	}
}

func TestEmitterPushNum64(t *testing.T) {
	e := Emitter{code: make([]byte, 0)}
	e.pushNum64(5000000000)
	if len(e.code) != 10 {
		t.Fatalf("pushNum64(5000000000): expected 10 bytes, got %d", len(e.code))
	}
	if e.code[0] != OP_PUSH {
		t.Errorf("byte 0: expected OP_PUSH, got %d", e.code[0])
	}
	if e.code[1] != TYPE_NUM64 {
		t.Errorf("byte 1: expected TYPE_NUM64, got %d", e.code[1])
	}
}

func TestEmitterEmit(t *testing.T) {
	e := Emitter{code: make([]byte, 0)}
	e.emit(OP_ADD)
	e.emit(OP_SUB)
	if len(e.code) != 2 {
		t.Fatalf("emit two ops: expected 2 bytes, got %d", len(e.code))
	}
	if e.code[0] != OP_ADD || e.code[1] != OP_SUB {
		t.Errorf("expected [OP_ADD, OP_SUB], got [%d, %d]", e.code[0], e.code[1])
	}
}

func TestEmitterEmit16(t *testing.T) {
	e := Emitter{code: make([]byte, 0)}
	e.emit16(0x0102)
	if len(e.code) != 2 {
		t.Fatalf("emit16: expected 2 bytes, got %d", len(e.code))
	}
	if e.code[0] != 0x02 || e.code[1] != 0x01 {
		t.Errorf("emit16(0x0102): expected [0x02, 0x01], got [%#x, %#x]", e.code[0], e.code[1])
	}
}

func TestEmitterDeferred(t *testing.T) {
	e := Emitter{code: make([]byte, 0), deferred: true, deferredBuf: make([]byte, 0)}
	e.emit(OP_ADD)
	if len(e.code) != 0 {
		t.Error("deferred emit should not write to code")
	}
	if len(e.deferredBuf) != 1 {
		t.Fatal("deferred emit should write to deferredBuf")
	}
	if e.deferredBuf[0] != OP_ADD {
		t.Errorf("deferred: expected OP_ADD, got %d", e.deferredBuf[0])
	}
	e.deferred = false
	e.emit(OP_SUB)
	if len(e.code) != 1 || e.code[0] != OP_SUB {
		t.Error("after un-deferred, emit should write to code")
	}
}

func TestPatchI16(t *testing.T) {
	e := Emitter{code: make([]byte, 0)}
	e.emit(0) // placeholder
	e.emit(0)
	e.patchI16(0, 42)
	if e.code[0] != 42 {
		t.Errorf("patchI16 low byte: expected 42, got %d", e.code[0])
	}
}

func TestPos(t *testing.T) {
	e := Emitter{code: make([]byte, 0)}
	if e.pos() != 0 {
		t.Errorf("empty emitter pos: expected 0, got %d", e.pos())
	}
	e.emit(OP_ADD)
	if e.pos() != 1 {
		t.Errorf("after emit pos: expected 1, got %d", e.pos())
	}
}

func TestResolveType(t *testing.T) {
	cg := NewCodeGen()
	tests := []struct {
		input string
		want  byte
	}{
		{"var", TYPE_NUM64},
		{"📥", TYPE_NUM64},
		{"n", TYPE_NUM64},
		{"sn", TYPE_NUM16},
		{"abc", TYPE_CHAR},
		{"trit", TYPE_TRIT},
		{"bool", TYPE_BOOL},
		{"pin", TYPE_POINT},
		{"unknown", TYPE_NUM64},
	}
	for _, tt := range tests {
		got := cg.resolveType(tt.input)
		if got != tt.want {
			t.Errorf("resolveType(%q): expected %d, got %d", tt.input, tt.want, got)
		}
	}
}

func TestCompileMissingFile(t *testing.T) {
	err := Compile("/nonexistent.paxo", "/tmp/out.pbc", false)
	if err == nil {
		t.Error("Compile with nonexistent file should return error")
	}
}

func TestCompileValidProgram(t *testing.T) {
	tmpDir := t.TempDir()
	paxoFile := filepath.Join(tmpDir, "simple.paxo")
	pbcFile := filepath.Join(tmpDir, "simple.pbc")

	err := os.WriteFile(paxoFile, []byte("local n x = 0\n"), 0644)
	if err != nil {
		t.Fatal(err)
	}

	err = Compile(paxoFile, pbcFile, false)
	if err != nil {
		t.Fatalf("Compile failed: %v", err)
	}

	data, err := os.ReadFile(pbcFile)
	if err != nil {
		t.Fatalf("Failed to read output: %v", err)
	}
	if len(data) == 0 {
		t.Error("Compiled bytecode is empty")
	}
	if data[len(data)-1] != OP_HALT {
		t.Errorf("Bytecode should end with OP_HALT(%d), got %d", OP_HALT, data[len(data)-1])
	}
}

func TestCompileUndefinedVar(t *testing.T) {
	tmpDir := t.TempDir()
	paxoFile := filepath.Join(tmpDir, "bad.paxo")
	pbcFile := filepath.Join(tmpDir, "bad.pbc")

	err := os.WriteFile(paxoFile, []byte("y = 10\n"), 0644)
	if err != nil {
		t.Fatal(err)
	}

	err = Compile(paxoFile, pbcFile, false)
	if err == nil {
		t.Error("Compile with undefined var should return error")
	}
}

func TestCompileArithmetic(t *testing.T) {
	tmpDir := t.TempDir()
	paxoFile := filepath.Join(tmpDir, "arith.paxo")
	pbcFile := filepath.Join(tmpDir, "arith.pbc")

	prog := `local n a = 3
local n b = 5
local n c = a + b
`
	err := os.WriteFile(paxoFile, []byte(prog), 0644)
	if err != nil {
		t.Fatal(err)
	}

	err = Compile(paxoFile, pbcFile, false)
	if err != nil {
		t.Fatalf("Compile arithmetic program failed: %v", err)
	}

	data, err := os.ReadFile(pbcFile)
	if err != nil {
		t.Fatal(err)
	}

	storeCount := 0
	for _, b := range data {
		if b == OP_STORE_VAR {
			storeCount++
		}
	}
	if storeCount != 3 {
		t.Errorf("Expected 3 OP_STORE_VAR, got %d", storeCount)
	}
}

func TestCompileIncrement(t *testing.T) {
	tmpDir := t.TempDir()
	paxoFile := filepath.Join(tmpDir, "inc.paxo")
	pbcFile := filepath.Join(tmpDir, "inc.pbc")

	prog := `local n x = 0
x++
`
	err := os.WriteFile(paxoFile, []byte(prog), 0644)
	if err != nil {
		t.Fatal(err)
	}

	err = Compile(paxoFile, pbcFile, false)
	if err != nil {
		t.Fatalf("Compile increment failed: %v", err)
	}

	data, err := os.ReadFile(pbcFile)
	if err != nil {
		t.Fatal(err)
	}

	hasInc := false
	for _, b := range data {
		if b == OP_INC {
			hasInc = true
			break
		}
	}
	if !hasInc {
		t.Error("Expected OP_INC in bytecode")
	}
}

func TestCompileDecrement(t *testing.T) {
	tmpDir := t.TempDir()
	paxoFile := filepath.Join(tmpDir, "dec.paxo")
	pbcFile := filepath.Join(tmpDir, "dec.pbc")

	prog := `local n x = 10
x--
`
	err := os.WriteFile(paxoFile, []byte(prog), 0644)
	if err != nil {
		t.Fatal(err)
	}

	err = Compile(paxoFile, pbcFile, false)
	if err != nil {
		t.Fatalf("Compile decrement failed: %v", err)
	}

	data, err := os.ReadFile(pbcFile)
	if err != nil {
		t.Fatal(err)
	}

	hasDec := false
	for _, b := range data {
		if b == OP_DEC {
			hasDec = true
			break
		}
	}
	if !hasDec {
		t.Error("Expected OP_DEC in bytecode")
	}
}

func TestCompileComparison(t *testing.T) {
	tmpDir := t.TempDir()
	paxoFile := filepath.Join(tmpDir, "cmp.paxo")
	pbcFile := filepath.Join(tmpDir, "cmp.pbc")

	prog := `local n a = 5
local n b = 3
local bool r = a > b
`
	err := os.WriteFile(paxoFile, []byte(prog), 0644)
	if err != nil {
		t.Fatal(err)
	}

	err = Compile(paxoFile, pbcFile, false)
	if err != nil {
		t.Fatalf("Compile comparison failed: %v", err)
	}

	data, err := os.ReadFile(pbcFile)
	if err != nil {
		t.Fatal(err)
	}

	hasGt := false
	for _, b := range data {
		if b == OP_GT {
			hasGt = true
			break
		}
	}
	if !hasGt {
		t.Error("Expected OP_GT in bytecode")
	}
}

func TestCompileBooleanLogic(t *testing.T) {
	tmpDir := t.TempDir()
	paxoFile := filepath.Join(tmpDir, "logic.paxo")
	pbcFile := filepath.Join(tmpDir, "logic.pbc")

	prog := `local bool x = .✓
local bool y = .×
local bool r = x .& y
`
	err := os.WriteFile(paxoFile, []byte(prog), 0644)
	if err != nil {
		t.Fatal(err)
	}

	err = Compile(paxoFile, pbcFile, false)
	if err != nil {
		t.Fatalf("Compile boolean logic failed: %v", err)
	}

	data, err := os.ReadFile(pbcFile)
	if err != nil {
		t.Fatal(err)
	}

	hasAnd := false
	for _, b := range data {
		if b == OP_AND {
			hasAnd = true
			break
		}
	}
	if !hasAnd {
		t.Error("Expected OP_AND in bytecode")
	}
}

func TestCompilePrintCall(t *testing.T) {
	tmpDir := t.TempDir()
	paxoFile := filepath.Join(tmpDir, "print.paxo")
	pbcFile := filepath.Join(tmpDir, "print.pbc")

	prog := `local n x = 42
println(x);
`
	err := os.WriteFile(paxoFile, []byte(prog), 0644)
	if err != nil {
		t.Fatal(err)
	}

	err = Compile(paxoFile, pbcFile, false)
	if err != nil {
		t.Fatalf("Compile print failed: %v", err)
	}

	data, err := os.ReadFile(pbcFile)
	if err != nil {
		t.Fatal(err)
	}

	hasCallNative := false
	for _, b := range data {
		if b == OP_CALL_NATIVE {
			hasCallNative = true
			break
		}
	}
	if !hasCallNative {
		t.Error("Expected OP_CALL_NATIVE in bytecode")
	}
}

func TestCompileBitwise(t *testing.T) {
	tmpDir := t.TempDir()
	paxoFile := filepath.Join(tmpDir, "bit.paxo")
	pbcFile := filepath.Join(tmpDir, "bit.pbc")

	prog := `local n a = 5
local n b = 3
local n c = a & b
`
	err := os.WriteFile(paxoFile, []byte(prog), 0644)
	if err != nil {
		t.Fatal(err)
	}

	err = Compile(paxoFile, pbcFile, false)
	if err != nil {
		t.Fatalf("Compile bitwise failed: %v", err)
	}

	data, err := os.ReadFile(pbcFile)
	if err != nil {
		t.Fatal(err)
	}

	hasBitAnd := false
	for _, b := range data {
		if b == OP_BIT_AND {
			hasBitAnd = true
			break
		}
	}
	if !hasBitAnd {
		t.Error("Expected OP_BIT_AND in bytecode")
	}
}

func TestCompileCharLiteral(t *testing.T) {
	tmpDir := t.TempDir()
	paxoFile := filepath.Join(tmpDir, "char.paxo")
	pbcFile := filepath.Join(tmpDir, "char.pbc")

	prog := `local abc c = 'A'
`
	err := os.WriteFile(paxoFile, []byte(prog), 0644)
	if err != nil {
		t.Fatal(err)
	}

	err = Compile(paxoFile, pbcFile, false)
	if err != nil {
		t.Fatalf("Compile char literal failed: %v", err)
	}

	data, err := os.ReadFile(pbcFile)
	if err != nil {
		t.Fatal(err)
	}

	hasPushChar := false
	for i := 0; i < len(data)-1; i++ {
		if data[i] == OP_PUSH && data[i+1] == TYPE_CHAR {
			hasPushChar = true
			break
		}
	}
	if !hasPushChar {
		t.Error("Expected PUSH CHAR in bytecode")
	}
}

func TestOpcodeValues(t *testing.T) {
	if OP_PUSH != 0 {
		t.Errorf("OP_PUSH should be 0, got %d", OP_PUSH)
	}
	if OP_HALT != 13 {
		t.Errorf("OP_HALT should be 13, got %d", OP_HALT)
	}
	if OP_ADD != 2 {
		t.Errorf("OP_ADD should be 2, got %d", OP_ADD)
	}
	if OP_DEC != 32 {
		t.Errorf("OP_DEC should be 32, got %d", OP_DEC)
	}
}

func TestTypeValues(t *testing.T) {
	if TYPE_NUM16 != 0 {
		t.Errorf("TYPE_NUM16 should be 0, got %d", TYPE_NUM16)
	}
	if TYPE_NUM64 != 1 {
		t.Errorf("TYPE_NUM64 should be 1, got %d", TYPE_NUM64)
	}
	if TYPE_BOOL != 4 {
		t.Errorf("TYPE_BOOL should be 4, got %d", TYPE_BOOL)
	}
}

func TestNewCodeGen(t *testing.T) {
	cg := NewCodeGen()
	if cg == nil {
		t.Fatal("NewCodeGen returned nil")
	}
	if len(cg.Code()) != 0 {
		t.Error("New code gen should have empty code")
	}
	if len(cg.Errors()) != 0 {
		t.Error("New code gen should have no errors")
	}
	if len(cg.locals) != 0 {
		t.Error("New code gen should have no locals")
	}
}

func TestVarDefaultIsNum64(t *testing.T) {
	tmpDir := t.TempDir()
	paxoFile := filepath.Join(tmpDir, "vardefault.paxo")
	pbcFile := filepath.Join(tmpDir, "vardefault.pbc")

	prog := `local var x
`
	err := os.WriteFile(paxoFile, []byte(prog), 0644)
	if err != nil {
		t.Fatal(err)
	}

	err = Compile(paxoFile, pbcFile, false)
	if err != nil {
		t.Fatalf("Compile var default failed: %v", err)
	}

	data, err := os.ReadFile(pbcFile)
	if err != nil {
		t.Fatal(err)
	}

	hasPushNum64 := false
	for i := 0; i < len(data)-1; i++ {
		if data[i] == OP_PUSH && data[i+1] == TYPE_NUM64 {
			hasPushNum64 = true
			break
		}
	}
	if !hasPushNum64 {
		t.Error("Expected PUSH NUM64 for var default type (uninitialized)")
	}
}

func TestCompileExplicitTypes(t *testing.T) {
	tests := []struct {
		name  string
		prog  string
		typ   byte
		check byte
	}{
		{"n", "local n x = 5\n", TYPE_NUM64, OP_STORE_VAR},
		{"sn", "local sn x = 300\n", TYPE_NUM16, OP_STORE_VAR},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			tmpDir := t.TempDir()
			paxoFile := filepath.Join(tmpDir, tt.name+".paxo")
			pbcFile := filepath.Join(tmpDir, tt.name+".pbc")

			err := os.WriteFile(paxoFile, []byte(tt.prog), 0644)
			if err != nil {
				t.Fatal(err)
			}

			err = Compile(paxoFile, pbcFile, false)
			if err != nil {
				t.Fatalf("Compile %s failed: %v", tt.name, err)
			}

			data, err := os.ReadFile(pbcFile)
			if err != nil {
				t.Fatal(err)
			}

			hasType := false
			for i := 0; i < len(data)-1; i++ {
				if data[i] == OP_PUSH && data[i+1] == tt.typ {
					hasType = true
					break
				}
			}
			if !hasType {
				t.Errorf("Expected PUSH %s in bytecode for type %s", tt.name, tt.name)
			}
		})
	}
}
