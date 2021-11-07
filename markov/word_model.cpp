/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Lucas Henke

   Modified: 10/24/2019
*/

#include "word_model.h"
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void word_model::initialize(string text, int order) {
    _markov.clear();
    while(text[text.size() - 1] == ' '){
        text = text.substr(0, text.size() - 1);
    }

    _training_text = text;
    _order = order;
    text += " ";
    int start = 0;
    for(int i = 0; i < _order; i++){
        string addon = text.substr(start, text.find(' ', start + 1) - start);
        start = text.find(' ', start + 1);
        text += addon;
    }
    text += " ";
    _original_training_text_size = text.size();
    int end = 0;
    int first = 0;
    while(end < _original_training_text_size){
        end = 0;
        for(int j = 1; j <= _order; j++){
            if(j == 1){
                first = text.find(' ',end + 1);
            }
            end = text.find(' ',end + 1);
        }
        string key = text.substr(0, end);
        string element = text.substr(end + 1,text.find(' ',end + 1) - end - 1);
        if(element == ""){
            break;
        }
        _markov[key].push_back(element);
        text = text.substr(first + 1, text.size() - (first + 1));
        _original_training_text_size += -(first + 1);
    }

}


string word_model::generate(int size) {
    string random_generated = "";
    int s = rand() % _markov.size();
    int i = 0;
    string key;
    for(auto &pair: _markov){
        if(i == s){
            key = pair.first;
        }
        else{
            i++;
        }
    }

    for(int i = 0; i < size; i++){
        vector<string> words = _markov.at(key);
        string word = words[rand() % words.size()];
        random_generated += word + " ";
        if(_order == 1){
            key = word;
        }
        else{
            key = key.substr(key.find(' ') + 1, key.size() - key.find(' ') + 1) + " " + word;
        }
    }

    return random_generated;
}
