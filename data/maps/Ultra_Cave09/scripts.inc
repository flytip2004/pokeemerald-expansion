Ultra_Cave09_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Ultra8_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Ultra8_OnResume
	.byte 0

Ultra8_OnTransition:
	call_if_set FLAG_CAUGHT_BLACEPHALON , Ultra8_EventScript_HideBlacephalon
	call_if_unset FLAG_CAUGHT_BLACEPHALON , Ultra8_EventScript_TryShowBlacephalon
	end

Ultra8_EventScript_HideBlacephalon::
	setflag FLAG_HIDE_BLACEPHALON
	return

Ultra8_EventScript_TryShowBlacephalon::
	goto_if_set FLAG_DEFEATED_BLACEPHALON, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_BLACEPHALON
	return

Ultra8_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Ultra8_EventScript_TryRemoveBlacephalon
	end

Ultra8_EventScript_TryRemoveBlacephalon::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Ultra8_EventScript_Blacephalon::
	lockall
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_BLACEPHALON, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Ultra8_EventScript_DefeatedBlacephalon
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Ultra8_EventScript_RanFromBlacephalon
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Ultra8_EventScript_RanFromBlacephalon
	setflag FLAG_CAUGHT_BLACEPHALON
	release
	end
	
Ultra8_EventScript_DefeatedBlacephalon::
	setflag FLAG_DEFEATED_BLACEPHALON
	setvar VAR_0x8004, SPECIES_BLACEPHALON
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra8_EventScript_RanFromBlacephalon::
	setvar VAR_0x8004, SPECIES_BLACEPHALON
	goto Common_EventScript_LegendaryFlewAway
	end




