// Oliver-katana.

#include "RunCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "PickUp.h"
#include "RunGameModeBase.h"

//*****************************************************************************************************************************************
ARunCharacter::ARunCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArmComponent"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	CameraArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	CameraArm->TargetArmLength = 350.0f;
	CameraArm->SocketOffset = FVector(0.0f, 0.0f, 100.0f);
	CameraArm->bUsePawnControlRotation = true;

	Camera->bUsePawnControlRotation = false;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARunCharacter::CapsuleBeginOverlap);
}

//*****************************************************************************************************************************************
void ARunCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator ControlRotation = GetActorRotation();
	ControlRotation.Roll = 0.0f;
	ControlRotation.Pitch = 0.0f;
	AddMovementInput(ControlRotation.Vector());
}

//*****************************************************************************************************************************************
void ARunCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComp->BindAction(SlideAction, ETriggerEvent::Started, this, &ACharacter::Crouch, true);
		EnhancedInputComp->BindAction(SlideAction, ETriggerEvent::Completed, this, &ACharacter::UnCrouch, true);

		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARunCharacter::Move);
		//EnhancedInputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARunCharacter::Look);
	}
}

//*****************************************************************************************************************************************
void ARunCharacter::Death()
{
	if (bIsAlive)
	{
		bIsAlive = false;
		if (DeathParticleSystem && DeathSound)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticleSystem, GetActorTransform());
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
		}

		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName(TEXT("BlockAll"));
		DisableInput(nullptr);

		if (GameMode)
		{
			GameMode->LivesCounter();
		}
	}
}

//*****************************************************************************************************************************************
void ARunCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ARunGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//*****************************************************************************************************************************************
void ARunCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, 1);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

//*****************************************************************************************************************************************
void ARunCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

//*****************************************************************************************************************************************
void ARunCharacter::CapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APickUp* PickUp = Cast<APickUp>(OtherActor);
	if (PickUp)
	{
		switch (PickUp->PickUpType)
		{
		case EPickUpEnum::Coin:
		{
			if (GameMode)
			{
				GameMode->CoinsCounter();
			}
			break;
		}
		case EPickUpEnum::Boost:
		{
			//PickUp some kind of bonus
			//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, TEXT("BOOST"));
			break;
		}
		case EPickUpEnum::Jump:
		{
			//PickUp some kind of bonus
			//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, TEXT("JUMP"));
			break;
		}
		case EPickUpEnum::Speed:
		{
			//PickUp some kind of bonus
			//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, TEXT("SPEED"));
			break;
		}
		default:
			break;
		}
	}
}

//*****************************************************************************************************************************************