#include "Game.h"



#pragma region ItemDefinition

const wchar_t* ItemDefinition::shortName() {

	if (!MemUtils::IsValidCheck(this))
		return _(L"");

	auto str = MemUtils::read<Unity::String*>(this + Dump::shortname);
	if (!MemUtils::IsValidCheck(str))
		return _(L"");

	return str->str;
}

#pragma endregion


#pragma region Item

ItemDefinition* Item::itemInfo() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return MemUtils::read<ItemDefinition*>(this + Dump::itemInfo);
}

#pragma endregion


#pragma region ItemContainer

Unity::Array<Item*>* ItemContainer::itemList() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return MemUtils::read<Unity::Array<Item*>*>(this + Dump::ItemList);
}

#pragma endregion

#pragma region PlayerInventory

ItemContainer* PlayerInventory::GetContainer(int idx) {

	if (!MemUtils::IsValidCheck(this) || idx > 2)
		return nullptr;

	uint32_t addr = 0;
	if (idx == 0)
		addr = Dump::ItemContainer;
	else if (idx == 1)
		addr = Dump::ItemContainer2;
	else if (idx == 2)
		addr = Dump::ItemContainer3;

	return MemUtils::read<ItemContainer*>(this + addr);
}

#pragma endregion

#pragma region PlayerWalkMovement

void PlayerWalkMovement::groundAngleNew(float value) {

	if (!MemUtils::IsValidCheck(this))
		return;

	MemUtils::write<float>((uintptr_t)this + Dump::groundAngleNew, value);
}

#pragma endregion



#pragma region Model

Unity::Array<Unity::Transform*>* Model::boneTransforms() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return MemUtils::read<Unity::Array<Unity::Transform*>*>(this + Dump::boneTransforms);
}

#pragma endregion


#pragma region BaseEntity

Model* BaseEntity::model() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return MemUtils::read<Model*>(this + Dump::model);
}

#pragma endregion


#pragma region BasePlayer

void BasePlayer::SetPlayerFlag(int Flg) {

	if (!MemUtils::IsValidCheck(this))
		return;

	int PlayerFlag = MemUtils::read<int>(this + Dump::playerFlags);
	MemUtils::write((uintptr_t)this + Dump::playerFlags, PlayerFlag |= (int)Flg);
}

bool BasePlayer::GetPlayerFlag(int Flg) {

	if (!MemUtils::IsValidCheck(this))
		return false;

	return MemUtils::read(this + Dump::playerFlags) & Flg;
}

const wchar_t* BasePlayer::GetName() {

	if (!MemUtils::IsValidCheck(this))
		return _(L"");

	auto str = MemUtils::read<Unity::String*>(this + Dump::playerNames);
	if (!MemUtils::IsValidCheck(str))
		return _(L"");

	return str->str;
}

Vector3 BasePlayer::GetBonePosition(int idx) {

	if (!MemUtils::IsValidCheck(this))
		return Vector3::Zero();

	auto boneTransform = model()->boneTransforms();
	if (!MemUtils::IsValidCheck(boneTransform))
		return Vector3::Zero();

	return boneTransform->Get(idx)->get_position();
}

PlayerInventory* BasePlayer::GetInventory() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return (PlayerInventory*)FieldHelper::GetDecryptedFieldInsideObject((Unity::Component*)this, _(L"PlayerInventory"));
}

PlayerModel* BasePlayer::GetPlayerModel() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return MemUtils::read<PlayerModel*>(this + Dump::playerModel);
}

PlayerWalkMovement* BasePlayer::GetMovement() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return MemUtils::read<PlayerWalkMovement*>(this + Dump::movement);
}

#pragma endregion
