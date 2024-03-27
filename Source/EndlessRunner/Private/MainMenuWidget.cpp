// Oliver-katana.

#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

//*****************************************************************************************************************************************
void UMainMenuWidget::NativeConstruct()
{
	if (Button_Start)
	{
		Button_Start->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartButtonClicked);
	}
	if (Button_Quit)
	{
		Button_Quit->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitButtonClicked);
	}

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
	}
}

//*****************************************************************************************************************************************
void UMainMenuWidget::OnStartButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainLevel"));
}

//*****************************************************************************************************************************************
void UMainMenuWidget::OnQuitButtonClicked()
{
	PlayerController->ConsoleCommand("quit");
}

//*****************************************************************************************************************************************