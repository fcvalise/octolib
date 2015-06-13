/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BspCompiler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 14:54:41 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 00:49:06 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSPCOMPILER_HPP
# define BSPCOMPILER_HPP
# include "Segment.hpp"
# include "BspTree.hpp"

# include <list>

namespace octo
{
	class BspCompiler
	{
		class SegmentScore;
	public:
		typedef std::list<Segment>				SegmentList;
		typedef SegmentList::const_iterator		SegmentListIt;

		enum class	HyperplanSelector
		{
			NoSelection,
			MinimumCuts,
			BalancingSegments
		};

		explicit BspCompiler(HyperplanSelector selector,
							 std::size_t maxSegmentPerNode);

		BspTree			run(SegmentList const& segments);
	private:
		bool			needSubspace(SegmentList const& segments)const;
		SegmentListIt	findHyperplan(SegmentList const& segments)const;
		float			computeScore(SegmentList const& segments, SegmentListIt current)const;
		void			build(SegmentList const& segments, BspNode* node);
	private:
		SegmentList			m_segments;
		HyperplanSelector	m_selector;
		std::size_t			m_maxSegmentPerNode;
	};
}

#endif
