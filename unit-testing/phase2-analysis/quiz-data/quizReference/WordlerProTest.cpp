/**
 * Unit Tests for Practice class
**/

#include <gtest/gtest.h>
#include "WordlerPro.h"
#include <string>
using namespace std;
class WordlerProTest : public ::testing::Test
{
	protected:
		WordlerProTest(){} //constructor runs before each test
		virtual ~WordlerProTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Test cases:
TEST(WordlerProTest, smoke_test)
{
    ASSERT_TRUE(true);
}

TEST(WordlerProTest, default_secret)
{
	WordlerPro obj("      ");
	ASSERT_EQ("PUZZLE", obj.submit_guess("PUZZLE") );
}

TEST(WordlerProTest, secret_too_short)
{
	WordlerPro obj("X");
	ASSERT_EQ("PUZZLE", obj.submit_guess("PUZZLE") );
}

TEST(WordlerProTest, secret_too_long)
{
	WordlerPro obj("ABCDEFGHIJKLM");
	ASSERT_EQ("PUZZLE", obj.submit_guess("PUZZLE") );
}

TEST(WordlerProTest, secret_min_length)
{
	WordlerPro obj("YA");
	ASSERT_EQ("YA", obj.submit_guess("YA") );
}

TEST(WordlerProTest, secret_max_length)
{
	WordlerPro obj("YAYAYAYAYAYA");
	ASSERT_EQ("YAYAYAYAYAYA", obj.submit_guess("YAYAYAYAYAYA") );
}

TEST(WordlerProTest, guess_too_long)
{
	WordlerPro obj("ABCD");
	ASSERT_EQ("", obj.submit_guess("ABCDE") );
}

TEST(WordlerProTest, guess_too_short)
{
	WordlerPro obj("ABCD");
	ASSERT_EQ("", obj.submit_guess("ABC") );
}

TEST(WordlerProTest, guess_matched_letter)
{
	WordlerPro obj("ABBB");
	ASSERT_EQ("A---", obj.submit_guess("AXXX") );
}

TEST(WordlerProTest, guess_matched_letter_end)
{
	WordlerPro obj("ABCDE");
	ASSERT_EQ("----E", obj.submit_guess("XXXXE") );
}

TEST(WordlerProTest, guess_multi_matched_letters)
{
	WordlerPro obj("ABCDE");
	ASSERT_EQ("A---E", obj.submit_guess("AXXXE") );
}

TEST(WordlerProTest, guess_misplaced_letter_after)
{
	WordlerPro obj("ABCDE");
	ASSERT_EQ("-?---", obj.submit_guess("XAXXX") );
}

TEST(WordlerProTest, guess_misplaced_letter_before)
{
	WordlerPro obj("ABCDE");
	ASSERT_EQ("?----", obj.submit_guess("BXXXX") );
}

TEST(WordlerProTest, guess_misplaced_letter_repeated)
{
	WordlerPro obj("ABABA");
	ASSERT_EQ("-?---", obj.submit_guess("XAXXX") );
}

TEST(WordlerProTest, guess_repeated_misplaced_letter)
{
	WordlerPro obj("AYYYY");
	ASSERT_EQ("-\?\?\?\?", obj.submit_guess("XAAAA") );
}

TEST(WordlerProTest, guess_repeated_correct)
{
	WordlerPro obj("CORRECT");
	ASSERT_EQ("CORRECT", obj.submit_guess("CORRECT") );
	ASSERT_EQ("CORRECT", obj.submit_guess("CORRECT") );
	ASSERT_EQ("CORRECT", obj.submit_guess("CORRECT") );
}

TEST(WordlerProTest, guess_two_misplaced_letters)
{
	WordlerPro obj("ABCCBA");
	ASSERT_EQ("--\?\?--", obj.submit_guess("XXABXX") );
}

TEST(WordlerProTest, guess_misplaced_and_matched_letters)
{
	WordlerPro obj("ABCCBA");
	ASSERT_EQ("-\?\?CBA", obj.submit_guess("XCBCBA") );
}

TEST(WordlerProTest, guess_all_misplaced)
{
	WordlerPro obj("ABCD");
	ASSERT_EQ("\?\?\?\?", obj.submit_guess("DABC") );
}

TEST(WordlerProTest, second_guess_right)
{
	WordlerPro obj("ABCD");
	ASSERT_EQ("\?\?\?\?", obj.submit_guess("DABC") );
	ASSERT_EQ("ABCD", obj.submit_guess("ABCD") );
}

TEST(WordlerProTest, history_one_guess)
{
	WordlerPro obj("WORD");
	obj.submit_guess("LOST");
	ASSERT_EQ("-O--\n",obj.get_history()  );
}

TEST(WordlerProTest, history_before_guesses)
{
	WordlerPro obj("WORD");
	ASSERT_EQ("",obj.get_history()  );
}

TEST(WordlerProTest, history_after_too_short_guess)
{
	WordlerPro obj("WORD");
	obj.submit_guess("A");
	ASSERT_EQ("",obj.get_history()  );
}

TEST(WordlerProTest, history_after_too_long_guess)
{
	WordlerPro obj("WORD");
	obj.submit_guess("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	ASSERT_EQ("", obj.get_history()  );
}

TEST(WordlerProTest, history_after_lowercase_guess)
{
	WordlerPro obj("WORD");
	obj.submit_guess("word");
	ASSERT_EQ("", obj.get_history()  );
}

TEST(WordlerProTest, history_after_invalid_symbols_guess)
{
	WordlerPro obj("WORD");
	obj.submit_guess("----");
	ASSERT_EQ("", obj.get_history()  );
}

TEST(WordlerProTest, history_multiple_guesses)
{
	WordlerPro obj("WORD");
	obj.submit_guess("LOVE");
	obj.submit_guess("PORT");
	ASSERT_EQ("-O--\n-OR-\n", obj.get_history() );
}

TEST(WordlerProTest, history_invalid_between_multiple_guesses)
{
	WordlerPro obj("WORD");
	obj.submit_guess("LOVE");
	obj.submit_guess("TWO");
	obj.submit_guess("PORT");
	ASSERT_EQ("-O--\n-OR-\n", obj.get_history() );
}

TEST(WordlerProTest, history_with_correct_guess)
{
	WordlerPro obj("WORD");
	obj.submit_guess("LOVE");
	obj.submit_guess("PORT");
	obj.submit_guess("WORD");
	ASSERT_EQ("-O--\n-OR-\nWORD\n", obj.get_history() );
}

TEST(WordlerProTest, history_with_correct_guess_repeated)
{
	WordlerPro obj("WORD");
	obj.submit_guess("LOVE");
	obj.submit_guess("PORT");
	obj.submit_guess("WORD");
	obj.submit_guess("WORD");
	ASSERT_EQ("-O--\n-OR-\nWORD\n", obj.get_history() );
}

TEST(WordlerProTest, history_with_wrong_after_right_guess)
{
	WordlerPro obj("WORD");
	obj.submit_guess("LOVE");
	obj.submit_guess("PORT");
	obj.submit_guess("WORD");
	obj.submit_guess("MORE");
	ASSERT_EQ("-O--\n-OR-\nWORD\n", obj.get_history() );
}

TEST(WordlerProTest, SubmitGuess_InvalidGuessAlpha)
{
	string secret = "SCIENCE";
	WordlerPro testObject(secret);
	ASSERT_EQ(testObject.submit_guess("SC13NC3"), "");
}