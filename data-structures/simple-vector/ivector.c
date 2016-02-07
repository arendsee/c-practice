#include <stdlib.h>

#include "ivector.h"

ivector * ivector_init(size_t available){
    ivector * v = (ivector *)malloc(sizeof(ivector)); 
    v->size = 0;
    v->available = available;
    v->data = (Interval *)malloc(available * sizeof(Interval));
    return(v);
}

void ivector_free(ivector * self){
    if(self){
        if(self->data){
            free(self->data);
        }
        free(self);
    }
}

void ivector_add (ivector * self, Interval dat){
    if(self->size == self->available){
        self->data = (Interval *)realloc(self->data, self->size * 2 * sizeof(Interval));
        self->available *= 2;
    }
    self->data[self->size] = dat;
    self->size++;
}

Interval * ivector_get (ivector * self, size_t index){
    if(index < self->size){
        return &self->data[index];
    } else {
        return (Interval*)0;
    }
}
