#include <iostream>
#include <compare>
#include <iomanip>
#include <vector>

#include <fmt/core.h>
#include <fmt/color.h>

#include <string.h>

using namespace std;

// declarations
char *trim(char *str);

string& trim2(string& s);
vector<string> split(string s, string delimiter);



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


    // TEST: string manipulation in C and C++
    // Always easy in JS, C# and PHP.
    // We need the equivalent of split() and trim()
    // String: ADCX — Unsigned Integer Addition of Two Operands with Carry Flag
    // var txt = "ADCX %E2%80%94 Unsigned Integer Addition of Two Operands with Carry Flag"
    // var mnemonic = decodeURIComponent( txt.split('%E2%80%94')[0] ).trim();
    // var summary  = decodeURIComponent( txt.split('%E2%80%94')[1] ).trim();

    // In C:
    char *token;
    char line[] = "ADCX %E2%80%94 Unsigned Integer Addition of Two Operands with Carry Flag";
    char search[] = "%E2%80%94";

    // NOTE: strtok() will modify the string
    token = strtok(line, search);
    char *mnemonic = token;
    token = strtok(NULL, search);
    char *summary = token;

    printf("%s\n", mnemonic);
    printf("%s\n", summary);

    // Roll your own trim()
    // See: https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
    printf("%s\n", trim(mnemonic));
    printf("%s\n", trim(summary));
    ///////////////////////////////////


    // In C++
    string line2 = "ADCX %E2%80%94 Unsigned Integer Addition of Two Operands with Carry Flag";
    string search2 = "%E2%80%94";

    // Roll your own split() Really?
    // See: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    // Let's not use boost, regex, templates, lambdas or ranges
    string mnemonic2 = split(line2, search2)[0];
    string summary2  = split(line2, search2)[1];

    cout << mnemonic2 << "\n";
    cout << summary2 << "\n";

    // And trim() roll your own. C++ sucks.
    // See: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
    cout << trim2(mnemonic2) << "\n";
    cout << trim2(summary2) << "\n";
    ///////////////////////////////////



    std::cout << std::flush;
    int dummy = 0;

    return 0;
}


// NOTE: isspace() needs (unsigned char) but who cares?
char *trim(char *str)
{
    char *p = str, *q = str;
    while (isspace(*p)) p++;
    while (*q) q++;
    while (q > str && isspace(*--q)) *q = 0;
    return p;
}

string& trim2(string& s)
{
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    s.erase(0, s.find_first_not_of(" \n\r\t"));                                                                                               
    return s;
}


vector<string> split(string s, string delimiter)
{
    size_t pos = 0;
    std::string token;
    vector<string> res;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        //std::cout << token << std::endl;
        res.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    // And the rest:
    //std::cout << s << std::endl;
    res.push_back(s);

    return res;
}