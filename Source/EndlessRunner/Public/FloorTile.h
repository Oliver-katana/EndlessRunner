// Oliver-katana.

#pragma once

#include "Components/ArrowComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

class UBoxComponent;

UCLASS()
class ENDLESSRUNNER_API AFloorTile : public AActor
{
	GENERATED_BODY()

public:
	AFloorTile();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FloorMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* RightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* LeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* FloorTriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* LeftWall;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* RightWall;

	FORCEINLINE const FTransform& GetAttachPointTransform() { return AttachPoint->GetComponentTransform(); }

	UFUNCTION(BlueprintCallable, Category = "SpawnItems")
	void SpawnItems();

protected:
	UFUNCTION()
	void TriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void TriggerBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "SpawnItems")
	void SpawnItemToLane(UArrowComponent* Lane);

private:
	UPROPERTY(EditDefaultsOnly, Category = "FloorAssets")
	TSubclassOf<class AObstacle> ObstacleSmallClass;

	UPROPERTY(EditDefaultsOnly, Category = "FloorAssets")
	TSubclassOf<class AObstacle> ObstacleBigClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "FloorAssets")
	TSubclassOf<class APickUp> PickUpCoinClass;

	UPROPERTY(EditDefaultsOnly, Category = "FloorAssets")
	TSubclassOf<class APickUp> PickUpBoostClass;

	UPROPERTY(EditDefaultsOnly, Category = "FloorAssets")
	TSubclassOf<class APickUp> PickUpSpeedClass;

	UPROPERTY(EditDefaultsOnly, Category = "FloorAssets")
	TSubclassOf<class APickUp> PickUpJumpClass;

};
