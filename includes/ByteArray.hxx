/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ByteArray.hxx                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 11:39:38 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/06 11:39:49 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	template <class I>
	ByteArray::ByteArray(I begin, I end) :
		ByteArray()
	{
		assign(begin, end);
	}

	template <class I>
	void ByteArray::assign(I begin, I end)
	{
		std::size_t	count = std::distance(begin, end);

		reserve(count);
		std::copy(begin, end, m_bytes.get());
		m_count = count;
	}

	template <class I>
	void 	ByteArray::append(I begin, I end)
	{
		std::size_t	count = std::distance(begin, end);

		if (m_count + count > m_capacity)
			reserve(m_count + count);
		std::copy(begin, end, this->end());
		m_count += count;
	}
}
