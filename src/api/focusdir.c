/*void
focusdir(const Arg *arg)
{
	Client *s = selmon->sel, *f = NULL, *c, *next;

	if (!s)
		return;

	unsigned int score = -1;
	unsigned int client_score;
	int dist = 0;
	int dirweight = 20;
	int isfloating = s->isfloating;

	next = s->next;
	if (!next)
		next = selmon->clients;
	for (c = next; c != s; c = next) {
		next = c->next;
		if (!next)
			next = selmon->clients;

		if (!ISVISIBLE(c) || c->isfloating != isfloating)
			continue;

		switch (arg->i) {
		case 0:
			dist = s->x - c->x - c->w;
			client_score = dirweight * MIN(abs(dist), abs(dist + s->mon->ww)) + abs(s->y - c->y);
			break;
		case 1:
			dist = c->x - s->x - s->w;
			client_score = dirweight * MIN(abs(dist), abs(dist + s->mon->ww)) + abs(c->y - s->y);
			break;
		case 2:
			dist = s->y - c->y - c->h;
			client_score = dirweight * MIN(abs(dist), abs(dist + s->mon->wh)) + abs(s->x - c->x);
			break;
		default:
		case 3:
			dist = c->y - s->y - s->h;
			client_score = dirweight * MIN(abs(dist), abs(dist + s->mon->wh)) + abs(c->x - s->x);
			break;
		}

		if (((arg->i == 0 || arg->i == 2) && dist <= 0) ||
		    ((arg->i == 1 || arg->i == 3) && dist >= 0))
			client_score += 10000;

		if (client_score < score) {
			score = client_score;
			f = c;
		}
	}

	if (f && f != s) {
		focus(f);
		restack(f->mon);
	}
}*/

/* Keep this translation unit non-empty for -pedantic. */
typedef int focusdir_placeholder;
