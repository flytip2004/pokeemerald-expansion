GODS3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GODS3_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, GODS3_OnResume
	.byte 0

GODS3_OnTransition:
	call_if_set FLAG_CAUGHT_PALKIA, GODS3_EventScript_HidePalkia
	call_if_unset FLAG_CAUGHT_PALKIA, GODS3_EventScript_TryShowPalkia
	end

GODS3_EventScript_HidePalkia::
	setflag FLAG_HIDE_PALKIA
	return

GODS3_EventScript_TryShowPalkia::
	goto_if_set FLAG_DEFEATED_PALKIA, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_PALKIA
	return

GODS3_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, GODS3_EventScript_TryRemovePalkia
	end

GODS3_EventScript_TryRemovePalkia::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

GODS3_EventScript_Palkia::
	lockall
	playmoncry SPECIES_PALKIA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    seteventmon SPECIES_PALKIA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, GODS3_EventScript_DefeatedPalkia
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GODS3_EventScript_RanFromPalkia
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GODS3_EventScript_RanFromPalkia
	setflag FLAG_CAUGHT_PALKIA
	release
	end
	
GODS3_EventScript_DefeatedPalkia::
	setflag FLAG_DEFEATED_PALKIA
	setvar VAR_0x8004, SPECIES_PALKIA
	goto Common_EventScript_LegendaryFlewAway
	end

GODS3_EventScript_RanFromPalkia::
	setvar VAR_0x8004, SPECIES_PALKIA
	goto Common_EventScript_LegendaryFlewAway
	end
