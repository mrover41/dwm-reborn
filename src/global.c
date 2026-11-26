#include <global.h>

Monitor *mons, *selmon;
Atom wmatom[WMLast], netatom[NetLast];
Display *dpy;
Window root, wmcheckwin;
int running = 1;
int bh;
int screen;
int sw, sh;
int lrpad;
unsigned int numlockmask = 0;
char stext[256];
int (*xerrorxlib)(Display *, XErrorEvent *) = NULL;

Cur *cursor[CurLast] = {0};
Drw *drw = NULL;
Clr **scheme = NULL;

const char autostartblocksh[] = "autostart_blocking.sh";
const char autostartsh[] = "autostart.sh";
const char broken[] = "broken";
const char dwmdir[] = "dwm";
const char localshare[] = ".local/share";
