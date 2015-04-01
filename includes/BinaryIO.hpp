/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryIO.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 08:35:49 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/01 09:15:30 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYIO_HPP
# define BINARYIO_HPP
# include <iostream>

namespace octo
{

	template <class H>
	void	binaryWrite(std::ostream& os, H const& value) 
	{ 
		os.write(reinterpret_cast<char const*>(&value), sizeof(H));
	}

	template<class H, class ... T> 
	void	binaryWrite(std::ostream& os, H const& value, T const& ... tail)
	{ 
		binaryWrite(os, value);
		binaryWrite(os, tail...);
	}

	template<class H, class ... T> 
	bool	binaryRead(std::istream& is, H& value, T& ... tail) 
	{ 
		if (!is.read(reinterpret_cast<char*>(&value), sizeof(H)))
			return (false);
		return (binaryRead(is, tail...));
	}

	template <class H>
	bool	binaryRead(std::istream& is, H& value) 
	{
		is.read(reinterpret_cast<char*>(&value), sizeof(H));
		return (is.operator bool());
	}
}

#endif
