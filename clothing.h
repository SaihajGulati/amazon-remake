#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product
{
    public:
        
        /**
         * constructor, includes all parameters from product constructer except for category since that's implied by name
         * also adds size and brand fields specific to book
         */
        Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand);
        
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

    ~Clothing();
    
    private:
        //data members specific to clothing
        std::string size_;
        std::string brand_;
    
};

#endif