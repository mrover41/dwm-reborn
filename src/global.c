#include <global.h>

Monitor *mons, *selmon;
Atom wmatom[WMLast], netatom[NetLast];
Display *dpy;
Window root, wmcheckwin;
int running = 1;
int bh;
int screen;
int sw, sh;
int bh;
int lrpad;

const char autostartblocksh[] = "autostart_blocking.sh";
const char autostartsh[] = "autostart.sh";
const char broken[] = "broken";
const char dwmdir[] = "dwm";
const char localshare[] = ".local/share";
