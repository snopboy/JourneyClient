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
#pragma once
#include "MapObjects.h"
#include "Mob.h"

#include "..\Combat\Attack.h"
#include "..\Combat\BulletEffect.h"
#include "..\Combat\DamageEffect.h"
#include "..\Combat\SpecialMove.h"
#include "..\Spawn.h"

#include <list>

namespace jrc
{
	// A collection of mobs on a map.
	class MapMobs
	{
	public:
		// Draw all mobs on a layer.
		void draw(int8_t layer, double viewx, double viewy, float alpha) const;
		// Update all mobs.
		void update(const Physics& physics);

		// Spawn a new mob.
		void sendspawn(const MobSpawn& spawn);
		// Kill a mob.
		void killmob(int32_t oid, int8_t effect);
		// Remove all mobs.
		void clear();

		// Update a mob's hp display.
		void sendmobhp(int32_t oid, int8_t percent, uint16_t playerlevel);
		// Update who a mob is controlled by.
		void setcontrol(int32_t oid, bool control);
		// Update a mob's movements.
		void movemob(int32_t oid, Point<int16_t> start, const Movement& movement);

		// Calculate the results of an attack.
		AttackResult sendattack(const Attack& attack);
		// Show the results of an attack.
		void showresult(const Char& user, const SpecialMove& skill, const AttackResult& result);

		Optional<Mob> getmob(int32_t oid);
		Optional<const Mob> getmob(int32_t oid) const;

	private:
		void applyeffect(const DamageEffect& effect);
		std::vector<int32_t> findclosest(Rectangle<int16_t> range, Point<int16_t> origin, uint8_t mobcount) const;

		MapObjects mobs;
		std::list<DamageNumber> damagenumbers;
		std::list<DamageEffect> damageeffects;
		std::list<BulletEffect> bulleteffects;
	};
}

