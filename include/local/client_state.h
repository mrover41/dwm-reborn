#pragma once

#include <types/monitor.h>

long getstate(Window w);
void setclientstate(Client *c, long state);
void setfullscreen(Client *c, int fullscreen);
void seturgent(Client *c, int urg);
void updatewindowtype(Client *c);
void updatewmhints(Client *c);
void updatetitle(Client *c);
