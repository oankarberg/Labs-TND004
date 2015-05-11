#include <assert.h>
#include <iomanip>

#include "hashTable.h"

const double MAX_LOAD_FACTOR = 0.5;

//Test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


//Return a prime number at least as large as n
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}


// Constructor
// IMPLEMENT
HashTable::HashTable(int table_size, HASH f)
    : size(nextPrime(table_size)), h(f), nItems(0)
{
    hTable = new Item*[size];
    for(int i = 0; i < size; i++){
        hTable[i] = nullptr;
    }

}


//destructor
// IMPLEMENT
HashTable::~HashTable()
{
    delete hTable;
}


//Return the load factor of the table
double HashTable::loadFactor() const
{
    return (double) nItems / size;
}


//Return the value associated with key
//If key does not exist in the table then NOT_FOUND is returned
// IMPLEMENT
int HashTable::find(string key) const
{
    int hVal = h(key,size);
    for(int i = 0; i < size; i++){
        int hNum = (hVal + i) % size;
        if(hTable[hNum] != nullptr){
            if(hTable[hNum]->key == key && hTable[hNum]->key != ""){
                return hTable[hNum]->value;
            }
        }
    }
    return NOT_FOUND; //to be deleted
}



//Insert the Item (key, v) in the table
//If key already exists in the table then change the associated value to v
//Re-hash if the table becomes 50% full
// IMPLEMENT
void HashTable::insert(string key, int v)
{


    //Check if the key exist in table and change the value to it
    int hVal = h(key,size);
    int tempV = find(key);

    for(int i = 0; i < size; i++){
        int hNum = (hVal+ i) % size;
        //If slot not empty, look if the key exist
        if(hTable[hNum] != nullptr){
            if(hTable[hNum]->key == key || hTable[hNum]->key == ""){
                hTable[hNum] = new Item(key, v);
                return;
            }
        //We know it not exist and therefore add it in first empty slot
        }else if(tempV == NOT_FOUND && 
                (hTable[hNum] == nullptr)){
            hTable[hNum] = new Item(key, v);
            break;
        }

    }

    nItems++;

    if(loadFactor() > MAX_LOAD_FACTOR){
        reHash();
    }



}


//Remove Item with key
//If an Item with key belongs to the table then return true,
//otherwise, return false
// IMPLEMENT
bool HashTable::remove(string key)
{
    //Get the hashvalue of key
    int hValue = h(key,size);
    for(int i = 0; i < size; i++){
        //increase hashvalue if the we dont find the right key
        int hVal = (hValue + i) % size;
        if(hTable[hVal] != nullptr){
            if(hTable[hVal]->key == key){
                delete hTable[hVal];
                hTable[hVal] = new Item("",-1);
                nItems--;
                return true;
            }
        }
    }

    return false; //to be deleted
}


void HashTable::display(ostream& os)
{
    if (!hTable) return;

    os << "-------------------------------\n";

    for (int i = 0; i < size; ++i)
    {
        os << setw(6) << i << ": ";

        if (!hTable[i])
        {
            os << "null" << endl;
        }
        else
        {
            string key = hTable[i]->key;

            os << "key = " << "\"" << key << "\""
               << setw(12) << "value = " << hTable[i]->value
               << "  (" << h(key,size) << ")" << endl;
        }
    }

    os << endl;
}

void HashTable::display_freq_table(ostream& os)
{
    if (!hTable) return;

    
    os << "Number unique  words in the file = " << uniqueWords << endl;
    os << "Frequency table ... " << endl << endl;
           
    for (int i = 0; i < size; ++i)
    {

        if (hTable[i])
        {
            string key = hTable[i]->key;

            os << "key = " <<  left << setw(20) << key 
                << "value = " << hTable[i]->value <<
                endl;
        }
    }

    os << endl;
}


//Display the table to stream os
// IMPLEMENT
ostream& operator<<(ostream& os, const HashTable& T)
{
    return os;
}


HashTable& HashTable::operator[](const string &key){
    int tempNum = find(key);
    
    //Check if the word exists and insert, incr unique
    if(tempNum  == NOT_FOUND ){
        insert(key, 1);
        uniqueWords++;
    }
    else //Insert and increment value
    {
        insert(key, tempNum+1);
    }
   return *this;
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash()
{
    
    int tempSize = size;
    size = nextPrime(tempSize*2);

    cout << "Rehashing.." << endl;
    cout << "New Size: " << size << endl;

    Item** hTemp = hTable;
    hTable = new Item*[size];
    nItems = 0;
    for(int i = 0; i < size; i++){
        hTable[i] = nullptr;
    }
    //Copy the table over;
    for(int i = 0; i < tempSize; i++){

        if(hTemp[i] != nullptr)
        {
            insert(hTemp[i]->key,hTemp[i]->value);
        }
    }


}



