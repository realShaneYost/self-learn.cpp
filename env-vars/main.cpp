#include <iostream>
#include <cstdlib>
#include <string>

int main()
{
    // std::stoi

    auto value = std::getenv("KITTY_PID");
    if (value)
    {
        try
        {
            std::cout << std::stoi(value) << std::endl;
        }
        catch (const std::invalid_argument&)
        {
            std::cerr << "not a valid number" << std::endl;
        }
        catch (const std::out_of_range&)
        {
            std::cerr << "out of integer range" << std::endl;
        }
    }
    else
    {
        std::cout << "out of integer range error" << std::endl;
    }
}
