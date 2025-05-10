#include "OnGUI.h"

VMatrix pViewMatrix;
Unity::Shader* NiggaShader = nullptr;

class CachedObjects {
public:

	CachedObjects() {
		step = -1;
	}

	void Clear() {
		step = -1;
		for (int i = 0; i < 255; i++)
			objects[i] = 0;
	}

	void Add(uintptr_t obj) {
		objects[++step] = obj;
	}

	int step;
	uintptr_t objects[255];
};

CachedObjects Players;

void DevControls::OnGUI(uintptr_t* ui) {

	auto FindMatrix = [](Unity::Camera* StoredMainCamera) {

		if (!MemUtils::IsValidCheck(StoredMainCamera))
			return;

		auto Entity = MemUtils::read<uintptr_t>(StoredMainCamera + 0x10);
		if (!MemUtils::IsValidCheck((void*)Entity))
			return;

		pViewMatrix = MemUtils::read<VMatrix>(Entity + 0x30C);
		return;
	};

	auto WorldToScreen = [](const Vector3& position, Vector2& screen_pos)
	{
		if (!pViewMatrix.m)
			return false;

		Vector2 out;
		const auto temp = pViewMatrix.transpose();

		auto translation_vector = Vector3{ temp[3][0], temp[3][1], temp[3][2] };
		auto up = Vector3{ temp[1][0], temp[1][1], temp[1][2] };
		auto right = Vector3{ temp[0][0], temp[0][1], temp[0][2] };

		float w = translation_vector.Dot(position) + temp[3][3];

		if (w < 0.098f)
			return false;

		float x = up.Dot(position) + temp._24;
		float y = right.Dot(position) + temp._14;

		out.x = (static_cast<float>(Unity::Screen::get_width()) / 2) * (1 + y / w);
		out.y = (static_cast<float>(Unity::Screen::get_height()) / 2) * (1 - x / w);

		screen_pos = out;

		return true;
	};

	auto DrawLine = [](Vector2 start, Vector2 end, Unity::Color color)
	{
		Unity::GL::PushMatrix();
		Unity::Material::material->SetPass(0);
		Unity::GL::Begin(1);
		Unity::GL::GLColor(color);
		Unity::GL::Vertex({ start.x, start.y, 0 });
		Unity::GL::Vertex({ end.x, end.y, 0 });
		Unity::GL::End();
		Unity::GL::PopMatrix();
	};

	auto DrawString = [](Unity::Rect pos, Unity::String text, Unity::Color clr, bool centered = false, float size = 12)
	{
		auto content = Unity::GUIContent::Temp(&text);

		if (centered)
			Unity::GUISkin::label->set_alignment(4);
		else
			Unity::GUISkin::label->set_alignment(0);

		Unity::GUISkin::label->set_fontSize(size);

		Unity::GUI::set_color({ 0,0,0,255 });
		Unity::GUI::Label({ pos.x - 1, pos.y, pos.wid, pos.hei }, content, Unity::GUISkin::label);
		Unity::GUI::Label({ pos.x + 1, pos.y, pos.wid, pos.hei }, content, Unity::GUISkin::label);
		Unity::GUI::Label({ pos.x, pos.y - 1, pos.wid, pos.hei }, content, Unity::GUISkin::label);
		Unity::GUI::Label({ pos.x, pos.y + 1, pos.wid, pos.hei }, content, Unity::GUISkin::label);

		Unity::GUI::set_color(clr.GetUnityColor());
		Unity::GUI::Label({ pos.x, pos.y, pos.wid, pos.hei }, content, Unity::GUISkin::label);
	};

	auto get_bounds = [&](BasePlayer* player, float expand = 0.f) {
		box_bounds ret = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };

		if (!player)
			return box_bounds::null();

		static int valid_bones[] = {
			17, 15,1,3,5,23,24,26,55,57,18,14,2,6,21,48,25,27,56,76
		};
 
		for (auto j : valid_bones) {
 			Vector2 sc;
			auto world_pos = player->GetBonePosition(j);
			if (world_pos.Empty())
				continue;

			if (j == 48)
				world_pos.y += 0.2f;

			if (WorldToScreen(world_pos, sc)) {
				Vector2 bone_screen = sc;


				if (bone_screen.x < ret.left)
					ret.left = bone_screen.x;
				if (bone_screen.x > ret.right)
					ret.right = bone_screen.x;
				if (bone_screen.y < ret.top)
					ret.top = bone_screen.y;
				if (bone_screen.y > ret.bottom)
					ret.bottom = bone_screen.y;
			}
		}

		if (ret.left == FLT_MAX)
			return box_bounds::null();
		if (ret.right == FLT_MIN)
			return box_bounds::null();
		if (ret.top == FLT_MAX)
			return box_bounds::null();
		if (ret.bottom == FLT_MIN)
			return box_bounds::null();

		ret.left -= expand;
		ret.right += expand;
		ret.top -= expand;
		ret.bottom += expand;

		return ret;
	};

	auto Skeleton = [&](BasePlayer* ply, Unity::Color clr)
	{
		auto head_b = ply->GetBonePosition(head);
		auto spine4_b = ply->GetBonePosition(spine4);
		auto l_upperarm_b = ply->GetBonePosition(l_upperarm);
		auto l_forearm_b = ply->GetBonePosition(l_forearm);
		auto l_hand_b = ply->GetBonePosition(l_hand);
		auto r_upperarm_b = ply->GetBonePosition(r_upperarm);
		auto r_forearm_b = ply->GetBonePosition(r_forearm);
		auto r_hand_b = ply->GetBonePosition(r_hand);
		auto pelvis_b = ply->GetBonePosition(pelvis);
		auto l_hip_b = ply->GetBonePosition(l_hip);
		auto l_knee_b = ply->GetBonePosition(l_knee);
		auto l_foot_b = ply->GetBonePosition(l_foot);
		auto r_hip_b = ply->GetBonePosition(r_hip);
		auto r_knee_b = ply->GetBonePosition(r_knee);
		auto r_foot_b = ply->GetBonePosition(r_foot);
		auto r_toe_b = ply->GetBonePosition(r_toe);
		auto l_toe_b = ply->GetBonePosition(l_toe);

		Vector2 head, spine, l_upperarm, l_forearm, l_hand, r_upperarm, r_forearm, r_hand, pelvis, l_hip, l_knee, l_foot, r_hip, r_knee, r_foot, l_toe, r_toe;
		if (WorldToScreen(head_b, head) &&
			WorldToScreen(spine4_b, spine) &&
			WorldToScreen(l_upperarm_b, l_upperarm) &&
			WorldToScreen(l_forearm_b, l_forearm) &&
			WorldToScreen(l_hand_b, l_hand) &&
			WorldToScreen(r_upperarm_b, r_upperarm) &&
			WorldToScreen(r_forearm_b, r_forearm) &&
			WorldToScreen(r_hand_b, r_hand) &&
			WorldToScreen(pelvis_b, pelvis) &&
			WorldToScreen(l_hip_b, l_hip) &&
			WorldToScreen(l_knee_b, l_knee) &&
			WorldToScreen(l_foot_b, l_foot) &&
			WorldToScreen(r_hip_b, r_hip) &&
			WorldToScreen(r_knee_b, r_knee) &&
			WorldToScreen(r_toe_b, r_toe) &&
			WorldToScreen(l_toe_b, l_toe) &&
			WorldToScreen(r_foot_b, r_foot)) {

			DrawLine(head, spine, clr);
			DrawLine(spine, l_upperarm, clr);
			DrawLine(l_upperarm, l_forearm, clr);
			DrawLine(l_forearm, l_hand, clr);
			DrawLine(spine, r_upperarm, clr);
			DrawLine(r_upperarm, r_forearm, clr);
			DrawLine(r_forearm, r_hand, clr);
			DrawLine(spine, pelvis, clr);
			DrawLine(pelvis, l_hip, clr);
			DrawLine(l_hip, l_knee, clr);
			DrawLine(l_knee, l_foot, clr);
			DrawLine(pelvis, r_hip, clr);
			DrawLine(r_hip, r_knee, clr);
			DrawLine(r_knee, r_foot, clr);
			DrawLine(r_foot, r_toe, clr);
			DrawLine(l_foot, l_toe, clr);
		}
	};

	auto UpdateDrawMaterial = [](Unity::Shader* shader) {
		Unity::Material::material = (Unity::Material*)il2cpp::object_new(il2cpp::InitClass(_("Material"), _("UnityEngine")));
		Unity::Material::CreateWithShader(Unity::Material::material, shader);
		Unity::Material::material->SetInt(_(L"_SrcBlend"), 5);
		Unity::Material::material->SetInt(_(L"_DstBlend"), 10);
		Unity::Material::material->SetInt(_(L"_Cull"), 0);
		Unity::Material::material->SetInt(_(L"_ZWrite"), 0);
		Unity::GameObject::DontDestroyOnLoad(Unity::Material::material);
	};

	static float ObjectsUpdateTime = 0.f;
	static BasePlayer* LocalPlayer = nullptr;
	static bool InitObjects = false;

	if (!InitObjects) {

		Players = CachedObjects();
		NiggaShader = Unity::Shader::Find(_(L"Hidden/Internal-Colored"));
		InitObjects = true;
	}
 
 
  
	if (!Unity::GUISkin::label) {
		auto skin = Unity::GUI::get_skin();
		if (MemUtils::IsValidCheck(skin))
			Unity::GUISkin::label = MemUtils::read<Unity::GUIStyle*>(skin + 0x38);
	}

	auto Camera = Unity::Camera::get_main();
	auto CameraPos = Camera->get_transform()->get_position();


	UpdateDrawMaterial(NiggaShader);
	auto currentTime = Unity::Time::get_time();
	auto SceneCount = Unity::SceneManager::get_sceneCount();
	if (SceneCount < 2) {
		LocalPlayer = nullptr;
		return;
	}

	if (currentTime >= ObjectsUpdateTime) {

		Players.Clear();
		
		for (int i = 0; i < SceneCount; i++) {

			auto Scene = (uint32_t)Unity::SceneManager::GetSceneAt(i);
			if (Scene) {

				auto GameObjects = Unity::SceneManager::GetRootGameObjects(&Scene);
				if (MemUtils::IsValidCheck(GameObjects)) {
					for (int j = 0; j < GameObjects->GetSize(); j++) {

						auto Object = GameObjects->Get(j);
						if (!MemUtils::IsValidCheck(Object))
							continue;

						auto ObjectName = Object->get_name();
						if (!MemUtils::IsValidCheck(ObjectName))
							continue;

						if (ObjectName->Contains(_(L"LocalPlayer")) && !MemUtils::IsValidCheck(LocalPlayer))
							LocalPlayer = (BasePlayer*)Object->GetComponent((Unity::Type*)il2cpp::TypeGetObject(_(""), _("BasePlayer")));

						if (ObjectName->Contains(_(L"player/player.prefab"))) {

							auto Player = (BasePlayer*)Object->GetComponent((Unity::Type*)il2cpp::TypeGetObject(_(""), _("BasePlayer")));
							if (!MemUtils::IsValidCheck(Player))
								continue;

							Players.Add((uintptr_t)Player);
						}

					}

				}
			}
		}

		ObjectsUpdateTime = currentTime + 1.f;
	}

	FindMatrix(Camera);
	auto currenEvent = Unity::Event::get_current();
	auto eventType = currenEvent->get_type();
	if (eventType != Unity::EventType::Repaint)
		return;

 	for (int i = 0; i < Players.step; i++) {

		auto Player = (BasePlayer*)Players.objects[i];
		if (!MemUtils::IsValidCheck(Player))
			continue;

		auto playerPos = Player->GetBonePosition(head);
		float dist = playerPos.Distance(CameraPos);
		if (Player == LocalPlayer)
			continue;

		if (Player->GetPlayerFlag(PlayerFlags::Sleeping) && !IgnoreSleepers)
			continue;

		if (DrawSkeleton)
			Skeleton(Player, Unity::Color(1, 1, 1, 1));

		box_bounds bounds = get_bounds(Player, 4.f);
		if (bounds.empty())
			continue;

		float leftSide = bounds.left - 2.f;
		float topSide = bounds.top;
		float box_width = bounds.right - leftSide + 4.f;
		float box_height = bounds.bottom - topSide;

		wchar_t buff[256];
		auto playerName = Player->GetName();
		GetSwprintf(buff, _(L"%s [%dm]"), playerName, int(dist));
		DrawString({ leftSide + (box_width / 2.f) - 100.f, bounds.top - 20.f, 200, 30 }, buff, { 255,255,255,255 }, true);

		float offset = 0.f;
		auto itemList = Player->GetInventory()->GetContainer(0)->itemList();
		if (MemUtils::IsValidCheck(itemList) && DrawPlayerWeapons) {

			for (int i = 0; i < itemList->GetSize(); i++) {

				auto item = itemList->GetValue(i);
				if (!MemUtils::IsValidCheck(item))
					continue;

				auto name = item->itemInfo()->shortName();
				DrawString({ leftSide + (box_width / 2.f) - 50.f, bounds.bottom - 10.f + offset, 100, 30 }, name, { 255,255,255,255 }, true);
				offset += 10.f;
			}

		}

		if (PlayerChams) {

			auto playerModel = Player->GetPlayerModel();
			auto RendererList = (Unity::Array<Unity::Renderer*>*)((Unity::Component*)playerModel)->GetComponentsInChildren((Unity::Type*)il2cpp::TypeGetObject(_("UnityEngine"), _("Renderer")));
			if (MemUtils::IsValidCheck(RendererList)) {

				for (int i = 0; i < RendererList->GetSize(); i++) {

					auto renderer = RendererList->Get(i);
					if (!MemUtils::IsValidCheck(renderer))
						continue;

					auto material = renderer->get_material();
					auto shader = material->get_shader();
					if (shader != NiggaShader) {
						material->set_shader(NiggaShader);
						material->SetColor(_(L"_Color"), { 1,0,0,1 });
						material->SetInt(_(L"ZTest"), 8);
					}
				}

			}

		}

	}
	
 
	if (MemUtils::IsValidCheck(LocalPlayer)) {

		if (FakeAdmin)
			LocalPlayer->SetPlayerFlag(PlayerFlags::IsAdmin);

		if (SpiderMan)
			LocalPlayer->GetMovement()->groundAngleNew(0.f);

	}

}