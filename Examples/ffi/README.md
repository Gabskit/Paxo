# Paxo extensible FFI

A module exports:

```c
bool paxo_module_init(PaxoNativeRegistry *registry, const PaxoFFIAPI *api);
```

Register functions with `paxo_ffi_register`. Paxo bytecode can call them through:

```paxo
ffiLoad("./libpaxo_math.so")
ffiCall("decimal_add_one", value)
```

`DEC` is passed as the original `decimal64` value and returned as `DEC`; it is not converted to `double` by the FFI ABI.
