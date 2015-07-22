/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystem.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/18 21:36:14 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/24 02:06:09 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICLESYSTEM_HPP
# define PARTICLESYSTEM_HPP
# include <SFML/Graphics/Drawable.hpp>
# include <SFML/Graphics/Transformable.hpp>
# include <SFML/Graphics/Vertex.hpp>
# include <SFML/Graphics/PrimitiveType.hpp>
# include <SFML/System/Time.hpp>

# include <functional>
# include <list>
# include <tuple>
# include <memory>

# include <VertexBuilder.hpp>

namespace octo
{
	/*!	\ingroup Graphics
	 *	\class ParticleSystem
	 *	\brief Bases for a particle system
	 *	\tparam C Custom components list
	 *
	 *	<h1>Particle is an entity</h1>
	 *	Particle management is based on Entity Component System pattern (ECS).<br>
	 *	A particle is an entity and you can define at compile time the list
	 *	of theses components.
	 *
	 *	\see <a href="https://en.wikipedia.org/wiki/Entity_component_system">Entity Component System at wikpidia</a>
	 *
	 *	<h1>Define a particle prototype</h1>
	 *	The particle prototype defines the positions and the number of vertices for each particles.<br>
	 *	For each position in the prototype will be created a vertex.<br>
	 *	When a particle is rendered, the prototype is used to creating vertices, then the vertices
	 *	are transformed with datas stored by the default components.<br>
	 *	The color of the vertices is controlled by the default color component.<br>
	 *	<h1>Add your own component</h1>
	 *	You can add variables to your own particles.<br>
	 *	To refer to your component, you must use the constant Component::User which is
	 *	the identifier of the first user component possible.
	 *
	 *	Exemple, you need to destroy particles after 2 seconds, you
	 *	can define a ParticleSystem as follow:
	 *	\code
	 *	// Here we put as template parameter of ParticleSystem 2 new variables
	 *	// of type MyOwnStuffData and MyNewStuffData
	 *	class YourParticleSystem : public octo::ParticleSystem<MyOwnStuffData, MyNewStuffData>
	 *	{
	 *		// Here we create an enum to defines the identifiers of
	 *		// our new components.
	 *		enum MyComponents
	 *		{
	 *			MyOwnStuff = User,
	 *			MyNewStuff	// This will be equal to User + 1, easy!
	 *		};
	 *	};
	 *	\endcode
	 *	The typedef Particle will be defined by the compiler as the following:
	 *	\code
	 *	typedef std::tuple<
	 *						sf::Color,		// The first default component, Component::Color
	 *						sf::Vector2f,	// The second default component, Component::Position
	 *						sf::Vector2f,	// The third default component, Component::Scale
	 *						float,			// The fourth default component, Component::Rotation
	 *					   	MyOwnStuffData,	// The first custom component
	 *						MyNewStuffData	// The second custom component
	 *						>	Particle;
	 *	\endcode
	 *	<h1>Update and kill your particles</h1>
	 *	Now we need particles with a time life defined.<br>
	 *	When a particle is too old, we delete it.<br>
	 *
	 *	We will create a new ParticleSystem and add an sf::Time as template parameter
	 *	of the ParticleSystem inerited by YourParticleSystem to stores the elapsed time.<br>
	 *	\code
	 *	class YourParticleSystem : public octo::ParticleSystem<sf::Time>
	 *	{
	 *		enum MyComponents
	 *		{
	 *			ElapsedTime = User
	 *		};
	 *	};
	 *	\endcode
	 *	Now we need to increase the time elapsed for each particles and kill particles which are
	 *	to old at each.<br>
	 *	Also, we need our particles moves at each frame.<br>
	 *	To to that, ParticleSystem provides two pure virtual methods, updateParticle() and
	 *	isDeadParticle() to defines your own behaviors.
	 *	
	 *	\code
	 *	class YourParticleSystem : public octo::ParticleSystem<sf::Time>
	 *	{
	 *	private:
	 *		// This method is called at each frame with each particle
	 *		virtual void	updateParticle(sf::Time frameTime, Particle& particle)
	 *		{
	 *			static sf::Vector2f const	Velocity(0.2f, 512.f);
	 *
	 *			// increase the life time
	 *			std::get<MyComponent::ElapsedTime>(particle) = std::get<MyComponent::ElapsedTime>(particle) + frameTime.asSeconds();
	 *			// move the particle
	 *			std::get<Component::Position>(particle) = std::get<Component::Position>(particle) + (Velocity * frameTime.asSeconds());
	 *		}
	 *
	 *		// This methods is called when the system is looking for dead particles
	 *		virtual bool	isDeadParticle(Particle const& particle)
	 *		{
	 *			// We check the time elapsed for each particles and return true
	 *			// if the particle is older than 2 seconds.
	 *			return (std::get<MyComponent::ElapsedTime>(particle) >= sf::second(2.f));
	 *		}
	 *	};
	 *	\endcode
	 *	
	 */
	template <class ... C>
	class ParticleSystem : public sf::Transformable
	{
	public:
		/*!	Particle shape prototype */
		typedef std::vector<sf::Vector2f>	Prototype;

		/*!	Type of the tuple which store each particle datas
		 *
		 *	By default each particle have at least:
		 *	<ul>
		 *	<li>a color</li>
		 *	<li>a position</li>
		 *	<li>a scale factor</li>
		 *	<li>a rotation angle (in degrees)</li>
		 */
		typedef std::tuple<sf::Color,
						   sf::Vector2f,
						   sf::Vector2f,
						   float,
						   C...>			Particle;

		/*!	Identify each default components */
		enum Component
		{
			/*!	Identifier of color component */
			Color = 0u,
			/*!	Identifier of position component */
			Position,
			/*!	Identifier of scale component */
			Scale,
			/*!	Identifier of rotation component */
			Rotation,
			/*!	First user identifier */
			User
		};

		/*!	Create a null system.
		 *
		 *	A null system has a capacity of 0.
		 *	A system require at least one call to reset() before usage.
		 *	\see reset()
		 *	\see getCapacity()
		 */
		ParticleSystem();

		/*!	Destroy the system and free all the memory used */
		virtual ~ParticleSystem() = default;

		/*!	Reset the system
		 *	\param prototype Point collection used to build particle prototype
		 *	\param type	Primitive type used to render particles
		 *	\param maxParticleCount Define the maximum of particles
		 *
		 *	Allocate the memory and prepare the system to run.<br>
		 *	All particles are destroyed when this methods is called.
		 */	 
		void			reset(Prototype const& prototype,
							  sf::PrimitiveType type,
							  std::size_t maxParticleCount);

		/*!	Add a new particle */
		void			add(Particle const& particle);

		/*!	Add a new particle */
		void			add(Particle&& particle);

		/*!	Emplace a new particle */
		template <class ... T>
		void			emplace(T&& ... args);

		/*!	Remove all particles */
		void			clear();

		/*!	Remove dead particles and updates alives particles */
		virtual void	update(sf::Time frameTime);

		virtual void	update(sf::Time frameTime, VertexBuilder & builder);

		/*!	Draw alives particles */
		void			draw(sf::RenderTarget& render, sf::RenderStates states = sf::RenderStates())const;

		/*!	Return the count of particles which can be created
		 *
		 *	The capacity is defined with reset().
		 */
		std::size_t		getCapacity()const;

		/*!	Return the count of alive particles */
		std::size_t		getCount()const;
	private:
		/*!	This methods is called each frame with each particle
		 *	\param frameTime Elapsed frame time
		 *	\param particle The particle tested
		 */
		virtual void	updateParticle(sf::Time frameTime, Particle& particle) = 0;

		/*!	This methods is called when the system removes the dead particles
		 *	\param particle The particle tested
		 *	\return true if particle is dead and must be removed from this system
		 */
		virtual bool	isDeadParticle(Particle const& particle) = 0;
	private:
		std::list<Particle>			m_particles;
		std::unique_ptr<sf::Vertex>	m_vertices;
		std::size_t					m_verticesCount;
		Prototype					m_prototype;
		sf::PrimitiveType			m_primitiveType;
		VertexBuilder				m_builder;
		std::size_t					m_maxParticleCount;
	};
}

#include "ParticleSystem.hxx"
#endif
