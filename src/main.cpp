#include <iostream>

static bool running = true;

int main()
{
    while (running)
    {
        std::cout << "Hello World";
    }

    return 0;
}