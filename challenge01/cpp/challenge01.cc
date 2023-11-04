#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <ranges>
#include <format>
#include <map>

const std::string FILE_NAME = "message_01.txt";

auto find_patterns(std::string &&data) -> std::string
{
	std::string result;

	//views::to could substitute views::transform, but not fully supported yet
	auto splitted_data = data   | std::views::drop_while(::isspace)	//trim left
								| std::views::reverse | std::views::drop_while(::isspace) | std::views::reverse //trim right
								| std::views::transform(::tolower)  //lower case
								| std::views::split(' ') //split
								| std::views::transform([](auto &&subview) { return std::string(subview.begin(), subview.end());}); //transform subranges into string

	std::vector<std::pair<std::string, size_t>> frequency_vector;
	auto by_string = [](const std::pair<std::string, size_t>& pair){ return std::get<std::string>(pair); };
	for(std::string word: splitted_data)
	{
		if(auto it = std::ranges::find(frequency_vector, word, by_string); it == frequency_vector.end())
		{
			frequency_vector.emplace_back(std::move(word), 1);
		}else
		{
			it->second++;
		}
	}

	for(auto &[word, freq] : frequency_vector)
	{
		result += std::format("{}{}", std::move(word), std::move(freq));
	}
	
	return result;
}

auto main() -> int
{
	std::cout << "\033[35m" << std::string(10, '-') << " TESTS " << std::string(10, '-') << "\033[0m" << std::endl;

    assert(find_patterns("keys house HOUSE house keys") == "keys2house3");
	std::cout << "\033[32m#Test1 -- PASSED\033[0m" << std::endl;

    assert(find_patterns("cup te a cup") == "cup2te1a1");
	std::cout << "\033[32m#Test2 -- PASSED\033[0m" << std::endl;

	assert(find_patterns("houses house housess") == "houses1house1housess1");
	std::cout << "\033[32m#Test3 -- PASSED\033[0m" << std::endl;

	std::cout << "\033[35m" << std::string(10, '-') << " END TESTS " << std::string(10, '-') << "\033[0m\n" << std::endl;

	std::cout << "\033[33mSOLUTION: \033[0m";


	if (std::ifstream file(FILE_NAME); file.is_open()) 
	{
    	std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    	file.close();
		std::cout << find_patterns(std::move(data)) << std::endl;
	}

    return 0;
}
