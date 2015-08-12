/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystem.hxx                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/19 00:55:39 by irabeson          #+#    #+#             */
/*   Updated: 2015/08/12 17:00:50 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>

namespace octo
{
	//
	//	ParticleSystem
	//
	template <class ... C>
	ParticleSystem<C...>::ParticleSystem() :
		m_particleCount(0u),
		m_primitiveType(sf::Triangles),
		m_maxParticleCount(0u),
		m_texture(nullptr)
	{
	}

	template <class ... C>
	void	ParticleSystem<C...>::reset(Prototype const& prototype,
										 sf::PrimitiveType type,
										 std::size_t maxParticleCount)
	{
		m_prototype = prototype;
		m_primitiveType = type;
		m_particles.reset(new Particle[maxParticleCount]);
		m_vertices.reset(new sf::Vertex[maxParticleCount * m_prototype.size()]);
		m_builder = VertexBuilder(m_vertices.get(), maxParticleCount * m_prototype.size());
		m_maxParticleCount = maxParticleCount;
		m_particleCount = 0u;
	}

	template <class ... C>
	void	ParticleSystem<C...>::setTexture(sf::Texture const& texture)
	{
		m_texture = &texture;
	}

	template <class ... C>
	void	ParticleSystem<C...>::add(Particle const& particle)
	{
		m_particles[m_particleCount] = particle;
		++m_particleCount;
	}

	template <class ... C>
	void	ParticleSystem<C...>::add(Particle&& particle)
	{
		m_particles[m_particleCount] = std::move(particle);
		++m_particleCount;
	}

	template <class ... C>
	template <class ... T>
	void	ParticleSystem<C...>::emplace(T&& ... args)
	{
		m_particles[m_particleCount] = Particle(std::forward<T>(args)...);
		++m_particleCount;
	}

	template <class ... C>
	void	ParticleSystem<C...>::clear()
	{
		m_particleCount = 0u;
	}

	template <class ... C>
	std::size_t	ParticleSystem<C...>::getCapacity()const
	{
		return (m_maxParticleCount - m_particleCount);
	}

	template <class ... C>
	std::size_t	ParticleSystem<C...>::getCount()const
	{
		return (m_particleCount);
	}

	template <class ... C>
	void	ParticleSystem<C...>::update(sf::Time frameTime)
	{
		sf::Transform	transform;
		auto			it = std::remove_if(m_particles.get(), m_particles.get() + m_particleCount, 
										 	[this](Particle const& p)
										 	{
												return (this->isDeadParticle(p));
										 	});

		m_particleCount = std::distance(m_particles.get(), it);
		m_builder.clear();
		for (std::size_t i = 0u; i < m_particleCount; ++i)
		{
			Particle&	particle = m_particles[i];

			updateParticle(frameTime, particle);
			transform = sf::Transform::Identity;
			transform.translate(std::get<Component::Position>(particle));
			transform.rotate(std::get<Component::Rotation>(particle));
			transform.scale(std::get<Component::Scale>(particle));
			for (auto vertex : m_prototype)
			{
				vertex.color = std::get<Component::Color>(particle);
				vertex.position = transform * vertex.position;
				m_builder.createVertex(std::move(vertex));
			}
		}
	}

	template <class ... C>
	void	ParticleSystem<C...>::draw(sf::RenderTarget& render, sf::RenderStates states)const
	{
		states.transform *= getTransform();
		states.texture = m_texture;
		render.draw(m_vertices.get(), m_builder.getUsed(), m_primitiveType, states);
	}
}
