/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Lucas Henke

   Modified: 10/24/2019
*/

#include "map_model.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

void map_model::initialize(string text, int order) {
    _matrix.clear();
    text = text.substr(0,text.size() - 1);
    _original_training_text_size = text.size();
    text += text.substr(0, order);
    _training_text = text;
    _order = order;
    for(int i = 0; i < _original_training_text_size; i++){
        string key = text.substr(i, _order);
        _matrix[key].push_back(text[i + order]);
    }
}

string map_model::generate(int size) {
    int start_index = rand() % _original_training_text_size;
    string random_generated = "";
    string seed = _training_text.substr(start_index, _order);

    for(int i = 0; i < size; i++){
        vector<char> letters = _matrix.at(seed);
        char random_letter = letters[rand() % letters.size()];
        random_generated += random_letter;
        seed = seed.substr(1,seed.size() - 1) + random_letter;
    }
    return random_generated;
}


