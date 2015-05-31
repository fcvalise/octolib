/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 07:34:43 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/30 15:13:38 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <PackageCompiler.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

void	printByteSize(std::ostream& os, std::uint64_t bytes)
{
	static std::string const	Unities[]{
		"B",
		"KiB",
		"MiB",
		"GiB"
	};
	float		floatValue = bytes;
	std::size_t	unityIndex = 0;

	while (floatValue / 1024.f > 1.f && unityIndex < 3)
	{
		floatValue /= 1024.f;
		++unityIndex;
	}
	os << std::setprecision(3) << floatValue << Unities[unityIndex];
}

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
			std::cout << " - packaged items count: " << header.count() << " (";
			printByteSize(std::cout, header.packagedByteCount());
			std::cout << ")" << std::endl;
			std::cout << " - header size: " << header.byteCount() << " bytes" << std::endl;
		}
};

int	main(int argc, char **argv)
{
	octo::PackageCompiler		compiler;
	CompilationListener			listener;
	std::vector<std::string>	inputPaths;
	std::string					outputPath;
	std::string					outputHeaderPath;
	std::size_t					firstInput = 2;

	if (argc < 3 || (argv[2] == std::string("-h") && argc < 4))
	{
		std::cerr << "usage: packager <output_file> [-h <header_file_path>] <input_files...>" << std::endl;
		return (1);
	}
	if (argv[2] == std::string("-h"))
	{
		outputHeaderPath = argv[3];
		std::cout << "header: " << outputHeaderPath << std::endl;
		firstInput += 2;
	}
	outputPath = argv[1];
	inputPaths.assign(argv + firstInput, argv + argc);
	inputPaths.erase(std::remove(std::begin(inputPaths), std::end(inputPaths), argv[0]), std::end(inputPaths));
	std::sort(inputPaths.begin(), inputPaths.end());
	std::unique(inputPaths.begin(), inputPaths.end());
	if (inputPaths.empty() == false)
	{
		compiler.setListener(&listener);
		if (compiler.compile(outputPath, outputHeaderPath, inputPaths))
			return (0);
	}
	return (1);
}
