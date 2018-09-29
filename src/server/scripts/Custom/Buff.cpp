/*
<--------------------------------------------------------------------------->
 - Developer(s): Ghostcrawler336
 - Made By: ??
 - Updated by: JadaDev
 - Complete: 100%
 - ScriptName: 'Buff Command'
 - Comment: Tested & Working
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"
#include "Chat.h"
 
 
uint32 auras[] = {31583, 24705, 23735, 23736, 23737, 23738, 23766, 23767, 23768, 23769, 48162, 48074, 48170, 43223, 43002, 467, 15366, 48470, 26393, 47440, 33377, 33779, 31305};
 
class buffcommand : public CommandScript
{
public:
    buffcommand() : CommandScript("buffcommand") { }
 
        ChatCommand* GetCommands() const
    {
        static ChatCommand IngameCommandTable[] =
        {
        { "buff",           rbac::RBAC_PERM_COMMAND_BUFF,         true,  &HandleBuffCommand,                "", NULL },
        { NULL,             0,                  false, NULL,                              "", NULL }
        };
                 return IngameCommandTable;
    }
 
        static bool HandleBuffCommand(ChatHandler * handler, const char * args)
    {
        Player * pl = handler->GetSession()->GetPlayer();
                if(pl->InArena())
                {
                        pl->GetSession()->SendNotification("You can't use that item in an arena match!");
                        return false;
                }
       
                pl->RemoveAurasByType(SPELL_AURA_MOUNTED);
                for(int i = 0; i < 23; i++)
                    pl->AddAura(auras[i], pl);
                handler->PSendSysMessage("|cffB400B4You have been buffed, enjoy!");
                return true;
 
    }
};
 
void AddSC_buffcommand()
{
    new buffcommand();
}