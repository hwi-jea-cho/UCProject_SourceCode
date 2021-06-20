#include "CPlayer.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Actor/CInteractorComponent.h"
#include "Components/Character/CMotionComponent.h"
#include "Components/Character/CStatusComponent.h"
#include "Components/Character/CStanceComponent.h"
#include "Components/Character/CEquipmentComponent.h"
#include "Components/Character/CMoveSpeedComponent.h"
#include "Components/PlayerOnly/COptionComponent.h"
#include "Components/PlayerOnly/CCommendComponent.h"
#include "Components/PlayerOnly/CLiteracyComponent.h"
#include "Components/PlayerOnly/CTargetingComponent.h"
#include "Components/PlayerOnly/CInventoryComponent.h"
#include "Components/PlayerOnly/CQuickConsumableComponent.h"
#include "Components/PlayerOnly/CMenuComponent.h"

ACPlayer::ACPlayer()
{
	// -- CreateComponent Scene -- //
	CHelpers::CreateComponent(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent(this, &Camera, "Camera", SpringArm);


	// -- CreateComponent Actor -- //
	CHelpers::CreateActorComponent(this, &Interactor, "Interactor");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Motion, "Motion");
	CHelpers::CreateActorComponent(this, &CStance, "CStance");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &MoveSpeed, "MoveSpeed");
	CHelpers::CreateActorComponent(this, &Equipment, "Equipment");
	CHelpers::CreateActorComponent(this, &QuickConsumable, "QuickConsumable");
	CHelpers::CreateActorComponent(this, &Inventory, "Inventory");
	CHelpers::CreateActorComponent(this, &Targeting, "Targeting");
	CHelpers::CreateActorComponent(this, &Literacy, "Literacy");
	CHelpers::CreateActorComponent(this, &Commend, "Commend");
	CHelpers::CreateActorComponent(this, &Option, "Option");
	CHelpers::CreateActorComponent(this, &Menu, "Menu");


	// -- Character -- //
	PrimaryActorTick.bCanEverTick = true;
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


	// -- Interactor -- //
	Interactor->SetInteractorType(EInteractorType::Player);
	Interactor->ConnectingTypes = 0;

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	State->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);
	Status->OnStatusChanged.AddDynamic(this, &ACPlayer::StatusChanged);
	Inventory->SetCharacterStatus(Status->GetLocalStatus());
	MoveSpeed->SetMoveSpeed(Status->GetMoveSpeed());
}

void ACPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FRotator controlRotation = GetControlRotation();
	controlRotation.Add(0.0f, 180.0f, 0.0f);
	controlRotation.Pitch = -controlRotation.Pitch;

	FRotator actorRotation = GetActorRotation();

	if (FVector::DotProduct(controlRotation.Vector(), actorRotation.Vector()) >= 0.0f)
	{
		FRotator result = (controlRotation - actorRotation);
		CStance->SetHeadRotation(result);
	}
	else
	{
		CStance->SetHeadRotation(FRotator::ZeroRotator);
	}

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
	PlayerInputComponent->BindAction("Targeting", EInputEvent::IE_Pressed, this, &ACPlayer::OnTargeting);
	PlayerInputComponent->BindAction("TargetLeft", EInputEvent::IE_Pressed, this, &ACPlayer::OnTargetLeft);
	PlayerInputComponent->BindAction("TargetRight", EInputEvent::IE_Pressed, this, &ACPlayer::OnTargetRight);
	PlayerInputComponent->BindAction("Quick1", EInputEvent::IE_Pressed, this, &ACPlayer::OnQuick1);
	PlayerInputComponent->BindAction("Quick2", EInputEvent::IE_Pressed, this, &ACPlayer::OnQuick2);
	PlayerInputComponent->BindAction("Quick3", EInputEvent::IE_Pressed, this, &ACPlayer::OnQuick3);
	PlayerInputComponent->BindAction("Quick4", EInputEvent::IE_Pressed, this, &ACPlayer::OnQuick4);

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
	float rate = Option->GetMouseLookRate();
	AddControllerYawInput(InAxis * rate);
}

// [Axis] LookUp
void ACPlayer::OnLookUp(float InAxis)
{
	float rate = Option->GetMouseLookRate();
	AddControllerPitchInput(InAxis * rate);
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
	SpringArm->TargetArmLength += (Option->GetZoomRate() * InAxis);
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
		Motion->PlayJump();
}

// [IE_Released] Jumping
void ACPlayer::OffJumping()
{
	StopJumping();
}

// [IE_Pressed] ToggleRun
void ACPlayer::OnToggleRun()
{
	MoveSpeed->ToggleRunMode();
}

// [IE_Pressed] WeakAttack
void ACPlayer::OnWeakAttack()
{
	if (State->IsTalkMode())
	{
		Literacy->NextTalk();
		return;
	}

	if (State->IsAttackMode())
	{
		Commend->WeakAttack();
		return;
	}

	if (State->IsIdleMode())
	{
		Interact();

		if (State->IsIdleMode())
			Commend->WeakAttack();

		return;
	}

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

// [IE_Pressed] Targeting
void ACPlayer::OnTargeting()
{
	Targeting->ToggleLookOn();
}

// [IE_Pressed] TargetLeft
void ACPlayer::OnTargetLeft()
{
	Targeting->LookOnLeft();
}

// [IE_Pressed] TargetRight
void ACPlayer::OnTargetRight()
{
	Targeting->LookOnRight();
}

// [IE_Pressed] Quick1
void ACPlayer::OnQuick1()
{
	QuickConsumable->OnQuick1();
}

// [IE_Pressed] Quick2
void ACPlayer::OnQuick2()
{
	QuickConsumable->OnQuick2();
}

// [IE_Pressed] Quick3
void ACPlayer::OnQuick3()
{
	QuickConsumable->OnQuick3();
}

// [IE_Pressed] Quick4
void ACPlayer::OnQuick4()
{
	QuickConsumable->OnQuick4();
}


// OnStateTypeChanged
void ACPlayer::Begin_Idle()
{
	Equipment->ChangeWeapon();
}

// OnStateTypeChanged
void ACPlayer::Begin_Roll()
{
	Motion->PlayRoll(FVector2D(
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

// OnStateTypeChanged
void ACPlayer::End_Talk()
{
	Literacy->CancelTalk();
}

// OnStateTypeChanged
void ACPlayer::End_Consum()
{
	QuickConsumable->SetCurrActorNull();
}


// OnWeakAttack
void ACPlayer::Interact()
{
	if (GetCharacterMovement()->IsFalling() == false)
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
		}
	}

	return;
}


// StateComponent -> OnStateTypeChanged
void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InPrevType)
	{
	case EStateType::Talk: End_Talk(); break;
	case EStateType::Consum: End_Consum(); break;
	}

	switch (InNewType)
	{
	case EStateType::Idle: Begin_Idle(); break;
	case EStateType::Roll: Begin_Roll(); break;
	case EStateType::Attack: Begin_Attack(); break;
	case EStateType::Take: Begin_Take(); break;
	}
}

// StatusComponent -> OnStatusChanged
void ACPlayer::StatusChanged(UCStatusInstance* InValue)
{
	MoveSpeed->SetMoveSpeed(InValue->GetMoveSpeed());
}
