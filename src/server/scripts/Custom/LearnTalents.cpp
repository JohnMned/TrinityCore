#include "Player.h"
#include "ScriptedGossip.h"
#include "WorldSession.h"
#include "ScriptedCreature.h"
#include "Creature.h"
#include "DBCStores.h"
#include "DBCStructure.h"
#include "Language.h"
#include "SpellMgr.h"
#include "Chat.h"

class npc_learn_talents : public CreatureScript
{
public:
	npc_learn_talents() : CreatureScript("npc_learn_talents") {}

	bool OnGossipHello(Player* player, Creature* creature) override
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Learn All my talents", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Nevermind..", GOSSIP_SENDER_MAIN, 2222);
		player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction) override
	{
		player->PlayerTalkClass->ClearMenus();

		if (uiSender != GOSSIP_SENDER_MAIN)
            return false;
		
		if (uiAction == 1)
		{
			uint32 classMask = player->getClassMask();

			for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
			{
				TalentEntry const* talentInfo = sTalentStore.LookupEntry(i);
				if (!talentInfo)
					continue;

				TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);
				if (!talentTabInfo)
					continue;

				if ((classMask & talentTabInfo->ClassMask) == 0)
					continue;

				// search highest talent rank
				uint32 spellId = 0;
				for (int8 rank = MAX_TALENT_RANK - 1; rank >= 0; --rank)
				{
					if (talentInfo->RankID[rank] != 0)
					{
						spellId = talentInfo->RankID[rank];
						break;
					}
				}

				if (!spellId)                                        // ??? none spells in talent
					continue;

				SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
				if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player->GetSession()->GetPlayer(), false))
					continue;

				// learn highest rank of talent and learn all non-talent spell ranks (recursive by tree)
				player->LearnSpellHighestRank(spellId);
				player->AddTalent(spellId, player->GetActiveSpec(), true);
			}

			player->SetFreeTalentPoints(0);
			player->SendTalentsInfoData(false);
			ChatHandler(player->GetSession()).SendSysMessage(LANG_COMMAND_LEARN_CLASS_TALENTS);
			player->PlayerTalkClass->SendCloseGossip();
			return true;
		}
		if (uiAction == 2222)
		{
			player->PlayerTalkClass->SendCloseGossip();
			return true;
		}
		return true;
	}
	
};
void AddSC_npc_learn_talents()
{
    new npc_learn_talents();
}