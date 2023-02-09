#ifndef _WORDLERPRO_H_
#define _WORDLERPRO_H_

#include <string>

class WordlerPro{
private:

public:
  /*
    Initiates a game with a provided secret word. The word must have only
    letters in the English alphabet, in ALL UPPER CASE (A-Z) and between
    2-12 characters. If an invalid string is provided, the secret word should
    default to "PUZZLE"
  */
  WordlerPro(std::string secret);

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
  std::string submit_guess(std::string guess);

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
  std::string get_history();


};

#endif
