#include "CTargetingComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/Actor/CTeamComponent.h"

UCTargetingComponent::UCTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPawn = Cast<APawn>(GetOwner());
}

void UCTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckNull(LookOnActor);

	float distance = GetOwner()->GetDistanceTo(LookOnActor);

	if (distance <= LookOnDistance)
	{
		FRotator r = OwnerPawn->GetControlRotation();
		OwnerPawn->GetController()->SetControlRotation(FRotator
		(
			r.Pitch,
			UKismetMathLibrary::FindLookAtRotation
			(
				GetOwner()->GetActorLocation(),
				LookOnActor->GetActorLocation()
			).Yaw,
			r.Roll
		));
	}
	else
	{
		EndLookOn();
	}
}


void UCTargetingComponent::LookOnAttack()
{
	AActor* lookOn = LookOnActor;

	if (!!lookOn == false)
		lookOn = GetNearbyAttackTarget();

	CheckNull(lookOn);

	FRotator lookAt = UKismetMathLibrary::FindLookAtRotation(
		GetOwner()->GetActorLocation(),
		lookOn->GetActorLocation()
	);

	GetOwner()->SetActorRotation(FRotator(0, lookAt.Yaw, 0));
}

void UCTargetingComponent::ToggleLookOn()
{
	if (!!LookOnActor)
	{
		EndLookOn();
		return;
	}

	StartLookOn();
}

void UCTargetingComponent::LookOnLeft()
{
	CheckNull(LookOnActor);

	UpdateLookOnTargets();

	FRotator r = OwnerPawn->GetControlRotation();
	FVector f = UKismetMathLibrary::GetForwardVector(r);
	FVector u = UKismetMathLibrary::GetUpVector(r);

	float min = 1.0f;
	AActor* leftTarget = nullptr;
	for (AActor* target : LookOnTargets)
	{
		if (LookOnActor == target)
			continue;

		FVector d = target->GetActorLocation() - GetOwner()->GetActorLocation();
		d.Normalize();

		FVector c = FVector::CrossProduct(f, d);
		c.Normalize();

		float curr = FVector::DotProduct(c, u);
		if (curr < 0.0f)
		{
			float absCurr = -curr;
			if (absCurr <= min)
			{
				float cameraDot = FVector::DotProduct(f, d);
				if (cameraDot <= 0.0f)
					continue;

				min = absCurr;
				leftTarget = target;
			}

		}
	}

	if (!!leftTarget)
		SetLookOn(leftTarget);
}

void UCTargetingComponent::LookOnRight()
{
	CheckNull(LookOnActor);

	UpdateLookOnTargets();

	FRotator r = OwnerPawn->GetControlRotation();
	FVector f = UKismetMathLibrary::GetForwardVector(r);
	FVector u = UKismetMathLibrary::GetUpVector(r);

	float min = 1.0f;
	AActor* rightTarget = nullptr;
	for (AActor* target : LookOnTargets)
	{
		if (LookOnActor == target)
			continue;

		FVector d = target->GetActorLocation() - GetOwner()->GetActorLocation();
		d.Normalize();

		FVector c = FVector::CrossProduct(f, d);
		c.Normalize();

		float curr = FVector::DotProduct(c, u);
		if (curr > 0.0f)
		{
			float absCurr = curr;
			if (absCurr <= min)
			{
				float cameraDot = FVector::DotProduct(f, d);
				if (cameraDot <= 0.0f)
					continue;

				min = absCurr;
				rightTarget = target;
			}

		}
	}

	if (!!rightTarget)
		SetLookOn(rightTarget);
}

void UCTargetingComponent::StartLookOn()
{
	UpdateLookOnTargets();

	FRotator r = OwnerPawn->GetControlRotation();
	FVector f = UKismetMathLibrary::GetForwardVector(r);

	float max = -1.0f;
	AActor* frontTarget = nullptr;
	for (AActor* target : LookOnTargets)
	{
		FVector d = target->GetActorLocation() - GetOwner()->GetActorLocation();
		d.Normalize();

		float curr = FVector::DotProduct(f, d);
		if (curr >= max)
		{
			max = curr;
			frontTarget = target;
		}
	}

	if (!!frontTarget)
		SetLookOn(frontTarget);
}

void UCTargetingComponent::EndLookOn()
{
	SetLookOn(nullptr);

}


AActor* UCTargetingComponent::GetNearbyAttackTarget()
{
	FVector start = GetOwner()->GetActorLocation();
	FVector end = start + 1.0f;

	TArray<FHitResult> hits;

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	TArray<AActor*> ignores;
	ignores.Add(GetOwner());
	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery6);
	CheckFalseResult(UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(), start, end,
		AttackOnDistance, objectTypes,
		false, ignores,
		EDrawDebugTrace::ForDuration, hits, true
	), nullptr);

	float angle = -1.0f;
	AActor* frontTarget = nullptr;
	for (FHitResult& hit : hits)
	{
		if (GetOwner() == hit.GetActor())
			continue;

		UCTeamComponent* team = CHelpers::GetComponent<UCTeamComponent>(hit.GetActor());
		if (!!team == false)
			continue;

		if (team->IsEnemy() == false)
			continue;

		FVector forward = GetOwner()->GetActorRotation().Quaternion().GetForwardVector();
		FVector dest = hit.GetActor()->GetActorLocation() - GetOwner()->GetActorLocation();
		dest = dest.GetSafeNormal();

		float hitAngle = FVector::DotProduct(forward, dest);
		if (hitAngle < angle)
			continue;

		angle = hitAngle;
		frontTarget = hit.GetActor();
	}

	return frontTarget;
}

void UCTargetingComponent::UpdateLookOnTargets()
{
	LookOnTargets.Empty();

	FVector start = GetOwner()->GetActorLocation();
	FVector end = start + 1.0f;

	TArray<FHitResult> hits;

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	TArray<AActor*> ignores;
	ignores.Add(GetOwner());
	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
	CheckFalse(UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(), start, end,
		LookOnDistance, objectTypes,
		false, ignores,
		EDrawDebugTrace::ForDuration, hits, true
	));

	for (FHitResult& hit : hits)
	{
		if (GetOwner() == hit.GetActor())
			continue;

		UCTeamComponent* team = CHelpers::GetComponent<UCTeamComponent>(hit.GetActor());
		if (!!team == false)
			continue;
	
		LookOnTargets.Add(hit.GetActor());
	}

}

void UCTargetingComponent::SetLookOn(AActor* InNewTarget)
{
	CheckTrue(InNewTarget == LookOnActor);

	AActor* oldTarget = LookOnActor;

	UCTeamComponent* team;
	if (!!oldTarget)
	{
		team = CHelpers::GetComponent<UCTeamComponent>(oldTarget);
		team->OffTarget();
	}

	LookOnActor = InNewTarget;

	CheckNull(InNewTarget);
	team = CHelpers::GetComponent<UCTeamComponent>(InNewTarget);
	team->OnTarget();
}
