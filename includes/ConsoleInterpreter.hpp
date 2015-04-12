/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleInterpreter.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 12:23:11 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/11 21:57:35 by irabeson         ###   ########.fr       */
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
		class AbstractCallable;

		template <class R, class ... A>
		class Callable;

		template <class ... A>
		class Callable<void, A...>;

		template <class C, class R, class ... A>
		class CallableMem;

		template <class C, class ... A>
		class CallableMem<C, void, A...>;

		template <class C, class R, class ... A>
		class CallableMemConst;

		template <class C, class ... A>
		class CallableMemConst<C, void, A...>;

		template <class C, class R, class ... A>
		class CallableFunctor;

		template <class C, class R, class ... A>
		class CallableConstFunctor;
	public:
		class ArgumentTypeException;
		class NotEnoughArgumentException;
		class UnknowCommandException;
		class SyntaxErrorException;

		/*!	Register a new command from a C++ free function */
		template <class R, class ... A>
		void			addCommand(std::wstring const& name, R(*function)(A...));

		/*!	Register a new command from a C++ member function */
		template <class C, class R, class ... A>
		void			addCommand(std::wstring const& name, C& instance, R(C::*function)(A...));

		/*!	Register a new command from a C++ member function */
		template <class C, class R, class ... A>
		void			addCommand(std::wstring const& name, C* instance, R(C::*function)(A...));

		/*!	Register a new command from a C++ constant member function */
		template <class C, class R, class ... A>
		void			addCommand(std::wstring const& name, C const& instance, R(C::*function)(A...)const);

		/*!	Register a new command from a C++ constant member function */
		template <class C, class R, class ... A>
		void			addCommand(std::wstring const& name, C const* instance, R(C::*function)(A...)const);

		/*!	Register a new command from a functor or a lambda function */
		template <class F>
		void			addCommand(std::wstring const& name, F&& functor);

		/*!	Execute a command line */
		std::wstring	execute(std::wstring const& line);
	private:
		template <class C, class R, class ... A>
		void			addFunctor(std::wstring const& name, C instance, R(C::*function)(A...));

		template <class C, class R, class ... A>
		void			addFunctor(std::wstring const& name, C instance, R(C::*function)(A...)const);

		typedef std::shared_ptr<AbstractCallable>	CallablePtr;
		typedef std::map<std::wstring, CallablePtr>	Map;

		Map	m_callables;
	};

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

	class ConsoleInterpreter::NotEnoughArgumentException
	{
	public:
		NotEnoughArgumentException() = default;
	};

	class ConsoleInterpreter::UnknowCommandException
	{
	public:
		explicit UnknowCommandException(std::wstring const& commandName);

		std::wstring const& getCommandName()const;
	private:
		std::wstring	m_commandName;
	};

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
