#include <iostream>
#include <cstdlib>
#include <string>

int main()
{
    auto value = std::getenv("KITTY_PID");

    // std::stoi
    // - convenient implicit cast happening for me from const char* to std::string&
    // - temporary allocation happening, may want to consider something else in tight loops
    // - convenient exception object for try/catch

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
        std::cout << "error in getting KITTY_PID" << std::endl;
    }

    // std::atoi
    // not very robust, no way to tell between success/failure if return value was 0
    // no error reporting to errno, no exception objects
    // would have to add more processing on 'value' prior to calling atoi but not practical

    if (value)
    {
        int value_to_integer = std::atoi(value);
        std::cout << value_to_integer << std::endl;
    }
    else
    {
        std::cout << "error in getting KITTY_PID" << std::endl;
    }

    // std::strtol
    // - not very idiomatic in C++, uses char* for example
    // - more involved since i need to check errno
    // - flexible handling of bases, it does work w/ C-style and partial strings though

    if (value)
    {
        char* end;
        errno = 0;
        auto value_to_integer = std::strtol(value, &end, 10);

        if (errno == ERANGE)
        {
            std::cerr << "KITTY_PID is out of range" << std::endl;
        }
        else if ((end == value) || (*end != '\0'))
        {
            std::cerr << "KITTY_PID is not a valid integer" << std::endl;
        }
        else
        {
            std::cout << value_to_integer << std::endl;
        }
    }
    else
    {
        std::cout << "error in getting KITTY_PID" << std::endl;
    }
}
