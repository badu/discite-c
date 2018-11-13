#include <stdio.h>

int main(int argc, char *argv[]) {
	// create two arrays we care about
	int ages[] = {23, 43, 12, 89, 2};
	char *names[] = {
			"Alan", "Frank",
			"Mary", "John", "Lisa"
	};

	// safely get the size of ages
	int ages_count = sizeof(ages) / sizeof(int);
	int i;

	// first way using indexing
	for (i = 0; i < ages_count; i++) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}

	printf("---\n");

	// setup the pointers to the start of the arrays
	int *cur_age = (int *) names;
	// each name in names - the utilization of pointer to pointer...
	char **cur_name = names;

	// second way using pointers
	for (i = 0; i < ages_count; i++) {
		printf("%s is %d years old.\n", *(cur_name + i), *(ages + i));
	}

	printf("---\n");

	// third way, pointers are just arrays
	for (i = 0; i < ages_count; i++) {
		printf("%s is %d years old.\n", cur_name[i], ages[i]);
	}

	printf("---\n");

	// fourth way with pointers in a stupid complex way
	for (cur_name = names, cur_age = ages; (cur_age - ages) < ages_count; cur_name++, cur_age++) {
		printf("%s lived %d years so far.\n", *cur_name, *cur_age);
	}

	return 0;
}
