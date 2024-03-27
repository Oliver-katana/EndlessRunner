// Oliver-katana.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class ENDLESSRUNNER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Start;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Quit;

	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnStartButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();

private:
	UPROPERTY()
	APlayerController* PlayerController;
};
