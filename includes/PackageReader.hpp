/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PackageReader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 02:51:53 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/26 05:20:07 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PACKAGE_READER_HPP
# define PACKAGE_READER_HPP
# include "PackageHeader.hpp"

#include <memory>
#include <fstream>

namespace octo
{
	/*!
	 *	Package file reader
	 *
	 *	Provide a way to load resources from a package file with C++ code.<br>
	 *	In a package each item is associated to an unique identifier generated
	 *	by package compiler.<br>
	 *	Octo library provides somes utilities to building and managing packages.
	 *
	 *	\see PackageHeader
	 *	\see PackageCompiler
	 */
	class PackageReader
	{
	public:
		/*!	Open a package file */
		bool					open(std::string const& fileName);

		/*!	Load an item from package */
		bool					load(std::unique_ptr<char>& buffer, std::uint64_t& size, std::uint64_t key);

		/*!	Return true if a file is open */
		bool					isOpen()const;

		/*!	Return the package header */
		PackageHeader const&	getHeader()const;
	private:
		PackageHeader	m_header;
		std::ifstream	m_file;
	};
}

#endif
