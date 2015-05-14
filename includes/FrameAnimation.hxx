/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FrameAnimation.hxx                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irabeson <irabeson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 20:26:04 by irabeson          #+#    #+#             */
/*   Updated: 2015/05/13 18:29:56 by irabeson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace octo
{
	/*!	Public frame datas */
	template <class T>
	struct FrameAnimation<T>::Frame
	{
		Frame() :
			value(T())
		{
		}

		explicit Frame(sf::Time durationParam, T const& valueParam = T()) :
			duration(durationParam),
			value(valueParam)
		{
		}

		sf::Time	duration;
		T			value;
	};

	/*!	Private frame datas */
	template <class T>
	struct FrameAnimation<T>::PrivateFrame
	{
		explicit PrivateFrame(sf::Time startParam) :
			start(startParam)
		{
		}

		explicit PrivateFrame(Frame const& other) :
			duration(other.duration),
			value(other.value)
		{
		}

		bool	operator == (PrivateFrame const& other)const
		{
			return (start == other.start);
		}

		bool	operator < (PrivateFrame const& other)const
		{
			return (start < other.start);
		}

		sf::Time	start;		// Only for binary search
		sf::Time	duration;
		T			value;
	};

	/*!	Compute start value of each frame */
	template <class T>
	struct	FrameAnimation<T>::SetupFrames
	{
		void	operator()(PrivateFrame& frame)
		{
			frame.start = m_currentStart;
			m_currentStart += frame.duration;
		}

		operator sf::Time () const
		{
			return (m_currentStart);
		}
	private:
		sf::Time	m_currentStart;
	};

	template <class T>
	FrameAnimation<T>::FrameAnimation() :
		m_loopMode(LoopMode::NoLoop)
	{
	}

	namespace
	{
		template <class T>
		static typename std::vector<T>::const_iterator	binarySearchImp(std::vector<T> const& values, T const& value)
		{
			std::size_t	start = 0;
			std::size_t	end = values.size();
			std::size_t	pivot = (start + end) / 2;

			while ((end - start) > 1)
			{
				T const&	v = values.at(pivot);

				if (v == value)
				{
					return (values.begin() + pivot);
				}
				else if (v < value)
				{
					start = pivot;
				}
				else
				{
					end = pivot;
				}
				pivot = (start + end) / 2;
			}
			return (values.begin() + pivot);
		}
	}

	template <class T>
	T const&	FrameAnimation<T>::value(sf::Time currentTime)const
	{
		PrivateFrame	timeFrame(currentTime);
		auto			it = binarySearchImp<PrivateFrame>(m_frames, timeFrame);

		if (it == m_frames.end())
			throw std::range_error("frame: binary search: invalid start");
		return (it->value);
	}

	template <class T>
	sf::Time	FrameAnimation<T>::duration()const
	{
		return (m_duration);
	}

	template <class T>
	LoopMode	FrameAnimation<T>::loopMode()const
	{
		return (m_loopMode);
	}

	template <class T>
	bool		FrameAnimation<T>::loadFromMemory(char* data, std::size_t count)
	{
		return (false);
		static_cast<void>(data);
		static_cast<void>(count);
	}

	template <class T>
	bool		FrameAnimation<T>::loadFromFile(std::string const& fileName)
	{
		return (false);
		static_cast<void>(fileName);
	}

	template <class T>
	bool		FrameAnimation<T>::saveToFile(std::string const& fileName)const
	{
		return (false);
		static_cast<void>(fileName);
	}

	template <class T>
	void		FrameAnimation<T>::setFrames(std::vector<Frame> const& frames)
	{
		std::vector<PrivateFrame>	tempFrames;

		for (auto frame : frames)
		{
			tempFrames.push_back(PrivateFrame(frame));
		}
		m_frames = std::move(tempFrames);
		m_duration = std::for_each(m_frames.begin(), m_frames.end(), SetupFrames());	
	}

	template <class T>
	sf::Time	FrameAnimation<T>::getFrameDuration(std::size_t i)const
	{
		return (m_frames.at(i).duration);
	}

	template <class T>
	T			FrameAnimation<T>::getFrameValue(std::size_t i)const
	{
		return (m_frames.at(i).value);
	}
}
