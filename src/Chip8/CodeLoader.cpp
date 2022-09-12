#include "CodeLoader.hpp"

bool CodeLoader::LoadSourceCode(const char* sourceCodePath)
{
    _fileReader = std::ifstream(sourceCodePath);
    if (_fileReader.is_open())
    {
        _fileStream << _fileReader.rdbuf();
        _content = _fileStream.str();
    }
    else
    {
        //Not found in log

    }

}