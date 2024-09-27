Purity_Azelf_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Purity1_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Purity1_OnResume
	.byte 0

Purity1_OnTransition:
	call_if_set FLAG_CAUGHT_AZELF , Purity1_EventScript_HideAzelf
	call_if_unset FLAG_CAUGHT_AZELF , Purity1_EventScript_TryShowAzelf
	end

Purity1_EventScript_HideAzelf::
	setflag FLAG_HIDE_AZELF
	return

Purity1_EventScript_TryShowAzelf::
	goto_if_set FLAG_DEFEATED_AZELF, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_AZELF
	return

Purity1_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Purity1_EventScript_TryRemoveAzelf
	end

Purity1_EventScript_TryRemoveAzelf::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Purity1_EventScript_Azelf::
	lockall
	playmoncry SPECIES_AZELF, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_AZELF, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Purity1_EventScript_DefeatedAzelf
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Purity1_EventScript_RanFromAzelf
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Purity1_EventScript_RanFromAzelf
	setflag FLAG_CAUGHT_AZELF
	release
	end
	
Purity1_EventScript_DefeatedAzelf::
	setflag FLAG_DEFEATED_AZELF
	setvar VAR_0x8004, SPECIES_AZELF
	goto Common_EventScript_LegendaryFlewAway
	end

Purity1_EventScript_RanFromAzelf::
	setvar VAR_0x8004, SPECIES_AZELF
	goto Common_EventScript_LegendaryFlewAway
	end



