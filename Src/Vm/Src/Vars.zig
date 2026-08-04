const std = @import("std");

//Deficion de variables
//Numeros
pub const PaxoNum8 = extern struct {
	signo: u1,
	exponente: u2,
	entero: u4,
	fraccion: u1}

pub const PaxoNum16 = extern struct {
	signo: u1,
	exponente: u4,
	entero: u5,
	fraccion: u6}

pub const PaxoNum32 = extern struct {
	signo: u1,
	exponente: u6,
	entero: u12,
	fraccion: u13}

//Números complejos
pub const PaxoCom8 = extern struct {
	real: PaxoNum8,
	imaginario: PaxoNum8}

pub const PaxoCom16 = extern struct {
	real: PaxoNum16,
	imaginario: PaxoNum16}

pub const PaxoCom32 = extern struct {
	real: PaxoNum32,
	imaginario: PaxoNum32}

//Bit
pub const PaxoBool = extern struct {
	valor: u2}

//Carácter
pub const PaxoChar8 = extern struct {
	caracter: u8}

pub const PaxoChar16 = extern struct {
	caracter: u16}

pub const PaxoChar32 = extern struct {
	caracter: u32}

//Conversion de tipos de datos
export fn num8tonum16(num: PaxoNum8) callconv(.C) PaxoNum16 {
	var result: PaxoNum16;
	result.signo = num.signo;
	result.exponente = @as(u4, num.exponente);
	result.entero = @as(u5, num.entero);
	result.fraccion = @as(u6, num.fraccion);
	return result;}

export fn num8tonum32(num: PaxoNum8) callconv(.C) PaxoNum32 {
	var result: PaxoNum32;
	result.signo = num.signo;
	result.exponente = @as(u6, num.exponente);
	result.entero = @as(u12, num.entero);
	result.fraccion = @as(u13, num.fraccion);
	return result;}

export fn num16tonum8(num: PaxoNum16) callconv(.C) PaxoNum8 {
	var result: PaxoNum8;
	result.signo = num.signo;
	result.exponente = @as(u2, num.exponente);
	result.entero = @as(u4, num.entero);
	result.fraccion = @as(u1, num.fraccion);
	return result;}

export fn num16tonum32(num: PaxoNum16) callconv(.C) PaxoNum32 {
	var result: PaxoNum32;
	result.signo = num.signo;
	result.exponente = @as(u6, num.exponente);
	result.entero = @as(u12, num.entero);
	result.fraccion = @as(u13, num.fraccion);
	return result;}

export fn num32tonum8(num: PaxoNum32) callconv(.C) PaxoNum8 {
	var result: PaxoNum8;
	result.signo = num.signo;
	result.exponente = @as(u2, num.exponente);
	result.entero = @as(u4, num.entero);
	result.fraccion = @as(u1, num.fraccion);
	return result;}

export fn num32tonum16(num: PaxoNum32) callconv(.C) PaxoNum16 {
	var result: PaxoNum16;
	result.signo = num.signo;
	result.exponente = @as(u4, num.exponente);
	result.entero = @as(u5, num.entero);
	result.fraccion = @as(u6, num.fraccion);
	return result;}

export fn bittonum8(bit: PaxoBool) callconv(.C) PaxoNum8 {
	 var result: PaxoNum8;
	 result.signo = 0;
	 result.exponente = 0;
	 result.entero = @as(u4, bit.valor);
	 result.fraccion = 0;
	 return result;}

export fn bittonum16(bit: PaxoBool) callconv(.C) PaxoNum16 {
	 var result: PaxoNum16;
	 result.signo = 0;
	 result.exponente = 0;
	 result.entero = @as(u5, bit.valor);
	 result.fraccion = 0;
	 return result;}

export fn bittonum32(bit: PaxoBool) callconv(.C) PaxoNum32 {
	 var result: PaxoNum32;
	 result.signo = 0;
	 result.exponente = 0;
	 result.entero = @as(u12, bit.valor);
	 result.fraccion = 0;
	 return result;}
