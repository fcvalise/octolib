/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 07:34:43 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/26 02:56:50 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <PackageCompiler.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

class CompilationListener : public octo::PackageCompiler::IListener
{
public:
		virtual void	headerBuilded(octo::PackageHeader const& header)
		{
			std::cout << " - header builded: " << header.byteCount() << " bytes" << std::endl;
		}

		virtual void	copyingFile(std::string const& filePath,
									std::size_t current,
									std::size_t total)
		{
			std::cout << " - adding '" << filePath << "' " << current + 1 << " / " << total << std::endl;
			static_cast<void>(filePath);
		}

		virtual void	error(std::string const& message)
		{
			std::cerr << "packager: error: " << message << std::endl;
		}

		virtual void	finished(octo::PackageHeader const& header)
		{
			writeDefineResources(header);	
		}
private:
		void	writeDefineResources(octo::PackageHeader const& header)
		{
			std::ofstream	ofs("DefineResources.hpp");
			std::uint64_t	key = 0;
			std::string		resourceMacroName;

			if (ofs.is_open() == false)
			{
				error("can't open file 'DefineResources.hpp'");
				return;
			}
			ofs <<	"#if !defined DEFINE_PACKAGED_RESOURCES_HPP\n"
					"# define DEFINE_PACKAGED_RESOURCES_HPP\n";
			ofs << "# include <cstdint>\n\n";
			ofs << "typedef std::uint64_t	ResourceKey\n";
			for (auto const& entry : header)
			{
				resourceMacroName = entry.name;
				std::for_each(resourceMacroName.begin(), resourceMacroName.end(), [](char& c){c = std::toupper(c);});
				std::for_each(resourceMacroName.begin(), resourceMacroName.end(), [](char& c)
						{
							if (c == '.')
								c = '_';
						});
				ofs << "static constexpr ResourceKey const	" << resourceMacroName << "\t" << key++ << "\n";
			}
			ofs << "\n" << "#endif // DEFINE_PACKAGED_RESOURCES_HPP";
		}
};

int	main(int argc, char **argv)
{
	octo::PackageCompiler		compiler;
	CompilationListener			listener;
	std::vector<std::string>	inputPaths;
	std::string					outputPath;

	if (argc < 3)
	{
		std::cerr << "usage: packager <output_file> <input_files...>" << std::endl;
		return (1);
	}
	outputPath = argv[1];
	inputPaths.assign(argv + 2, argv + argc);
	inputPaths.erase(std::remove(std::begin(inputPaths), std::end(inputPaths), argv[0]), std::end(inputPaths));
	if (inputPaths.empty() == false)
	{
		compiler.setListener(&listener);
		if (compiler.compile(outputPath, inputPaths))
			return (0);
	}
	return (1);
}
