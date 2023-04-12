#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void nerdler( std::string in,  std::string floating, std::set<std::string>* words);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> words;

    //wordler(in, floating, &words);

    nerdler(in, floating, &words);

    std::set<std::string> valid;

    std::set<std::string>::iterator it;


    for(it = words.begin(); it != words.end(); it++){
      if (dict.find(*it) != dict.end()){
        valid.insert(*it);
      }
    }

  return valid;
}

// Define any helper functions here

void nerdler( std::string in,  std::string floating, std::set<std::string>* words){

  //std::cout << in << std::endl;


  for(size_t i = 0; i < in.length(); i++){
    std::string sin = in;
    if(in[i] == '-' && floating.length() > 0){
        sin[i] = floating[floating.length()-1];
        std::string fl = floating;
        fl.pop_back();
        nerdler(sin, fl, words);
    }
    else if(in[i] == '-'){
      for(char c = 'a'; c <= 'z'; c++){
        sin[i] = c;
        nerdler(sin, floating, words);
      }
    }

    if(i == in.length()-1) words->insert(sin);
  }
}


