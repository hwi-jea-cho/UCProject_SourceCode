#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataAssets/CWeaponData.h"
#include "CAttachment.generated.h"

UCLASS()
class UCPROJECT_API ACAttachment : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCComboComponent* Combo;

	UPROPERTY(BlueprintReadOnly)
		class UCStanceComponent* Stance;

public:
	ACAttachment();
	void SetData(const FAttachmentData& InData);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
		void AttachTo(FName InSocketName);

	UFUNCTION(BlueprintCallable)
		void AttachToCollision(class USceneComponent* InComponent, FName InSocketName);

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Unequip();
	void Unequip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Unequip();
	void Begin_Unequip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void End_Unequip();
	void End_Unequip_Implementation();

	void OnCollision();
	void OffCollision();

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FAttachmentData Data;
	bool bEquip = false;

	TArray<class UShapeComponent*> ShapeComponents;

	UPROPERTY()
		class UCHittedCollector* HittedCollector;

};
