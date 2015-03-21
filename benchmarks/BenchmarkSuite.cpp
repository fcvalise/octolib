/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BenchmarkSuite.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 21:42:15 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/21 23:32:25 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BenchmarkSuite.hpp"

BenchmarkSuite::BenchmarkSuite(std::string const& name) :
	m_name(name)
{
}

void	BenchmarkSuite::add(Benchmark&& benchmark)
{
	m_benchmarks.emplace_back(std::forward<Benchmark>(benchmark));
}

void	BenchmarkSuite::run(float beginFunctionRange, float endFunctionRange, unsigned int measureCount)
{
	for (auto& benchmark : m_benchmarks)
	{
		benchmark.run(beginFunctionRange, endFunctionRange, measureCount);
	}
}

void	BenchmarkSuite::displayResults(std::ostream& os)const
{
	os << "==================================================\n" 
	   << " Suite " << m_name << "\n"
	   << "==================================================\n";
	for (auto const& benchmark : m_benchmarks)
	{
		benchmark.displayResults(os);
	}
}
