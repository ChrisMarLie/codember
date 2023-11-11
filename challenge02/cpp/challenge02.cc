#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <format>

const std::string FILE_NAME = "message_02.txt";

const char INCREMENT = '#';
const char DECREMENT = '@';
const char PRODUCT = '*';
const char PRINT = '&';

auto compile(const std::string &data) -> std::string
{
    std::string result_str;
    int result = 0;
    for(const char& operation : data)
    {
        switch(operation)
        {
            case INCREMENT:
                result++;
                break;
            case DECREMENT:
                result--;
                break;
            case PRODUCT:
                result *= result;
                break;
            case PRINT:
                result_str = std::format("{}{}", std::move(result_str), result);
                break;
        }
    }

    return result_str;
}

auto main() -> int
{
    	
	std::cout << "\033[35m" << std::string(10, '-') << " TESTS " << std::string(10, '-') << "\033[0m" << std::endl;

    assert(compile("##*&") == "4");
	std::cout << "\033[32m#Test1 -- PASSED\033[0m" << std::endl;

    assert(compile("&##&*&@&") == "0243");
	std::cout << "\033[32m#Test2 -- PASSED\033[0m" << std::endl;

	std::cout << "\033[35m" << std::string(10, '-') << " END TESTS " << std::string(10, '-') << "\033[0m\n" << std::endl;

	std::cout << "\033[33mSOLUTION: \033[0m";


	if (std::ifstream file(FILE_NAME); file.is_open()) 
	{
    	std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    	file.close();
		std::cout << compile(data) << std::endl;
	}

    return 0;
}