#pragma once

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

typedef struct Fnt {
	Display *dpy;
	unsigned int h;
	XftFont *xfont;
	FcPattern *pattern;
	struct Fnt *next;
} Fnt;
