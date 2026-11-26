#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>

void buttonpress(XEvent *e);
void clientmessage(XEvent *e);
void configurerequest(XEvent *e);
void configurenotify(XEvent *e);
void destroynotify(XEvent *e);
void enternotify(XEvent *e);
void expose(XEvent *e);
void focusin(XEvent *e);
void keypress(XEvent *e);
void mappingnotify(XEvent *e);
void maprequest(XEvent *e);
void motionnotify(XEvent *e);
void propertynotify(XEvent *e);
void unmapnotify(XEvent *e);

extern void (*handler[LASTEvent]) (XEvent *);
