#include <iostream>

int X{1};
int cycle{1};
int strength{0};

static int constexpr DISPLAY_WIDTH{40};

char display[6][40];

void nextCycle()
{
    int cur = (cycle - 1);
    int a = X % DISPLAY_WIDTH;
    int b = cur % DISPLAY_WIDTH;
    display[cur / DISPLAY_WIDTH][cur % DISPLAY_WIDTH] = (a >= b && a < b + 3) ? '#' : '.';
    ++cycle;
    
    if(((cycle - 20) % 40) == 0)
    {
        int increment{X * cycle};
        strength += increment;
        std::cout << increment << std::endl;
    }
}

int main(int argc, const char* argv[])
{

    std::string command;

    while(std::cin >> command)
    {
        int V;
        if(command == "addx")
        {
            nextCycle();
            std::cin >> V;
            X += V;
        }
        nextCycle();
    }

    for(int y{0}; y < 6; ++y)
    {
        for(int x{0}; x < DISPLAY_WIDTH; ++x)
        {
            std::cout << display[y][x];
        }
        std::cout << std::endl;
    }

    //std::cout << "result: " << strength << std::endl;

    return 0;
}