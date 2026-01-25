ihc
===
Ilonic's Headers Collection
Similarly to [stb](https://github.com/nothings/stb/tree/master) this repository is just a collection of header files.

Quick Start
===
```sh
curl -O raw.githubusercontent.com/ilonic23/ihc/refs/heads/master/ihc_libname.h
```

```c
#define IHC_LIBNAME_IMPLEMENTATION
#include "ihc_libname.h"
```
Libraries list
===

|Header File|Version|Description|
|-----------|-------|-----------|
|**ihc_sorts.h**|v0.11|Implementation of a variety of sorting algorithms made to work with any type.
|**ihc_string.h**|v0.11|Implementation of a safe to use string type.
|**ihc_tga.h**|?|Implementation of TGA file reader/decoder.
|**ihc_collections.h**|?|Implementation of some collections types|

FAQ
===

### Are the files free of charge?
Yes, they totally are, every file is licensed with the [**Unlicense**](unlicense.org) license.
I provide this software "as is" and don't give any warranties.
You are free to do whatever you want with them.

### How to use the header files?
Just the header file.
**Notice:** you have to select one file where to put the implementation:
```c
#define IHC_LIBNAME_IMPLEMENTATION
#include "ihc_libname.h"
```

### What C standard the libraries are?
C99

### Where to find documentation to the libraries?
In the start of the header file itself.
