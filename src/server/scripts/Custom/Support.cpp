/*
<--------------------------------------------------------------------------->
 - Developer(s): Ghostcrawler336
 - Complete: %100
 - ScriptName: 'Ingame Support NPC(npc_info)' 
 - Comment: N/A
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

class npc_info : public CreatureScript
{
	public:
		npc_info() : CreatureScript("npc_info")
		{
		}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Spell_Holy_SealOfSacrifice:25|tServer Info !", GOSSIP_SENDER_MAIN, 0);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Spell_Shadow_SacrificialShield:25|tPatch Problem !?", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Achievement_Quests_Completed_08:25|tWhere can i start ??", GOSSIP_SENDER_MAIN, 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Mail_GMIcon:25|tNevermind...", GOSSIP_SENDER_MAIN, 3);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;
			
			switch(uiAction)
			{
				case 0: // This case will send the support message for "How Do I get Gold?"
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("Server Info : ||Start Level 55 & levelup to 85|| ||Server rates||=||Rate.XP.Kill = 10||Rate.XP.Quest = 75||Rate.XP.Explore = 5||. ", Player->GetName());
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 1: // This case will send the support message for "How Do I Make A Ticket?
					{

						ChatHandler(Player->GetSession()).PSendSysMessage("Be sure always to download Patch-A.MPQ from our website LINK : 'http://yugowow.com/Patch-A.Rar', Patch-A is very important as he'll fix your weapon melee bug and you're also able to see the correct items and their prices!", Player->GetName());
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 2: // This case will send the support message for "How Do I Gear Up?"
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("Always start leveling using, Server Teleporter --> Leveling Zone --> and than gear up by doing PVP - PVE or Quest's etc..", Player->GetName());
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 3:
					{
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			}
			return true;
		}

};

void AddSC_npc_info()
{
	new npc_info();
}