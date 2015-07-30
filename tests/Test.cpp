#include "test.hpp"

Test::Test(int x, int y, int z)
{
	m_array.resize(x, y, z);
	int x2;
	int y2;
	int z2 = 0;
	while (z2 < z){
		x2 = 0;
		while (x2 < x){
			y2 = 0;
			while (y2 < y){
				m_array.set(x2, y2 , z2, z2);
				y2++;
			}
			x2++;
		}
		z2++;
	}
}
