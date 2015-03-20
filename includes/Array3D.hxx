/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array3D.hxx                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 18:00:45 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/20 22:24:06 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>

namespace octo
{
	template <class T>
	std::size_t	Array3D<T>::index3dToIndex1D(std::size_t column, std::size_t row, std::size_t depth)const
	{
		return (column + (row * m_columns) + (depth * m_columns * m_depth));
	}

	template <class T>
	Array3D<T>::Array3D() :
		m_values(nullptr),
		m_columns(0u),
		m_rows(0u),
		m_depth(0u),
		m_count(0u)
	{
	}

	template <class T>
	Array3D<T>::Array3D(std::size_t columns, std::size_t rows, std::size_t depth) :
		m_values(new T[columns * rows * depth]),
		m_columns(columns),
		m_rows(rows),
		m_depth(depth),
		m_count(columns * rows * depth)
	{
	}

	template <class T>
	Array3D<T>::Array3D(std::size_t columns, std::size_t rows, std::size_t depth, T defaultValue) :
		Array3D<T>(columns, rows, depth)
	{
		std::fill(begin(), end(), defaultValue);
	}

	template <class T>
	Array3D<T>::Array3D(Array3D&& other) :
		m_values(std::move(other.m_values)),
		m_columns(other.m_columns),
		m_rows(other.m_rows),
		m_depth(other.m_depth),
		m_count(other.m_count)
	{
		other.m_columns = 0u;
		other.m_rows = 0u;
		other.m_depth = 0u;
		other.m_count = 0u;
	}

	template <class T>
	Array3D<T>&	Array3D<T>::operator = (Array3D&& other)
	{
		m_values = std::move(other.m_values);
		m_columns = other.m_columns;
		m_rows = other.m_rows;
		m_depth = other.m_depth;
		m_count = other.m_count;
		other.m_columns = 0u;
		other.m_rows = 0u;
		other.m_depth = 0u;
		other.m_count = 0u;
		return (*this);
	}

	template <class T>
	void	Array3D<T>::resize(std::size_t columns, std::size_t rows, std::size_t depth)
	{
		std::size_t	count = columns * rows * depth;

		if (count > m_count)
			m_values.reset(new T[count]);
		m_columns = columns;
		m_rows = rows;
		m_depth = depth;
		m_count = count;
	}

	template <class T>
	void	Array3D<T>::resize(std::size_t columns, std::size_t rows, std::size_t depth, T const& defaultValue)
	{
		resize(columns, rows, depth);
		std::fill(begin(), end(), defaultValue);
	}

	template <class T>
	T&	Array3D<T>::get(std::size_t column, std::size_t row, std::size_t depth)
	{
		return (m_values[index3dToIndex1D(column, row, depth)]);
	}

	template <class T>
	T const&	Array3D<T>::get(std::size_t column, std::size_t row, std::size_t depth)const
	{
		return (m_values[index3dToIndex1D(column, row, depth)]);
	}

	template <class T>
	void		Array3D<T>::set(std::size_t column, std::size_t row, std::size_t depth, T const& value)
	{
		m_values[index3dToIndex1D(column, row, depth)] = value;
	}

	template <class T>
	bool		Array3D<T>::isNull()const
	{
		return (m_values == nullptr);
	}

	template <class T>
	std::size_t	Array3D<T>::columns()const
	{
		return (m_columns);
	}

	template <class T>
	std::size_t		Array3D<T>::rows()const
	{
		return (m_rows);
	}

	template <class T>
	std::size_t		Array3D<T>::depth()const
	{
		return (m_depth);
	}

	template <class T>
	std::size_t		Array3D<T>::count()const
	{
		return (m_count);
	}

	template <class T>
	T&				Array3D<T>::operator()(std::size_t column, std::size_t row, std::size_t depth)
	{
		return (get(column, row, depth));
	}
	
	template <class T>
	T const&		Array3D<T>::operator()(std::size_t column, std::size_t row, std::size_t depth)const
	{
		return (get(column, row, depth));
	}

	template <class T>
	typename Array3D<T>::iterator	Array3D<T>::begin()
	{
		return (m_values.get());
	}

	template <class T>
	typename Array3D<T>::iterator	Array3D<T>::end()
	{
		return (m_values.get() + m_count);
	}

	template <class T>
	typename Array3D<T>::const_iterator	Array3D<T>::begin()const
	{
		return (m_values.get());
	}

	template <class T>
	typename Array3D<T>::const_iterator	Array3D<T>::end()const
	{
		return (m_values.get() + m_count);
	}
}
