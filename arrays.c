#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Shorthand notation
-----
```int array[10] = {[0 ... 3]1, [6 ... 9]2};``` is the same with ```array[10] = {1, 1, 1, 1, 0, 0, 2, 2, 2, 2};```
 */

void print_array(int *arr, int m, int n) {
	printf("\nPrinting array:\n");
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", *((arr + i * n) + j));
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	int numbers[4] = {0};

	int a[][2][2] = {{{1, 2}, {3, 4}},
					 {{5, 6}, {7, 8}}
	}; // Works
	printf("%d", sizeof(a)); // prints 8*sizeof(int)

	// This line is same as int array[10] = {1, 1, 1, 1, 0, 0, 2, 2, 2, 2};
	// This is called shorthand array notation
	int array[10] = {[0 ... 3]1, [6 ... 9]2};
	int *ptr_to_array = array;
	printf("Size of ptr (same for all type of pointers) : %d\n", sizeof(ptr_to_array));
	// first, print them out raw
	printf("numbers: %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3]);
	// setup the numbers
	numbers[0] = 1;
	numbers[1] = 2;
	numbers[2] = 3;
	numbers[3] = 4;
	printf("numbers: %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3]);

	int first_array[2] = {10, 11};
	printf("First Element = %d\n", first_array[0]);
	// now the weird part
	printf("Same First Element = %d and second element = %d\n", 0[first_array], *(1 + first_array));
	int arr_size = sizeof(first_array) / sizeof(first_array[0]); /* incorrect use of siseof*/
	// note the correct usage of sizeof
	for (int i = 0; i < sizeof(first_array) / sizeof(first_array[0]); i++) {
		printf("Element %d is %d\n", i, *(i + first_array));
	}
	int r = 3, c = 4;
	// 1) using a single pointer
	int *single_pointer_array = (int *) malloc(r * c * sizeof(int));

	int i, j, count = 0;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			*(single_pointer_array + i * c + j) = ++count;
		}
	}
	print_array(single_pointer_array, r, c);

	// 2) using an array of pointers
	int *array_of_pointers[r];
	for (i = 0; i < r; i++) {
		array_of_pointers[i] = (int *) malloc(c * sizeof(int));
	}

	// Note that array_of_pointers[i][j] is same as *(*(array_of_pointers+i)+j)
	count = 0;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			array_of_pointers[i][j] = ++count;
		}
	} // Or *(*(array_of_pointers+i)+j) = ++count

	print_array(array_of_pointers, r, c);

	// 3) using pointer to a pointer
	int **pointer_to_pointer_array = (int **) malloc(r * sizeof(int *));
	for (i = 0; i < r; i++) {
		pointer_to_pointer_array[i] = (int *) malloc(c * sizeof(int));
	}

	// Note that pointer_to_pointer_array[i][j] is same as *(*(pointer_to_pointer_array+i)+j)
	count = 0;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			pointer_to_pointer_array[i][j] = ++count;
		}
	}  // OR *(*(pointer_to_pointer_array+i)+j) = ++count

	print_array(pointer_to_pointer_array, r, c);

	int len = 0;
	int **double_pointer, *ptr;
	//4 ) one malloc and double pointer
	len = sizeof(int *) * r + sizeof(int) * c * r;
	double_pointer = (int **) malloc(len);

	// ptr is now pointing to the first element in of 2D array
	ptr = double_pointer + r;

	// for loop to point rows pointer to appropriate location in 2D array
	for (i = 0; i < r; i++) {
		double_pointer[i] = (ptr + c * i);
	}

	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			double_pointer[i][j] = ++count;
		}
	} // OR *(*(double_pointer+i)+j) = ++count

	print_array(double_pointer, r, c);

	// explanation for pointer to bidimensional array
	int nums[2][3]  =  { {16, 18, 20}, {25, 26, 27} };
	//*(*(nums + 0) + 0)	nums[0][0]	16
	//*(*(nums + 0) + 1)	nums[0][1]	18
	//*(*(nums + 0) + 2)	nums[0][2]	20
	//*(*(nums + 1) + 0)	nums[1][0]	25
	//*(*(nums + 1) + 1)	nums[1][1]	26
	//*(*(nums + 1) + 2)	nums[1][2]	27
	return 0;
}