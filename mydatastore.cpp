#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    std::map<std::string, User*>::iterator it;
    //delete memory taken up by user objects
    for (it = users_.begin(); it != users_.end(); ++it)
    {
        delete it->second;
    }
    //delete memory taken up by product objects
    std::vector<Product*>::iterator it2;
    for (it2 = products_.begin(); it2 != products_.end(); ++it2)
    {
        delete *it2;
    }
}

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p)
{
    //get keywords for product
    set<string>  words = p->keywords();
    set<string>::iterator it;

    //for each keyword, add a pointer to a product to the set in the mapping
    for (it = words.begin(); it != words.end(); ++it)
    {
        keywordProducts_[*it].insert(p);
    }

    products_.push_back(p);
}


/**
 * Adds a user to the data store
 * adds a user pointer to the map, associated with it's name as the key
 */
void MyDataStore::addUser(User* u)
{
    users_[convToLower(u->getName())] = u;
}


/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    //temporary set to store products that match search criteria
    set<Product*> temp;
    vector<string>::iterator it;

    if (type == 1)
    {
        //for each term, get the set of products and find its union with the current running set
        
        for (it = terms.begin(); it != terms.end(); ++it)
        {
            temp = setUnion(temp, keywordProducts_[*it]);
        }

    }
    else if (type == 0)
    {
        //for each term, get the set of products and find its intersection with the current set
        for (it = terms.begin(); it != terms.end(); ++it)
        {
            //have to handle case that is the first term, in which case need to do union, as intersection would do nothing as need to add to set even though temp is empty 
            if (it == terms.begin())
            {
                temp = setUnion(temp, keywordProducts_[*it]);
            }
            else
            {
                temp = setIntersection(temp, keywordProducts_[*it]);
            }
        }
    }

    //assign to vector of master set of products that match search criteria
    lastSearchHits_.assign(temp.begin(), temp.end());
    std::sort(lastSearchHits_.begin(), lastSearchHits_.end(), ProdNameSort());
    return lastSearchHits_;
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile)
{
    
    /**
     * first dump products part
     */
    ofile << "<products>" << endl;

    //set to hold all products and iterator for map
    set<Product*> allProducts;
    map<string, set<Product*>>::iterator it;

    //for each keyword in keywordproducts, construct master set of products using union so that duplicates are avoided
    for (it = keywordProducts_.begin(); it != keywordProducts_.end(); ++it)
    {
        allProducts = setUnion(allProducts, (*it).second);
    }

    //
    set<Product*>::iterator ite;

    //iterate through allProducts and dump each product's information
    for (ite = allProducts.begin(); ite != allProducts.end(); ++ite)
    {
        (*ite)->dump(ofile);
    }

    ofile << "</products>" << endl;

    /**
     * now time to dump users part
     */
    ofile << "<users>" << endl;

    map<string, User*>::iterator iter;

    //iterate through users which are mapped with name as key and pointer as value, and dump each users information
    for (iter = users_.begin(); iter != users_.end(); ++iter)
    {
        (*iter).second->dump(ofile);
    }

    ofile << "</users>" << endl;

}

/**
 * add the hit at index to cart container
 * index user gives starts at 1 and vector starts at zero so have to subtract by 1
 */
bool MyDataStore::addToCart(string username, long unsigned int index)
{
    username = convToLower(username);
    // as long as user is found and the index is greater than 0 and less than or equal to size, add to cart of user
    if (users_.find(username) != users_.end() && (index > 0 && index <= lastSearchHits_.size()))
    {
        carts_[username].push_back(lastSearchHits_[index-1]);
        return true;
    }
    return false;
}

/**
     * displays cart
     * returns bool that tells whether could be done correctly depending on whether username was valid
     */
bool MyDataStore::displayCart(std::string username)
{
    username = convToLower(username);
    if (users_.find(username) != users_.end())
    {
        vector<Product*> cart = carts_[username];
        int cartIndex = 1;
        for(vector<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) {
            cout << "Item "  << cartIndex << endl;
            cout << (*it)->displayString() << endl;
            cout << endl;
            cartIndex++;
        }
        return true;
    }

    return false;

}

/**
 * "buys cart" 
 * return bool that tells whether could be done correctly based on whether username was valid
 */
bool MyDataStore::buyCart(std::string username)
{
    username = convToLower(username);
    if (users_.find(username) != users_.end())
    {
        //make aliases to parts stored in maps so can use easier but also change the originals
        //alias for cart of specific user, need alias bc otherwise will copy vector
        vector<Product*>& cart = carts_[username];
        //user pointer
        User* user = users_[username];

        // go through cart and handle each cart item
        vector<Product*>::iterator it = cart.begin();
        while (it != cart.end())
        {
            //product pointer in cart
            Product* item = (*it);

            //check if have stock and user has enough money
            if (item->getQty() > 0 && user->getBalance() >= item->getPrice())
            {
                //if so then one less of item left, user pays price money, and the product is removed from cart
                item->subtractQty(1);
                user->deductAmount(item->getPrice());
                it = cart.erase(it);

            }
            else //if product not in stock or user doesn't have enough money, move on
            {
                ++it;
            }

        }
        return true;
    }
    return false;

}

