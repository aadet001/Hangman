#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <iterator>

using namespace std;

class hangman {
public:
	hangman() {
		vector<char> t(6, ' ');
		pts = t;
		strike = 0;

		fill_dictionary();
		getword();

		int k = word.size();
		vector<char> x(k, '_');
		table = x;
	}

	void fill_dictionary() {
		ifstream f("dictionary.txt");
		string s;
		while (getline(f, s)) {
			dictionary.push_back(s);
		}
		f.close();
	}

	void getword() {
		srand(time(NULL));

		word = dictionary.at(rand() % 223);

	}

	void print_table() {
		for (unsigned int i = 0; i < word.size(); i++) {
			cout << table.at(i) << " ";
		}
		cout << endl;
	}

	void pass_input() {
		size_t pos = word.find(guess);
		string t = word;
		int n = 0;
		if (pos == string::npos) {
			attempts.push_back(guess);
			pts[strike] = tree.at(strike);
			strike++;
			if (strike == 6) {
				lost = true;
			}
			return;
		}
		while (pos != string::npos) {
			table[pos + n] = guess;
			t.erase(t.begin() + pos);
			pos = t.find(guess);
			n++;
		}

		attempts.push_back(guess);

	}

	void get_input() {
		cout << "Guess: ";
		cin >> guess;

		pass_input();
	}

	void print_attempts() {
		cout << "Attempted: ";
		for (unsigned int i = 0; i < attempts.size(); i++) {
			cout << attempts.at(i) << " ";
		}
		cout << endl;
	}

	void update_screen() {
		system("CLS");

		cout << "+------+        w: " << win << " - l: " << loss << endl
			<< "|      |\n"
			<< "|      " << pts[0] << endl
			<< "|     " << pts[1] << pts[2] << pts[3] << endl
			<< "|     " << pts[4] << " " << pts[5] << endl
			<< "|" << endl;

		print_attempts();
		print_table();
	}

	void clear_board() {
		vector<char> t(6, ' ');
		pts = t;
		strike = 0;

		fill_dictionary();
		getword();

		int k = word.size();
		vector<char> x(k, '_');
		table = x;

		attempts.clear();
		won = false;
		lost = false;
	}

	void run() {
	another:
		string in;
		while (won == false) {
			auto it = find(table.begin(), table.end(), '_');

			update_screen();
			if (it == table.end()) {
				win++;
				won = true;
				cout << "You win!\n";
				break;
			}
			if (lost == true) {
				loss++;
				cout << "Hangman!\nAnswer: ";
				cout << word << endl;
				break;
			}
			get_input();
			cin.ignore();

		}

		cout << "play again? (y/n) ";
		cin >> in;
		if (in == "y" || in == "Y") {
			clear_board();
			goto another;
		}
	}

private:
	bool lost = false, won = false;
	char guess;
	string word;
	vector<string> dictionary;
	int win = 0, loss = 0, strike;
	vector<char> tree = { '0', '/', '|', '\\', '/', '\\' };
	vector<char> pts, table, attempts;
};


int main() {
	/*vector<string> dict;
	ifstream f("dictionary.txt");
	string s;
	while (getline(f, s)) {
	dict.push_back(s);
	}
	f.close();*/

	//ofstream o("dictionary.txt"); 
	//size_t p; 
	//for (unsigned int i = 0; i < dict.size(); i++) {
	//	p = dict.at(i).find(' ');
	//	if (p != string::npos) {
	//		dict[i].erase(dict.at(i).begin() + p);
	//	}
	//	//o << dict.at(i) << "\n";
	//	
	//}
	//ostream_iterator<string> oi(o, "\n");
	//copy(dict.begin(), dict.end(), oi);
	//o.close(); 

	hangman h;
	h.run();


	return 0;
}