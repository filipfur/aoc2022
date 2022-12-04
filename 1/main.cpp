#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, const char* argv[])
{
	int c;
	int calories = 0;
	int maxCalories = 0;
	std::vector<int> totalCalories;

	while(std::cin >> c)
	{
		std::cin.ignore();
		calories += c;
		if(std::cin.peek() == '\n')
		{
			/*if(calories > maxCalories)
			{
				maxCalories = calories;
			}*/
			totalCalories.push_back(calories);
			calories = 0;
		}
	}

	std::sort(totalCalories.begin(), totalCalories.end(), std::greater<int>());

	std::cout << "min: " << totalCalories[totalCalories.size() - 1] << std::endl;
	std::cout << "max: " << totalCalories[0] << std::endl;

	std::cout << (totalCalories[0] + totalCalories[1] + totalCalories[2]) << std::endl;
	return 0;
}
