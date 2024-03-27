// Oliver-katana.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameModeBase.generated.h"

UCLASS()
class ENDLESSRUNNER_API ARunGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	class UGameHudWidget* GameHudWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	class UGameOverWidget* GameOverWidget;

	UFUNCTION(BlueprintCallable)
	class AFloorTile* AddFloorTile(const bool bSpawnItems);

	UFUNCTION(BlueprintCallable, Category = "PlayerPropertys")
	void CoinsCounter();

	UFUNCTION(BlueprintCallable, Category = "PlayerPropertys")
	void LivesCounter();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "PlayerPropertys")
	uint8 LivesNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerPropertys")
	uint8 MaxLivesNum = 3;

	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = "PlayerSpawn")
	void SpawnPlayer(uint8 lives_num);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void GameOver();

private:
	UPROPERTY(EditAnywhere, Category = "ConfigInit")
	TSubclassOf<AFloorTile> FloorTileClass;

	UPROPERTY(EditAnywhere, Category = "ConfigInit")
	TSubclassOf<UGameHudWidget> GameHudClass;
	
	UPROPERTY(EditAnywhere, Category = "ConfigInit")
	TSubclassOf<UGameOverWidget> GameOverClass;

	UPROPERTY(EditAnywhere, Category = "ConfigInit")
	TSubclassOf<class ARunCharacter> RunCharacterClass;

	UPROPERTY(EditAnywhere, Category = "ConfigInit")
	int32 NumInitialFloorTiles = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "RunTime")
	FTransform NextSpawnPoint;

	UPROPERTY()
	FTimerHandle RespawnTimerHandle;

	uint8 CoinsNum = 0;

	UFUNCTION(BlueprintCallable)
	void CreateInitialFloorTiles();
};
