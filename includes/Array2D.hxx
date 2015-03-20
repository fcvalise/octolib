/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array2D.hxx                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 20:30:33 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/20 22:26:25 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>

namespace octo
{
	template <class T>
	inline std::size_t	Array2D<T>::index2dToIndex1D(std::size_t column, std::size_t row)const
	{
		return (column + (row * m_columns));
	}

	template <class T>
	Array2D<T>::Array2D() :
		m_values(nullptr),
		m_columns(0u),
		m_rows(0u),
		m_count(0u)
	{
	}

	template <class T>
	Array2D<T>::Array2D(std::size_t columns, std::size_t rows) :
		m_values(new T[columns * rows]),
		m_columns(columns),
		m_rows(rows),
		m_count(columns * rows)
	{
	}

	template <class T>
	Array2D<T>::Array2D(std::size_t columns, std::size_t rows, T defaultValue) :
		Array2D<T>(columns, rows)
	{
		std::fill(begin(), end(), defaultValue);
	}

	template <class T>
	Array2D<T>::Array2D(Array2D<T>&& other) :
		m_values(std::move(other.m_values)),
		m_columns(other.m_columns),
		m_rows(other.m_rows),
		m_count(other.m_count)
	{
		other.m_columns = 0u;
		other.m_rows = 0u;
		other.m_count = 0u;
	}

	template <class T>
	Array2D<T>&	Array2D<T>::operator = (Array2D<T>&& other)
	{
		m_values = std::move(other.m_values);
		m_columns = other.m_columns;
		m_rows = other.m_rows;
		m_count = other.m_count;
		other.m_columns = 0u;
		other.m_rows = 0u;
		other.m_count = 0u;
		return (*this);
	}

	template <class T>
	void	Array2D<T>::resize(std::size_t columns, std::size_t rows)
	{
		std::size_t	count = columns * rows;

		if (count > m_count)
			m_values.reset(new T[count]);
		m_columns = columns;
		m_rows = rows;
		m_count = count;
	}

	template <class T>
	void	Array2D<T>::resize(std::size_t columns, std::size_t rows, T defaultValue)
	{
		resize(columns, rows);
		std::fill(begin(), end(), defaultValue);
	}

	template <class T>
	T&	Array2D<T>::get(std::size_t column, std::size_t row)
	{
		return (m_values[index2dToIndex1D(column, row)]);
	}

	template <class T>
	T const&	Array2D<T>::get(std::size_t column, std::size_t row)const
	{
		return (m_values[index2dToIndex1D(column, row)]);
	}

	template <class T>
	void		Array2D<T>::set(std::size_t column, std::size_t row, T const& value)
	{
		m_values[index2dToIndex1D(column, row)] = value;
	}

	template <class T>
	std::size_t	Array2D<T>::columns()const
	{
		return (m_columns);
	}

	template <class T>
	std::size_t	Array2D<T>::rows()const
	{
		return (m_rows);
	}

	template <class T>
	std::size_t	Array2D<T>::count()const
	{
		return (m_count);
	}

	template <class T>
	bool	Array2D<T>::isNull()const
	{
		return (m_values == nullptr);
	}

	template <class T>
	T&			Array2D<T>::operator()(std::size_t colum,  std::size_t row)
	{
		return (get(colum, row));
	}

	template <class T>
	T const&	Array2D<T>::operator()(std::size_t colum,  std::size_t row)const
	{
		return (get(colum, row));
	}

	template <class T>
	typename Array2D<T>::iterator	Array2D<T>::begin()
	{
		return (m_values.get());
	}

	template <class T>
	typename Array2D<T>::iterator	Array2D<T>::end()
	{
		return (m_values.get() + m_count);
	}

	template <class T>
	typename Array2D<T>::const_iterator	Array2D<T>::begin()const
	{
		return (m_values.get());
	}

	template <class T>
	typename Array2D<T>::const_iterator	Array2D<T>::end()const
	{
		return (m_values.get() + m_count);
	}
}
