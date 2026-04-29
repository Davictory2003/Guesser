/**
 * Unit Tests for the class
 **/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
protected:
	GuesserTest() {}		   // constructor runs before each test
	virtual ~GuesserTest() {}  // destructor cleans up after tests
	virtual void SetUp() {}	   // sets up before each test (after constructor)
	virtual void TearDown() {} // clean up after each test, (before destructor)
};

TEST(GuesserTest, match_exact_string)
{
	Guesser g("Secret");
	ASSERT_TRUE(g.match("Secret"));
}

TEST(GuesserTest, match_incorrect_length_diff_less_than_two)
{
	Guesser g("Secret");
	ASSERT_FALSE(g.match("Secre"));
}

TEST(GuesserTest, match_incorrect_length_diff_greater_than_two)
{
	Guesser g("Secret");
	ASSERT_FALSE(g.match("Sec"));
}

TEST(GuesserTest, match_incorrect_char_diff_less_than_two)
{
	Guesser g("Secret");
	ASSERT_FALSE(g.match("Secrtt"));
}

TEST(GuesserTest, match_incorrect_char_diff_greater_than_two)
{
	Guesser g("Secret");
	ASSERT_FALSE(g.match("Scccct"));
}

TEST(GuesserTest, brute_force_lock)
{
	Guesser g("Secret");
	g.match("Scccct");
	ASSERT_FALSE(g.match("Secret"));
}

TEST(GuesserTest, three_consecutive_fails_locks)
{
	Guesser g("Secret");
	g.match("Secre");
	g.match("Secre");
	g.match("Secre");
	ASSERT_FALSE(g.match("Secret"));
}

TEST(GuesserTest, reset_on_successful_match)
{
	Guesser g("Secret");
	g.match("Secre");
	g.match("Secre");
	g.match("Secret");

	g.match("Secre");
	g.match("Secre");
	ASSERT_TRUE(g.match("Secret"));
}

TEST(GuesserTest, constructor_truncate_secret)
{
	Guesser g("123456789012345678901234567890123");
	ASSERT_TRUE(g.match("12345678901234567890123456789012"));
}

TEST(GuesserTest, constructor_no_truncate_secret)
{
	Guesser g("12345678901234567890123456789012");
	ASSERT_TRUE(g.match("12345678901234567890123456789012"));
}

TEST(GuesserTest, distance_guess_much_longer_than_secret)
{
	Guesser g("Sec");
	g.match("Secret1");
	ASSERT_FALSE(g.match("Sec"));
}

TEST(GuesserTest, distance_exactly_two_does_not_lock)
{
	Guesser g("Secret");
	g.match("Secrtt");
	ASSERT_TRUE(g.match("Secret"));
}

TEST(GuesserTest, distance_exactly_three_locks)
{
	Guesser g("Secret");
	g.match("Secxxx");
	ASSERT_FALSE(g.match("Secret"));
}

TEST(GuesserTest, empty_string_match)
{
	Guesser g("");
	ASSERT_TRUE(g.match(""));
}

TEST(GuesserTest, empty_secret_guess_does_not_lock_due_to_cap)
{
	Guesser g("");
	g.match("123");
	ASSERT_TRUE(g.match(""));
}

TEST(GuesserTest, guess_longer_than_secret_char_mismatches)
{
	Guesser g("abcd");
	g.match("abce12");
	ASSERT_FALSE(g.match("abcd"));
}
TEST(GuesserTest, remaining_and_locked_combinations)
{
	Guesser g("Secret");
	g.match("Sec");
	ASSERT_FALSE(g.match("Secret"));
	ASSERT_FALSE(g.match("Sec"));
}

TEST(GuesserTest, lock_on_last_remaining)
{
	Guesser g("Secret");
	g.match("Secre");
	g.match("Secre");
	g.match("Sec");
	ASSERT_FALSE(g.match("Secret"));
}

TEST(GuesserTest, distance_truncation_large_length_diff)
{
	Guesser g("A");
	g.match("AAAA");
	ASSERT_TRUE(g.match("A"));
}

TEST(GuesserTest, distance_completely_different_strings)
{
	Guesser g("abc");
	g.match("xyz");
	ASSERT_FALSE(g.match("abc"));
}

TEST(GuesserTest, guess_longer_than_truncated_secret)
{
	Guesser g("123456789012345678901234567890123");
	ASSERT_FALSE(g.match("123456789012345678901234567890123"));
	ASSERT_TRUE(g.match("12345678901234567890123456789012"));
}

TEST(GuesserTest, shorthand_guess_with_mismatch)
{
	Guesser g("apple");
	ASSERT_FALSE(g.match("ax"));
	ASSERT_FALSE(g.match("apple"));
}

TEST(GuesserTest, special_characters_and_spaces)
{
	Guesser g("!@# $ %^&*()");
	ASSERT_TRUE(g.match("!@# $ %^&*()"));
}

TEST(GuesserTest, spaces_in_secret)
{
	Guesser g("hello world");
	ASSERT_TRUE(g.match("hello world"));
}

TEST(GuesserTest, spaces_mismatch)
{
	Guesser g("hello world");
	ASSERT_FALSE(g.match("helloworld"));
}
