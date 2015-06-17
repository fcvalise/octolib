/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryInputStream.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 14:41:46 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/15 17:03:27 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYINPUTSTREAM_HPP
# define BINARYINPUTSTREAM_HPP
# include "ByteArray.hpp"

# include <string>

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

		void		readBytes(char* buffer, std::size_t size);
		void		readBytes(ByteArray& buffer, std::size_t size);

		template <class H, class ... T>
		void		read(H& value, T&... tails)
		{
			read(value);
			read(tails...);
		}

		template <class H>
		void		read(H& value)
		{
			readBytes(reinterpret_cast<char *>(&value), sizeof(H));
		}
	
		void		read(std::string& value)
		{
			std::uint32_t	size = 0u;
			
			read(size);
			value.resize(size);
			if (size > 0u)
				readBytes(&value.front(), size);
		}

		void		skip(std::size_t bytes);
		bool		isOk()const;
		bool		hasDataToRead()const;
		std::size_t	getPosition()const;
					operator bool()const;
	private:
		ByteArray const&			m_bytes;
		std::size_t					m_pos;
		bool						m_isOk;
	};
}

#endif
