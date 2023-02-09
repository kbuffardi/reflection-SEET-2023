#include "WordlerPro.h"

/*
  Initiates a game with a provided secret word. The word must have only
  letters in the English alphabet, in ALL UPPER CASE (A-Z) and between
  2-12 characters. If an invalid string is provided, the secret word should
  default to "PUZZLE"
*/
WordlerPro::WordlerPro(std::string secret){
  if( isValid(secret) ){
    m_secret = secret;
  }
  else{
    m_secret = "PUZZLE";
  }
  m_history = "";
  m_correct = false;
}

bool WordlerPro::isValid(std::string word){
  if(word.length() >= 2 && word.length() <=12){
    for(int i=0; i<word.length(); i++){
      if( word[i] < 'A' || word[i] > 'Z' ){
        return false;
      }
    }
    return true;
  }
  else{
    return false;
  }
}

/*
  A string parameter submits a guess to compare to the secret. If they match,
  the guess is correct and should be returned. Otherwise, a comparison string
  should be returned, which indicates matched letters, misplaced letters, and
  incorrect letters.

  Matched letters are where a letter is in the right location within the
  secret word and should be displayed as such. For example, if the guess is
  "PUDDLE" for the default "PUZZLE" secret, 'P' 'U' 'L' and 'E' are matched
  letters and should return: "PU--LE"

  Misplaced letters are any letters that are in the secret word, but are not
  in the same location in the word. Misplaced letters should be displayed as
  a '?' even if there is a difference in number of times it is in the secret
  word. For example, if the guess is "LEADED" and secret is "PUZZLE" then
  'L' and 'E' are misplaced letters and should return "??--?-"

  Incorrect letters are any that are neither matched nor misplaced.

  If the guess is invalid, it should not be registered as an official guess
  and an empty string "" should be returned. Invalid guesses include any
  strings without the matching number of characters as the secret and/or any
  strings that contain characters that are not upper case English alphabet
  letters.
*/
std::string WordlerPro::submit_guess(std::string guess){
  std::string hint = "";
  if( isValid(guess) && guess.length() == m_secret.length() ){
    hint = guess;
    for(int i=0; i<guess.length(); i++){
      if( guess[i] == m_secret[i] ){
        hint[i] = guess[i];
      }
      else{
        char letter = guess[i];
        bool found = false;
        for(int j=0; j<m_secret.length(); j++){
          if( m_secret[j] == letter ){
            hint[i] = '\?';
            found = true;
          }
        }
        if( !found ){
          hint[i] = '-';
        }
      }
    }
    if( !m_correct ){
      m_history += hint + '\n';
    }
    if( hint == m_secret ){
      m_correct = true;
    }
  }
  return hint;
}

/*
  This function shows the history of registered guesses, as represented by
  their hints. The hints are the strings returned by submit_guess when there
  are valid/registered guesses. Each hint should be on its own line. For
  example, if the secret is "PUZZLE" and the guesses are "LEADED" then
  "PUDDLE" then "PUZZLE" the history should show:
  ??--?-
  PU--LE
  PUZZLE

  If more guesses are submitted after the correct word has been guessed, they
  should be excluded from the history. If no guesses have been made, the
  history should be an empty string ""
*/
std::string WordlerPro::get_history(){
  return m_history;
}
