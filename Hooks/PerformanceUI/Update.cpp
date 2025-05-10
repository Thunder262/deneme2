#include "Update.h"

void PerformanceUI::Update(uintptr_t* ui) {

	static Unity::GameObject* object = nullptr;
	static bool flag = false;
 	if (!flag) {
		object = (Unity::GameObject*)il2cpp::object_new(il2cpp::InitClass(_("GameObject"), _("UnityEngine")));
		Unity::GameObject::Internal_CreateGameObject(object, _(L""));
		object->Internal_AddComponentWithType((Unity::Type*)il2cpp::TypeGetObject(_(""), _("DevControls")));
		Unity::Object::DontDestroyOnLoad(object);
		flag = true;
	} 

	if (Unity::Input::GetKeyDown(Unity::KeyCode::F2))
		DrawSkeleton = !DrawSkeleton;

	if (Unity::Input::GetKeyDown(Unity::KeyCode::F3))
		DrawPlayerWeapons = !DrawPlayerWeapons;

	if (Unity::Input::GetKeyDown(Unity::KeyCode::F4))
		IgnoreSleepers = !IgnoreSleepers;

	if (Unity::Input::GetKeyDown(Unity::KeyCode::F5))
		PlayerChams = !PlayerChams;

	if (Unity::Input::GetKeyDown(Unity::KeyCode::F6))
		SpiderMan = !SpiderMan;

	if (Unity::Input::GetKeyDown(Unity::KeyCode::F7))
		FakeAdmin = !FakeAdmin;

	Orig(ui);
}