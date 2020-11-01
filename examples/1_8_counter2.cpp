#include <iostream>

using namespace std;

int count_x(const char* p, char x)
{
    if (p==nullptr) return 0;

    int count = 0;
    while(*p) {
        if (*p==x)
            ++count;   
        ++p;
    }

    return count;
}


int main()
{
    int result = count_x("how many n-s are in here?", 'n');
    cout << result << "\n";
}