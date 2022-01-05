// HELL: this is about trimming empty lines from the start and end of a text,
// NOT about trimming whitespace off the start and end of a line.
// How can I trim empty/whitespace lines?
// See: https://stackoverflow.com/questions/68648591/how-can-i-trim-empty-whitespace-lines
// Three ways: regex, std, indexes. Slow, fast, faster: 21s, 0.04s, 0.003s.
#include <string>
#include <sstream>
#include <chrono>
#include <iostream>
#include <regex>
#include <exception>

struct perf {
    std::chrono::steady_clock::time_point start_;
    perf() : start_(std::chrono::steady_clock::now()) {}
    double elapsed() const {
        auto stop = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = stop - start_;
        return elapsed_seconds.count();
    }
};

std::string Generate(size_t line_len, size_t empty, size_t nonempty) {
    std::string es(line_len, ' ');
    es += '\n';
    for (size_t i = 0; i < empty; ++i) {
        es += es;
    }

    std::string nes(line_len - 1, ' ');
    es += "a\n";
    for (size_t i = 0; i < nonempty; ++i) {
        nes += nes;
    }

    return es + nes + es;
}


int main()
{
    std::string test;
    //test = "  \n\t\n  \n  \tTEST\n\tTEST\n\t\t\n  TEST\t\n   \t\n \n  ";
    std::cout << "Generating...";
    std::cout.flush();
    test = Generate(1000, 8, 10);
    std::cout << " done." << std::endl;

    std::cout << "Test 1...";
    std::cout.flush();
    perf p1;
    std::string out1;
    std::regex re(R"(^\s*\n|\n\s*$)");
    try {
        out1 = std::regex_replace(test, re, "");
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << " done. Elapsed time: " << p1.elapsed() << "s" << std::endl;

    std::cout << "Test 2...";
    std::cout.flush();
    perf p2;
    std::stringstream is(test);
    std::string line;
    while (std::getline(is, line) && line.find_first_not_of(" \t\n\v\f\r") == std::string::npos);
    std::string out2 = line;
    size_t end = out2.size();
    while (std::getline(is, line)) {
        out2 += '\n';
        out2 += line;
        if (line.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
            end = out2.size();
        }
    }
    out2.resize(end);
    std::cout << " done. Elapsed time: " << p2.elapsed() << "s" << std::endl;

    if (out1 == out2) {
        std::cout << "out1 == out2\n";
    }
    else {
        std::cout << "out1 != out2\n";
    }

    std::cout << "Test 3...";
    std::cout.flush();
    perf p3;
    static bool whitespace_table[] = {
        1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    };
    size_t sfl = 0; // Start of first line
    for (size_t i = 0, end = test.size(); i < end; ++i) {
        if (test[i] == '\n') {
            sfl = i + 1;
        }
        else if (whitespace_table[(unsigned char)test[i]]) {
            break;
        }
    }
    size_t ell = test.size(); // End of last line
    for (size_t i = test.size(); i-- > 0;) {
        if (test[i] == '\n') {
            ell = i;
        }
        else if (whitespace_table[(unsigned char)test[i]]) {
            break;
        }
    }
    std::string out3 = test.substr(sfl, ell - sfl);
    std::cout << " done. Elapsed time: " << p3.elapsed() << "s" << std::endl;

    if (out1 == out3) {
        std::cout << "out1 == out3\n";
    }
    else {
        std::cout << "out1 != out3\n";
    }

    return 0;
}