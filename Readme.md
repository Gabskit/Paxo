# Paxo

Paxo es un nuevo lenguaje de tipado dinamico, multiparadigma, de vm, este lenguaje esta pensado en el ahorro de memoria por lo que se puede usar varibles de diferentes tamaños

## Tipos

```
n8 foo = 6.7 //numero
ni8 foo = 9-4.4 i //complejo
bit foo = ✓ //booleano
abc8 foo = 'C' //caracter
abc8 foo = "Texto"
n8 foo[] = «4, 5.08, «6, 7»»

📦 foo = {
  abc goo = "Paquetes" //contiene variables y funciones
}
🗳️ foo = {
  n8 inte
  bit ou
} //como union
fx foo = (){
abc8 goo = "Esto es una función"
}

```

## Tamaños de variable

```
n8 8 bits
n16 16 bits
n32 32 bits
n64 64 bits //en consideración 

ni8
ni16
ni32
ni64

abc8 utf 8
abc16 uft 16
abc32 utf 32
```
## Funciones

```
fx name = (){
//codigo
}
```

Las funciones tambien pueden estar en paquetes para generar clases

```
📦 hi = {
  n8 i1 = 8
  fx metodo = (){
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
} 🪤 (error){
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
bit entero = •
n8 i = 0
fx main = (){
  entero = ✓
  (i > 50): || |:
  i++
  :|
  ↻{
  abc8 texto
    (i ≠ 1000){
      texto = "completado"
    } →{
      texto = "en progreso"
    }
  } 🪤 (paxo.vartype) {
    print(i)
  }
}
```
