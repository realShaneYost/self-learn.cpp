/**
 * std::atoi
 * 
 * Advantages:
 * - Simple to use for quick integer conversions.
 * - No exceptions or errno to manage.
 * 
 * Disadvantages:
 * - Returns 0 on failure, which is ambiguous (e.g., "0" vs "foo").
 * - Provides no way to detect parse errors or overflow.
 * - Not recommended for robust or production-level code.
 * 
 *
 * std::strtol
 * 
 * Advantages:
 * - Detects parsing errors using `endptr` and `errno`.
 * - Supports various numeric bases (e.g., decimal, hex, octal).
 * - Doesn't throw exceptions — suitable for embedded/low-level use.
 * - Allows partial parsing (e.g., stopping at first non-numeric character).
 * 
 * Disadvantages:
 * - Verbose: requires more boilerplate (e.g., managing `errno`, `endptr`).
 * - Uses C-style strings and pointers (not idiomatic in modern C++).
 * - Must manually check for leftover characters and range errors.
 * 
 * 
 * std::stoi (C++11 and newer)
 *
 * Advantages:
 * - Works directly with std::string.
 * - Throws clear exceptions (`std::invalid_argument`, `std::out_of_range`).
 * - Cleaner syntax than strtol for many use cases.
 * - Overloads available for long, float, double, etc. (`std::stol`, `std::stod`, etc.).
 * 
 * Disadvantages:
 * - Uses exceptions, which may be undesirable in performance-critical code.
 * - Does not auto-detect base (e.g., "0x10" not treated as hex by default).
 * - Slightly slower than strtol due to exception handling overhead.
 */


#include <iostream>
#include <cstdlib>
#include <string>

int main()
{
    auto value = std::getenv("KITTY_PID");

    /**
     * stoi
     */
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

    /**
     * atoi
     */
    if (value)
    {
        int value_to_integer = std::atoi(value);
        std::cout << value_to_integer << std::endl;
    }
    else
    {
        std::cout << "error in getting KITTY_PID" << std::endl;
    }

    /**
     * strtol
     */
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
