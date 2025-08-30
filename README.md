# am64xx-reset-cause

Reset cause determination program for TI (Texas Instruments) AM64xx family.

## Description

This tool reads the reset register ``CTRLMMR_RST_SRC`` of the SoC via
``/dev/mem`` and displays the results as ``pretty (-p)`` or ``binary (-b)``
representation on standard output.

Querying the register may require additional permissions like
elevated privileges (``sudo`` or ``root``).

## Compatibility

``ARM64``only support on SoC [AM64xx family](https://www.ti.com/product/AM6442#tech-docs)

## Hint on the technical reference manual

The complexity of the TI AM64xx family makes it rather complicated to
give a brief hint on the reset cause determination.

``CTRLMMR_RST_SRC`` is a 32bit register in the 64 and 32 bit addressable memory
area of the AM64xx SoCs, which is intended to be read once by software.

Usually does the reading procedure require a subsequent clear of the
register as well.

This program supports only the read of the register.

Further information can be found in the chapter ``reset`` of the SoC associated
technical reference manual.

## Build the program

Build the program with the following command in a release setup:

```
cmake -DCMAKE_BUILD_TYPE=Release -B build-release/
```

Alternatively as debug build:

```
cmake -DCMAKE_BUILD_TYPE=Debug  -B build-debug/
```

## Determining the reset cause

```
cd build/
./src/am64xx-reset-cause
```

## Codestyle check

Issue following command from root of repository for ``llvm``
coding style deviations.

```
cd /am64xx-reset-cause
clang-format --dry-run -i src/*.c src/am64xx/*.*
```
