/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Benchmark.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 18:02:32 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/21 18:55:01 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCHMARK_HPP
# define BENCHMARK_HPP
# include <chrono>
# include <iostream>
# include <string>
# include <vector>
# include <cmath>
# include <numeric>


class Benchmark
{
	typedef std::chrono::high_resolution_clock	Clock;
	typedef typename Clock::duration			Duration;
	typedef typename Clock::time_point			TimePoint;

	class Measure
	{
	public:
		Measure();
		Measure(float input, float output, Duration const& duration);

		Measure(Measure const& other) = default;
		Measure(Measure&& other) = default;
		Measure&	operator = (Measure const& other) = default;
		Measure&	operator = (Measure&& other) = default;

		float			input()const;
		Duration const&	duration()const;
		float			deltaOutput(Measure const& other)const;
	private:
		float		m_input;
		float		m_output;
		Duration	m_duration;
	};
public:
	Benchmark(std::string const& name, std::size_t measureCount);
	~Benchmark();

	void			runFunction(float functionRangeBegin, float functionRangeEnd, std::function<float(float)> func);
	void			displayResults(std::ostream& os)const;
private:
	void			compileResults();
	static Duration	accumulateDuration(Duration const& init, Measure const& measure);
	static bool		compareDuration(Measure const& left, Measure const& right);
private:
	std::vector<Measure>	m_measures;
	std::string				m_name;
	TimePoint				m_start;
	std::size_t				m_measureCount;
	Duration				m_totalDuration;
	Duration				m_averageDuration;
	Measure					m_fastestMeasure;
	Measure					m_slowestMeasure;
};

#endif
