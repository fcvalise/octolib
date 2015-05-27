/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexicalTree.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/27 03:42:11 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 05:53:08 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <iterator>

#include <LexicalTree.hpp>

BOOST_AUTO_TEST_SUITE( lexical_tree )

BOOST_AUTO_TEST_CASE( get_words_tests0 )
{
	octo::LexicalTree<char, int, -1, 0>	tree;
	std::vector<std::string>			result;
	std::vector<std::string> 			expected
	{
		"a",
		"aa",
		"ab",
		"aba",
		"abab",
		"abc",
		"abcd",
		"b",
		"bc",
		"bcd"	
	};

	for (auto str : expected)
	{
		tree.addWord(str, 1);
	}
	tree.getWords(result);
	std::sort(expected.begin(), expected.end());
	std::sort(result.begin(), result.end());
	BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected.begin(), expected.end() );
}

BOOST_AUTO_TEST_CASE( get_words_tests1 )
{
	octo::LexicalTree<char, int, -1, 0>	tree;
	std::vector<std::string>			result;
	std::vector<std::string> 			expected
	{
		"a",
		"aa",
		"ab",
		"abab",
		"abc",
		"abcd",
		"b",
		"bc",
		"bcd"	
	};

	for (auto str : expected)
	{
		tree.addWord(str, 1);
	}
	tree.getWords(result);
	std::sort(expected.begin(), expected.end());
	std::sort(result.begin(), result.end());
	BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected.begin(), expected.end() );
}

BOOST_AUTO_TEST_CASE( get_words_tests2 )
{
	octo::LexicalTree<char, int, -1, 0>	tree;
	std::vector<std::string>			result;
	std::vector<std::string> 			expected
	{
		"a",
		"aa",
		"ab",
		"abab",
		"abababa"
		"abc",
		"abcc",
		"abcd",
		"b",
		"bc",
		"bcd"	
	};

	for (auto str : expected)
	{
		tree.addWord(str, 1);
	}
	tree.getWords(result);
	std::sort(expected.begin(), expected.end());
	std::sort(result.begin(), result.end());
	BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected.begin(), expected.end() );
}

BOOST_AUTO_TEST_CASE( complete_words_tests )
{
	octo::LexicalTree<char, int, -1, 0>	tree;
	std::vector<std::string> 			words
	{
		"a",
		"ab",
		"abc",
		"abcd",
		"b",
		"bc",
		"bcd"	
	};
	std::vector<std::string>			expected_a =
	{
		"b",
		"bc",
		"bcd"
	};
	std::vector<std::string>			result;

	for (auto str : words)
	{
		tree.addWord(str, 1);
	}
	tree.completeWord("a", result);
	std::sort(expected_a.begin(), expected_a.end());
	std::sort(result.begin(), result.end());
	BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_a.begin(), expected_a.end() );
}

BOOST_AUTO_TEST_CASE( complete_words_tests2 )
{
	octo::LexicalTree<char, int, -1, 0>	tree;
	std::vector<std::string> 			words
	{
		"a",
		"aa",
		"ab",
		"abab",
		"abc",
		"abcd",
		"b",
		"bc",
		"bcd"	
	};
	std::vector<std::string>			expected_a =
	{
		"a",
		"b",
		"bab",
		"bc",
		"bcd"
	};
	std::vector<std::string>			expected_ab =
	{
		"ab",
		"c",
		"cd"
	};
	std::vector<std::string>			expected_b =
	{
		"c",
		"cd"
	};
	std::vector<std::string>			expected_c =
	{
	};
	std::vector<std::string>			result;

	for (auto str : words)
	{
		tree.addWord(str, 1);
	}
	std::sort(expected_a.begin(), expected_a.end());
	std::sort(expected_ab.begin(), expected_ab.end());
	std::sort(expected_b.begin(), expected_b.end());
	std::sort(expected_c.begin(), expected_c.end());
	tree.completeWord("a", result);
	std::sort(result.begin(), result.end());
	BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_a.begin(), expected_a.end() );
	result.clear();
	tree.completeWord("ab", result);
	std::sort(result.begin(), result.end());
	BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_ab.begin(), expected_ab.end() );
	result.clear();
	tree.completeWord("b", result);
	std::sort(result.begin(), result.end());
	BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_b.begin(), expected_b.end() );
	result.clear();
	tree.completeWord("c", result);
	std::sort(result.begin(), result.end());
	BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_c.begin(), expected_c.end() );
}

BOOST_AUTO_TEST_CASE( complete_words_tests3 )
{
	octo::LexicalTree<char, int, -1, 0>	tree;
	std::vector<std::string> 			words
	{
		"a",
		"ab",
		"abc",
		"abcd",
		"b",
		"bc",
		"bcd"	
	};
	std::vector<std::string>			expected_a =
	{
		"c",
		"cd"
	};
	std::vector<std::string>			result;

	for (auto str : words)
	{
		tree.addWord(str, 1);
	}
	tree.completeWord("b", result);
	std::sort(expected_a.begin(), expected_a.end());
	std::sort(result.begin(), result.end());
	BOOST_CHECK_EQUAL_COLLECTIONS( result.begin(), result.end(), expected_a.begin(), expected_a.end() );
}
BOOST_AUTO_TEST_SUITE_END()
