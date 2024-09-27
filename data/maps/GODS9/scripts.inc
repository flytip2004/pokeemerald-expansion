GODS9_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GODS9_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, GODS9_OnResume
	.byte 0

GODS9_OnTransition:
	call_if_set FLAG_CAUGHT_GIRATINA, GODS9_EventScript_HideGiratina
	call_if_unset FLAG_CAUGHT_GIRATINA, GODS9_EventScript_TryShowGiratina
	end

GODS9_EventScript_HideGiratina::
	setflag FLAG_HIDE_GIRATINA
	return

GODS9_EventScript_TryShowGiratina::
	goto_if_set FLAG_DEFEATED_GIRATINA, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_GIRATINA
	return

GODS9_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, GODS9_EventScript_TryRemoveGiratina
	end

GODS9_EventScript_TryRemoveGiratina::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

GODS9_EventScript_Giratina::
	lockall
	playmoncry SPECIES_GIRATINA_ORIGIN, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_GIRATINA_ORIGIN, 75, ITEM_GRISEOUS_CORE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, GODS9_EventScript_DefeatedGiratina
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GODS9_EventScript_RanFromGiratina
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GODS9_EventScript_RanFromGiratina
	setflag FLAG_CAUGHT_GIRATINA
	release
	end
	
GODS9_EventScript_DefeatedGiratina::
	setflag FLAG_DEFEATED_GIRATINA
	setvar VAR_0x8004, SPECIES_GIRATINA
	goto Common_EventScript_LegendaryFlewAway
	end

GODS9_EventScript_RanFromGiratina::
	setvar VAR_0x8004, SPECIES_GIRATINA
	goto Common_EventScript_LegendaryFlewAway
	end
