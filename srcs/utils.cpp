
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include <cstring>
#include <list>

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
        out.push_back(trim(str.substr(start, end - start)));
    }
    return out;
}



std::list<std::string> tokenize_list(std::string const &str, const char delim)
{
    size_t start;
    size_t end = 0;
    std::list<std::string> out;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(trim(str.substr(start, end - start)));
    }
    return out;
}


std::string         implodeMessage(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end)
{
    std::vector<std::string> 	vec_msg(begin,end);
    return (vecToString(vec_msg));
}

std::string         toLower(std::string str)
{
    std::string res;
    for (size_t x=0; x<str.length(); x++)
        res.push_back(tolower(str[x]));
    return res;
}

bool            pattern_match (std::string str, std::string pattern)
{
    size_t n = str.size();
    size_t m = pattern.size();

    if (m == 0)
        return n == 0;

    bool T[n + 1][m + 1];

    std::memset(&T, false, sizeof(T));

    T[0][0] = true;

    for (size_t j = 1; j <= m; ++j)
    {
        if (pattern[j - 1] == '*')
            T[0][j] = T[0][j - 1];
    }
    for (size_t i = 1; i <= n; ++i)
    {
        for (size_t j = 1; j <= m; ++j)
        {
            if (pattern[j - 1] == str[i - 1] || pattern[j - 1] == '?')
                T[i][j] = T[i - 1][j - 1];
            else if (pattern[j - 1] == '*')
                T[i][j] = T[i][j - 1] || T[i - 1][j];
            else
                T[i][j] = false;
        }
    }
    return T[n][m];
}