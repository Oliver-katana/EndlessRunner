// Oliver-katana.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

UCLASS()
class ENDLESSRUNNER_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_MainMenu;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Restart;

	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnMainMenuButtonClicked();

	UFUNCTION()
	void OnRestartButtonClicked();

};



