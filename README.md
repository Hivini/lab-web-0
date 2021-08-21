# C++ to WASM Example
This is a homework activity for the web development laboratory. Is just a simple example. This tutorial was based on [Compiling a New C/C++ Module to WebAssembly](https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm).

## Requeriments
- [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)

## How to compile
If changes are made, you can create a new .js and .wasm files with this command:
```
emcc test.cpp -s WASM=1 -s NO_EXIT_RUNTIME=1  -s "EXPORTED_RUNTIME_METHODS=['ccall']"
```

## How to run
```
go run main.go
```

[Demo video](https://youtu.be/eIEhuFNVQmQ)