#include <iostream>

using namespace std;

bool accept()
{
    cout << "Do you want to proceed (y or n)?\n";
    char answer = 0;
    cin >> answer;

    if (answer == 'y')
        return true;
    return false;
}

bool accept2()
{
    cout << "Do you want to proceed (y or n)?\n";
    char answer = 0;
    cin >> answer;

    switch (answer) 
    {
        case 'y':
            return true;
        case 'n':
            return false;
        default:
            cout << "I'll take that for a no.\n";
            return false;
    }
}


int main()
{
    cout << "accept()\n";
    bool a = accept();
    cout << a << "\n";

    cout << "accept2()\n";
    bool a2 = accept2();
    cout << a2 << "\n";
}