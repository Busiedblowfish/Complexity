#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>

int complexity (const std::string&);
bool dictionaryWord(const std::string&);

int main()
{
    int i;
    std::string result;
    std::string input;

    std::cout << "\tThis program rates the complexity of a password [1 - 5]; 1 for weak, 5 for strong.\n";
    std::cout << "\tEnter a password or \"q\" to quit\n";
    //std::cin.ignore();
    while(1)
    {
        std::cout << "\nEnter a password: ";
        std::getline(std::cin, input);

        if (input == "q")
            break;
        std::cout << "User input: " << input;

        if(dictionaryWord(input) == 1)
            result = "Yes";
        else
            result = "No";

        std::cout << "\nThere are " << complexity(input) <<" characters\n";
        std::cout << "Is the password in the dictionary? " << result <<"\n";
    }

    return 0;
}


/*
    There are different ways to solve this problem, but due to the scope of this program,
    I will use a very straight forward approach.
    The password will be rated [1 - 5]; 1 for weak, 5 for strong.
    Below are the password requirements I believe should be met by a password in
    order to be considered strong:

    1. At least 8 characters; the longer the better.
    2. Not a dictionary word
    3. Atleast 1 letter [a-z]
    4. Atleast 1 capital letter [A-Z]
    5. Atleast 1 number [0-9]
    6. Atleast 1 special character
*/


/*Accept a string input and return a complexity rating*/
int complexity (const std::string &pwd)
{
    int howMany;
    howMany = strlen(pwd.c_str());
    return howMany;
}


/* Check if the password is in the dictionary */
bool dictionaryWord(const std::string &pwd)
{
    std::string word;
    std::ifstream file("dictionary.txt");
    bool found = false;

    if(file.is_open())
    {
        while(getline(file, word))
        {
            if(word == pwd.c_str())    //The password is in the list
            {
                found = true;
                std::cout <<"\nThis is the word: " << word;
                std::cout << "\nFound inside the loop: " << found;
                break;
            }
            else
                found = false;
        }
        file.close();
    }
    else
        std::cout << "\n Error opening file, try again";
    std::cout << "\nFound outside the loop: " << found;

    return found;
}

