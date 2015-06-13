/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BspCompilerImp.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/07 20:40:06 by irabeson          #+#    #+#             */
/*   Updated: 2015/06/14 01:12:20 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSPCOMPILERIMP_HPP
# define BSPCOMPILERIMP_HPP

namespace octo
{
	namespace details
	{
		enum class	Placement
		{
			Front,
			Back,
			Aligned,
			Cutted
		};

		static bool	segmentCutTest(Segment const& segment, Segment const& other)
		{
			sf::Vector2f	normale = segment.normale();
			float			denominator = dotProduct(-normale, (other.p1() - other.p0()));

			return (std::abs(denominator) < std::numeric_limits<float>::epsilon());
		}

		static Placement	findPlace(Segment const& segment,
														Segment const& toPlace)
		{
			sf::Vector2f	normale;
			float			numerator = 0.f;
			float			denominator = 0.f;
			float			inter = 0.f;

			normale = segment.normale();
			numerator = dotProduct(normale, (toPlace.p0() - segment.p0()));
			denominator = dotProduct(-normale, (toPlace.p1() - toPlace.p0()));				
			if (std::abs(denominator) < std::numeric_limits<float>::epsilon())
			{
				// Segment parallele a l'hyperplan
				if (Segment::areAligned(segment, toPlace))
					return (Placement::Aligned);
				else if (numerator < 0.f)
					return (Placement::Front);
				else
					return (Placement::Back);
			}
			else
			{
				inter = numerator / denominator;
				if (inter >= 0.f && inter <= 1.f)
				{
					return (Placement::Cutted);
				}
				else
				{
					if (numerator < 0.f)
						return (Placement::Front);
					else
						return (Placement::Back);
				}
			}
		}

		static float	noSelection(BspCompiler::SegmentList const& segments, BspCompiler::SegmentListIt current)
		{
			return (segments.begin() == current ? 0.f : std::numeric_limits<float>::max());
		}

		/*! Determine le score du segment \a current en fonction du nombre de coupures
		 * 	qui seraient provoquees si ce segment etait choisit comme hyperplan
		 */
		static float	minimumCuts(BspCompiler::SegmentList const& segments, BspCompiler::SegmentListIt current)
		{
			std::size_t	cutCount = 0;

			for (auto it = segments.begin(); it != segments.end(); ++it)
			{
				if (it != current && segmentCutTest(*current, *it))
				{
					++cutCount;
				}
			}
			return (static_cast<float>(cutCount));
		}

		/*!
		 *	Determine le score du segment \a current en fonction de la repartition des segments dans les
		 *	liste front, back et aligned.
		 *
		 */
		static float	balancingSegments(BspCompiler::SegmentList const& segments, BspCompiler::SegmentListIt current)
		{
			ssize_t	frontCount = 0;
			ssize_t	backCount = 0;
			ssize_t	alignedCount = 0;
			ssize_t	cuttedCount = 0;

			for (auto it = segments.begin(); it != segments.end(); ++it)
			{
				if (it != current)
				{
					switch (findPlace(*current, *it))
					{
						case Placement::Front:
							++frontCount;
							break;
						case Placement::Back:
							++backCount;
							break;
						case Placement::Cutted:
							++cuttedCount;
							++frontCount;
							++backCount;
							break;
						case Placement::Aligned:
							++alignedCount;
							break;
						default:
							break;
					}
				}
			}
			return (std::abs(frontCount - backCount) + (cuttedCount * 2.f) - (alignedCount * 3));
		}

		static void		distribute(BspCompiler::SegmentList const& segments,
									BspCompiler::SegmentListIt hyperplan,
									BspCompiler::SegmentList& front, 
									BspCompiler::SegmentList& back,
									BspCompiler::SegmentList& aligned,
									std::size_t& cutCount)
		{
			sf::Vector2f	normale;
			float			numerator = 0.f;
			float			denominator = 0.f;
			float			inter = 0.f;
			Segment			first;
			Segment			second;

			for (auto it = segments.begin(); it != segments.end(); ++it)
			{
				if (it != hyperplan)
				{
					normale = hyperplan->normale();
					numerator = dotProduct(normale, (it->p0() - hyperplan->p0()));
					denominator = dotProduct(-normale, (it->p1() - it->p0()));				
					if (std::abs(denominator) < std::numeric_limits<float>::epsilon())
					{
						// Le segment it est parallele a l'hyperplan
						if (Segment::areAligned(*hyperplan, *it))
							aligned.push_back(*it);
						else if (numerator < 0.f)
							front.push_back(*it);
						else
							back.push_back(*it);
					}
					else
					{
						inter = numerator / denominator;
						if (inter >= 0.f && inter <= 1.f)
						{
							// Le segment it est coupe par l'hyperplan
							Segment::split(*it, inter, first, second);
							++cutCount;
							if (determinant(hyperplan->p1() - hyperplan->p0(),
											  first.p0() - hyperplan->p0()) > 0.f)
							{
								front.push_back(first);
								back.push_back(second);
							}
							else
							{
								front.push_back(second);
								back.push_back(first);
							}
						}
						else
						{
							if (numerator < 0.f)
								front.push_back(*it);
							else
								back.push_back(*it);
						}
					}
				}
			}
		}
	}
}

#endif
