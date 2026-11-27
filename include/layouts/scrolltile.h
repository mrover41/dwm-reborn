#pragma once

#include <types/monitor.h>

struct ScrollEnt {
	Client *c;
	float wf;        /* width fraction of the monitor (0.5 = half screen) */
	float savedwf;   /* wf before Mod+1 expansion */
	int expanded;
	struct ScrollEnt *next;
};

void scrolltile(Monitor *m);
struct ScrollEnt *scrollent(Client *c);
void scrollremove(Client *c);

void attachaside(Client *);
void attachlast(Client *);
