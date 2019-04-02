#include "core.h"
#include "stdafx.h"
using namespace std;
int main()
{
    string s;
    int i;
    cin >> s;
    try
    {
        cout << calc_core::calc(s) << endl;
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}