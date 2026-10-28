# NocturneSDK
NocturneOS SDK - modular toolkit for working with compilers that doesn't implement a support for NocturneOS.

It includes:
- Nocturne LibC (standard C library)
- Nocturne LibM (standard math library)

# Installation
```bash
# Quick start
sudo mkdir /opt/nocturne
sudo chown $USER /opt/nocturne

./insttool.py --targets i586 x86_64 --gcc-langs c --prefix /opt/nocturne
```

> [!IMPORTANT]
> Be sure to add `/opt/nocturne/bin` to your `$PATH` and restart your shell to apply your changes.

