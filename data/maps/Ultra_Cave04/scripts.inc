Ultra_Cave04_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Ultra3_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Ultra3_OnResume
	.byte 0

Ultra3_OnTransition:
	call_if_set FLAG_CAUGHT_PHEROMOSA , Ultra3_EventScript_HidePheromosa
	call_if_unset FLAG_CAUGHT_PHEROMOSA , Ultra3_EventScript_TryShowPheromosa
	end

Ultra3_EventScript_HidePheromosa::
	setflag FLAG_HIDE_PHEROMOSA
	return

Ultra3_EventScript_TryShowPheromosa::
	goto_if_set FLAG_DEFEATED_PHEROMOSA, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_PHEROMOSA
	return

Ultra3_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Ultra3_EventScript_TryRemovePheromosa
	end

Ultra3_EventScript_TryRemovePheromosa::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Ultra3_EventScript_Pheromosa::
	lockall
	playmoncry SPECIES_PHEROMOSA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_PHEROMOSA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Ultra3_EventScript_DefeatedPheromosa
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Ultra3_EventScript_RanFromPheromosa
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Ultra3_EventScript_RanFromPheromosa
	setflag FLAG_CAUGHT_PHEROMOSA
	release
	end
	
Ultra3_EventScript_DefeatedPheromosa::
	setflag FLAG_DEFEATED_PHEROMOSA
	setvar VAR_0x8004, SPECIES_PHEROMOSA
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra3_EventScript_RanFromPheromosa::
	setvar VAR_0x8004, SPECIES_PHEROMOSA
	goto Common_EventScript_LegendaryFlewAway
	end


