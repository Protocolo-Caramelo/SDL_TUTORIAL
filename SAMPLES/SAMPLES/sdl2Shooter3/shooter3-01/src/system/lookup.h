/*
 * Copyright (C) 2023 Parallel Realities. All rights reserved.
 */

void        initLookups(void);
long        lookup(const char *name);
char	   *getLookupName(const char *prefix, long num);
const char *getFlagValues(const char *prefix, long flags);
