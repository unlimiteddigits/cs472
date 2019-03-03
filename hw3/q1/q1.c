do {
	waiting[i] = true;
	key = true;
	while (waiting[i] && key)
		key = test and set(&lock);
	waiting[i] = false;
	/* critical section */
	j = (i + 1) % n;
	while ((j != i) && !waiting[j])
		j = (j + 1) % n;
	if (j == i)
		lock = false;
	else
		waiting[j] = false;
	/* remainder section */
} while (true)5;