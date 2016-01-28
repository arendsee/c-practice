#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

struct Person {
    char * name;
    int age;
};

struct Person * create_person(char * name, int age){
    struct Person * person = malloc(sizeof(struct Person));
    assert(person != NULL);
    /* I could just set person name to name, but then name could potentially
     * be changed from the outside. So the structure could be changed
     * unintentionally (vulnerable to side effects) */
    person->name = strdup(name);
    person->age = age;
    return person;
}

struct Person * create_person_nocopy(char * name, int age){
    struct Person * person = malloc(sizeof(struct Person));
    assert(person != NULL);
    person->name = name;
    person->age = age;
    return person;
}


void free_person(struct Person * person){
    assert(person != NULL);
    free(person->name);
    free(person);
}

void free_person_nocopy(struct Person * person){
    assert(person != NULL);
    free(person);
}

void print_person(struct Person * person){
    assert(person != NULL);
    printf("name: %s\n", person->name);
    printf("age: %d\n", person->age);
}

int main(int argc, char * argv[]){
    struct Person * p1 = create_person("Bob the builder", 48);
    print_person(p1);

    // To test the assert statements
    // print_person(NULL);

    // If you do not free person, valgrind will find two memory leaks.
    free_person(p1);

    // Now changing the name2 outside the structure has the side effect of
    // changing name in the structure
    char name2[] = "Hank the hunk";
    struct Person * p2 = create_person_nocopy(name2, 28);
    print_person(p2);

    strncpy(name2, "Just Hank", strlen(name2)-1);
    print_person(p2);

    free_person_nocopy(p2);

    return 0;
}
