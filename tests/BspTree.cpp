/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsptree.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 10:36:15 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 05:44:10 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <Segment.hpp>
#include <BspTree.hpp>
#include <BspNode.hpp>
#include <BspCompiler.hpp>
#include <ByteArray.hpp>
#include <BinaryInputStream.hpp>
#include <BinaryOutputStream.hpp>

#include <sstream>
#include <list>

BOOST_AUTO_TEST_SUITE( bsptree )

std::list<octo::Segment> listHyperplans(octo::BspTree const& tree)
{
	std::list<octo::Segment>	results;

	tree.forEach<octo::BspTree::VisitorMode::Infix>([&results](octo::BspNode const* node)
	{
		if (node)
			results.push_back(node->hyperplan());
	});
	return (results);
}

BOOST_AUTO_TEST_CASE( io )
{
	octo::BspNode*				n0 = new octo::BspNode(octo::Segment(0, 1, 1, 0));	
	octo::BspNode*				n1 = new octo::BspNode(octo::Segment(2, 3, 3, 2));	
	octo::BspNode*				n2 = new octo::BspNode(octo::Segment(4, 5, 5, 4));	
	octo::BspNode*				n3 = new octo::BspNode(octo::Segment(6, 7, 7, 6));	
	octo::BspNode*				n4 = new octo::BspNode(octo::Segment(8, 9, 9, 8));	
	octo::BspNode*				n5 = new octo::BspNode(octo::Segment(10, 11, 11, 10));	
	octo::BspTree				tree;
	octo::BspTree				loaded;
	std::istringstream			is;
	std::ostringstream			os;
	std::list<octo::Segment>	hyperplans;
	std::list<octo::Segment>	loadedHyperplans;

	n0->setFrontNode(n1);
	n0->setBackNode(n2);
	n1->setFrontNode(n3);
	n2->setBackNode(n4);
	n4->setFrontNode(n5);
	tree.reset(n0);
	tree.write(os);
	is.str(os.str());
	loaded.read(is);
	hyperplans = listHyperplans(tree);
	loadedHyperplans = listHyperplans(loaded);
	BOOST_CHECK_EQUAL_COLLECTIONS(hyperplans.begin(), hyperplans.end(),
								 loadedHyperplans.begin(), loadedHyperplans.end());
}

BOOST_AUTO_TEST_CASE( binary_io )
{
	octo::BspNode*				n0 = new octo::BspNode(octo::Segment(0, 1, 1, 0));	
	octo::BspNode*				n1 = new octo::BspNode(octo::Segment(2, 3, 3, 2));	
	octo::BspNode*				n2 = new octo::BspNode(octo::Segment(4, 5, 5, 4));	
	octo::BspNode*				n3 = new octo::BspNode(octo::Segment(6, 7, 7, 6));	
	octo::BspNode*				n4 = new octo::BspNode(octo::Segment(8, 9, 9, 8));	
	octo::BspNode*				n5 = new octo::BspNode(octo::Segment(10, 11, 11, 10));	
	octo::BspTree				tree;
	octo::BspTree				loaded;
	octo::ByteArray				buffer;
	octo::BinaryOutputStream	os(buffer);
	octo::BinaryInputStream		is(buffer);

	std::list<octo::Segment>	hyperplans;
	std::list<octo::Segment>	loadedHyperplans;

	n0->setFrontNode(n1);
	n0->setBackNode(n2);
	n1->setFrontNode(n3);
	n2->setBackNode(n4);
	n4->setFrontNode(n5);
	tree.reset(n0);
	tree.writeToMemory(os);
	loaded.readFromMemory(is);
	hyperplans = listHyperplans(tree);
	loadedHyperplans = listHyperplans(loaded);
	BOOST_CHECK_EQUAL_COLLECTIONS(hyperplans.begin(), hyperplans.end(),
								 loadedHyperplans.begin(), loadedHyperplans.end());
}

BOOST_AUTO_TEST_CASE( at )
{
	octo::BspCompiler::SegmentList	segments(
	{
		octo::Segment(1, 1, 2, 2),
		octo::Segment(2, 2, 3, 3),
		octo::Segment(2, 7, 7, 2),
		octo::Segment(6, 6, 7, 7),
		octo::Segment(7, 6, 8, 7)
	});

	octo::BspCompiler					compiler(octo::BspCompiler::HyperplanSelector::MinimumCuts, 1);
	octo::BspTree						t0 = compiler.run(segments);
	octo::BspNode const*				n0 = t0.root()->back(); 	// pos = 1;3: b -> f
	octo::BspNode	const*				n1 = t0.root()->back();  	// pos = 1;2: b -> b
	octo::BspNode const*				n2 = t0.root()->front();	// pos = 7;5: f -> b
	octo::BspNode const*				n3 = t0.root()->front();	// pos = 5;7: f -> f
	
	BOOST_CHECK_EQUAL(t0.nodeAt(sf::Vector2f(1, 3)), n0);
	BOOST_CHECK_EQUAL(t0.nodeAt(sf::Vector2f(1, 2)), n1);
	BOOST_CHECK_EQUAL(t0.nodeAt(sf::Vector2f(7, 5)), n2);
	BOOST_CHECK_EQUAL(t0.nodeAt(sf::Vector2f(5, 7)), n3);
}

BOOST_AUTO_TEST_SUITE_END()
