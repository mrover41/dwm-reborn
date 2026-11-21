#include <api/focus.h>

#include <local/focus.h>

#include <types/monitor.h>
#include <local/geometry.h>
#include <local/client_stack.h>

#include <global.h>
#include <config.h>

#ifndef ISVISIBLE
#define ISVISIBLEONTAG(C, T)    ((C->tags & T))
#define ISVISIBLE(C) ISVISIBLEONTAG(C, C->mon->tagset[C->mon->seltags])
#endif

void
focusmon(const Arg *arg) {
	Monitor *m;

	if (!mons->next)
		return;
	if ((m = dirtomon(arg->i)) == selmon)
		return;
	unfocus(selmon->sel, 0);
	selmon = m;
	focus(NULL);
}

void
focusstack(const Arg *arg) {
	Client *c = NULL, *i;

	if (!selmon->sel || (selmon->sel->isfullscreen && lockfullscreen))
		return;
	if (arg->i > 0) {
		for (c = selmon->sel->next; c && !ISVISIBLE(c); c = c->next);
		if (!c)
			for (c = selmon->clients; c && !ISVISIBLE(c); c = c->next);
	} else {
		for (i = selmon->clients; i != selmon->sel; i = i->next)
			if (ISVISIBLE(i))
				c = i;
		if (!c)
			for (; i; i = i->next)
				if (ISVISIBLE(i))
					c = i;
	}
	if (c) {
		focus(c);
		restack(selmon);
	}
}
