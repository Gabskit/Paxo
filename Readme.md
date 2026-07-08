# Axolang 
Axolang es un nuevo lenguaje de tipado dinamico, multiparadigma, transpilado a c23, este lenguaje esta pensado en el ahorro de memoria por lo que se puede usar varibles de diferentes tamaños 
## Tipos
```
var foo = 6 //entero
var foo = 7u //entero sin signo
var foo = 5.5 //flotante
var foo = 8D //decimal
var foo = 5+6 i //complejo
var foo = true //booleano
var foo = 'C' //caracter
var foo = "Texto"
var goo = &foo //puntero
var foo = {
  var goo = "Paquetes" //contiene variables y funciones
}
var foo = «4, 5D, "Arreglos", «6, 7»»
```
## Tamaños de variable
```
xxsvar //1 byte 8 bits
xsvar //2 bytes 16 bits
svar //4 bytes 32 bits
var //8 bytes 64 bits
lvar //16 bytes 128 bits
xlvar //32 bytes 256 bits
```
- xxsvar acepta entero con signo y sin signo, caracteres y booleano
- xsvar acepta entero con signo y sin signo, caracteres, booleano y flotantes
- svar acepta entero con signo y sin signo, caracteres, booleano, flotantes, complejos y decimales
- var a xlvar aceptaa todos los tipos
## Funciones
```
fun name = (){
//codigo
}
```
Las funciones tambien pueden estar en paquetes para generar clases
```
var pkg = {
  var i1 = 8
  fun metodo = (){
    //codigo
  }
}
```
## Condicionales
Declaración if else
```
if (variable){
  //caso
} else {
  //caso
}
```
Declaración match
```
match (variable){
  1 -> {
    //caso 1
  }
  'a' -> {
    //caso a
  }
  default -> {
    //caso por defecto
  }
}
```
## Bucles
```
loop (condicion): stop | go {
  //codigo
}
```
- stop: ejecutara el código declarado hasta que la condición sea verdadera
- go: ejecutara el código declarado mientras la condición sea verdadera
## Manejo de errores
```
try {
  //codigo
} catch (error){
  //error
}
```
## Ejemplo
```
add <Basic.axo>
var entero = false
var i = 0
fun main = (){
  entero = 9
  loop (i > 50): stop {
    entero++
  }
  try {
    if (entero ≠ 1000){
      i = "completado"
    } else {
      i = "en progreso"
    }
  } catch (axo.vartype) {
    print(i)
  }
}
```