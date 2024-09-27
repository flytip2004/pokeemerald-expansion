GODS6_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GODS6_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, GODS6_OnResume
	.byte 0

GODS6_OnTransition:
	call_if_set FLAG_CAUGHT_DIALGA, GODS6_EventScript_HideDialga
	call_if_unset FLAG_CAUGHT_DIALGA, GODS6_EventScript_TryShowDialga
	end

GODS6_EventScript_HideDialga::
	setflag FLAG_HIDE_DIALGA
	return

GODS6_EventScript_TryShowDialga::
	goto_if_set FLAG_DEFEATED_DIALGA, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_DIALGA
	return

GODS6_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, GODS6_EventScript_TryRemoveDialga
	end

GODS6_EventScript_TryRemoveDialga::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

GODS6_EventScript_Dialga::
	lockall
	playmoncry SPECIES_DIALGA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    seteventmon SPECIES_DIALGA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, GODS6_EventScript_DefeatedDialga
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GODS6_EventScript_RanFromDialga
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GODS6_EventScript_RanFromDialga
	setflag FLAG_CAUGHT_PALKIA
	release
	end
	
GODS6_EventScript_DefeatedDialga::
	setflag FLAG_DEFEATED_DIALGA
	setvar VAR_0x8004, SPECIES_DIALGA
	goto Common_EventScript_LegendaryFlewAway
	end

GODS6_EventScript_RanFromDialga::
	setvar VAR_0x8004, SPECIES_DIALGA
	goto Common_EventScript_LegendaryFlewAway
	end
