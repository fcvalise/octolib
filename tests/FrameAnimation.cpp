/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FrameAnimation.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 20:53:36 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/11 00:33:23 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <iterator>

#include <FrameAnimation.hpp>

BOOST_AUTO_TEST_SUITE( frame_animation )

BOOST_AUTO_TEST_CASE( set_frames_test )
{
	typedef octo::FrameAnimation<int>::FrameList	FrameList;

	octo::FrameAnimation<int>	anim;
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
}

BOOST_AUTO_TEST_SUITE_END()
