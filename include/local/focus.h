#pragma once

#include <types/monitor.h>

void focus(Client *c);
void setfocus(Client *c);
void unfocus(Client *c, int setfocus);
Client *nexttagged(Client *c);
Client *nexttiled(Client *c);
