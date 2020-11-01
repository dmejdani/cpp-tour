#include <iostream>

using namespace std;


int count_x(const char* p, char x)
{
    if (p == nullptr) return 0;

    int count = 0;

    for (; *p != 0; ++p)
    {
        if (*p == x)
            ++count;
    }

    return count;
}


int main()
{
    char* p = "how many a-s are in here?";
    char x = 'a';
    int result;

    result = count_x(&p[0], x);

    cout << result << "\n";
}