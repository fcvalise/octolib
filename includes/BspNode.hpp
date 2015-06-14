/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BspNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 11:12:55 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 02:18:13 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSPNODE_HPP
# define BSPNODE_HPP
# include "Segment.hpp"

# include <memory>
# include <iostream>

namespace octo
{
	class BspNode
	{
		typedef std::unique_ptr<Segment>	SegmentPtr;
	public:
		typedef SegmentArray::iterator			Iterator;
		typedef SegmentArray::const_iterator	ConstIterator;
		
		enum class	SegmentCollection : unsigned char
		{
			Front,
			Back,
			Aligned
		};

		explicit BspNode(BspNode* parent = nullptr);
		explicit BspNode(Segment const& hyperplan, BspNode* parent = nullptr);
		~BspNode();

		BspNode(BspNode const&) = delete;
		BspNode&		operator = (BspNode const&) = delete;

		BspNode*			parent()const;
		BspNode*			front()const;
		BspNode*			back()const;
		unsigned int		depth()const;
		bool				segmentHitTest(Segment const& segment, Collision& collision)const;

		Segment const&		hyperplan()const;
		Iterator			begin(SegmentCollection collection);
		Iterator			end(SegmentCollection collection);
		ConstIterator		begin(SegmentCollection collection)const;
		ConstIterator		end(SegmentCollection collection)const;
		SegmentArray&		segments(SegmentCollection collection);
		SegmentArray const&	segments(SegmentCollection collection)const;

		void				setFrontNode(BspNode* node);
		void				setBackNode(BspNode* node);
		void				setHyperplan(Segment const& hyperplan);
		void				setSegments(SegmentCollection collection, SegmentArray const& segments);
		void				emplaceSegments(SegmentCollection collection, SegmentArray&& segments);

		template <class I>
		void				setSegments(SegmentCollection collection, I begin, I end)
		{
			segments(collection).assign(begin, end);
		}

		void				write(std::ostream& os)const;
		void				read(std::istream& is);
		void				writeToMemory(BinaryOutputStream& os)const;
		void				readFromMemory(BinaryInputStream& is);
	private:
		SegmentArray	m_frontSegments;
		SegmentArray	m_backSegments;
		SegmentArray	m_alignedSegments;
		Segment			m_hyperplan;
		BspNode*		m_parent;
		BspNode*		m_front;
		BspNode*		m_back;
	};
}

#endif
