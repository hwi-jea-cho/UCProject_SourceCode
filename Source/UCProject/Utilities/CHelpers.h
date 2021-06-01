#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"

class UCPROJECT_API CHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"asset.Succed()");

		(*OutObject) = asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* uobj = Cast<T>(
			StaticLoadObject(T::StaticClass(), nullptr, *InPath)
		);
		verifyf(!!uobj, L"!!uobj");

		(*OutObject) = uobj;
	}

	// 클래스를 가져올 때 파일명 끝에 _C를 붙여준다.
	template<typename T>
	static void GetClass(TSubclassOf<T>* OutObject, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		(*OutObject) = asset.Class;
	}

	template<typename T>
	static void CreateComponent(AActor* InActor, T** InComponent, FName InName, USceneComponent* InParent = nullptr)
	{
		(*InComponent) = InActor->CreateDefaultSubobject<T>(InName);
		//verifyf(!!(*InComponent), L"!!*InComponent");

		if (!!InParent)
		{
			(*InComponent)->SetupAttachment(InParent);
			return;
		}

		InActor->SetRootComponent(*InComponent);
	}

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** InComponent, FName InName)
	{
		(*InComponent) = InActor->CreateDefaultSubobject<T>(InName);
	}


	template<typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

};
