#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <random>
#include <cstring>
using namespace std;

void printGuess(char *guess, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << guess[i];
    }
    cout << "\n";
}

int in()
{
    char input;
    int end = true;
    while (end)
    {
        cout << "(1) To play the game.\n(2) To add a new word.\n(3) To look at the list of words\n(4) To close the program" << endl;
        cin >> input;
        if (input >= '1' && input <= '4')
        {
            end = false;
        }
        else
        {
            cout << "Invalid input" << endl;
        }
    }

    int temp = int(input) - '1' + 1;
    return temp;
}

int main()
{

    bool cont = true;

    string filename = "words.txt";
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open the file " << filename << std::endl;
        return 1;
    }

    while (cont)
    {
        int input = in();

        if (input == 1)
        {
            int total_words = 0;
            file.clear();
            file.seekg(0);
            string word;
            while (file >> word)
            {
                total_words++;
            }
            random_device rand;
            mt19937 gen(rand());
            uniform_int_distribution<> dis(1, total_words);
            int random_number = dis(gen);

            int currentIndex = 0;
            file.clear();
            file.seekg(0);
            string selectedWord;
            string hiddenWord;
            while (file >> selectedWord)
            {
                if (currentIndex == random_number)
                {
                    cout << selectedWord << endl;
                    hiddenWord = selectedWord;
                }
                currentIndex++;
            }

            cout << "Its a " << hiddenWord.length() << " letter word." << endl;
            int length = hiddenWord.length();

            char guess[length];
            for (int i = 0; i < length; i++)
            {
                guess[i] = '*';
            }

            printGuess(guess, length);

            for (int i = 0; i < length + 10; i++)
            {
                cout << "You have " << length + 10 - i << " tries left" << endl;
                char temp;
                cin >> temp;

                for (int j = 0; j < length; j++)
                {
                    if (temp == hiddenWord[j])
                    {
                        guess[j] = hiddenWord[j];
                        printGuess(guess, length);
                        if (guess == hiddenWord)
                        {
                            cout << "You guess the word!" << endl;
                            i = length + 10;
                            break;
                        }
                    }
                }
            }
        }
        else if (input == 2)
        {
            file.clear();
            file.seekg(0);
            string word;
            cout << "Enter a new word to add: ";
            string new_word;
            cin >> new_word;
            bool toAdd = true;

            while (file >> word)
            {
                if (new_word == word)
                {
                    cout << "The word '" << new_word << "' already exists in the file." << endl;
                    toAdd = false;
                    break;
                }
            }

            if (toAdd)
            {
                ofstream outfile(filename, ios::app);
                outfile << "\n"
                        << new_word;
                outfile.close();
                cout << "The word '" << new_word << "' has been added to the file." << endl;
            }

            // set<string> words;
            // cout << "Enter a new word to add: ";
            // string new_word;
            // cin >> new_word;

            // if (words.find(new_word) != words.end())
            // {
            //     cout << "The word '" << new_word << "' already exists in the file." << endl;
            // }
            // else
            // {
            //     ofstream outfile(filename, ios::app);
            //     outfile << "\n" << new_word;
            //     outfile.close();
            //     cout << "The word '" << new_word << "' has been added to the file." << endl;
            // }
        }
        else if (input == 3)
        {
            file.clear();
            file.seekg(0);
            string word;
            while (file >> word)
            {
                cout << word << endl;
            }
        }
        else if (input == 4)
        {
            cont = false;
        }
    }

    file.close();
    return 0;
}
