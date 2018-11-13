#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// A structure of type student
struct student {
	int stud_id;
	int name_len;
	int struct_size;
	char stud_name[0]; //variable length array must be last.
};

typedef struct student stu; // thus avoiding struct student *result in declaration below?

//Memory allocation and initialisation of structure
struct student *createStudent(stu *result, int id, char a[]) {
	int name_size = strlen(a);
	int struct_size = sizeof(*result) + sizeof(char) * name_size;
	result = malloc(struct_size);
	assert(result != NULL);
	strcpy(result->stud_name, a);

	result->stud_id = id;
	result->name_len = name_size;
	result->struct_size = struct_size;
	return result;
}

// Print student details
void printStudent(struct student *who) {
	assert(who != NULL);
	printf("Student_id : %d\n"
		   "Stud_Name  : %s\n"
		   "Name_Length: %d\n"
		   "Allocated_Struct_size: %d\n\n",
		   who->stud_id, who->stud_name, who->name_len, who->struct_size);

	//Value of Allocated_Struct_size here is in bytes.
}

void student_destroy(struct student *who) {
	assert(who != NULL);
	who->stud_name[0] = '\0';// cleanup name - however, it doesn't get freed! why?
	who = NULL;
	free(who);
}

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight) {
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);
	who->name = strdup(name);
	who->age = age;
	who->height = height;
	who->weight = weight;
	return who;
}

void Person_destroy(struct Person *who) {
	assert(who != NULL);
	free(who->name);
	free(who);
}

void Person_print(struct Person *who) {
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
}

bool pointer_allocated(void *ptr) {
	return ptr != NULL;
}

int main(int argc, char *argv[]) {
	struct student *s1, *s2;
	char *s1name = "Bogdan";
	char *s2name = "Gabriel";
	s1 = createStudent(s1, 444, s1name);
	s2 = createStudent(s1, 555, s2name);

	printStudent(s1);
	printStudent(s2);
	printf("s1 is at memory location %p:\n", s1);

	//free(s1name);
	//free(s2name);

	student_destroy(s1);
	student_destroy(s2);

	if (pointer_allocated(s1)) {
		printf("s1 is still allocated at memory location %p:\n", s1);
	}
	printStudent(s1);
	printStudent(s2);

	// make two people structures
	struct Person *joe = Person_create("Joe Alex", 32, 64, 140);

	struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

	// print them out and where they are in memory
	printf("Joe is at memory location %p:\n", joe);
	Person_print(joe);

	printf("Frank is at memory location %p:\n", frank);
	Person_print(frank);

	// make everyone age 20 years and print them again
	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	Person_print(joe);

	frank->age += 20;
	frank->weight += 20;
	free(frank);
	printf("Frank was destroyed. Let's print him : %p\n", frank);
	Person_print(frank);
	// destroy them both so we clean up
	Person_destroy(joe);
	Person_destroy(frank);

	return 0;
}