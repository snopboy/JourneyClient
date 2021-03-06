/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 Daniel Allendorf                                        //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "Mapinfo.h"

namespace jrc
{
	MapInfo::MapInfo(nl::node src, Range<int16_t> walls, Range<int16_t> borders)
	{
		nl::node info = src["info"];
		if (info["VRLeft"].data_type() == nl::node::type::integer)
		{
			mapwalls = Range<int16_t>(info["VRLeft"], info["VRRight"]);
			mapborders = Range<int16_t>(info["VRTop"], info["VRBottom"]);
		}
		else
		{
			mapwalls = walls;
			mapborders = borders;
		}

		std::string bgmpath = info["bgm"];
		size_t split = bgmpath.find('/');
		bgm = bgmpath.substr(0, split) + ".img/" + bgmpath.substr(split + 1);

		cloud = info["cloud"].get_bool();
		fieldlimit = info["fieldLimit"];
		hideminimap = info["hideMinimap"].get_bool();
		mapmark = info["mapMark"];
		swim = info["swim"].get_bool();
		town = info["town"].get_bool();

		for (auto seat : src["seat"])
		{
			seats.push_back(seat);
		}

		for (auto ladder : src["ladderRope"])
		{
			ladders.push_back(ladder);
		}
	}

	MapInfo::MapInfo() {}

	bool MapInfo::isswimmap() const
	{
		return swim;
	}

	std::string MapInfo::getbgm() const
	{
		return bgm;
	}

	Range<int16_t> MapInfo::getwalls() const
	{
		return mapwalls;
	}

	Range<int16_t> MapInfo::getborders() const
	{
		return mapborders;
	}

	Optional<const Seat> MapInfo::findseat(Point<int16_t> position) const
	{
		return Optional<Seat>::findfirst(seats, &Seat::inrange, position);
	}

	Optional<const Ladder> MapInfo::findladder(Point<int16_t> position, bool upwards) const
	{
		return Optional<Ladder>::findfirst(ladders, &Ladder::inrange, position, upwards);
	}


	Seat::Seat(nl::node src)
	{
		pos = src;
	}

	bool Seat::inrange(Point<int16_t> position) const
	{
		auto hor = Range<int16_t>::symmetric(position.x(), 10);
		auto ver = Range<int16_t>::symmetric(position.y(), 10);
		return hor.contains(pos.x()) && ver.contains(pos.y());
	}

	Point<int16_t> Seat::getpos() const
	{
		return pos;
	}


	Ladder::Ladder(nl::node src)
	{
		x = src["x"];
		y1 = src["y1"];
		y2 = src["y2"];
		ladder = src["l"].get_bool();
	}

	bool Ladder::isladder() const
	{
		return ladder;
	}

	bool Ladder::inrange(Point<int16_t> position, bool upwards) const
	{
		auto hor = Range<int16_t>::symmetric(position.x(), 10);
		auto ver = Range<int16_t>(y1, y2);
		int16_t y = upwards ?
			position.y() - 5 :
			position.y() + 5;
		return hor.contains(x) && ver.contains(y);
	}

	bool Ladder::felloff(int16_t y, bool downwards) const
	{
		int16_t dy = downwards ? y + 5 : y - 5;
		return dy > y2 || y + 5 < y1;
	}

	int16_t Ladder::getx() const
	{
		return x;
	}
}
