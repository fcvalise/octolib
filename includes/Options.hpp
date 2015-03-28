/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Options.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 22:34:27 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/27 20:04:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_HPP
# define OPTIONS_HPP
# include <string>
# include <map>
# include <sstream>
# include <vector>
# include <fstream>

namespace octo
{
	/*!	Option container
	 *	
	 *	This container store a pair of key/value.<br>
	 *	getValue() methods provides access to value from his key.<br>
	 *	load() loads data into the container.
	 */
	class Options
	{
		typedef std::map<std::string, std::string>	Map;
	public:
		class AbstractLoader;
		class AbstractExporter;
		class CommandLineLoader;
		class ConfigFileLoader;
		class ConfigFileExporter;

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

		/*!	Get a value
		 *
		 * 	\warning Do not use an invalid key since this causes an undefined behavior.
		 */
		template <class T>
		T			getValue(std::string const& key)const;

		std::string	getValue(std::string const& key)const;

		/*!	Get a value or \a defaultValue if \a key is not found
		 *	\param key Key searched
		 *	\param defaultValue Value used if the key is not found
		 */
		template <class T>
		T			getValue(std::string const& key, T const& defaultValue)const;

		std::string	getValue(std::string const& key, std::string const& defaultValue)const;

		/*!	Define or replace a pair of key/value */
		template <class T>
		void		setValue(std::string const& key, T const& value);

		void		setValue(std::string const& key, std::string const& value);

		/*!	Remove all data */
		void		clear();
	private:
		Map			m_values;
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
}

#include "Options.hxx"
#endif
