#define DWM_CONFIG_LAYOUTS
#include <config.h>

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include <api/lifecycle.h>
#include <api/util.h>
#include <global.h>
#include <local/lifecycle.h>

int
main(int argc, char *argv[]) {
	if (argc == 2 && !strcmp("-v", argv[1]))
		die("dwm-"VERSION);
	else if (argc != 1)
		die("usage: dwm [-v]");
	if (!setlocale(LC_CTYPE, "") || !XSupportsLocale())
		fputs("warning: no locale support\n", stderr);
	if (!(dpy = XOpenDisplay(NULL)))
		die("dwm: cannot open display");
	checkotherwm();
	setup();
#ifdef __OpenBSD__
	if (pledge("stdio rpath proc exec", NULL) == -1)
		die("pledge");
#endif
	scan();
	runautostart();
	run(); //event loop

	cleanup();
	XCloseDisplay(dpy);
	return EXIT_SUCCESS;
}
