================================================================================
OpenGL Samples Pack 
--------------------------------------------------------------------------------
ogl-samples.g-truc.net
ogl-samples@g-truc.net

================================================================================
The MIT License
--------------------------------------------------------------------------------
Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

================================================================================
OpenGL Samples Pack Usage
--------------------------------------------------------------------------------
The OpenGL Samples Pack supports Windows build through Visual C++ only and 
Linux build with G++.

MacOSX or MinGW are not supported yet... 

================================================================================
Visual C++ instructions
--------------------------------------------------------------------------------
The OpenGL Samples Pack's project can be generated for Visual C++ 2008 and 2010,
in 32 and 64 bits using CMake.
http://www.cmake.org/cmake/resources/software.html

The samples run only when launched from Visual C++ IDE.

================================================================================
Linux G++ instructions
--------------------------------------------------------------------------------
Tested on Ubuntu 11.04 on a NVIDIA platform:
- Install FreeGLUT package
- Download GLEW 1.6.0 (http://glew.sourceforge.net) and install depend packages
- Run CMake to create a makefile for G++
- Launch the sample from the build output directory

================================================================================
OpenGL Samples Pack 4.1.7.2: 2011-07-29
--------------------------------------------------------------------------------
- Added point sprite sample
- Added interface matching sample
- Fixed interface matching of some samples
- Fixed transform feedback stream sample
- Fixed GLEW extension loading

================================================================================
OpenGL Samples Pack 4.1.7.1: 2011-07-11
--------------------------------------------------------------------------------
- Added Linux support

================================================================================
OpenGL Samples Pack 4.1.7.0: 2011-07-10
--------------------------------------------------------------------------------
- Removed all the workaround used since OpenGL 3.3 beta drivers release
- Some samples refactoring
- Added more transformed feedback tests
- Added pixel store for texture 2d sample
- Fixed extension loading

================================================================================
OpenGL Samples Pack 4.1.6.1: 2011-06-22
--------------------------------------------------------------------------------
- Added this readme.txt
- Added ogl-330-primitive-front-face sample
- Generalized matching by location
- Fixed bugs

================================================================================
