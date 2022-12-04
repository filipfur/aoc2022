#include <iostream>
#include <set>
#include <algorithm>

/*
n=100
nHalf=50
compartmentA=[0,49]
compartmentB=[50,99]
*/

int computePriority(char c)
{
    int prio = static_cast<int>(c);
    if(prio > 90)
    {
        prio += 1 - 'a';
    }
    else
    {
        prio += 27 - 'A';
    }
    return prio;
}

int main(int argc, const char* argv[])
{
    char c;
    int N = 0;
    char rucksack[512];
    int priority = 0;

    std::cout << "a " << computePriority('a') << std::endl;
    std::cout << "z " << computePriority('z') << std::endl;
    std::cout << "A " << computePriority('A') << std::endl;
    std::cout << "Z " << computePriority('Z') << std::endl;

    std::set<char> groupIntersect;
    std::set<char> currentGroup;

    int groupId = 0;

    while(std::cin >> c)
    {
        rucksack[N++] = c;
        currentGroup.emplace(c);
        if(std::cin.peek() == '\n')
        {
            if(groupId % 3 == 0)
            {
                groupIntersect = currentGroup;
            }
            else
            {
                std::set<char> tmp;
                std::set_intersection(groupIntersect.begin(), groupIntersect.end(),
                    currentGroup.begin(), currentGroup.end(),
                    std::inserter(tmp, tmp.begin()));
                groupIntersect = tmp;
            }
            currentGroup.clear();

            if(groupId % 3 == 2)
            {
                for(char c : groupIntersect)
                {
                    priority += computePriority(c);
                }
                groupIntersect.clear();
            }
            
            /*int nHalf = N / 2;
            std::set<char> compartmentA;
            std::set<char> compartmentB;
            for(int i{0}; i < N; ++i)
            {
                if(i < nHalf)
                {
                    compartmentA.emplace(rucksack[i]);
                }
                else
                {
                    compartmentB.emplace(rucksack[i]);
                }
            }
            std::set<char> intersect;
            std::set_intersection(compartmentA.begin(), compartmentA.end(),
                compartmentB.begin(), compartmentB.end(),
                std::inserter(intersect, intersect.begin()));
            for(char c : intersect)
            {
                priority += computePriority(c);
            }*/
            N=0;
            ++groupId;
        }
    }

    std::cout << "total priority: " << priority << std::endl;

    return 0;
}