#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"

class Movie : public Product
{
    public:
        
        /**
         * constructor, includes all parameters from product constructer except for category since that's implied by name
         * also adds genre and rating fields specific to book
         */
        Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating);
       
        /**
         * Returns the appropriate keywords that this product should be associated with
         */
        std::set<std::string> keywords() const;
        
        /**
         * Returns a string to display the product info for hits of the search
         */
        std::string displayString() const;

        /**
         * Outputs the product info in the database format
         */
        void dump(std::ostream& os) const;

    ~Movie();

    private:
        //data members specific to movie
        std::string genre_;
        std::string rating_;
    
};

#endif