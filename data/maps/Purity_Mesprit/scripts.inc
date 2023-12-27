Purity_Mesprit_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Purity2_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Purity2_OnResume
	.byte 0

Purity2_OnTransition:
	call_if_set FLAG_CAUGHT_MESPRIT , Purity2_EventScript_HideMesprit
	call_if_unset FLAG_CAUGHT_MESPRIT , Purity2_EventScript_TryShowMesprit
	end

Purity2_EventScript_HideMesprit::
	setflag FLAG_HIDE_MESPRIT
	return

Purity2_EventScript_TryShowMesprit::
	goto_if_set FLAG_DEFEATED_MESPRIT, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_MESPRIT
	return

Purity2_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Purity2_EventScript_TryRemoveMesprit
	end

Purity2_EventScript_TryRemoveMesprit::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Purity2_EventScript_Mesprit::
	lockall
	playmoncry SPECIES_MESPRIT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_MESPRIT, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Purity2_EventScript_DefeatedMesprit
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Purity2_EventScript_RanFromMesprit
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Purity2_EventScript_RanFromMesprit
	setflag FLAG_CAUGHT_MESPRIT
	release
	end
	
Purity2_EventScript_DefeatedMesprit::
	setflag FLAG_DEFEATED_MESPRIT
	setvar VAR_0x8004, SPECIES_MESPRIT
	goto Common_EventScript_LegendaryFlewAway
	end

Purity2_EventScript_RanFromMesprit::
	setvar VAR_0x8004, SPECIES_MESPRIT
	goto Common_EventScript_LegendaryFlewAway
	end


