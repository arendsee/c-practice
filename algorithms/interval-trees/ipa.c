#include <stdlib.h>

#include "ipa.h"
#include "interval.h"

IPA * init_ipa(){
    IPA * ipa = (IPA *)malloc(sizeof(IPA));
    ipa->size = 0;
    ipa->v = NULL;
    return(ipa);
}

IPA * init_set_ipa(size_t size){
    IPA * ipa = (IPA *)malloc(sizeof(IPA));
    ipa->size = size;
    if(size > 0){
        ipa->v = (Interval *)malloc(size * sizeof(Interval));
    } else {
        ipa->v = NULL;
    }
    return(ipa);
}

void free_ipa(IPA * ipa){
    if(ipa->v)
        free(ipa->v);
    if(ipa)
        free(ipa);
}
