#include <stdlib.h>

#include "ipa.h"

IPA * init_ipa(){
    IPA * ipa = (IPA *)malloc(sizeof(IPA));
    return(ipa);
}

void free_ipa(IPA * ipa){
    for(int i = 0; i < ipa->size; i++){
        free(ipa->v[i]);
    }
    if(ipa->v)
        free(ipa->v);
}
