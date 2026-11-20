#pragma once

#include <types/monitor.h>
#include <X11/Xlib.h>

void applyrules(Client *c);
void configure(Client *c);
void manage(Window w, XWindowAttributes *wa);
void unmanage(Client *c, int destroyed);
int sendevent(Client *c, Atom proto);
Atom getatomprop(Client *c, Atom prop);
int gettextprop(Window w, Atom atom, char *text, unsigned int size);
Client *wintoclient(Window w);
void showhide(Client *c);
