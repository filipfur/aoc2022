#include <iostream>
#include <vector>

int main(int argc, const char* argv[])
{
    int i{0};
    std::string line;
    std::vector<std::vector<char>> data(9);
    int n{0};
    while(std::getline(std::cin, line, '\n'))
    {
        bool done{false};
        n = 0;
        for(int i{0}; i < line.size(); ++i)
        {
            if((i - 1) % 4 == 0)
            {
                char c = line[i];
                if(c >= '1' && c <='9')
                {
                    done = true;
                }
                else if(c >= 'A' && c <= 'Z')
                {
                    data[n].push_back(c);
                    std::cout << c << " to " << n << std::endl;

                }
                ++n;
            }
        }
        if(done)
        {
            break;
        }

        ++i;
    }

    int N = n;

    std::string command;
    while(std::cin >> command)
    {
        assert(command == "move");
        int n, m, k;
        std::cin >> n >> command >> m >> command >> k;
        //std::cout << n << ". " << m << ". " << k << std::endl;
        int from = m - 1;
        int to = k - 1;
        data[to].insert(data[to].begin(), std::make_move_iterator(data[from].begin()), 
                    std::make_move_iterator(data[from].begin() + n));
        data[from].erase(data[from].begin(), data[from].begin() + n);

        /*for(int i{0}; i < n; ++i)
        {
            data[to].insert(data[to].begin(), data[from].begin(), data[from].begin() + 1);
            data[from].erase(data[from].begin(), data[from].begin() + 1);
        }*/
        std::cout << std::endl;
        for(int i{0}; i < N; ++i)
        {
            std::cout << (i + 1) << ": ";
            for(char c : data[i])
            {
                std::cout << c << ' ';
            }
            std::cout << std::endl;
        }
    }

    std::cout << "n: " << n << std::endl;

    for(int i{0}; i < N; ++i)
    {
        /*std::cout << (i + 1) << ": ";
        for(char c : data[i])
        {
            std::cout << c << ' ';
        }
        std::cout << std::endl;*/
        std::cout << *(data[i].begin());
    }
    
    std::cout << std::endl;

    return 0;
}