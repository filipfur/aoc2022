#include <iostream>

enum class Shape
{
    Rock, Paper, Scissor
};

int shapeScore(const Shape& shape)
{
    switch(shape)
    {
        case Shape::Rock:
            return 1;
        case Shape::Paper:
            return 2;
        case Shape::Scissor:
            return 3;
        default:
            std::cerr << "enum value dont exist." << std::endl;
            return 0;
    }
    return 0;
}

bool winsAgainst(const Shape& a, const Shape& b)
{
    switch(a)
    {
        case Shape::Rock:
            return b == Shape::Scissor;
        case Shape::Paper:
            return b == Shape::Rock;
        case Shape::Scissor:
            return b == Shape::Paper;
        default:
            std::cerr << "enum value dont exist." << std::endl;
            return false;
    }
    return false;
}

Shape actionToShape(const Shape& other, int action)
{
    switch(other)
    {
        // LOSE DRAW WIN
        case Shape::Rock:
            return action == 0 ? Shape::Scissor : (action == 1 ? Shape::Rock : Shape::Paper);
        break;
        case Shape::Paper:
            return action == 0 ? Shape::Rock : (action == 1 ? Shape::Paper : Shape::Scissor);
        break;
        case Shape::Scissor:
            return action == 0 ? Shape::Paper : (action == 1 ? Shape::Scissor : Shape::Rock);
        break;
    }
}

int computeScore(char a, char x)
{
    auto shapeA = static_cast<Shape>(a - 'A');
    auto shapeX = actionToShape(shapeA, static_cast<int>(x - 'X')); 
    int score = shapeScore(shapeX);
    if(shapeA == shapeX)
    {
        score += 3;
    }
    else if(winsAgainst(shapeX, shapeA))
    {
        score += 6;
    }
    return score;
}

int main(int argc, const char* argv[])
{
    char a;
    char x;
    int totalScore = 0;
    while(std::cin >> a)
    {
        std::cin >> x;
        int matchScore = computeScore(a, x);
        std::cout << matchScore << std::endl;
        totalScore += matchScore;
    }
    std::cout << totalScore << std::endl;
    return 0;
}