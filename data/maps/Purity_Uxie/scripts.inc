Purity_Uxie_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Purity3_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Purity3_OnResume
	.byte 0

Purity3_OnTransition:
	call_if_set FLAG_CAUGHT_UXIE , Purity3_EventScript_HideUxie
	call_if_unset FLAG_CAUGHT_UXIE , Purity3_EventScript_TryShowUxie
	end

Purity3_EventScript_HideUxie::
	setflag FLAG_HIDE_UXIE
	return

Purity3_EventScript_TryShowUxie::
	goto_if_set FLAG_DEFEATED_AZELF, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_UXIE
	return

Purity3_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Purity3_EventScript_TryRemoveUxie
	end

Purity3_EventScript_TryRemoveUxie::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Purity3_EventScript_Uxie::
	lockall
	playmoncry SPECIES_UXIE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_UXIE, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Purity3_EventScript_DefeatedUxie
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Purity3_EventScript_RanFromUxie
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Purity3_EventScript_RanFromUxie
	setflag FLAG_CAUGHT_UXIE
	release
	end
	
Purity3_EventScript_DefeatedUxie::
	setflag FLAG_DEFEATED_UXIE
	setvar VAR_0x8004, SPECIES_UXIE
	goto Common_EventScript_LegendaryFlewAway
	end

Purity3_EventScript_RanFromUxie::
	setvar VAR_0x8004, SPECIES_UXIE
	goto Common_EventScript_LegendaryFlewAway
	end


