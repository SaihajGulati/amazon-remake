#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include <map>
#include <vector>
#include <iostream>

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 */


class MyDataStore : public DataStore{
public:
    MyDataStore();
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    /**
     * add the hit at index to cart container
     * returns a bool that tells whether could be added to car successfully
     */
    bool addToCart(std::string username, long unsigned int index);

    /**
     * displays cart
     * returns bool that tells whether could be done correctly depending on whether username was valid
     */
    bool displayCart(std::string username);

    /**
     * "buys cart" 
     * return bool that tells whether could be done correctly based on whether username was valid
     */
    bool buyCart(std::string username);

private:

    //make maps for storing keyword:set of products pointers and username:user pointer

    std::map<std::string, std::set<Product*>> keywordProducts_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::vector<Product*>> carts_;
    std::vector<Product*> lastSearchHits_;
    
};

#endif
