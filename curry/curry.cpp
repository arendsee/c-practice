#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

/*
fmap :: (a -> b) -> [a] -> [b]
fmap f [] = []
fmap f (x:xs) = f x : fmap f xs

inc :: Num a => a -> a
inc x = x + 1
*/


template <class A, class B>
std::vector<B> fmap(std::function<B(A)> f, const std::vector<A> &xs){
    std::vector<B> ys(xs.size());
    std::transform(xs.begin(), xs.end(), ys.begin(), f);
    return ys;
}

template <class A, class B, class C>
A add(B x, C y){
    return x + y;
}

template <class A>
A inc(A x){
    return x + 1;
}

int main(int argc, char * argv[]){
    std::vector<double> xs1{1,2,3};

    // // the static_cast is unfortunately required for template resolution
    // // I'll have to generate this also in the morloc generators
    std::function<double(double)> inc2 = static_cast<double(*)(double)>(&inc);
    std::vector<double> ys1 = fmap(inc2, xs1);
    std::cout << ys1[0] << " " << ys1[1] << std::endl;

    int x = 42;
    std::vector<double> xs2{1,2,3};

    std::function<double(double)> add42 = std::bind(static_cast<double(*)(double,double)>(&add), x, std::placeholders::_1);

    // test that the partially applied function works:
    std::cout << add42(42) << std::endl;

    std::vector<double> ys2 = fmap(add42, xs2);

    std::cout << ys2[0] << " " << ys2[1] << std::endl;

    return 0;
}
