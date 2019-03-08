/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<StringTriple> result;
    ifstream word_list_file(word_list_fname);
    string word;
    if (word_list_file.is_open()) {
        while (getline(word_list_file, word)) {
            if (word.length() >= 3) {
                string first_removed = word.substr(1, word.length());
                string second_removed = word[0] + word.substr(2, word.length());
                if (d.homophones(word, first_removed)
                    && d.homophones(word, second_removed)) {
                    result.emplace_back(word, first_removed, second_removed);
                }
            }
        }
    }
    return result;
}
