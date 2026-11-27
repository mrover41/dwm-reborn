#include <stdlib.h>

#include <layouts/scrolltile.h>

#include <api/util.h>
#include <local/focus.h>
#include <local/geometry.h>
#include <local/handlers.h>

#include <macros.h>

static int scrollx = 0; /* horizontal offset of the ribbon in pixels */
static struct ScrollEnt *scrollents;

struct ScrollEnt *
scrollent(Client *c) {
	struct ScrollEnt *e;

	for (e = scrollents; e; e = e->next)
		if (e->c == c)
			return e;
	e = ecalloc(1, sizeof(*e));
	e->c = c;
	e->wf = e->savedwf = 0.5f;
	e->next = scrollents;
	scrollents = e;

	c->layout_destroy = scrollremove;
	return e;
}

void
scrollremove(Client *c) {
	struct ScrollEnt *e, **pp;

	for (pp = &scrollents; (e = *pp); pp = &e->next)
		if (e->c == c) {
			*pp = e->next;
			free(e);
			return;
		}
}

static int
scrollwidth(struct ScrollEnt *e, Monitor *m) {
	float f = e->expanded ? 1.0f : e->wf;
	int w = (int)(m->ww * f);

	if (w < m->ww / 8)
		w = m->ww / 8;
	if (w > m->ww)
		w = m->ww;
	return w;
}

/* Scrollable ribbon.
 * All windows keep their natural sequential coordinates (cumulative widths).
 * We only add a global scrollx offset to every window, exactly like panning a
 * long strip. scrollx is nudged just enough to keep the focused column visible.
 * No size hints here: columns keep their exact requested width. */
void
scrolltile(Monitor *m) {
	int cum = 0, w;
	Client *c;
	struct ScrollEnt *e;

	for (c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
		e = scrollent(c);
		w = scrollwidth(e, m);
		if (c == m->sel) {
			if (cum < scrollx)
				scrollx = cum;
			else if (cum + w > scrollx + m->ww)
				scrollx = cum + w - m->ww;
		}
		cum += w;
	}

	for (c = nexttiled(m->clients), cum = 0; c; c = nexttiled(c->next)) {
		e = scrollent(c);
		w = scrollwidth(e, m);
		resizeclient(c,
		             m->wx + cum - scrollx,
		             m->wy,
		             w - 2 * c->bw,
		             m->wh - 2 * c->bw);
		cum += w;
	}
}

void
attachaside(Client *c) {
	Client *at = c->mon->sel;

	if (!at || at == c || at->isfloating || !ISVISIBLEONTAG(at, c->tags))
		at = nexttagged(c);
	if (!at) {
		attachlast(c);
		return;
	}
	c->next = at->next;
	at->next = c;
}

void
attachlast(Client *c) {
	Client **pp;

	for (pp = &c->mon->clients; *pp; pp = &(*pp)->next);
	*pp = c;
	c->next = NULL;
}
