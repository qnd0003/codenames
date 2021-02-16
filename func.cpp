#include "func.h"
std::vector<std::vector<std::string>> getWords(std::string filename) {
	std::ifstream file;
	file.open(filename.c_str());
	if (!file.is_open()) {
		printf("error, cannot open file\n");
		exit(1);
	}
	
	// reading file
	int total_words = 0;
	std::string line;
	std::vector<std::vector<std::string>> lines;
	std::vector<std::string> lineWords;
	while (!file.eof()) {
		std::getline(file, line);
		std::string read;
		if (!line.empty()) {
			std::istringstream ss(line);
			while (getline(ss, read, ',')) {
				lineWords.push_back(read);
			}
			lines.push_back(lineWords);
			lineWords.clear();
		}
	}
	file.close();
	return lines;
}

int rndm(int min, int max) {
	return min + rand() % (max - min + 1);
}

void shuffle(std::vector<std::vector<std::string>> &lines) {
	// shuffle the rows
	std::vector<int> rn;
	srand(time(NULL));
	for (int i = 0; i < 10; i++) { 
		int random = rndm(0, lines.size() - 1);
		std::vector<std::string> temp;
		for (int j = 0; j < lines[random].size(); j++) {
			temp.push_back(lines[random][j]);
		}
		
		lines[random].clear();
		for (int j = 0; j < lines[0].size(); j++) {
			lines[random].push_back(lines[0][j]);
		}

		lines[0].clear();
		for (int j = 0; j < temp.size(); j++) {
			lines[0].push_back(temp[j]);
		}
		
	}
	
	int x = 3;
	// shuffle the words in first x rows size times
	for (int i = 0; i < 3; i++) {
		int y = lines[i].size();
		for (int j = 0; j < y; j++) {
			int rnd = rndm(0, lines[i].size() - 1);
			std::string temp = lines[i][rnd];
			lines[i][rnd] = lines[i][0];
			lines[i][0] = temp;
		}
	}
}

void printVector(std::vector<std::vector<std::string>> lines) {
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[i].size(); j++) {
			std::cout << lines[i][j] << ",";
		}
		std::cout << "\n";
	}
}

std::string lowercase(std::string input) {
	for (int i = 0; i < input.length(); i++) {
		input[i] = tolower(input[i]);
	}
	return input;
}

void menu(std::vector<guessWords> allWords) {
	std::cout << "-----------------------------------------" << std::endl;
	for (int i = 0; i < allWords.size(); i++) {
		for (int j = 0; j < allWords[i].pickedWords.size(); j++) {
			std::cout << "[" << allWords[i].pickedWords[j] << "] ";
		}
		std::cout << "\n";
	}
	std::cout << "-----------------------------------------" << std::endl;
}

void hint(std::vector<guessWords>& allWords, int currentRow, std::string& hintWord, int& hintNum) {
	if (allWords[currentRow].currentHint == allWords[currentRow].similar.size()-1) {
		allWords[currentRow].currentHint = 0;
		hintWord = allWords[currentRow].similar[allWords[currentRow].currentHint];
	} else {
		allWords[currentRow].currentHint++;
		hintWord = allWords[currentRow].similar[allWords[currentRow].currentHint];
	}

	hintNum = allWords[currentRow].hint;

	std::cout << "Hint: [" << allWords[currentRow].similar[allWords[currentRow].currentHint] << "," << allWords[currentRow].hint << "]\n";
}

bool isMatch(std::string input, std::vector<guessWords>& allWords, int currentRow) {
	for (int i = 0; i < allWords[currentRow].pickedWords.size(); i++) {
		if (lowercase(input) == allWords[currentRow].pickedWords[i] && lowercase(input) != FILLERSTRING) {
			allWords[currentRow].pickedWords[i] = FILLERSTRING;
			allWords[currentRow].hint--;
			return true;
		}
	}
	return false;
}

void chooseRow(std::vector<guessWords> allWords, int &currentRow) {
	// find the row
	bool change = false;
	for (int i = currentRow+1; i < allWords.size(); i++) {
		if (allWords[i].hint > 0) {
			currentRow = i;
			change = true;
			break;
		}
	}

	if (!change) {
		for (int i = 0; i < currentRow; i++) {
			if (allWords[i].hint > 0) {
				currentRow = i;
				break;
			}
		}
	}
}

// shuffle display
std::vector<std::string> getAllWords(std::vector<guessWords> allWords) {
	std::vector<std::string> w;
	for (int i = 0; i < allWords.size(); i++) {
		for (int j = 0; j < allWords[i].pickedWords.size(); j++) {
			w.push_back(allWords[i].pickedWords[j]);
		}
	}
	
	// shuffle the list
	for (int i = 0; i < 20; i++) {
		int random = rndm(0, w.size()-1);
		std::string temp = w[random];
		w[random] = w[0];
		w[0] = temp;
	}

	return w;
}

void printList(std::vector<std::string> list) {
	std::cout << "--------------------------------------\n";
	for (int i = 0; i < list.size(); i++) {
		if (i % 4 == 0 && i > 0)
			std::cout << "\n";
		std::cout << "[" << list[i] << "] ";
	}
	std::cout << "\n";
	std::cout << "--------------------------------------\n";
}

void updateList(std::vector<std::string> &list, std::string input) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == input) {
			list[i] = FILLERSTRING;
		}
	}
}
