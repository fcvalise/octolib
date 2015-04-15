/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 02:35:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 12:26:06 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <StateManager.hpp>
#include <AbstractState.hpp>
#include <DefaultTransition.hpp>
#include <Application.hpp>
#include <GraphicsManager.hpp>
#include <Console.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "FireFlyTest.hpp"

int main(int argc, char **argv)
{
	using namespace octo;

	try
	{
		Application::initialize("Application works!", "default.conf", argc, argv);
		StateManager&							states = Application::getStateManager();
		FireFly									fireFly;

		states.registerState<FireFlyTest>("firefly");
		states.registerTransition<octo::BlackFadeTransition>("black_f");
		Application::run("firefly");
	}
	catch (std::exception const& e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
	Application::destroy();
	std::cout << "Goodbye!" << std::endl;
    return 0;
}
