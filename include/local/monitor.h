#pragma once

#include <types/monitor.h>

void arrange(Monitor *m);
void arrangemon(Monitor *m);
Monitor *createmon(void);
void cleanupmon(Monitor *mon);
void sendmon(Client *c, Monitor *m);
Monitor *wintomon(Window w);
void updateclientlist(void);
