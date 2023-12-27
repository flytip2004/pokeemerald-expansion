.set LOCALID_NURSE, 1

NewWorldCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewWorldCenter_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

NewWorldCenter_OnTransition::
	setrespawn HEAL_LOCATION_NEW_CITY
	end

Pokecenter_Employee_Simple2::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
