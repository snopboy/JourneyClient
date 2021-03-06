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
#include "MapObject.h"

namespace jrc
{
	MapObject::MapObject(int32_t o)
	{
		oid = o;
		active = true;
	}

	int8_t MapObject::update(const Physics& physics)
	{
		physics.moveobject(phobj);
		return phobj.fhlayer;
	}

	void MapObject::setposition(int16_t x, int16_t y)
	{
		phobj.setx(x);
		phobj.sety(y);
	}

	void MapObject::setposition(Point<int16_t> position)
	{
		int16_t x = position.x();
		int16_t y = position.y();
		setposition(x, y);
	}

	void MapObject::makeactive()
	{
		active = true;
	}

	void MapObject::deactivate()
	{
		active = false;
	}

	bool MapObject::isactive() const
	{
		return active;
	}

	int8_t MapObject::getlayer() const
	{
		return phobj.fhlayer;
	}

	int32_t MapObject::getoid() const
	{
		return oid;
	}

	Point<int16_t> MapObject::getposition() const
	{
		return phobj.getposition();
	}

	PhysicsObject& MapObject::getphobj()
	{
		return phobj;
	}
}