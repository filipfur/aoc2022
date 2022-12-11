#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#include "monkey.h"

void parseArray(std::vector<Item*>& vec, std::string& str)
{
    size_t a = 0;
    size_t b = str.find_first_of(",");
    if(b >= str.length())
    {
        vec.push_back(new Item{static_cast<uint64_t>(std::stol(str))});
        return;
    }
    while(str.length() > 0)
    {
        vec.push_back(new Item{static_cast<uint64_t>(std::stol(str.substr(a, b)))});
        str = str.substr(std::min(b + 2, str.length()));
        size_t b = str.find_first_of(",");
    }
}

int main(int argc, const char* argv[])
{
    std::vector<Monkey*> monkeys;
    std::string str;
    int monkeyId{0};

    while(std::getline(std::cin, str))
    {
        std::vector<Item*> itemList;
        std::getline(std::cin, str); // Starting items: x, y
        auto a = str.find_first_of(":") + 2;
        str = str.substr(a, str.size() - a);
        parseArray(itemList, str);
        std::cout << "{";
        std::for_each(itemList.begin(), itemList.end(), [](Item* item) {
            std::cout << " " << item->worryLevel();
        });
        std::cout << " }" << std::endl;
        std::getline(std::cin, str);
        a = 19;
        str = str.substr(a, str.size() - a);
        std::stringstream ss{str};
        ss >> str;
        ss >> str;
        Monkey::Maths maths{Monkey::Maths::ADD};
        if(str == "*")
        {
            maths = Monkey::Maths::MULTIPLY;
        }
        ss >> str;
        int scalar{2};
        if(str == "old")
        {
            maths = Monkey::Maths::POWER;
        }
        else
        {
            std::cout << "ss" << str << std::endl;
            scalar = std::stoi(str);
        }

        std::getline(std::cin, str);
        int div = std::stoi(str.substr(21));

        int monkeyA, monkeyB;

        std::getline(std::cin, str);
        monkeyA = std::stoi(str.substr(29));

        std::getline(std::cin, str);
        monkeyB = std::stoi(str.substr(30));

        monkeys.push_back(new Monkey(monkeyId++, itemList, maths, scalar, div, monkeyA, monkeyB));
        //Monkey& monkey = *monkeys.front();

        std::getline(std::cin, str);
    }

    //int worry{0};
    for(int i{1}; i <= 10000; ++i)
    {
        for(Monkey* monkey : monkeys)
        {
            (*monkey)([monkeys](Item* item, int toMonkey){
                monkeys[toMonkey]->giveItem(item);
            });
        }
        if(false && i % 5 == 0)
        {
            std::cout << "After round: " << i << std::endl;
            for(Monkey * monkey : monkeys)
            {
                monkey->printItems();
            }
        }
    }


    std::vector<uint64_t> inspections;
    for(Monkey * monkey : monkeys)
    {
        monkey->printInspections();
        inspections.push_back(monkey->inspections());
    }

    std::sort(inspections.begin(), inspections.end(), std::greater<uint64_t>());

    uint64_t monkeybussiness = inspections[0] * inspections[1];

    std::cout << "monkey bussiness: " << monkeybussiness << std::endl;

    return 0;
}