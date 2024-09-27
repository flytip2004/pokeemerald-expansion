Tau_Cave_Verizion_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, Tau8_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Tau8_OnResume
	.byte 0

Tau8_OnTransition:
	call_if_set FLAG_CAUGHT_VIRIZION, Tau8_EventScript_HideVirizion
	call_if_unset FLAG_CAUGHT_VIRIZION, Tau8_EventScript_TryShowVirizion
	end

Tau8_EventScript_HideVirizion::
	setflag FLAG_HIDE_VIRIZION
	return

Tau8_EventScript_TryShowVirizion::
	goto_if_set FLAG_DEFEATED_VIRIZION, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_VIRIZION
	return

Tau8_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Tau8_EventScript_TryRemoveVirizion
	end

Tau8_EventScript_TryRemoveVirizion::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Tau8_EventScript_Virizion::
	lockall
	playmoncry SPECIES_VIRIZION, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    seteventmon SPECIES_VIRIZION, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Tau8_EventScript_DefeatedVirizion
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Tau8_EventScript_RanFromVirizion
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Tau8_EventScript_RanFromVirizion
	setflag FLAG_CAUGHT_COBALION
	release
	end
	
Tau8_EventScript_DefeatedVirizion::
	setflag FLAG_DEFEATED_VIRIZION
	setvar VAR_0x8004, SPECIES_VIRIZION
	goto Common_EventScript_LegendaryFlewAway
	end

Tau8_EventScript_RanFromVirizion::
	setvar VAR_0x8004, SPECIES_VIRIZION
	goto Common_EventScript_LegendaryFlewAway
	end
