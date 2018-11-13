#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getString() {
	char *str = "Shared"; /* Stored in read only part of shared segment */
	/* No problem: remains at address str after getString() returns */
	return str;
}

char *getOkString() {
	int size = 4;
	char *str = (char *) malloc(sizeof(char) * size); /*Stored in heap segment*/
	*(str + 0) = 'D';
	*(str + 1) = 'a';
	*(str + 2) = 'a';
	*(str + 3) = '\0';

	/* No problem: string remains at str after getString() returns */
	return str;
}

char *getStackString() {
	char str[] = "Stack"; /* Stored in stack segment */
	/* Problem: string may not be present after getStackString() returns */
	return str;
}

/* Swaps strings by swapping pointers */
void swap_strings_pointers(char **str1_ptr, char **str2_ptr) {
	char *temp = *str1_ptr;
	*str1_ptr = *str2_ptr;
	*str2_ptr = temp;
}

/* Swaps strings by swapping data */
void swap_strings_data(char *str1, char *str2) {
	char *temp = (char *) malloc((strlen(str1) + 1) * sizeof(char));
	strcpy(temp, str1);
	strcpy(str1, str2);
	strcpy(str2, temp);
	free(temp);
}

int main(int argc, char *argv[]) {
/**

 Difference between pointer and array in C
------
```
char a[]="Amsterdam";
char *s ="Stockholm";
```

* a is an array, with sizeOf(a) of 8 bytes.
* p is a pointer, with sizeOf(p) of 4 bytes.
* a and &a are the same.
* p and &p are NOT the same.
* "Amsterdam" is stored in stack section of the memory.
* p is stored at stack, but "Stockholm" is stored in code section of the memory.
* ```char str_const[10]="Bucharest"; str_const = "Hello";``` // is invalid because str_const is an address and "Hello" is also an address.
* ```char *city = "Romania"; city = "Galati";```// is valid, because we're loading the pointer of "Galati" into p.
* a++ is invalid
* p++ is valid

 */
	char amsterdam[] = "Amsterdam";
	char *stockholm = "Stockholm";
	printf("Size of Amsterdam = %d and size of Stockholm = %d\n", sizeof(amsterdam), sizeof(stockholm));
	printf("[Amsterdam] %s == [Amsterdam] %s\n", amsterdam, &amsterdam);
	printf("[Stockholm] %s != [Stockholm] %p\n", stockholm, &stockholm);
	stockholm++;
	printf("[Stockholm++] = `%s`\n", stockholm);// gives you "tockholm" after incrementing the pointer

	char str_const[10] = "Bucharest";
	// str_const = "Hello"; // yeap, not assignable

	char *city = "Romania";
	city = "Galati";
	printf("City : %s\n", city);

	char name[4] = {'B', 'A', 'D', 'U'};
	printf("name each: %c %c %c %c\nname full : %s.\n", name[0], name[1], name[2], name[3], name);
	fflush(stdout);
	// setup the name - to lowercase
	name[0] = name[0] | 0x20;
	name[1] = name[1] | 0x20;
	name[2] = name[2] | 0x20;
	name[3] = name[3] | 0x20;

	// then print them out initialized
	printf("name lower: %c %c %c %c\nname lower full : %s.\n", name[0], name[1], name[2], name[3], name);
	fflush(stdout);
	// another way to use name
	char *another = "BaDu";
	// if string is quoted, it will end up with '\0' else - it doesn't
	char nonZeroEnding = 'bAdU'; // cannot be printed as string because %s display a string. The argument is a pointer to char. Characters are displayed until a '\0' is encountered, or until the number of characters indicated by the precision have been displayed. (The terminating '\0' is not output.)
	// as compiler says, nonZeroEnding is actually an integer

	printf("another each: %c %c %c %c = %s [sized %d each %d byte]\n", another[0], another[1], another[2], another[3], another, sizeof(another), sizeof(another[0]));

	printf("another: %s of size %d and the size of the one without zero ending %d \n", another, sizeof(another), sizeof(nonZeroEnding));

	int areas[] = {10, 12, 13, 14, 20};

	char full_name[] = {
			'D', 'a', 'd',
			' ', 'Q', '.', ' ',
			'F', 'o', 'o', 'w'
	};

	// WARNING: On some systems you may have to change the
	// %ld in this code to a %u since it will use unsigned ints
	printf("The size of an int: %ld\n", sizeof(int));
	printf("The size of areas (int[]): %ld\n", sizeof(areas));
	printf("The number of ints in areas: %ld\n", sizeof(areas) / sizeof(int));
	printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);

	printf("The size of a char: %ld\n", sizeof(char));
	printf("The size of name (char[]): %ld\n", sizeof(name));
	printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));

	printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
	printf("The number of chars: %ld\n", sizeof(full_name) / sizeof(char));

	// allocation memory to out of bound element... and it doesn't segmentation fault
	full_name[12] = 'X';

	printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

	// 1) read only string
	char *str = "GfG";
	//*(str + 1) = 'n'; // yeap, this crashes

	// 2) dynamically allocated in heap string
	char *str2;
	int size = 4; /*one extra for ‘\0’*/
	str2 = (char *) malloc(sizeof(char) * size);
	*(str2 + 0) = 'A';
	*(str2 + 1) = 'S';
	*(str2 + 2) = 'D';
	*(str2 + 3) = '\0';
	char *r = getOkString();
	char *ss = getString();
	printf("SS : %s - R : %s - Stack string : %s STR2 : %s\n", ss, r, getStackString(), str2);
	free(r);
	// free(ss);// cannot be freed!
	printf("Post mortem R : `%s`\n\n", r);

	int i = 247593;
	char strconv[10];

	sprintf(strconv, "%d", i);
	printf("And the last string is : %c%c%c.%c%c%c\n", strconv[0],strconv[1],strconv[2],strconv[3],strconv[4],strconv[5]);

	// let's make our own array of strings
	char *states[] = {
			"California", "Oregon",
			"Washington", "Texas"
	};
	printf("%d states.\n", sizeof(states)/ sizeof(__ptr_t));

	int num_states = sizeof(states)/ sizeof(__ptr_t);

	for (i = 0; i < num_states; i++) {
		printf("state %d: %s\n", i, states[i]);
	}

	fflush(stdout);
	return 0;
}


