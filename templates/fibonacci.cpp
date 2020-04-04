#include <iostream>

template<unsigned long N>
struct fibonacci
{
    // This value is static since it is computed at compile time and remains
    // unchanged for the lifetime of the program.
    // Removing the static raises a compile-time error.
    static const unsigned long value = fibonacci<N-1>::value + fibonacci<N-2>::value;
};

// The template with no parameters indicates a "template specialization"
template<>
struct fibonacci<1> // <===== SPECIALIZATION
{
    static const unsigned long value = 1;
};

template<>
struct fibonacci<2> // <===== SPECIALIZATION
{
    static const unsigned long value = 1;
};

int main(int argc, char * argv[]){
    // Here is a expensive (and very overflowy) computation of the 902nd fibonacci number
    // It is computed at compile-time, leaving runtime constant
    //
    // If you set the number too high, there will be a template depth error (900 on my system)
    std::cout << fibonacci<902>::value << std::endl;
    return 0;
}
