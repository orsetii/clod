# clod - A Binary Loader

This binary makes use of Binary File Descriptor library `libbfd` which provides a common interface for reading and parsing all popular binary formats. This includes ELF and PE for x86 and x64.

The BFD library is part of the GNU project in the `binutils` and is included in the `binutils-dev` package.

You can find the core `libbfd` API in `/usr/include/bfd.h`.
