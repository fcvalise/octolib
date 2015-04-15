/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Options.hxx                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 15:32:46 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/14 03:56:23 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrintSFML.hpp"
#include <cassert>
#include <sstream>

namespace octo
{
	template <class T>
	T	Options::getValue(std::string const& key)const
	{
		std::istringstream	iss;
		auto				it = m_values.find(key);
		T					value;

		if (it != m_values.end())
		{
			iss.flags(std::ios::boolalpha);
			iss.str(it->second);
			iss >> value;
			if (iss.fail() || iss.bad())
				throw Options::InvalidTypeException(key);
		}
		else
		{
			throw std::range_error("options: invalid key: " + key);
		}
		return (value);
	}

	template <class T>
	T	Options::getValue(std::string const& key, T const& defaultValue)const
	{
		std::istringstream	iss;
		auto				it = m_values.find(key);
		T					value;

		if (it != m_values.end())
		{
			iss.flags(std::ios::boolalpha);
			iss.str(it->second);
			iss >> value;
			if (iss.fail() || iss.bad())
				throw Options::InvalidTypeException(key);
		}
		else
		{
			value = defaultValue;
		}
		return (value);
	}
	
	template <class T>
	void	Options::setValue(std::string const& key, T const& value)
	{
		std::ostringstream	oss;

		oss.flags(std::ios::boolalpha);
		oss << value;
		m_values[key] = oss.str();
	}
}
