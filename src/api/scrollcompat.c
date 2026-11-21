/* scroll-compatible extras: scratchpad, modal resize, focus-mode toggle */

static unsigned int scratchprevtag = 0;
static int resizemode = 0;
static int scrollx = 0; /* horizontal offset of the ribbon in pixels */

struct ScrollEnt {
	Client *c;
	float wf;        /* width fraction of the monitor (0.5 = half screen) */
	float savedwf;   /* wf before Mod+1 expansion */
	int expanded;
	struct ScrollEnt *next;
};
static struct ScrollEnt *scrollents;

static struct ScrollEnt *
scrollent(Client *c)
{
	struct ScrollEnt *e;

	for (e = scrollents; e; e = e->next)
		if (e->c == c)
			return e;
	e = ecalloc(1, sizeof(*e));
	e->c = c;
	e->wf = e->savedwf = 0.5f;
	e->next = scrollents;
	scrollents = e;
	return e;
}

static void
scrollremove(Client *c)
{
	struct ScrollEnt *e, **pp;

	for (pp = &scrollents; (e = *pp); pp = &e->next)
		if (e->c == c) {
			*pp = e->next;
			free(e);
			return;
		}
}

static int
scrollwidth(struct ScrollEnt *e, Monitor *m)
{
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
static void
scrolltile(Monitor *m)
{
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

/* Same logic as scroll's maximize.lua: remember the width fraction,
 * expand to 1.0, restore on second press. */
static void
scrollmax(const Arg *arg)
{
	Client *c = selmon->sel;
	struct ScrollEnt *e;

	if (!c)
		return;
	if (selmon->lt[selmon->sellt]->arrange != scrolltile) {
		togglefullscr(arg);
		return;
	}
	e = scrollent(c);
	if (e->expanded) {
		e->expanded = 0;
		e->wf = e->savedwf;
	} else {
		e->savedwf = e->wf;
		e->expanded = 1;
	}
	arrange(selmon);
}

static void
scratchpush(const Arg *arg)
{
	Client *c = selmon->sel;
	unsigned int scratchtag = 1 << (LENGTH(tags) - 1);

	if (!c)
		return;
	scratchprevtag = selmon->tagset[selmon->seltags];
	c->tags = scratchtag;
	if (selmon->tagset[selmon->seltags] == scratchtag)
		view(&(Arg){ .ui = scratchprevtag });
	focus(NULL);
	arrange(selmon);
}

static void
scratchshow(const Arg *arg)
{
	Client *c;
	unsigned int scratchtag = 1 << (LENGTH(tags) - 1);

	if (selmon->tagset[selmon->seltags] == scratchtag) {
		view(&(Arg){ .ui = scratchprevtag });
		return;
	}
	for (c = selmon->clients; c && !(c->tags & scratchtag); c = c->next);
	if (c) {
		c->tags = scratchprevtag;
		view(&(Arg){ .ui = scratchprevtag });
		focus(c);
		arrange(selmon);
	} else {
		view(&(Arg){ .ui = scratchtag });
	}
}

static void
togglefocusmode(const Arg *arg)
{
	Client *c, *target = NULL;

	if (!selmon->sel)
		return;
	for (c = selmon->clients; c; c = c->next)
		if (c != selmon->sel && ISVISIBLE(c)
		&& c->isfloating != selmon->sel->isfloating) {
			target = c;
			break;
		}
	if (target) {
		focus(target);
		restack(target->mon);
	}
}

static void
cyclefocus(const Arg *arg)
{
	Client *c, *target = NULL, *first = NULL, *last = NULL;

	if (!selmon->sel)
		return;

	for (c = selmon->clients; c; c = c->next) {
		if (!ISVISIBLE(c))
			continue;
		if (!first)
			first = c;
		last = c;
	}
	if (!first || first == last)
		return;

	if (arg->i > 0) {
		for (c = selmon->sel->next; c; c = c->next)
			if (ISVISIBLE(c)) {
				target = c;
				break;
			}
		if (!target)
			target = first;
	} else {
		for (c = selmon->clients; c && c != selmon->sel; c = c->next)
			if (ISVISIBLE(c))
				target = c;
		if (!target)
			target = last;
	}

	if (target && target != selmon->sel) {
		focus(target);
		arrange(selmon); /* scrolltile recomputes the visible page here */
		restack(target->mon);
	}
}

static void
resizeby(const Arg *arg)
{
	Client *c = selmon->sel;
	int dw = 0, dh = 0;

	if (!c)
		return;
	switch (arg->i) {
	case 0: dw = -10; break;	/* left  / h: shrink width  */
	case 1: dw =  10; break;	/* right / l: grow width    */
	case 2: dh = -10; break;	/* up    / k: shrink height */
	case 3: dh =  10; break;	/* down  / j: grow height   */
	}

	if (c->isfloating || !selmon->lt[selmon->sellt]->arrange) {
		if (dw) {
			c->w = MAX(1, c->w + dw);
			resizeclient(c, c->x, c->y, c->w, c->h);
		}
		if (dh) {
			c->h = MAX(1, c->h + dh);
			resizeclient(c, c->x, c->y, c->w, c->h);
		}
	} else if (selmon->lt[selmon->sellt]->arrange == scrolltile) {
		if (dw) {
			struct ScrollEnt *e = scrollent(c);
			e->expanded = 0;
			e->wf = MAX(0.2f, MIN(1.0f, e->wf + (dw > 0 ? 0.05f : -0.05f)));
			e->savedwf = e->wf;
		}
		arrange(selmon);
	} else {
		if (dw)
			selmon->mfact = MAX(0.05, MIN(0.95, selmon->mfact + (dw > 0 ? 0.05 : -0.05)));
		if (dh)
			selmon->nmaster = MAX(0, selmon->nmaster + (dh > 0 ? 1 : -1));
		arrange(selmon);
	}
	drawbar(selmon);
}

static void
toggleresizemode(const Arg *arg)
{
	static const KeySym resizekeys[] = {
		XK_h, XK_j, XK_k, XK_l,
		XK_Left, XK_Down, XK_Up, XK_Right,
		XK_Return, XK_Escape
	};
	size_t i;

	resizemode = !resizemode;
	for (i = 0; i < LENGTH(resizekeys); i++) {
		KeyCode kc = XKeysymToKeycode(dpy, resizekeys[i]);
		if (!kc)
			continue;
		if (resizemode)
			XGrabKey(dpy, kc, 0, root, True, GrabModeAsync, GrabModeAsync);
		else
			XUngrabKey(dpy, kc, 0, root);
	}
}
