/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BspNode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 11:53:51 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 01:11:18 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BspNode.hpp"
#include "ExpectChar.hpp"
#include "Collision.hpp"
#include "Math.hpp"
#include <algorithm>

namespace octo
{
	namespace
	{
		inline bool	nearestHitTest(Segment const&segment,
									SegmentArray const& segments,
									float& bestDistance,
									Collision& bestCollision)
		{
			Collision	minDistCollision;
			Collision	collision;
			float		dist = 0;
			float		minDist = std::numeric_limits<float>::max();
			bool		hitTestResult = false;

			for (Segment const& s : segments)
			{
				if (segment.hitTest(s, collision))
				{
					dist = squaredDistance(segment.p0(), collision.position());
					if (dist < minDist)
					{
						minDistCollision = collision;
						minDist = dist;
						hitTestResult = true;
					}
				}
			}
			if (hitTestResult)
			{
				bestCollision = minDistCollision;
				bestDistance = minDist;
			}
			return (hitTestResult);
		}
	}

	BspNode::BspNode(BspNode* parent) :
		m_parent(parent),
		m_front(nullptr),
		m_back(nullptr)
	{
	}

	BspNode::BspNode(Segment const& hyperplan, BspNode* parent) :
		m_hyperplan(Segment(hyperplan)),
		m_parent(parent),
		m_front(nullptr),
		m_back(nullptr)
	{
	}

	BspNode::~BspNode()
	{
		if (m_front)
			delete m_front;
		if (m_back)
			delete m_back;
	}

	bool		BspNode::segmentHitTest(Segment const& segment, Collision& collision)const
	{
		bool		hitTestResult = false;
		float		bestDistance = std::numeric_limits<float>::max();
		Collision	bestCollision;
		Collision	tempCollision;

		hitTestResult = (segment.hitTest(m_hyperplan, bestCollision));
		bestDistance = squaredDistance(segment.p0(), bestCollision.position());
		hitTestResult |= nearestHitTest(segment, m_alignedSegments, bestDistance, bestCollision);
		// TODO ne tester qu'un des 2 cotes en fonction de la localisation du point
		hitTestResult |= nearestHitTest(segment, m_frontSegments, bestDistance, bestCollision);
		hitTestResult |= nearestHitTest(segment, m_backSegments, bestDistance, bestCollision);
		if (hitTestResult)
		{
			collision = bestCollision;
		}
		return (hitTestResult);
	}

	BspNode*	BspNode::parent()const
	{
		return (m_parent);
	}

	BspNode*	BspNode::front()const
	{
		return (m_front);
	}

	BspNode*	BspNode::back()const
	{
		return (m_back);
	}

	unsigned int	BspNode::depth()const
	{
		unsigned int	depthFront = 0;
		unsigned int	depthBack = 0;

		if (front() == nullptr && back() == nullptr)
			return (0);
		if (front())
			depthFront = front()->depth();
		if (back())
			depthBack = back()->depth();
		return (std::max(depthFront, depthBack) + 1);
	}

	Segment const&	BspNode::hyperplan()const
	{
		return (m_hyperplan);
	}

	BspNode::Iterator	BspNode::begin(SegmentCollection collection)
	{
		return (segments(collection).begin());
	}

	BspNode::Iterator	BspNode::end(SegmentCollection collection)
	{
		return (segments(collection).end());
	}

	BspNode::ConstIterator	BspNode::begin(SegmentCollection collection)const
	{
		return (segments(collection).begin());
	}

	BspNode::ConstIterator	BspNode::end(SegmentCollection collection)const
	{
		return (segments(collection).end());
	}

	void		BspNode::setFrontNode(BspNode* node)
	{
		if (m_front)
			m_front->m_parent = nullptr;
		m_front = node;
		if (m_front)
			m_front->m_parent = this;
	}

	void		BspNode::setBackNode(BspNode* node)
	{
		if (m_back)
			m_back->m_parent = nullptr;
		m_back = node;
		if (m_back)
			m_back->m_parent = this;
	}

	void		BspNode::setSegments(SegmentCollection collection, SegmentArray const& segments)
	{
		switch (collection)
		{
			case SegmentCollection::Front:
				m_frontSegments = segments;
				break;
			case SegmentCollection::Back:
				m_backSegments = segments;
				break;
			case SegmentCollection::Aligned:
				m_alignedSegments = segments;
				break;
			default:
				break;
		}
	}

	void		BspNode::emplaceSegments(SegmentCollection collection, SegmentArray&& segments)
	{
		switch (collection)
		{
			case SegmentCollection::Front:
				m_frontSegments = std::move(segments);
				break;
			case SegmentCollection::Back:
				m_backSegments = std::move(segments);
				break;
			case SegmentCollection::Aligned:
				m_alignedSegments = std::move(segments);
				break;
			default:
				break;
		}
	}

	void		BspNode::setHyperplan(Segment const& hyperplan)
	{
		m_hyperplan = hyperplan;
	}

	void		BspNode::write(std::ostream& os)const
	{
		os << "[" << m_hyperplan << ':';
		os << m_frontSegments << ':';
		os << m_backSegments << ':';
		os << m_alignedSegments << ']';
	}

	/*!
		Charge les donnees stockees par un noeud.
	*/
	void	BspNode::read(std::istream& is)
	{
		Segment					hyperplan;
		SegmentArray			frontSegments;
		SegmentArray			backSegments;
		SegmentArray			alignedSegments;
		std::istream::sentry	init(is);

		if (init)
		{
			is >> ExpectChar('[') >> hyperplan >> ExpectChar(':');
			is >> frontSegments >> ExpectChar(':');
			is >> backSegments >> ExpectChar(':');
			is >> alignedSegments >> ExpectChar(']');
			m_hyperplan = std::move(hyperplan);
			m_frontSegments = std::move(frontSegments);
			m_backSegments = std::move(backSegments);
			m_alignedSegments = std::move(alignedSegments);
		}
	}

	SegmentArray&	BspNode::segments(SegmentCollection collection)
	{
		switch (collection)
		{
			case SegmentCollection::Front:
				return (m_frontSegments);
				break;
			case SegmentCollection::Back:
				return (m_backSegments);
				break;
			case SegmentCollection::Aligned:
				return (m_alignedSegments);
				break;
			default:
				throw std::logic_error("invalid collection");
				break;
		}
	}

	SegmentArray const&	BspNode::segments(SegmentCollection collection)const
	{
		switch (collection)
		{
			case SegmentCollection::Front:
				return (m_frontSegments);
				break;
			case SegmentCollection::Back:
				return (m_backSegments);
				break;
			case SegmentCollection::Aligned:
				return (m_alignedSegments);
				break;
			default:
				throw std::logic_error("invalid collection");
				break;
		}
	}
}
