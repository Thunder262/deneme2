#include "Dump.h"


void Dump::Init() {

	playerNames = FieldHelper::GetEncryptedFieldAddrByFirstObjectDataType(_("BasePlayer"), _(L"System.String"), 0, true, Unity::FieldAttributes::Family);
	playerFlags = il2cpp::GetOffset(_("BasePlayer"), _("playerFlags"));
	model = il2cpp::GetOffset(_("BaseEntity"), _("model"));
	boneTransforms = il2cpp::GetOffset(_("Model"), _("boneTransforms"));
	ItemContainer = FieldHelper::GetEncryptedFieldAddrByFirstObjectDataType(_("PlayerInventory"), _(L"%"), 0, true, Unity::FieldAttributes::Public);
	ItemContainer2 = FieldHelper::GetEncryptedFieldAddrByFirstObjectDataType(_("PlayerInventory"), _(L"%"), 1, true, Unity::FieldAttributes::Public);
	ItemContainer3 = FieldHelper::GetEncryptedFieldAddrByFirstObjectDataType(_("PlayerInventory"), _(L"%"), 2, true, Unity::FieldAttributes::Public);

	char buffer[128];
	auto ItemContainerClass = wcharToChar(FieldHelper::FindEncryptedClassNameByFirstObjectDataType(_("PlayerInventory"), _(L"%"), 0, true, Unity::FieldAttributes::Public), buffer, sizeof(buffer));
 	ItemList = FieldHelper::GetEncryptedFieldAddrByFirstObjectDataType(ItemContainerClass, _(L"List"), 0, true, Unity::FieldAttributes::Public);
 	
	auto ItemClass = wcharToChar(FieldHelper::FindEncryptedClassNameByFirstObjectDataType(ItemContainerClass, _(L"List"), 0, true, Unity::FieldAttributes::Public), buffer, sizeof(buffer));
	ItemClass = RebuildChar(ItemClass, FindCharPos(ItemClass, '%'), FindCharPos(ItemClass, ','), buffer, sizeof(buffer));

	itemInfo = FieldHelper::GetEncryptedFieldAddrByFirstObjectDataType(ItemClass, _(L"ItemDefinition"));
	shortname = il2cpp::GetOffset(_("ItemDefinition"), _("shortname"));

	playerModel = FieldHelper::GetEncryptedFieldAddrByFirstObjectDataType(_("BasePlayer"), _(L"PlayerModel"));
	movement = FieldHelper::GetEncryptedFieldAddrByFirstObjectDataType(_("BasePlayer"), _(L"BaseMovement"));
	groundAngleNew = FieldHelper::GetEncryptedFieldAddrByFirstObjectDataType(_("PlayerWalkMovement"), _(L"PlayerWalkMovement"), 2);

}