Regieleki_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Regieleki_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Regieleki_OnResume
	.byte 0

Regieleki_OnTransition:
	call_if_set FLAG_CAUGHT_REGIELEKI , Regieleki_EventScript_HideRegieleki
	call_if_unset FLAG_CAUGHT_REGIELEKI , Regieleki_EventScript_TryShowRegieleki
	end

Regieleki_EventScript_HideRegieleki::
	setflag FLAG_HIDE_REGIELEKI
	return

Regieleki_EventScript_TryShowRegieleki::
	goto_if_set FLAG_DEFEATED_REGIELEKI, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_REGIELEKI
	return

Regieleki_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Regieleki_EventScript_TryRemoveRegieleki
	end

Regieleki_EventScript_TryRemoveRegieleki::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Regieleki_EventScript_Regieleki::
	lockall
	playmoncry SPECIES_REGIELEKI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_REGIELEKI, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Regieleki_EventScript_DefeatedRegieleki
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Regieleki_EventScript_RanFromRegieleki
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Regieleki_EventScript_RanFromRegieleki
	setflag FLAG_CAUGHT_REGIELEKI
	release
	end
	
Regieleki_EventScript_DefeatedRegieleki::
	setflag FLAG_DEFEATED_REGIELEKI
	setvar VAR_0x8004, SPECIES_REGIELEKI
	goto Common_EventScript_LegendaryFlewAway
	end

Regieleki_EventScript_RanFromRegieleki::
	setvar VAR_0x8004, SPECIES_REGIELEKI
	goto Common_EventScript_LegendaryFlewAway
	end






