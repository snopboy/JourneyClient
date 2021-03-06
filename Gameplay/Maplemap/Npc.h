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
#pragma once
#include "MapObject.h"

#include "..\Physics\PhysicsObject.h"

#include "..\..\Graphics\Animation.h"
#include "..\..\Graphics\Text.h"
#include "..\..\Util\Randomizer.h"

#include <map>

namespace jrc
{
	// Represents a npc on the current map.
	// Implements the 'Mapobject' interface to be used in a 'Mapobjects' template.
	class Npc : public MapObject
	{
	public:
		// Constructs an npc by combining data from game files with
		// data sent by the server.
		Npc(int32_t npcid, int32_t oid, bool mirrored, uint16_t fhid, 
			bool control, Point<int16_t> position);

		// Draws the current animation and name/function tags.
		void draw(double viewx, double viewy, float alpha) const override;
		// Updates the current animation and physics.
		int8_t update(const Physics& physics) override;

		// Changes stance and resets animation.
		void setstance(const std::string& stance);

		// Check wether this is a server-sided npc.
		bool isscripted() const;
		// Check if the npc is in range of the cursor.
		bool inrange(Point<int16_t> cursorpos, Point<int16_t> viewpos) const;

	private:
		std::map<std::string, Animation> animations;
		std::map<std::string, std::vector<std::string>> lines;
		std::vector<std::string> states;
		std::string name;
		std::string func;
		bool hidename;
		bool scripted;
		bool mouseonly;

		int32_t npcid;
		bool flip;
		std::string stance;
		bool control;

		Randomizer random;
		Text namelabel;
		Text funclabel;
	};
}

