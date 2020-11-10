// user
// build with something like 
// g++ -o builds/3_2_vector examples/3_2_vector_user.cpp examples/3_2_vector.cpp 

#include "3_2_vector.h"
#include <cmath>
#include <iostream>


double sqrt_sum(Vector& v)
{
    double sum = 0;
    for (int i = 0; i != v.size(); ++i)
        sum += std::sqrt(v[i]);
    return sum;
}


int main()
{
    Vector v(3);
    v[0] = 1;
    v[1] = 4;
    v[2] = 9;
    
    double r = sqrt_sum(v);
    std::cout << r << "\n";
    return 0;
}
