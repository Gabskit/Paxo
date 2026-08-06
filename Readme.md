# Paxo

Paxo es un nuevo lenguaje de tipado dinamico, multiparadigma, de vm, este lenguaje esta pensado en el ahorro de memoria por lo que se puede usar varibles de diferentes tamaños

## Tipos

```
var foo = 6.7 //numero
var foo = §7.87 //decimal monetario
var foo = 9-4.4 i //complejo
var foo = • //booleano trit
var foo = 'C' //caracter
var foo = "Texto"
var goo = @foo //puntero
var foo = .× //booleano bit
var foo[] = «4, 5.08,•, "arreglos", «6, 7»»

var foo = {
  var goo = "Paquetes" //contiene variables y funciones
}

var foo = (){
var goo = "Esto es una función"
}
```

## Tamaños de variable

```
.8 8 bits
.16 16 bits
.32 32 bits
.64 64 bits //en consideración 

var.8
```
## Funciones

```
var name = (){
//codigo
}
```

Las funciones tambien pueden estar en paquetes para generar clases

```
var hi = {
  var i1 = 8
  var metodo = (){
    //codigo
  }
}
```

## Condicionales

Declaración if else

```
(variable){
  //caso
}→{
  //caso
}
```

Declaración match

```
(variable){
  1 -> {
    //caso 1
  }
  'a' -> {
    //caso a
  }
  _ -> {
    //caso por defecto
  }
}
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
var entero = •
var i = 0
var main = (){
  entero = 9
  (i > 50): || |:
  i++
  :|
  ↻{
    (i ≠ 1000){
      i = "completado"
    } →{
      i = "en progreso"
    }
  } 🪤 (paxo.vartype) {
    print(i)
  }
}
```
