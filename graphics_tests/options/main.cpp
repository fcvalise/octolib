/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 02:35:21 by irabeson          #+#    #+#             */
/*   Updated: 2015/03/24 16:44:49 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Options.hpp>
#include <iostream>

int main(int argc, char **argv)
{
	octo::Options	options;

	std::cout << "usage: ./test.app <key0=value0> ... <keyN=valueN>" << std::endl;
	std::cout << "Option is saved to test.tmp" << std::endl;
	options.load(octo::Options::CommandLineLoader(argc, argv));
	options.save(octo::Options::ConfigFileExporter("test.tmp"));
    return 0;
}
