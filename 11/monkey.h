#pragma once

#include <vector>
#include <functional>
#include "item.h"

class Monkey
{
public:

    enum class Maths
    {
        ADD,
        MULTIPLY,
        POWER
    };

    Monkey(int id, const std::vector<Item*>& items, Maths maths, int scalar, int divider, int monkeyA, int monkeyB)
        : _id{id}, _items{items}, _maths{maths}, _scalar{scalar}, _divider{divider}, _monkeyA{monkeyA}, _monkeyB{monkeyB}
    {
        std::cout << "created Monkey: " << _id << ", " << static_cast<int>(maths) << ", " << scalar << ", " << divider << std::endl;
    }

    void giveItem(Item * item)
    {
        _items.push_back(item);
    }

    void printItems()
    {
        std::cout << "Monkey " << _id << ':';
        std::for_each(_items.begin(), _items.end(), [](Item* item){
            std::cout << ' ' << item->worryLevel();
        });
        std::cout << std::endl;
    }

    void printInspections()
    {
        std::cout << "Monkey " << _id << " inspected items " << _inspections << " times." << std::endl;
    }

    void operator()(const std::function<void(Item*,int)>& passItem)
    {
        //std::cout << "Monkey " << _id << ":" << std::endl;
        while(!_items.empty())
        {
            auto it = _items.begin();
            ++_inspections;
            Item* item = *it;
            _items.erase(it);
            uint64_t worry = item->worryLevel();
            switch(_maths)
            {
                case Maths::ADD:
                    worry += _scalar;
                    //std::cout << "  Worry level is increased by " << _scalar << " to " << worry << std::endl;
                    break;
                case Maths::MULTIPLY:
                    worry *= _scalar;
                    //std::cout << "  Worry level is multiplied by " << _scalar << " to " << worry << std::endl;
                    break;
                case Maths::POWER:
                    worry *= worry;
                    //std::cout << "  Worry level is raised to " << worry << std::endl;
                    break;
            }
            if(worry < item->worryLevel())
            {
                std::cout << "worry decreased!" << std::endl;
                std::cout << worry << std::endl << item->worryLevel();
                //assert(false);
            }
            while(worry > 9699690)
            {
                worry -= 9699690;
            }
            //worry /= 10000;
            //worry /= 3;
            //std::cout << "  Monkey gets bored with item. Worry level is divided by 3 to " << worry << std::endl;
            bool divble = (worry % _divider == 0);
            //std::cout << "  Current worry level is" << (divble ? " " : " not ") << "divisible by " << _divider << std::endl;
            item->setWorryLevel(worry);
            int nextMonkey = divble ? _monkeyA : _monkeyB;
            //std::cout << "  Item with worry level " << worry << " is thrown to monkey " << nextMonkey << std::endl;
            passItem(item, nextMonkey);
        }
    }

    int inspections() const
    {
        return _inspections;
    }

    int _id;
    std::vector<Item*> _items;
    Maths _maths;
    int _scalar;
    int _divider;
    int _monkeyA;
    int _monkeyB;
    int _inspections{0};
};