/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bspcompiler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 10:10:56 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 01:04:37 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <Segment.hpp>
#include <BspCompiler.hpp>
#include <BspNode.hpp>
#include <BspTreeUtility.hpp>

BOOST_AUTO_TEST_SUITE( bspcompiler )

BOOST_AUTO_TEST_CASE( split_segment_0 )
{
	octo::BspCompiler::SegmentList	segments(
	{
		octo::Segment(1, 2, 3, 2),
		octo::Segment(2, 1, 2, 3)
	});
	octo::BspCompiler	compiler(octo::BspCompiler::HyperplanSelector::NoSelection, 0);
	octo::BspTree		t0 = compiler.run(segments);

	BOOST_CHECK_EQUAL(0, t0.root()->depth());
	BOOST_CHECK_EQUAL((t0.root()->hyperplan()), octo::Segment(1, 2, 3, 2));
	BOOST_CHECK_EQUAL(1, t0.root()->segments(octo::BspNode::SegmentCollection::Front).size());
	BOOST_CHECK_EQUAL(1, t0.root()->segments(octo::BspNode::SegmentCollection::Back).size());
	BOOST_CHECK_EQUAL(0, t0.root()->segments(octo::BspNode::SegmentCollection::Aligned).size());
	BOOST_CHECK_EQUAL(t0.root()->segments(octo::BspNode::SegmentCollection::Front).front(), octo::Segment(2, 2, 2, 3));
	BOOST_CHECK_EQUAL(t0.root()->segments(octo::BspNode::SegmentCollection::Back).front(), octo::Segment(2, 1, 2, 2));
}

BOOST_AUTO_TEST_CASE( split_segment_1 )
{
	octo::BspCompiler::SegmentList	segments(
	{
		octo::Segment(5, 1, 5, 3),
		octo::Segment(4, 5, 6, 5)
	});
	octo::BspCompiler	compiler(octo::BspCompiler::HyperplanSelector::NoSelection, 0);
	octo::BspTree		t0 = compiler.run(segments);

	BOOST_CHECK_EQUAL(0, t0.root()->depth());
	BOOST_REQUIRE_EQUAL((t0.root()->hyperplan()), octo::Segment(5, 1, 5, 3));
	BOOST_CHECK_EQUAL(1, t0.root()->segments(octo::BspNode::SegmentCollection::Front).size());
	BOOST_CHECK_EQUAL(1, t0.root()->segments(octo::BspNode::SegmentCollection::Back).size());
	BOOST_CHECK_EQUAL(0, t0.root()->segments(octo::BspNode::SegmentCollection::Aligned).size());
	BOOST_CHECK_EQUAL(t0.root()->segments(octo::BspNode::SegmentCollection::Front).front(), octo::Segment(4, 5, 5, 5));
	BOOST_CHECK_EQUAL(t0.root()->segments(octo::BspNode::SegmentCollection::Back).front(), octo::Segment(5, 5, 6, 5));
}

BOOST_AUTO_TEST_CASE( no_selection_0 )
{
	octo::BspCompiler::SegmentList	segments(
	{
		octo::Segment(1, 1, 2, 2),
		octo::Segment(2, 2, 3, 3),
		octo::Segment(2, 7, 7, 2),
		octo::Segment(6, 6, 7, 7)
	});

	octo::BspCompiler	compiler(octo::BspCompiler::HyperplanSelector::NoSelection, 0);
	octo::BspTree		t0 = compiler.run(segments);

	BOOST_CHECK_EQUAL(0, t0.root()->depth());
	BOOST_CHECK_EQUAL((t0.root()->hyperplan()), octo::Segment(1, 1, 2, 2));
	BOOST_CHECK_EQUAL(1, t0.root()->segments(octo::BspNode::SegmentCollection::Front).size());
	BOOST_CHECK_EQUAL(1, t0.root()->segments(octo::BspNode::SegmentCollection::Back).size());
	BOOST_CHECK_EQUAL(2, t0.root()->segments(octo::BspNode::SegmentCollection::Aligned).size());
}

BOOST_AUTO_TEST_CASE( minimum_cuts_0 )
{
	octo::BspCompiler::SegmentList	segments(
	{
		octo::Segment(1, 1, 2, 2),
		octo::Segment(2, 2, 3, 3),
		octo::Segment(2, 7, 7, 2),
		octo::Segment(6, 6, 7, 7)
	});

	octo::BspCompiler	compiler(octo::BspCompiler::HyperplanSelector::MinimumCuts, 0);
	octo::BspTree		t0 = compiler.run(segments);

	BOOST_CHECK_EQUAL(0, t0.root()->depth());
	BOOST_CHECK_EQUAL((t0.root()->hyperplan()), octo::Segment(2, 7, 7, 2));
	BOOST_CHECK_EQUAL(1, t0.root()->segments(octo::BspNode::SegmentCollection::Front).size());
	BOOST_CHECK_EQUAL(2, t0.root()->segments(octo::BspNode::SegmentCollection::Back).size());
	BOOST_CHECK_EQUAL(0, t0.root()->segments(octo::BspNode::SegmentCollection::Aligned).size());
}

BOOST_AUTO_TEST_CASE( minimum_cuts_and_max )
{
	octo::BspCompiler::SegmentList	segments(
	{
		octo::Segment(1, 1, 2, 2),
		octo::Segment(2, 2, 3, 3),
		octo::Segment(2, 7, 7, 2),
		octo::Segment(6, 6, 7, 7),
		octo::Segment(7, 6, 8, 7)
	});

	octo::BspCompiler	compiler(octo::BspCompiler::HyperplanSelector::MinimumCuts, 1);
	octo::BspTree		t0 = compiler.run(segments);
	octo::BspNode*	root = t0.root();
	octo::BspNode*	d = root->front();
	octo::BspNode*	a = root->back();

	BOOST_CHECK_EQUAL(1, t0.root()->depth());
	BOOST_CHECK_EQUAL((t0.root()->hyperplan()), octo::Segment(2, 7, 7, 2));
	BOOST_CHECK_EQUAL(0, t0.root()->segments(octo::BspNode::SegmentCollection::Front).size());
	BOOST_CHECK_EQUAL(0, t0.root()->segments(octo::BspNode::SegmentCollection::Back).size());
	BOOST_CHECK_EQUAL(0, t0.root()->segments(octo::BspNode::SegmentCollection::Aligned).size());
	BOOST_CHECK(d != nullptr);
	BOOST_CHECK(a != nullptr);
	BOOST_CHECK_EQUAL(d->hyperplan(), octo::Segment(6, 6, 7, 7));
	BOOST_CHECK_EQUAL(a->hyperplan(), octo::Segment(1, 1, 2, 2));
	BOOST_CHECK_EQUAL(0, (d->segments(octo::BspNode::SegmentCollection::Front).size()));
	BOOST_CHECK_EQUAL(1, (d->segments(octo::BspNode::SegmentCollection::Back).size()));
	BOOST_CHECK_EQUAL(0, (d->segments(octo::BspNode::SegmentCollection::Aligned).size()));
	BOOST_CHECK_EQUAL(0, (a->segments(octo::BspNode::SegmentCollection::Front).size()));
	BOOST_CHECK_EQUAL(0, (a->segments(octo::BspNode::SegmentCollection::Back).size()));
	BOOST_CHECK_EQUAL(1, (a->segments(octo::BspNode::SegmentCollection::Aligned).size()));
}

BOOST_AUTO_TEST_SUITE_END()
