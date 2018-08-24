# webassembly-example

Simple example to show how to use webassembly.

First of we need a compiler. This compiler is called emscripten and can handle at least C, C++ and Rust. I've seen code hinting at java support so that might be an option.

The commands below will clone the respository of emscripten sdk and install the latest version. Also activate it's use in your operating system.
```
git clone https://github.com/juj/emsdk
emsdk install latest
emsdk activate latest
```

If you are using windows you want to run the command below to setup your environment variables.
```
emsdk_env.bat
```

First of we will compile the simple hello world example with emscripten full output.
```
emcc hello.c -s WASM=1 -o hello.html
```

Emscripten has a runner so you can test your files live in your browser. Adding --no_browser will hinder it from opening a new browser window.
```
emrun --no_browser --port 8080 .
```

Next up we have a minimal shell compile with optimization so we can see it in action with less other elements and less code.
```
emcc -o hello2.html hello.c -O3 -s WASM=1 --shell-file shell_minimal.html
```

Lastly we compile the addition demo exporting the addition function and also the cwrap and ccall functions to create javascript functions to invoke or call your function directly.
```
emcc addition.c -o addition.js -s EXPORTED_FUNCTIONS=['_addition']  -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall','cwrap']
```
