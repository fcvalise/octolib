/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleInterpreter.hxx                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/05 15:01:38 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/10 17:56:25 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

		template <std::size_t I, std::size_t N>
		struct	ArgumentChecker
		{
			template <class ... A>
			static bool	check(std::vector<std::wstring> const& arguments)
			{
				typedef std::tuple<A...>							Tuple;
				typedef typename std::tuple_element<I, Tuple>::type	CurrentType;
				std::wistringstream									iss;
				CleanedType<CurrentType>							value;

				iss.setf(std::ios_base::boolalpha);
				iss.str(arguments[I]);
				if (iss >> value)
					return (ArgumentChecker<I + 1, N>::template check<A...>(arguments));
				else
					return (false);
			}
		};

		template <std::size_t I>
		struct	ArgumentChecker<I, I>
		{
			template <class ... A>
			static bool	check(std::vector<std::wstring> const&)
			{
				return (true);
			}
		};
	}

	class ConsoleInterpreter::AbstractCallable
	{
	protected:
		template <class ... A>
		static bool				checkArguments(std::vector<std::wstring> const& arguments)
		{
			if (sizeof...(A) == arguments.size())
			{
				return (details::ArgumentChecker<0u, sizeof ... (A)>::template check<A...>(arguments));	
			}
			else
			{
				return (false);
			}
		}

		template <class T, class ... A>
		static CleanedType<T>	fromString(std::vector<std::wstring> const& arguments)
		{
			return (details::fromStringImp<CleanedType<T>>(arguments[details::IndexOf<T, A...>::Value]));
		}

	public:
		virtual ~AbstractCallable(){};
		virtual std::wstring	call(std::vector<std::wstring> const& arguments, bool& ok) = 0;
	};

	template <class R, class ... A>
	class ConsoleInterpreter::Callable : public AbstractCallable
	{
		typedef R(*Function)(A...);
	public:
		explicit Callable(Function function) :
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments, bool &ok)
		{
			std::wstring	result;
			R				resultValue;

			if (checkArguments<A...>(arguments))
			{
				resultValue = (*m_function)(fromString<A, A...>(arguments)...);
				result = details::toStringImp(resultValue);
				ok = true;
			}
			else
			{
				ok = false;
			}
			return (result);
		}
	private:
		Function	m_function;
	};

	template <class ... A>
	class ConsoleInterpreter::Callable<void, A...> : public AbstractCallable
	{
		typedef	void(*Function)(A...);
	public:
		explicit Callable(Function function) :
			m_function(function)
		{
		}

		virtual std::wstring	call(std::vector<std::wstring> const& arguments, bool &ok)
		{
			if (checkArguments<A...>(arguments))
			{
				(*m_function)(fromString<A, A...>(arguments)...);
				ok = true;
			}
			else
			{
				ok = false;
			}
			return (L"");
		}
	private:
		Function	m_function;
	};

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

		virtual std::wstring	call(std::vector<std::wstring> const& arguments, bool &ok)
		{
			std::wstring	result;
			R				resultValue;

			if (checkArguments<A...>(arguments))
			{
				resultValue = (m_object->*m_function)(fromString<A, A...>(arguments)...);
				result = details::toStringImp(resultValue);
				ok = true;
			}
			else
			{
				ok = false;
			}
			return (result);
		}
	private:
		C*			m_object;
		Function	m_function;
	};

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

		virtual std::wstring	call(std::vector<std::wstring> const& arguments, bool &ok)
		{
			if (checkArguments<A...>(arguments))
			{
				(m_object->*m_function)(fromString<A, A...>(arguments)...);
				ok = true;
			}
			else
			{
				ok = false;
			}
			return (L"");
		}
	private:
		C*			m_object;
		Function	m_function;
	};

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

		virtual std::wstring	call(std::vector<std::wstring> const& arguments, bool &ok)
		{
			if (checkArguments<A...>(arguments))
			{
				(m_object->*m_function)(fromString<A, A...>(arguments)...);
				ok = true;
			}
			else
			{
				ok = false;
			}
			return (L"");
		}
	private:
		C const*	m_object;
		Function	m_function;
	};

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

		virtual std::wstring	call(std::vector<std::wstring> const& arguments, bool &ok)
		{
			std::wstring	result;
			R				resultValue;

			if (checkArguments<A...>(arguments))
			{
				resultValue = (m_object.*m_function)(fromString<A, A...>(arguments)...);
				result = details::toStringImp(resultValue);
				ok = true;
			}
			else
			{
				ok = false;
			}
			return (result);
		}
	private:
		C			m_object;
		Function	m_function;
	};

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

		virtual std::wstring	call(std::vector<std::wstring> const& arguments, bool &ok)
		{
			std::wstring	result;
			R				resultValue;

			if (checkArguments<A...>(arguments))
			{
				resultValue = (m_object.*m_function)(fromString<A, A...>(arguments)...);
				result = details::toStringImp(resultValue);
				ok = true;
			}
			else
			{
				ok = false;
			}
			return (result);
		}
	private:
		C			m_object;
		Function	m_function;
	};

	template <class R, class ... A>
	void	ConsoleInterpreter::addFunction(std::wstring const& name, R(*function)(A...))
	{
		m_callables[name] = std::make_shared<Callable<R, A...>>(function);	
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addFunction(std::wstring const& name, C& instance, R(C::*function)(A...))
	{
		m_callables[name] = std::make_shared<CallableMem<C, R, A...>>(&instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addFunction(std::wstring const& name, C* instance, R(C::*function)(A...))
	{
		m_callables[name] = std::make_shared<CallableMem<C, R, A...>>(instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addFunction(std::wstring const& name, C const& instance, R(C::*function)(A...)const)
	{
		m_callables[name] = std::make_shared<CallableMemConst<C, R, A...>>(&instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addFunction(std::wstring const& name, C const* instance, R(C::*function)(A...)const)
	{
		m_callables[name] = std::make_shared<CallableMemConst<C, R, A...>>(instance, function);
	}

	template <class F>
	void	ConsoleInterpreter::addFunction(std::wstring const& name, F&& functor)
	{
		addFunctor(name, functor, &F::operator());
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addFunctor(std::wstring const& name, C instance, R(C::*function)(A...))
	{
		m_callables[name] = std::make_shared<CallableFunctor<C, R, A...>>(instance, function);
	}

	template <class C, class R, class ... A>
	void	ConsoleInterpreter::addFunctor(std::wstring const& name, C instance, R(C::*function)(A...)const)
	{
		m_callables[name] = std::make_shared<CallableConstFunctor<C, R, A...>>(instance, function);
	}
}
