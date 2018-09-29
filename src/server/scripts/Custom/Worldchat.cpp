#include "ScriptPCH.h"
#include "Chat.h"
 
#define FACTION_SPECIFIC 0
 
std::string GetNameLink(Player* player)
{
        std::string name = player->GetName();
        std::string color;
        switch(player->getClass())
        {
        case CLASS_DEATH_KNIGHT:
                color = "|TInterface\\icons\\Spell_Deathknight_ClassIcon:15|t|cffC41F3B";
                break;
        case CLASS_DRUID:
                color = "|TInterface\\icons\\INV_Misc_MonsterClaw_04:15|t|cffFF7D0A";
                break;
        case CLASS_HUNTER:
                color = "|TInterface\\icons\\INV_Weapon_Bow_07:15|t|cffABD473";
                break;
        case CLASS_MAGE:
                color = "|TInterface\\icons\\INV_Staff_13:15|t|cff69CCF0";
                break;
        case CLASS_PALADIN:
                color = "|TInterface\\icons\\Ability_ThunderBolt:15|t|cffF58CBA";
                break;
        case CLASS_PRIEST:
                color = "|TInterface\\icons\\INV_Staff_30:15|t|cffFFFFFF";
                break;
        case CLASS_ROGUE:
                color = "|TInterface\\icons\\INV_ThrowingKnife_04:15|t|cffFFF569";
                break;
        case CLASS_SHAMAN:
                color = "|TInterface\\icons\\Spell_Nature_BloodLust:15|t|cff0070DE";
                break;
        case CLASS_WARLOCK:
                color = "|TInterface\\icons\\Spell_Nature_Drowsy:15|t|cff9482C9";
                break;
        case CLASS_WARRIOR:
                color = "|TInterface\\icons\\INV_Sword_27:15|t|cffC79C6E";
                break;
        }
        return "|Hplayer:"+name+"|h|cffFFFFFF["+color+name+"|cffFFFFFF]|h|r";
}
 
class world_chat : public CommandScript
{
        public:
        world_chat() : CommandScript("world_chat"){}

		static bool HandleWorldChatCommand(ChatHandler * pChat, const char * args)
		{
			if (!pChat->GetSession()->GetPlayer()->CanSpeak())
				return false;
			std::string temp = args;

			if (!args || temp.find_first_not_of(' ') == std::string::npos)
				return false;

			std::string msg = "";
			Player * player = pChat->GetSession()->GetPlayer();

			switch (player->GetSession()->GetSecurity())
			{
				// Player
			case SEC_PLAYER:
				if (player->GetTeam() == ALLIANCE)
				{
					msg += "|TInterface\\icons\\INV_Bijou_Blue:15|t|cff0000ff[A] ";
					msg += GetNameLink(player);
					msg += " |cfffaeb00";
				}

				else
				{
					msg += "|TInterface\\icons\\INV_Bijou_Red:15|t|cffff0000[H] ";
					msg += GetNameLink(player);
					msg += " |cfffaeb00";
				}
				break;
				// V.I.P
			case SEC_MODERATOR:
				if (player->GetTeam() == ALLIANCE)
				{
					msg += "|TInterface\\icons\\Achievement_PVP_A_A:15|t|cffB70093|A]|cffFFFFFF[Donator] ";
					msg += GetNameLink(player);
					msg += " |cffcaca00";
				}
				
				else
				{
					msg += "|TInterface\\icons\\Achievement_PVP_H_H:15|t|cffB70093|H]|cffFFFFFF[Donator] ";
					msg += GetNameLink(player);
					msg += " |cffcaca00";
				}
				break;
				// GM
			case SEC_GAMEMASTER:
				msg += "|TInterface\\icons\\Mail_GMIcon:15|t|cffFFFFFF™|cffFF0000[GM] ";
				msg += GetNameLink(player);
				msg += " |cffb0b000";
				break;
				// Admin
			case SEC_ADMINISTRATOR:
				msg += "|TInterface\\icons\\Mail_GMIcon:15|t|cffFFFFFF™|cffFF0000[Staff] ";
				msg += GetNameLink(player);
				msg += " |cffb0b000";
				break;
				// Console
			case SEC_CONSOLE:
				msg += "|TInterface\\icons\\Mail_GMIcon:15|t|cffFF0000";
				msg += " ";
				break;

			}

			msg += args;
			if (FACTION_SPECIFIC)
			{
				SessionMap sessions = sWorld->GetAllSessions();
				for (SessionMap::iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
					if (Player* plr = itr->second->GetPlayer())
						if (plr->GetTeam() == player->GetTeam())
							sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), plr);
			}
			else
				sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);

			return true;

		}
 
		ChatCommand * GetCommands() const
		{
			static ChatCommand HandleWorldChatCommandTable[] =
			{
				{ "world", rbac::RBAC_PERM_COMMAND_CHANNEL, true, &HandleWorldChatCommand, "", NULL },
				{ NULL, 0, false, NULL, "", NULL }
			};
			return HandleWorldChatCommandTable;
		}
};
 
void AddSC_world_chat()
{
        new world_chat();
}