// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BT_SelectSpotIfPatrol.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UBT_SelectSpotIfPatrol : public UBTService
{
	GENERATED_BODY()
protected:

	virtual void ScheduleNextTick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
