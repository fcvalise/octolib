/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BspTree.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 10:26:25 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 00:53:16 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BspTree.hpp"
#include "BspNode.hpp"
#include "ExpectChar.hpp"
#include "Segment.hpp"
#include "Collision.hpp"

#include <map>
#include <cstdint>
#include <stdexcept>
#include <limits>

namespace octo
{
	namespace
	{
		typedef std::uint64_t				NodeId;

		static NodeId const					NullNodeId = std::numeric_limits<NodeId>::max();

		class	MakeNodeTableOut
		{
			typedef BspNode const*	NodePtr;
		public:
			typedef std::map<NodePtr, NodeId>	NodeTableOut;
			
			MakeNodeTableOut() :
				m_nextId(0)
			{
			}

			void	operator()(NodePtr node)
			{
				if (m_nodeIdMap.insert(std::make_pair(node, m_nextId)).second == false)
					throw std::logic_error("node already in table");
				++m_nextId;
			}

			NodeTableOut const&	table()const
			{
				return (m_nodeIdMap);
			}

			void		printTable(std::ostream& os)const
			{
				std::uint64_t const	count = m_nodeIdMap.size();

				os << "[" << count << ":";
				for (auto it = m_nodeIdMap.begin(); it != m_nodeIdMap.end(); ++it)
				{
					os << "[" << it->second << ":" << getId(it->first->front()) << ":" << getId(it->first->back()) << "]";
				}
				os << "]";
			}

			NodeId		getId(NodePtr node)const
			{
				NodeId							id = NullNodeId;
				NodeTableOut::const_iterator	it;

				if (node)
				{
					it = m_nodeIdMap.find(node);
					id = it->second;
				}		
				return (id);
			}
		private:
			NodeTableOut	m_nodeIdMap;
			NodeId			m_nextId;
		};

		class MakeNodeTableIn
		{
			typedef BspNode*					NodePtr;
			typedef std::map<NodeId, NodePtr>	IdNodeMap;
		public:
			NodePtr		read(std::istream& is)
			{
				std::unique_ptr<BspNode>	root;
				std::istream::sentry		init(is);

				if (init)
				{
					is >> ExpectChar('[');
					root.reset(readTable(is));
					is >> ExpectChar(':');
					readNodeData(is);
					is >> ExpectChar(']');
				}
				return (root.release());
			}

		private:
			void		readNodeData(std::istream& is)
			{
				NodePtr	node = nullptr;
				NodeId	id = NullNodeId;

				for (unsigned int i = 0; i < m_idNodeMap.size(); ++i)
				{
					is >> id;
					node = get(id);
					is >> ExpectChar(':');
					node->read(is);
					is >> ExpectChar(':');
				}
			}

			NodePtr		readTable(std::istream& is)
			{
				std::uint64_t				count = 0;
				NodePtr						node = nullptr;
				std::unique_ptr<BspNode>	root;
				NodeId						id = NullNodeId;
				NodeId						frontId = NullNodeId;
				NodeId						backId = NullNodeId;

				is >> ExpectChar('[') >> count >> ExpectChar(':');
				for (std::uint64_t i = 0; i < count; ++i)
				{
					is >> ExpectChar('[') >> id >> ExpectChar(':') >> frontId >> ExpectChar(':') >> backId >> ExpectChar(']');
					node = getOrCreate(id);
					if (node == nullptr)
						throw std::runtime_error("invalid bsp table");
					if (root == nullptr)
						root.reset(node);
					node->setFrontNode(getOrCreate(frontId));
					node->setBackNode(getOrCreate(backId));
				}
				is >> ExpectChar(']');
				return (root.release());
			}
		private:
			NodePtr	get(NodeId id)const
			{
				return (m_idNodeMap.at(id));
			}

			NodePtr	getOrCreate(NodeId id)
			{
				NodePtr				node = nullptr;
				IdNodeMap::iterator	it;

				if (id != NullNodeId)
				{
					it = m_idNodeMap.find(id);
					if (it == m_idNodeMap.end())
					{
						node = new BspNode;
						it = m_idNodeMap.insert(std::make_pair(id, node)).first;
					}
					else
					{
						node = it->second;
					}
				}
				return (node);
			}
		private:
			IdNodeMap	m_idNodeMap;
		};
	}

	BspTree::BspTree(BspNode* root) :
		m_root(root)
	{
	}

	void	BspTree::reset(BspNode* root)
	{
		m_root.reset(root);
	}

	void	BspTree::write(std::ostream& os)const
	{
		MakeNodeTableOut	tableMaker;
		
		// L'ordre de parcours est important.
		// On veut en particulier que le premier noeud visite soit
		// le noeud racine.
		visit<VisitorMode::Prefix>(tableMaker);
		os << "[";
		tableMaker.printTable(os);
		os << ":";
		for (auto const& entry : tableMaker.table())
		{
			os << entry.second << ":";
			entry.first->write(os);
			os << ":";
		}
		os << "]";
		(void)os;
	}

	void	BspTree::read(std::istream& is)
	{
		MakeNodeTableIn				reader;
		
		m_root.reset(reader.read(is));
	}

	BspNode const*	BspTree::nodeAt(sf::Vector2f const& pos)const
	{
		BspNode const*	current = m_root.get();
		BspNode const*	result = nullptr;
		float			location = 0.f;

		while (current)
		{
			location = current->hyperplan().location(pos);
			result = current;
			if (location < 0.f)
			{
				current = current->front();
			}
			else if (location > 0.f)
			{
				current = current->back();
			}
			else
			{
				return (result);
			}
		}
		return (result);
	}

	bool			BspTree::segmentHitTest(Segment const& segment, Collision& collision)const
	{
		BspNode const*	current = m_root.get();
		BspNode const*	result = nullptr;
		float			location = 0.f;
		Collision		c;

		while (current)
		{
			location = current->hyperplan().location(segment.p0());
			result = current;
			if (current->segmentHitTest(segment, c))
			{
				collision = c;
				return (true);
			}
			if (location < 0.f)
			{
				current = current->front();
			}
			else if (location > 0.f)
			{
				current = current->back();
			}
			else
			{
				break;
			}
		}
		return (result && result->segmentHitTest(segment, collision));
	}

	BspNode*		BspTree::root()
	{
		return (m_root.get());
	}

	BspNode const*	BspTree::root()const
	{
		return (m_root.get());
	}

	bool			BspTree::empty()const
	{
		return (m_root == nullptr);
	}
}
