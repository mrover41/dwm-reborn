#include <string.h>

#include <api/util.h>
#include <api/commands.h>
#include <global.h>
#include <config.h>
#include <local/bar.h>
#include <local/monitor.h>

void
cyclelayout(const Arg *arg) {
	int n, idx = 0, step, i;

	if (!selmon)
		return;

	n = (int)layoutcount();
	if (n <= 0)
		return;

	for (i = 0; i < n; i++)
		if (&layouts[i] == selmon->lt[selmon->sellt]) {
			idx = i;
			break;
		}

	step = (arg && arg->i) ? arg->i : 1;
	for (i = 0; i < n; i++) {
		idx = ((idx + step) % n + n) % n;
		if (layouts[idx].arrange)
			break;
	}
	if (!layouts[idx].arrange)
		return;

	selmon->lt[selmon->sellt] = &layouts[idx];
	strncpy(selmon->ltsymbol, layouts[idx].symbol, sizeof selmon->ltsymbol);

	if (selmon->sel)
		arrange(selmon);
	else
		drawbar(selmon);
}
