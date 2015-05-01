/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Benchmark.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 18:05:25 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/01 16:40:01 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Benchmark.hpp"
#include <algorithm>

Benchmark::Measure::Measure() :
	m_output(0.f)
{
}

Benchmark::Measure::Measure(float input, float output, Duration const& duration) :
	m_input(input),
	m_output(output),
	m_duration(duration)
{
}

float	Benchmark::Measure::input()const
{
	return (m_input);
}

Benchmark::Duration const&	Benchmark::Measure::duration()const
{
	return (m_duration);
}

float	Benchmark::Measure::deltaOutput(Measure const& other)const
{
	return (std::abs(m_output - other.m_output));
}

Benchmark::Benchmark(std::string const& name, RunFunction function) :
	m_name(name),
	m_function(function)
{
}

Benchmark::~Benchmark()
{
}

void	Benchmark::run(float functionRangeBegin, float functionRangeEnd, unsigned int measureCount)
{
	float		rangeStep = (functionRangeEnd - functionRangeBegin) / measureCount;
	float		functionInput = functionRangeBegin;
	float		functionOutput = 0.f;
	TimePoint	start;
	Duration	duration;

	m_measures.clear();
	m_measures.reserve(measureCount);
	for (std::size_t i = 0u; i < measureCount; ++i)
	{
		start = Clock::now();
		functionOutput = m_function(functionInput);
		duration = Clock::now() - start;
		m_measures.emplace_back(Measure(functionInput, functionOutput, duration));
		functionInput += rangeStep;
	}
	compileResults();
}

void	Benchmark::run(std::function<float()> gen, unsigned int measureCount)
{
	float		functionInput = 0.f;
	float		functionOutput = 0.f;
	TimePoint	start;
	Duration	duration;

	m_measures.clear();
	m_measures.reserve(measureCount);
	for (std::size_t i = 0u; i < measureCount; ++i)
	{
		functionInput = gen();
		start = Clock::now();
		functionOutput = m_function(functionInput);
		duration = Clock::now() - start;
		m_measures.emplace_back(Measure(functionInput, functionOutput, duration));
	}
	compileResults();
}

void	Benchmark::displayResults(std::ostream& os)const
{
	os << " *** " << m_name << ":\n"
	   << " - measures count: " << m_measures.size() << "\n"
	   << " - total: " << m_totalDuration.count() << " ns\n"
	   << " - average: " << m_totalDuration.count() / m_measures.size() << " ns \n"
	   << " - fastest: " << m_fastestMeasure.duration().count() << " ns [input: " << m_fastestMeasure.input() << "]\n"
	   << " - slowest: " << m_slowestMeasure.duration().count() << " ns [input: " << m_slowestMeasure.input() << "]" << std::endl;
}

void	Benchmark::compileResults()
{
	Duration	totalDuration = std::accumulate(m_measures.begin(), m_measures.end(), Duration(0u), &accumulateDuration);
	auto		minMaxDuration = std::minmax_element(m_measures.begin(), m_measures.end(), &compareDuration);

	m_totalDuration = totalDuration;
	m_averageDuration = totalDuration / m_measures.size();
	m_fastestMeasure = *minMaxDuration.first; 
	m_slowestMeasure = *minMaxDuration.second;
}

Benchmark::Duration	Benchmark::accumulateDuration(Duration const& init, Measure const& measure)
{
	return (init + measure.duration());
}

bool		Benchmark::compareDuration(Measure const& left, Measure const& right)
{
	return (left.duration() < right.duration());
}

