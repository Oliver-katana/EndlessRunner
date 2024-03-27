// Oliver-katana.

#include "FloorTile.h"
#include "RunGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Obstacle.h"
#include "PickUp.h"

//*****************************************************************************************************************************************
AFloorTile::AFloorTile()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	FloorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachPoint"));
	LeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftLane"));
	CenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("CenterLane"));
	RightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("RightLane"));
	FloorTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	LeftWall = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftWall"));
	RightWall = CreateDefaultSubobject<UBoxComponent>(TEXT("RightWall"));

	RootComponent = SceneComponent;
	FloorMeshComponent->SetupAttachment(SceneComponent);
	AttachPoint->SetupAttachment(SceneComponent);
	LeftLane->SetupAttachment(SceneComponent);
	CenterLane->SetupAttachment(SceneComponent);
	RightLane->SetupAttachment(SceneComponent);
	FloorTriggerBox->SetupAttachment(SceneComponent);
	LeftWall->SetupAttachment(SceneComponent);
	RightWall->SetupAttachment(SceneComponent);

	FloorTriggerBox->SetBoxExtent(FVector(32.0f, 500.0f, 200.0f));
	FloorTriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	LeftWall->SetBoxExtent(FVector(32.0f, 500.0f, 200.0f));
	LeftWall->SetCollisionProfileName(TEXT("BlockAll"));
	RightWall->SetBoxExtent(FVector(32.0f, 500.0f, 200.0f));
	RightWall->SetCollisionProfileName(TEXT("BlockAll"));

	FloorTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::TriggerBoxBeginOverlap);
	FloorTriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFloorTile::TriggerBoxEndOverlap);
}

//*****************************************************************************************************************************************
void AFloorTile::SpawnItems()
{
	if (ObstacleSmallClass && ObstacleBigClass && PickUpCoinClass && PickUpBoostClass && PickUpSpeedClass && PickUpJumpClass)
	{
		SpawnItemToLane(LeftLane);
		SpawnItemToLane(CenterLane);
		SpawnItemToLane(RightLane);
	}
}

//*****************************************************************************************************************************************
void AFloorTile::TriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunGameModeBase* GameMode = Cast<ARunGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	check(GameMode);
	GameMode->AddFloorTile(true);
}

//*****************************************************************************************************************************************
void AFloorTile::TriggerBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Destroy();
}

//*****************************************************************************************************************************************
void AFloorTile::SpawnItemToLane(UArrowComponent* Lane)
{
	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	switch (FMath::Rand() % 4)
	{
	case 0:
	{
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(ObstacleSmallClass, Lane->GetComponentTransform(), Parameters);
		break;
	}
	case 1:
	{
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(ObstacleBigClass, Lane->GetComponentTransform(), Parameters);
		break;
	}
	case 2:
	{
		if (FMath::Rand() % 4 > 0)
		{
			APickUp* PickUp = GetWorld()->SpawnActor<APickUp>(PickUpCoinClass, Lane->GetComponentTransform(), Parameters);
		}
		else
		{
			switch (FMath::Rand() % 3)
			{
			case 0:
			{
				//APickUp* PickUp = GetWorld()->SpawnActor<APickUp>(PickUpBoostClass, Lane->GetComponentTransform(), Parameters);

				APickUp* PickUp = GetWorld()->SpawnActor<APickUp>(PickUpCoinClass, Lane->GetComponentTransform(), Parameters);
				break;
			}
			case 1:
			{
				//APickUp* PickUp = GetWorld()->SpawnActor<APickUp>(PickUpSpeedClass, Lane->GetComponentTransform(), Parameters);

				APickUp* PickUp = GetWorld()->SpawnActor<APickUp>(PickUpCoinClass, Lane->GetComponentTransform(), Parameters);
				break;
			}
			case 2:
			{
				//APickUp* PickUp = GetWorld()->SpawnActor<APickUp>(PickUpJumpClass, Lane->GetComponentTransform(), Parameters);

				APickUp* PickUp = GetWorld()->SpawnActor<APickUp>(PickUpCoinClass, Lane->GetComponentTransform(), Parameters);
				break;
			}
			default:
				break;
			}
		}
		break;
	}
	default:
	{
	}
	break;
	}
}

//*****************************************************************************************************************************************