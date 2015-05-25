/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Console.hxx                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 18:32:18 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/25 23:02:00 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	/*!	Register a free function
	 *
	 *	\code
	 *
	 *	double	foo(int param){ ... }
	 *
	 *	...
	 *
	 *	// Register foo
	 *	console.addCommand(L"foo", &foo);
	 *	\endcode
	 */
	template <class R, class ... A>
	void	Console::addCommand(std::wstring const& name, R(*function)(A...))
	{
		m_core.addCommand(name, function);
	}

	/*!	Register a member function
	 *
	 *	\code
	 *	struct Foo
	 *	{
	 *		double	bar(int param){ ... }
	 *	};
	 *
	 *	...
	 *
	 *	Foo	fooInstance;
	 *
	 *	// Register Foo::bar()
	 *	console.addCommand(L"foobar", fooInstance, &bar);
	 *	\endcode
	 */
	template <class C, class R, class ... A>
	void	Console::addCommand(std::wstring const& name, C& instance, R(C::*function)(A...))
	{
		m_core.addCommand(name, instance, function);
	}

	/*!	Register a member function
	 *
	 *	\code
	 *	struct Foo
	 *	{
	 *		double	bar(int param){ ... }
	 *	};
	 *
	 *	...
	 *
	 *	Foo*	fooInstance = new Foo;
	 *
	 *	// Register Foo::bar()
	 *	console.addCommand(L"foobar", fooInstance, &bar);
	 *	\endcode
	 */
	template <class C, class R, class ... A>
	void	Console::addCommand(std::wstring const& name, C* instance, R(C::*function)(A...))
	{
		m_core.addCommand(name, instance, function);
	}

	/*!	Register a constant member function
	 *
	 *	\code
	 *	struct Foo
	 *	{
	 *		double	bar(int param)const{ ... }
	 *	};
	 *
	 *	...
	 *
	 *	Foo	const	fooInstance;
	 *
	 *	// Register Foo::bar()
	 *	console.addCommand(L"foobar", fooInstance, &bar);
	 *	\endcode
	 */
	template <class C, class R, class ... A>
	void	Console::addCommand(std::wstring const& name, C const& instance, R(C::*function)(A...)const)
	{
		m_core.addCommand(name, instance, function);
	}

	/*!	Register a constant member function
	 *
	 *	\code
	 *	struct Foo
	 *	{
	 *		double	bar(int param)const{ ... }
	 *	};
	 *
	 *	...
	 *
	 *	Foo const*	fooInstance = new Foo;
	 *
	 *	// Register Foo::bar()
	 *	console.addCommand(L"foobar", fooInstance, &bar);
	 *	\endcode
	 */
	template <class C, class R, class ... A>
	void	Console::addCommand(std::wstring const& name, C const* instance, R(C::*function)(A...)const)
	{
		m_core.addCommand(name, instance, function);
	}

	/*!	Register a functor or a lambda function
	 *
	 *	\code
	 *	struct Foo
	 *	{
	 *		double	operator()(int param){ ... }
	 *	};
	 *
	 *	...
	 *
	 *	// Register a functor
	 *	console.addCommand(L"foobar", Foo());
	 *
	 *	// Register a lambda
	 *	console.addCommand(L"lambdalala", [](int, double){ ... });
	 *	\endcode
	 */
	template <class F>
	void	Console::addCommand(std::wstring const& name, F&& functor)
	{
		m_core.addCommand(name, functor);
	}
}
