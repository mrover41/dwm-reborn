#pragma once //TODO: разобрать чо за переменные и уменьшить их количество тут

#include <X11/Xlib.h>

#include <types/monitor.h>
#include <enums/atoms.h>

extern Monitor *mons, *selmon;
extern Atom wmatom[WMLast], netatom[NetLast];
extern Display *dpy;
extern Window root, wmcheckwin;
extern int running;
extern int bh;
extern int screen;
extern int sw, sh;
extern int lrpad;
extern unsigned int numlockmask;
extern char stext[256];
extern int (*xerrorxlib)(Display *, XErrorEvent *);

#include <types/cursor.h>
#include <types/clr.h>
#include <enums/cursor.h>

extern Cur *cursor[CurLast];
extern Clr **scheme;

#include <types/drw.h>
extern Drw *drw;

extern const char autostartblocksh[];
extern const char autostartsh[];
extern const char broken[];
extern const char dwmdir[];
extern const char localshare[];
