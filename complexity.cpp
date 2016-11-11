/* This program will score a user supplied password based on how complex it is */

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>

//SC is the list of all special characters on the keyboard
#define SC " `~!@#$%^&*()-_+={}[]\\|:;\"\'<>,.?/"
#define MAX_SCORE 5
#define MIN_SCORE 1

/* Function prototype */
int pwdLength(const std::string&);               //Return the length of the password
bool inDictionary(const std::string&);           //Return 1 for true or 0 for false if the password is in the dictionary[dictionary.txt]
bool atleast1Letter (const std::string&);        //Return the number of letter[small] in the password
bool atleast1CL(const std::string&);             //Return the number of capital letter in the password
bool atleast1Num(const std::string&);            //Return the number of numbers in the password
bool atleast1SC(const std::string&);             //Return the number of special characters in the password



/*
            CRITERIA                                                                 STRENGTH
    -----------------------------------------------------------------------------------------
    1. At most 8 characters  or dictionary word                                         [1]
    2. 9-10 characters and non-dictionary word with any combinations of characters      [2]
    3. 11-12 characters, non-dictionary word and all combinations of characters         [3]
    4. 13-14 characters, non-dictionary word and all combinations of characters         [4]
    5. 15 or more characters, non-dictionary word and all combinations of characters    [5]

        combinations of characters:
        . At least 1 letter [a-z]
        . At least 1 capital letter [A-Z]
        . At least 1 number [0-9]
        . At least 1 special character

*/

int main()
{
    std::string result;
    std::string input;
    int score = 0;

    std::cout << "\tThis program rates the complexity of a password [1 - 5]; 1 for very weak, 5 for very strong.\n";
    std::cout << "\tEnter a password or \"q\" to quit\n";
    //std::cin.ignore();
    while(1)
    {
        std::cout << "\nEnter a password: ";
        std::getline(std::cin, input);

        if (input == "q")
        {
            break;
            exit(0);
        }
        else if(input[0] == '\0') //Do nothing when user presses "Enter"
            continue;
        // True = 1, False = 0
        else if (pwdLength(input) < 9 || (inDictionary(input) == 1 ))
            score = MIN_SCORE;
        else if (pwdLength(input) >= 9 && pwdLength(input) < 11 && inDictionary(input) == 0 && (atleast1CL(input) == 1 || atleast1Letter(input) == 1 || atleast1Num(input) == 1 || atleast1SC(input) == 1))
            score = MIN_SCORE + 1;
        else if (pwdLength(input) >= 11 && pwdLength(input) < 13 && inDictionary(input) == 0 && (atleast1CL(input) == 1 && atleast1Letter(input) == 1 && atleast1Num(input) == 1 && atleast1SC(input) == 1))
            score = MIN_SCORE + 2;
        else if (pwdLength(input) >= 13 && pwdLength(input) < 15 && inDictionary(input) == 0 && (atleast1CL(input) == 1 && atleast1Letter(input) == 1 && atleast1Num(input) == 1 && atleast1SC(input) == 1))
            score = MIN_SCORE + 3;
        else if (pwdLength(input) >= 15 && inDictionary(input) == 0 && (atleast1CL(input) == 1 && atleast1Letter(input) == 1 && atleast1Num(input) == 1 && atleast1SC(input) == 1))
            score = MIN_SCORE + 4;
        else
            score = MIN_SCORE + 1;  //case where the password is very long but doesn't have complete components of a Password

        //std::cout << "\nUser input: " << input;  //Verify the input

        std::cout << "Password strength: " <<  score << "\n";
/*
        std::cout << "\nThere are " << pwdLength(input) <<" characters";
        std::cout << "\nIs the password in the dictionary? " << inDictionary(input) << "\n";
        std::cout << "\nAt least 1 small letter: " << atleast1Letter(input) << "\n";
        std::cout << "\nAt least 1 capital letter: " << atleast1CL(input) << "\n";
        std::cout << "\nAt least 1 number: " << atleast1Num(input) << "\n";
        std::cout << "\nAt least 1 special character: " << atleast1SC(input) << "\n";
*/
    }
    return 0;
}

/*Accept a string input and return a complexity rating*/
int pwdLength (const std::string &pwd)
{
    int howMany;
    howMany = strlen(pwd.c_str());
    return howMany;
}


/* Check if the password is in the dictionary */
bool inDictionary(const std::string &pwd)
{
    /* dictionary.txt from 'https://github.com/dwyl/english-words/blob/master/words3.txt' */
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
                //std::cout <<"\nThis is the word: " << word;
                //std::cout << "\nFound inside the loop: " << found;
                //break;
            }
        }
        file.close();
    }
    else
        std::cout << "\n Error opening file, try again\n";
    //std::cout << "\nFound outside the loop: " << found;

    return found;
}


/* Check for at least 1 letter [a-z] */
bool atleast1Letter (const std::string &pwd)
{
    bool letterFound;
    bool found;
    int length = pwdLength(pwd.c_str());
    int j = 0;  //count the number of letters
    for(int i = 0;  i < length;  i++)
    {
        if(pwd.c_str()[i] >= 'a' && pwd.c_str()[i] <= 'z')
        {
            letterFound = true;
            found = letterFound;
            j = j + 1;
        }
        else
            letterFound = false;
    }
    //std::cout << "\nNumber of letters found: " << j;
    return j;
}


/* check for at least 1 capital letter [A-Z] */
bool atleast1CL (const std::string &pwd)
{
    bool clFound =  false;
    int length = pwdLength(pwd.c_str());
    int j = 0;  //count the number of capital letters
    for(int i = 0;  i < length;  i++)
    {
        if(pwd.c_str()[i] >= 'A' && pwd.c_str()[i] <= 'Z')
        {
            clFound = true;
            j = j + 1;
        }
    }
    //std::cout << "\nNumber of capital letters found: " << j;
    return clFound;
}

/* check for at least 1 special character [] */
bool atleast1Num (const std::string &pwd)
{
    bool numFound;
    int length = pwdLength(pwd.c_str());
    int j = 0;  //count the number of capital letters
    for(int i = 0;  i < length;  i++)
    {
        if((pwd.c_str()[i] - '0')  >= 0 && (pwd.c_str()[i] - '0' <= 9))
        {
            numFound = true;
            j = j + 1;
        }
    }
    //std::cout << "\nNumber of numbers found: " << j;
    return numFound;
}

bool atleast1SC (const std::string &pwd)
{
    bool scFound = false;
    int length = pwdLength(pwd.c_str());
    int j = 0;  //count the numbers of special character
    int macroSC_len = sizeof(SC)/sizeof(SC[0]);
    for(int i = 0;  i < length;  i++)
    {
        for( int k = 0; k < macroSC_len; k++)
        {
            if(pwd.c_str()[i] == SC[k])
            {
                scFound = true;   //Found at least one special character
                j = j + 1;      //count how many special characters in the password
            }
        }
    }
    //std::cout << "\nNumber of special characters found: " << j;     //how many special characters?
    //std::cout << "\nSpecial character found loop? " << scFound;
    return scFound;
}
