#include "CPlayer.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Actor/CInteractorComponent.h"
#include "Components/Character/CStatusComponent.h"
#include "Components/Character/CStanceComponent.h"
#include "Components/Character/CEquipmentComponent.h"
#include "Components/PlayerOnly/COptionComponent.h"
#include "Components/PlayerOnly/CCommendComponent.h"
#include "Components/PlayerOnly/CLiteracyComponent.h"
#include "Components/PlayerOnly/CTargetingComponent.h"
#include "Components/PlayerOnly/CInventoryComponent.h"
#include "Components/PlayerOnly/CPlayerMovementComponent.h"
#include "Components/PlayerOnly/CQuickConsumableComponent.h"
#include "Components/PlayerOnly/CMenuComponent.h"

ACPlayer::ACPlayer()
{
	// -- CreateComponent Scene -- //
	CHelpers::CreateComponent(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent(this, &Camera, "Camera", SpringArm);


	// -- CreateComponent Actor -- //
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &Option, "Option");
	CHelpers::CreateActorComponent(this, &Stance, "Stance");
	CHelpers::CreateActorComponent(this, &Commend, "Commend");
	CHelpers::CreateActorComponent(this, &Literacy, "Literacy");
	CHelpers::CreateActorComponent(this, &Movement, "Movement");
	CHelpers::CreateActorComponent(this, &Targeting, "Targeting");
	CHelpers::CreateActorComponent(this, &Equipment, "Equipment");
	CHelpers::CreateActorComponent(this, &Inventory, "Inventory");
	CHelpers::CreateActorComponent(this, &Interactor, "Interactor");
	CHelpers::CreateActorComponent(this, &QuickConsumable, "QuickConsumable");
	CHelpers::CreateActorComponent(this, &Menu, "Menu");


	// -- Property -- //
	CHelpers::GetAsset<USoundBase>(&JumpVoice,
		"SoundCue'/Game/_MyWorld/Art/Audio/JumpVoices/Jump_Voice_Cue.Jump_Voice_Cue'");


	// -- Character -- //
	PrimaryActorTick.bCanEverTick = false;
	bUseControllerRotationYaw = false;


	// -- Mesh -- //
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh,
		"SkeletalMesh'/Game/Mixamo/Kachujin/Mesh/kachujin_g_rosales.kachujin_g_rosales'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance,
		"AnimBlueprint'/Game/_MyWorld/Animations/Kachujin/Blueprints/ABP_CPlayer.ABP_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);


	// -- CharacterMovement -- //
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = 60.0f;
	GetCharacterMovement()->RotationRate.Yaw = 360.0f;
	GetCharacterMovement()->AirControl = 1.0f;


	// -- SpringArm -- //
	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;


	// -- FStatusData -- //
	StatusCharacter.MoveSpeed = 100;
	StatusCharacter.Hp = 100;
	StatusCharacter.Attack = 10;
	StatusCharacter.Armor = 1;


	// -- Interactor -- //
	Interactor->SetInteractorType(EInteractorType::Player);
	Interactor->ConnectingTypes = 0;

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	Movement->SetMoveSpeed(StatusCharacter.MoveSpeed);
	Status->SetLocalStatus(StatusCharacter);

	State->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);
	Status->OnStatusChanged.AddDynamic(this, &ACPlayer::StatusChanged);
	Inventory->SetCharacterStatus(Status->GetLocalStatus());
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACPlayer::OnTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayer::OnLookUp);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACPlayer::OnTurnRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACPlayer::OnLookUpRate);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);

	PlayerInputComponent->BindAction("Rolling", EInputEvent::IE_Pressed, this, &ACPlayer::OnRolling);
	PlayerInputComponent->BindAction("Jumping", EInputEvent::IE_Pressed, this, &ACPlayer::OnJumping);
	PlayerInputComponent->BindAction("Jumping", EInputEvent::IE_Released, this, &ACPlayer::OffJumping);
	PlayerInputComponent->BindAction("ToggleRun", EInputEvent::IE_Pressed, this, &ACPlayer::OnToggleRun);
	PlayerInputComponent->BindAction("WeakAttack", EInputEvent::IE_Pressed, this, &ACPlayer::OnWeakAttack);
	PlayerInputComponent->BindAction("StrongAttack", EInputEvent::IE_Pressed, this, &ACPlayer::OnStrongAttack);
	PlayerInputComponent->BindAction("OpenMenu", EInputEvent::IE_Pressed, this, &ACPlayer::OnOpenMenu);
	PlayerInputComponent->BindAction("Targeting", EInputEvent::IE_Pressed, Targeting, &UCTargetingComponent::ToggleLookOn);
	PlayerInputComponent->BindAction("TargetLeft", EInputEvent::IE_Pressed, Targeting, &UCTargetingComponent::LookOnLeft);
	PlayerInputComponent->BindAction("TargetRight", EInputEvent::IE_Pressed, Targeting, &UCTargetingComponent::LookOnRight);
	PlayerInputComponent->BindAction("Quick1", EInputEvent::IE_Pressed, QuickConsumable, &UCQuickConsumableComponent::OnQuick1);
	PlayerInputComponent->BindAction("Quick2", EInputEvent::IE_Pressed, QuickConsumable, &UCQuickConsumableComponent::OnQuick2);
	PlayerInputComponent->BindAction("Quick3", EInputEvent::IE_Pressed, QuickConsumable, &UCQuickConsumableComponent::OnQuick3);
	PlayerInputComponent->BindAction("Quick4", EInputEvent::IE_Pressed, QuickConsumable, &UCQuickConsumableComponent::OnQuick4);

}



// [Axis] MoveForward
void ACPlayer::OnMoveForward(float InAxis)
{
	CheckFalse(State->IsCanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);
}

// [Axis] MoveRight
void ACPlayer::OnMoveRight(float InAxis)
{
	CheckFalse(State->IsCanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
}

// [Axis] Turn
void ACPlayer::OnTurn(float InAxis)
{
	AddControllerYawInput(InAxis);
}

// [Axis] LookUp
void ACPlayer::OnLookUp(float InAxis)
{
	AddControllerPitchInput(InAxis);
}

// [Axis] TurnRate
void ACPlayer::OnTurnRate(float InAxis)
{
	float rate = Option->GetHorizontalLookRate();
	AddControllerYawInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

// [Axis] LookUpRate
void ACPlayer::OnLookUpRate(float InAxis)
{
	float rate = Option->GetVerticalLookRate();
	AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

// [Axis] Zoom
void ACPlayer::OnZoom(float InAxis)
{
	SpringArm->TargetArmLength += (10.0f * InAxis);
	//SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, ZoomRange.X, ZoomRange.Y);
}

// [IE_Pressed] Rolling
void ACPlayer::OnRolling()
{
	State->SetRollMode();
}

// [IE_Pressed] Jumping
void ACPlayer::OnJumping()
{
	CheckFalse(State->IsIdleMode());

	if (GetCharacterMovement()->IsFalling() == false)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			GetWorld(), JumpVoice, GetActorLocation()
		);
	}
	Jump();
}

// [IE_Released] Jumping
void ACPlayer::OffJumping()
{
	StopJumping();
}

// [IE_Pressed] ToggleRun
void ACPlayer::OnToggleRun()
{
	Movement->ToggleRunMode();
}

// [IE_Pressed] WeakAttack
void ACPlayer::OnWeakAttack()
{
	if (State->IsTalkMode())
	{
		Literacy->NextTalk();
		return;
	}

	if (State->IsIdleMode() && !GetCharacterMovement()->IsFalling())
	{
		UCInteractorComponent* target = Interactor->GetLastConnecting();
		if (!!target)
		{
			switch (target->GetInteractorType())
			{
			case EInteractorType::Chest:
				State->SetTakeMode();
				break;
			case EInteractorType::DropItem:
				State->SetTakeMode();
				break;
			case EInteractorType::NPC:
			{
				FRotator newRotator = UKismetMathLibrary::FindLookAtRotation(
					GetActorLocation(), target->GetOwner()->GetActorLocation()
				);

				FRotator rotator = GetActorRotation();
				newRotator.Pitch = rotator.Pitch;
				newRotator.Roll = rotator.Roll;
				SetActorRotation(newRotator);
				target->Interact(Interactor);
				break;
			}
			default:
				target->Interact(Interactor);
				break;
			}

			return;
		}
	}

	Commend->WeakAttack();
}

// [IE_Pressed] StrongAttack
void ACPlayer::OnStrongAttack()
{
	Commend->StrongAttack();
}

// [IE_Pressed] OpenMenu
void ACPlayer::OnOpenMenu()
{
	Menu->OpenMenu();
}


// OnStateTypeChanged
void ACPlayer::Begin_Roll()
{
	Movement->Begin_Roll(FVector2D(
		InputComponent->GetAxisValue("MoveForward"),
		InputComponent->GetAxisValue("MoveRight")
	));
}

// OnStateTypeChanged
void ACPlayer::Begin_Attack()
{
	Targeting->LookOnAttack();
}

// OnStateTypeChanged
void ACPlayer::Begin_Take()
{
	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, this, &ACPlayer::End_Take, 0.2f);

	State->SetStop();
	Crouch();
}

// Begin_Take
void ACPlayer::End_Take()
{
	UnCrouch();

	CheckFalse(State->IsTakeMode());
	State->SetIdleMode();
	State->SetMove();

	UCInteractorComponent* target = Interactor->GetLastConnecting();
	CheckNull(target);

	target->Interact(Interactor);
}

// StateComponent
void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InPrevType)
	{
	case EStateType::Talk: Literacy->CancelTalk(); break;
	}

	switch (InNewType)
	{
	case EStateType::Idle: Equipment->ChangeWeapon(); break;
	case EStateType::Roll: Begin_Roll(); break;
	case EStateType::Attack: Begin_Attack(); break;
	case EStateType::Take: Begin_Take(); break;
	}
}


void ACPlayer::StatusChanged(UCStatusInstance* InValue)
{
	Movement->SetMoveSpeed(InValue->GetMoveSpeed());
}
