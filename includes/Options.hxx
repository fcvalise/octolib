/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Options.hxx                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 15:32:46 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/24 17:03:24 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrintSFML.hpp"

namespace octo
{
	template <class T>
	T	Options::getValue(std::string const& key)const
	{
		std::istringstream	iss;
		T					value;

		iss.flags(std::ios::boolalpha);
		iss.str(getValue<std::string>(key));
		value >> iss;
		return (value);
	}

	template <class T>
	T	Options::getValue(std::string const& key, T const& defaultValue)const
	{
		auto				it = m_values.find(key);
		T					value;

		if (it != m_values.end())
		{
			std::istringstream	iss;

			iss.flags(std::ios::boolalpha);
			iss.str(it->second);
			iss >> value;
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

		oss.str(value);
		oss.flags(std::ios::boolalpha);
		oss << value;
		m_values[key] = oss.str();
	}
}
