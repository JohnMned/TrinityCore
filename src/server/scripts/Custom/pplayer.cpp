/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//// MADE BY: encrypted //// DO NOT RIP! ////////////////////
//// TrinityCore C++    //// DI NOT CLAIM IT YOURS! /////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////



#include "ScriptPCH.h"
#include "Chat.h"
#include "InstanceSaveMgr.h"
 
class PlayerCommands : public CommandScript
{
public:
        PlayerCommands() : CommandScript("PlayerCommands"){}
 
        ChatCommand * GetCommands() const
        {
                static ChatCommand PlayerCommandsCommandTable[] =
                {
                        {"start", SEC_PLAYER, false, &HandleStartCommand, "", NULL},
                        {"maxskills", SEC_PLAYER, false, &HandleMaxSkillsCommand, "", NULL},
                        {"resetcombat", SEC_PLAYER, false, &HandleResetCombatCommand, "", NULL},
                        {"vault", SEC_PLAYER, false, &HandleVaultCommand, "", NULL},
                        {NULL, 0, false, NULL, "", NULL}
                };
 
                return PlayerCommandsCommandTable;
        }
		
        static bool HandleStartCommand(ChatHandler * handler, const char * args)
        {
                Player* player = handler->GetSession()->GetPlayer();
 
                if (player->IsInFlight() || player->IsInCombat())
                {
                        handler->SendSysMessage("Cannot do that while combat or flying.");
                        handler->SetSentErrorMessage(true);
                        return false;
                }
 
                if (player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
                {
                        player->ResurrectPlayer(100);
                        player->TeleportTo(player->GetStartPosition());
						handler->PSendSysMessage("|cff00E5EEYou have been revived and teleported to the |cffff0000Mall|cff00E5EE, enjoy !!");
                        return true;
                }
 
                player->SetFullHealth();
                player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
				player->TeleportTo(player->GetStartPosition());
				handler->PSendSysMessage("|cff00E5EEYou have been healed and teleported to the |cffff0000Mall|cff00E5EE, enjoy !!"); //send message
                return true;
        }
		
        static bool HandleMaxSkillsCommand(ChatHandler* handler, const char* args)
        {
 
                Player* player = handler->GetSession()->GetPlayer();
 
                if (player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
                {
                        player->GetSession()->SendNotification("You can't chat when you're dead!");
                        handler->SetSentErrorMessage(true);
                        return false;
                }
 
                player->UpdateSkillsToMaxSkillsForLevel();
                return true;
        }
		
		static bool HandleResetCombatCommand(ChatHandler * handler, const char * args)
		{
			Player* player = handler->GetSession()->GetPlayer();

			if (player->IsInCombat())
			{
				player->CombatStop();
				PreparedStatement * mt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_MUTE_TIME);
				int64 muteTime = time(NULL) + 5;
				player->GetSession()->m_muteTime = muteTime;
				mt->setInt64(0, muteTime);
				return true;
			}
			return true;
		}
        static bool HandleVaultCommand(ChatHandler * handler, const char * args)
        {
                Player* player = handler->GetSession()->GetPlayer();
 
                if (player->IsInFlight() || player->IsInCombat())
                {
                        handler->SendSysMessage("Cannot do that while combat or flying.");
                        handler->SetSentErrorMessage(true);
                        return false;
                }
 
                if (player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
                {
                        player->GetSession()->SendNotification("You can't chat when you're dead!");
                        handler->SetSentErrorMessage(true);
                        return false;
                }
 
                handler->GetSession()->SendShowBank(handler->GetSession()->GetPlayer()->GetGUID());
                return true;
        }
};
 
void AddSC_PlayerCommands()
{
        new PlayerCommands();
}