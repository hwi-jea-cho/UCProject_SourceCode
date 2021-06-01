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

	UCStatusInstance* oldParent = InChild->Parent;

	if (!!InChild->Parent)
		InChild->Parent->RemoveChild(this);

	// ������ ���� �Ǵ� ���� �����ϱ� ���� ('A - B - C - A' �̷� ���°� �Ǹ� ���� ������ �ȴ�)
	for (auto p = this; p != nullptr; p = p->Parent)
	{
		// �� �θ��� �θ� �ڱ� �ڽ��̶�� �� �θ��� �θ� �� �θ�� �����. 
		if (p->Parent == InChild)
		{
			p->SetParent(oldParent);
			break;
		}
	}

	Childs.Add(this);
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

	Status += InInvData;

	if (OnStatusChanged.IsBound())
		OnStatusChanged.Broadcast(this);
}
