#include <api/bar.h>

#include <local/bar.h>
#include <local/monitor.h>

#include <global.h>

void
togglebar(const Arg *arg) {
	selmon->showbar = !selmon->showbar;
	updatebarpos(selmon);
	XMoveResizeWindow(dpy, selmon->barwin, selmon->wx, selmon->by, selmon->ww, bh);
	arrange(selmon);
}
