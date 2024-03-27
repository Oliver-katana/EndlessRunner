// Oliver-katana.


#include "RunGameModeBase.h"
#include "FloorTile.h"
#include "GameHudWidget.h"
#include "GameOverWidget.h"
#include "RunCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

//*****************************************************************************************************************************************
AFloorTile* ARunGameModeBase::AddFloorTile(const bool bSpawnItems)
{
	AFloorTile* Tile = nullptr;
	UWorld* World = GetWorld();
	if (World)
	{
		Tile = World->SpawnActor<AFloorTile>(FloorTileClass, NextSpawnPoint);
		if (Tile)
		{
			NextSpawnPoint = Tile->GetAttachPointTransform();
			if (bSpawnItems)
			{
				Tile->SpawnItems();
			}
		}

	}
	return Tile;
}

//*****************************************************************************************************************************************
void ARunGameModeBase::CoinsCounter()
{
	++CoinsNum;
	if (GameHudWidget)
	{
		GameHudWidget->TextBlock_CoinsNum->SetText(FText::AsNumber(CoinsNum));
	}
}

//*****************************************************************************************************************************************
void ARunGameModeBase::LivesCounter()
{
	--LivesNum;
	GameHudWidget->TextBlock_LivesNum->SetText(FText::AsNumber(LivesNum));

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("SpawnPlayer"), LivesNum);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, TimerDelegate, 3.0f, false);
}

//*****************************************************************************************************************************************
void ARunGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CreateInitialFloorTiles();

	GameHudWidget = Cast<UGameHudWidget>(CreateWidget(GetWorld(), GameHudClass));
	if (GameHudWidget)
	{
		GameHudWidget->AddToViewport();
		GameHudWidget->TextBlock_LivesNum->SetText(FText::AsNumber(MaxLivesNum));
		LivesNum = MaxLivesNum;
	}
}

//*****************************************************************************************************************************************
void ARunGameModeBase::SpawnPlayer(uint8 lives_num)
{
	if (RespawnTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(RespawnTimerHandle);
	}
	if (lives_num > 0)
	{
		ARunCharacter* RunCharacter = Cast<ARunCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (RunCharacter)
		{
			FTransform SpawnTransform = RunCharacter->GetRootComponent()->GetComponentTransform();
			FVector SpawnLocation = SpawnTransform.GetLocation();
			SpawnLocation.X += 200.f;
			SpawnTransform.SetLocation(SpawnLocation);
			RunCharacter->Destroy();
			if (RunCharacterClass)
			{
				RunCharacter = GetWorld()->SpawnActor<ARunCharacter>(RunCharacterClass, SpawnTransform);
			}
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(RunCharacter);
		}
	}
	else
	{
		GameOver();
	}
}

//*****************************************************************************************************************************************
void ARunGameModeBase::GameOver()
{
	if (GameOverClass)
	{
		GameOverWidget = Cast<UGameOverWidget>(CreateWidget(GetWorld(), GameOverClass));
		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();
		}
	}
}

//*****************************************************************************************************************************************
void ARunGameModeBase::CreateInitialFloorTiles()
{
	for (size_t i = 0; i < NumInitialFloorTiles; ++i)
	{
		if (i < 3)
		{
			AddFloorTile(false);
		}
		else
		{
			AddFloorTile(true);
		}
	}
}

//*****************************************************************************************************************************************