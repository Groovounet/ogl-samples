================================================================================
OpenGL Samples Pack 
--------------------------------------------------------------------------------
ogl-samples.g-truc.net
ogl-samples@g-truc.net

================================================================================
The MIT License
--------------------------------------------------------------------------------
Copyright (c) 2005 - 2012 G-Truc Creation (www.g-truc.net)

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
- Install FreeGLUT package
- Download GLEW 1.9.0 (http://glew.sourceforge.net) and install depend packages
- Run CMake to create a makefile for G++
- Launch the sample from the build output directory

================================================================================
OpenGL Samples Pack 4.3.0.1: 2012-08-30
--------------------------------------------------------------------------------
- Added 430-texture-view sample
- Added 430-image-sampling sample
- Added 430-program-subroutine sample
- Added 420-primitive-line-aa sample
- Fixed 430-multi-draw-indirect, precision issue
- Fixed 430-interface-matching

================================================================================
OpenGL Samples Pack 4.3.0.0: 2012-08-12
--------------------------------------------------------------------------------
- Added 430-texture-copy sample
- Added 430-program-compute sample
- Added 430-multi-draw-indirect sample
- Added 430-interface-matching sample
- Added 430-image-store sample
- Added 430-draw-without-vertex-attrib sample
- Added 430-direct-state-access sample
- Added 430-atomic-counter sample

================================================================================
OpenGL Samples Pack 4.2.3.0: 2012-01-28
--------------------------------------------------------------------------------
- Added 420-blend-op-amd sample
- Added 420-buffer-pinned-amd sample
- Added 420-debug-output sample
- Added 420-fbo-srgb-decode-ext sample
- Added 420-interface-matching sample
- Added 330-texture-format sample
- Added 330-fbo-multisample-explicit-nv sample
- Updated 410-program-binary sample
- Refactored code

================================================================================
OpenGL Samples Pack 4.2.2.1: 2012-01-24
--------------------------------------------------------------------------------
- Fixed bugs

================================================================================
OpenGL Samples Pack 4.2.2.0: 2011-11-26
--------------------------------------------------------------------------------
- Clean up DSA samples and build a single one
- Added image store sample
- Added clamp separate test
- Take advantage of texture max level
- Generalized pipeline and uniform buffer for OpenGL 4.2 samples
- Fixed dynamic uniform variable use for sampler array and uniform block array
- Tessellation without control shader

================================================================================
OpenGL Samples Pack 4.2.1.1: 2011-08-26
--------------------------------------------------------------------------------
- Fixed CTest default value

================================================================================
OpenGL Samples Pack 4.2.1.0: 2011-08-26
--------------------------------------------------------------------------------
- Added CTest
- Rewritten OpenGL 4.2 samples
- Refactored direct state access samples
- Removed some deprecated/duplicated samples

================================================================================
OpenGL Samples Pack 4.2.0.2: 2011-08-11
--------------------------------------------------------------------------------
- Fixed samples on AMD implementation

================================================================================
OpenGL Samples Pack 4.2.0.1: 2011-08-10
--------------------------------------------------------------------------------
- Fixed samples on NVIDIA implementation

================================================================================
OpenGL Samples Pack 4.2.0.0: 2011-08-09
--------------------------------------------------------------------------------
- Added atomic counter sample
- Added buffer uniform sample
- Added draw base instance sample
- Added GLSL interface matching array sample
- Added depth conservative test sample
- Added pixel store for compressed texture 2d sample
- Added immunable texture sample
- Added compressed texture
- Added texture image sample
- Added transform feedback instancing sample

================================================================================
OpenGL Samples Pack 4.1.7.2: 2011-08-04
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
