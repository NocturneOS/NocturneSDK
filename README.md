# NocturneSDK
NocturneOS SDK - modular toolkit for working with compilers that doesn't implement a support for NocturneOS.

It includes:
- Nocturne LibC (standard C library)
- Nocturne LibM (standard math library)
- Nocturne-CC (compiler wrapper) (DEPRECATED!)

# Installation
```bash
cmake -B build .
cmake --build build/
sudo cmake --install build/
```

After installation you'll find libraries, header files and Nocturne-CC at `/usr/local/i386-nocturne/`.

> [!IMPORTANT]
> Be sure to add `/usr/local/nocturneos/bin` to your `$PATH` and restart your shell to apply your changes.

# Usage

Use [binutils](https://github.com/NocturneOS/binutils-gdb) and [gcc](https://github.com/NocturneOS/gcc) to make it work with NocturneSDK.
