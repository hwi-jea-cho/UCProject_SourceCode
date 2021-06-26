#include "CStatusInstance.h"

// -- FStatusData -- //

FStatusData& FStatusData::operator+=(const FStatusData& rhs)
{
	MoveSpeed += rhs.MoveSpeed;
	Hp += rhs.Hp;
	Attack += rhs.Attack;
	Armor += rhs.Armor;

	return *this;
}

const FStatusData FStatusData::operator+(const FStatusData& other) const
{
	return FStatusData(*this) += other;
}

FStatusData& FStatusData::operator-=(const FStatusData& rhs)
{
	MoveSpeed -= rhs.MoveSpeed;
	Hp -= rhs.Hp;
	Attack -= rhs.Attack;
	Armor -= rhs.Armor;

	return *this;
}

const FStatusData FStatusData::operator-(const FStatusData& other) const
{
	return FStatusData(*this) -= other;
}

FStatusData& FStatusData::operator*=(const FStatusData& rhs)
{
	MoveSpeed *= rhs.MoveSpeed;
	Hp *= rhs.Hp;
	Attack *= rhs.Attack;
	Armor *= rhs.Armor;

	return *this;
}

const FStatusData FStatusData::operator*(const FStatusData& other) const
{
	return FStatusData(*this) *= other;
}

const FStatusData FStatusData::operator-() const
{
	FStatusData result;
	result.MoveSpeed = -result.MoveSpeed;
	result.Hp = -result.Hp;
	result.Attack = -result.Attack;
	result.Armor = -result.Armor;
	return result;
}


// -- CStatusInstance -- //

UCStatusInstance::UCStatusInstance()
{
}

UCStatusInstance::~UCStatusInstance()
{
}

void UCStatusInstance::SetLocalData(FStatusData InData)
{
	FStatusData InvData = InData - LocalStatus;
	LocalStatus = InData;
	UpdateStatus(InvData);
}


void UCStatusInstance::SetParent(UCStatusInstance* InParent)
{
	if (!!InParent)
	{
		// AddChild에서 변수 셋팅
		InParent->AddChild(this);
		return;
	}

	if (!!Parent)
		Parent->RemoveChild(this);

}

void UCStatusInstance::AddChild(UCStatusInstance* InChild)
{
	if (!!InChild == false)
		return;

	if (InChild == this)
		return;

	if (InChild->Parent == this)
		return;

	UCStatusInstance* inChildParent = InChild->Parent;

	// 인풋의 부모 제거
	if (!!inChildParent)
		inChildParent->RemoveChild(InChild);

	// 루프로 연결 되는 것을 방지하기 위해 ('A - B - C - A' 이런 형태가 되면 무한 루프가 된다)
	for (auto p = this; p != nullptr; p = p->Parent)
	{
		// (A - B - C) 에서 B를 C 밑으로 부모를 넣는 다면 (A - C - B)로 만든다.
		if (p->Parent == InChild)
		{
			p->SetParent(inChildParent);
			break;
		}
	}

	Childs.Add(InChild);
	InChild->Parent = this;
	UpdateStatus(InChild->LocalStatus);
}

void UCStatusInstance::RemoveChild(UCStatusInstance* InChild)
{
	for (UCStatusInstance* child : Childs)
	{
		if (child == InChild)
		{
			Childs.Remove(InChild);
			InChild->Parent = nullptr;
			UpdateStatus(-InChild->LocalStatus);
			return;
		}
	}
}

void UCStatusInstance::UnLink()
{
	for (UCStatusInstance* child : Childs)
	{
		child->SetParent(Parent);
	}
	SetParent(nullptr);
}

void UCStatusInstance::UpdateStatus(const FStatusData& InInvData)
{
	if (!!Parent)
		Parent->UpdateStatus(InInvData);

	TotalStatus += InInvData;

	if (OnStatusChanged.IsBound())
		OnStatusChanged.Broadcast(this);
}
