
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
# include <sstream>
#include <iterator>

const std::string WHITESPACE = " \n\r\t\f\v";
 
std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}


std::string vecToString(std::vector<std::string> input)
{
    std::ostringstream imploded;
    std::copy(input.begin(), input.end(),  std::ostream_iterator<std::string>(imploded, " "));
    std::ostream_iterator<std::string>(imploded, " ");
    return imploded.str();
}

std::vector<std::string> tokenize(std::string const &str, const char delim)
{
    size_t start;
    size_t end = 0;
    std::vector<std::string> out;
 
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
    return out;
}


std::string         implodeMessage(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end)
{
    std::vector<std::string> 	vec_msg(begin,end);
    return (vecToString(vec_msg));
}