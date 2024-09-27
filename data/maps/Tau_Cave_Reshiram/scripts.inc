Tau_Cave_Reshiram_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, Tau7_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Tau7_OnResume
	.byte 0

Tau7_OnTransition:
	call_if_set FLAG_CAUGHT_RESHIRAM, Tau7_EventScript_HideReshiram
	call_if_unset FLAG_CAUGHT_RESHIRAM, Tau7_EventScript_TryShowReshiram
	end

Tau7_EventScript_HideReshiram::
	setflag FLAG_HIDE_RESHIRAM
	return

Tau7_EventScript_TryShowReshiram::
	goto_if_set FLAG_DEFEATED_RESHIRAM, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_RESHIRAM
	return

Tau7_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Tau7_EventScript_TryRemoveReshiram
	end

Tau7_EventScript_TryRemoveReshiram::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Tau_EventScript_Reshiram::
	lockall
	playmoncry SPECIES_UXIE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_UXIE, 75
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Tau7_EventScript_DefeatedReshiram
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Tau7_EventScript_RanFromReshiram
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Tau7_EventScript_RanFromReshiram
	setflag FLAG_CAUGHT_RESHIRAM
	release
	end
	
Tau7_EventScript_DefeatedReshiram::
	setflag FLAG_DEFEATED_RESHIRAM
	setvar VAR_0x8004, SPECIES_RESHIRAM
	goto Common_EventScript_LegendaryFlewAway
	end

Tau7_EventScript_RanFromReshiram::
	setvar VAR_0x8004, SPECIES_RESHIRAM
	goto Common_EventScript_LegendaryFlewAway
	end
