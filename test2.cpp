#include <iostream>
#include <compare>
#include <iomanip>

#include <fmt/core.h>
#include <fmt/color.h>

using namespace std;

int main()
{
    int x = 2;

    if ((x<=>1) > 0) {
        std::cout << "Test!\n";
    }

    fmt::print("The answer is {}.\n", 42);

    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
             "Hello, {}!\n", "world");
    fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
             fmt::emphasis::underline, "Hello, {}!\n", "мир");
    fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
             "Hello, {}!\n", "世界");


    string str1 = "Hello, ";
    string str2 = "world!\n";

    cout << "cout: " + str1 + str2;
    fmt::print("fmt: {}{}", str1, str2);
    fmt::print("fmt: {}", str1+str2);

    // printf
    printf("%0.10f:%04d:%+g:%s:%p:%c:%%\n",
                1.234, 42, 3.13, "str", (void*)1000, (int)'X');

    // iostreams (What a mess! chevron hell)
    std::cout << std::setprecision(10) << std::fixed << 1.234 << ':'
                << std::resetiosflags(std::ios::floatfield)
                << std::setw(4) << std::setfill('0') << 42 << std::setfill(' ') << ':'
                << std::setiosflags(std::ios::showpos) << 3.13 << std::resetiosflags(std::ios::showpos) << ':'
                << "str" << ':'
                << (void*)1000 << ':'
                << 'X' << ":%\n";

    // fmt
    fmt::print("{:.10f}:{:04}:{:+}:{}:{}:{}:%\n",
                1.234, 42, 3.13, "str", (void*)1000, 'X');


    std::cout << std::flush;
    int dummy = 0;

    return 0;
}