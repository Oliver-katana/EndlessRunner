// Oliver-katana.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

UCLASS()
class ENDLESSRUNNER_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	class UMainMenuWidget* MainMenuWidget;

protected:
	virtual void BeginPlay();

private:
	UPROPERTY(EditAnywhere, Category = "MainMenuWidget")
	TSubclassOf<class UMainMenuWidget> MainMenuClass;
};
