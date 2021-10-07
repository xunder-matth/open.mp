#include "sdk.hpp"
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include <iostream>
#include "../Types.hpp"

SCRIPT_API(SetPlayerCheckpoint, bool(IPlayer& player, Vector3 position, float size))
{
	IPlayerCheckpointData* playerCheckpointData = player.queryData<IPlayerCheckpointData>();
	if (playerCheckpointData) {
		IPlayerStandardCheckpointData& cp = playerCheckpointData->getStandardCheckpoint();
		cp.setPosition(position);
		cp.setRadius(size / 2.0f); // samp native receives diameter so we turn this into radius
		cp.enable();
		return true;
	}
	return false;
}

SCRIPT_API(DisablePlayerCheckpoint, bool(IPlayer& player))
{
	IPlayerCheckpointData* playerCheckpointData = player.queryData<IPlayerCheckpointData>();
	if (playerCheckpointData) {
		IPlayerStandardCheckpointData& cp = playerCheckpointData->getStandardCheckpoint();
		cp.disable();
		return true;
	}
	return false;
}

SCRIPT_API(IsPlayerInCheckpoint, bool(IPlayer& player))
{
	IPlayerCheckpointData* playerCheckpointData = player.queryData<IPlayerCheckpointData>();
	if (playerCheckpointData) {
		IPlayerStandardCheckpointData& cp = playerCheckpointData->getStandardCheckpoint();
		if (cp.isEnabled()) {
			return cp.isPlayerInside();
		}
	}
	return false;
}

SCRIPT_API(SetPlayerRaceCheckpoint, bool(IPlayer& player, int type, Vector3 position, Vector3 nextPosition, float size))
{
	IPlayerCheckpointData* playerCheckpointData = player.queryData<IPlayerCheckpointData>();
	if (playerCheckpointData) {
		IPlayerRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
		if (type >= 0 && type <= 8) {
			cp.setType(RaceCheckpointType(type));
			cp.setPosition(position);
			cp.setNextPosition(nextPosition);
			cp.setRadius(size); // samp native receives radius unlike standard checkpoints
			cp.enable();
			return true;
		}
	}
	return false;
}

SCRIPT_API(DisablePlayerRaceCheckpoint, bool(IPlayer& player))
{
	IPlayerCheckpointData* playerCheckpointData = player.queryData<IPlayerCheckpointData>();
	if (playerCheckpointData) {
		IPlayerRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
		cp.disable();
		return true;
	}
	return false;
}

SCRIPT_API(IsPlayerInRaceCheckpoint, bool(IPlayer& player))
{
	IPlayerCheckpointData* playerCheckpointData = player.queryData<IPlayerCheckpointData>();
	if (playerCheckpointData) {
		IPlayerRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
		if (cp.getType() != RaceCheckpointType::RACE_NONE && cp.isEnabled()) {
			return cp.isPlayerInside();
		}
	}
	return false;
}
