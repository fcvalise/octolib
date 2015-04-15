/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BSpline.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/29 13:07:36 by irabeson          #+#    #+#             */
/*   Updated: 2015/04/15 11:50:18 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSPLINE_HPP
# define BSPLINE_HPP
# include <SFML/System/Vector2.hpp>
# include <deque>
# include <Math.hpp>

class BSpline
{
	static sf::Vector2f	bspline(sf::Vector2f const& p0,
								sf::Vector2f const& p1,
								sf::Vector2f const& p2,
								sf::Vector2f const& p3,
								float t)
	{
		sf::Vector2f	result;

		result.x =	(1.f / 6.f) * (octo::pow<3>(1.f - t) * p0.x +
					((3.f * octo::pow<3>(t) - 6.f * octo::pow<2>(t) + 4.f) * p1.x) +
					((-3.f * octo::pow<3>(t) + 3.f * octo::pow<2>(t) + (3.f * t) + 1.f) * p2.x) +
					octo::pow<3>(t) * p3.x);
		result.y =	(1.f / 6.f) * (octo::pow<3>(1.f - t) * p0.y +
					((3.f * octo::pow<3>(t) - 6.f * octo::pow<2>(t) + 4.f) * p1.y) +
					((-3.f * octo::pow<3>(t) + 3.f * octo::pow<2>(t) + (3.f * t) + 1.f) * p2.y) +
					octo::pow<3>(t) * p3.y);
		return (result);
	}
public:
	typedef typename std::deque<sf::Vector2f>::iterator				iterator;
	typedef typename std::deque<sf::Vector2f>::const_iterator		const_iterator;

	void	pushFront(sf::Vector2f const& position)
	{
		m_points.push_front(position);
	}

	void	pushBack(sf::Vector2f const& position)
	{
		m_points.push_back(position);
	}

	void	popFront()
	{
		m_points.pop_front();
	}

	void	popBack()
	{
		m_points.pop_back();
	}

	sf::Vector2f	compute(float t)const
	{
		int					intIndex = static_cast<int>(t);
		float				floatIndex = t - intIndex;
		sf::Vector2f const&	p0 = getPoint(intIndex);
		sf::Vector2f const&	p1 = getPoint(intIndex + 1);
		sf::Vector2f const&	p2 = getPoint(intIndex + 2);
		sf::Vector2f const&	p3 = getPoint(intIndex + 3);
		
		return (bspline(p0, p1, p2, p3, floatIndex));
	}

	float				maxT()const
	{
		return (m_points.size());
	}

	sf::Vector2f&		operator[](std::size_t i)
	{
		return (m_points[i]);
	}

	sf::Vector2f const&	operator[](std::size_t i)const
	{
		return (m_points[i]);
	}

	std::size_t	size()const
	{
		return (m_points.size());
	}

	iterator	begin()
	{
		return (m_points.begin());
	}

	iterator	end()
	{
		return (m_points.end());
	}

	const_iterator	begin()const
	{
		return (m_points.begin());
	}

	const_iterator	end()const
	{
		return (m_points.end());
	}

	const_iterator	cbegin()const
	{
		return (m_points.begin());
	}

	const_iterator	cend()const
	{
		return (m_points.end());
	}
private:
	sf::Vector2f const&	getPoint(int i)const
	{
		int			count = static_cast<int>(m_points.size());

		if (i <= 0)
			return (m_points.front());
		else if (i >= count)
			return (m_points.back());
		else
			return (m_points[i]);
	}
private:
	std::deque<sf::Vector2f>	m_points;
	sf::Vector2f				m_beforeBeginPoint;
	sf::Vector2f				m_afterEndPoint;
};

#endif
