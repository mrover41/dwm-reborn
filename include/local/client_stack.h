#pragma once

#include <types/monitor.h>

void attach(Client *c);
void attachaside(Client *c);
void attachlast(Client *c);
void push_focus(Client *c);
void detach(Client *c);
void detachstack(Client *c);
void pop(Client *c);
void restack(Monitor *m);
