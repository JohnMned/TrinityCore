/*
Made by: Ghostcrawler
Updated by : JadaDev
Script Info : VIP Commands Script
Compile : Success.
Note : Contacted Ghostcrawler, and he allowed to share this !
*/
#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Chat.h"
#include "Common.h"
#include "Language.h"
 
class vipcommands : public CommandScript
{
public:
    vipcommands() : CommandScript("vipcommands") { }
 
    ChatCommand* GetCommands() const
    {
        static ChatCommand vipCommandTable[] =
 
        {
            { "mall",       SEC_MODERATOR,     true, &HandleVipMallCommand,         "", NULL },
            { "changerace",    SEC_MODERATOR,  false, &HandleChangeRaceCommand,             "", NULL },
            { "changefaction",  SEC_MODERATOR,  false, &HandleChangeFactionCommand,             "", NULL },
            { "customize",      SEC_MODERATOR,  false, &HandleCustomizeCommand,         "", NULL },
            { "tele",           SEC_MODERATOR,  false, &HandleTeleCommand,              "", NULL },
			{ "heal",           SEC_MODERATOR,  false, &HandleHealCommand,              "", NULL },
			{ "gear",       SEC_MODERATOR,     true, &HandleVipgearCommand,         "", NULL },
 
            { NULL,             0,                     false, NULL,                                           "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "vip",        SEC_MODERATOR,   true, NULL,      "",  vipCommandTable},
               { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }
 
 
 
static bool HandleTeleCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;
 
        Player* me = handler->GetSession()->GetPlayer();
 
        // id, or string, or [name] Shift-click form |color|Htele:id|h[name]|h|r
        GameTele const* tele = handler->extractGameTeleFromLink((char*)args);
 
        if (!tele)
        {
            handler->SendSysMessage(LANG_COMMAND_TELE_NOTFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }
 
        if (me->IsInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }
 
        MapEntry const* map = sMapStore.LookupEntry(tele->mapId);
        if (!map || map->IsBattlegroundOrArena())
        {
            handler->SendSysMessage(LANG_CANNOT_TELE_TO_BG);
            handler->SetSentErrorMessage(true);
            return false;
        }
 
        // stop flight if need
        if (me->IsInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();
 
        me->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
        return true;
                }
 
static bool HandlevipCommand(ChatHandler* handler, const char* args)
    {
 
        Player* me = handler->GetSession()->GetPlayer();
 
            me->Say("vip command?", LANG_UNIVERSAL);
            return true;
    }
 
static bool HandleHealCommand(ChatHandler * handler, const char * args)
{
	Player * me = handler->GetSession()->GetPlayer();

	if (me->IsInCombat())
	{
		handler->SendSysMessage(LANG_YOU_IN_COMBAT);
		handler->SetSentErrorMessage(true);
		return false;
	}
	else
		me->SetHealth(me->GetMaxHealth());
		handler->PSendSysMessage("You Have Been Healed!");
		return true;
	
}
 
static bool HandleChangeRaceCommand(ChatHandler* handler, const char* args)
    {
 
        Player* me = handler->GetSession()->GetPlayer();
                me->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
                handler->PSendSysMessage("Relog to change race of your character.");
        return true;
    }
 
static bool HandleChangeFactionCommand(ChatHandler* handler, const char* args)
    {
 
        Player* me = handler->GetSession()->GetPlayer();
                me->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                handler->PSendSysMessage("Relog to change faction of your character.");
        return true;
    }
 
 
static bool HandleCustomizeCommand(ChatHandler* handler, const char* args)
    {
 
        Player* me = handler->GetSession()->GetPlayer();
                me->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
                handler->PSendSysMessage("Relog to customize your character.");
        return true;
    }
 
static bool HandleVipMallCommand(ChatHandler* handler, const char* args)
    {
 
        Player* me = handler->GetSession()->GetPlayer();
 
        if (me->IsInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }
 
        // stop flight if need
        if (me->IsInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();
 
                me->TeleportTo(0,       23.8378f,       -1588.85f,      195.419f,       4.54306f); // MapId, X, Y, Z, O
                return true;
    }
 
  
static bool HandleVipgearCommand(ChatHandler* handler, const char* args)
    {
 
        Player* me = handler->GetSession()->GetPlayer();
 
        if (me->IsInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }
 
        // stop flight if need
        if (me->IsInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();
 
                me->TeleportTo(13,       123.460609f,       -119.202065f,      -144.708664f,       6.278389f); // MapId, X, Y, Z, O
                return true;
    }
       
       
};
 
void AddSC_vipcommands()
{
    new vipcommands();
}