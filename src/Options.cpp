/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Options.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 22:39:33 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/28 14:37:51 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Options.hpp"
#include "OptionParser.hpp"
#include <cassert>
#include <fstream>

namespace octo
{
	void	Options::load(AbstractLoader const& loader)
	{
		loader.load(*this);
	}

	void	Options::save(AbstractExporter&& exporter)const
	{
		for (auto it = m_values.begin(); it != m_values.end(); ++it)
		{
			exporter.writeKeyValue(it->first, it->second);
		}
	}

	bool	Options::containsKey(std::string const& key)const
	{
		return (m_values.find(key) != m_values.end());
	}

	bool		Options::hasValue(std::string const& key)const
	{
		auto		it = m_values.find(key);
		
		if (it != m_values.end())
			return (it->second.empty() == false);
		else
			return (false);
	}

	std::string	Options::getValue(std::string const& key)const
	{
		auto		it = m_values.find(key);

		assert (it != m_values.end());
		return (it->second);
	}

	std::string	Options::getValue(std::string const& key, std::string const& defaultValue)const
	{
		auto		it = m_values.find(key);
		
		if (it != m_values.end())
			return (it->second);
		else
			return (defaultValue);
	}

	void		Options::setValue(std::string const& key, std::string const& value)
	{
		m_values[key] = value;
	}

	void		Options::clear()
	{
		m_values.clear();
	}

	// AbstractLoader
	Options::AbstractLoader::~AbstractLoader()
	{
	}

	// AbstractExporter
	Options::AbstractExporter::~AbstractExporter()
	{
	}

	// CommandLineLoader
	Options::CommandLineLoader::CommandLineLoader(int argc, char **argv)
	{
		for (int i = 1; i < argc; ++i)
			m_args.push_back(argv[i]);
	}

	void	Options::CommandLineLoader::load(Options& options)const
	{
		std::string	key;
		std::string	value;

		for (auto const& arg : m_args)
		{
			if (OptionParser::parseLine(arg, key, value))
			{
				options.setValue(key, value);
			}
		}
	}
	
	// ConfigFileLoader
	Options::ConfigFileLoader::ConfigFileLoader(std::string const& fileName) :
		m_fileName(fileName)
	{
	}

	void	Options::ConfigFileLoader::load(Options& options)const
	{
		std::string		key;
		std::string		value;
		std::string		line;
		std::ifstream	file;
		
		file.open(m_fileName.c_str());
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				if (OptionParser::parseLine(line, key, value))
				{
					options.setValue(key, value);
				}
			}	
		}
	}

	Options::ConfigFileExporter::ConfigFileExporter(std::string const& filePath)
	{
		m_file.open(filePath);
	}

	Options::ConfigFileExporter::~ConfigFileExporter()
	{
	}

	bool	Options::ConfigFileExporter::writeKeyValue(std::string const& key, std::string const& value)
	{
		if (m_file.is_open() == false)
			return (false);
		m_file << key << " = " << value << "\n";
		return (true);
	}
}
