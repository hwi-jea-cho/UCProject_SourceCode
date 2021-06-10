#include "CThrowItem.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ACThrowItem::ACThrowItem()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CHelpers::CreateComponent<USphereComponent>(this, &Sphere, "Sphere");
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle", Sphere);

	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");

	InitialLifeSpan = 3.0f;

	Sphere->SetSimulatePhysics(true);
	Sphere->SetCollisionProfileName("BlockAllDynamic");
	Sphere->SetGenerateOverlapEvents(false);
	Sphere->SetNotifyRigidBodyCollision(true);

}

void ACThrowItem::BeginPlay()
{
	Super::BeginPlay();

	TArray<USphereComponent*> components;
	GetComponents<USphereComponent>(components);
	for (USphereComponent* component : components)
		component->OnComponentHit.AddDynamic(this, &ACThrowItem::OnComponentHit);
}

void ACThrowItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EEndPlayReason::Destroyed == EndPlayReason)
	{
		CheckTrue(bHit);

		bHit = true;
		if (!!Explosion)
		{
			FTransform transform = ExplosionTransform;
			transform.AddToTranslation(GetActorLocation());

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, transform);
		}
		OnExplosion();
	}
}

void ACThrowItem::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	CheckTrue(bHit);
	CheckTrue(OtherActor == GetOwner());

	bHit = true;

	if (!!Explosion)
	{
		FTransform transform = ExplosionTransform;
		transform.AddToTranslation(Hit.Location);
		transform.SetRotation(FQuat(Hit.ImpactNormal.Rotation()));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, transform);
	}

	if (OnThrowBeginOverlap.IsBound())
		OnThrowBeginOverlap.Broadcast(Hit);

	OnExplosion();
	Destroy();
}

