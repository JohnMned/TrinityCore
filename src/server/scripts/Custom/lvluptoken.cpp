//Script Created and Tested by carcar21
//Script Created for Sovereign-WoW (http://www.nelthorya.net/Sovereign)

    #include "ScriptPCH.h"
     
    enum
    {
    item_id = 789000,
    max_lvl = 85,
	lvlup = 85,
     };
     
    class item_level : public ItemScript
    {
    public:
        item_level() : ItemScript("item_level") { }
     
        bool OnUse(Player* player, Item* item, const SpellCastTargets &)
        {
                    if(player->IsInCombat())
                    {
                            player->GetSession()->SendNotification("You can't use your leveling token right now as you are currently in combat.");
                            return false;
                    }
                    if(player->getLevel() == max_lvl)
                    {
                            player->GetSession()->SendNotification("You are already level 85. You can send this token to another character on your account!");
                            return false;
                    }
                    player->SetLevel(lvlup);
                    player->DestroyItemCount(item_id, 1, true);
                    player->GetSession()->SendNotification("Your leveling token has now deteriorated, but you have finally reached level 85!");
                    return true;
                    }
    };
     
    void AddSC_item_level()
    {
        new item_level();
    }