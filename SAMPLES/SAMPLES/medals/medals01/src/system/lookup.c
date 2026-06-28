/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "lookup.h"

static Lookup  head;
static Lookup *tail;

static void addLookup(char *name, long value);

void initLookups(void)
{
	memset(&head, 0, sizeof(Lookup));
	tail = &head;

	addLookup("MEDAL_BRONZE", MEDAL_BRONZE);
	addLookup("MEDAL_SILVER", MEDAL_SILVER);
	addLookup("MEDAL_GOLD", MEDAL_GOLD);
	addLookup("MEDAL_RUBY", MEDAL_RUBY);
}

long lookup(char *name)
{
	Lookup *l;

	for (l = head.next; l != NULL; l = l->next)
	{
		if (strcmp(l->name, name) == 0)
		{
			return l->value;
		}
	}

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "No such lookup value '%s'", name);

	exit(1);

	return 0;
}

char *getLookupName(char *prefix, long num)
{
	Lookup *l;

	for (l = head.next; l != NULL; l = l->next)
	{
		if (l->value == num && strncmp(prefix, l->name, strlen(prefix)) == 0)
		{
			return l->name;
		}
	}

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "No such lookup value %ld, prefix=%s", num, prefix);

	exit(1);

	return "";
}

static void addLookup(char *name, long value)
{
	Lookup *lookup;

	lookup = malloc(sizeof(Lookup));
	memset(lookup, 0, sizeof(Lookup));
	tail->next = lookup;
	tail = lookup;

	STRNCPY(lookup->name, name, MAX_NAME_LENGTH);
	lookup->value = value;
}
