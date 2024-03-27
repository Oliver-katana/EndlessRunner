// Oliver-katana.

#include "PickUp.h"
#include "Components/SphereComponent.h"
#include "RunCharacter.h"
#include "Kismet/GameplayStatics.h"

//*****************************************************************************************************************************************
APickUp::APickUp()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerBox"));

	RootComponent = SceneComponent;
	StaticMeshComp->SetupAttachment(SceneComponent);
	SphereCollision->SetupAttachment(SceneComponent);

	SphereCollision->SetSphereRadius(40.0f);
	SphereCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APickUp::SphereBeginOverlap);
}

//*****************************************************************************************************************************************
void APickUp::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PickUpSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickUpSound, GetActorLocation());
	}
	Destroy();
}

//*****************************************************************************************************************************************
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StaticMeshComp->AddWorldRotation(FRotator(0.0f, 5.0f, 0.0f));
}

//*****************************************************************************************************************************************