#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product("book", name, price, qty),
    genre_(genre),
    rating_(rating)
{
}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Movie::keywords() const
{
    //create set with keywords from name
    set<std::string> words(parseStringToWords(name_));

    //insert rest of keywords that we take as is
    words.insert(genre_);

    return words;   

}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Movie::displayString() const
{
    return 
    name_ + "\n" +
    "Genre: " + genre_ + " Rating: " + rating_ + "\n" +
    std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

/**
 * Outputs the product info in the database format
 */
void Movie::dump(std::ostream& os) const
{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}