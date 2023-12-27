Tau_CaveF3Out_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Tau5_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Tau5_OnResume
	.byte 0

Tau5_OnTransition:
	call_if_set FLAG_CAUGHT_ARTICUNO, Tau5_EventScript_HideArticuno
	call_if_unset FLAG_CAUGHT_ARTICUNO, Tau5_EventScript_TryShowArticuno
	end

Tau5_EventScript_HideArticuno::
	setflag FLAG_HIDE_ARTICUNO
	return

Tau5_EventScript_TryShowArticuno::
	goto_if_set FLAG_DEFEATED_ARTICUNO, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_ARTICUNO
	return

Tau5_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Tau5_EventScript_TryRemoveArticuno
	end

Tau5_EventScript_TryRemoveArticuno::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Tau5_EventScript_Articuno::
	lockall
	playmoncry SPECIES_ARTICUNO_GALARIAN, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_ARTICUNO_GALARIAN, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Tau5_EventScript_DefeatedArticuno
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Tau5_EventScript_RanFromArticuno
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Tau5_EventScript_RanFromArticuno
	setflag FLAG_CAUGHT_ARTICUNO
	release
	end
	
Tau5_EventScript_DefeatedArticuno::
	setflag FLAG_DEFEATED_ARTICUNO
	setvar VAR_0x8004, SPECIES_ARTICUNO_GALARIAN
	goto Common_EventScript_LegendaryFlewAway
	end

Tau5_EventScript_RanFromArticuno::
	setvar VAR_0x8004, SPECIES_ARTICUNO_GALARIAN
	goto Common_EventScript_LegendaryFlewAway
	end
