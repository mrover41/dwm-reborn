#pragma once

#include <types/monitor.h>

int applysizehints(Client *c, int *x, int *y, int *w, int *h, int interact);
void updatesizehints(Client *c);
void resize(Client *c, int x, int y, int w, int h, int interact);
void resizeclient(Client *c, int x, int y, int w, int h);
int getrootptr(int *x, int *y);
Monitor *recttomon(int x, int y, int w, int h);
Monitor *dirtomon(int dir);
int updategeom(void);
