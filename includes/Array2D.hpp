/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array2D.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 20:29:37 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/29 01:45:41 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY2D_HPP
# define ARRAY2D_HPP
# include <memory>

namespace octo
{
	/*!
	 *	\ingroup Core
	 *	\class Array2D
	 *	\brief Generic 2d array
	 *	
	 *	This class provide a generic two dimmensional array.
	 *	
	 *	This container provide the couple of methods begin/end so it can
	 *	be used with for each loop (C++ 11) or with STL algorithms exactly
	 *	as std::vector.
	 *	\code
	 *	Array2D<int>	mat(3, 3, 0);
	 *	int			counter = 0;
	 *	
	 *	for (auto& value : mat)
	 *		value = counter++;
	 *	for (auto value : mat)
	 *		std::cout << value << std::endl;
	 *	\endcode
	 */
	template <class T>
	class Array2D
	{
		Array2D(Array2D<T> const&) = delete;
		Array2D&				operator = (Array2D<T> const&) = delete;
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
		Array2D();

		/*!	Create an array */
		Array2D(std::size_t columns, std::size_t rows);

		/*!	Create an array filled by a value */
		Array2D(std::size_t columns, std::size_t rows, T defaultValue);

		/*!	Move constructor */
		Array2D(Array2D<T>&& other);

		/*!	Move assignement operator */
		Array2D<T>&	operator = (Array2D<T>&& other);

		/*!	Resize the array
		 *	Internal memory is reallocated only if the new size is greater
		 *	than the current size.<br>
		 *	\warning This method invalidates iterators.
		 */
		void				resize(std::size_t columns, std::size_t rows);

		/*!	Resize the array and fill it with a value
		 *	Internal memory is reallocated only if the new size is greater
		 *	than the current size.<br>
		 *	\warning This method invalidates iterators.
		 */
		void				resize(std::size_t columns, std::size_t rows, T defaultValue);

		/*!	Get a value
		 *
		 *	\warning Never call this function with parameters column or row out of
		 *	bound, since this will cause an undefinied behavior.
		 */
		T&					get(std::size_t column, std::size_t row);

		/*!	Get a constant value
		 *
		 *	\warning Never call this function with parameters column or row out of
		 *	bound, since this will cause an undefinied behavior.
		 */
		T const&			get(std::size_t column, std::size_t row)const;

		/*!	Set a value
		 *
		 *	\warning Never call this function with parameters column or row out of
		 *	bound, since this will cause an undefinied behavior.
		 */
		void				set(std::size_t column, std::size_t row, T const& value);

		/*!	Indicates if the array is null */
		bool				isNull()const;

		/*!	Get the columns count */
		std::size_t			columns()const;

		/*!	Get the rows count */
		std::size_t			rows()const;

		/*!	Get the count of values */
		std::size_t			count()const;

		/*!	Get a value */
		T&					operator()(std::size_t colum,  std::size_t row);

		/*!	Get a constant value */
		T const&			operator()(std::size_t colum,  std::size_t row)const;

		iterator			begin();
		iterator			end();
		const_iterator		begin()const;
		const_iterator		end()const;
	private:
		inline std::size_t	index2dToIndex1D(std::size_t column, std::size_t row)const;
	private:
		std::unique_ptr<T[]>	m_values;
		std::size_t				m_columns;
		std::size_t				m_rows;
		std::size_t				m_count;
	};
}

#include "Array2D.hxx"
#endif
