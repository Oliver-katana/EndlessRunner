// Oliver-katana.

#pragma once

#include "CoreMinimal.h"
#include "PickUpEnum.generated.h"

UENUM(BlueprintType)
enum class EPickUpEnum :uint8
{
	Coin,
	Boost,
	Speed,
	Jump
};
