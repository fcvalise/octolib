/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Options.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 03:03:00 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/14 04:50:01 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <Options.hpp>

BOOST_AUTO_TEST_SUITE( options )

BOOST_AUTO_TEST_CASE( simple_test )
{
	octo::Options	opt;

	opt.setValue("boolean", true);
	opt.setValue("integer", 6565);
	opt.setValue("float", 3.14159f);
	opt.setValue("videomode", sf::VideoMode(800, 600, 32));
	opt.setValue("vector2u", sf::Vector2u(1, 2));
	opt.setValue("vector3f", sf::Vector3f(11.22f, 22.33f, 33.44f));
	opt.setValue("color", sf::Color(50, 60, 70, 80));
	opt.setValue("string", "youloulou krr krr krr .,$$3qwr");

	BOOST_CHECK( opt.getValue<bool>("boolean") == true );
	BOOST_CHECK( opt.getValue<int>("integer") == 6565 );
	BOOST_CHECK( opt.getValue<float>("float") == 3.14159f );
	BOOST_CHECK( opt.getValue<sf::Vector2u>("vector2u") == sf::Vector2u(1, 2) );
	BOOST_CHECK( opt.getValue<sf::Vector3f>("vector3f") == sf::Vector3f(11.22f, 22.33f, 33.44f) );
	BOOST_CHECK( opt.getValue<sf::VideoMode>("videomode") == sf::VideoMode(800, 600, 32) );
	BOOST_CHECK( opt.getValue<sf::Color>("color") == sf::Color(50, 60, 70, 80) );
	BOOST_CHECK_EQUAL( opt.getValue<std::string>("string"), "youloulou krr krr krr .,$$3qwr" );
}

BOOST_AUTO_TEST_SUITE_END()
