#pragma once

#include <types/args.h>

#define ISVISIBLEONTAG(C, T)    ((C->tags & T))
#define ISVISIBLE(C)            ISVISIBLEONTAG(C, C->mon->tagset[C->mon->seltags])

void focusmon(const Arg *arg);
void focusstack(const Arg *arg);
