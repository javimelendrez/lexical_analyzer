#include<iostream>
#include<fstream> //for ifstream
#include<stdlib.h>
#include<string.h>
#include<ctype.h> //for isalnum
#include <vector>
#include <string>
using namespace std;
//array of keywords
int Keyword(char buffer[]) {
	char keywords[32][10] = { "auto","break","case","char","const","continue","default", //has to be represented by 2d array
		"do","double","else","enum","extern","float","for","goto",
		"if","int","long","register","return","short","signed",
		"sizeof","static","struct","switch","typedef","union",
		"unsigned","void","volatile","while" };
	int i, f = 0;

	for (i = 0; i < 32; ++i) {
		if (strcmp(keywords[i], buffer) == 0) { //Compare two strings
			f = 1;
			break;
		}
	}

	return f;
}

int main() {
	string filename; //hold file name
	ofstream outputFile; //will be used for output file
	outputFile.open("output.txt"); //open and write to this 1
	vector<char> g1; //create vector to put all ch in
	char ch, buffer[15], operators[] = "*+-=/><%"; //define operators and separators
	char separators[] = "'(){}[],.:;";
	cout << "what is the name of the file?" << endl; //ask for the name of the file and open it
	cin >> filename;
	ifstream fin(filename);
	int i, j = 0, k;
	//int hello = 5;
	if (!fin.is_open()) { //check if open success
		cout << "error while opening the file\n";
		exit(0);
	}
	cout << "Tokens - Lexemes \n";
	while (!fin.eof()) { //until the end of the file push into the vector
		ch = fin.get();
		g1.push_back(ch);

	}
	fin.close();
	//    for (auto i = g1.begin(); i != g1.end(); ++i)
	//        cout << *i << " ";
	for (auto i = g1.begin(); i != g1.end(); ++i) { //loop through the vector now
		for (int a = 0; a < 8; a++) {
			if (*i == operators[a]) { //if you find operator write it into the file
				cout << "operator = " << *i << endl;
				outputFile << "operator = " << *i << endl;
			}
		}
		for (int b = 0; b < 11; b++) {
			if (*i == separators[b]) { //if you find a separator write it into the file
				cout << "separator = " << *i << endl;
				outputFile << "separator = " << *i << endl;
			}
		}
		if (*i == '!') //if you reach comment ignore what is in between until you see the comment again
		{
			for (auto z = i + 1; z != g1.end(); ++z) {
				if (*z == '!') {
					//set the outer counter to the new
					i = z; //this should skip everything between comments
				}
			}
		}
		//        if (*i == ' ') {
		//            cout << "separator sp" << endl;
		//        } this recognizes if the char is a space
		if (isalnum(*i)) { //check for num
			buffer[j++] = *i;
		}
		else if ((*i == ' ' || *i == '\n') && (j != 0)) {
			buffer[j] = '\0';
			j = 0;

			if (Keyword(buffer) == 1) { //check if keyword or identifier
				cout << "Keyword = " << buffer << endl;
				outputFile << "Keyword = " << buffer << endl;
			}
			else {
				cout << "Identifier = " << buffer << endl;
				outputFile << "Identifier = " << buffer << endl;
			}
		
		}
	}
	system("pause"); //use to pause terminal
	return 0;
}

