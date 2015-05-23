/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryOutputStream.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 15:32:23 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/24 18:54:10 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYOUTPUTSTREAM_HPP
# define BINARYOUTPUTSTREAM_HPP
# include "ByteArray.hpp"
# include "details/Meta.hpp"

namespace octo
{
	class BinaryOutputStream
	{
	public:
		explicit BinaryOutputStream(ByteArray& bytes);
	
		template <class ... T>
		void	write(T const&...values)
		{
			std::size_t	byteCount = details::totalSizeOf<T...>();

			m_bytes.reserve(m_bytes.size() + byteCount);
			writeImp<T...>(values...);
		}

		void	writeBytes(char const* buffer, std::size_t size);
		void	writeBytes(ByteArray const& buffer);
	private:
		template <class H, class ... T>
		void	writeImp(H const& head, T const&...tails)
		{
			writeImp(head);
			writeImp(tails...);	
		}

		template <class H>
		void	writeImp(H const& head)
		{
			writeBytes(reinterpret_cast<char const*>(&head), sizeof(H));
		}
	private:
		ByteArray&	m_bytes;
	};
}

#endif
