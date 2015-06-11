/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GenericFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 04:31:43 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/11 12:07:19 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <GenericFactory.hpp>

#include <iterator>
#include <array>

BOOST_AUTO_TEST_SUITE( generic_factory )

class ATest
{
public:
	explicit ATest(int value, int const cvalue, int const& crvalue, int&& mvalue) :
		m_value0(value),
		m_value1(cvalue),
		m_value2(crvalue),
		m_value3(mvalue)
	{}

	virtual ~ATest(){}

	virtual char get()const = 0;
	int			getValue0()const{return (m_value0);}
	int			getValue1()const{return (m_value1);}
	int			getValue2()const{return (m_value2);}
	int			getValue3()const{return (m_value3);}
private:
	int	m_value0;
	int	m_value1;
	int	m_value2;
	int	m_value3;
};

class TestA : public ATest
{
public:
	TestA(int value, int const cvalue, int const& crvalue, int&& mvalue) :
		ATest(value, cvalue, crvalue, std::forward<int>(mvalue))
	{
	}

	virtual char get()const
	{
		return ('A');
	}
};

class TestB : public ATest
{
public:
	TestB(int value, int const cvalue, int const& crvalue, int&& mvalue) :
		ATest(value, cvalue, crvalue, std::forward<int>(mvalue))
	{
	}

	virtual char get()const
	{
		return ('B');
	}
};

class TestC : public ATest
{
public:
	TestC(int value, int const cvalue, int const& crvalue, int&& mvalue) :
		ATest(value, cvalue, crvalue, std::forward<int>(mvalue))
	{
	}

	virtual char get()const
	{
		return ('C');
	}
};

BOOST_AUTO_TEST_CASE( register_ctor )
{
	octo::GenericFactory<char, ATest, int, int const, int const&, int&&>	factory;

	factory.template registerCreator<TestA>('A');	
	factory.template registerCreator<TestB>('B');	
	factory.template registerCreator<TestC>('C');	
}

BOOST_AUTO_TEST_CASE( instanciate )
{
	octo::GenericFactory<char, ATest, int, int const, int const&, int&&>	factory;
	std::array<ATest*, 3>				instances;
	int										value = 1234;

	factory.template registerCreator<TestA>('A');	
	factory.template registerCreator<TestB>('B');	
	factory.template registerCreator<TestC>('C');

	instances[0] = factory.create('A', value, value, value, 12);
	instances[1] = factory.create('B', value, value, value, 12);
	instances[2] = factory.create('C', value, value, value, 12);
	BOOST_CHECK_EQUAL( instances[0]->get(), 'A' );
	BOOST_CHECK_EQUAL( instances[1]->get(), 'B' );
	BOOST_CHECK_EQUAL( instances[2]->get(), 'C' );
	for (auto* ptr : instances)
		delete ptr;
}

BOOST_AUTO_TEST_SUITE_END()
