#include "clothing.h"
#include "util.h"
#include <iomanip>
#include <sstream>

using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand) :
    Product("clothing", name, price, qty),
    size_(size),
    brand_(brand)
{
}

Clothing::~Clothing(){}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Clothing::keywords() const
{
    //create set with the keywords from the name of the product
    set<std::string> nameWords(parseStringToWords(name_));

    //create set with keywords from brand
    set<std::string> brandWords(parseStringToWords(brand_));

    //create set with words from both of above
    set<std::string> words(setUnion(nameWords, brandWords));

    return words;   

}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Clothing::displayString() const
{
    std::stringstream ss;
    ss << name_ << "\n";
    ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    ss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return ss.str();
}

/**
 * Outputs the product info in the database format
 */
void Clothing::dump(std::ostream& os) const
{
    //dump the product version first and then add category specific
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}