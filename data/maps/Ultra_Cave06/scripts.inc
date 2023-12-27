Ultra_Cave06_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Ultra5_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Ultra5_OnResume
	.byte 0

Ultra5_OnTransition:
	call_if_set FLAG_CAUGHT_XURKITREE , Ultra5_EventScript_HideXurkitree
	call_if_unset FLAG_CAUGHT_XURKITREE , Ultra5_EventScript_TryShowXurkitree
	end

Ultra5_EventScript_HideXurkitree::
	setflag FLAG_HIDE_XURKITREE
	return

Ultra5_EventScript_TryShowXurkitree::
	goto_if_set FLAG_DEFEATED_XURKITREE, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_XURKITREE
	return

Ultra5_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Ultra5_EventScript_TryRemoveXurkitree
	end

Ultra5_EventScript_TryRemoveXurkitree::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Ultra5_EventScript_Xurkitree::
	lockall
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_XURKITREE, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Ultra5_EventScript_DefeatedXurkitree
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Ultra5_EventScript_RanFromXurkitree
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Ultra5_EventScript_RanFromXurkitree
	setflag FLAG_CAUGHT_XURKITREE
	release
	end
	
Ultra5_EventScript_DefeatedXurkitree::
	setflag FLAG_DEFEATED_XURKITREE
	setvar VAR_0x8004, SPECIES_XURKITREE
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra5_EventScript_RanFromXurkitree::
	setvar VAR_0x8004, SPECIES_XURKITREE
	goto Common_EventScript_LegendaryFlewAway
	end


