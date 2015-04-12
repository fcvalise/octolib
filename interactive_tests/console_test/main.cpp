/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 03:18:05 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/11 22:20:42 by irabeson         ###   ########.fr       */
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

struct	ElFunctor
{
	double	operator()(int x, float y, double z)
	{
		return (x + y + z);
	}
};

struct	ElConstantFunctor
{
	double	operator()(int x, float y, double z)const
	{
		return (x + y + z);
	}
};

int	main()
{
	octo::ConsoleInterpreter	interpreter;
	Captain						captain;

	interpreter.addCommand(L"lambda", [](int x){return (x + 2);});
	interpreter.addCommand(L"hello", &sayHello);
	interpreter.addCommand(L"captainAge", &getCaptainAge);
	interpreter.addCommand(L"print", &print);
	interpreter.addCommand(L"printTwo", &print2);
	interpreter.addCommand(L"printStr", &printStr);
	interpreter.addCommand(L"say", &saySomething);
	interpreter.addCommand(L"puteBorgne", captain, &Captain::sayPuteBorgne);
	interpreter.addCommand(L"puteBorgneAge", captain, &Captain::sayPuteBorgneAndReturnAge);
	interpreter.addCommand(L"puteBorgneAgeConst", captain, &Captain::sayPuteBorgneConst);
	interpreter.addCommand(L"functor", (ElFunctor()));
	interpreter.addCommand(L"cfunctor", (ElConstantFunctor()));
	interpreter.execute(L"hello()");
	std::wcout << interpreter.execute(L"captainAge()") << std::endl;
	std::wcout << interpreter.execute(L"print(\"90\")") << std::endl;
	std::wcout << interpreter.execute(L"printTwo(90, 87)") << std::endl;
	std::wcout << interpreter.execute(L"printStr(\"90, 87\")") << std::endl;
	std::wcout << interpreter.execute(L"say(\"90, 87\")") << std::endl;
	std::wcout << interpreter.execute(L"puteBorgne()") << std::endl;
	std::wcout << interpreter.execute(L"puteBorgneAge()") << std::endl;
	std::wcout << interpreter.execute(L"puteBorgneAgeConst()") << std::endl;
	std::wcout << interpreter.execute(L"functor(4, 5., 10.33)") << std::endl;
	std::wcout << interpreter.execute(L"cfunctor(4, 5., 10.33)") << std::endl;
	std::wcout << interpreter.execute(L"lambda(43)") << std::endl;
	return (0);
}
