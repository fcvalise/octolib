/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleInterpreter.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 12:23:11 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/27 21:54:45 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLEINTERPRETER_HPP
# define CONSOLEINTERPRETER_HPP
# include <memory>
# include <map>
# include <string>
# include <vector>
# include <sstream>
# include "details/Meta.hpp"

namespace octo
{
	/*!	\ingroup Core
	 *	\class ConsoleInterpreter
	 *	\brief Simple command interpreter
	 *
	 *	This interpreter is able to call free functions or members functions
	 *	with or without parameters or return type.<br>
	 *
	 *	Syntax of call is:
	 *	\code
	 *	<command_name>([arg0][,arg1][,arg...][,argN])
	 *	\endcode
	 */
	class ConsoleInterpreter
	{
		/*!	\addtogroup Console
		 *	@{
		 */

		/*!	
		 *	\class AbstractCallable
		 *	\brief Abstraction of a callable object
		 */
		class AbstractCallable;

		/*!	Store a free function */
		template <class R, class ... A>
		class Callable;

		/*!	Store a free function without return */
		template <class ... A>
		class Callable<void, A...>;

		/*!	Store a member function */
		template <class C, class R, class ... A>
		class CallableMem;

		/*!	Store a member function without return */
		template <class C, class ... A>
		class CallableMem<C, void, A...>;

		/*!	Store a constant member function */
		template <class C, class R, class ... A>
		class CallableMemConst;

		/*!	Store a constant member function without return */
		template <class C, class ... A>
		class CallableMemConst<C, void, A...>;

		/*!	Store a functor or a lamdba expression */
		template <class C, class R, class ... A>
		class CallableFunctor;

		/*!	Store a constant functor */
		template <class C, class R, class ... A>
		class CallableConstFunctor;

		/*!
		 *	@}
		 */
	public:
		class ArgumentTypeException;
		class NotEnoughArgumentException;
		class TooManyArgumentException;
		class UnknowCommandException;
		class SyntaxErrorException;

		/*!	Register a new command from a C++ free function */
		template <class R, class ... A>
		void						addCommand(std::wstring const& name, R(*function)(A...));

		/*!	Register a new command from a C++ member function */
		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C& instance, R(C::*function)(A...));

		/*!	Register a new command from a C++ member function */
		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C* instance, R(C::*function)(A...));

		/*!	Register a new command from a C++ constant member function */
		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C const& instance, R(C::*function)(A...)const);

		/*!	Register a new command from a C++ constant member function */
		template <class C, class R, class ... A>
		void						addCommand(std::wstring const& name, C const* instance, R(C::*function)(A...)const);

		/*!	Register a new command from a functor or a lambda function */
		template <class F>
		void						addCommand(std::wstring const& name, F functor);

		/*!	Execute a command line */
		std::wstring				execute(std::wstring const& line);
	
		/*!	Return a list of each command name availables */
		std::vector<std::wstring>	getCommandList()const;
	private:
		template <class C, class R, class ... A>
		void						addFunctor(std::wstring const& name, C instance, R(C::*function)(A...));

		template <class C, class R, class ... A>
		void						addFunctor(std::wstring const& name, C instance, R(C::*function)(A...)const);

		typedef std::shared_ptr<AbstractCallable>	CallablePtr;
		typedef std::map<std::wstring, CallablePtr>	Map;

		Map	m_callables;
	};

	/*!	Exception thrown when an argument is not of the type expected */
	class ConsoleInterpreter::ArgumentTypeException
	{
	public:
		explicit ArgumentTypeException(std::size_t argumentIndex, std::string const& expectedTypeName);

		std::size_t		getArgumentIndex()const;
		std::wstring	getExpectedTypeName()const
		{
			return (m_expectedTypeName);
		}
	private:
		std::wstring	m_expectedTypeName;
		std::size_t		m_argumentIndex;
	};

	/*!	Exception thrown when there not enough argument */
	class ConsoleInterpreter::NotEnoughArgumentException
	{
	public:
		NotEnoughArgumentException(std::size_t expected, std::size_t provided);

		std::size_t	getExpected()const;
		std::size_t	getProvided()const;
	private:
		std::size_t	m_expected;
		std::size_t	m_provided;
	};

	/*!	Exception thrown when there too many argument */
	class ConsoleInterpreter::TooManyArgumentException
	{
	public:
		TooManyArgumentException(std::size_t expected, std::size_t provided);

		std::size_t	getExpected()const;
		std::size_t	getProvided()const;
	private:
		std::size_t	m_expected;
		std::size_t	m_provided;
	};

	/*!	Exception thrown when an unknow command is called */
	class ConsoleInterpreter::UnknowCommandException
	{
	public:
		explicit UnknowCommandException(std::wstring const& commandName);

		std::wstring const& getCommandName()const;
	private:
		std::wstring	m_commandName;
	};

	/*!	Exception thrown when a syntax error is detected */
	class ConsoleInterpreter::SyntaxErrorException
	{
	public:
		SyntaxErrorException(std::wstring const& description, std::size_t pos);

		std::wstring const&	getDescription()const;
		std::size_t			getPosition()const;
	private:
		std::wstring 	m_description;
		std::size_t		m_pos;
	};
}

#include "ConsoleInterpreter.hxx"
#endif
