#include <iostream>
#include <fstream>

int main()
{
    // Data must be generated in result.txt before start
    // Test is successful if there is no difference in files
    std::ifstream input{"result.txt", std::ios_base::in};
    std::ifstream output{"output.tst", std::ios_base::in};

    int line_n = 1;
    while(!input.eof() && !output.eof())
    {
        std::string line1;
        std::string line2;

        input  >> line1;
        output >> line2;

        if (line1 != line2)
        {
            std::cout << "Difference in the [" << line_n++ << "] line\n";
            std::cout << "input:\t[" << line1 << "]\n";
            std::cout << "output:\t[" << line2 << ']' << std::endl;
        }
    }

    return 0;
}