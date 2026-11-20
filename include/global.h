#pragma once //TODO: разобрать чо за переменные и уменьшить их количество тут

#include <X11/Xlib.h>

#include <types/monitor.h>
#include <enums/atoms.h>

extern Monitor *mons, *selmon;
extern Atom wmatom[WMLast], netatom[NetLast];
extern Display *dpy;
extern Window root, wmcheckwin;
