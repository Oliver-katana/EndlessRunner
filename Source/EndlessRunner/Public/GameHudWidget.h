// Oliver-katana.

#pragma once

#include "Components/TextBlock.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHudWidget.generated.h"

UCLASS()
class ENDLESSRUNNER_API UGameHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock_CoinsNum;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock_LivesNum;

	UFUNCTION(BlueprintCallable)
	void OnContinueButtonClicked();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Pause;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UPauseWidget> PauseWidgetClass;

	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnPauseButtonClicked();

private:
	UPROPERTY()
	APlayerController* PlayerController;

};
