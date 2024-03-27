// Oliver-katana.

#include "GameOverWidget.h"
#include "RunGameModeBase.h"
#include "GameHudWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

//*****************************************************************************************************************************************
void UGameOverWidget::NativeConstruct()
{
	if (Button_MainMenu)
	{
		Button_MainMenu->OnClicked.AddDynamic(this, &UGameOverWidget::OnMainMenuButtonClicked);
	}
	if (Button_Restart)
	{
		Button_Restart->OnClicked.AddDynamic(this, &UGameOverWidget::OnRestartButtonClicked);
	}
	ARunGameModeBase* GameMode = Cast<ARunGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->GameHudWidget->RemoveFromParent();
	}
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
}

//*****************************************************************************************************************************************
void UGameOverWidget::OnMainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("StartLevel"));
}

//*****************************************************************************************************************************************
void UGameOverWidget::OnRestartButtonClicked()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
}

//*****************************************************************************************************************************************