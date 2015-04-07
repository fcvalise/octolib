/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 03:18:05 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/07 10:59:46 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ConsoleInterpreter.hpp>
#include <iostream>

static void	sayHello()
{
	std::wcout << L"Hello" << std::endl;
}

static int getCaptainAge()
{
	return (42);
}

static void	print(int n)
{
	std::wcout << "print: " << n << std::endl;
}

static void	print2(int n, int y)
{
	std::wcout << "print: " << n << ":" << y << std::endl;
}

static void printStr(std::wstring const& text)
{
	std::wcout << "print: " << text << std::endl;
}

static std::wstring saySomething(std::wstring const& text)
{
	return (L"I say: " + text);
}

class Captain
{
public:
	void	sayPuteBorgne()
	{
		std::cout << "Pute borgne" << std::endl;
	}

	void	sayPuteBorgneConst()const
	{
		std::cout << "Pute borgne const" << std::endl;
	}

	int	sayPuteBorgneAndReturnAge()
	{
		std::cout << "Pute borgne" << std::endl;
		return (123);
	}
};

int	main()
{
	octo::ConsoleInterpreter	interpreter;
	Captain						captain;

	interpreter.addFunction(L"hello", &sayHello);
	interpreter.addFunction(L"captainAge", &getCaptainAge);
	interpreter.addFunction(L"print", &print);
	interpreter.addFunction(L"printTwo", &print2);
	interpreter.addFunction(L"printStr", &printStr);
	interpreter.addFunction(L"say", &saySomething);
	interpreter.addFunction(L"puteBorgne", captain, &Captain::sayPuteBorgne);
	interpreter.addFunction(L"puteBorgneAge", captain, &Captain::sayPuteBorgneAndReturnAge);
	interpreter.addFunction(L"puteBorgneAgeConst", captain, &Captain::sayPuteBorgneConst);
	interpreter.execute(L"hello()");
	std::wcout << interpreter.execute(L"captainAge()") << std::endl;
	std::wcout << interpreter.execute(L"print(\"90\")") << std::endl;
	std::wcout << interpreter.execute(L"printTwo(90, 87)") << std::endl;
	std::wcout << interpreter.execute(L"printStr(\"90, 87\")") << std::endl;
	std::wcout << interpreter.execute(L"say(\"90, 87\")") << std::endl;
	std::wcout << interpreter.execute(L"puteBorgne()") << std::endl;
	std::wcout << interpreter.execute(L"puteBorgneAge()") << std::endl;
	std::wcout << interpreter.execute(L"puteBorgneAgeConst()") << std::endl;
	return (0);
}
