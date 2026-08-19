# Paxo

Paxo es un nuevo lenguaje de tipado dinamico, multiparadigma, de vm, este lenguaje esta pensado en el ahorro de memoria por lo que se puede usar varibles de diferentes tamaños

## Tipos

```
var foo = 6.7 //numero
n foo = 6.7
var foo = • //booleano trit
trit foo = •
var foo = 'C' //caracter
abc foo = 'C'
var foo = "Texto"
abc foo = "Texto"
var goo = @foo //puntero
pin goo = @foo
var foo = .× //booleano bit
bool foo = .×
var foo[] = «4, 5.08, •, "arreglos", «6 + 8.0, 7»»

var foo = {
  var goo = "Paquetes" //contiene variables y funciones
}

var foo = (){
	var goo = "Esto es una función"
	return goo;
}
```

## Tamaños de variable

```
.8 8 bits
.16 16 bits
.32 32 bits
.64 64 bits //en consideración 

var.8
n.8
```

## Acceso de variables

```
local var //local

pub var //global
🌎 var
```
## Funciones

```
📥 var name = (){
//codigo
}
```

Las funciones tambien pueden estar en paquetes para generar clases

```
pub var hi = {
  local var i1 = 8
  local var metodo = (){
    //codigo
  }
}
```

## Condicionales

Declaracion Condicionales

```
(expresión | variable)?
    //caso 1
  : 'a' -> 
    //caso a
  : (expresión) ->
		//caso
	: _ -> 
    //caso por defecto
  ;
```

## Bucles

```
(condicion): ⏸️ | ▶️ |:
  //codigo
:|
```

- ⏸️ | ||: ejecutara el código declarado hasta que la condición sea verdadera
- ▶️ | >: ejecutara el código declarado mientras la condición sea verdadera

## Manejo de errores

```
↻ {
  //codigo
} 🪤 | /] (error){
  //error
}
```
## Operadores

==, =, <, >, ≤, ≥, ≠, ×, ÷, √, •«, »•, &, |, !, .&, .|, .!, ^, +, -
•« desplazamiento de bits L
»• desplazamiento de bits R
& and
| or
! not
.& and bit
.| or bit
.! not bit
^ xor

## Ejemplo

```
+📚 <Basic.paxo>
local var entero = •
local var i = 0
pub var main = (){
  entero = 9
  (i > 50): || |:
  i++
  :|
  ↻{
    (i ≠ 1000) ?
      i = "completado"
    : _ →
      i = "en progreso"
    ;
  } 🪤 (paxo.vartype) {
    print(i)
  }
}
```

## Funciones nativas

```
print(valor)    // imprime sin salto de línea
println(valor)  // imprime con salto de línea
typeof(valor)   // retorna el tipo del valor como char
```

Soportan múltiples argumentos y strings:
```
println("hola mundo");
println("nota: ", 8.5);
print("suma: ", 2 + 3);
```

## Dependencias usadas
termcolor https://github.com/ararslan/termcolor-c.git
