/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array3D.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 17:53:46 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/20 22:22:39 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY3D_HPP
# define ARRAY3D_HPP
# include <memory>

namespace octo
{
	/*!
	 *	\class Array3D
	 *	\brief Generic three dimensional array
	 *	\tparam T Type of value stored
	 *	
	 *	This class provide a generic three dimmensional array.
	 *	
	 *	This container provide the couple of methods begin/end so it can
	 *	be used with for each loop (C++ 11) or with STL algorithms exactly
	 *	as std::vector.
	 *	\code
	 *	Array3D<int>	array(3, 3, 3, 0);
	 *	int				counter = 0;
	 *	
	 *	for (auto& value : array)
	 *		value = counter++;
	 *	for (auto value : array)
	 *		std::cout << value << std::endl;
	 *	std::fill(array.begin(), array.end(), 666);
	 *	for (auto value : array)
	 *		std::cout << value << std::endl;
	 *	\endcode
	 */
	template <class T>
	class Array3D
	{
		Array3D(Array3D<T> const&) = delete;
		Array3D&	operator = (Array3D<T> const&) = delete;
	public:
		typedef T*			iterator;
		typedef T const*	const_iterator;

		/*!	Create a null array
		 *	
		 *	A null array has no memory reserved.<br>
		 *	\warning Using set() and get() method on a null array causes an undefined
		 *	behavior.
		 *	\see isNull()
		 *	\see resize()
		 */
		Array3D();

		/*!	Create an array */
		Array3D(std::size_t columns, std::size_t rows, std::size_t depth);

		/*!	Create an array filled by a value */
		Array3D(std::size_t columns, std::size_t rows, std::size_t depth, T defaultValue);

		/*!	Move constructor */
		Array3D(Array3D<T>&& other);

		/*!	Move assignement operator */
		Array3D<T>&	operator = (Array3D<T>&& other);

		/*!	Resize the array
		 *	Internal memory is reallocated only if the new size is greater
		 *	than the current size.<br>
		 *	\warning This method invalidates iterators.
		 */
		void				resize(std::size_t columns, std::size_t rows, std::size_t depth);

		/*!	Resize the array and fill it with a value
		 *	Internal memory is reallocated only if the new size is greater
		 *	than the current size.<br>
		 *	\warning This method invalidates iterators.
		 */
		void				resize(std::size_t columns, std::size_t rows, std::size_t depth, T const& defaultValue);

		/*!	Get a value
		 *
		 *	\warning never call this function with parameters column, row or depth out of
		 *	bound, since this will cause an undefinied behavior.
		 */
		T&					get(std::size_t column, std::size_t row, std::size_t depth);

		/*!	Get a constant value
		 *
		 *	\warning never call this function with parameters column, row or depth out of
		 *	bound, since this will cause an undefinied behavior.
		 */
		T const&			get(std::size_t column, std::size_t row, std::size_t depth)const;

		/*!	Set a value
		 *
		 *	\warning Never call this function with parameters column, row or depth out of
		 *	bound, since this will cause an undefinied behavior.
		 */
		void				set(std::size_t column, std::size_t row, std::size_t depth, T const& value);

		/*!	Indicates if the array is null */
		bool				isNull()const;

		/*!	Get the columns count */
		std::size_t			columns()const;

		/*!	Get the rows count */
		std::size_t			rows()const;

		/*!	Get the depth */
		std::size_t			depth()const;

		/*!	Get the count of values */
		std::size_t			count()const;

		/*!	Get a value */
		T&					operator()(std::size_t colum, std::size_t row, std::size_t depth);
		
		/*!	Get a constant value */
		T const&			operator()(std::size_t colum, std::size_t row, std::size_t depth)const;

		iterator			begin();
		iterator			end();
		const_iterator		begin()const;
		const_iterator		end()const;
	private:
		inline std::size_t	index3dToIndex1D(std::size_t column, std::size_t row, std::size_t depth)const;
	private:
		std::unique_ptr<T[]>	m_values;
		std::size_t				m_columns;
		std::size_t				m_rows;
		std::size_t				m_depth;
		std::size_t				m_count;
	};
}

#include "Array3D.hxx"
#endif
