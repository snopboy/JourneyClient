//////////////////////////////////////////////////////////////////////////////
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
#include "MapChars.h"

namespace jrc
{
	void MapChars::draw(int8_t layer, double viewx, double viewy, float alpha) const
	{
		chars.draw(layer, viewx, viewy, alpha);
	}

	void MapChars::update(const Physics& physics)
	{
		chars.update(physics);
	}

	void MapChars::sendspawn(const CharSpawn& spawn)
	{
		int32_t cid = spawn.getcid();
		Optional<OtherChar> ochar = getchar(cid);
		if (ochar)
		{

		}
		else
		{
			chars.add(
				spawn.instantiate()
			);
		}
	}

	void MapChars::removechar(int32_t cid)
	{
		chars.remove(cid);
	}

	void MapChars::clear()
	{
		chars.clear();
	}

	void MapChars::movechar(int32_t cid, const std::vector<Movement>& movements)
	{
		Optional<OtherChar> otherchar = getchar(cid);
		if (otherchar)
		{
			otherchar->sendmovement(movements);
		}
	}

	void MapChars::updatelook(int32_t cid, const LookEntry& look)
	{
		Optional<OtherChar> otherchar = getchar(cid);
		if (otherchar)
		{
			otherchar->updatelook(look);
		}

	}

	Optional<OtherChar> MapChars::getchar(int32_t cid)
	{
		return chars.get(cid)
			.reinterpret<OtherChar>();
	}
}
