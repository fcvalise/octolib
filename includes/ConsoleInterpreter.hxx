/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleInterpreter.hxx                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/05 15:01:38 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/30 05:54:00 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "details/GetTypeName.hpp"
#include "WPrintSFML.hpp"

namespace octo
{
	template <class T>
	using CleanedType = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

	namespace details
	{
		template <class T>
		T		fromStringImp(std::wstring const& str)
		{
			std::wistringstream	iss;
			T					value;

			iss.setf(std::ios_base::boolalpha);
			iss.str(str);
			iss >> value;
			return (value);
		}

		template <>
		std::wstring	fromStringImp(std::wstring const& str);

		template <>
		std::string		fromStringImp(std::wstring const& str);

		template <class T>
		std::wstring	toStringImp(T const& value)
		{
			std::wostringstream	oss;

			oss.setf(std::ios_base::boolalpha);
			oss << value;
			return (oss.str());
		}

		template <>
		std::wstring	toStringImp(std::wstring const& value);

		template <>
		std::wstring	toStringImp(std::string const& value);

		template <std::size_t I, std::size_t N>
		struct	ArgumentChecker
		{
			template <class ... A>
			static void	check(std::vector<std::wstring> const& arguments)
			{
				typedef std::tuple<A...>							Tuple;
				typedef typename std::tuple_element<I, Tuple>::type	CurrentType;
				std::wistringstream									iss;
				CleanedType<CurrentType>							value;

				value = details::fromStringImp<decltype(value)>(arguments[I]);
				if (iss.fail() == false && iss.bad() == false)
					return (ArgumentChecker<I + 1, N>::template check<A...>(arguments));
				else
					throw ConsoleInterpreter::ArgumentTypeException(I, details::GetTypeName<CleanedType<CurrentType>>::Value);
			}
		};

		template <std::size_t I>
		struct	ArgumentChecker<I, I>
		{
			template <class ... A>
			static void	check(std::vector<std::wstring> const&)
			{
			}
		};
	}

	//
	//	AbstractCallable
	//
	class ConsoleInterpreter::AbstractCallable
	{
	protected:
		template <class ... A>
		static void				checkArguments(std::vector<std::wstring> const& arguments)
		{
			if (sizeof...(A) == arguments.size())
			{
				details::ArgumentChecker<0u, sizeof ... (A)>::template check<A...>(arguments);
			}
			else
			{
				throw ConsoleInterpreter::NotEnoughArgumentException();
			}
		}

		template <class T, class ... A>
		static CleanedType<T>	fromString(std::vector<std::wstring> const& arguments)
		{
			return (details::fromStringImp<CleanedType<T>>(arguments[details::IndexOf<T, A...>::Value]));
		}
	public:
		virtual ~AbstractCallable(){};
		virtual std::wstring	call(std::vector<std::wstring> const& arguments) = 0;
	};

	//
	//	Callable
	//
	template <class R, class ... A>
	class ConsoleInterpreter::Callable : public AbstractCallable
	{
		typedef R(*Function)(A...);
	public:
		explicit Callable(Function function) :
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments)
		{
			std::wstring	result;

			checkArguments<A...>(arguments);
			R	resultValue = (*m_function)(fromString<A, A...>(arguments)...);
			result = details::toStringImp(resultValue);
			return (result);
		}
	private:
		Function	m_function;
	};

	//
	//	Callable without result
	//
	template <class ... A>
	class ConsoleInterpreter::Callable<void, A...> : public AbstractCallable
	{
		typedef	void(*Function)(A...);
	public:
		explicit Callable(Function function) :
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments)
		{
			checkArguments<A...>(arguments);
			(*m_function)(fromString<A, A...>(arguments)...);
			return (L"");
		}
	private:
		Function	m_function;
	};

	//
	//	Member
	//
	template <class C, class R, class ... A>
	class ConsoleInterpreter::CallableMem : public AbstractCallable
	{
		typedef R(C::*Function)(A...);
	public:
		explicit CallableMem(C* object, Function function) :
			m_object(object),
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments)
		{
			std::wstring	result;

			checkArguments<A...>(arguments);
			R	resultValue = (m_object->*m_function)(fromString<A, A...>(arguments)...);
			result = details::toStringImp(resultValue);
			return (result);
		}
	private:
		C*			m_object;
		Function	m_function;
	};

	//
	//	Member without result
	//
	template <class C, class ... A>
	class ConsoleInterpreter::CallableMem<C, void, A...> : public AbstractCallable
	{
		typedef void(C::*Function)(A...);
	public:
		explicit CallableMem(C* object, Function function) :
			m_object(object),
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments)
		{
			checkArguments<A...>(arguments);
			(m_object->*m_function)(fromString<A, A...>(arguments)...);
			return (L"");
		}
	private:
		C*			m_object;
		Function	m_function;
	};

	//
	//	Member const
	//
	template <class C, class R, class ... A>
	class ConsoleInterpreter::CallableMemConst : public AbstractCallable
	{
		typedef R(C::*Function)(A...)const;
	public:
		explicit CallableMemConst(C const* object, Function function) :
			m_object(object),
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments)
		{
			std::wstring	result;

			checkArguments<A...>(arguments);
			R	resultValue = (m_object->*m_function)(fromString<A, A...>(arguments)...);
			result = details::toStringImp(resultValue);
			return (result);
		}
	private:
		C const*	m_object;
		Function	m_function;
	};

	//
	//	Member const without result
	//
	template <class C, class ... A>
	class ConsoleInterpreter::CallableMemConst<C, void, A...> : public AbstractCallable
	{
		typedef void(C::*Function)(A...)const;
	public:
		explicit CallableMemConst(C const* object, Function function) :
			m_object(object),
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments)
		{
			checkArguments<A...>(arguments);
			(m_object->*m_function)(fromString<A, A...>(arguments)...);
			return (L"");
		}
	private:
		C const*	m_object;
		Function	m_function;
	};

	//
	//	Functor
	//
	template <class C, class R, class ... A>
	class ConsoleInterpreter::CallableFunctor : public AbstractCallable
	{
		typedef R(C::*Function)(A...);
	public:
		explicit CallableFunctor(C object, Function function) :
			m_object(object),
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments)
		{
			std::wstring	result;

			checkArguments<A...>(arguments);
			R	resultValue = (m_object.*m_function)(fromString<A, A...>(arguments)...);
			result = details::toStringImp(resultValue);
			return (result);
		}
	private:
		C			m_object;
		Function	m_function;
	};

	//
	//	Functor without result
	//
	template <class C, class ... A>
	class ConsoleInterpreter::CallableFunctor<C, void, A...> : public AbstractCallable
	{
		typedef void(C::*Function)(A...);
	public:
		explicit CallableFunctor(C object, Function function) :
			m_object(object),
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments)
		{
			checkArguments<A...>(arguments);
			(m_object.*m_function)(fromString<A, A...>(arguments)...);
			return (L"");
		}
	private:
		C			m_object;
		Function	m_function;
	};

	//
	//	Constant functor
	//
	template <class C, class R, class ... A>
	class ConsoleInterpreter::CallableConstFunctor : public AbstractCallable
	{
		typedef R(C::*Function)(A...)const;
	public:
		explicit CallableConstFunctor(C object, Function function) :
			m_object(object),
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments)
		{
			std::wstring	result;

			checkArguments<A...>(arguments);
			R	resultValue = (m_object.*m_function)(fromString<A, A...>(arguments)...);
			result = details::toStringImp(resultValue);
			return (result);
		}
	private:
		C const		m_object;
		Function	m_function;
	};

	//
	//	Constant functor without result
	//
	template <class C, class ... A>
	class ConsoleInterpreter::CallableConstFunctor<C, void, A...> : public AbstractCallable
	{
		typedef void(C::*Function)(A...)const;
	public:
		explicit CallableConstFunctor(C object, Function function) :
			m_object(object),
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments)
		{
			checkArguments<A...>(arguments);
			(m_object.*m_function)(fromString<A, A...>(arguments)...);
			return (L"");
		}
	private:
		C			m_object;
		Function	m_function;
	};

	template <class R, class ... A>
	void	ConsoleInterpreter::addCommand(std::wstring const& name, R(*function)(A...))
	{
		if (m_callables.find(name) != m_callables.end())
			std::wcout << "Warning: command " << name << " replaced" << std::endl;
		m_callables[name] = std::make_shared<Callable<R, A...>>(function);	
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addCommand(std::wstring const& name, C& instance, R(C::*function)(A...))
	{
		if (m_callables.find(name) != m_callables.end())
			std::wcout << "Warning: command " << name << " replaced" << std::endl;
		m_callables[name] = std::make_shared<CallableMem<C, R, A...>>(&instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addCommand(std::wstring const& name, C* instance, R(C::*function)(A...))
	{
		if (m_callables.find(name) != m_callables.end())
			std::wcout << "Warning: command " << name << " replaced" << std::endl;
		m_callables[name] = std::make_shared<CallableMem<C, R, A...>>(instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addCommand(std::wstring const& name, C const& instance, R(C::*function)(A...)const)
	{
		if (m_callables.find(name) != m_callables.end())
			std::wcout << "Warning: command " << name << " replaced" << std::endl;
		m_callables[name] = std::make_shared<CallableMemConst<C, R, A...>>(&instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addCommand(std::wstring const& name, C const* instance, R(C::*function)(A...)const)
	{
		if (m_callables.find(name) != m_callables.end())
			std::wcout << "Warning: command " << name << " replaced" << std::endl;
		m_callables[name] = std::make_shared<CallableMemConst<C, R, A...>>(instance, function);
	}

	template <class F>
	void	ConsoleInterpreter::addCommand(std::wstring const& name, F functor)
	{
		if (m_callables.find(name) != m_callables.end())
			std::wcout << "Warning: command " << name << " replaced" << std::endl;
		addFunctor(name, functor, &F::operator());
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addFunctor(std::wstring const& name, C instance, R(C::*function)(A...))
	{
		if (m_callables.find(name) != m_callables.end())
			std::wcout << "Warning: command " << name << " replaced" << std::endl;
		m_callables[name] = std::make_shared<CallableFunctor<C, R, A...>>(instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addFunctor(std::wstring const& name, C instance, R(C::*function)(A...)const)
	{
		if (m_callables.find(name) != m_callables.end())
			std::wcout << "Warning: command " << name << " replaced" << std::endl;
		m_callables[name] = std::make_shared<CallableConstFunctor<C, R, A...>>(instance, function);
	}
}
