/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 21:55:42 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/17 19:49:34 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Math.hpp"

namespace octo
{
	float	cosLPA(float x)
	{
		x += 1.57079632f;
		if (x >  3.14159265f)
			x -= 6.28318531f;
		if (x < 0)
			 return (1.27323954f * x + 0.405284735f * x * x);
		else
			return (1.27323954f * x - 0.405284735f * x * x);
	}

	float	cosHPA(float x)
	{
		static float	result = 0.f;

		x += 1.57079632f;
		if (x > 3.14159265f)
			x -= 6.28318531f;
		if (x < 0.f)
		{
			result = 1.27323954f * x + 0.405284735f * x * x;
			if (result < 0.f)
				return (.225f * (result * -result - result) + result);
			else
				return (.225f * (result * result - result) + result);
		}
		else
		{
			result = 1.27323954f * x - 0.405284735f * x * x;
			if (result < 0.f)
				return (.225f * (result * -result - result) + result);
			else
				return (.225f * (result * result - result) + result);
		}
	}
}
