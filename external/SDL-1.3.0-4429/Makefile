# Makefile to build and install the SDL library

top_builddir = .
srcdir  = .
objects = build
prefix = /Users/christophericcio/Documents/g-truc/git/ogl-samples/external/SDL-1.3.0-4429
exec_prefix = ${prefix}
bindir	= ${exec_prefix}/bin
libdir  = ${exec_prefix}/lib
includedir = ${prefix}/include
datarootdir = ${prefix}/share
datadir	= ${datarootdir}
auxdir	= ./build-scripts
distpath = $(srcdir)/..
distdir = SDL-1.3.0
distfile = $(distdir).tar.gz


SHELL	= /bin/sh
CC      = gcc
INCLUDE = -I./include
CFLAGS  = -g -O3
EXTRA_CFLAGS = -I./include  -mmmx -m3dnow -msse -msse2 -DTARGET_API_MAC_CARBON -DTARGET_API_MAC_OSX -fvisibility=hidden  -I/usr/X11R6/include -D_THREAD_SAFE -falign-loops=16 -force_cpusubtype_ALL -fpascal-strings
LDFLAGS = 
EXTRA_LDFLAGS =  -Wl,-framework,OpenGL  -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,AudioUnit
LIBTOOL = $(SHELL) $(top_builddir)/libtool
INSTALL = /usr/bin/install -c
NASM	= @NASM@ @NASMFLAGS@
AR	= ar
RANLIB	= ranlib
WINDRES	= 

TARGET  = libSDL.la
OBJECTS = $(objects)/SDL.lo $(objects)/SDL_assert.lo $(objects)/SDL_compat.lo $(objects)/SDL_error.lo $(objects)/SDL_fatal.lo $(objects)/SDL_audio.lo $(objects)/SDL_audiocvt.lo $(objects)/SDL_audiodev.lo $(objects)/SDL_audiotypecvt.lo $(objects)/SDL_mixer.lo $(objects)/SDL_mixer_MMX.lo $(objects)/SDL_mixer_MMX_VC.lo $(objects)/SDL_mixer_m68k.lo $(objects)/SDL_wave.lo $(objects)/SDL_cpuinfo.lo $(objects)/SDL_events.lo $(objects)/SDL_keyboard.lo $(objects)/SDL_mouse.lo $(objects)/SDL_quit.lo $(objects)/SDL_windowevents.lo $(objects)/SDL_rwops.lo $(objects)/SDL_getenv.lo $(objects)/SDL_iconv.lo $(objects)/SDL_malloc.lo $(objects)/SDL_qsort.lo $(objects)/SDL_stdlib.lo $(objects)/SDL_string.lo $(objects)/SDL_thread.lo $(objects)/SDL_timer.lo $(objects)/SDL_RLEaccel.lo $(objects)/SDL_alphamult.lo $(objects)/SDL_blendfillrect.lo $(objects)/SDL_blendline.lo $(objects)/SDL_blendpoint.lo $(objects)/SDL_blendrect.lo $(objects)/SDL_blit.lo $(objects)/SDL_blit_0.lo $(objects)/SDL_blit_1.lo $(objects)/SDL_blit_A.lo $(objects)/SDL_blit_N.lo $(objects)/SDL_blit_auto.lo $(objects)/SDL_blit_copy.lo $(objects)/SDL_blit_slow.lo $(objects)/SDL_bmp.lo $(objects)/SDL_drawline.lo $(objects)/SDL_drawpoint.lo $(objects)/SDL_drawrect.lo $(objects)/SDL_fillrect.lo $(objects)/SDL_gamma.lo $(objects)/SDL_pixels.lo $(objects)/SDL_rect.lo $(objects)/SDL_renderer_gl.lo $(objects)/SDL_renderer_gles.lo $(objects)/SDL_renderer_sw.lo $(objects)/SDL_stretch.lo $(objects)/SDL_surface.lo $(objects)/SDL_video.lo $(objects)/SDL_yuv_mmx.lo $(objects)/SDL_yuv_sw.lo $(objects)/SDL_joystick.lo $(objects)/SDL_haptic.lo $(objects)/SDL_power.lo $(objects)/SDL_nullevents.lo $(objects)/SDL_nullrender.lo $(objects)/SDL_nullvideo.lo $(objects)/SDL_diskaudio.lo $(objects)/SDL_dummyaudio.lo $(objects)/SDL_sysloadso.lo $(objects)/SDL_cocoaevents.lo $(objects)/SDL_cocoakeyboard.lo $(objects)/SDL_cocoamodes.lo $(objects)/SDL_cocoamouse.lo $(objects)/SDL_cocoaopengl.lo $(objects)/SDL_cocoavideo.lo $(objects)/SDL_cocoawindow.lo $(objects)/SDL_x11dyn.lo $(objects)/SDL_x11events.lo $(objects)/SDL_x11gamma.lo $(objects)/SDL_x11keyboard.lo $(objects)/SDL_x11modes.lo $(objects)/SDL_x11mouse.lo $(objects)/SDL_x11opengl.lo $(objects)/SDL_x11opengles.lo $(objects)/SDL_x11render.lo $(objects)/SDL_x11video.lo $(objects)/SDL_x11window.lo $(objects)/imKStoUCS.lo $(objects)/AllCmap.lo $(objects)/CmapAlloc.lo $(objects)/CrCmap.lo $(objects)/DelCmap.lo $(objects)/Distinct.lo $(objects)/LookupCmap.lo $(objects)/StdCmap.lo $(objects)/VisCmap.lo $(objects)/XF86VMode.lo $(objects)/Xv.lo $(objects)/Xinerama.lo $(objects)/SDL_systhread.lo $(objects)/SDL_syssem.lo $(objects)/SDL_sysmutex.lo $(objects)/SDL_syscond.lo $(objects)/SDL_coreaudio.lo $(objects)/SDL_atomic.lo $(objects)/SDL_sysjoystick.lo $(objects)/SDL_syshaptic.lo $(objects)/SDL_syspower.lo $(objects)/SDL_systimer.lo
VERSION_OBJECTS = 

SDLMAIN_TARGET = libSDLmain.a
SDLMAIN_OBJECTS = $(objects)/SDL_dummy_main.o

# PS3 SPU programs
SPU_GCC = 
EMBEDSPU = 
#include $(srcdir)/src/video/ps3/spulibs/Makefile

DIST = acinclude autogen.sh Borland.html Borland.zip BUGS build-scripts configure configure.in COPYING CREDITS include INSTALL Makefile.minimal Makefile.in README* sdl-config.in sdl.m4 sdl.pc.in SDL.spec SDL.spec.in src test TODO VisualC.html VisualC VisualCE Watcom-Win32.zip WhatsNew Xcode Xcode-iPhoneOS

HDRS = SDL.h SDL_assert.h SDL_atomic.h SDL_audio.h SDL_compat.h SDL_cpuinfo.h SDL_endian.h SDL_error.h SDL_events.h SDL_haptic.h SDL_joystick.h SDL_keyboard.h SDL_keysym.h SDL_loadso.h SDL_main.h SDL_mouse.h SDL_mutex.h SDL_name.h SDL_opengl.h SDL_opengles.h SDL_pixels.h SDL_platform.h SDL_power.h SDL_quit.h SDL_rect.h SDL_revision.h SDL_rwops.h SDL_scancode.h SDL_stdinc.h SDL_surface.h SDL_syswm.h SDL_thread.h SDL_timer.h SDL_types.h SDL_version.h SDL_video.h begin_code.h close_code.h

LT_AGE      = 0
LT_CURRENT  = 0
LT_RELEASE  = 1.3
LT_REVISION = 0
LT_LDFLAGS  = -no-undefined -rpath $(DESTDIR)$(libdir) -release $(LT_RELEASE) -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

all: $(srcdir)/configure Makefile $(objects) $(objects)/$(TARGET) $(objects)/$(SDLMAIN_TARGET)

$(srcdir)/configure: $(srcdir)/configure.in
	@echo "Warning, configure.in is out of date"
	#(cd $(srcdir) && sh autogen.sh && sh configure)
	@sleep 3

Makefile: $(srcdir)/Makefile.in
	$(SHELL) config.status $@

Makefile.in:;

$(objects):
	$(SHELL) $(auxdir)/mkinstalldirs $@

# To make sure parallel builds will not fail
$(srcdir)/include/SDL_revision.h: update-revision

update-revision:
	$(SHELL) $(auxdir)/updaterev.sh

.PHONY: all update-revision install install-bin install-hdrs install-lib install-data uninstall uninstall-bin uninstall-hdrs uninstall-lib uninstall-data clean distclean dist $(OBJECTS:.lo=.d)

-include $(OBJECTS:.lo=.d)

$(objects)/SDL.lo: ./src/SDL.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_assert.lo: ./src/SDL_assert.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_compat.lo: ./src/SDL_compat.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_error.lo: ./src/SDL_error.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_fatal.lo: ./src/SDL_fatal.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_audio.lo: ./src/audio/SDL_audio.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_audiocvt.lo: ./src/audio/SDL_audiocvt.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_audiodev.lo: ./src/audio/SDL_audiodev.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_audiotypecvt.lo: ./src/audio/SDL_audiotypecvt.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_mixer.lo: ./src/audio/SDL_mixer.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_mixer_MMX.lo: ./src/audio/SDL_mixer_MMX.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_mixer_MMX_VC.lo: ./src/audio/SDL_mixer_MMX_VC.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_mixer_m68k.lo: ./src/audio/SDL_mixer_m68k.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_wave.lo: ./src/audio/SDL_wave.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_cpuinfo.lo: ./src/cpuinfo/SDL_cpuinfo.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_events.lo: ./src/events/SDL_events.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_keyboard.lo: ./src/events/SDL_keyboard.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_mouse.lo: ./src/events/SDL_mouse.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_quit.lo: ./src/events/SDL_quit.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_windowevents.lo: ./src/events/SDL_windowevents.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_rwops.lo: ./src/file/SDL_rwops.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_getenv.lo: ./src/stdlib/SDL_getenv.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_iconv.lo: ./src/stdlib/SDL_iconv.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_malloc.lo: ./src/stdlib/SDL_malloc.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_qsort.lo: ./src/stdlib/SDL_qsort.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_stdlib.lo: ./src/stdlib/SDL_stdlib.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_string.lo: ./src/stdlib/SDL_string.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_thread.lo: ./src/thread/SDL_thread.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_timer.lo: ./src/timer/SDL_timer.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_RLEaccel.lo: ./src/video/SDL_RLEaccel.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_alphamult.lo: ./src/video/SDL_alphamult.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blendfillrect.lo: ./src/video/SDL_blendfillrect.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blendline.lo: ./src/video/SDL_blendline.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blendpoint.lo: ./src/video/SDL_blendpoint.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blendrect.lo: ./src/video/SDL_blendrect.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blit.lo: ./src/video/SDL_blit.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blit_0.lo: ./src/video/SDL_blit_0.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blit_1.lo: ./src/video/SDL_blit_1.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blit_A.lo: ./src/video/SDL_blit_A.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blit_N.lo: ./src/video/SDL_blit_N.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blit_auto.lo: ./src/video/SDL_blit_auto.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blit_copy.lo: ./src/video/SDL_blit_copy.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_blit_slow.lo: ./src/video/SDL_blit_slow.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_bmp.lo: ./src/video/SDL_bmp.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_drawline.lo: ./src/video/SDL_drawline.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_drawpoint.lo: ./src/video/SDL_drawpoint.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_drawrect.lo: ./src/video/SDL_drawrect.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_fillrect.lo: ./src/video/SDL_fillrect.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_gamma.lo: ./src/video/SDL_gamma.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_pixels.lo: ./src/video/SDL_pixels.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_rect.lo: ./src/video/SDL_rect.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_renderer_gl.lo: ./src/video/SDL_renderer_gl.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_renderer_gles.lo: ./src/video/SDL_renderer_gles.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_renderer_sw.lo: ./src/video/SDL_renderer_sw.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_stretch.lo: ./src/video/SDL_stretch.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_surface.lo: ./src/video/SDL_surface.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_video.lo: ./src/video/SDL_video.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_yuv_mmx.lo: ./src/video/SDL_yuv_mmx.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_yuv_sw.lo: ./src/video/SDL_yuv_sw.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_joystick.lo: ./src/joystick/SDL_joystick.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_haptic.lo: ./src/haptic/SDL_haptic.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_power.lo: ./src/power/SDL_power.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_nullevents.lo: ./src/video/dummy/SDL_nullevents.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_nullrender.lo: ./src/video/dummy/SDL_nullrender.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_nullvideo.lo: ./src/video/dummy/SDL_nullvideo.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_diskaudio.lo: ./src/audio/disk/SDL_diskaudio.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_dummyaudio.lo: ./src/audio/dummy/SDL_dummyaudio.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_sysloadso.lo: ./src/loadso/dlopen/SDL_sysloadso.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_cocoaevents.lo: ./src/video/cocoa/SDL_cocoaevents.m
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_cocoakeyboard.lo: ./src/video/cocoa/SDL_cocoakeyboard.m
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_cocoamodes.lo: ./src/video/cocoa/SDL_cocoamodes.m
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_cocoamouse.lo: ./src/video/cocoa/SDL_cocoamouse.m
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_cocoaopengl.lo: ./src/video/cocoa/SDL_cocoaopengl.m
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_cocoavideo.lo: ./src/video/cocoa/SDL_cocoavideo.m
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_cocoawindow.lo: ./src/video/cocoa/SDL_cocoawindow.m
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_x11dyn.lo: ./src/video/x11/SDL_x11dyn.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_x11events.lo: ./src/video/x11/SDL_x11events.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_x11gamma.lo: ./src/video/x11/SDL_x11gamma.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_x11keyboard.lo: ./src/video/x11/SDL_x11keyboard.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_x11modes.lo: ./src/video/x11/SDL_x11modes.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_x11mouse.lo: ./src/video/x11/SDL_x11mouse.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_x11opengl.lo: ./src/video/x11/SDL_x11opengl.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_x11opengles.lo: ./src/video/x11/SDL_x11opengles.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_x11render.lo: ./src/video/x11/SDL_x11render.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_x11video.lo: ./src/video/x11/SDL_x11video.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_x11window.lo: ./src/video/x11/SDL_x11window.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/imKStoUCS.lo: ./src/video/x11/imKStoUCS.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/AllCmap.lo: ./src/video/Xext/XmuStdCmap/AllCmap.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/CmapAlloc.lo: ./src/video/Xext/XmuStdCmap/CmapAlloc.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/CrCmap.lo: ./src/video/Xext/XmuStdCmap/CrCmap.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/DelCmap.lo: ./src/video/Xext/XmuStdCmap/DelCmap.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/Distinct.lo: ./src/video/Xext/XmuStdCmap/Distinct.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/LookupCmap.lo: ./src/video/Xext/XmuStdCmap/LookupCmap.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/StdCmap.lo: ./src/video/Xext/XmuStdCmap/StdCmap.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/VisCmap.lo: ./src/video/Xext/XmuStdCmap/VisCmap.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/XF86VMode.lo: ./src/video/Xext/Xxf86vm/XF86VMode.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/Xv.lo: ./src/video/Xext/Xv/Xv.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/Xinerama.lo: ./src/video/Xext/Xinerama/Xinerama.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_systhread.lo: ./src/thread/pthread/SDL_systhread.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_syssem.lo: ./src/thread/pthread/SDL_syssem.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_sysmutex.lo: ./src/thread/pthread/SDL_sysmutex.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_syscond.lo: ./src/thread/pthread/SDL_syscond.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_coreaudio.lo: ./src/audio/macosx/SDL_coreaudio.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_atomic.lo: ./src/atomic/macosx/SDL_atomic.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_sysjoystick.lo: ./src/joystick/darwin/SDL_sysjoystick.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_syshaptic.lo: ./src/haptic/darwin/SDL_syshaptic.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_syspower.lo: ./src/power/macosx/SDL_syspower.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@ 
$(objects)/SDL_systimer.lo: ./src/timer/unix/SDL_systimer.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@


$(objects)/SDL_dummy_main.o: ./src/main/dummy/SDL_dummy_main.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -MMD -MT $@ -c $< -o $@

$(objects)/$(TARGET): $(OBJECTS) $(VERSION_OBJECTS)
	$(LIBTOOL) --mode=link $(CC) -o $@ $(OBJECTS) $(VERSION_OBJECTS) $(LDFLAGS) $(EXTRA_LDFLAGS) $(LT_LDFLAGS)

$(objects)/$(SDLMAIN_TARGET): $(SDLMAIN_OBJECTS)
	$(AR) cru $@ $(SDLMAIN_OBJECTS)
	$(RANLIB) $@

install: all install-bin install-hdrs install-lib install-data
install-bin:
	$(SHELL) $(auxdir)/mkinstalldirs $(DESTDIR)$(bindir)
	$(INSTALL) -m 755 sdl-config $(DESTDIR)$(bindir)/sdl-config
install-hdrs:
	$(SHELL) $(auxdir)/mkinstalldirs $(DESTDIR)$(includedir)/SDL
	for file in $(HDRS); do \
	    $(INSTALL) -m 644 $(srcdir)/include/$$file $(DESTDIR)$(includedir)/SDL/$$file; \
	done
	$(INSTALL) -m 644 include/SDL_config.h $(DESTDIR)$(includedir)/SDL/SDL_config.h
install-lib: $(objects) $(objects)/$(TARGET) $(objects)/$(SDLMAIN_TARGET)
	$(SHELL) $(auxdir)/mkinstalldirs $(DESTDIR)$(libdir)
	$(LIBTOOL) --mode=install $(INSTALL) $(objects)/$(TARGET) $(DESTDIR)$(libdir)/$(TARGET)
	$(INSTALL) -m 644 $(objects)/$(SDLMAIN_TARGET) $(DESTDIR)$(libdir)/$(SDLMAIN_TARGET)
	$(RANLIB) $(DESTDIR)$(libdir)/$(SDLMAIN_TARGET)
install-data:
	$(SHELL) $(auxdir)/mkinstalldirs $(DESTDIR)$(datadir)/aclocal
	$(INSTALL) -m 644 $(srcdir)/sdl.m4 $(DESTDIR)$(datadir)/aclocal/sdl.m4
	$(SHELL) $(auxdir)/mkinstalldirs $(DESTDIR)$(libdir)/pkgconfig
	$(INSTALL) -m 644 sdl.pc $(DESTDIR)$(libdir)/pkgconfig

uninstall: uninstall-bin uninstall-hdrs uninstall-lib uninstall-data
uninstall-bin:
	rm -f $(DESTDIR)$(bindir)/sdl-config
uninstall-hdrs:
	for file in $(HDRS); do \
	    rm -f $(DESTDIR)$(includedir)/SDL/$$file; \
	done
	rm -f $(DESTDIR)$(includedir)/SDL/SDL_config.h
	-rmdir $(DESTDIR)$(includedir)/SDL
uninstall-lib:
	$(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(libdir)/$(TARGET)
	rm -f $(DESTDIR)$(libdir)/$(SDLMAIN_TARGET)
uninstall-data:
	rm -f $(DESTDIR)$(datadir)/aclocal/sdl.m4
	rm -f $(DESTDIR)$(libdir)/pkgconfig/sdl.pc

clean:
	rm -rf $(objects)
	if test -f test/Makefile; then (cd test; $(MAKE) $@); fi

distclean: clean
	rm -f Makefile include/SDL_config.h sdl-config
	rm -f SDL.qpg
	rm -f config.status config.cache config.log libtool
	rm -rf $(srcdir)/autom4te*
	find $(srcdir) \( \
	    -name '*~' -o \
	    -name '*.bak' -o \
	    -name '*.old' -o \
	    -name '*.rej' -o \
	    -name '*.orig' -o \
	    -name '.#*' \) \
	    -exec rm -f {} \;
	cp $(srcdir)/include/SDL_config.h.default $(srcdir)/include/SDL_config.h
	if test -f test/Makefile; then (cd test; $(MAKE) $@); fi

dist $(distfile):
	$(SHELL) $(auxdir)/mkinstalldirs $(distdir)
	tar cf - $(DIST) | (cd $(distdir); tar xf -)
	cp $(distdir)/include/SDL_config.h.default $(distdir)/include/SDL_config.h
	$(SHELL) $(distdir)/build-scripts/updaterev.sh
	rm -rf `find $(distdir) -name .svn`
	find $(distdir) \( \
	    -name '*~' -o \
	    -name '*.bak' -o \
	    -name '*.old' -o \
	    -name '*.rej' -o \
	    -name '*.orig' -o \
	    -name '.#*' \) \
	    -exec rm -f {} \;
	if test -f $(distdir)/test/Makefile; then (cd $(distdir)/test && make distclean); fi
	tar cvf - $(distdir) | gzip --best >$(distfile)
	rm -rf $(distdir)

rpm: $(distfile)
	rpmbuild -ta $?

# Run indent on the source to standardize coding style
indent:
	@echo "Running indent... modified files:"
	@cd $(srcdir) && \
	find . \( \
	    -name '*.h' -o \
	    -name '*.c' -o \
	    -name '*.cc' \) \
	    -print | fgrep -v ./Xcode | \
	while read file; do \
	    indent "$$file" -o "$$file.indent"; \
	    if cmp "$$file" "$$file.indent" >/dev/null; then \
	        rm -f "$$file.indent"; \
	    else \
	        echo "$$file"; \
	        mv -f "$$file.indent" "$$file"; \
	    fi; \
	done

# Run indent and then commit modified files
commit: indent
	svn commit

# Create a SVN snapshot that people can run update on
snapshot:
	$(SHELL) $(auxdir)/snapshot.sh
