/*
  Name: hashTable.h
  Author: Aida Nordman
  Course: TND004, Lab 2
  Description: test program for class HashTable
*/

#include <iostream>
#include <fstream>
#include <string>

#include "hashTable.h"

using namespace std;

//A simple hash function
unsigned my_hash(string s, int tableSize)
{
    unsigned hashVal = 0;

    for(unsigned i = 0; i < s.length(); i++)
        hashVal += s[i];

    hashVal %= tableSize;
    return hashVal;
}

unsigned int my_hash2( const string & key, int tableSize )
{
    unsigned int hashVal = 0;

    for( char ch : key )
    hashVal = 37 * hashVal + ch;

    return hashVal % tableSize;

}


//Test the code
int menu()
{
    int choice = 0;

    cout << "\n-------------------------" << endl;
    cout << "Operations on Hash Table" << endl;
    cout << "\n-------------------------" << endl;

    cout << "1. Insert " << endl;
    cout << "2. Search" << endl;
    cout << "3. Delete" << endl;
    cout << "4. Dump table" << endl;
    cout << "5. Read in from file" << endl;
    cout << "6. Exit" << endl;

    cout << "Enter your choice: ";

    cin >> choice;

    return choice;
}


int main()
{
    fstream myfile;
    string word;

    const int TABLE_SIZE = 7;

    HashTable table(TABLE_SIZE, my_hash);

    string key;
    int value = 0;

    int choice;
    bool go = true;

    while( go )
    {
        choice = menu();

        switch(choice)
        {
        case 1:

            cout << "Enter value to be inserted: ";
            cin >> value;

            cout << "Enter key for the value to be inserted: ";
            cin >> key;

            table.insert(key, value);
            break;

        case 2:

            cout << "Enter key of the value to be searched: ";
            cin >> key;

            value = table.find(key);

            if (value == NOT_FOUND)
            {
                cout << "No element found at key " << key << endl;
            }
            else
            {
                cout << "value at key " << key << ": ";
                cout << value << endl;
            }
            break;

        case 3:
            cout << "Enter key of the value to be deleted: ";
            cin >> key;

            table.remove(key);
            break;

        case 4:
            table.display(cout);
            break;

        case 5:
//            myfile.open("test_files/test_file1.txt");
//
//
//            while (myfile >> word)
//            {
//                table[word];
//            }
            break;
        case 6:
            go = false;
            break;

        default:
            cout << "\nEnter correct option\n";
        }
    }

    return 0;
}
