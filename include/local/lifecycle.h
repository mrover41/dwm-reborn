#pragma once

#include <types/monitor.h>

void checkotherwm(void);
void grabbuttons(Client *c, int focused);
void grabkeys(void);
void runautostart(void);
void scan(void);
void updatenumlockmask(void);
