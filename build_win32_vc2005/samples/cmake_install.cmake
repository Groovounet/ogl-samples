# Install script for directory: E:/G-Truc/git/ogl-samples/samples

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files/ogl-samples-pack")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-buffer-type/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-buffer-update/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-buffer-uniform/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-draw-elements/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-draw-range/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-draw-multiple/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-draw-instanced/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-draw-instanced-array/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-draw-base-vertex/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-fbo-blit/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-fbo-mipmaps/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-fbo-srgb/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-fbo-multiple-output/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-fbo-multisample/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-image-2d/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-image-2d-compressed/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-image-array/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-image-rect/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-query-occlusion/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-query-conditional/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-query-timer/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-rasterizer-viewport/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-sampler-anisotropy-ext/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-sampler-filter/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-sampler-wrap/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-sampler-swizzle/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-sampler-object/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-test-scissor/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-transform-feedback/cmake_install.cmake")
  INCLUDE("E:/G-Truc/git/ogl-samples/build_win32_vc2005/samples/ogl-vao/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

