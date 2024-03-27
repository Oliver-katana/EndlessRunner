// Oliver-katana.

#pragma once

#include "GameHudWidget.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

UCLASS()
class ENDLESSRUNNER_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Continue;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Restart;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_MainMenu;

	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnContinueButtonClicked();

	UFUNCTION()
	void OnRestartButtonClicked();
	
	UFUNCTION()
	void OnMainMenuButtonClicked();

};
