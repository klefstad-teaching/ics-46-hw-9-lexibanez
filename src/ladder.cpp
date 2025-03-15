#include "ladder.h"
#include <algorithm>

void error(string word1, string word2, string msg) {
    cout << "Error: " << word1 << " " << word2 << " " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d) {return false;}

    int diff_count = 0;
    int i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            diff_count++;
            if (diff_count > d) return false;
            if (len1 < len2) {j++;}
            else if (len1 > len2) {i++;}
            else {i++; j++;}
        } else {
            i++;
            j++;
        }
    } diff_count += len1 - i + len2 - j;
    return diff_count <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    set<string> visited;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream word_file(file_name);
    string word;
    while (word_file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    for (const string& word: ladder) {
        cout << word << " ";
    }
    cout << endl;
}

void verify_word_ladder() {
    string begin_word, end_word;
    cout << "Enter the start word: ";
    cin >> begin_word;
    cout << "Enter the end word: ";
    cin >> end_word;

    transform(begin_word.begin(), begin_word.end(), begin_word.begin(), ::tolower);
    transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);

    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words must be different.");
        return;
    }

    set<string> word_list;
    load_words(word_list, "words.txt");

    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    if (!ladder.empty()) {
        cout << "Word ladder found: ";
        print_word_ladder(ladder);
    } else {
        cout << "No ladder found." << endl;
    }
}