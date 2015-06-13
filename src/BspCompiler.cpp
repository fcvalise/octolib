/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BspCompiler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 14:56:13 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 01:20:42 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BspCompiler.hpp"
#include "BspNode.hpp"
#include "Math.hpp"

#include "details/BspCompilerImp.hpp"

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace octo
{
	/*!
	 *	\class SegmentScore
	 *	\brief Associe a un segment un score d'eligibilite comme hyperplan
	 *	de partitionnement.
	 *
	 * 	Le segment au score le plus bas sera choisit.
	 */
	class BspCompiler::SegmentScore
	{
	public:
		static bool	compare(SegmentScore const& lhs, SegmentScore const& rhs);

		SegmentScore();
		SegmentScore(SegmentListIt it, float score);
		float						score()const;
		SegmentListIt	iterator()const;
	private:
		SegmentListIt	m_iterator;
		float			m_score;
	};

	bool	BspCompiler::SegmentScore::compare(SegmentScore const& lhs, SegmentScore const& rhs)
	{
		return (lhs.score() < rhs.score());
	}

	BspCompiler::SegmentScore::SegmentScore() :
		m_score(0.f)
	{
	}

	BspCompiler::SegmentScore::SegmentScore(SegmentListIt it, float score) :
		m_iterator(it),
		m_score(score)
	{
	}

	float	BspCompiler::SegmentScore::score()const
	{
		return (m_score);
	}

	BspCompiler::SegmentListIt	BspCompiler::SegmentScore::iterator()const
	{
		return (m_iterator);
	}

	/*!
	 *	\class BspCompiler
	 *	\brief Build a BSP tree from a segment list
	 */

	/*!
	 *	Construct a compiler by defining how are chosen segment splitter
	 *	and the maximum segment count by node.
	 *
	 */
	BspCompiler::BspCompiler(HyperplanSelector selector,
							 std::size_t maxSegmentPerNode) :
		m_selector(selector),
		m_maxSegmentPerNode(maxSegmentPerNode)
	{
	}

	/*! Compiles the tree */
	BspTree	BspCompiler::run(SegmentList const& segments)
	{
		std::unique_ptr<BspNode>	root(new BspNode);

		build(segments, root.get());
		return (BspTree(root.release()));
	}

	/*!	Indique si la liste de segments restant necessite une subdivision. */
	bool	BspCompiler::needSubspace(SegmentList const& segments)const
	{
		return (m_maxSegmentPerNode > 0 && segments.size() > m_maxSegmentPerNode);
	}

	/*!	Returns an iterator on the segment chosen as hyperplan for splitting */
	BspCompiler::SegmentListIt	BspCompiler::findHyperplan(SegmentList const& segments)const
	{
		std::vector<SegmentScore>	scores;
		SegmentListIt				result = segments.end();
		
		scores.reserve(segments.size());
		for (auto it = segments.begin(); it != segments.end(); ++it)
		{
			scores.emplace_back(it, computeScore(segments, it));
		}
		if (scores.empty() == false)
		{
			std::sort(scores.begin(), scores.end(), SegmentScore::compare);
			result = scores.front().iterator();
		}
		return (result);
	}

	/*!	Compute a score for a segment */
	float	BspCompiler::computeScore(SegmentList const& segments, SegmentListIt current)const
	{
		float	score = 0.f;

		switch (m_selector)
		{
			case HyperplanSelector::NoSelection:
				score = details::noSelection(segments, current);
				break;
			case HyperplanSelector::MinimumCuts:
				score = details::minimumCuts(segments, current);
				break;
			case HyperplanSelector::BalancingSegments:
				score = details::balancingSegments(segments, current);
				break;
			default:
				break;
		}
		return (score);
	}

	/*!	Create the tree recursively from the root node
	 *	\param segments	Segments to put in the node \a node
	 *	If the count of segment is greater than the limits specified by the constructor then
	 *	the current sub-space is splitted in two part, separated by an hyperplan defined
	 *	by one segment of the list \a segments.<br>
	 *	\param	Current node
	 */
	void	BspCompiler::build(SegmentList const& segments, BspNode* node)
	{
		SegmentList		front;
		SegmentList		back;
		SegmentList		aligned;
		SegmentListIt	hyperplan = findHyperplan(segments); 
		BspNode*		newNode = nullptr;
		std::size_t		cutCount = 0;

		details::distribute(segments, hyperplan, front, back, aligned, cutCount);
		Segment	h = *hyperplan;
		h.setIdentifier(0);
		node->setHyperplan(h);
		if (needSubspace(front))
		{
			newNode = new BspNode;
			build(front, newNode);
			node->setFrontNode(newNode);
		}
		else
		{
			node->setSegments(BspNode::SegmentCollection::Front, front.begin(), front.end());
		}
		if (needSubspace(back))
		{
			newNode = new BspNode;
			build(back, newNode);
			node->setBackNode(newNode);
		}
		else
		{
			node->setSegments(BspNode::SegmentCollection::Back, back.begin(), back.end());
		}
		node->setSegments(BspNode::SegmentCollection::Aligned, aligned.begin(), aligned.end());
	}
}
