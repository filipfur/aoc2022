#include <iostream>
#include <set>

int main(int argc, const char* argv[])
{
    char c;
    const int N_SEQ{14};
    char buffer[N_SEQ - 1];
    memset(buffer, 0, N_SEQ - 1);
    int N{0};
    while(std::cin >> c)
    {
        if(N > N_SEQ - 2)
        {
            std::set<char> charset;
            charset.emplace(c);
            for(int i{0}; i < N_SEQ - 1; ++i)
            {
                charset.emplace(buffer[i]);
            }
            if(charset.size() == N_SEQ)
            {
                std::cout << "buffer: ";
                for(auto cc : charset)
                {
                    std::cout << cc << ' ';
                }
                break;
            }
        }
        memmove(buffer + 1, buffer, N_SEQ - 2);
        buffer[0] = c;
        ++N;
    }

    std::cout << std::endl << (N + 1) << std::endl;

    return 0;
}