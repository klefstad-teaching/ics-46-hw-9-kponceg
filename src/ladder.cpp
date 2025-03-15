#include "ladder.h"
#include <queue>
#include <vector>

void error(string word1, string word2, string msg){
    cerr << word1 << msg << word2;
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
            if (is_adjacent(last_word, word) && !visited.contains(word)){
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) return new_ladder;
            }
        }
    }
    return partial_ladder;
}