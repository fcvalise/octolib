/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Options.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 22:34:27 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 05:50:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_HPP
# define OPTIONS_HPP
# include <string>
# include <map>
# include <sstream>
# include <vector>
# include <fstream>
# include <stdexcept>
# include "NonCopyable.hpp"

namespace octo
{
	/*!	\ingroup Core
	 *	Option container
	 *	
	 *	This container stores a pair of key/value.<br>
	 *	A set of methods getValue() provides access to the values stored from their keys.<br>
	 *	load() loads data into the container.
	 *
	 *	The following table describes the format of somes possible
	 *	type storable as value:
	 *	<TABLE>
	 *	<TR>
	 *		<TH>type</TH>
	 *		<TH>format</TH>
	 *		<TH>example</TH>
	 *	</TR>
	 *	<TR>
	 *		<TD>bool</TD>
	 *		<TD>value</TD>
	 *		<TD>true</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>integer types</TD>
	 *		<TD>value</TD>
	 *		<TD>666</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>float types</TD>
	 *		<TD>integer_part.decimal_part</TD>
	 *		<TD>2.8182</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>sf::Vector2<T></TD>
	 *		<TD>x;y</TD>
	 *		<TD>for T=int 12;34</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>sf::Vector3<T></TD>
	 *		<TD>x;y;z</TD>
	 *		<TD>for T=float 1.2;3.4;5.6</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>sf::Rect<T></TD>
	 *		<TD>left;top;width;height</TD>
	 *		<TD>for T=float: 1.2;3.4;5.6;7.8</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>sf::Color</TD>
	 *		<TD>red;green;blue;alpha</TD>
	 *		<TD>255;20;147;255</TD>
	 *	</TR>
	 *	<TR>
	 *		<TD>sf::VideoMode</TD>
	 *		<TD>width;height;bit_per_pixels</TD>
	 *		<TD>2880;1800;32</TD>
	 *	</TR>
	 *	</TABLE>
	 *		
	 */
	class Options : public NonCopyable
	{
		typedef std::map<std::string, std::string>	Map;
	public:
		class AbstractLoader;
		class AbstractExporter;
		class CommandLineLoader;
		class ConfigFileLoader;
		class ConfigFileExporter;
		class InvalidTypeException;

		/*!	Load values from a loader
		 *
		 *	\param loader Reference on a loader derived from AbstractLoader
		 *	Values of old keys can be replaced, this behavior is defined
		 *	by the loader used.
		 */
		void		load(AbstractLoader const& loader);

		/*!	Export values with an exporter */
		void		save(AbstractExporter&& exporter)const;

		/*!	Return true if the key \a key is in the container */
		bool		containsKey(std::string const& key)const;

		/*!	Return true if the key \a key has a value defined */
		bool		hasValue(std::string const& key)const;

		/*!	Get a value
		 *
		 *	\throw std::range_error if key is not found
		 *	\throw InvalidTypeException if value is not interpretable as type T
		 */
		template <class T>
		T			getValue(std::string const& key)const;

		/*!	Get a value or \a defaultValue if \a key is not found
		 *	\param key Key searched
		 *	\param defaultValue Value used if the key is not found
		 *	\remark Compiler can deduce automatically the type of T using the type of defaultValue
		 */
		template <class T>
		T			getValue(std::string const& key, T const& defaultValue)const;

		/*!	Define or replace a pair of key/value */
		template <class T>
		void		setValue(std::string const& key, T const& value);

		void		setPath(std::string path);
		std::string	getPath(void) const;

		/*!	Remove all data */
		void		clear();
	private:
		Map			m_values;
		std::string	m_path;
	};

	/*!	Provide a way to create new data loader for option container */
	class Options::AbstractLoader
	{
	public:
		virtual ~AbstractLoader();

		virtual void	load(Options& options)const = 0;
	};

	/*!	Provide a way to create new data exporter for option container */
	class Options::AbstractExporter
	{
	public:
		virtual ~AbstractExporter();

		virtual bool	writeKeyValue(std::string const& key, std::string const& value) = 0;
	};

	/*!	Load options from command line arguments */
	class Options::CommandLineLoader : public Options::AbstractLoader
	{
	public:
		CommandLineLoader(int argc, char **argv);

		virtual void	load(Options& options)const;
	private:
		std::vector<std::string>	m_args;
	};
	
	/*!	Load options from a text file */
	class Options::ConfigFileLoader : public Options::AbstractLoader
	{
	public:
		explicit ConfigFileLoader(std::string const& fileName);

		virtual void	load(Options& options)const;
	private:
		std::string	m_fileName;
	};

	/*!	Export option as text file */
	class Options::ConfigFileExporter : public Options::AbstractExporter
	{
	public:
		explicit ConfigFileExporter(std::string const& filePath);
		virtual ~ConfigFileExporter();

		virtual bool	writeKeyValue(std::string const& key, std::string const& value);
	private:
		std::ofstream	m_file;
	};

	/*!	Exception thrown when a value can't be interpreted as a particular type */
	class Options::InvalidTypeException : public std::logic_error
	{
	public:
		explicit InvalidTypeException(std::string const& key);

		std::string const&	getKey()const;
	private:
		std::string	m_key;
	};
}

#include "Options.hxx"
#endif
