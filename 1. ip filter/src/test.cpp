#include <iostream>
#include <fstream>

int main()
{
    // Data must be generated in results.txt (by the main program) before start
    // via  "data | main.exe > result.txt" command
    // Test is successful if there is no difference in files
    std::ifstream results{"results.txt", std::ios_base::in};
    std::ifstream output{"output.txt", std::ios_base::in};

    if (results.fail())
        throw std::runtime_error("There is no results.txt data file.");
    if (output.fail())
        throw std::runtime_error("There is no output.txt data file.");

    int line_n = 1;
    while(!results.eof() && !output.eof())
    {
        std::string line1;
        std::string line2;

        results >> line1;
        output >> line2;

        if (line1 != line2)
        {
            std::cout << "Difference in the [" << line_n++ << "] line\n";
            std::cout << "results:\t[" << line1 << "]\n";
            std::cout << "output:\t[" << line2 << ']' << std::endl;
        }
    }

    return 0;
}