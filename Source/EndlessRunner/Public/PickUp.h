// Oliver-katana.

#pragma once

#include "PickUpEnum.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS()
class ENDLESSRUNNER_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	APickUp();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USoundBase* PickUpSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	EPickUpEnum PickUpType;

	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION()
	void SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
