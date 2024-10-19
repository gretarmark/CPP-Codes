#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

class Test {
    private:
            static const int SIZE = 100;

            int *_pBuffer;

    public:
            Test() {
                cout << "constructor" << endl;
                _pBuffer = new int[SIZE] { };
            }

            Test(int i) {
                cout << "parameterized constructor" << endl;
                _pBuffer = new int[SIZE] { };

                for(int i=0; i<SIZE; i++) {
                    _pBuffer[i] = 7 * i;
                }
            }

            Test(const Test &other) {
                cout << "copy constructor" << endl;
                _pBuffer = new int[SIZE] { };
                memcpy(_pBuffer, other._pBuffer, SIZE * sizeof(int));
            }

            Test &operator=(const Test &other) {
                cout << "assignment" << endl;
                _pBuffer = new int[SIZE] { };
                memcpy(_pBuffer, other._pBuffer, SIZE * sizeof(int));
                return *this;
            }

            ~Test() {
                cout << "destructor" << endl;
                delete[] _pBuffer;
            }

            friend ostream &operator<<(ostream &out, const Test &test);
};

ostream &operator<<(ostream &out, const Test &test) {
    out << "Hello from test";
    return out;
}

Test getTest() {
    return Test();
}

int main()
{

    Test test1 = getTest();
    cout << test1 << endl;

    vector<Test> vec;
    vec.push_back(Test());

    int value1 = 7; //value1 is an lvalue and 7 is an rvalue. value1 is on the left, 7 is on the right of = (or of this statement)
    //C++ 11 changed the importance of lvalue and rvalue
    //in C++ 11, an lvalue is anything you can take the address of
    
    int *pValue1 = &value1; //This shows us that value1 is an lvalue because we can take the address of it.
    //int *pValue2 = &7 //This shows us that 7 is an rvalue because we cannot take the address of it (7 is a primitive value).

    //The same thing applies with objects. test1 is an lvalue since we can take the address of it.
    Test *pTest1 = &test1;  //This is going to work. On the right side of Test test1 = getTest() above, we have the rvalue getTest().
                            //This is because return values of functions are rvalues and they are often temporary values
    //Test *pTest2 = &getTest(); // So, this is something we cannot do. The reason for that is the return value is an rvalue (a temporary value in this case).
                                 // Sometimes the distinction between lvalues and rvalues is hard to find.

    int *pValue3 = &value1; //This works. What also works is:
    int *pValue4 = &++value1; //This also works. This gives us: the prefix increment operator increments the value and then uses it. 7 will become 8.
    cout << pValue4 << endl;

    //On the otherhand, if we try the same thing using postfix increment operator it will not work.
    //int *pValue5 = &value1++;   //The reason this doesn't work is because there is a temporary value in there. Because the postfix operator 
                                //needs to use the value, and afterwards increment it. So it has to create a temporary copy of the value
                                //so that the actual original value can be used, and then we can increment basically a different value.
                                //There got to be 2 values in there somewhere. Here C++ thinks we are taking the address of a temporary value.
                                //So this is an rvalue and &++value1 above is an lvalue.
    //cout << pValue5 << endl;

    //There are lots of other examples that exist.

    int s = 7 + value1; //value1 is itself an lvalue, but the whole thing 7+value1 is an rvalue.
    //int *s = &(7+value1); // You cannot set brackets around 7+value1 and take the address of it.

    //This takes very long time to wrap your head around this. It's good to try this a bit and find some examples.
    //Remember that one of the most important rvalues we find is in the return of a functions.
    //It's good to have this in your head before moving to lvalue and rvalue references and then move constructors.
    //Constructors are really great but sometimes they do require us to think a bit more deeply then we might be accustomed to thinking. 


    return 0;
}
