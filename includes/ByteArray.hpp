/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ByteArray.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 10:05:51 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/01 11:34:14 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BYTEARRAY_HPP
# define BYTEARRAY_HPP
# include <memory>

namespace octo
{
	class ByteArray
	{
	public:
		typedef char*			iterator;
		typedef char const*		const_iterator;

		ByteArray();
		explicit ByteArray(std::size_t count);

		template <class I>
		ByteArray(I begin, I end) :
			ByteArray()
		{
			assign(begin, end);
		}
		
		template <class I>
		void assign(I begin, I end)
		{
			std::size_t	count = std::distance(begin, end);

			reserve(count);
			std::copy(begin, end, m_bytes.get());
			m_count = count;
		}

		void			resize(std::size_t count);
		void			clear();

		std::size_t		capacity()const;
		std::size_t		size()const;

		iterator		begin();
		iterator		end();
		const_iterator	begin()const;
		const_iterator	end()const;

		char			operator[](std::size_t i)const;
		char&			operator[](std::size_t i);

		char const*		bytes()const;

		/*!	Read \a count bytes from an input stream
		 *	Buffer is resized if needed.
		 */
		bool			read(std::istream& is, std::size_t count);

		/*!	Write buffer to an output stream */
		void			write(std::ostream& os)const;
	private:
		void			reserve(std::size_t count);
	private:
		std::unique_ptr<char[]>	m_bytes;
		std::size_t				m_capacity;
		std::size_t				m_count;
	};
}

#endif
