#include <iostream>
#include <sstream>
#include <map>
#include <vector>

class State
{
public:
    virtual int reward(int timeLeft) = 0;
};

class Valve : public State
{
public:
    Valve(const std::string& name, int rate) : _name{name}, _rate{rate}
    {
        std::cout << "Created Valve: " << name << " " << rate << std::endl;
    }

    std::string name() const
    {
        return _name;
    }

    Valve* traverse(size_t index)
    {
        return _connections.at(index);
    }

    void addConnection(Valve* valve)
    {
        _connections.push_back(valve);
    }

    int rate() const
    {
        return _rate;
    }

    virtual int reward(int timeLeft)
    {
        return _rate * timeLeft;
    }

private:
    const std::string _name;
    const int _rate;
    std::vector<Valve*> _connections;
};

int main(int argc, const char* argv[])
{

    std::string str;

    std::map<std::string, Valve*> valves;
    std::multimap<std::string, std::string> connections;

    Valve* currentValve{nullptr};

    std::string lab;
    while(std::cin >> lab)
    {
        std::cin >> lab;
        std::getline(std::cin, str);
        size_t a = str.find_first_of('=') + 1;
        size_t b = str.find_first_of(';');
        int rate = std::stoi(str.substr(a, b - a));

        valves.emplace(lab, new Valve(lab, rate));

        const std::string label{" valv"};
        const size_t label_n = label.size();
        a = str.find(label) + label_n;
        str = str.substr(a, str.size() - a);
        //std::cout << rate << std::endl;
        std::stringstream ss{str};
        ss >> str;

        while(ss >> str)
        {
            //std::cout << str.substr(0,2) << std::endl;
            int id{0};
            for(int i = 0; i < 2; ++i)
            {
                id += ((i + 1)) * (str.at(i) - 'A' + 1);
            }
            connections.emplace(lab, str.substr(0,2));
        }
    }

    for(auto it = connections.begin(); it != connections.end(); ++it)
    {
        valves[it->first]->addConnection(valves[it->second]);
    }

    currentValve = valves["AA"];

    std::cout << currentValve->traverse(0)->name() << std::endl;

    return 0;
}