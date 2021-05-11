# BurnYourPC

## Supported Platform

1) Microsoft Windows [TESTED]

2) Linux [NOT TESTED]

## Compile IDE / Tool

- [CLion](https://www.jetbrains.com/clion/)
   - Supported toolchains
      1) MingW64 [RECOMMANDED]
      2) Cygwin
      3) WSL
   - GPU burning should use MingW64 to compile, otherwisw it may not work properly
    
- [Visual Studio](https://visualstudio.microsoft.com/)

- Command line: [CMake](https://cmake.org/) and [MakeFile](https://www.gnu.org/software/make/)

## External Libraries
- [Please refer to here](https://github.com/1552980358/BurnYourPC/tree/master/ExtLibs)

1) [OpenCL-Headers](https://github.com/KhronosGroup/OpenCL-Headers)
   - Included in [OpenCL-ICD-Loader](https://github.com/1552980358/BurnYourPC/tree/master/ExtLibs/OpenCL-ICD-Loader) `./inc/`
  
2) [OpenCL-ICD-Loader](https://github.com/1552980358/BurnYourPC/tree/master/ExtLibs/OpenCL-ICD-Loader)
   - It is already compiled
   - You are adviced to compile it again with [Visual Studio](https://visualstudio.microsoft.com/)

3) [Boost.Compute](https://www.boost.org/)
   - No need to get compiled library file

4) [mingw-std-threads](https://github.com/meganz/mingw-std-threads)
    - No need to get compiled library file

## Open Source License - [GNU General Public License v3.0](LICENSE)
```
                    GNU GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007

 Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.
```

## Credit Project
1. [KhronosGroup/OpenCL-ICD-Loader](https://github.com/KhronosGroup/OpenCL-ICD-Loader)
    - Owner:   KhronosGroup
    - License: [Apache License 2.0](https://github.com/KhronosGroup/OpenCL-ICD-Loader/blob/master/LICENSE)

2. [KhronosGroup/OpenCL-Headers](https://github.com/KhronosGroup/OpenCL-Headers)
    - Owner:   KhronosGroup
    - License: [Apache License 2.0](https://github.com/KhronosGroup/OpenCL-Headers/blob/master/LICENSE)

3. [Boost.Compute 1.76.0](https://www.boost.org/)
    - Owner   : boostorg
    - License : [Boost Software License 1.0](https://github.com/boostorg/compute/blob/master/LICENSE_1_0.txt)

4. [MegaNz/mingw-std-threads](https://github.com/meganz/mingw-std-threads)
    - Owner   : Mega Limited
    - License : [BSD 2-Clause "Simplified" License](https://github.com/meganz/mingw-std-threads/blob/master/LICENSE)