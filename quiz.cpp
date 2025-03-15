#include <iostream>

int main()
{
    int x{-1};
    long runs{0};
    while (x)
    {
        x--;
        runs++;
    }
    std::cout << runs << std::endl;
}