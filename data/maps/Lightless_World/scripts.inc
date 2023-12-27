Lightless_World_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Light_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Light_OnLoad
	map_script MAP_SCRIPT_ON_RESUME, Light_OnResume
	.byte 0

Light_OnTransition:
	call_if_set FLAG_DEFEATED_UNECROZMA , Light_EventScript_HideNecrozma
	call_if_unset FLAG_DEFEATED_UNECROZMA , Light_EventScript_TryShowNecrozma
	call_if_set FLAG_DEFEATED_DNECROZMA , Light_EventScript_HideDNecrozma
	call_if_unset FLAG_DEFEATED_DNECROZMA , Light_EventScript_TryShowDNecrozma
	end

Light_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Light_EventScript_TryRemoveDNecrozma
	call_if_unset FLAG_DEFEATED_DNECROZMA, Light_EventScript_HideUltraEntrance
	end

Light_OnLoad:
	call_if_unset FLAG_DEFEATED_DNECROZMA, Light_EventScript_HideUltraEntrance
	call_if_set FLAG_DEFEATED_DNECROZMA, Light_EventScript_OpenUltraEntrance
	end

Light_EventScript_HideUltraEntrance::
	setmetatile 9, 14, METATILE_Cave_EntranceCover, TRUE
	setmetatile 9, 15, METATILE_Cave_EntranceCover, TRUE
	return

Light_EventScript_OpenUltraEntrance::
	setmetatile 9, 14, METATILE_Cave_SealedChamberEntrance_TopMid, TRUE
	setmetatile 9, 15, METATILE_Cave_SealedChamberEntrance_BottomMid, FALSE
	end

Light_EventScript_CaveEntrance::
	lockall
	goto_if_set FLAG_DEFEATED_DNECROZMA, Light_EventScript_BigHoleInWall
	end

Light_EventScript_BigHoleInWall::
	msgbox gText_BigHoleInTheWall, MSGBOX_DEFAULT
	releaseall
	end

Light_EventScript_HideDNecrozma::
	setflag FLAG_HIDE_DNECROZMA
	return

Light_EventScript_TryShowDNecrozma::
	goto_if_set FLAG_DEFEATED_DNECROZMA, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_DNECROZMA
	return

Light_EventScript_TryRemoveDNecrozma::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Light_EventScript_DNecrozma::
	lockall
	playmoncry SPECIES_NECROZMA_DAWN_WINGS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_NECROZMA_DAWN_WINGS, 75
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	setflag B_FLAG_NO_CATCHING
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Light_EventScript_DefeatedDNecrozma
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Light_EventScript_RanFromDNecrozma
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Light_EventScript_RanFromDNecrozma
	release
	end
	
Light_EventScript_DefeatedDNecrozma::
	clearflag B_FLAG_NO_CATCHING
	setflag FLAG_DEFEATED_DNECROZMA
	setvar VAR_0x8004, SPECIES_NECROZMA_DAWN_WINGS
	goto Common_EventScript_LegendaryFlewAway
	end

Light_EventScript_RanFromDNecrozma::
	clearflag B_FLAG_NO_CATCHING
	setvar VAR_0x8004, SPECIES_NECROZMA_DAWN_WINGS
	goto Common_EventScript_LegendaryFlewAway
	end

Light_EventScript_HideNecrozma::
	setflag FLAG_HIDE_NECROZMA
	return

Light_EventScript_TryShowNecrozma::
	goto_if_set FLAG_DEFEATED_DNECROZMA, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_NECROZMA
	return

Light_EventScript_TryRemoveNecrozma::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Light_EventScript_Necrozma::
	lockall
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_NECROZMA, 75
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Light_EventScript_DefeatedNecrozma
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Light_EventScript_RanFromNecrozma
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Light_EventScript_RanFromNecrozma
	setflag FLAG_CAUGHT_NECROZMA
	release
	end
	
Light_EventScript_DefeatedNecrozma::
	setflag FLAG_DEFEATED_NECROZMA
	setvar VAR_0x8004, SPECIES_NECROZMA
	goto Common_EventScript_LegendaryFlewAway
	end

Light_EventScript_RanFromNecrozma::
	setvar VAR_0x8004, SPECIES_NECROZMA
	goto Common_EventScript_LegendaryFlewAway
	end










