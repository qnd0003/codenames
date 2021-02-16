#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctype.h>

#define FILLERSTRING ".."

struct guessWords {
	std::vector<std::string> pickedWords;
	std::vector<std::string> similar;
	int hint;
	int currentHint;
};

// get all the words
std::vector<std::vector<std::string>> getWords(std::string);
// random generate
int rndm(int, int);
// shuffle 
void shuffle(std::vector<std::vector<std::string>>&);
// data vector
void printVector(std::vector<std::vector<std::string>>);
// convert string to lowercase
std::string lowercase(std::string input);
// menu
void menu(std::vector<guessWords>);
// hint
void hint(std::vector<guessWords>& allWords, int currentRow, std::string&, int&);
// check for matching words
bool isMatch(std::string input, std::vector<guessWords>& allWords, int currentRow);
// choose row
void chooseRow(std::vector<guessWords> allWords, int& currentRow);
// get list
std::vector<std::string> getAllWords(std::vector<guessWords> allWords);
// print list
void printList(std::vector<std::string> list);
// list displaying list
void updateList(std::vector<std::string> &, std::string);
