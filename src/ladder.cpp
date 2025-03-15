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
}

void verify_word_ladder() {
    
}