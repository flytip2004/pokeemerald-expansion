Lightless_world02_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, Light2_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Light2_OnLoad
	map_script MAP_SCRIPT_ON_RESUME, Light2_OnResume
	.byte 0

Light2_OnTransition:
	call_if_set FLAG_DEFEATED_UNECROZMA , Light2_EventScript_HideUNecrozma
	call_if_unset FLAG_DEFEATED_UNECROZMA , Light2_EventScript_TryShowUNecrozma
	end

Light2_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Light2_EventScript_TryRemoveUNecrozma
	call_if_unset FLAG_DEFEATED_UNECROZMA, Light2_EventScript_HideUltraEntrance
	end

Light2_OnLoad:
	call_if_unset FLAG_DEFEATED_UNECROZMA, Light2_EventScript_HideUltraEntrance
	call_if_set FLAG_DEFEATED_UNECROZMA, Light2_EventScript_OpenUltraEntrance
	end

Light2_EventScript_HideUltraEntrance::
	setmetatile 9, 15, METATILE_Cave_EntranceCover, TRUE
	setmetatile 9, 16, METATILE_Cave_EntranceCover, TRUE
	return

Light2_EventScript_OpenUltraEntrance::
	setmetatile 9, 14, METATILE_Cave_SealedChamberEntrance_TopMid, TRUE
	setmetatile 9, 15, METATILE_Cave_SealedChamberEntrance_BottomMid, FALSE
	end

Light2_EventScript_CaveEntrance::
	lockall
	goto_if_set FLAG_DEFEATED_DNECROZMA, Light2_EventScript_BigHoleInWall
	end

Light2_EventScript_BigHoleInWall::
	msgbox gText_BigHoleInTheWall, MSGBOX_DEFAULT
	releaseall
	end

Light2_EventScript_HideUNecrozma::
	setflag FLAG_HIDE_UNECROZMA
	return

Light2_EventScript_TryShowUNecrozma::
	goto_if_set FLAG_DEFEATED_UNECROZMA, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_UNECROZMA
	return

Light2_EventScript_TryRemoveUNecrozma::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Light2_EventScript_UNecrozma::
	lockall
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_NECROZMA_ULTRA, 90
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	setflag B_FLAG_NO_CATCHING
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Light2_EventScript_DefeatedUNecrozma
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Light2_EventScript_RanFromUNecrozma
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Light2_EventScript_RanFromUNecrozma
	release
	end
	
Light2_EventScript_DefeatedUNecrozma::
	clearflag B_FLAG_NO_CATCHING
	setflag FLAG_DEFEATED_UNECROZMA
	setvar VAR_0x8004, SPECIES_NECROZMA_ULTRA
	goto Common_EventScript_LegendaryFlewAway
	end

Light2_EventScript_RanFromUNecrozma::
	clearflag B_FLAG_NO_CATCHING
	setvar VAR_0x8004, SPECIES_NECROZMA_ULTRA
	goto Common_EventScript_LegendaryFlewAway
	end

