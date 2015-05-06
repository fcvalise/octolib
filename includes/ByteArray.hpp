/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ByteArray.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 10:05:51 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/06 11:39:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BYTEARRAY_HPP
# define BYTEARRAY_HPP
# include <memory>
# include <algorithm>
# include <initializer_list>

namespace octo
{
	/*!	\ingroup Core
	 *	\class ByteArray
	 *	\brief Array of bytes
	 *
	 *	This container is designed to reduce the count of
	 *	reallocation.
	 */
	class ByteArray
	{
	public:
		typedef char*			iterator;
		typedef char const*		const_iterator;

		/*!	Create an empty array with no memory allocated */
		ByteArray();

		/*!	Create an empty array with \a count bytes allocated */
		explicit ByteArray(std::size_t count);

		/*!	Create an array from bytes */
		explicit ByteArray(std::initializer_list<char> bytes);

		/*!	Create an array from a byte array */
		ByteArray(char const* str, std::size_t size);

		/*!	Create an array from an other bytes container */
		template <class I>
		ByteArray(I begin, I end);
		
		/*!	Copy bytes from an other bytes container */
		void			assign(ByteArray const& bytes);

		/*!	Copy bytes from a list initializer */
		void			assign(std::initializer_list<char> bytes);

		/*!	Copy bytes from a bytes array */
		void			assign(char const* str, std::size_t size);

		/*!	Copy bytes from an other bytes container */
		template <class I>
		void			assign(I begin, I end);

		/*!	Appends bytes at the end */
		void			append(ByteArray const& bytes);

		/*!	Appends bytes at the end */
		void			append(std::initializer_list<char> bytes);

		/*!	Appends bytes from a bytes array */
		void			append(char const* str, std::size_t size);

		/*!	Appends a range of bytes at the end */
		template <class I>
		void 			append(I begin, I end);

		/*!	Reallocate the internal array
		 *
		 *	Datas stored are preserved but truncated if \a count > count()
		 */
		void			reserve(std::size_t count);

		/*!	Resize the array
		 *
		 *	Re allocation is done only if count is greater than
		 *	the capacity of the internal buffer.
		 */
		void			resize(std::size_t count);

		/*!	Clear the array.
		 *	After the size of the array will be null.
		 */
		void			clear();

		/*!	Read \a count bytes from an input stream
		 *	Buffer is resized if needed.
		 */
		bool			read(std::istream& is, std::size_t count);

		/*!	Read all bytes availables from a stream */
		bool			read(std::istream& is);

		/*!	Write buffer to an output stream */
		void			write(std::ostream& os)const;

		/*!	Constant access to a byte */
		char			operator[](std::size_t i)const;
		/*!	Access to a byte */
		char&			operator[](std::size_t i);

		/*!	Pointer on the first byte of the array */
		char const*		bytes()const;

		/*!	Number of bytes used in this array */
		std::size_t		size()const;

		/*!	Number of bytes allocated by the internal array */
		std::size_t		capacity()const;

		/*!	Return true if the size is equal to 0 */
		bool			empty()const;

		/*!	Iterator on the first byte */
		iterator		begin();
		/*!	Iterator on the end of the container */
		iterator		end();
		/*!	Iterator on the first byte */
		const_iterator	begin()const;
		/*!	Iterator on the end of the container */
		const_iterator	end()const;
	private:
		std::unique_ptr<char[]>	m_bytes;
		std::size_t				m_capacity;
		std::size_t				m_count;
	};
}

#include "ByteArray.hxx"
#endif
