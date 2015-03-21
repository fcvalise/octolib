/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Benchmark.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 18:02:32 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/21 23:31:05 by irabeson         ###   ########.fr       */
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
	typedef std::function<float(float)>	RunFunction;

	Benchmark(std::string const& name, RunFunction function);
	Benchmark(Benchmark const&) = delete;
	Benchmark& operator = (Benchmark const&) = delete;
	Benchmark(Benchmark&&) = default;
	Benchmark& operator = (Benchmark&&) = default;
	~Benchmark();

	void			run(float functionRangeBegin, float functionRangeEnd, unsigned int measureCount);
	void			run(std::function<float()> gen, unsigned int measureCount);
	void			displayResults(std::ostream& os)const;
private:
	void			compileResults();
	static Duration	accumulateDuration(Duration const& init, Measure const& measure);
	static bool		compareDuration(Measure const& left, Measure const& right);
private:
	std::vector<Measure>	m_measures;
	std::string				m_name;
	TimePoint				m_start;
	RunFunction				m_function;
	Duration				m_totalDuration;
	Duration				m_averageDuration;
	Measure					m_fastestMeasure;
	Measure					m_slowestMeasure;
};

#endif
