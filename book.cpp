#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>
using namespace std;

/**
* constructor, includes all parameters from product constructer except for category since that's implied by name
* also adds isbn and author fields specific to book
*/
Book::Book(const std::string name, double price, int qty, const std::string isbn, const std::string author) :
    Product("book", name, price, qty),
    isbn_(isbn),
    author_(author)
{
}

Book::~Book(){}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Book::keywords() const
{
    //create set with the keywords from the name of the product
    set<std::string> nameWords(parseStringToWords(name_));

    //create set with keywords from author
    set<std::string> authorWords(parseStringToWords(author_));

    //create set with words from both of above
    set<std::string> words(setUnion(nameWords, authorWords));

    //insert rest of keywords that we take as is
    words.insert(isbn_);

    return words;    
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book::displayString() const
{
    std::stringstream ss;
    ss << name_ + "\n";
    ss << "Author: " + author_ + " ISBN: " + isbn_ + "\n";
    ss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return ss.str();
}

/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream& os) const
{
    //dump the product version first and then add category specific
    Product::dump(os);
    os << isbn_ << "\n" << author_ << endl;
}