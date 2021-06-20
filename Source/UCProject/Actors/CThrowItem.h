#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CThrowItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FThrowBeginOverlap, const FHitResult&, InHitResult);

UCLASS()
class UCPROJECT_API ACThrowItem : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* Explosion;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UProjectileMovementComponent* Projectile;
	
private:
	UPROPERTY(EditDefaultsOnly)
		FTransform ExplosionTransform;

	UPROPERTY(EditAnywhere)
		float OverlapSphereRadius = 32.0f;

public:
	ACThrowItem();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable)
		void TakeDamage_ThrowItem(float InDamageAmount, AActor* InAttackTarget);

private:
	UFUNCTION()
		void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	UPROPERTY(BlueprintAssignable)
		FThrowBeginOverlap OnThrowBeginOverlap;

private:
	bool bHit = false;

};
