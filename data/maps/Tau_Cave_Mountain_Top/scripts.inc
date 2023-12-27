Tau_Cave_Mountain_Top_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Tau3_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Tau3_OnResume
	.byte 0

Tau3_OnTransition:
	call_if_set FLAG_CAUGHT_ZEKROM, Tau3_EventScript_HideZekrom
	call_if_unset FLAG_CAUGHT_ZEKROM, Tau3_EventScript_TryShowZekrom
	end

Tau3_EventScript_HideZekrom::
	setflag FLAG_HIDE_ZEKROM
	return

Tau3_EventScript_TryShowZekrom::
	goto_if_set FLAG_DEFEATED_ZEKROM, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_ZEKROM
	return

Tau3_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Tau3_EventScript_TryRemoveZekrom
	end

Tau3_EventScript_TryRemoveZekrom::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Tau3_EventScript_Zekrom::
	lockall
	playmoncry SPECIES_ZEKROM, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_ZEKROM, 75
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Tau3_EventScript_DefeatedZekrom
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Tau3_EventScript_RanFromZekrom
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Tau3_EventScript_RanFromZekrom
	setflag FLAG_CAUGHT_ZEKROM
	release
	end
	
Tau3_EventScript_DefeatedZekrom::
	setflag FLAG_DEFEATED_ZEKROM
	setvar VAR_0x8004, SPECIES_ZEKROM
	goto Common_EventScript_LegendaryFlewAway
	end

Tau3_EventScript_RanFromZekrom::
	setvar VAR_0x8004, SPECIES_ZEKROM
	goto Common_EventScript_LegendaryFlewAway
	end
