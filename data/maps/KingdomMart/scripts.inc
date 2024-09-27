KingdomMart_MapScripts::
	.byte 0

KingdomMart_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart KingdomMart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
KingdomMart_Pokemart:
	.2byte ITEM_RED_ORB
	.2byte ITEM_MEGA_RING
	.2byte ITEM_BLUE_ORB
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_GRISEOUS_ORB
	.2byte ITEM_MASTER_BALL
	.2byte ITEM_Z_POWER_RING
	.2byte ITEM_DYNAMAX_BAND
	.2byte ITEM_ULTRANECROZIUM_Z
	.2byte ITEM_DNA_SPLICERS
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

