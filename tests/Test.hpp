#ifndef TEST_HPP
# define TEST_HPP
# include "Array3D.hpp"

class Test
{
	public:
		Test(int x, int y, int z);
		octo::Array3D<int>const &			getArray() const{
			return m_array;
		};
	private:
		octo::Array3D<int>	m_array;
};

#endif
