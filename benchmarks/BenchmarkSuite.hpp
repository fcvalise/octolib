/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BenchmarkSuite.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 21:42:00 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/21 23:32:19 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCHMARKSUITE_HPP
# define BENCHMARKSUITE_HPP
# include <string>
# include <ostream>

# include "Benchmark.hpp"

class BenchmarkSuite
{
public:
	explicit BenchmarkSuite(std::string const& name);

	void	add(Benchmark&& benchmark);

	template <class ... A>
	void	emplace(A&& ... args)
	{
		m_benchmarks.emplace_back(std::forward<A>(args)...);
	}

	void	run(float beginFunctionRange, float endFunctionRange, unsigned int measureCount);

	template <class G>
	void	run(G&& gen, unsigned int measureCount)
	{
		for (auto& benchmark : m_benchmarks)
		{
			benchmark.run(gen, measureCount);
		}
	}

	void	displayResults(std::ostream& os)const;
private:
	std::vector<Benchmark>	m_benchmarks;
	std::string				m_name;
};

#endif
