// Oliver-katana.

#include "PauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RunGameModeBase.h"

//*****************************************************************************************************************************************
void UPauseWidget::NativeConstruct()
{
	if (Button_Continue)
	{
		Button_Continue->OnClicked.AddDynamic(this, &UPauseWidget::OnContinueButtonClicked);
	}
	if (Button_Restart)
	{
		Button_Restart->OnClicked.AddDynamic(this, &UPauseWidget::OnRestartButtonClicked);
	}
	if (Button_MainMenu)
	{
		Button_MainMenu->OnClicked.AddDynamic(this, &UPauseWidget::OnMainMenuButtonClicked);
	}
}

//*****************************************************************************************************************************************
void UPauseWidget::OnContinueButtonClicked()
{
	RemoveFromParent();

	ARunGameModeBase* GameMode = Cast<ARunGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->GameHudWidget->OnContinueButtonClicked();
	}
}

//*****************************************************************************************************************************************
void UPauseWidget::OnRestartButtonClicked()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
}

//*****************************************************************************************************************************************
void UPauseWidget::OnMainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("StartLevel"));
}

//*****************************************************************************************************************************************