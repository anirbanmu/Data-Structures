CXX := clang++
CXXFLAGS := -O2 -Wall -Werror -std=c++14

# Link
test: *.o
    $(CXX) $(CXXFLAGS) $(inputs) -o $(output)

test.o: test.cpp
    $(CXX) $(CXXFLAGS) -c $(input) -o $(output)