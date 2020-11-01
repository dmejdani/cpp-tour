#include <iostream>

using namespace std;


class Vector {
public:
    Vector(int s):elem{new double[s]}, sz{s}{}  // construct a vector
    double& operator[](int i) {return elem[i];} // element access: subscripting
    int size() {return sz;}
private:
    double* elem;
    int sz;
};


double read_and_sum(int s)
{
    Vector v(s);
    for (int i = 0; i < v.size(); ++i)
    {
        cin >> v[i];
    }

    double sum = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        sum += v[i];
    }
    return sum;
}


int main()
{
    cout << "Number of elements: ";
    int s;
    cin >> s;
    double sum = read_and_sum(s);
    cout << "The sum of all elements is: " << sum << "\n";

    return 0;
}
