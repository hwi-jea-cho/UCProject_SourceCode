#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CStatusInstance.generated.h"

USTRUCT(BlueprintType)
struct FStatusData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Hp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Attack = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Armor = 0;

public:
	FStatusData& operator+=(const FStatusData& rhs);
	const FStatusData operator+(const FStatusData& other) const;
	FStatusData& operator-=(const FStatusData& rhs);
	const FStatusData operator-(const FStatusData& other) const;
	FStatusData& operator*=(const FStatusData& rhs);
	const FStatusData operator*(const FStatusData& other) const;
	const FStatusData operator-() const;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatusChanged, class UCStatusInstance*, InValue);

// --
// 스텟에 증감 연산 사용을 지양하기 위한 클래스
// 상태이상 등으로 증감하고 싶다면 자식으로 추가하고,
// 복구되면 자식에서 제거하는 방법을 권장합니다.
// --
UCLASS()
class UCPROJECT_API UCStatusInstance : public UObject
{
	GENERATED_BODY()

public:
	UCStatusInstance();
	~UCStatusInstance();

public:
	void SetLocalData(FStatusData InData);

public:
	void SetParent(UCStatusInstance* InParent);
	void AddChild(UCStatusInstance* InChild);
	void RemoveChild(UCStatusInstance* InChild);
	void UnLink();  // 부모 자식 관계 해제

private:
	// LocalStatus가 바껴서 TotalStatus 값을 갱신
	void UpdateStatus(const FStatusData& InInvData);

public:
	FORCEINLINE UCStatusInstance* GetParent() { return Parent; }
	FORCEINLINE UCStatusInstance** GetChilds() { return Childs.GetData(); }
	FORCEINLINE UINT ChildCount() const { return Childs.Num(); }
	FORCEINLINE FStatusData GetData() const { return TotalStatus; }
	FORCEINLINE FStatusData GetLocalData() const { return LocalStatus; }
	FORCEINLINE float GetMoveSpeed() const { return TotalStatus.MoveSpeed; }
	FORCEINLINE float GetHp() const { return TotalStatus.Hp; }
	FORCEINLINE float GetAttack() const { return TotalStatus.Attack; }
	FORCEINLINE float GetArmor() const { return TotalStatus.Armor; }
	FORCEINLINE float GetLocalMoveSpeed() const { return LocalStatus.MoveSpeed; }
	FORCEINLINE float GetLocalHp() const { return LocalStatus.Hp; }
	FORCEINLINE float GetLocalAttack() const { return LocalStatus.Attack; }
	FORCEINLINE float GetLocalArmor() const { return LocalStatus.Armor; }

	UPROPERTY(BlueprintAssignable)
		FStatusChanged OnStatusChanged;

private:
	UCStatusInstance* Parent = nullptr;
	TArray<UCStatusInstance*> Childs;
	FStatusData LocalStatus;
	FStatusData TotalStatus;
};
