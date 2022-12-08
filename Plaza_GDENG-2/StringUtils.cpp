#include "StringUtils.h"

std::vector<std::string> StringUtils::split(const std::string& s, char delim)
{
    std::stringstream stream(s);
    std::string item;
    std::vector<std::string> elem;

    while (std::getline(stream, item, delim))
    {
        elem.push_back(item);
    }

    return elem;
}
