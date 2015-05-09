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

bool test_special_char(char c);

//A simple hash function
unsigned my_hash(string s, int tableSize)
{
    unsigned hashVal = 0;

    for(unsigned i = 0; i < s.length(); i++)
        hashVal += s[i];

    hashVal %= tableSize;
    return hashVal;
}

unsigned int my_hash2( string key, int tableSize )
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
    HashTable freq_table(TABLE_SIZE, my_hash2);

    string key;
    int value = 0;

    int choice;
    bool go = true;

    while( go )
    {
        choice = menu();
        int count =0;
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
           myfile.open("test_files/test_file2.txt");
           cout << "heelo " << endl;
           
           while (myfile >> word)
           {
                transform(word.begin(), word.end(), word.begin(),::tolower);
                string temp = "";
                copy_if(word.begin(),word.end(), back_inserter(temp), test_special_char);

               freq_table[temp];
               count++;
           }
           cout << "Number of words in the file = "<< count <<  endl;
           freq_table.display_freq_table(cout);
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
bool test_special_char(char c){
    if( c == ',' || c == '"' || c == '.' || c == '?' || c =='!' || 
        c == ';' || c == '\'' || c == ':')
        return false;
    else 
        return true;
}

