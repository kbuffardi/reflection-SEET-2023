/**
 * Unit Tests for Practice class
**/

#include <gtest/gtest.h>
#include "WordlerPro.h"

class WordlerProTest : public ::testing::Test
{
	protected:
		WordlerProTest(){} //constructor runs before each test
		virtual ~WordlerProTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Test cases:
