#include "Engine.h"

using namespace Unity;

#pragma region Color

Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color Color::Rainbow()
{
	static float r = 1.00f, g = 0.00f, b = 1.00f;
	static int cases = 0;
	switch (cases) {
	case 0: { r -= 0.006f; if (r <= 0) cases += 1; break; }
	case 1: { g += 0.006f; b -= 0.006f; if (g >= 1) cases += 1; break; }
	case 2: { r += 0.006f; if (r >= 1) cases += 1; break; }
	case 3: { b += 0.006f; g -= 0.006f; if (b >= 1) cases = 0; break; }
	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	}

	return Color(r, g, b, 1);
}

Color Color::GetUnityColor()
{
	return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

Color Color::GetBrightColor()
{
	return Color(r * 10, g * 10, b * 10, a / 255.0f);
}

Color Color::Zero()
{
	return Color(0, 0, 0, 0);
}

#pragma endregion

#pragma region Rect

Rect::Rect(float x, float y/*top left*/, float x_rightsize, float y_downsize) {
	this->x = x;
	this->y = y;
	wid = x_rightsize;
	hei = y_downsize;
}

Rect::Rect() {
	this->x = 0;
	this->y = 0;
	wid = 0;
	hei = 0;
}

bool Rect::Contains(Vector2 point)
{
	return point.x >= x && point.x < (x + wid) && point.y >= y && point.y < (y + hei);
}

#pragma endregion



#pragma region Methods

void Methods::Init() {
	Contains = reinterpret_cast<bool(*)(String*, String)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("String"), _("Contains"), -1, _(""), _("System"))));
	FindObjectsOfType = reinterpret_cast<Array<Object*>*(*)(Type*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Object"), _("FindObjectsOfType"), 1, _("type"), _("UnityEngine"))));
	Internal_CreateGameObject = reinterpret_cast<void(*)(Object*, String)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GameObject"), _("Internal_CreateGameObject"), 0, _(""), _("UnityEngine"))));
	Internal_AddComponentWithType = reinterpret_cast<Component* (*)(GameObject*, Type*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GameObject"), _("Internal_AddComponentWithType"), 0, _(""), _("UnityEngine"))));
	DontDestroyOnLoad = reinterpret_cast<void(*)(Object*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Object"), _("DontDestroyOnLoad"), 0, _(""), _("UnityEngine"))));
	get_time = reinterpret_cast<float(*)()>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Time"), _("get_time"), 0, _(""), _("UnityEngine"))));
	FindObjectOfType = reinterpret_cast<Object * (*)(Type*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Object"), _("FindObjectOfType"), 1, _("type"), _("UnityEngine"))));
	get_main = reinterpret_cast<Camera*(*)()>(il2cpp::resolve_icall(_("UnityEngine.Camera::get_main()")));
	get_position = reinterpret_cast<Vector3(*)(Transform*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Transform"), _("get_position"), 0, _(""), _("UnityEngine"))));
	get_transform = reinterpret_cast<Transform * (*)(Component*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Component"), _("get_transform"), 0, _(""), _("UnityEngine"))));
	GetType = reinterpret_cast<Type * (*)(uintptr_t)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Object"), _("GetType"), 0, _(""), _("System"))));
	get_FullNameOrDefault = reinterpret_cast<String * (*)(Type*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Type"), _("get_FullNameOrDefault"), 0, _(""), _("System"))));
	GetFields = reinterpret_cast<Array<RuntimeFieldInfo*>*(*)(RuntimeType*, BindingFlags)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("RuntimeType"), _("GetFields"), 1, _("bindingAttr"), _("System"))));
	get_Name = reinterpret_cast<String * (*)(RuntimeFieldInfo*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("RuntimeFieldInfo"), _("get_Name"), 0, _(""), _("System.Reflection"))));
	get_FieldType = reinterpret_cast<Type * (*)(RuntimeFieldInfo*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("RuntimeFieldInfo"), _("get_FieldType"), 0, _(""), _("System.Reflection"))));
	GetFieldOffset = reinterpret_cast<int(*)(RuntimeFieldInfo*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("RuntimeFieldInfo"), _("GetFieldOffset"), 0, _(""), _("System.Reflection"))));
	GetComponentsInChildren = reinterpret_cast<Array<uintptr_t>*(*)(Component*, Type*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Component"), _("GetComponentsInChildren"), 0, _(""), _("UnityEngine"))));
	get_material = reinterpret_cast<Material * (*)(Renderer*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Renderer"), _("get_material"), 0, _(""), _("UnityEngine"))));
	get_shader = reinterpret_cast<Shader* (*)(Material*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Material"), _("get_shader"), -1, _(""), _("UnityEngine"))));
	ShaderFind = reinterpret_cast<Shader* (*)(String)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Shader"), _("Find"), 1, _(""), _("UnityEngine"))));
	set_shader = reinterpret_cast<void(*)(Material*, Shader*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Material"), _("set_shader"), 0, _(""), _("UnityEngine"))));
	SetColor = reinterpret_cast<void(*)(Material*, String, Color)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Material"), _("SetColor"), 2, _(""), _("UnityEngine"))));
	SetInt = reinterpret_cast<void(*)(Material*, String, int)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Material"), _("SetInt"), 2, _(""), _("UnityEngine"))));
	get_Attributes = reinterpret_cast<FieldAttributes(*)(RuntimeFieldInfo*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("RuntimeFieldInfo"), _("get_Attributes"), 0, _(""), _("System.Reflection"))));
	PushMatrix = reinterpret_cast<void(*)()>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GL"), _("PushMatrix"), 0, _(""), _("UnityEngine"))));
	PopMatrix = reinterpret_cast<void(*)()>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GL"), _("PopMatrix"), 0, _(""), _("UnityEngine"))));
	Begin = reinterpret_cast<void(*)(int)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GL"), _("Begin"), 1, _(""), _("UnityEngine"))));
	GLColor = reinterpret_cast<void(*)(Color)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GL"), _("Color"), 1, _(""), _("UnityEngine"))));
	Vertex = reinterpret_cast<void(*)(Vector3)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GL"), _("Vertex"), 1, _(""), _("UnityEngine"))));
	End = reinterpret_cast<void(*)()>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GL"), _("End"), 0, _(""), _("UnityEngine"))));
	CreateWithShader = reinterpret_cast<void(*)(Material*, Shader*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Material"), _("CreateWithShader"), 2, _(""), _("UnityEngine"))));
	SetPass = reinterpret_cast<bool(*)(Material*, int)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Material"), _("SetPass"), 1, _(""), _("UnityEngine"))));
	get_width = reinterpret_cast<int(*)()>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Screen"), _("get_width"), 0, _(""), _("UnityEngine"))));
	get_height = reinterpret_cast<int(*)()>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Screen"), _("get_height"), 0, _(""), _("UnityEngine"))));
	get_skin = reinterpret_cast<GUISkin*(*)()>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GUI"), _("get_skin"), 0, _(""), _("UnityEngine"))));
	set_alignment = reinterpret_cast<void(*)(GUIStyle*, int)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GUIStyle"), _("set_alignment"), -1, _(""), _("UnityEngine"))));
	set_color = reinterpret_cast<void(*)(Color)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GUI"), _("set_color"), -1, _(""), _("UnityEngine"))));
	set_fontSize = reinterpret_cast<void(*)(GUIStyle*, int)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GUIStyle"), _("set_fontSize"), -1, _(""), _("UnityEngine"))));
	Label = reinterpret_cast<void(*)(Rect, GUIContent*, GUIStyle*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GUI"), _("Label"), 3, _("content"), _("UnityEngine"), 2)));
	content_temp = reinterpret_cast<GUIContent * (*)(String*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GUIContent"), _("Temp"), 1, _("t"), _("UnityEngine"), 1)));
	get_current = reinterpret_cast<Event * (*)()>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Event"), _("get_current"), 0, _(""), _("UnityEngine"))));
	get_type = reinterpret_cast<EventType(*)(Event*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Event"), _("get_type"), 0, _(""), _("UnityEngine"))));
	GetKeyDown = reinterpret_cast<bool(*)(KeyCode)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Input"), _("GetKeyDown"), 1, _("key"), _("UnityEngine"))));
	GetSceneAt = reinterpret_cast<uintptr_t(*)(int)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("SceneManager"), _("GetSceneAt"), 1, _(""), _("UnityEngine.SceneManagement"))));
	GetRootGameObjects = reinterpret_cast<Array<GameObject*>*(*)(uint32_t*)>(MemUtils::SignatureScan(GameAssembly, _("48 89 5C 24 ? 57 48 83 EC ? 80 3D ? ? ? ? ? 48 8B F9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? F0 83 0C 24 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? F0 83 0C 24 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? F0 83 0C 24 ? C6 05 ? ? ? ? ? 48 8B 05 ? ? ? ? 8B 1F")));
	get_object_name = reinterpret_cast<String * (*)(Object*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("Object"), _("get_name"), 0, _(""), _("UnityEngine"))));
	get_gameobject_transform = reinterpret_cast<Transform * (*)(GameObject*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GameObject"), _("get_transform"), 0, _(""), _("UnityEngine"))));
	get_sceneCount = reinterpret_cast<int (*)()>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("SceneManager"), _("get_sceneCount"), 0, _(""), _("UnityEngine.SceneManagement"))));
	GameObjectGetComponent = reinterpret_cast<uintptr_t(*)(GameObject*, Type*)>(*reinterpret_cast<DWORD64*>(il2cpp::Method(_("GameObject"), _("GetComponent"), 1, _("type"), _("UnityEngine"), 1)));

}

#pragma endregion


#pragma region String

String::String(const wchar_t* st) {
	if (st)
	{
		size = min(m_wcslen((wchar_t*)st), MAX_STRING_LEN);
		for (int i = 0; i < size; i++) {
			str[i] = st[i];
		}
		str[size] = 0;
	}
}

bool String::Contains(String value)
{
	if (!MemUtils::IsValidCheck(this)) return false;
	return Methods::Contains(this, value);
}

const wchar_t* String::str_wcsstr(const wchar_t* str, const wchar_t* substr) {
	const wchar_t* p = str;
	const wchar_t* q = substr;

	while (*str) {
		p = str;
		q = substr;
		while (*p && *q && *p == *q) {
			p++;
			q++;
		}
		if (*q == L'\0') {
			return str;
		}
		str++;
	}

	return nullptr;
}

int String::find(const wchar_t* substr) {
	return str_wcsstr(str, substr) != nullptr ? 0 : -1;
}

#pragma endregion


#pragma region Time

float Time::get_time() {
	return Methods::get_time();
}

#pragma endregion

#pragma region RuntimeFieldInfo

String* RuntimeFieldInfo::get_Name() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return Methods::get_Name(this);
}

Type* RuntimeFieldInfo::get_FieldType() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return Methods::get_FieldType(this);
}

int RuntimeFieldInfo::GetFieldOffset() {

	if (!MemUtils::IsValidCheck(this))
		return 0;

	return Methods::GetFieldOffset(this);
}

FieldAttributes RuntimeFieldInfo::get_Attributes() {

	if (!MemUtils::IsValidCheck(this))
		return FieldAttributes::PrivateScope;

	return Methods::get_Attributes(this);
}

#pragma endregion


#pragma region RuntimeType

Array<RuntimeFieldInfo*>* RuntimeType::GetFields(BindingFlags bindingAttr) {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return Methods::GetFields(this, bindingAttr);
}

#pragma endregion


#pragma region Type

String* Type::get_FullNameOrDefault() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return Methods::get_FullNameOrDefault(this);
}

#pragma endregion


#pragma region Object

void Object::DontDestroyOnLoad(Object* target) {

	if (!MemUtils::IsValidCheck(target))
		return;

	Methods::DontDestroyOnLoad(target);
}

Array<Object*>* Object::FindObjectsOfType(Type* type) {

	if (!MemUtils::IsValidCheck(type))
		return nullptr;

	return Methods::FindObjectsOfType(type);
}

Object* Object::FindObjectOfType(Type* type) {

	if (!MemUtils::IsValidCheck(type))
		return nullptr;

	return Methods::FindObjectOfType(type);
}

Type* Object::GetType(uintptr_t object) {

	if (!MemUtils::IsValidCheck((void*)object))
		return nullptr;

	return Methods::GetType(object);
}

String* Object::get_name() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return Methods::get_object_name(this);
}

#pragma endregion

#pragma region Shader

Shader* Shader::Find(String name) {
	return Methods::ShaderFind(name);
}

#pragma endregion

#pragma region Material

Shader* Material::get_shader() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return Methods::get_shader(this);
}

void Material::set_shader(Shader* value) {

	if (!MemUtils::IsValidCheck(this) || !MemUtils::IsValidCheck(value))
		return;

	Methods::set_shader(this, value);
}

void Material::SetColor(String name, Color value) {

	if (!MemUtils::IsValidCheck(this))
		return;

	Methods::SetColor(this, name, value);
}

void Material::SetInt(String name, int value) {

	if (!MemUtils::IsValidCheck(this))
		return;

	Methods::SetInt(this, name, value);
}

void Material::CreateWithShader(Material* self, Shader* shader) {

	if (!MemUtils::IsValidCheck(self) || !MemUtils::IsValidCheck(shader))
		return;

	Methods::CreateWithShader(self, shader);
}

bool Material::SetPass(int pass) {

	if (!MemUtils::IsValidCheck(this))
		return false;

	return Methods::SetPass(this, pass);
}

#pragma endregion


#pragma region Renderer

Material* Renderer::get_material() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return Methods::get_material(this);
}

#pragma endregion


#pragma region Component

Transform* Component::get_transform() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return Methods::get_transform(this);
}

Array<uintptr_t>* Component::GetComponentsInChildren(Type* type) {

	if (!MemUtils::IsValidCheck(this) || !MemUtils::IsValidCheck(type))
		return nullptr;

	return Methods::GetComponentsInChildren(this, type);
}

#pragma endregion

#pragma region Transform

Vector3 Transform::get_position() {

	if (!MemUtils::IsValidCheck(this))
		return Vector3::Zero();

	return Methods::get_position(this);
}

#pragma endregion

#pragma region GameObject

void GameObject::Internal_CreateGameObject(GameObject* self, String name) {

	if (!MemUtils::IsValidCheck(self))
		return;

	Methods::Internal_CreateGameObject(self, name);
}

Component* GameObject::Internal_AddComponentWithType(Type* componentType) {

	if (!MemUtils::IsValidCheck(this) || !MemUtils::IsValidCheck(componentType))
		return nullptr;

	Methods::Internal_AddComponentWithType(this, componentType);
}

Transform* GameObject::get_transform() {

	if (!MemUtils::IsValidCheck(this))
		return nullptr;

	return Methods::get_gameobject_transform(this);
}

uintptr_t GameObject::GetComponent(Type* type) {

	if (!MemUtils::IsValidCheck(this) || !MemUtils::IsValidCheck(type))
		return 0;

	return Methods::GameObjectGetComponent(this, type);
}

#pragma endregion

#pragma region Camera

Camera* Camera::get_main() {
	return Methods::get_main();
}

#pragma endregion

#pragma region Screen

int Screen::get_width() {
	return Methods::get_width();
}

int Screen::get_height() {
	return Methods::get_height();
}

#pragma endregion

#pragma region GL

void GL::PushMatrix() {
	Methods::PushMatrix();
}

void GL::PopMatrix() {
	Methods::PopMatrix();
}

void GL::Begin(int mode) {
	Methods::Begin(mode);
}

void GL::GLColor(Color color) {
	Methods::GLColor(color);
}

void GL::Vertex(Vector3 value) {
	Methods::Vertex(value);
}

void GL::End() {
	Methods::End();
}

#pragma endregion

#pragma region GUIContent

GUIContent* GUIContent::Temp(String* t) {

	if (!MemUtils::IsValidCheck(t))
		return nullptr;

	return Methods::content_temp(t);
}


#pragma endregion


#pragma region GUIStyle

void GUIStyle::set_alignment(int anchor) {

	if (!MemUtils::IsValidCheck(this))
		return;

	Methods::set_alignment(this, anchor);
}

void GUIStyle::set_fontSize(int size) {

	if (!MemUtils::IsValidCheck(this))
		return;

	Methods::set_fontSize(this, size);
}

#pragma endregion


#pragma region GUISkin



#pragma endregion


#pragma region GUI

GUISkin* GUI::get_skin() {
	return Methods::get_skin();
}

void GUI::set_color(Color color) {
	return Methods::set_color(color);
}

void GUI::Label(Rect pos, GUIContent* content, GUIStyle* style) {
	
	if (!MemUtils::IsValidCheck(content) || !MemUtils::IsValidCheck(style))
		return;

	Methods::Label(pos, content, style);
}

#pragma endregion

#pragma region Event

EventType Event::get_type() {

	if (!MemUtils::IsValidCheck(this))
		return EventType::MouseDown;

	return Methods::get_type(this);
}

Event* Event::get_current() {
	return Methods::get_current();
}

#pragma endregion

#pragma region Input

bool Input::GetKeyDown(KeyCode key) {
	return Methods::GetKeyDown(key);
}

#pragma endregion

#pragma region SceneManager


Array<GameObject*>* SceneManager::GetRootGameObjects(uint32_t* scene) {
	return Methods::GetRootGameObjects(scene);
}

uintptr_t SceneManager::GetSceneAt(int idx) {
	return Methods::GetSceneAt(idx);
}

int SceneManager::get_sceneCount() {
	return Methods::get_sceneCount();
}


#pragma endregion

