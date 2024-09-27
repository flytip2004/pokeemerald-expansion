TauF3_Cobalion_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Tau_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Tau_OnResume
	.byte 0

Tau_OnTransition:
	call_if_set FLAG_CAUGHT_COBALION, Tau_EventScript_HideCobalion
	call_if_unset FLAG_CAUGHT_COBALION, Tau_EventScript_TryShowCobalion
	end

Tau_EventScript_HideCobalion::
	setflag FLAG_HIDE_COBALION
	return

Tau_EventScript_TryShowCobalion::
	goto_if_set FLAG_DEFEATED_COBALION, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_COBALION
	return

Tau_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Tau_EventScript_TryRemoveCobalion
	end

Tau_EventScript_TryRemoveCobalion::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Tau_EventScript_Cobalion::
	lockall
	playmoncry SPECIES_COBALION, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    seteventmon SPECIES_COBALION, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Tau_EventScript_DefeatedCobalion
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Tau_EventScript_RanFromCobalion
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Tau_EventScript_RanFromCobalion
	setflag FLAG_CAUGHT_COBALION
	release
	end
	
Tau_EventScript_DefeatedCobalion::
	setflag FLAG_DEFEATED_COBALION
	setvar VAR_0x8004, SPECIES_COBALION
	goto Common_EventScript_LegendaryFlewAway
	end

Tau_EventScript_RanFromCobalion::
	setvar VAR_0x8004, SPECIES_COBALION
	goto Common_EventScript_LegendaryFlewAway
	end
