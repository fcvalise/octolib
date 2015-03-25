/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 07:34:43 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/25 17:17:44 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Package.hpp>

#include <map>
#include <functional>
#include <sstream>

typedef std::vector<std::string>							Args;
typedef std::function<bool(octo::Package&, Args const&)>	Command;
typedef std::map<std::string, Command>						CommandMap;

static std::string	getEntryTypeLabel(octo::PackageHeader::EntryType type);
static bool			execute(std::string const& command, Args const& args, octo::Package& package);

static std::map<octo::PackageHeader::EntryType, std::string> const	EntryTypeTexts
{
	{octo::PackageHeader::EntryType::Font, "FONT"},
	{octo::PackageHeader::EntryType::Texture, "TEXTURE"},
	{octo::PackageHeader::EntryType::Sound, "SOUND"},
	{octo::PackageHeader::EntryType::Text, "TEXT"}
};

static CommandMap const	Commands
{
	{
		"--help", [](octo::Package&, Args const&)
		{
			std::cout << "usage: package_reader <package_file> <command> [args...]" << std::endl;
			return (true);
		}
	},
	{
		"--info", [](octo::Package& package, Args const&)
		{
			octo::PackageHeader const&	header = package.getHeader();

			std::cout << " - package item count: " << header.count() << std::endl;
			std::cout << " - header size: " << header.byteCount() << " bytes" << std::endl;
			return (true);
		}
	},
	{
		"--list", [](octo::Package& package, Args const& args)
		{
			octo::PackageHeader const&	header = package.getHeader();
			std::uint64_t				key = 0;

			if (args.size() > 0)
			{
				std::cerr << "usage: package_reader <package_file> --list" << std::endl;
				return (false);
			}
			for (auto const& entry : header)
			{
				std::cout << " - " << getEntryTypeLabel(entry.type) << " " << key++ << " " << entry.name << " " << entry.size << " bytes" << std::endl;
			}
			return (true);
		}
	},
	{
		"--extract", [](octo::Package& package, Args const& args)
		{
			std::uint64_t				key = 0;
			std::istringstream			iss;
			std::unique_ptr<char>		buffer;
			std::uint64_t				size = 0;
			std::ofstream				output;

			if (args.size() < 2)
			{
				std::cerr << "usage: package_reader <package_file> --extract key <output_file>" << std::endl;
				return (false);
			}
			iss.str(args[0]);
			output.open(args[1], std::ios_base::binary);
			if (output.is_open() == false)
			{
				std::cerr << "package_reader: error: can't open file '" << args[1] << "' for writing" << std::endl;
				return (false);
			}
			if (iss >> key)
			{
				package.load(buffer, size, key);
				output.write(buffer.get(), size);
			}
			else
			{
				std::cerr << "package_reader: error: invalid key: " << key << std::endl;
				return (false);
			}
			return (true);
		}
	}
};

std::string	getEntryTypeLabel(octo::PackageHeader::EntryType type)
{
	auto it = EntryTypeTexts.find(type);

	if (it == EntryTypeTexts.end())
		return ("UNKNOWN");
	else
		return (it->second);
}

bool	execute(std::string const& command, Args const& args, octo::Package& package)
{
	auto	it = Commands.find(command);

	if (it == Commands.end())
		return (false);
	return (it->second(package, args));
}

int	main(int argc, char **argv)
{
	octo::Package				package;
	std::string					packagePath;
	std::string					command;
	std::vector<std::string>	args;

	if (argc < 3)
	{
		execute("--help", {}, package);
		return (1);
	}
	packagePath = argv[1];
	command = argv[2];
	args.assign(argv + 3, argv + argc);
	if (package.open(packagePath) == false)
	{
		std::cerr << "package_reader: error: unable to open package file '" << packagePath << "'" << std::endl;
		return (1);
	}	
	if (execute(command, args, package) == false)
	{
		std::cerr << "package_reader: error: unknow command: " << command << std::endl;
		return (1);
	}
	return (0);
}