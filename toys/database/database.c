#include <stdio.h>

#define MAX_SIZE 4

struct Datum {
    char * name;
    int number;
}

struct Database {
    struct Datum data[MAX_SIZE];
}

struct Connection {
    FILE * conn;
    struct Database * db;
}

void Database_open(struct * conn){
    for(int i = 0; i < MAX_SIZE; i++){
        struct Datum datum = {.name = "bob", .number = i};
        conn->db[i] = datum;
    }
}

int main(int argc, char * argv[]){

    return 0;
}
