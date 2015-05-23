/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FrameAnimation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 20:53:36 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/23 14:21:31 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <iterator>

#include <AbstractFrameAnimation.hpp>

BOOST_AUTO_TEST_SUITE( frame_animation )

class FrameAnimationTest : public octo::AbstractFrameAnimation<int>
{
public:
	virtual bool		loadFromMemory(octo::ByteBuffer const&)
	{
		return (false);
	}
};

BOOST_AUTO_TEST_CASE( set_frames_test0 )
{
	typedef FrameAnimationTest::FrameList	FrameList;

	FrameAnimationTest			anim;
	FrameList					frames;
	
	frames.emplace_back(sf::seconds(1), 0);
	frames.emplace_back(sf::seconds(2), 1);
	frames.emplace_back(sf::seconds(3), 2);
	anim.setFrames(frames);
	BOOST_CHECK_EQUAL( anim.getFrameDuration(0).asMilliseconds(), 1000 );
	BOOST_CHECK_EQUAL( anim.getFrameDuration(1).asMilliseconds(), 2000 );
	BOOST_CHECK_EQUAL( anim.getFrameDuration(2).asMilliseconds(), 3000 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(0)), 0 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(999)), 0 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(1000)), 1 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(2999)), 1 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(3000)), 2 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(5999)), 2 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(6000)), 2 );
}

BOOST_AUTO_TEST_CASE( set_frames_test1 )
{
	typedef FrameAnimationTest::FrameList	FrameList;

	FrameAnimationTest			anim;
	FrameList					frames;
	
	frames.emplace_back(sf::seconds(1), 0);
	frames.emplace_back(sf::seconds(2), 1);
	frames.emplace_back(sf::seconds(3), 2);
	frames.emplace_back(sf::seconds(4), 3);
	anim.setFrames(frames);
	BOOST_CHECK_EQUAL( anim.getFrameDuration(0).asMilliseconds(), 1000 );
	BOOST_CHECK_EQUAL( anim.getFrameDuration(1).asMilliseconds(), 2000 );
	BOOST_CHECK_EQUAL( anim.getFrameDuration(2).asMilliseconds(), 3000 );
	BOOST_CHECK_EQUAL( anim.getFrameDuration(3).asMilliseconds(), 4000 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(0)), 0 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(999)), 0 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(1000)), 1 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(2999)), 1 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(3000)), 2 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(5999)), 2 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(6000)), 3 );
	BOOST_CHECK_EQUAL( anim.value(sf::milliseconds(9999)), 3 );
}

BOOST_AUTO_TEST_SUITE_END()
