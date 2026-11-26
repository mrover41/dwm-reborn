#pragma once

#include <X11/Xlib.h>
#include <types/clr.h>
#include <types/fnt.h>

typedef struct {
	unsigned int w, h;
	Display *dpy;
	int screen;
	Window root;
	Drawable drawable;
	GC gc;
	Clr *scheme;
	Fnt *fonts;
} Drw;
