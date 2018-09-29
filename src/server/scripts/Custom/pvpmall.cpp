#include "ScriptPCH.h"
#include "Chat.h"


class mall_commandscript : public CommandScript
{
public:
	mall_commandscript() : CommandScript("mall_commandscript") { }

	ChatCommand* GetCommands() const
	{
		static ChatCommand IngameCommandTable[] =
		{
			{ "mall", rbac::RBAC_PERM_COMMAND_RELOAD_AREATRIGGER_TELEPORT, false, &HandleMallCommand, "", NULL },
			{ NULL, 0, false, NULL, "", NULL }
		};
		return IngameCommandTable;
	}

	static bool HandleMallCommand(ChatHandler * handler, const char * args) //MALL COMMAND
	{
		Player * me = handler->GetSession()->GetPlayer();

		if  (me->IsInCombat())
			handler->PSendSysMessage("|cffff0000You are in Combat!|r");
		else
		{
			me->TeleportTo(530, 281.041748f, 5999.461426f, 144.730270f, 1.598671f), //if not in combat - teleport
			handler->PSendSysMessage("|cff00E5EEYou have been teleported to the |cffff0000Mall!"); //send message
		}
        return true;
		}

};

void AddSC_Ingame_commandscript()
{
	new mall_commandscript();
}
