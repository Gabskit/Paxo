package parser

import (
	"fmt"
	"os"
	"strconv"
	"strings"

	"github.com/antlr4-go/antlr/v4"
)

// ==========================================
// OPCODES — deben coincidir con Vm.c
// ==========================================
const (
	OP_PUSH          byte = 0
	OP_POP           byte = 1
	OP_ADD           byte = 2
	OP_SUB           byte = 3
	OP_MUL           byte = 4
	OP_DIV           byte = 5
	OP_CAST          byte = 6
	OP_LOAD_VAR      byte = 7
	OP_STORE_VAR     byte = 8
	OP_PRINT         byte = 9
	OP_JUMP          byte = 10
	OP_JUMP_IF_FALSE byte = 11
	OP_JUMP_IF_TRUE  byte = 12
	OP_HALT          byte = 13
	OP_CALL          byte = 14
	OP_CALL_NATIVE   byte = 15
	OP_EQ            byte = 16
	OP_NEQ           byte = 17
	OP_LT            byte = 18
	OP_GT            byte = 19
	OP_LTE           byte = 20
	OP_GTE           byte = 21
	OP_AND           byte = 22
	OP_OR            byte = 23
	OP_NOT           byte = 24
	OP_BIT_AND       byte = 25
	OP_BIT_OR        byte = 26
	OP_BIT_NOT       byte = 27
	OP_BIT_XOR       byte = 28
	OP_BIT_SHL       byte = 29
	OP_BIT_SHR       byte = 30
	OP_INC           byte = 31
	OP_DEC           byte = 32
	OP_RETURN        byte = 33
	OP_CALL_VAR      byte = 34
	OP_ARRAY_NEW     byte = 35
	OP_ARRAY_GET     byte = 36
	OP_ARRAY_SET     byte = 37
	OP_PKG_NEW       byte = 38
	OP_PKG_GET       byte = 39
	OP_PKG_SET       byte = 40
	OP_TRY_SETUP     byte = 41
	OP_TRY_END       byte = 42
	OP_THROW         byte = 43
	OP_STORE_LOCAL   byte = 44
	OP_LOAD_LOCAL    byte = 45
)

const (
	TYPE_NUM16  byte = 0
	TYPE_NUM64  byte = 1
	TYPE_CHAR   byte = 2
	TYPE_TRIT   byte = 3
	TYPE_BOOL   byte = 4
	TYPE_POINT  byte = 5
	TYPE_FUNC   byte = 6
	TYPE_STRING byte = 7
	TYPE_ARRAY  byte = 8
	TYPE_PKG    byte = 9
	TYPE_INT    byte = 10
	TYPE_PKDEC  byte = 11
	TYPE_COLOR  byte = 12
	TYPE_COMPLEX  byte = 13
	TYPE_COMPLEX16 byte = 14
)

const (
	NATIVE_PRINT          uint16 = 0
	NATIVE_PRINTLN        uint16 = 1
	NATIVE_TYPEOF         uint16 = 2
	NATIVE_SET_COLOR_TEXT uint16 = 3
	NATIVE_SET_TYPE_TEXT  uint16 = 4
	NATIVE_SET_COLOR_BACK uint16 = 5
	NATIVE_RESET_COLOR    uint16 = 6
	NATIVE_SCAN           uint16 = 7
	NATIVE_ARRAY_LEN      uint16 = 8
	NATIVE_ARRAY_PUSH     uint16 = 9

	// Nuevas funciones gráficas
	NATIVE_INIT_WINDOW  uint16 = 10
	NATIVE_CLEAR_SCREEN uint16 = 11
	NATIVE_DRAW_RECT    uint16 = 12

	// Manejo de archivos
	NATIVE_FILE_READ   uint16 = 13
	NATIVE_FILE_WRITE  uint16 = 14
	NATIVE_FILE_APPEND uint16 = 15
	NATIVE_FILE_EXISTS uint16 = 16
	NATIVE_FILE_DELETE uint16 = 17

	// Imágenes (stb)
	NATIVE_IMG_LOAD     uint16 = 18
	NATIVE_IMG_INFO     uint16 = 19
	NATIVE_IMG_SAVE_PNG uint16 = 20
	NATIVE_IMG_SAVE_JPG uint16 = 21
	NATIVE_IMG_SAVE_BMP uint16 = 22
	NATIVE_IMG_RESIZE   uint16 = 23

	// Fuentes (stb_truetype)
	NATIVE_FONT_LOAD    uint16 = 24
	NATIVE_FONT_GLYPH   uint16 = 25
	NATIVE_FONT_METRICS uint16 = 26
	NATIVE_FONT_FREE    uint16 = 27

	// Audio (miniaudio)
	NATIVE_AUDIO_INIT    uint16 = 28
	NATIVE_AUDIO_QUIT    uint16 = 29
	NATIVE_AUDIO_PLAY    uint16 = 30
	NATIVE_AUDIO_PAUSE   uint16 = 31
	NATIVE_AUDIO_RESUME  uint16 = 32
	NATIVE_AUDIO_STOP    uint16 = 33
	NATIVE_AUDIO_VOLUME  uint16 = 34
	NATIVE_AUDIO_PLAYING uint16 = 35

	// Física (Chipmunk2D)
	NATIVE_PHYS_SPACE       uint16 = 36
	NATIVE_PHYS_GRAVITY     uint16 = 37
	NATIVE_PHYS_STEP        uint16 = 38
	NATIVE_PHYS_BODY        uint16 = 39
	NATIVE_PHYS_BODY_STATIC uint16 = 40
	NATIVE_PHYS_POS         uint16 = 41
	NATIVE_PHYS_VEL         uint16 = 42
	NATIVE_PHYS_SET_POS     uint16 = 43
	NATIVE_PHYS_SET_VEL     uint16 = 44
	NATIVE_PHYS_ANGLE       uint16 = 45
	NATIVE_PHYS_SET_ANGLE   uint16 = 46
	NATIVE_PHYS_FORCE       uint16 = 47
	NATIVE_PHYS_IMPULSE     uint16 = 48
	NATIVE_PHYS_CIRCLE      uint16 = 49
	NATIVE_PHYS_BOX         uint16 = 50
	NATIVE_PHYS_SEGMENT     uint16 = 51
	NATIVE_PHYS_ELASTICITY  uint16 = 52
	NATIVE_PHYS_FRICTION    uint16 = 53
	NATIVE_PHYS_COLLIDE     uint16 = 54
	NATIVE_PHYS_FREE_SHAPE  uint16 = 55
	NATIVE_PHYS_FREE_BODY   uint16 = 56
	NATIVE_PHYS_FREE_SPACE  uint16 = 57

	// Ventana/gráficos (SDL3, opcional)
	NATIVE_WIN_OPEN      uint16 = 58
	NATIVE_WIN_CLOSE     uint16 = 59
	NATIVE_WIN_COLOR     uint16 = 60
	NATIVE_WIN_CLEAR     uint16 = 61
	NATIVE_WIN_RECT      uint16 = 62
	NATIVE_WIN_LINE      uint16 = 63
	NATIVE_WIN_CIRCLE    uint16 = 64
	NATIVE_WIN_TEXT      uint16 = 65
	NATIVE_TEX_LOAD      uint16 = 66
	NATIVE_TEX_DRAW      uint16 = 67
	NATIVE_TEX_FREE      uint16 = 68
	NATIVE_WIN_SHOW      uint16 = 69
	NATIVE_WIN_POLL      uint16 = 70
	NATIVE_WIN_KEY       uint16 = 71
	NATIVE_WIN_MOUSE     uint16 = 72
	NATIVE_WIN_MOUSEDOWN uint16 = 73
	NATIVE_WIN_TIME      uint16 = 74
	NATIVE_WIN_DELAY     uint16 = 75

	// PDF (pdfio)
	NATIVE_PDF_OPEN       uint16 = 76
	NATIVE_PDF_NEW        uint16 = 77
	NATIVE_PDF_PAGES      uint16 = 78
	NATIVE_PDF_PAGE_SIZE  uint16 = 79
	NATIVE_PDF_TEXT       uint16 = 80
	NATIVE_PDF_FONT       uint16 = 81
	NATIVE_PDF_PAGE_BEGIN uint16 = 82
	NATIVE_PDF_COLOR      uint16 = 83
	NATIVE_PDF_WRITE_RECT uint16 = 84
	NATIVE_PDF_WRITE_LINE uint16 = 85
	NATIVE_PDF_WRITE_TEXT uint16 = 86
	NATIVE_PDF_CLOSE      uint16 = 87
)

// nativeNames mapea los nombres de funciones nativas del lenguaje a su ID.
// Debe mantenerse en sincronía con el enum NativeId de Functions.c (VM).
var nativeNames = map[string]uint16{
	"print":        NATIVE_PRINT,
	"println":      NATIVE_PRINTLN,
	"typeof":       NATIVE_TYPEOF,
	"text_color":   NATIVE_SET_COLOR_TEXT,
	"text_type":    NATIVE_SET_TYPE_TEXT,
	"bg_color":     NATIVE_SET_COLOR_BACK,
	"reset_color":  NATIVE_RESET_COLOR,
	"scan":         NATIVE_SCAN,
	"array_len":    NATIVE_ARRAY_LEN,
	"array_push":   NATIVE_ARRAY_PUSH,
	"init_window":  NATIVE_INIT_WINDOW,
	"clear_screen": NATIVE_CLEAR_SCREEN,
	"draw_rect":    NATIVE_DRAW_RECT,
	"file_read":    NATIVE_FILE_READ,
	"file_write":   NATIVE_FILE_WRITE,
	"file_append":  NATIVE_FILE_APPEND,
	"file_exists":  NATIVE_FILE_EXISTS,
	"file_delete":  NATIVE_FILE_DELETE,

	"img_load":     NATIVE_IMG_LOAD,
	"img_info":     NATIVE_IMG_INFO,
	"img_save_png": NATIVE_IMG_SAVE_PNG,
	"img_save_jpg": NATIVE_IMG_SAVE_JPG,
	"img_save_bmp": NATIVE_IMG_SAVE_BMP,
	"img_resize":   NATIVE_IMG_RESIZE,

	"font_load":    NATIVE_FONT_LOAD,
	"font_glyph":   NATIVE_FONT_GLYPH,
	"font_metrics": NATIVE_FONT_METRICS,
	"font_free":    NATIVE_FONT_FREE,

	"audio_init":    NATIVE_AUDIO_INIT,
	"audio_quit":    NATIVE_AUDIO_QUIT,
	"audio_play":    NATIVE_AUDIO_PLAY,
	"audio_pause":   NATIVE_AUDIO_PAUSE,
	"audio_resume":  NATIVE_AUDIO_RESUME,
	"audio_stop":    NATIVE_AUDIO_STOP,
	"audio_volume":  NATIVE_AUDIO_VOLUME,
	"audio_playing": NATIVE_AUDIO_PLAYING,

	"phys_space":       NATIVE_PHYS_SPACE,
	"phys_gravity":     NATIVE_PHYS_GRAVITY,
	"phys_step":        NATIVE_PHYS_STEP,
	"phys_body":        NATIVE_PHYS_BODY,
	"phys_body_static": NATIVE_PHYS_BODY_STATIC,
	"phys_pos":         NATIVE_PHYS_POS,
	"phys_vel":         NATIVE_PHYS_VEL,
	"phys_set_pos":     NATIVE_PHYS_SET_POS,
	"phys_set_vel":     NATIVE_PHYS_SET_VEL,
	"phys_angle":       NATIVE_PHYS_ANGLE,
	"phys_set_angle":   NATIVE_PHYS_SET_ANGLE,
	"phys_force":       NATIVE_PHYS_FORCE,
	"phys_impulse":     NATIVE_PHYS_IMPULSE,
	"phys_circle":      NATIVE_PHYS_CIRCLE,
	"phys_box":         NATIVE_PHYS_BOX,
	"phys_segment":     NATIVE_PHYS_SEGMENT,
	"phys_elasticity":  NATIVE_PHYS_ELASTICITY,
	"phys_friction":    NATIVE_PHYS_FRICTION,
	"phys_collide":     NATIVE_PHYS_COLLIDE,
	"phys_free_shape":  NATIVE_PHYS_FREE_SHAPE,
	"phys_free_body":   NATIVE_PHYS_FREE_BODY,
	"phys_free_space":  NATIVE_PHYS_FREE_SPACE,

	"win_open":      NATIVE_WIN_OPEN,
	"win_close":     NATIVE_WIN_CLOSE,
	"win_color":     NATIVE_WIN_COLOR,
	"win_clear":     NATIVE_WIN_CLEAR,
	"win_rect":      NATIVE_WIN_RECT,
	"win_line":      NATIVE_WIN_LINE,
	"win_circle":    NATIVE_WIN_CIRCLE,
	"win_text":      NATIVE_WIN_TEXT,
	"tex_load":      NATIVE_TEX_LOAD,
	"tex_draw":      NATIVE_TEX_DRAW,
	"tex_free":      NATIVE_TEX_FREE,
	"win_show":      NATIVE_WIN_SHOW,
	"win_poll":      NATIVE_WIN_POLL,
	"win_key":       NATIVE_WIN_KEY,
	"win_mouse":     NATIVE_WIN_MOUSE,
	"win_mousedown": NATIVE_WIN_MOUSEDOWN,
	"win_time":      NATIVE_WIN_TIME,
	"win_delay":     NATIVE_WIN_DELAY,

	"pdf_open":       NATIVE_PDF_OPEN,
	"pdf_new":        NATIVE_PDF_NEW,
	"pdf_pages":      NATIVE_PDF_PAGES,
	"pdf_page_size":  NATIVE_PDF_PAGE_SIZE,
	"pdf_text":       NATIVE_PDF_TEXT,
	"pdf_font":       NATIVE_PDF_FONT,
	"pdf_page_begin": NATIVE_PDF_PAGE_BEGIN,
	"pdf_color":      NATIVE_PDF_COLOR,
	"pdf_write_rect": NATIVE_PDF_WRITE_RECT,
	"pdf_write_line": NATIVE_PDF_WRITE_LINE,
	"pdf_write_text": NATIVE_PDF_WRITE_TEXT,
	"pdf_close":      NATIVE_PDF_CLOSE,
}

// ==========================================
// EMITTER
// ==========================================
type Emitter struct {
	code []byte
	caps [][]byte
}

// cur retorna el stream de salida activo (código principal o el buffer
// de captura más reciente). Las posiciones y parches de saltos siempre
// son consistentes dentro del mismo stream.
func (e *Emitter) cur() *[]byte {
	if n := len(e.caps); n > 0 {
		return &e.caps[n-1]
	}
	return &e.code
}

func (e *Emitter) emit(b byte) {
	if n := len(e.caps); n > 0 {
		e.caps[n-1] = append(e.caps[n-1], b)
	} else {
		e.code = append(e.code, b)
	}
}
func (e *Emitter) emit16(v uint16) { e.emit(byte(v)); e.emit(byte(v >> 8)) }
func (e *Emitter) emitI16(v int16) { e.emit(byte(v)); e.emit(byte(v >> 8)) }
func (e *Emitter) patchI16(off int, val int16) {
	buf := *e.cur()
	buf[off] = byte(val)
	buf[off+1] = byte(val >> 8)
}
func (e *Emitter) pos() int { return len(*e.cur()) }

func (e *Emitter) pushBool(val bool) {
	e.emit(OP_PUSH)
	e.emit(TYPE_BOOL)
	if val {
		e.emit(1)
	} else {
		e.emit(0)
	}
}
func (e *Emitter) pushChar(val uint8) { e.emit(OP_PUSH); e.emit(TYPE_CHAR); e.emit(val) }

func (e *Emitter) pushFunc(offset uint16, paramCount uint8) {
	e.emit(OP_PUSH)
	e.emit(TYPE_FUNC)
	e.emit16(offset)
	e.emit(paramCount)
}

func (e *Emitter) pushString(val string) {
	e.emit(OP_PUSH)
	e.emit(TYPE_STRING)
	inner := val[1 : len(val)-1] // strip quotes
	e.emit16(uint16(len(inner)))
	for i := 0; i < len(inner); i++ {
		e.emit(byte(inner[i]))
	}
	e.emit(0) // null terminator
}

// Emite un valor de punto fijo / decimal empaquetado (signo + escala + entero
// escalado). comparte el mismo layout de bytecode, solo cambia el tipo.
func (e *Emitter) pushScaled(typ byte, val string) {
	neg := false
	s := val
	if strings.HasPrefix(s, "+") {
		s = s[1:]
	} else if strings.HasPrefix(s, "-") {
		neg = true
		s = s[1:]
	}

	parts := strings.SplitN(s, ".", 2)
	intPart := parts[0]
	fracPart := ""
	if len(parts) > 1 {
		fracPart = parts[1]
	}

	digits := intPart + fracPart
	if digits == "" {
		digits = "0"
	}
	num, err := strconv.ParseInt(digits, 10, 64)
	if err != nil {
		num = 0
	}
	if neg {
		num = -num
	}

	e.emit(OP_PUSH)
	e.emit(typ)
	e.emit(byte(len(fracPart) & 0xFF)) // escala (dígitos fraccionarios)
	v16 := int16(num)
	e.emit(byte(v16))
	e.emit(byte(v16 >> 8))
}

func (e *Emitter) pushInt(val string) { e.pushScaled(TYPE_INT, val) }
func (e *Emitter) pushDec(val string) { e.pushScaled(TYPE_PKDEC, val) }

// pushColor emite un literal de color '#RRGGBB' o '#RRGGBBAA'.
func (e *Emitter) pushColor(hex string) {
	r, g, b, a := 0, 0, 0, 255
	h := strings.TrimPrefix(hex, "#")
	if len(h) >= 6 {
		if v, err := strconv.ParseUint(h[0:2], 16, 8); err == nil {
			r = int(v)
		}
		if v, err := strconv.ParseUint(h[2:4], 16, 8); err == nil {
			g = int(v)
		}
		if v, err := strconv.ParseUint(h[4:6], 16, 8); err == nil {
			b = int(v)
		}
		if len(h) >= 8 {
			if v, err := strconv.ParseUint(h[6:8], 16, 8); err == nil {
				a = int(v)
			}
		}
	}
	e.emit(OP_PUSH)
	e.emit(TYPE_COLOR)
	e.emit(byte(r))
	e.emit(byte(g))
	e.emit(byte(b))
	e.emit(byte(a))
}

// Codifica un valor en el formato MP16 radix mixto: v = bc·2^(-2p)·10^(s)
// con s = exp-BIAS. Busca ajuste EXACTO probando la década menor y dentro
// de ella la celda más dividida (p desc); si no existe toma el más
// cercano (menor error por comparación cruzada, empate lejos de cero).
func (e *Emitter) emitRaw16(val uint64, signo uint16) {
	pow4 := [6]uint64{1, 4, 16, 64, 256, 1024}
	pow10 := [3]uint64{1, 10, 100}

	bc, p, s := val, uint64(0), uint64(0)
	ok := false
	for si := uint64(0); si <= 2 && !ok; si++ {
		for pi := uint64(5); ; pi-- {
			num := val * pow4[pi]
			if num%pow10[si] == 0 {
				b := num / pow10[si]
				if b >= 1 && b <= 1023 {
					bc, p, s, ok = b, pi, si, true
					break
				}
			}
			if pi == 0 {
				break
			}
		}
	}
	if !ok {
		// el más cercano: mínimo error relativo a su década
		bestErr := uint64(1) << 62
		for si := uint64(0); si <= 2; si++ {
			for pi := uint64(0); pi <= 5; pi++ {
				num := val * pow4[pi]
				den := pow10[si]
				q := num / den
				r := num % den
				if q < 1 || q > 1023 {
					continue
				}
				err := r
				if den-r < err {
					err = den - r
				}
				l, rr := err*pow10[s], bestErr*pow10[si]
				if l < rr || (l == rr && q > bc) {
					bestErr, bc, p, s = err, q, pi, si
				}
			}
		}
	}
	raw := (uint16(p) << 13) | (uint16(bc) << 3) | (uint16(s+1) << 1) | signo
	e.emit(byte(raw))
	e.emit(byte(raw >> 8))
}

func (e *Emitter) pushNum16(val uint16) {
	e.emit(OP_PUSH)
	e.emit(TYPE_NUM16)
	e.emitRaw16(uint64(val), 0)
}

func (e *Emitter) pushNum16Signed(val int64) {
	e.emit(OP_PUSH)
	e.emit(TYPE_NUM16)
	signo := uint16(0)
	if val < 0 {
		signo = 1
		val = -val
	}
	e.emitRaw16(uint64(uint16(val)), signo)
}

func (e *Emitter) pushNum64(val uint64) {
	e.emit(OP_PUSH)
	e.emit(TYPE_NUM64)
	var p uint64
	var signo uint64
	exp := uint64(127) // bias de Num64 = 127
	bc := val
	for bc > 1125899906842623 { // 2^50 - 1
		bc /= 10
		exp++
	}
	raw := (p << 59) | (bc << 9) | (exp << 1) | signo
	e.emit(byte(raw))
	e.emit(byte(raw >> 8))
	e.emit(byte(raw >> 16))
	e.emit(byte(raw >> 24))
	e.emit(byte(raw >> 32))
	e.emit(byte(raw >> 40))
	e.emit(byte(raw >> 48))
	e.emit(byte(raw >> 56))
}

func (e *Emitter) pushNum64Signed(val int64) {
	e.emit(OP_PUSH)
	e.emit(TYPE_NUM64)
	var p uint64
	signo := uint64(0)
	if val < 0 {
		signo = 1
		val = -val
	}
	exp := uint64(127) // bias de Num64 = 127
	bc := uint64(val)
	for bc > 1125899906842623 { // 2^50 - 1
		bc /= 10
		exp++
	}
	raw := (p << 59) | (bc << 9) | (exp << 1) | signo
	e.emit(byte(raw))
	e.emit(byte(raw >> 8))
	e.emit(byte(raw >> 16))
	e.emit(byte(raw >> 24))
	e.emit(byte(raw >> 32))
	e.emit(byte(raw >> 40))
	e.emit(byte(raw >> 48))
	e.emit(byte(raw >> 56))
}

func (e *Emitter) pushNum64Float(val float64) {
	e.emit(OP_PUSH)
	e.emit(TYPE_NUM64)
	signo := uint64(0)
	if val < 0 {
		signo = 1
		val = -val
	}
	exp := uint64(127) // bias de Num64 = 127
	// Convertir a representación base-10: val = bc × 10^(exp - bias - p)
	// Usamos p=4 como precisión fraccionaria para decimales
	const fracDigits = 4
	bcFloat := val
	for i := 0; i < fracDigits; i++ {
		bcFloat *= 10.0
	}
	bc := uint64(bcFloat)
	for bc > 1125899906842623 { // 2^50 - 1
		bc /= 10
		exp++
	}
	raw := (uint64(fracDigits) << 59) | (bc << 9) | (exp << 1) | signo
	e.emit(byte(raw))
	e.emit(byte(raw >> 8))
	e.emit(byte(raw >> 16))
	e.emit(byte(raw >> 24))
	e.emit(byte(raw >> 32))
	e.emit(byte(raw >> 40))
	e.emit(byte(raw >> 48))
	e.emit(byte(raw >> 56))
}

// Codifica un float64 a los 8 bytes de un componente Num64 (MP64) en el
// formato que espera la VM (mismo layout que pushNum64Float, sin op/tipo):
// raw = (p<<59) | (bc<<9) | (exp<<1) | signo, con p=4 dígitos fraccionarios.
func rawNum64(val float64) [8]byte {
	var raw [8]byte
	signo := uint64(0)
	if val < 0 {
		signo = 1
		val = -val
	}
	exp := uint64(127)
	const fracDigits = 4
	bcFloat := val
	for i := 0; i < fracDigits; i++ {
		bcFloat *= 10.0
	}
	bc := uint64(bcFloat)
	for bc > 1125899906842623 { // 2^50 - 1
		bc /= 10
		exp++
	}
	r := (uint64(fracDigits) << 59) | (bc << 9) | (exp << 1) | signo
	for i := 0; i < 8; i++ {
		raw[i] = byte(r >> (i * 8))
	}
	return raw
}

// Emite un literal complejo: OP_PUSH, TYPE_COMPLEX y dos componentes Num64
// crudos (re, im). Cada número se interpreta con su signo propio.
func (e *Emitter) pushComplex(re, im string) {
	e.emit(OP_PUSH)
	e.emit(TYPE_COMPLEX)
	reV, err := strconv.ParseFloat(re, 64)
	if err != nil {
		reV = 0
	}
	imV, err := strconv.ParseFloat(im, 64)
	if err != nil {
		imV = 0
	}
	for _, b := range rawNum64(reV) {
		e.emit(b)
	}
	for _, b := range rawNum64(imV) {
		e.emit(b)
	}
}

// Separa un literal complejo ("3+4i", "-2+3.5i", "+3i") en (real, imaginaria).
// La parte imaginaria siempre lleva su propio signo y es la última: todo lo
// anterior al último '+'/'-' es la parte real (puede faltar).
func parseComplexLiteral(text string) (re, im string) {
	s := strings.TrimSuffix(text, "i")
	lastSign := -1
	for i := len(s) - 1; i >= 0; i-- {
		if s[i] == '+' || s[i] == '-' {
			lastSign = i
			break
		}
	}
	if lastSign < 0 {
		return "0", "0"
	}
	im = s[lastSign:]
	if im == "" || im == "+" || im == "-" {
		return "0", "0"
	}
	re = s[:lastSign]
	if re == "" {
		re = "0"
	}
	return re, im
}

// ==========================================
// HELPERS
// ==========================================
func tokText(node antlr.ParseTree) string {
	if tn, ok := node.(antlr.TerminalNode); ok {
		return tn.GetText()
	}
	return ""
}

func childTokText(ctx antlr.ParserRuleContext, idx int) string {
	if idx >= ctx.GetChildCount() {
		return ""
	}
	child := ctx.GetChild(idx)
	if tn, ok := child.(antlr.TerminalNode); ok {
		return tn.GetText()
	}
	return ""
}

// ==========================================
// CODE GENERATOR
// ==========================================
// pkgField es un campo de package: 'local' lo marca privado (encapsulamiento),
// sin modificador o con 'pub' queda público.
type pkgField struct {
	name    string
	private bool
}

type CodeGen struct {
	*BasePaxoListener
	Emitter
	locals    map[string]uint16
	nextLocal uint16
	errors    []string
	warnings  []string

	varTypes     map[string]byte
	funcVarTypes map[string]byte

	inFunction         bool
	savedCode          []byte
	funcBodies         [][]byte
	funcPatchPositions []int
	funcParamCounts    []int

	funcLocals      map[string]uint16
	funcNextLocal   uint16
	savedFuncLocals map[string]uint16
	savedFuncNext   uint16

	// Condicionales (x ? v -> {} : ...): cada frame guarda el inicio del
	// statement en el stream activo, su variable temporal y los bloques
	// capturados por caso. caseOwner mapea cada bloque-caso a su frame.
	conds     []*condFrame
	caseOwner map[*BlockContext]*condFrame

	// Bucles anidados: cada frame guarda el inicio de su condición y el
	// parche del salto al final. pendingLoopBody marca que el próximo
	// bloque abierto es el cuerpo del bucle recién iniciado.
	loops           []loopFrame
	pendingLoopBody bool

	inPkg     bool
	pkgFields []pkgField

	inTryCatch       bool
	tryBlockCount    int
	tryCatchVarIdx   uint16
	catchOffsetPatch int
	tryCatchEndPatch int
}

func NewCodeGen() *CodeGen {
	return &CodeGen{
		BasePaxoListener: &BasePaxoListener{},
		Emitter:          Emitter{code: make([]byte, 0)},
		locals:           make(map[string]uint16),
		varTypes:         make(map[string]byte),
		funcVarTypes:     make(map[string]byte),
		caseOwner:        make(map[*BlockContext]*condFrame),
	}
}

func (cg *CodeGen) reportError(msg string) { cg.errors = append(cg.errors, msg) }
func (cg *CodeGen) reportWarning(msg string) {
	cg.warnings = append(cg.warnings, msg)
}
func (cg *CodeGen) Code() []byte       { return cg.code }
func (cg *CodeGen) Errors() []string   { return cg.errors }
func (cg *CodeGen) Warnings() []string { return cg.warnings }

func (cg *CodeGen) resolveIdent(name string) (idx uint16, isLocal bool, found bool) {
	if cg.inFunction {
		if i, ok := cg.funcLocals[name]; ok {
			return i, true, true
		}
	}
	if i, ok := cg.locals[name]; ok {
		return i, false, true
	}
	return 0, false, false
}

func (cg *CodeGen) resolveType(token string) byte {
	switch token {
	case "var", "📥":
		return TYPE_NUM64
	case "sn":
		return TYPE_NUM16
	case "n":
		return TYPE_NUM64
	case "abc":
		return TYPE_CHAR
	case "trit":
		return TYPE_TRIT
	case "bool":
		return TYPE_BOOL
	case "pin":
		return TYPE_POINT
	case "fx":
		return TYPE_FUNC
	case "pkg", "📦":
		return TYPE_PKG
	case "int":
		return TYPE_INT
	case "pdec":
		cg.reportWarning("el tipo 'pdec' (decimal empaquetado) está deprecado: " +
			"ya no garantiza números únicos sin error y quedará sin soporte. " +
			"Usa 'n' (mobile point) o 'var' en su lugar")
		return TYPE_PKDEC
	case "col":
		return TYPE_COLOR
	case "ni":
		return TYPE_COMPLEX
	case "sni":
		return TYPE_COMPLEX16
	default:
		cg.reportError("tipo desconocido: " + token)
		return TYPE_NUM64
	}
}

func (cg *CodeGen) walkTree(tree antlr.ParseTree) {
	antlr.ParseTreeWalkerDefault.Walk(cg, tree)
}

// ==========================================
// Program
// ==========================================
func (cg *CodeGen) ExitProgram(ctx *ProgramContext) {
	cg.emit(OP_HALT)

	funcStart := len(cg.code)
	offsets := make([]int, len(cg.funcBodies))
	running := funcStart
	for i, body := range cg.funcBodies {
		offsets[i] = running
		cg.code = append(cg.code, body...)
		running += len(body)
	}

	for i, pos := range cg.funcPatchPositions {
		offset := uint16(offsets[i])
		cg.code[pos] = byte(offset)
		cg.code[pos+1] = byte(offset >> 8)
	}
}

// ==========================================
// VarDeclaration
// ==========================================
func (cg *CodeGen) ExitVarDeclaration(ctx *VarDeclarationContext) {
	name := ctx.IDENTIFIER().GetText()

	if cg.inPkg {
		private := false
		if sc := ctx.Scope(); sc != nil && sc.GetStart().GetText() == "local" {
			private = true
		}
		cg.pkgFields = append(cg.pkgFields, pkgField{name: name, private: private})
		return
	}

	// Fuera de packages los modificadores de scope no hacen nada: deprecados.
	if sc := ctx.Scope(); sc != nil {
		token := sc.GetStart().GetText()
		msg := fmt.Sprintf("línea %d: el modificador de scope '%s' está deprecado y se ignora",
			sc.GetStart().GetLine(), token)
		if ctx.Type_() != nil {
			msg = fmt.Sprintf("línea %d: el modificador de scope '%s' está deprecado; escríbelo como '%s %s'",
				sc.GetStart().GetLine(), token, ctx.Type_().GetText(), name)
		}
		cg.reportWarning(msg)
	}

	var varType byte = TYPE_NUM64
	var isDynamic bool
	if ctx.Type_() != nil {
		token := ctx.Type_().GetStart().GetText()
		varType = cg.resolveType(token)
		isDynamic = (token == "var" || token == "📥")
	} else {
		isDynamic = true
	}

	var idx uint16
	var storeOp byte
	if cg.inFunction {
		idx = cg.funcNextLocal
		cg.funcLocals[name] = idx
		cg.funcNextLocal++
		storeOp = OP_STORE_LOCAL
		if !isDynamic {
			cg.funcVarTypes[name] = varType
		}
	} else {
		idx = cg.nextLocal
		cg.locals[name] = idx
		cg.nextLocal++
		storeOp = OP_STORE_VAR
		if !isDynamic {
			cg.varTypes[name] = varType
		}
	}

	if ctx.Expression() != nil {
		if ctx.Type_() != nil {
			token := ctx.Type_().GetStart().GetText()
			if token != "var" && token != "📥" {
				cg.emit(OP_CAST)
				cg.emit(varType)
			}
		}
		cg.emit(storeOp)
		cg.emit16(idx)
	} else if ctx.ArrayLiteral() != nil {
		cg.emitArrayLiteral(ctx.ArrayLiteral())
		cg.emit(storeOp)
		cg.emit16(idx)
	} else {
		switch varType {
		case TYPE_NUM16:
			cg.pushNum16(0)
		case TYPE_NUM64:
			cg.pushNum64(0)
		case TYPE_BOOL:
			cg.pushBool(false)
		case TYPE_CHAR:
			cg.pushChar(0)
		case TYPE_FUNC:
			cg.pushFunc(0, 0)
		case TYPE_INT:
			cg.pushInt("0")
		case TYPE_PKDEC:
			cg.pushDec("0.0")
		case TYPE_COLOR:
			cg.pushColor("#00000000")
		case TYPE_COMPLEX:
			cg.pushComplex("0", "0")
		case TYPE_COMPLEX16:
			cg.emit(OP_PUSH)
			cg.emit(TYPE_COMPLEX16)
			cg.emit16(0)
			cg.emit16(0)
		default:
			cg.pushNum64(0)
		}
		cg.emit(storeOp)
		cg.emit16(idx)
	}
}

// ==========================================
// Assignment
// ==========================================
func (cg *CodeGen) EnterAssignment(ctx *AssignmentContext) {
	exprs := ctx.AllExpression()
	if len(exprs) == 2 {
		name := ctx.IDENTIFIER().GetText()
		idx, isLocal, ok := cg.resolveIdent(name)
		if !ok {
			cg.reportError("variable no declarada: " + name)
			return
		}
		if isLocal {
			cg.emit(OP_LOAD_LOCAL)
		} else {
			cg.emit(OP_LOAD_VAR)
		}
		cg.emit16(idx)
	}
}

func (cg *CodeGen) ExitAssignment(ctx *AssignmentContext) {
	name := ctx.IDENTIFIER().GetText()
	idx, isLocal, ok := cg.resolveIdent(name)
	if !ok {
		cg.reportError("variable no declarada: " + name)
		return
	}

	storeOp := OP_STORE_VAR
	loadOp := OP_LOAD_VAR
	if isLocal {
		storeOp = OP_STORE_LOCAL
		loadOp = OP_LOAD_LOCAL
	}

	exprs := ctx.AllExpression()
	if len(exprs) == 2 {
		cg.emit(OP_ARRAY_SET)
	} else if len(exprs) == 1 {
		var varType byte
		found := false
		if isLocal {
			varType, found = cg.funcVarTypes[name]
		} else {
			varType, found = cg.varTypes[name]
		}
		if found {
			cg.emit(OP_CAST)
			cg.emit(varType)
		}
		cg.emit(storeOp)
		cg.emit16(idx)
	} else {
		cg.emit(loadOp)
		cg.emit16(idx)
		if childTokText(ctx, 1) == "++" {
			cg.emit(OP_INC)
		} else {
			cg.emit(OP_DEC)
		}
		cg.emit(storeOp)
		cg.emit16(idx)
	}
}

// ==========================================
// CondStatement
// ==========================================
// ==========================================
// CondStatement
// Layout por caso: [LOAD tmp][valor][EQ][JIF siguiente][bloque][JMP fin]
// ==========================================

type condFrame struct {
	start    int // posición del statement en el stream activo
	tmpVar   uint16
	localTmp bool     // true si el temporal vive en el frame de función (OP_*_LOCAL)
	blocks   [][]byte // bytecode capturado de cada caso, en orden
}

func caseBlockOf(mc IMatchCaseContext) *BlockContext {
	if blk := mc.Block(); blk != nil {
		if c, ok := blk.(*BlockContext); ok {
			return c
		}
	}
	return nil
}

func (cg *CodeGen) EnterCondStatement(ctx *CondStatementContext) {
	// La variable temporal se aloja al entrar (no al salir) para que los
	// condicionales anidados usen slots distintos y no se pisen en runtime.
	// Dentro de una función el temporal debe vivir en el frame local: si se
	// usara un slot global pisaría variables del llamador (p. ej. un contador
	// de bucle) en cuanto la función se invoque.
	f := &condFrame{start: cg.pos()}
	if cg.inFunction {
		f.tmpVar = cg.funcNextLocal
		f.localTmp = true
		cg.funcNextLocal++
	} else {
		f.tmpVar = cg.nextLocal
		cg.nextLocal++
	}
	for _, mc := range ctx.AllMatchCase() {
		if blk := caseBlockOf(mc); blk != nil {
			cg.caseOwner[blk] = f
		}
	}
	cg.conds = append(cg.conds, f)
}

// Layout lineal por caso: [LOAD tmp][valor][EQ][JIF siguiente][bloque][JMP fin]
// El wildcard (_) emite su bloque sin guard (siempre ejecuta).
func (cg *CodeGen) ExitCondStatement(ctx *CondStatementContext) {
	n := len(cg.conds)
	if n == 0 {
		return
	}
	f := cg.conds[n-1]
	cg.conds = cg.conds[:n-1]
	for _, mc := range ctx.AllMatchCase() {
		if blk := caseBlockOf(mc); blk != nil {
			delete(cg.caseOwner, blk)
		}
	}

	cases := ctx.AllMatchCase()
	out := cg.cur()
	*out = (*out)[:f.start]

	cg.walkTree(ctx.Expression())
	if f.localTmp {
		cg.emit(OP_STORE_LOCAL)
	} else {
		cg.emit(OP_STORE_VAR)
	}
	cg.emit16(f.tmpVar)

	var endPatches []int

	for i, mc := range cases {
		if i >= len(f.blocks) {
			break
		}
		if childTokText(mc, 0) == "_" {
			p := cg.cur()
			*p = append(*p, f.blocks[i]...)
			continue
		}
		if f.localTmp {
			cg.emit(OP_LOAD_LOCAL)
		} else {
			cg.emit(OP_LOAD_VAR)
		}
		cg.emit16(f.tmpVar)
		cg.walkTree(mc.Expression())
		cg.emit(OP_EQ)
		cg.emit(OP_JUMP_IF_FALSE)
		skipPatch := cg.pos()
		cg.emitI16(0)
		p := cg.cur()
		*p = append(*p, f.blocks[i]...)
		cg.emit(OP_JUMP)
		endPatch := cg.pos()
		cg.emitI16(0)
		cg.patchI16(skipPatch, int16(cg.pos()-skipPatch-2))
		endPatches = append(endPatches, endPatch)
	}

	for _, ep := range endPatches {
		cg.patchI16(ep, int16(cg.pos()-ep-2))
	}

	if f.localTmp {
		cg.funcNextLocal--
	} else {
		cg.nextLocal--
	}
}

// ==========================================
// LoopStatement
// Layout lineal: [cond][JIF fin][cuerpo][JMP cond]
// ==========================================

type loopFrame struct {
	condStart int
	jifEnd    int
	bodyBlock *BlockContext // bloque que abrió el cuerpo; su cierre cierra el bucle
}

func (cg *CodeGen) EnterLoopStatement(ctx *LoopStatementContext) {
	if ld := ctx.LoopDelimiter(); ld != nil {
		tok := ld.GetStart()
		cg.reportWarning(fmt.Sprintf(
			"línea %d: el delimitador de bucle '%s' está deprecado; usa el nuevo formato de bloque",
			tok.GetLine(), tok.GetText()))
	}
	cg.loops = append(cg.loops, loopFrame{condStart: cg.pos()})
	cg.pendingLoopBody = true
}

func (cg *CodeGen) ExitLoopStatement(ctx *LoopStatementContext) {
	// El cierre real ocurre en ExitBlock al cerrar el cuerpo; esto es
	// una red de seguridad por si el cuerpo nunca se abrió.
	if len(cg.loops) > 0 && !cg.pendingLoopBody {
		return
	}
	if len(cg.loops) > 0 {
		cg.loops = cg.loops[:len(cg.loops)-1]
	}
	cg.pendingLoopBody = false
}

// ==========================================
// Expression — literals + identifiers
// ==========================================
func (cg *CodeGen) EnterEveryRule(ctx antlr.ParserRuleContext) {}

func (cg *CodeGen) ExitEveryRule(ctx antlr.ParserRuleContext) {
	if _, ok := ctx.(IExpressionContext); ok {
		cg.handleBaseExpression(ctx)
	}
}

func (cg *CodeGen) handleBaseExpression(ctx antlr.ParserRuleContext) {
	switch expr := ctx.(type) {
	case *IntLitExprContext:
		text := expr.INT_LITERAL().GetText()
		val, err := strconv.ParseInt(text, 10, 64)
		if err != nil {
			cg.reportError("literal entero inválido: " + text)
			cg.pushNum64(0)
		} else if val < 0 {
			cg.pushNum64Signed(val)
		} else {
			cg.pushNum64(uint64(val))
		}
	case *DecLitExprContext:
		text := expr.DECIMAL_LITERAL().GetText()
		val, err := strconv.ParseFloat(text, 64)
		if err != nil {
			cg.reportError("literal decimal inválido: " + text)
			cg.pushNum64(0)
		} else {
			cg.pushNum64Float(val)
		}
	case *CharLitExprContext:
		text := expr.CHAR_LITERAL().GetText()
		if len(text) >= 3 {
			cg.pushChar(uint8(text[1]))
		} else {
			cg.pushChar(0)
		}
	case *BoolBitExprContext:
		cg.pushBool(expr.BOOLEAN_BIT().GetText() == ".✓")
	case *BoolTritExprContext:
		text := expr.BOOLEAN_TRIT().GetText()
		cg.emit(OP_PUSH)
		cg.emit(TYPE_TRIT)
		if text == "•" {
			cg.emit(1)
		} else if text == "✓" {
			cg.emit(2)
		} else {
			cg.emit(0)
		}
	case *ColLitExprContext:
		cg.pushColor(expr.COLOR_LITERAL().GetText())
	case *ComLitExprContext:
		re, im := parseComplexLiteral(expr.COMPLEX_LITERAL().GetText())
		cg.pushComplex(re, im)
	case *StringLitExprContext:
		cg.pushString(expr.STRING_LITERAL().GetText())
	case *IdentExprContext:
		name := expr.IDENTIFIER().GetText()
		idx, isLocal, found := cg.resolveIdent(name)
		if !found {
			cg.reportError("variable no declarada: " + name)
			return
		}
		if isLocal {
			cg.emit(OP_LOAD_LOCAL)
		} else {
			cg.emit(OP_LOAD_VAR)
		}
		cg.emit16(idx)
	case *PtrLitExprContext:
		text := expr.POINTER_LITERAL().GetText()
		name := text[1:]
		idx, _, found := cg.resolveIdent(name)
		if !found {
			cg.reportError("variable no declarada para puntero: " + name)
			return
		}
		cg.emit(OP_PUSH)
		cg.emit(TYPE_POINT)
		ptr := uintptr(idx)
		for i := 0; i < 8; i++ {
			cg.emit(byte(ptr >> (i * 8)))
		}
	case *ArrayLitExprContext:
		cg.emitArrayLiteral(expr.ArrayLiteral())
	case *IndexedAccessExprContext:
		cg.emit(OP_ARRAY_GET)
	case *DotAccessExprContext:
		cg.emitDotAccess(expr)
	case *PkgExprContext:
		cg.emitPackage(expr.PkgDeclaration())
	}
}

// ==========================================
// Binary Expressions
// ==========================================
func (cg *CodeGen) ExitAddSubExpr(ctx *AddSubExprContext) {
	switch childTokText(ctx, 1) {
	case "+":
		cg.emit(OP_ADD)
	case "-":
		cg.emit(OP_SUB)
	}
}

func (cg *CodeGen) ExitMultDivExpr(ctx *MultDivExprContext) {
	switch childTokText(ctx, 1) {
	case "×":
		cg.emit(OP_MUL)
	case "÷":
		cg.emit(OP_DIV)
	}
}

func (cg *CodeGen) ExitRelationalExpr(ctx *RelationalExprContext) {
	switch childTokText(ctx, 1) {
	case "==":
		cg.emit(OP_EQ)
	case "≠", "!=":
		cg.emit(OP_NEQ)
	case "<":
		cg.emit(OP_LT)
	case ">":
		cg.emit(OP_GT)
	case "≤", "<=":
		cg.emit(OP_LTE)
	case "≥", ">=":
		cg.emit(OP_GTE)
	}
}

func (cg *CodeGen) ExitBitwiseExpr(ctx *BitwiseExprContext) {
	switch childTokText(ctx, 1) {
	case "&":
		cg.emit(OP_BIT_AND)
	case "|":
		cg.emit(OP_BIT_OR)
	case ".&":
		cg.emit(OP_AND)
	case ".|":
		cg.emit(OP_OR)
	}
}

func (cg *CodeGen) ExitShiftExpr(ctx *ShiftExprContext) {
	switch childTokText(ctx, 1) {
	case "•«":
		cg.emit(OP_BIT_SHL)
	case "»•":
		cg.emit(OP_BIT_SHR)
	}
}

func (cg *CodeGen) ExitNotgateExpr(ctx *NotgateExprContext) {
	switch childTokText(ctx, 0) {
	case ".!", "!.!":
		cg.emit(OP_BIT_NOT)
	default:
		cg.emit(OP_NOT)
	}
}

// ==========================================
// CallExpr
// ==========================================
func (cg *CodeGen) ExitCallExpr(ctx *CallExprContext) {
	name := ctx.IDENTIFIER().GetText()
	argCount := 0
	if ctx.ArgumentList() != nil {
		for range ctx.ArgumentList().AllExpression() {
			argCount++
		}
	}

	if id, ok := nativeNames[name]; ok {
		cg.emit(OP_CALL_NATIVE)
		cg.emit16(id)
		cg.emit(byte(argCount))
		return
	}

	switch name {
	default:
		idx, ok := cg.locals[name]
		if !ok {
			cg.reportError("función no definida: " + name)
			return
		}
		cg.emit(OP_LOAD_VAR)
		cg.emit16(idx)
		cg.emit(OP_CALL_VAR)
		cg.emit(byte(argCount))
	}
}

func (cg *CodeGen) EnterBlock(ctx *BlockContext) {
	if cg.inTryCatch {
		if cg.tryBlockCount == 1 {
			// Second block (catch): emit OP_TRY_END + STORE_VAR for catch variable
			cg.emit(OP_TRY_END)
			cg.tryCatchEndPatch = cg.pos()
			cg.emitI16(0) // placeholder — end_offset
			cg.emit(OP_STORE_VAR)
			cg.emit16(cg.tryCatchVarIdx)
		}
		return
	}
	// Bloque-caso de un condicional: se captura en un buffer propio.
	if _, ok := cg.caseOwner[ctx]; ok {
		cg.caps = append(cg.caps, nil)
		return
	}
	// El primer bloque tras iniciar un bucle es su cuerpo: se emite el
	// salto condicional al final y se marca el frame como abierto.
	if cg.pendingLoopBody {
		f := &cg.loops[len(cg.loops)-1]
		cg.emit(OP_JUMP_IF_FALSE)
		f.jifEnd = cg.pos()
		cg.emitI16(0)
		f.bodyBlock = ctx
		cg.pendingLoopBody = false
		return
	}
}

func (cg *CodeGen) ExitBlock(ctx *BlockContext) {
	if cg.inTryCatch {
		cg.tryBlockCount++
		return
	}
	// Cierre de bloque-caso: el buffer capturado pasa a su frame.
	if f, ok := cg.caseOwner[ctx]; ok {
		n := len(cg.caps)
		f.blocks = append(f.blocks, cg.caps[n-1])
		cg.caps = cg.caps[:n-1]
		return
	}
	// Cierre del cuerpo de un bucle (identificado por bloque, no por
	// profundidad, para no confundirlo con bloques anidados).
	if len(cg.loops) > 0 && cg.loops[len(cg.loops)-1].bodyBlock == ctx {
		f := cg.loops[len(cg.loops)-1]
		cg.loops = cg.loops[:len(cg.loops)-1]
		cg.emit(OP_JUMP)
		back := int16(f.condStart - (cg.pos() + 2))
		cg.emitI16(back)
		cg.patchI16(f.jifEnd, int16(cg.pos()-f.jifEnd-2))
	}
}
func (cg *CodeGen) ExitMatchCase(ctx *MatchCaseContext) {}

// ==========================================
// ParameterList
// ==========================================
func (cg *CodeGen) EnterParameterList(ctx *ParameterListContext) {
	if !cg.inFunction {
		return
	}
	identifiers := ctx.AllIDENTIFIER()
	for _, id := range identifiers {
		name := id.GetText()
		cg.funcLocals[name] = cg.funcNextLocal
		cg.funcNextLocal++
	}
}

// ==========================================
// ReturnStatement
// ==========================================
func (cg *CodeGen) ExitReturnStatement(ctx *ReturnStatementContext) {
	cg.emit(OP_RETURN)
}

// ==========================================
// TryCatchStatement
// ==========================================
func (cg *CodeGen) EnterTryCatchStatement(ctx *TryCatchStatementContext) {
	catchVarName := ctx.AllIDENTIFIER()[0].GetText()
	idx := cg.nextLocal
	cg.nextLocal++
	cg.tryCatchVarIdx = idx
	cg.locals[catchVarName] = idx

	cg.inTryCatch = true
	cg.tryBlockCount = 0

	cg.emit(OP_TRY_SETUP)
	cg.catchOffsetPatch = cg.pos()
	cg.emitI16(0) // placeholder — catch_offset
}

func (cg *CodeGen) ExitTryCatchStatement(ctx *TryCatchStatementContext) {
	// Patch catch_offset to point to STORE_VAR (right after OP_TRY_END operand)
	catchTarget := cg.tryCatchEndPatch + 2
	cg.patchI16(cg.catchOffsetPatch, int16(catchTarget-cg.catchOffsetPatch-2))

	// Patch end_offset to jump past catch block
	cg.patchI16(cg.tryCatchEndPatch, int16(cg.pos()-cg.tryCatchEndPatch-2))

	cg.inTryCatch = false
	cg.tryBlockCount = 0
}

// ==========================================
// ThrowStatement
// ==========================================
func (cg *CodeGen) ExitThrowStatement(ctx *ThrowStatementContext) {
	cg.emit(OP_THROW)
}

// ==========================================
// FuncExpr
// ==========================================
func (cg *CodeGen) EnterFuncExpr(ctx *FuncExprContext) {
	cg.savedCode = cg.code
	cg.code = make([]byte, 0)
	cg.inFunction = true

	cg.savedFuncLocals = cg.funcLocals
	cg.savedFuncNext = cg.funcNextLocal
	cg.funcLocals = make(map[string]uint16)
	cg.funcNextLocal = 0
}

func (cg *CodeGen) ExitFuncExpr(ctx *FuncExprContext) {
	cg.emit(OP_RETURN)

	funcBody := cg.code
	paramCount := 0
	if fd := ctx.FunctionDeclaration(); fd != nil {
		if pl := fd.ParameterList(); pl != nil {
			paramCount = len(pl.AllIDENTIFIER())
		}
	}
	cg.funcBodies = append(cg.funcBodies, funcBody)
	cg.funcParamCounts = append(cg.funcParamCounts, paramCount)

	cg.code = cg.savedCode
	cg.inFunction = false

	cg.funcLocals = cg.savedFuncLocals
	cg.funcNextLocal = cg.savedFuncNext

	cg.emit(OP_PUSH)
	cg.emit(TYPE_FUNC)
	cg.funcPatchPositions = append(cg.funcPatchPositions, len(cg.code))
	cg.emit16(0)
	cg.emit(byte(paramCount))
}

// ==========================================
// Array Literals
// ==========================================
func (cg *CodeGen) emitArrayLiteral(ctx IArrayLiteralContext) {
	exprs := ctx.AllExpression()
	count := uint16(len(exprs))
	cg.emit(OP_ARRAY_NEW)
	cg.emit16(count)
}

// ==========================================
// Dot Access (pkg.field) — expression already on stack from walker
// ==========================================
func (cg *CodeGen) emitDotAccess(ctx *DotAccessExprContext) {
	fieldName := ctx.IDENTIFIER().GetText()
	cg.emit(OP_PKG_GET)
	cg.emit16(uint16(len(fieldName)))
	for _, b := range []byte(fieldName) {
		cg.emit(b)
	}
}

// ==========================================
// Package Declaration
// ==========================================
func (cg *CodeGen) EnterPkgExpr(ctx *PkgExprContext) {
	cg.inPkg = true
	cg.pkgFields = nil
}

func (cg *CodeGen) emitPackage(ctx IPkgDeclarationContext) {
	cg.inPkg = false
	fields := cg.pkgFields
	cg.pkgFields = nil

	count := uint16(len(fields))
	cg.emit(OP_PKG_NEW)
	cg.emit16(count)
	for i := len(fields) - 1; i >= 0; i-- {
		f := fields[i]
		cg.emit16(uint16(len(f.name)))
		for _, b := range []byte(f.name) {
			cg.emit(b)
		}
		if f.private {
			cg.emit(1) // campo privado: OP_PKG_GET/SET lo rechazan desde fuera
		} else {
			cg.emit(0)
		}
	}
}

// ==========================================
// Array native functions (len, push)
// ==========================================
func Compile(inputFile, outputFile string, dump bool) error {
	input, err := antlr.NewFileStream(inputFile)
	if err != nil {
		return fmt.Errorf("error leyendo %s: %v", inputFile, err)
	}

	lexer := NewPaxoLexer(input)
	stream := antlr.NewCommonTokenStream(lexer, 0)
	p := NewPaxoParser(stream)
	tree := p.Program()

	cg := NewCodeGen()
	antlr.ParseTreeWalkerDefault.Walk(cg, tree)

	for _, w := range cg.warnings {
		fmt.Fprintf(os.Stderr, "Warning: %s\n", w)
	}

	if len(cg.errors) > 0 {
		for _, e := range cg.errors {
			fmt.Fprintf(os.Stderr, "Error: %s\n", e)
		}
		return fmt.Errorf("%d errores de compilación", len(cg.errors))
	}

	err = os.WriteFile(outputFile, cg.code, 0o644)
	if err != nil {
		return fmt.Errorf("error escribiendo %s: %v", outputFile, err)
	}

	fmt.Printf("Compilado: %s → %s (%d bytes)\n", inputFile, outputFile, len(cg.code))

	if dump {
		fmt.Println("\nBytecode hex dump:")
		for i := 0; i < len(cg.code); i += 16 {
			fmt.Printf("  %04X: ", i)
			end := i + 16
			if end > len(cg.code) {
				end = len(cg.code)
			}
			for j := i; j < end; j++ {
				fmt.Printf("%02X ", cg.code[j])
			}
			fmt.Println()
		}
	}
	return nil
}
