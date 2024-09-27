.set LOCALID_NURSE, 1

KingdomCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, KingdomCenter_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

KingdomCenter_OnTransition::
	setrespawn HEAL_LOCATION_KINGDOM_CITY
	end

Pokecenter_Employee_Simple::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end


