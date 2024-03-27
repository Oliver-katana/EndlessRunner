// Oliver-katana.

#include "MainMenuGameModeBase.h"
#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"

//*****************************************************************************************************************************************
void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenuWidget = Cast<UMainMenuWidget>(CreateWidget(GetWorld(), MainMenuClass));
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}

//*****************************************************************************************************************************************