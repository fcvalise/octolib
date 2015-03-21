/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 04:15:39 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/21 20:39:57 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Benchmark.hpp"
#include <Math.hpp>

static unsigned int const	MeasureCount = 200000;

int	main(int argc, char **argv)
{
	Benchmark	stlCos("stl cos", MeasureCount);
	Benchmark	octoTaylorCos30("cos using taylor series order 30", MeasureCount);
	Benchmark	octoTaylorCos15("cos using taylor series order 15", MeasureCount);
	Benchmark	octoTaylorCos7("cos using taylor series order 7", MeasureCount);

	stlCos.runFunction(M_PI * -2.f, M_PI * 2.f, [](float x){return (std::cos(x));});
	octoTaylorCos30.runFunction(M_PI * -2.f, M_PI * 2.f, [](float x){return (octo::cos<30>(x));});
	octoTaylorCos15.runFunction(M_PI * -2.f, M_PI * 2.f, [](float x){return (octo::cos<15>(x));});
	octoTaylorCos7.runFunction(M_PI * -2.f, M_PI * 2.f, [](float x){return (octo::cos<7>(x));});

	stlCos.displayResults(std::cout);
	octoTaylorCos30.displayResults(std::cout);
	octoTaylorCos15.displayResults(std::cout);
	octoTaylorCos7.displayResults(std::cout);
	return (0);
	static_cast<void>(argc);
	static_cast<void>(argv);
}
