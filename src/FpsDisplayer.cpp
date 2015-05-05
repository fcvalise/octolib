/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FpsDisplayer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 02:36:54 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/05 19:22:04 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FpsDisplayer.hpp"
#include "IColorProvider.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace octo
{
	namespace
	{
		inline void appendQuad(float x, float y, float w, float h,
							   sf::Color const &color,
							   std::size_t& index,
						       sf::Vertex* vertices)
		{
			sf::Vertex      leftTop(sf::Vector2f(x, y), color);
			sf::Vertex      rightTop(sf::Vector2f(x + w, y), color);
			sf::Vertex      rightBottom(sf::Vector2f(x + w, y + h), color);
			sf::Vertex      leftBottom(sf::Vector2f(x, y + h), color);

			vertices[index + 0u] = leftTop;
			vertices[index + 1u] = rightTop;
			vertices[index + 2u] = rightBottom;
			vertices[index + 3u] = leftBottom;
			index += 4u;
		}
	}

	FpsDisplayer::FpsDisplayer(sf::Font const* font, unsigned int fontSize, IColorProvider const* colors, std::size_t maxSamples) :
		octo::AbstractFpsDisplayer(maxSamples),
		m_text(sf::String(), *font, fontSize),
		m_size(128.f, 128.f),
		m_vertices(new sf::Vertex[(maxSamples + 1) * 4u]),
		m_count(0),
		m_colors(colors),
		m_visible(true)
	{
		appendQuad(0.f, 0.f, m_size.x, m_size.y, m_colors->getColor(BackgroundColor),
				   m_count, m_vertices.get());
		m_text.setPosition(4.f, m_size.y);
	}

	void	FpsDisplayer::setVisible(bool visible)
	{
		m_visible = visible;
	}

	void	FpsDisplayer::update(sf::View const& view)
	{
		sf::Vector2f	pos	= view.getCenter() - (view.getSize() / 2.f);

		setPosition(pos);
	}

	void	FpsDisplayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_visible == false)
			return;
		states.transform = getTransform();
		target.draw(m_vertices.get(), m_count, sf::Quads, states);
		target.draw(m_text, states);
	}

	void	FpsDisplayer::updateDisplay(octo::RingBuffer<unsigned int> const& samples,
										unsigned int maxFrameCount)
	{
		float			sampleHeight = 0.f;
		float			sampleWidth = m_size.x / getMaxSamples();
		float			samplePosX = sampleWidth * (getMaxSamples() - samples.size());
		float			samplePosY = 0;
		float			maxSample = static_cast<float>(maxFrameCount);

		m_text.setString(sf::String("FPS: " + std::to_string(getLastSample()) +
									"\nAVG: " + std::to_string(getAverage())));
		m_count = 0;
		appendQuad(0.f, 0.f, m_size.x,
				   m_size.y + m_text.getGlobalBounds().height + 10.f, m_colors->getColor(BackgroundColor),
				   m_count, m_vertices.get());
		for (std::size_t i = 0; i < samples.size(); ++i)
		{
			sampleHeight = (samples[i] / maxSample) * m_size.y;
			samplePosY = m_size.y - sampleHeight;
			appendQuad(samplePosX, samplePosY, sampleWidth - 2.f, sampleHeight,
					   m_colors->getColor((samples[i] < 60) ? AlertBarColor : BarColor),
					   m_count,
					   m_vertices.get());
			samplePosX += sampleWidth;
		}
	}
}
