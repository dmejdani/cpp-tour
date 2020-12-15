#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>


std::vector<uint32_t> read_file(std::string path)
{

    std::ifstream infile(path);
    std::vector<uint32_t> vinput;
    uint32_t i;
    while (infile >> i)
        vinput.push_back(i);
    
    return vinput;

}
 
// Return product of elements from (v choose K) sets, if their sum is 2020
uint32_t comb(std::vector<uint32_t> v, int K)
{
    auto N = v.size();

    // The first lexicographically-ordered permutation; 11100000... if K is 3
    std::string permutation(K, 1); // K leading 1's
    permutation.resize(N, 0); // N-K trailing 0's
 
    // print integers and permute bitmask
    do {
        uint32_t sum = 0;
        uint32_t prod = 1;
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (permutation[i]){
                sum += v[i];
                prod *= v[i];
            }
        }

        if (sum == 2020)
            return prod;

    } while (std::prev_permutation(permutation.begin(), permutation.end()));
    return 0;
}


int main()
{
    auto vinput = read_file("../aoc/1/input");

    // There are 'N choose 2' combinations
    std::cout << "From N choose 2 " << comb(vinput, 2) << std::endl;
    std::cout << "From N choose 3 " << comb(vinput, 3) << std::endl;
}