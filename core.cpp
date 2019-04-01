#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using std::cin, std::cout, std::cerr, std::runtime_error, std::overflow_error, std::underflow_error, std::endl, std::vector, std::string;

int plus(int x, int y)
{
    int z = x + y;
    if (x > 0 && y > 0 && z <= 0)
        throw overflow_error("plus overflow");
    if (x < 0 && y < 0 && z >= 0)
        throw underflow_error("plus underflow");
    return z;
}
int minus(int x, int y)
{
    int z = x - y;
    if (x > 0 && y < 0 && z <= 0)
        throw overflow_error("minus overflow");
    if (x < 0 && y > 0 && z >= 0)
        throw underflow_error("minus underflow");
    return z;
}
int multiply(int x, int y)
{
    int z = x * y;
    if ((x > 0 && y > 0 && z < 0) || (x < 0 && y < 0 && z < 0))
        throw overflow_error("multiply overflow");
    if ((x > 0 && y < 0 && z > 0) || (x < 0 && y > 0 && z > 0))
        throw underflow_error("multiply underflow");
    return z;
}
int divide(int x, int y)
{
    if (!y)
        throw runtime_error("divide 0");
    return x / y;
}
class ele
{
  public:
    bool type;
    union {
        int a = 0;
        char c;
    } s;
    int judge()
    {
        int res = 0;
        if (type)
            switch (s.c)
            {
            case '+':
                res = 1;
                break;
            case '-':
                res = 1;
                break;
            case '*':
                res = 2;
                break;
            case '/':
                res = 2;
                break;
            case '(':
                res = 3;
                break;
            case ')':
                res = -1;
                break;
            default:
                throw runtime_error("unknown element");
            }
        return res;
    }
    ele(string &p)
    {
        int i = 0;
        if (p[i] <= '9' && p[i] >= '0')
            for (type = 0; p[i] <= '9' && p[i] >= '0'; s.a = s.a * 10 + p[i++] - '0')
                ;
        else
        {
            type = 1;
            s.c = p[i++];
        }
        p = p.substr(i);
    }
    int gnum()
    {
        return s.a;
    }
    char gchar()
    {
        return s.c;
    }
};

int calc(string &s)
{
    int ret = 0;
    vector<ele> data;
    //stack<int> num;
    while (!s.empty())
    {
        ele p(s);
        if (p.judge() == -1)
            break;
        if (!p.judge())
            data.push_back(p);
        else
        {
            ele r(s);
            if (r.judge() == 3)
            {
                r.type = 0;
                r.s.a = calc(s);
            }

            switch (p.gchar())
            {
            case '*':
                (data.end() - 1)->s.a = multiply(r.s.a, (data.end() - 1)->s.a);
                break;
            case '/':
                (data.end() - 1)->s.a = divide((data.end() - 1)->s.a, r.s.a);
                break;
            case '+':
            case '-':
                data.push_back(p);
                data.push_back(r);
                break;
            }
        }
    }
    while (data.size() > 1)
    {
        switch (data[1].s.c)
        {
        case '+':
            data[0].s.a = plus(data[0].s.a, data[2].s.a);
            break;
        case '-':
            data[0].s.a = minus(data[0].s.a, data[2].s.a);
            break;
        default:
            cout << "error in +-" << endl;
        }
        data.erase(data.begin() + 1);
        data.erase(data.begin() + 1);
    }
    return data[0].gnum();
}

int main()
{
    string s;
    int i;
    cin >> s;
    try
    {
        cout << calc(s) << endl;
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}