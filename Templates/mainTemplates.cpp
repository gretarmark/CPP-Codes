#include <iostream>

using namespace std;

// https://www.youtube.com/watch?v=-Svq5IYPWbc

template<typename T>
class Calculator
{

public: // public means we can use these functions outside of the class
    T add(T a, T b)
    {
        return a+b;
    }

    T subtract(T a, T b)
    {
        return a-b;
    }

    T multiply(T a, T b)
    {
        return a*b;
    }

    T divide(T a, T b)
    {
        if(b==0)
        {
            cout << "Error: Division by zero!" << endl;
            return 0;
        }
        return a/b;
    }

};

int main()
{
    Calculator<int> intCalculator;

    cout << intCalculator.add(5,8) << endl;
    cout << intCalculator.subtract(5,8) << endl;

    Calculator<float> floatCalculator;

    cout << floatCalculator.add(5.2,7.84) << endl;
    cout << floatCalculator.subtract(5.2,7.84) << endl;
    cout << floatCalculator.multiply(5.2,7.84) << endl;
    cout << floatCalculator.divide(5.2,7.84) << endl;
    cout << floatCalculator.divide(5.2,0) << endl;


    return 0;
}
