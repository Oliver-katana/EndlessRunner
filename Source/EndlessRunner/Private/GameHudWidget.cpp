// Oliver-katana.

#include "GameHudWidget.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PauseWidget.h"

//*****************************************************************************************************************************************
void UGameHudWidget::OnContinueButtonClicked()
{
	SetVisibility(ESlateVisibility::Visible);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, this);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

//*****************************************************************************************************************************************
void UGameHudWidget::NativeConstruct()
{
	SetVisibility(ESlateVisibility::Visible);
	if (Button_Pause)
	{
		Button_Pause->OnClicked.AddDynamic(this, &UGameHudWidget::OnPauseButtonClicked);
	}
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, this);
	}
}

//*****************************************************************************************************************************************
void UGameHudWidget::OnPauseButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	if (PauseWidgetClass)
	{
		UPauseWidget* PauseWidget = CreateWidget<UPauseWidget>(this, PauseWidgetClass);
		if (PauseWidget)
		{
			PauseWidget->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, PauseWidget);
		}
	}
}

//*****************************************************************************************************************************************