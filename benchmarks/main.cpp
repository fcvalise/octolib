/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 04:15:39 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/21 23:29:49 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Benchmark.hpp"
#include "BenchmarkSuite.hpp"
#include <Math.hpp>

#include <random>

static unsigned int const	MeasureCount = 200000;

int	main(int argc, char **argv)
{
	std::default_random_engine 				generator;
	std::uniform_real_distribution<float>	distribution(M_PI * -2.f, M_PI * 2.f);

	BenchmarkSuite	powSuite("pow");
	powSuite.emplace("stl pow 2", [](float x){return (std::pow(x, 2));});
	powSuite.emplace("octo pow 2", [](float x){return (octo::pow<2>(x));});
	powSuite.emplace("stl pow 3", [](float x){return (std::pow(x, 3));});
	powSuite.emplace("octo pow 3", [](float x){return (octo::pow<3>(x));});
	powSuite.emplace("stl pow 5", [](float x){return (std::pow(x, 5));});
	powSuite.emplace("octo pow 5", [](float x){return (octo::pow<5>(x));});

	BenchmarkSuite	cosSuite("cosinus");
	cosSuite.emplace("stl cos", [](float x){return (std::cos(x));});
	cosSuite.emplace("cos using taylor series order 30", [](float x){return (octo::cos<30>(x));});
	cosSuite.emplace("cos using taylor series order 15", [](float x){return (octo::cos<15>(x));});
	cosSuite.emplace("cos using taylor series order 7", [](float x){return (octo::cos<7>(x));});
	cosSuite.emplace("cos quadratic high precision approximation", [](float x){return (octo::cosHPA(x));});
	cosSuite.emplace("cos quadratic low precision approximation", [](float x){return (octo::cosLPA(x));});

	powSuite.run(std::bind(distribution, generator), MeasureCount);
	cosSuite.run(std::bind(distribution, generator), MeasureCount);

	powSuite.displayResults(std::cout);
	cosSuite.displayResults(std::cout);
	return (0);
	static_cast<void>(argc);
	static_cast<void>(argv);
}
