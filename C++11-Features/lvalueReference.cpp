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

    //In C++98 we have references. In C++11 we have lvalue and rvalue references. 
    // lvalue reference is a normal kind of reference.
    Test &rTest1 = test1; //This reference is lvalue reference and is normal and will compile fine.

    //If we try to bind a lvalue reference to an rvalue, we find that we cannot do it.
    //Remember that the return value of a function s rvalue:
    //Test &rTest2 = getTest(); //Here we are combining lvalue (&rTest2) to rvalue (getTest()), this will not work.
    //BUT, we can actually make it work. We can make it "const". Because const value references can in fact bind to rvalue
    const Test &rTest2 = getTest(); //What happens here is we get the lifetime of the rvalue returned from the function, in this case it 
                                    //gets extended. So as long as this reference exists, this object that is returned from getTest()
                                    //will continue to exist. It is extended beyond the lifetime that it would normally have.
                                    //Normally would be a temporary variable, which is a variable that would be destroyed very quickly.
                                    //As soon as it has served its purpose. Here it will hang around until we reach the closed bracked
                                    //next to return 0 in the main function.
    //It has to be like this, because if you look at a copy constructor "Test(const Test &other)", it always 
    //has const lvalue reference parameter to it. 

    //If we have copy constructor, we can do like this:
    Test test2(Test(1)); //Here we are just calling the parameterized version of the constructor. 
                         //The reason is if we call non-parameterized constructor, then this version gives compile error.
                         //It thinks it looks like a function. This works because const value references work, Test(1) is an rvalue
                         //By passing it into the constructor test2, it causes an lvalue.

  

    return 0;
}
