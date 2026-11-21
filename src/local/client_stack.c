#include <X11/Xlib.h>
#include <local/client_stack.h>

#include <local/focus.h>
#include <local/bar.h>
#include <local/monitor.h>

#include <macros.h>
#include <global.h>
#include <config.h>

void attach(Client *c) {
	if (selmon->lt[selmon->sellt]->attach != NULL) {
		selmon->lt[selmon->sellt]->attach(c);
		return;
	}
	c->next = c->mon->clients;
	c->mon->clients = c;
}
void push_focus(Client *c) {
	if (selmon->lt[selmon->sellt]->push_focus != NULL) {
		selmon->lt[selmon->sellt]->push_focus(c);
		return;
	}
	c->snext = c->mon->stack;
	c->mon->stack = c;
}
void detach(Client *c) {
	if (selmon->lt[selmon->sellt]->push_focus != NULL) {
		selmon->lt[selmon->sellt]->push_focus(c);
		return;
	}

	Client **tc, *t;

	for (tc = &c->mon->stack; *tc && *tc != c; tc = &(*tc)->snext);
	*tc = c->snext;

	if (c == c->mon->sel) {
		for (t = c->mon->stack; t && !ISVISIBLE(t); t = t->snext);
		c->mon->sel = t;
	}
}
void detachstack(Client *c) {
	if (selmon->lt[selmon->sellt]->detachstack != NULL) {
		selmon->lt[selmon->sellt]->detachstack(c);
		return;
	}

	Client **tc, *t;

	for (tc = &c->mon->stack; *tc && *tc != c; tc = &(*tc)->snext);
	*tc = c->snext;

	if (c == c->mon->sel) {
		for (t = c->mon->stack; t && !ISVISIBLE(t); t = t->snext);
		c->mon->sel = t;
	}
}
void pop(Client *c) {
	if (selmon->lt[selmon->sellt]->pop != NULL) {
		selmon->lt[selmon->sellt]->pop(c);
		return;
	}

	detach(c);
	attach(c);
	focus(c);
	arrange(c->mon);
}
void restack(Monitor *m) {
	if (selmon->lt[selmon->sellt]->restack != NULL) {
		selmon->lt[selmon->sellt]->restack(m);
		return;
	}

	Client *c;
	XEvent ev;
	XWindowChanges wc;

	drawbar(m);
	if (!m->sel)
		return;
	if (m->sel->isfloating || !m->lt[m->sellt]->arrange)
		XRaiseWindow(dpy, m->sel->win);
	if (m->lt[m->sellt]->arrange) {
		wc.stack_mode = Below;
		wc.sibling = m->barwin;
		for (c = m->stack; c; c = c->snext)
			if (!c->isfloating && ISVISIBLE(c)) {
				XConfigureWindow(dpy, c->win, CWSibling|CWStackMode, &wc);
				wc.sibling = c->win;
			}
	}
	XSync(dpy, False);
	while (XCheckMaskEvent(dpy, EnterWindowMask, &ev));
}
