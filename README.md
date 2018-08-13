# compare-json-libraries \*
This project is to compare the json libraries available in c++. we are running 1 Million reads on nlohmann json, boost property tree and rapid json.

Rapid json takes minimal time and is fastest among all three.

**To Build**\
clang++ -march=native -mtune=native -msse4.2 -std=c++14 -Ofast -Iinclude -lboost_system InputParserTest.cpp

**To Run**\
./a.out
