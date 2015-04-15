/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryOutputStream.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 15:32:23 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/02 08:52:57 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

		void	write(char const* buffer, std::size_t size);
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
			write(reinterpret_cast<char const*>(&head), sizeof(H));
		}
	
	private:
		ByteArray&	m_bytes;
	};
}
