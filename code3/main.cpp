/**********************************************
* File: main.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2015                             *
* Description: frequency table                *
* DO NOT MODIFY                               *
***********************************************/

#include "threaded_BST.h"
#include "BiIterator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


/**********************************************
* File: main.cpp                              *
* Author: Daniel Holst                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2015                             *
* Description: frequency table                *
* DO NOT MODIFY                               *
***********************************************/

#include "threaded_BST.h"
#include "BiIterator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

string Unvalid_chars = "(-.,!?/\");:'";

/*******************************
* 2. Main function             *
********************************/

bool isNotAlnum(char c)
{
    for(int i = 0; i < Unvalid_chars.size(); i++)
    {

        if(c == Unvalid_chars[i])
            return true;
    }
    return false;
}

void displayTable(MAP& table)
{
    cout << "Frequency table sorted alphabetically..." << endl << endl
        << setw(15) << "KEY" << setw(10) << "" << "COUNTER" << endl
        << "=================================" << endl;

    BiIterator it = table.begin();

    while(it != table.end())
    {
        cout << setw(15) << right << it->first
             << setw(15) << it->second << endl;

        it++;

    }
}

int main()
{
    MAP table;

    string name, s;
    int count = 0;

    /******************************************************
    * PHASE 0: Load the words in the text file            *
    *          into a the table                           *
    *******************************************************/

    cout << "File name? ";
    getline(cin, name);

    ifstream textFile(name);

    if (!textFile)
    {
        cerr << "Text file could not be opened!!" << endl;
        exit(1);
    }

    cout << "Loading the words from " << name << " ...\n";

    //Read words and load them in the table
    while (textFile >> s)
    {
        //remove non-alphanumeric chars
        s.erase(remove_if(s.begin(), s.end(), isNotAlnum), s.end());

        //convert to lower-case letters
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        if (!s.size()) continue; //skip numbers and punctuation signs
        table[s].second++;  //if s is not in the table then it is inserted

        count++;

    }


    /******************************************************
    * PHASE 1: Display                                    *
    * - number of words in the text                       *
    * - number of unique words (occurring only once)      *
    * - frequency table                                   *
    *******************************************************/

    cout << "Number of words in file: " << count << endl;
    cout << "Number of unique words in file: " << table.size() << endl << endl;
    cout << "---------------------------------------------- " << endl << endl;


    displayTable(table);


    /******************************************************
    * PHASE 3: remove all words with counter 1            *
    *          and display table again                    *
    *******************************************************/

    string wait;
    getline(cin, wait);

    BiIterator it = table.begin();
    
    for(; it != table.end(); it++){
        if(it->second == 1){
            table.remove(it->first);
        }
    }
    it = table.begin();
    for(; it != table.end(); it++){
        if(it->second == 1){
            cout << "FIRST: " << it->first << " SECOND: " << it->second << endl;
        }
    }



    cout << "Number of words in file after remove: " << table.size() << endl << endl;

    displayTable(table);

    // /***********************************************************
    // * PHASE 4: request two words to the user w1 and w2         *
    // *          then display all words in the interval [w1,w2]  *
    // ************************************************************/

    string input1, input2;

    cout << "Enter two words: ";
    cin >> input1 >> input2;

    cout << "Frequency table in [" << input1 << "," << input2 << "]" << endl
              << setw(15) << "KEY" << setw(10) << "" << "COUNTER" << endl
              << "=================================" << endl;

    if(table.find(input1) == table.end() || table.find(input2) == table.end() || input2 < input1)
        cout << "ERROR! Input string(s) does not exist in table or interval is not entered as [min, max]" << endl;

    else
    {

        it = table.find(input2);

        for(; it!= table.begin(); it--)
        {
            cout << setw(15) << right << it->first
                 << setw(15) << it->second << endl;


            if(it->first == input1)
                break;
        }

    }

    return 0;
}
