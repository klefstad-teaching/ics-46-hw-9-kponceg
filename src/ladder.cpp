#include "ladder.h"
#include <cassert>

void error(string word1, string word2, string msg){
    cerr << word1 << msg << word2;
}

bool same_distance(string word1, string word2){
    for (int i = 0; i < word1.length(); i++){
        string copy_word1 = word1, copy_word2 = word2;
        copy_word1[i] = '_' ; copy_word2[i] = '_';
        if (copy_word1 == copy_word2) return true;
    }
    return false;
}

auto small_string = [](const string& str1, const string& str2){return str1.length() < str2.length();};

bool add_letter(string &smaller_string, string &bigger_string, int d){
    for (int i = 0; i < d; i++){
        string copy_smallString = smaller_string, copy_biggerString = bigger_string;
        copy_smallString.insert(i, 1, '_'); copy_biggerString[i] = '_';
        if (copy_smallString == copy_biggerString) return true;
    }
    return false;
}

bool remove_letter(string& smaller_string, string& bigger_string, int d){
    for (int i = 0; i < d; i++){
        string copy_biggerString = bigger_string;
        copy_biggerString.erase(i, 1);
        if (smaller_string == copy_biggerString) return true;
    }
    return false;
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d){
    string smaller_string, bigger_string;
    if (small_string(str1, str2)) smaller_string = str1, bigger_string = str2;
    else  smaller_string = str2, bigger_string = str1;
    if ((bigger_string.length()-smaller_string.length()) > 1) return false;
    if (add_letter(smaller_string, bigger_string, d)) return true;
    if (remove_letter(smaller_string, bigger_string, d)) return true;
    return false;
}

bool is_adjacent(const string &word1, const string &word2){
    if (word1 == word2) return false;
    if (word1.length() == word2.length()) return same_distance(word1, word2);
    else{
        int d = (word1.length() > word2.length()) ? word1.length() : word2.length();
        return edit_distance_within(word1, word2, d);}
    return false;
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list){
    vector<string> partial_ladder;
    if (begin_word == end_word) {
        partial_ladder.push_back(begin_word);
        return partial_ladder;
    }
    set<string> visited;
    queue<vector<string>> ladder_queue;
    partial_ladder.push_back(begin_word);
    ladder_queue.push(partial_ladder);
    visited.insert(begin_word);

    while (!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (auto word : word_list){
            if (is_adjacent(last_word, word) && !visited.count(word)){
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }
    return partial_ladder;
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    for (string word; in >> word;) word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string> &ladder){
    for (auto word: ladder){
        cout << word << "-->";
    }
    cout << endl;
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");
    assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    assert(generate_word_ladder("code", "data", word_list).size() == 6);
    assert(generate_word_ladder("work", "play", word_list).size() == 6);
    assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
    vector<string> ladder = generate_word_ladder("wow", "woven", word_list);
    print_word_ladder(ladder);
}