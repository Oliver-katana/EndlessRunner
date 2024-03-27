// Oliver-katana.

#include "Obstacle.h"
#include "Components/BoxComponent.h"
#include "RunCharacter.h"

//*****************************************************************************************************************************************
AObstacle::AObstacle()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));

	RootComponent = SceneComponent;
	StaticMeshComp->SetupAttachment(SceneComponent);
	TriggerBox->SetupAttachment(SceneComponent);

	TriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::TriggerBeginOverlap);
}

//*****************************************************************************************************************************************
void AObstacle::TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunCharacter* Character = Cast<ARunCharacter>(OtherActor);
	if (Character)
	{
		Character->Death();
	}
}

//*****************************************************************************************************************************************