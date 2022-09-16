#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> words;
    int left = 0;
    for (long unsigned int i = 0; i < rawWords.length(); i++)
    {
        char curr = rawWords[i];

         //if not a letter, check if long enough (2 characters and then decide whether to put in set)
         //regardless of whether long enough, start of next is one character after i
        if (curr < 48 || (curr > 57 && curr < 65) || (curr > 90 && curr <=97) || curr > 122)
        {
            if (i - left > 1)
            {
                string word = convToLower(rawWords.substr(left, i - left));
                words.insert(word);
            }
            left = i + 1;
        }
    }
    if (rawWords.length() - left > 1)
    {
        words.insert(rawWords.substr(left, rawWords.length() - left));
    }
    
    return words;

}


/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
