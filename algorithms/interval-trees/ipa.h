#ifndef __IPA_H__
#define __IPA_H__

/** Interval pointer array */
typedef struct {
    size_t size;
    Interval ** v;
} IPA;
void free_ipa();
IPA * init_ipa();


IPA * init_ipa(){
void free_ipa(IPA * ipa){

#endif
