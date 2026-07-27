# Paxo

Paxo es un nuevo lenguaje de tipado dinamico, multiparadigma, de vm, este lenguaje esta pensado en el ahorro de memoria por lo que se puede usar varibles de diferentes tamaños

## Tipos

```
📥 foo = 6 //entero
📥 foo = 6.7 //Decimal
📥 foo = 9-4.4 i //complejo decimal 
📥 foo = ✓ //booleano
📥 foo = 'C' //caracter
📥 foo = "Texto"
📥 foo = [4, 6] //vector bidimensional
📥 foo = [6, 8, 4, 8]//vector 4d
📥 foo = 97:10:06:20.878.345 //tiempo
📥 foo[] = «4, 5.08, "Arreglos", «6, 7»»

📦 foo = {
  📥 goo = "Paquetes" //contiene variables y funciones
}
🗳️ foo = {
  📥 inte
  s📥 ou
} //como union
fx foo(){
📥 goo = "Esto es una función"
}

var foo // aloclave
```

## Tamaños de variable

```
xs📥 //2 bytes 16 bits
s📥 //4 bytes 32 bits
📥 //8 bytes 64 bits
l📥 //16 bytes 128 bits
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
  📥 i1 = 8
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
📥 entero = false
📥 i = 0
fx main(){
  entero = 9
  (i > 50): ⏸️ |:
    entero++
  :|
  ↻{
    (entero ≠ 1000){
      i = "completado"
    } →{
      i = "en progreso"
    }
  } 🪤 (axo.vartype) {
    print(i)
  }
}
```
