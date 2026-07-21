# Paxo

Paxo es un nuevo lenguaje de tipado dinamico, multiparadigma, transpilado a c23, este lenguaje esta pensado en el ahorro de memoria por lo que se puede usar varibles de diferentes tamaños

## Tipos

```
📥 foo = 6 //entero
📥 foo = 7u //entero sin signo
📥 foo = 6.7 //Decimal
📥 foo = 9-4.4 i //complejo decimal 
📥 foo = ✓ //booleano
📥 foo = 'C' //caracter
📥 foo = "Texto"
📥 foo = "Abc" il //texto embebido 
📥 foo = [4, 6] //vector bidimensional
📥 foo = [8, 6, 6] //vector 3d
📥 foo = [6, 8, 4, 8]//vector 4d
📥 foo = 97:765 //nanotiempo
📥 goo = &foo~2 //slice
📥 goo = &foo //puntero
📥 foo = 35.106.255.97 //ipv4
📥 foo = 6a:aff:... //ipv6
📥 foo = «4, 5.08, "Arreglos", «6, 7»»

📦 foo = {
  📥 goo = "Paquetes" //contiene variables y funciones
}
🗳️ foo = {
  📥 inte
  s📥 ou
} //como union
📥 foo = (){
📥 goo = "Esto es una función"
}
```

## Tamaños de variable

```
xxs📥 //1 byte 8 bits
xs📥 //2 bytes 16 bits
s📥 //4 bytes 32 bits
📥 //8 bytes 64 bits
l📥 //16 bytes 128 bits
xl📥 //32 bytes 256 bits
```
## Funciones

```
📥 name = (){
//codigo
}
```

Las funciones tambien pueden estar en paquetes para generar clases

```
📦 hi = {
  📥 i1 = 8
  📥 metodo = (){
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
.& and bit
.| or bit
.! not bit
§ xor

## Ejemplo

```
+📚 <Basic.paxo>
📥 entero = false
📥 i = 0
📥 main = (){
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
