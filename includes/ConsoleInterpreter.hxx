/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleInterpreter.hxx                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/05 15:01:38 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/05 15:04:25 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	namespace details
	{
		template <class T>
		T		fromStringImp(std::wstring const& str)
		{
			std::wistringstream	iss;
			T					value;

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

			oss << value;
			return (oss.str());
		}

		template <>
		std::wstring	toStringImp(std::wstring const& value);
	}

	class ConsoleInterpreter::AbstractCallable
	{
	protected:
		template <class ... A>
		static bool				checkArguments(std::vector<std::wstring> const& arguments)
		{
			return (sizeof...(A) == arguments.size());
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
		C const*	m_object;
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
}
