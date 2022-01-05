#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>


using namespace std;


class CountFrom
{
public:
    CountFrom(int count) : count_(count) {}

    int operator()() { return count_++; }

private:
    int count_;
};


// Closure
// See: https://en.wikipedia.org/wiki/Closure_(computer_programming)
// NOTE: capture turns lambda into closure
string foo(string myname) {
    int y = 3;
    vector<string> n {{"Jan"}, {"Ab"}, {"Piet"}};
    // ...
    auto i = std::find_if(n.begin(), n.end(),
               // this is the lambda expression:
               [&](const string& s) { return s != myname && s.size() > y; }
             );
    // 'i' is now either 'n.end()' or points to the first string in 'n'
    // which is not equal to 'myname' and whose length is greater than 'y'
    return *i;
}

///////
void f1(int (*)(int)) {}
void f2(char (*)(int)) {}
void h(int (*)(int)) {}  // #1
void h(char (*)(int)) {} // #2


/////////
class CHello
{
public:
    int func()
    {
        std::vector<int> some_list{ 1, 2, 3, 4, 5 };
        int total = 0;
        int value = 5;
        std::for_each(begin(some_list), end(some_list), 
                    [&total, value, this](int x) { total += x * value * this->some_func(); });

        return total;
    }

    int some_func()
    {
        return 3;
    }
};




int main()
{
    const int state(10);
    std::generate_n(std::ostream_iterator<int>(std::cout, "\n"), 5, CountFrom(state));

    // lambda
    std::generate_n(std::ostream_iterator<int>(std::cout, "\n"), 5, [count = 10]() mutable { 
        return count++;
    });

    ///////////
    cout << foo("Jan");

    ///////////
    cout << endl;

    // See: https://en.cppreference.com/w/cpp/language/lambda
    // Party time []<>(){}
    // generic lambda, operator() is a template with two parameters
    auto glambda = []<class T>(T a, auto&& b) { return a < b; };
 
    // generic lambda, operator() is a template with one parameter pack
    auto glambda2 = []<typename ...Ts>(Ts&& ...ts) {
        return baz(std::forward<Ts>(ts)...);
    };

    
    ////////////
    auto glambda3 = [](auto a) { return a; };
    f1(glambda3); // ok
    //f2(glambda3); // error: not convertible
    h(glambda3); // ok: calls #1 since #2 is not convertible
    
    // NOTE: -> is trailing-return-type (optional)
    int& (*fpi)(int*) = [](auto* a)->auto& { return *a; }; // ok


    ///////////////
    // For every parameter in params whose type is specified as auto, an invented
    // template parameter is added to template-params, in order of appearance. 
    // The invented template parameter may be a parameter pack if the corresponding 
    // function member of params is a function parameter pack.

    // generic lambda, operator() is a template with two parameters
    auto glambda4 = [](auto a, auto&& b) { return a < b; };
    bool b = glambda4(3, 3.14); // ok
    
    // generic lambda, operator() is a template with one parameter
    auto vglambda = [](auto printer) {
        return [=](auto&&... ts) // generic lambda, ts is a parameter pack
        { 
            printer(std::forward<decltype(ts)>(ts)...);
            return [=] { printer(ts...); }; // nullary lambda (takes no parameters)
        };
    };
    auto p = vglambda([](auto v1, auto v2, auto v3) { std::cout << v1 << v2 << v3; });
    auto q = p(1, 'a', 3.14); // outputs 1a3.14
    q();                      // outputs 1a3.14

    
    cout << endl;


    ///////////////
    std::cout << "Emulate `recursive lambda` calls:\nFibonacci numbers: ";
    auto nth_fibonacci = [](int n) {
        std::function<int(int,int,int)> fib = [&](int a, int b, int n) {
            return n ? fib(a + b, a, n - 1) : b;
        };
        return fib(1, 0, n);
    };
    for (int i{1}; i != 9; ++i) { std::cout << nth_fibonacci(i) << ", "; }
 
    std::cout << "\nAlternative approach to lambda recursion:\nFibonacci numbers: ";
    auto nth_fibonacci2 = [](int n) {
        auto fib = [](auto self, int a, int b, int n) -> int {
            return n ? self(self, a + b, a, n - 1) : b;
        };
        return fib(fib, 1, 0, n);
    };
    for (int i{1}; i != 9; ++i) { std::cout << nth_fibonacci2(i) << ", "; }
 
    // C++23 approach to lambda recursion
    // auto nth_fibonacci3 = [](this auto self, int a, int b, int n) {
    //     return n ? self(a + b, a, n - 1) : b;
    // };


    cout << endl;

    ///////////////
    std::cout << "Printable ASCII [32..126]:\n";
    for (char i = ' '; i <= '~'; ++i) {
        std::cout << i << ((i % 16 == 15) ? '\n' : ' ');
    }

    cout << endl;

    //////////////////
    // closure
    // See: https://en.wikipedia.org/wiki/Anonymous_function#C++_(since_C++11)
    std::vector<int> some_list{ 1, 2, 3, 4, 5 };
    int total = 0;
    std::for_each(begin(some_list), end(some_list), 
                [&total](int x) { total += x; });
    // Note that std::accumulate would be a way better alternative here...
    cout << total << endl;

    CHello hello;
    cout << hello.func() << endl;

    
    return 0;
}