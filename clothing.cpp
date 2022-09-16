#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand) :
    Product("book", name, price, qty),
    size_(size),
    brand_(brand)
{
}

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
    return 
    name_ + "\n" +
    "Size: " + size_ + " Brand: " + brand_ + "\n" +
    std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

/**
 * Outputs the product info in the database format
 */
void Clothing::dump(std::ostream& os) const
{
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}