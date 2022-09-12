#include <fstream>
#include <sstream>

#include <iostream>

class CodeLoader
{
public :
    CodeLoader() = default;

    bool LoadSourceCode(const char* sourceCodePath);

private :
    std::ifstream _fileReader;
    std::stringstream _fileStream;
    std::string _content;
};