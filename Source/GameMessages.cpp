#include "GameMessages.h"
#include "Common.h"
#include "WorldServer.h"
#include "AccountsDB.h"
#include "Social.h"
#include "FileConfiguration.h"
#include "WorldObjectsDB.h"

#include <map>
#include <sstream>

#include <chrono>
#include <thread>

std::map<long long, ObjectInformation> Objects;
std::map<long long, ZoneId> LaunchPads;
bool isObjectsInitialized = false;

void initializeObject(ObjectInformation oinfo){
	Objects[oinfo.objid] = oinfo;
}

void initializeObject(long long objid, ZoneId zone, ObjectType type, std::string comment){
	Objects[objid] = ObjectInformation(objid, zone, type, comment);
}

void initializeLaunchPad(long long objid, ZoneId zone, ZoneId target, std::string comment = ""){
	Objects[objid] = ObjectInformation(objid, zone, ObjectType::LaunchPad, comment);
	LaunchPads[objid] = target;
}

void initializeObjects(){
	//Collecting all objectids from every zone
	initializeLaunchPad(70368746922751, ZoneId::CRUX_PRIME, ZoneId::NEXUS_TOWER);

	initializeLaunchPad(70368747133960, ZoneId::AVANT_GROVE, ZoneId::AVANT_GARDENS);
	initializeObject(70368747133989, ZoneId::AVANT_GROVE, ObjectType::PostBox, "Hub"); //9

	initializeLaunchPad(70368747143926, ZoneId::NIMBUS_ISLE, ZoneId::NIMBUS_STATION);
	initializeObject(70368747143977, ZoneId::NIMBUS_ISLE, ObjectType::PostBox, "Hub");

	initializeLaunchPad(70368747150591, ZoneId::GNARLED_FOREST, ZoneId::CHANTEY_SHANTEY);
	initializeLaunchPad(70368747150592, ZoneId::GNARLED_FOREST, ZoneId::NIMBUS_STATION, "Pirate Camp");
	initializeLaunchPad(70368747150593, ZoneId::GNARLED_FOREST, ZoneId::NIMBUS_STATION);
	initializeObject(70368747150602, ZoneId::GNARLED_FOREST, ObjectType::Minigame, "Cannon Cove Shooting Gallery"); //9
	initializeObject(70368747150603, ZoneId::GNARLED_FOREST, ObjectType::Minigame, "Keelhaul Canyon Racetrack"); //9
	initializeObject(70368747150623, ZoneId::GNARLED_FOREST, ObjectType::Plaque, "Brig Rock Tunnel"); //9

	initializeObject(70368747161296, ZoneId::FORBIDDEN_VALLEY_DRAGON, ObjectType::Minigame, "Leave Minigame"); //9

	initializeLaunchPad(70368747162328, ZoneId::RAVEN_BLUFF, ZoneId::FORBIDDEN_VALLEY);
	initializeObject(70368747162358, ZoneId::RAVEN_BLUFF, ObjectType::PostBox, "Hub"); //9

	initializeLaunchPad(70368747172233, ZoneId::LEGO_CLUB, ZoneId::GNARLED_FOREST);
	initializeLaunchPad(70368747172234, ZoneId::LEGO_CLUB, ZoneId::FORBIDDEN_VALLEY);
	initializeLaunchPad(70368747172235, ZoneId::LEGO_CLUB, ZoneId::AVANT_GARDENS);
	initializeObject(70368747172236, ZoneId::LEGO_CLUB, ObjectType::PostBox, "Inside"); //9

	initializeLaunchPad(70368747172584, ZoneId::MOON_BASE, ZoneId::STARBASE_3001);
	initializeLaunchPad(70368747173214, ZoneId::DEEP_FREEZE, ZoneId::STARBASE_3001);
	initializeLaunchPad(70368747194845, ZoneId::ROBOT_CITY, ZoneId::STARBASE_3001);

	initializeLaunchPad(70368747531976, ZoneId::NIMBUS_ROCK, ZoneId::NIMBUS_STATION);
	initializeObject(70368747531998, ZoneId::NIMBUS_ROCK, ObjectType::PostBox, "Hub"); //9

	initializeLaunchPad(70368747534285, ZoneId::CHANTEY_SHANTEY, ZoneId::GNARLED_FOREST);
	initializeObject(70368747534312, ZoneId::CHANTEY_SHANTEY, ObjectType::PostBox, "Hub"); //9

	initializeObject(70368747635921, ZoneId::STARBASE_3001, ObjectType::LaunchPad, "Rocket Laucher"); //9
	initializeObject(70368747636011, ZoneId::STARBASE_3001, ObjectType::Binoculars, "Entrance Right"); //9
	initializeObject(70368747636012, ZoneId::STARBASE_3001, ObjectType::Binoculars, "Entrance Left"); //9

	initializeLaunchPad(70368747873772, ZoneId::VENTURE_EXPLORER_RETURN, ZoneId::AVANT_GARDENS, "2");
	initializeObject(70368747873850, ZoneId::VENTURE_EXPLORER_RETURN, ObjectType::Plaque, "Captain's Log"); //9
	initializeObject(70368747873894, ZoneId::VENTURE_EXPLORER_RETURN, ObjectType::Binoculars, "Start Area Left"); //9
	initializeObject(70368747873895, ZoneId::VENTURE_EXPLORER_RETURN, ObjectType::Binoculars, "Start Area Right"); //9
	initializeObject(70368747873896, ZoneId::VENTURE_EXPLORER_RETURN, ObjectType::Binoculars, "Launch Area"); //9
	initializeObject(70368747873897, ZoneId::VENTURE_EXPLORER_RETURN, ObjectType::Binoculars, "Behind Bob"); //9
	initializeObject(70368747873898, ZoneId::VENTURE_EXPLORER_RETURN, ObjectType::Binoculars, "Platform"); //9
	initializeObject(70368747873906, ZoneId::VENTURE_EXPLORER_RETURN, ObjectType::Plaque, "Coded Message From: Beck Strongheart"); //9
	initializeObject(70368747873908, ZoneId::VENTURE_EXPLORER_RETURN, ObjectType::Plaque, "Ship's Registry"); //9

	initializeLaunchPad(70368747874563, ZoneId::NIMBUS_STATION, ZoneId::FORBIDDEN_VALLEY);
	initializeLaunchPad(70368747874564, ZoneId::NIMBUS_STATION, ZoneId::GNARLED_FOREST);
	initializeLaunchPad(70368747874571, ZoneId::NIMBUS_STATION, ZoneId::NIMBUS_ISLE, "Brick Annex");
	initializeLaunchPad(70368747874572, ZoneId::NIMBUS_STATION, ZoneId::NIMBUS_ROCK, "Brick Annex");
	initializeLaunchPad(70368747874573, ZoneId::NIMBUS_STATION, ZoneId::NEXUS_TOWER, "Nexus Checkpoint");
	initializeLaunchPad(70368747874574, ZoneId::NIMBUS_STATION, ZoneId::PET_COVE, "Brick Annex");
	initializeLaunchPad(70368747874575, ZoneId::NIMBUS_STATION, ZoneId::AVANT_GARDENS);
	initializeObject(70368747874576, ZoneId::NIMBUS_STATION, ObjectType::Minigame, "Vertigo Loop Racetrack, Nexus Checkpoint");
	initializeObject(70368747874579, ZoneId::NIMBUS_STATION, ObjectType::Portal, "To LEGO Club"); //9
	initializeObject(70368747874580, ZoneId::NIMBUS_STATION, ObjectType::Minigame, "Battle of Nimbus Station"); //9
	
	initializeLaunchPad(70368747893770, ZoneId::AVANT_GARDENS, ZoneId::VENTURE_EXPLORER_RETURN);
	initializeLaunchPad(70368747893771, ZoneId::AVANT_GARDENS, ZoneId::NIMBUS_STATION);
	initializeLaunchPad(70368747893772, ZoneId::AVANT_GARDENS, ZoneId::BLOCK_YARD);
	initializeLaunchPad(70368747893773, ZoneId::AVANT_GARDENS, ZoneId::AVANT_GROVE);
	initializeObject(70368747893774, ZoneId::AVANT_GARDENS, ObjectType::Minigame, "Survival Mini-Game"); //9
	initializeObject(70368747893777, ZoneId::AVANT_GARDENS, ObjectType::Minigame, "Spider-Queen Battle"); //9
	
	initializeObject(70368747895179, ZoneId::VENTURE_EXPLORER, ObjectType::Machine, "Launch Area Right"); //9
	initializeLaunchPad(70368747895189, ZoneId::VENTURE_EXPLORER, ZoneId::AVANT_GARDENS, "4");
	initializeLaunchPad(70368747895190, ZoneId::VENTURE_EXPLORER, ZoneId::AVANT_GARDENS, "2");
	initializeLaunchPad(70368747895191, ZoneId::VENTURE_EXPLORER, ZoneId::AVANT_GARDENS, "3");
	initializeLaunchPad(70368747895192, ZoneId::VENTURE_EXPLORER, ZoneId::AVANT_GARDENS, "1");
	initializeObject(70368747895218, ZoneId::VENTURE_EXPLORER, ObjectType::Plaque, "Captains Log"); //9
	initializeObject(70368747895266, ZoneId::VENTURE_EXPLORER, ObjectType::Binoculars, "Start Area Left"); //9
	initializeObject(70368747895267, ZoneId::VENTURE_EXPLORER, ObjectType::Binoculars, "Start Area Right"); //9
	initializeObject(70368747895268, ZoneId::VENTURE_EXPLORER, ObjectType::Binoculars, "Launch Area"); //9
	initializeObject(70368747895269, ZoneId::VENTURE_EXPLORER, ObjectType::Binoculars, "Behind Bob"); //9
	initializeObject(70368747895270, ZoneId::VENTURE_EXPLORER, ObjectType::Binoculars, "Platform"); //9
	initializeObject(70368747895311, ZoneId::VENTURE_EXPLORER, ObjectType::Plaque, "Coded Message From: Beck Strongheart"); //9
	initializeObject(70368747895314, ZoneId::VENTURE_EXPLORER, ObjectType::Plaque, "Ship's Registry"); //9

	initializeLaunchPad(70368747895359, ZoneId::FORBIDDEN_VALLEY, ZoneId::RAVEN_BLUFF, "Main Gate");
	initializeLaunchPad(70368747895360, ZoneId::FORBIDDEN_VALLEY, ZoneId::NIMBUS_STATION, "Great Tree");
	initializeLaunchPad(70368747895361, ZoneId::FORBIDDEN_VALLEY, ZoneId::NIMBUS_STATION, "Main Gate");
	initializeObject(70368747895387, ZoneId::FORBIDDEN_VALLEY, ObjectType::Minigame, "Dragon Battle"); //9
	initializeObject(70368747895388, ZoneId::FORBIDDEN_VALLEY, ObjectType::Minigame, "Dragonmaw Chasm Racetrack"); //9

	initializeLaunchPad(70368748024518, ZoneId::NEXUS_TOWER, ZoneId::NINJAGO_MONASTERY, "Outer Platform");
	initializeLaunchPad(70368748024521, ZoneId::NEXUS_TOWER, ZoneId::NIMBUS_STATION, "Outer Platform");
	initializeObject(70368748024542, ZoneId::NEXUS_TOWER, ObjectType::Portal, "To Crux Prime, Sentinel Sector");
	initializeObject(70368748024544, ZoneId::NEXUS_TOWER, ObjectType::Portal, "To LEGO Club, Venture Lague Observatory");

	initializeObject(70368748035362, ZoneId::NINJAGO_MONASTERY, ObjectType::Minigame, "Frakjaw Battle"); //9
	initializeLaunchPad(70368748035363, ZoneId::NINJAGO_MONASTERY, ZoneId::NEXUS_TOWER);
	initializeLaunchPad(70368748035364, ZoneId::NINJAGO_MONASTERY, ZoneId::NEXUS_TOWER);

	initializeLaunchPad(70368748035995, ZoneId::PET_COVE, ZoneId::NIMBUS_STATION);
	initializeObject(70368748036113, ZoneId::PET_COVE, ObjectType::Binoculars, "Tower"); //9
	initializeObject(70368748036114, ZoneId::PET_COVE, ObjectType::Binoculars, "Jumper"); //9
	initializeObject(70368748036115, ZoneId::PET_COVE, ObjectType::Binoculars, "Bridge"); //9
	initializeObject(70368748036116, ZoneId::PET_COVE, ObjectType::Binoculars, "Launch Area"); //9
	initializeObject(70368748036250, ZoneId::PET_COVE, ObjectType::Plaque, "Pet Cove"); //9

	initializeLaunchPad(70368748055482, ZoneId::PORTABELLO, ZoneId::STARBASE_3001);

	initializeObject(70643622146017, ZoneId::CRUX_PRIME, ObjectType::PostBox, "Sentinel Point Zeta"); //1 9
	initializeObject(70643622146030, ZoneId::CRUX_PRIME, ObjectType::Plaque, "Sentinel Point Zeta"); //1 9
	initializeObject(70643622146035, ZoneId::CRUX_PRIME, ObjectType::Binoculars, "Sentinel Point Zeta"); // 1 9
	
	initializeObject(70918500266380, ZoneId::GNARLED_FOREST, ObjectType::Object, "Pirate Camp, Boat"); //0 9
	initializeObject(70918500266383, ZoneId::GNARLED_FOREST, ObjectType::Machine, "Pirate Camp, Bird Blockage"); //0 9
	initializeObject(70918500266432, ZoneId::GNARLED_FOREST, ObjectType::PostBox, "Pirate Camp"); //0 9
	initializeObject(70918500266460, ZoneId::GNARLED_FOREST, ObjectType::Binoculars, "Pirate Camp"); //0 9
	initializeObject(70918500266512, ZoneId::GNARLED_FOREST, ObjectType::Plaque, "Pirate Camp"); //0 9

	initializeObject(70918500270095, ZoneId::FORBIDDEN_VALLEY, ObjectType::PostBox, "Great Tree, Top"); //0 9
	initializeObject(70918500270182, ZoneId::FORBIDDEN_VALLEY, ObjectType::Binoculars, "Great Tree, Top, View Cavalry Hill"); //0 9
	initializeObject(70918500291607, ZoneId::NEXUS_TOWER, ObjectType::Binoculars, "Sentinel Training Chamber");
	initializeObject(70918500349608, ZoneId::AVANT_GARDENS, ObjectType::Binoculars, "Landing Area"); //0 9
	initializeObject(70918500349609, ZoneId::AVANT_GARDENS, ObjectType::Binoculars, "Paradox Research Facility"); //0 9
	initializeObject(70918500353520, ZoneId::NIMBUS_STATION, ObjectType::Plaque, "Red Blocks Amphitheatre"); //0 9

	initializeObject(71193378161101, ZoneId::NEXUS_TOWER, ObjectType::Vault, "Vault 1"); //0 1 9
	initializeObject(71193378161102, ZoneId::NEXUS_TOWER, ObjectType::Vault, "Vault 2"); //0 1 9
	initializeObject(71193378161103, ZoneId::NEXUS_TOWER, ObjectType::Vault, "Vault 3"); //0 1 9
	initializeObject(71193378161104, ZoneId::NEXUS_TOWER, ObjectType::Vault, "Vault 4"); //0 1 9
	initializeObject(71193378161105, ZoneId::NEXUS_TOWER, ObjectType::Vault, "Vault 5"); //0 1 9
	initializeObject(71193378161106, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Vault"); //0 1 9

	initializeObject(71193378196058, ZoneId::NIMBUS_STATION, ObjectType::Plaque, "Nimbus Station"); //0 1 9
	initializeObject(71193378197171, ZoneId::AVANT_GARDENS, ObjectType::Plaque, "Assembly Monument"); //0 1 9

	initializeObject(71193378197425, ZoneId::FORBIDDEN_VALLEY, ObjectType::Object, "Pond"); //0 1 9
	initializeObject(71193378197511, ZoneId::FORBIDDEN_VALLEY, ObjectType::PostBox, "Main Gate"); //0 1 9
	initializeObject(71193378197589, ZoneId::FORBIDDEN_VALLEY, ObjectType::Plaque, "Main Gate"); //0 1 9
	initializeObject(71193378197605, ZoneId::FORBIDDEN_VALLEY, ObjectType::Binoculars, "Launch Area"); //0 1 9

	initializeObject(71468255879625, ZoneId::FORBIDDEN_VALLEY, ObjectType::Binoculars, "The Great Tree"); //9 15
	initializeObject(71468255879626, ZoneId::FORBIDDEN_VALLEY, ObjectType::Plaque, "The Great Tree"); //9 15

	initializeObject(71468255900780, ZoneId::CRUX_PRIME, ObjectType::Machine, "Rivendark Canyon Bridge Console"); //9 15
	initializeObject(71468255950718, ZoneId::NINJAGO_MONASTERY, ObjectType::Binoculars, "Entrance");

	initializeObject(71743133775548, ZoneId::FORBIDDEN_VALLEY, ObjectType::Plaque, "Mantis Rock"); //1 9 15
	initializeObject(71743133781636, ZoneId::GNARLED_FOREST, ObjectType::Plaque, "Fort");
	initializeObject(71743133781654, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Sentinel War Room, Infected Bricks -> 5 Faction Tokens"); //1 9 15
	initializeObject(71743133781655, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Sentinel War Room, Red Imaginite -> Surprise"); //1 9 15
	initializeObject(71743133781658, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Sentinel War Room"); //1 9 15
	initializeObject(71743133781659, ZoneId::NEXUS_TOWER, ObjectType::PostBox, "Sentinel War Room"); //1 9 15
	initializeObject(71743133781667, ZoneId::NEXUS_TOWER, ObjectType::Binoculars, "Sentinel War Room Top");
	initializeObject(71743133789565, ZoneId::AVANT_GARDENS, ObjectType::Binoculars, "Assembly Monument"); //1 9 15
	initializeObject(71743133790046, ZoneId::NIMBUS_STATION, ObjectType::Binoculars, "Red Blocks Amphitheatre"); //1 9 15

	initializeObject(72018011732500, ZoneId::FORBIDDEN_VALLEY, ObjectType::Binoculars, "Cavalry Hill"); //0 9 15
	initializeObject(72018011738868, ZoneId::CRUX_PRIME, ObjectType::Plaque, "Maelstrom Quarry"); //0 9 15
	initializeObject(72018011738889, ZoneId::CRUX_PRIME, ObjectType::Binoculars, "Studburst Pass"); //0 9 15
	initializeObject(72018011738901, ZoneId::CRUX_PRIME, ObjectType::Binoculars, "Maelstrom Quarry"); //0 9 15
	initializeObject(72018011738902, ZoneId::CRUX_PRIME, ObjectType::Plaque, "Studburst Pass"); //0 9 15
	initializeObject(72018011739912, ZoneId::GNARLED_FOREST, ObjectType::Binoculars, "Race Place"); //0 9 15

	initializeObject(72018011766437, ZoneId::NIMBUS_STATION, ObjectType::Binoculars, "Plaza");

	initializeObject(72292889654081, ZoneId::FORBIDDEN_VALLEY, ObjectType::Plaque, "Cavalry Hill"); //0 1 9 15
	initializeObject(72292889655302, ZoneId::CRUX_PRIME, ObjectType::Plaque, "Caldera Mar"); //0 1 9 15
	initializeObject(72292889655743, ZoneId::GNARLED_FOREST, ObjectType::Binoculars, "Lake Entrance"); //0 1 9 15
	initializeObject(72292889655744, ZoneId::GNARLED_FOREST, ObjectType::Binoculars, "Lake"); //0 1 9 15
	initializeObject(72292889657051, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Sentinel Command Center"); //0 1 9 15
	initializeObject(72292889665739, ZoneId::AVANT_GARDENS, ObjectType::Binoculars, "Outpost"); //0 1 9 15
	initializeObject(72292889665740, ZoneId::AVANT_GARDENS, ObjectType::Machine, "Outpost Console"); //0 1 9 15
	initializeObject(72292889665744, ZoneId::AVANT_GARDENS, ObjectType::Plaque, "Paradox Research Facility"); //0 1 9 15
	initializeObject(72292889665947, ZoneId::NINJAGO_MONASTERY, ObjectType::Plaque, "Monastery of Spinjitzu"); //0 1 9 15
	initializeObject(72292889667055, ZoneId::NIMBUS_STATION, ObjectType::PostBox, "To Gnarled Forest"); //0 1 9 15
	initializeObject(72292889667069, ZoneId::NIMBUS_STATION, ObjectType::Binoculars, "To Gnarled Forest"); //0 1 9 15

	initializeObject(72567767517764, ZoneId::NIMBUS_STATION, ObjectType::Binoculars, "Brick Annex"); //9 14
	initializeObject(72567767517765, ZoneId::NIMBUS_STATION, ObjectType::PostBox, "Brick Annex"); //9 14
	initializeObject(72567767517778, ZoneId::NIMBUS_STATION, ObjectType::Plaque, "Brick Annex"); //9 14

	initializeObject(72842645471485, ZoneId::GNARLED_FOREST, ObjectType::PostBox, "Launch Pad"); //1 9 14
	initializeObject(72842645471542, ZoneId::GNARLED_FOREST, ObjectType::Binoculars, "Bridge Pond"); //1 9 14
	initializeObject(72842645471543, ZoneId::GNARLED_FOREST, ObjectType::Binoculars, "Bridge"); //1 9 14
	initializeObject(72842645471553, ZoneId::GNARLED_FOREST, ObjectType::Binoculars, "Launch Pad"); //1 9 14
	initializeObject(72842645471602, ZoneId::GNARLED_FOREST, ObjectType::Plaque, "Launch Pad"); //1 9 14
	initializeObject(72842645479744, ZoneId::NIMBUS_STATION, ObjectType::Binoculars, "To Forbidden Valley"); //1 9 14
	initializeObject(72842645480990, ZoneId::NIMBUS_STATION, ObjectType::Plaque, "Maelstrom Forcefield"); //1 9 14

	initializeObject(73117523384592, ZoneId::FORBIDDEN_VALLEY, ObjectType::Binoculars, "Paradox Maelstrom Refinery"); //0 9 14
	initializeObject(73117523384619, ZoneId::FORBIDDEN_VALLEY, ObjectType::Binoculars, "Paradox Maelstrom Refinery 3"); //0 9 14
	initializeObject(73117523384623, ZoneId::FORBIDDEN_VALLEY, ObjectType::Binoculars, "Paradox Maelstrom Refinery 2"); //0 9 14
	initializeObject(73117523384625, ZoneId::FORBIDDEN_VALLEY, ObjectType::Plaque, "Paradox Maelstrom Refinery"); //0 9 14
	initializeObject(73117523384630, ZoneId::FORBIDDEN_VALLEY, ObjectType::Binoculars, "Paradox Maelstrom Refinery 4"); //0 9 14
	initializeObject(73117523384637, ZoneId::FORBIDDEN_VALLEY, ObjectType::Binoculars, "Dragon"); //0 9 14
	initializeObject(73117523391546, ZoneId::NINJAGO_MONASTERY, ObjectType::PostBox, "Monastery Courtyard"); //0 9 14
	initializeObject(73117523391551, ZoneId::NINJAGO_MONASTERY, ObjectType::Binoculars, "Monastery Courtyard"); //0 9 14
	initializeObject(73117523401514, ZoneId::NIMBUS_STATION, ObjectType::Binoculars, "Path To Avant Gardens"); //0 9 14

	initializeObject(73392401181075, ZoneId::FORBIDDEN_VALLEY, ObjectType::Binoculars, "The Great Tree, 2"); //0 1 9 14
	initializeObject(73392401201346, ZoneId::NIMBUS_STATION, ObjectType::Portal, "To Starbase 3001, Brick Annex"); //0 1 9 14
	initializeObject(73392401202185, ZoneId::AVANT_GARDENS, ObjectType::Plaque, "Paradox Maelstrom Mines"); //0 1 9 14
	initializeObject(73392401208497, ZoneId::NINJAGO_MONASTERY, ObjectType::Plaque, "Monastery Courtyard"); //0 1 9 14

	initializeObject(73667279106949, ZoneId::NEXUS_TOWER, ObjectType::Binoculars, "Outer Platform"); //9 14 15
	initializeObject(73667279128744, ZoneId::AVANT_GARDENS, ObjectType::Binoculars, "Sentinel Encampment"); //9 14 15
	initializeObject(73667279128745, ZoneId::AVANT_GARDENS, ObjectType::Plaque, "Sentinel Encampment"); //9 14 15
	initializeObject(73667279128748, ZoneId::AVANT_GARDENS, ObjectType::PostBox, "Sentinel Encampment"); //9 14 15
	initializeObject(73667279133324, ZoneId::NIMBUS_STATION, ObjectType::WaterPot, "Brick Annex"); //9 14 15
	initializeObject(73667279133326, ZoneId::NIMBUS_STATION, ObjectType::Binoculars, "Brick Annex"); //9 14 15

	initializeObject(73942156985321, ZoneId::FORBIDDEN_VALLEY, ObjectType::Plaque, "Maelstrom Valley"); //1 9 14 15

	initializeObject(74217034937052, ZoneId::NIMBUS_STATION, ObjectType::Binoculars, "To Brick Annex"); //0 9 14 15
	initializeObject(74217034937466, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Nexus Naomi Hologram"); //0 9 14 15
	
	initializeObject(74491912819086, ZoneId::GNARLED_FOREST, ObjectType::Plaque, "Maelstrom Trench"); //0 1 9 14 15
	initializeObject(74491912839034, ZoneId::NIMBUS_STATION, ObjectType::PostBox, "Nexus Checkpoint");
	initializeObject(74491912839048, ZoneId::NIMBUS_STATION, ObjectType::Binoculars, "Nexus Checkpoint");
	initializeObject(74491912839052, ZoneId::NIMBUS_STATION, ObjectType::Plaque, "Nexus Checkpoint");

	initializeObject(74491912850866, ZoneId::NINJAGO_MONASTERY, ObjectType::Plaque, "Dojo of Earth"); //0 1 9 14 15
	initializeObject(74491912850869, ZoneId::NINJAGO_MONASTERY, ObjectType::Binoculars, "Dojo of Earth"); //0 1 9 14 15

	initializeObject(75041668653659, ZoneId::CRUX_PRIME, ObjectType::PostBox, "Mealstrom Quarry Rest"); //1 9 13

	initializeObject(75316546548795, ZoneId::CRUX_PRIME, ObjectType::Binoculars, "Maelstrom Eye"); //0 9 13

	initializeObject(75316546548974, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Venture League Map Room"); //0 9 13
	initializeObject(75316546548975, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Venture League Map Room"); //0 9 13
	initializeObject(75316546549183, ZoneId::NIMBUS_STATION, ObjectType::Plaque, "To Avant Gardens Lauch Pad"); //0 9 13
	initializeObject(75316546549184, ZoneId::NIMBUS_STATION, ObjectType::PostBox, "To Avant Gardens Lauch Pad"); //0 9 13

	initializeObject(75591424409874, ZoneId::NIMBUS_STATION, ObjectType::Binoculars, "To Red Blocks Amphitheatre"); //0 1 9 13
	initializeObject(75591424442068, ZoneId::NEXUS_TOWER, ObjectType::PostBox, "Venture League Map Room"); //0 1 9 13
	initializeObject(75591424442077, ZoneId::NEXUS_TOWER, ObjectType::Machine, "Canon to Venture League Observatory");
	initializeObject(75591424442078, ZoneId::NEXUS_TOWER, ObjectType::WaterPot, "Venture Lague Observatory"); //0 1 9 13
	initializeObject(75591424442081, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Venture Lague Observatory"); //0 1 9 13

	initializeObject(75591424453101, ZoneId::NINJAGO_MONASTERY, ObjectType::Plaque, "Dojo of Lightning"); //0 1 9 13

	initializeObject(75866302347039, ZoneId::CRUX_PRIME, ObjectType::Binoculars, "Rivendark Canyon, Above");
	initializeObject(75866302347041, ZoneId::CRUX_PRIME, ObjectType::Plaque, "Rivendark Canyon");
	initializeObject(75866302347053, ZoneId::CRUX_PRIME, ObjectType::Binoculars, "Rivendark Canyon");
	initializeObject(75866302347055, ZoneId::CRUX_PRIME, ObjectType::Machine, "Rivendark Canyon Bridge Console"); //9 13 15

	initializeObject(76416058130662, ZoneId::NIMBUS_STATION, ObjectType::Plaque, "Nexus Tower Progress");

	initializeObject(76690936104520, ZoneId::NINJAGO_MONASTERY, ObjectType::Plaque, "Dojo of Ice"); //0 1 9 13 15

	initializeObject(76965813951596, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Assembly Storerooms, Left"); // 9 13 14
	initializeObject(76965813951597, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Assembly Storerooms, Right"); // 9 13 14

	initializeObject(77240691855441, ZoneId::AVANT_GARDENS, ObjectType::Binoculars, "Broken Bridge");
	
	initializeObject(77515569774747, ZoneId::NEXUS_TOWER, ObjectType::PostBox, "Second Floor, Assembly Sector, Right"); //0 9 13 14
	initializeObject(77790447712134, ZoneId::NINJAGO_MONASTERY, ObjectType::Plaque, "Dojo of Fire"); //0 1 9 13 14

	initializeObject(78065325572326, ZoneId::AVANT_GARDENS, ObjectType::PostBox, "Launch Area"); //9 13 14 15
	initializeObject(78065325582716, ZoneId::NEXUS_TOWER, ObjectType::PostBox, "Second Floor, Assembly Sector, Left"); //9 13 14 15

	initializeObject(78615081386742, ZoneId::NINJAGO_MONASTERY, ObjectType::Plaque, "Ninjago Caves"); //0 9 13 14 15

	initializeObject(78616155129237, ZoneId::AVANT_GARDENS, ObjectType::Binoculars, "Launch Area, Left"); //0 9 13 14 15
	initializeObject(78616155129238, ZoneId::AVANT_GARDENS, ObjectType::Binoculars, "Launch Area, Right"); //0 9 13 14 15
	initializeObject(78616155129240, ZoneId::AVANT_GARDENS, ObjectType::Plaque, "Launch Area"); //0 9 13 14 15
	initializeObject(78616155129241, ZoneId::AVANT_GARDENS, ObjectType::Machine, "Launch Area, Drinkmachine"); //0 9 13 14 15

	initializeObject(78889959312587, ZoneId::NEXUS_TOWER, ObjectType::Machine, "Paradox Logo Machine");
	initializeObject(78889959312604, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Paradox Main Hall");
	initializeObject(78889959312605, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Paradox Laboratory");
	initializeObject(78889959312605, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Faction Leader");
	initializeObject(78889959312607, ZoneId::NEXUS_TOWER, ObjectType::PostBox, "Paradox Main Hall");
	initializeObject(78889959312610, ZoneId::NEXUS_TOWER, ObjectType::Machine, "Paradox Main Hall, Under right Stairwell");
	initializeObject(78889959327071, ZoneId::NINJAGO_MONASTERY, ObjectType::Binoculars, "Black Cave"); //0 1 9 13 14 15
	initializeObject(79439715114396, ZoneId::NEXUS_TOWER, ObjectType::Machine, "Paradox Sector, By Right Nexus Portal");
	initializeObject(79989470935540, ZoneId::NINJAGO_MONASTERY, ObjectType::Binoculars, "Ninjago Caves"); //0 1 9 12

	initializeObject(80539226748439, ZoneId::NEXUS_TOWER, ObjectType::Binoculars, "Nexus Core"); //1 9 2 15;
	initializeObject(80539226748440, ZoneId::NEXUS_TOWER, ObjectType::Plaque, "Nexus Core, Dr. Albert Overbuild"); //1 9 12 15
	

	initializeObject(86311662781347, ZoneId::NEXUS_TOWER, ObjectType::Portal, "To Starbase 3001, Assembly Sector");

	isObjectsInitialized = true;
}

ObjectInformation getObjectInformation(long long objectid){
	if (!isObjectsInitialized)initializeObjects();
	return Objects[objectid];
}

std::string getObjectDescription(ObjectInformation obj, long long objid){
	long long objidA = obj.objid;
	if (objidA == 0 && objid > -1) objidA = objid;

	std::stringstream ss;
	ss << "[" << objidA << "] ";
	ss << obj.zone << " ";
	switch (obj.type)
	{
	case ObjectType::Binoculars:
		ss << "Binoculars: ";
		break;
	case ObjectType::LaunchPad:
		ss << "to " << LaunchPads[objidA];
		ss << " via ROCKET ";
		break;
	case ObjectType::Machine:
		ss << "Machine:    ";
		break;
	case ObjectType::Minigame:
		ss << "Minigame:   ";
		break;
	case ObjectType::Object:
		ss << "Object:     ";
		break;
	case ObjectType::Plaque:
		ss << "Plaque:     ";
		break;
	case ObjectType::Portal:
		ss << "Portal:     ";
		break;
	case ObjectType::PostBox:
		ss << "PostBox:    ";
		break;
	case ObjectType::Vault:
		ss << "Vault:      ";
		break;
	case ObjectType::WaterPot:
		ss << "Waterpot:   ";
		break;
	case ObjectType::NONE:
		ss << "NOT REGISTERED!";
		return ss.str();
		break;
	default:
		ss << "???:        ";
		break;
	}
	ss << obj.info;
	return ss.str();
}

ZoneId getLaunchPadTarget(ObjectInformation obj){
	if (obj.type == ObjectType::LaunchPad){
		return LaunchPads[obj.objid];
	}
	return NO_ZONE;
}

void GameMSG::addSkill(long long charid, unsigned long skillid, unsigned long slot) {
	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 127);
	
	for (int i = 0; i < 5; i++) {
		bs->Write((bool)false);
	}

	bs->Write(skillid);
	bs->Write((bool)true);
	bs->Write(slot);
	bs->Write((bool)true);

	std::vector<SessionInfo> sessionsz = SessionsTable::getClientsInWorld(s.zone);
	for (unsigned int k = 0; k < sessionsz.size(); k++){
		WorldServer::sendPacket(bs, sessionsz.at(k).addr);
	}
}

void GameMSG::castActiveSkill(long long charid, unsigned long someNumber) {
	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 125);
	bs->Write(someNumber);

	std::vector<SessionInfo> sessionsz = SessionsTable::getClientsInWorld(s.zone);
	for (unsigned int k = 0; k < sessionsz.size(); k++){
		WorldServer::sendPacket(bs, sessionsz.at(k).addr);
	}
}

void GameMSG::addItemToInventoryClientSync(long long charid, long long objectID, long lotTemplate, long slotid, bool showFlyingLoot) {
	SystemAddress addr = SessionsTable::findCharacter(charid);

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 227);
	bool f_true = true, f_false = false;
	bs->Write(f_true);
	bs->Write(f_true);
	bs->Write(f_false);
	bs->Write(f_false);
	bs->Write((unsigned long)0);
	bs->Write(lotTemplate);
	
	for (auto i = 0; i < 4; i++) {
		bs->Write(f_false);
	}

	bs->Write(objectID);

	for (auto i = 0; i < 3; i++) {
		bs->Write((unsigned long)0);
	}

	bs->Write(showFlyingLoot);
	bs->Write(slotid);

	WorldServer::sendPacket(bs, addr);
}

void GameMSG::removeSkill(long long charid, unsigned long skillid) {
	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 128);
	bs->Write((bool)false);
	bs->Write(skillid);

	std::vector<SessionInfo> sessionsz = SessionsTable::getClientsInWorld(s.zone);
	for (unsigned int k = 0; k < sessionsz.size(); k++){
		WorldServer::sendPacket(bs, sessionsz.at(k).addr);
	}
}

//void GameMSG::setLoseCoinsOnDeath(long long charid, bool loseCoinsOnDeath) {
//	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));
//
//	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 128);
//	bs->Write(loseCoinsOnDeath);
//
//	std::vector<SessionInfo> sessionsz = SessionsTable::getClientsInWorld(s.zone);
//	for (unsigned int k = 0; k < sessionsz.size(); k++){
//		WorldServer::sendPacket(bs, sessionsz.at(k).addr);
//	}
//}

void GameMSG::playAnimation(long long charid, std::wstring animationID, bool playImmediate) {
	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 43);
	bs->Write((unsigned long)animationID.size());

	for (int i = 0; i < animationID.size(); i++) {
		bs->Write((char)animationID.at(i));
		bs->Write((char)0);
	}

	bs->Write((bool)true);
	bs->Write(playImmediate);
	bs->Write((bool)true);

	std::vector<SessionInfo> sessionsz = SessionsTable::getClientsInWorld(s.zone);
	for (unsigned int k = 0; k < sessionsz.size(); k++){
		WorldServer::sendPacket(bs, sessionsz.at(k).addr);
	}
}

void GameMSG::setName(long long charid, std::wstring name) {
	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 72);
	bs->Write((unsigned long)name.size());

	for (int i = 0; i < name.size(); i++) {
		bs->Write((char)name.at(i));
		bs->Write((char)0);
	}

	std::vector<SessionInfo> sessionsz = SessionsTable::getClientsInWorld(s.zone);
	for (unsigned int k = 0; k < sessionsz.size(); k++){
		WorldServer::sendPacket(bs, sessionsz.at(k).addr);
	}
}

void GameMSG::displayMessageBox(long long charid, long long callbackClient, std::wstring identifier, std::wstring text, std::wstring userData) {
	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 0x0211);
	bs->Write(true);
	bs->Write(callbackClient);

	bs->Write((unsigned long)identifier.size());
	for (int i = 0; i < identifier.size(); i++) {
		bs->Write((char)identifier.at(i));
		bs->Write((char)0);
	}

	bs->Write((long)0);

	bs->Write((unsigned long)text.size());
	for (int i = 0; i < text.size(); i++) {
		bs->Write((char)text.at(i));
		bs->Write((char)0);
	}

	bs->Write((unsigned long)userData.size());
	for (int i = 0; i < userData.size(); i++) {
		bs->Write((char)userData.at(i));
		bs->Write((char)0);
	}

	std::vector<SessionInfo> sessionsz = SessionsTable::getClientsInWorld(s.zone);
	for (unsigned int k = 0; k < sessionsz.size(); k++){
		WorldServer::sendPacket(bs, sessionsz.at(k).addr);
	}
}

void GameMSG::displayZoneSummary(long long charid, bool isProperty, bool isZoneStart) {
	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 1043);
	bs->Write(isProperty);
	bs->Write(isZoneStart);
	bs->Write((unsigned long long)charid);

	WorldServer::sendPacket(bs, s.addr);
}

void GameMSG::teleport(long long charid, COMPONENT1_POSITION position) {
	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 19);
	bs->Write(false);
	bs->Write(false);
	bs->Write(false);

	bs->Write(position.x);
	bs->Write(position.y);
	bs->Write(position.z);

	std::vector<SessionInfo> sessionsz = SessionsTable::getClientsInWorld(s.zone);
	for (unsigned int k = 0; k < sessionsz.size(); k++){
		WorldServer::sendPacket(bs, sessionsz.at(k).addr);
	}
}

void GameMSG::smash(long long objid, bool ignoreObjectVisibility, float force, float ghostOpacity, long long killerID) { // TODO: Fix!
	WorldObjectInfo info = WorldObjectsTable::getObjectInfo(objid);

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(objid, 531);
	bs->Write(ignoreObjectVisibility);
	bs->Write(force);
	bs->Write(ghostOpacity);
	bs->Write(killerID);

	std::vector<SessionInfo> sessionsz = SessionsTable::getClientsInWorld(info.zone);
	for (unsigned int k = 0; k < sessionsz.size(); k++){
		WorldServer::sendPacket(bs, sessionsz.at(k).addr);
	}
}

void GameMSG::setJetPackMode(long long charid, bool bypassChecks, bool doHover, bool use) { // TODO: Fix!
	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 0x0231);
	bs->Write(bypassChecks);
	bs->Write(doHover);
	bs->Write(use);

	bs->Write(false); // effectID
	bs->Write(false); // airSpeed
	bs->Write(false); // maxAirSpeed
	bs->Write(false); // vertVel
	bs->Write(false); // warningEffectID

	WorldServer::sendPacket(bs, s.addr);
}

void GameMSG::dropClientLoot(long long charid, float posX, float posY, float posZ, long currency, unsigned long LOT, long long objid, long long ownerid, long long sourceid) {
	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 0x001e);
	bs->Write(true);

	bs->Write(true);
	bs->Write(posX);
	bs->Write(posY);
	bs->Write(posZ);

	bs->Write(currency);

	bs->Write(LOT);
	bs->Write(objid);

	bs->Write(ownerid);
	bs->Write(sourceid);

	bs->Write(true);
	bs->Write(posX);
	bs->Write(posY);
	bs->Write(posZ);

	WorldServer::sendPacket(bs, s.addr);
}

void GameMSG::knockback(long long charid, long long casterid, float vecX, float vecY, float vecZ) {
	SessionInfo s = SessionsTable::getClientSession(SessionsTable::findCharacter(charid));

	RakNet::BitStream *bs = WorldServerPackets::InitGameMessage(charid, 0x00ca);
	if (casterid > 0) {
		bs->Write(true);
		bs->Write(casterid);
		bs->Write(true);
		bs->Write(casterid);
	}
	else {
		bs->Write(false);
		bs->Write(false);
	}

	bs->Write(false);

	bs->Write(vecX);
	bs->Write(vecY);
	bs->Write(vecZ);

	WorldServer::sendPacket(bs, s.addr);
}
