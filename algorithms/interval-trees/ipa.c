#include <stdlib.h>

#include "ipa.h"

// REMOVE ME
#include <stdio.h>

IPA * init_ipa(){
    IPA * ipa = (IPA *)malloc(sizeof(IPA));
    return(ipa);
}

void free_ipa(IPA * ipa){
    if(ipa->v)
        free(ipa->v);
    if(ipa)
        free(ipa);
}
