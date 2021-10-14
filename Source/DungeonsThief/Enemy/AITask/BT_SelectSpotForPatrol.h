// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BT_BaseTaskDungeonsThief.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DungeonsThief/Food/FoodSpot.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "BT_SelectSpotForPatrol.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_SelectSpotForPatrol : public UBT_BaseTaskDungeonsThief
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type CodeToExecute() override;

};
