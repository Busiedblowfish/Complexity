#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>


#define S_C " `~!@#$%^&*()-_+={}[]\\|:;\"\'<>,.?/"
#define MAX_SCORE 5
#define MIN_SCORE 1

/* Function prototype */
int pwdLength(const std::string&);              //Return the length of the password
bool dictionaryCheck(const std::string&);       //Return 1 for true or 0 for false if the password is in the dictionary[dictionary.txt]
int atleast1Letter (const std::string&);        //Return the number of letter[small] in the password
int atleast1CL(const std::string&);             //Return the number of capital letter in the password
int atleast1Num(const std::string&);            //Return the number of numbers in the password
int atleast1SC(const std::string&);             //Return the number of special characters in the password
bool rockyouCheck(const std::string&);          //Return 1 for true or 0 for false if the password is in the rockyou8.txt


/*
    There are different ways to solve this problem, but due to the scope of this program,
    I will use a very straight forward approach.
    The password will be rated [1 - 5]; 1 for weak, 5 for strong.
    Below are the  minimum requirements I believe should be met by a password in
    order to be considered strong:

                CRITERIA                              STRENGTH
    ------------------------------------------------------------
    1. At least 8 characters; the longer the better.    [1]
    2. Not a dictionary word                            [1]
    3. At least 1 letter [a-z]                          [1]
    4. At least 1 capital letter [A-Z]                  [1]
    5. At least 1 number [0-9]                          [1]
    6. Not in rockyou.txt                               [1]
    7. At least 1 special character                     [1]

    A combination of all this criteria will yield the maximum strength of 5
*/


int main()
{
    int i;
    std::string result;
    std::string input;
    int score = 0;

    std::cout << "\tThis program rates the complexity of a password [1 - 5]; 1 for weak, 5 for strong.\n";
    std::cout << "\tEnter a password or \"q\" to quit\n";
    //std::cin.ignore();
    while(1)
    {
        std::cout << "\nEnter a password: ";
        std::getline(std::cin, input);

        if (input == "q")
        {
            break;
            exit(EXIT_SUCCESS);
        }
        else if(input[0] == '\0')
            continue;
        //std::cout << "\nUser input: " << input;  //Verify the input
/*
                CRITERIA                              STRENGTH
    ------------------------------------------------------------
    1. At least 8 characters; the longer the better.    [1]
    2. Not a dictionary word                            [1]
    3. At least 1 letter [a-z]                          [1]
    4. At least 1 capital letter [A-Z]                  [1]
    5. At least 1 number [0-9]                          [1]
    6. Not in rockyou.txt                               [1]
    7. At least 1 special character                     [1]

    A combination of all this criteria will yield the maximum strength of 5

*/
        else if (pwdLength(input) < 8 || (dictionaryCheck(input) == 1) || (atleast1CL(input) >= 1) || (atleast1Letter(input) >= 1))
            score = MIN_SCORE;
        else if (pwdLength(input) >= 8 && dictionaryCheck(input) == 0 && atleast1CL(input) >= 1 || atleast1Letter(input) >= 1)
            score = MIN_SCORE + 1;
        else if (pwdLength(input) >= 8 && dictionaryCheck(input) == 0 && (atleast1CL(input) >= 1 || atleast1Letter(input) >= 1 && atleast1Num(input) >= 1))
            score = MIN_SCORE + 2;
        else if (pwdLength(input) >= 8 && dictionaryCheck(input) == 0 && (atleast1CL(input) >= 1 && atleast1Letter(input) >= 1 && atleast1Num(input) >= 1))
            score = MIN_SCORE + 3;
        else if (pwdLength(input) >= 8 && dictionaryCheck(input) == 0 && (atleast1CL(input) >= 1 && atleast1Letter(input) >= 1 && atleast1Num(input) >= 1) && rockyouCheck(input) == 0 && atleast1SC(input))
            score = MAX_SCORE;
        else
            score = 3;
        std::cout << "Password strength: " << score;
/*
        std::cout << "\nThere are " << pwdLength(input) <<" characters";
        std::cout << "\nIs the password in the dictionary? " << dictionaryCheck(input) << "\n";
        std::cout << "\nNumber of letters: " << atleast1Letter(input) << "\n";
        std::cout << "\nNumber of \'numbers\': " << atleast1Num(input) << "\n";
        std::cout << "\nNumber of special characters: " << atleast1SC(input) << "\n";
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
bool dictionaryCheck(const std::string &pwd)
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
                std::cout <<"\nThis is the word: " << word;
                //std::cout << "\nFound inside the loop: " << found;
                break;
            }
            else
                found = false;
        }
        file.close();
    }
    else
        std::cout << "\n Error opening file, try again";
    //std::cout << "\nFound outside the loop: " << found;

    return found;
}


/* Check for at least 1 letter [a-z] */
int atleast1Letter (const std::string &pwd)
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
    //std::cout << "\nLetter found? " << found;
    return j;
}


/* check for at least 1 capital letter [A-Z] */
int atleast1CL (const std::string &pwd)
{
    bool clFound;
    bool found;
    int length = pwdLength(pwd.c_str());
    int j = 0;  //count the number of capital letters
    for(int i = 0;  i < length;  i++)
    {
        if(pwd.c_str()[i] >= 'A' && pwd.c_str()[i] <= 'Z')
        {
            clFound = true;
            found = clFound;
            j = j + 1;
        }
        else
            clFound = false;
    }
    //std::cout << "\nNumber of capital letters found: " << j;
    //std::cout << "\nCapital letter found? " << found;
    return j;
}

/* check for at least 1 special character [] */
int atleast1Num (const std::string &pwd)
{
    bool numFound;
    bool found;
    int length = pwdLength(pwd.c_str());
    int j = 0;  //count the number of capital letters
    for(int i = 0;  i < length;  i++)
    {
        if((pwd.c_str()[i] - '0')  >= 0 && (pwd.c_str()[i] - '0' <= 9))
        {
            numFound = true;
            found = numFound;
            j = j + 1;
        }
        else
            numFound = false;
    }
    //std::cout << "\nNumber of numbers found: " << j;
    std::cout << "\nNumber found? " << found;
    return j;
}

int atleast1SC (const std::string &pwd)
{
    bool scFound;
    bool found;
    int length = pwdLength(pwd.c_str());
    int j = 0;  //count the numbers of special character
    int macroSC_len = sizeof(S_C)/sizeof(S_C[0]);
    for(int i = 0;  i < length;  i++)
    {
        for( int k = 0; k < macroSC_len; k++)
        {
            if(pwd.c_str()[i] == S_C[k])
            {
                scFound = true;   //Found at least one special character
                found = scFound;
                j = j + 1;      //count how many special characters in the password
                //std::cout << "\nSpecial character found in the loop? " << scFound;
            }
            else
                scFound = false;
        }
    }
    //std::cout << "\nNumber of special characters found: " << j;     //how many special characters?
    //std::cout << "\nSpecial character found loop? " << found;
    return j;
}

/* Check rockyou.txt that contains at least 8 characters */

bool rockyouCheck(const std::string &pwd)
{
    /* rockyou.txt from KALI linux */
    std::string word;
    std::ifstream file("rockyou8.txt");
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
                break;
            }
            else
                found = false;
        }
        file.close();
    }
    else
        std::cout << "\n Error opening file, try again";
    //std::cout << "\nFound outside the loop: " << found;

    return found;
}
