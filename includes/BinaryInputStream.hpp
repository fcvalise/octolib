/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryInputStream.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 14:41:46 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/02 07:52:36 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYINPUTSTREAM_HPP
# define BINARYINPUTSTREAM_HPP
# include "ByteArray.hpp"

namespace octo
{
	/*!	\ingroup Core
	 *	\brief Helper whose help to reading values from a byte array
	 *
	 */
	class BinaryInputStream
	{
	public:
		explicit BinaryInputStream(ByteArray const& bytes);

		template <class H, class ... T>
		void	read(H& value, T&... tails)
		{
			read(value);
			read(tails...);
		}

		template <class H>
		void	read(H& value)
		{
			read(reinterpret_cast<char *>(&value), sizeof(H));
		}

		bool	isOk()const;
		bool	hasDataToRead()const;
				operator bool()const;
	private:
		void	read(char* buffer, std::size_t size);
	private:
		ByteArray const&			m_bytes;
		ByteArray::const_iterator	m_it;
		bool						m_isOk;
	};
}

#endif
