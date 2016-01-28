#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

struct Person {
    char * name;
    int age;
};

struct Person create_person(char * name, int age){
    char * name_cpy = strdup(name);
    struct Person person = {name_cpy, age};
    return person;
}


void free_person(struct Person person){
    free(person.name);
}

void print_person(struct Person person){
    printf("name: %s\n", person.name);
    printf("age: %d\n", person.age);
}

int main(int argc, char * argv[]){
    struct Person p1 = create_person("Bob the builder", 48);
    print_person(p1);
    free_person(p1);
    return 0;
}
