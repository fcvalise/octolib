/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BspTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 08:32:01 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 05:30:38 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSPTREE_HPP
# define BSPTREE_HPP
# include <memory>
# include <functional>

# include <SFML/System/Vector2.hpp>

namespace octo
{
	class BspNode;
	class Segment;
	class Collision;
	class BinaryOutputStream;
	class BinaryInputStream;

	class BspTree
	{
		typedef std::shared_ptr<BspNode>			NodePtr;
	public:
		enum class VisitorMode : unsigned short
		{
			Infix,
			Prefix,
			Postfix
		};

		typedef std::function<void(BspNode*)>		Visitor;
		typedef std::function<void(BspNode const*)>	ConstVisitor;

		explicit BspTree(BspNode* root = nullptr);

		void			reset(BspNode* root = nullptr);
		void			write(std::ostream& os)const;
		void			read(std::istream& is);
		void			writeToMemory(BinaryOutputStream& os)const;
		void			readFromMemory(BinaryInputStream& is);

		BspNode const*	nodeAt(sf::Vector2f const& pos)const;
		bool			segmentHitTest(Segment const& segment, Collision& collision)const;

		bool			empty()const;
		BspNode*		root();
		BspNode const*	root()const;

		template <VisitorMode M, class V>
		void			visit(V& visitor);

		template <VisitorMode M, class V>
		void			visit(V& visitor)const;

		template <VisitorMode M, class V>
		void			forEach(V visitor);

		template <VisitorMode M, class V>
		void			forEach(V visitor)const;

	private:
		template <class N, class V, VisitorMode M>
		struct	VisitorPolicy;
	private:
		NodePtr	m_root;
	};
}

#include "BspTree.hxx"
#endif
