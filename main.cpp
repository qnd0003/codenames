#include <iostream>
#include "func.h"
#include <iterator>

int main() {
	std::vector<std::vector<std::string>> lines = getWords("words.txt");
	
	// shuffling the data vector
	shuffle(lines);
	
	// struct vector
	std::vector<guessWords> allWords;

	int linesnum = 3;
	int n = 4; // number of selected words/hints for each row
	for (int i = 0; i < linesnum; i++) {
		// pick random # of words from first three rows
		std::vector<std::string> picked;
		for (int j = 0; j < n; j++) {
			picked.push_back(lines[i][j]);
		}
		std::vector<std::string> similar;
		for (int j = n; j < lines[i].size(); j++) {
			similar.push_back(lines[i][j]);
		}
		
		allWords.push_back(guessWords {picked, similar, n, 0});
		picked.clear();
		similar.clear();
	}

	// get allWords as 1D vector
	std::vector<std::string> list = getAllWords(allWords);
	
	// 1st row's turn
	int currentRow = 0;
	int lives = 3; // three lives
	int right = 0;
	int limit = 6; // get this many correct guesses to win
	std::string hintWord;
	int hintNum = 0;

	// game
	bool run = 1;
	while (run) {
		// display words
		// menu(allWords);
		printList(list);
		// display hint
		printf("End turn: \"!\"\n");
		hint(allWords, currentRow, hintWord, hintNum);
		int inputCount = allWords[currentRow].hint;

		// user input
		std::string input;
		while (input != "!" || inputCount != 0) {
			printf("-> ");
			std::cin >> input; 
			
			// end turn
			if (input == "!") {
				std::cout << "end turn" << "\n";
				break;
			}
			
			// match word
			if (isMatch(input, allWords, currentRow)) {
				std::cout << "MATCH" << "\n";
				updateList(list, lowercase(input));
				inputCount--;
				right++;
				if (right == limit) {
					std::cout << "you win\n";
					printList(list);
					exit(1);
				}
				hintNum--;
			} else {
				// end turn by wrong guess
				std::cout << "WRONG!" << "\n";
				lives--;
				if (lives == 0) {
					std::cout << "out of lives" << "\n";
					exit(1);
				}
				break;
			}
			
			// end turn by guessing all the words in the same row
			if (inputCount == 0) {
				std::cout << "You've guessed all the words" << "\n";
				break;
			}
			
			// display
			//menu(allWords);
			printList(list);
			std::cout << "Hint: [" << hintWord << "," << hintNum << "]\n";
		}

		// select row
		chooseRow(allWords, currentRow);
	}

	return 0;
}
