const std = @import("std");

pub const PaxoNum8 = extern struct {
	signo: u1,
	exponente: u1,
	entero: u4,
	fraccion: u2}

pub const PaxoNum16 = extern struct {
	signo: u1,
	exponente: u4,
	entero: u5,
	fraccion: u6}

pub const PaxoNum32 = extern struct {
	signo: u1,
	exponente: u7,
	entero: u11,
	fraccion: u13}

pub const PaxoNum64 = extern struct {
	signo: u1,
	exponente: u11,
	entero: u25,
	fraccion: u27}

pub const PaxoCom8 = extern struct {
	real: PaxoNum8,
	imaginario: PaxoNum8}

pub const PaxoCom16 = extern struct {
	real: PaxoNum16,
	imaginario: PaxoNum16}

pub const PaxoCom32 = extern struct {
	real: PaxoNum32,
	imaginario: PaxoNum32}

pub const PaxoCom64 = extern struct {
	real: PaxoNum64,
	imaginario: PaxoCom64}

pub const PaxoBool = extern struct {
	valor: u2}

pub const PaxoChar8 = extern struct {
	caracter: u8}

pub const PaxoChar16 = extern struct {
	caracter: u16}

pub const PaxoChar32 = extern struct {
	caracter: u32}