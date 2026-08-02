# Paxo

Paxo es un nuevo lenguaje de tipado dinamico, multiparadigma, de vm, este lenguaje esta pensado en el ahorro de memoria por lo que se puede usar varibles de diferentes tamaños

## Tipos

```
xn foo = 6.7 //numero
xi foo = 9-4.4 i //complejo
bit foo = ✓ //booleano
abc foo = 'C' //caracter
abc foo = "Texto"
📥 foo[] = «4, 5.08, «6, 7»»

📦 foo = {
  abc goo = "Paquetes" //contiene variables y funciones
}
🗳️ foo = {
  xn inte
  bit ou
} //como union
fx foo(){
abc goo = "Esto es una función"
}

```

## Tamaños de variable

```
8xn 8bits
16xn 16 bits

xsabc utf 8
sabc uft 16
abc utf 32


```
## Funciones

```
fx name(){
//codigo
}
```

Las funciones tambien pueden estar en paquetes para generar clases

```
📦 hi = {
  xn i1 = 8
  fx metodo(){
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

- ⏸️: ejecutara el código declarado hasta que la condición sea verdadera
- ▶️: ejecutara el código declarado mientras la condición sea verdadera

## Manejo de errores

```
↻ {
  //codigo
} 🪤 (error){
  //error
}
```
## Operadores
==, =, <, >, ≤, ≥, ≠, ×, ÷, √, •«, »•, &, |, !, .&, .|, .!, §, +, -
•« desplazamiento de bits L
»• desplazamiento de bits R
& and
| or
! not
.& and bit trit
.| or bit trit
.! not bit trit
§ xor

## Ejemplo

```
+📚 <Basic.paxo>
bit entero = •
xn i = 0
fx main(){
  entero = ✓
  (i > 50): ⏸️ |:
  i++
  :|
  ↻{
  abc texto
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
