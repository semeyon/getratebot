#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <limits.h>
#include <algorithm>


template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::string trim(const std::string& str,
                 const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str,
                   const std::string& fill = " ",
                   const std::string& whitespace = " \t")
{
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

std::string join(const std::vector<std::string>& vec, const char* delim)
{
    std::stringstream res;
    copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(res, delim));
    return res.str();
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}


//int index = FuzzyBitapSearch("The quick brown fox jumps over the lazy dog", "fox");
static int FuzzyBitapSearch(std::string text, std::string pattern, unsigned int k) {
    unsigned int result = -1;
    unsigned int m = pattern.size();
    unsigned long *R;
    unsigned long patternMask[CHAR_MAX + 1];
    unsigned int i, d;

    if (pattern[0] == '\0') return 0;
    if (m > 31) return -1; //Error: The pattern is too long!

    R = new unsigned long[(k + 1) * sizeof *R];
    for (i = 0; i <= k; ++i)
        R[i] = ~1;

    for (i = 0; i <= CHAR_MAX; ++i)
        patternMask[i] = ~0;

    for (unsigned int i = 0; i < m; ++i)
        patternMask[(unsigned char)pattern[i]] &= ~(1UL << i);

    for (i = 0; text[i] != '\0'; ++i)
    {
        unsigned long oldRd1 = R[0];

        R[0] |= patternMask[(unsigned char)text[i]];
        R[0] <<= 1;

        for (d = 1; d <= k; ++d)
        {
            unsigned long tmp = R[d];

            R[d] = (oldRd1 & (R[d] | patternMask[(unsigned char)text[i]])) << 1;
            oldRd1 = tmp;
        }

        if (0 == (R[k] & (1UL << m)))
        {
            result = (i - m) + 1;
            break;
        }
    }

    free(R);
    return result;
}

void StrToLower(std::string &msg) {
    transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
}