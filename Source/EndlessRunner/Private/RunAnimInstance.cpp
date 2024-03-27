// Oliver-katana.

#include "RunAnimInstance.h"
#include "RunCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

//*****************************************************************************************************************************************
void URunAnimInstance::NativeInitializeAnimation()
{
	Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		MovementComponent = Pawn->GetMovementComponent();
	}
}

//*****************************************************************************************************************************************
void URunAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Pawn && MovementComponent)
	{
		bIsInAir = MovementComponent->IsFalling();
		bIsSlide = Pawn->GetMovementComponent()->IsCrouching();
		Speed = Pawn->GetVelocity().Size();
	}
}

//*****************************************************************************************************************************************