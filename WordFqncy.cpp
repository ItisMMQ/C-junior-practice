//****************************  genSplay.cpp ****************************

#include <iostream>
#include <fstream>
#include <cctype> //此库为字符函数库
#include <cstring>
#include <cstdlib> //该头文件相对于C里的stdlib.h,包含exit()等标准函数; 
#include "WordFqncy.h"

using namespace std;

class Word {
	friend class WordSplay;
public:
	Word() {freq = 1;}
	int operator== (const Word& ir) const {
		return strcmp(word, ir.word) == 0;
	}
	int operator< (const Word& ir) const {
		return strcmp(word, ir.word) < 0;
	}
private:
	char *word;
	int freq;
};

class WordSplay : public SplayTree<Word> {
public:
	WordSplay() {
		differentWords = wordCnt = 0;
	}
	void run(ifstream&, char*);
private:
	int differentWords, // counter of different words in a text file;
		wordCnt;            // counter of all words in the same file;
	void visit(SplayingNode<Word>*);
};
//仅计数，在访问当前值时
void WordSplay::visit(SplayingNode<Word> *p) {
	differentWords++;           
	wordCnt += p->info.freq;
}

void WordSplay::run(ifstream& fIn, char *fileName) {
	char ch = ' ', i;
	char s[100];
	Word rec;
	while (!fIn.eof()) {//确认文件未结束，见P280
		while (1)
			if (!fIn.eof() && !isalpha(ch)) // skip nonletters
				fIn.get(ch);
			else break;
			if (fIn.eof())       // spaces at the end of fIn;
				break;
			for (i = 0; !fIn.eof() && isalpha(ch); i++) {
				s[i] = toupper(ch);
				fIn.get(ch);
			}
			s[i] = '\0';
			if (!(rec.word = new char[strlen(s) + 1])) {
				cerr << "No room for new words.\n";
				exit(1);
			}
			strcpy(rec.word, s);
			Word *p = search(rec);
			if (p == 0)
				insert(rec);
			else p->freq++;
	}
	inorder();
	cout << "\n\nFile " << fileName
		<< " contains " << wordCnt << " words among which "
		<< differentWords << " are different\n";
}
//实为主函数
int count(int argc, char* argv[]) {
	char fileName[80];
	WordSplay splayTree;
	if (argc != 2) {
		cout << "Enter a file name: ";
		cin >> fileName;
	}
	else strcpy(fileName, argv[1]);
	ifstream fIn(fileName);
	if (fIn.fail()) {
		cerr << "Cannot open " << fileName << endl;
		return 1;
	}
	splayTree.run(fIn, fileName);
	fIn.close();
	return 0;
}
