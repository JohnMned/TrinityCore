class honorable_kills_shoptwo : public CreatureScript
{
public:
	honorable_kills_shoptwo() : CreatureScript("hk_kills_shop2") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Ability_Paladin_BlessedHands:25|t[Lifetime Kills are required in order to view my goods. Make sure you have it, or you won't be able to view nor purchase anything from my epic items !.]", GOSSIP_SENDER_MAIN, 1001); //first menu option - a note for what this creature is
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Achievement_PVP_O_05:25|t[1000 kills] Show me what you got!", GOSSIP_SENDER_MAIN, 1002); //second option, click to send to the vendor (if he has 5k kills)
		player->SEND_GOSSIP_MENU(1, creature->GetGUID()); // This sends the menu to the player
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*uiSender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		switch (action)
		{
			///////////START ACTIONS//////////////////
		case 1001:
			player->CLOSE_GOSSIP_MENU();
			break;
		

		case 1002:
			if (player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS) >= 1000)
			{
				player->GetSession()->SendListInventory(pCreature->GetGUID()), //send to the vendor himself. add items via .npc add item command
					pCreature->Whisper("You have 1000 kills or more, therefore you can view my goods.", LANG_UNIVERSAL, player); //if the player has 5k kills, send this message when 
			}
			else
			{
				pCreature->Whisper("You do not have 1000 kills or more, therefore I cannot allow you to check my store. Sorry.", LANG_UNIVERSAL, player), player->CLOSE_GOSSIP_MENU(); //send this "error" message and close everything
			}
			break;
	}
		return true;
	}
};

void AddSC_honorable_kills_shoptwo()
{
	new honorable_kills_shoptwo();
}