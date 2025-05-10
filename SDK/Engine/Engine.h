#pragma once


#ifndef ENGINE_H
#define ENGINE_H

#define MAX_STRING_LEN 128
#include "../../Imports.h"

namespace Unity {
	class String;
	class Object;
	class Type;
	class Component;
	class GameObject;
	class Camera;
	class Transform;
	class RuntimeType;
	class RuntimeFieldInfo;
	class Material;
	class Renderer;
	class Shader;
	class GUI;
	class GUISkin;
	class GUIStyle;
	class GUIContent;
	class Event;
	class SceneManager;

	enum class FieldAttributes : int
	{
		FieldAccessMask = 7,
		PrivateScope = 0,
		Private = 1,
		FamANDAssem = 2,
		Assembly = 3,
		Family = 4,
		FamORAssem = 5,
		Public = 6,
		Static = 16,
		InitOnly = 32,
		Literal = 64,
		NotSerialized = 128,
		SpecialName = 512,
		PinvokeImpl = 8192,
		RTSpecialName = 1024,
		HasFieldMarshal = 4096,
		HasDefault = 32768,
		HasFieldRVA = 256,
		ReservedMask = 38144
	};

	enum class BindingFlags : int
	{
		Default = 0,
		IgnoreCase = 1,
		DeclaredOnly = 2,
		Instance = 4,
		Static = 8,
		Public = 16,
		NonPublic = 32,
		FlattenHierarchy = 64,
		InvokeMethod = 256,
		CreateInstance = 512,
		GetField = 1024,
		SetField = 2048,
		GetProperty = 4096,
		SetProperty = 8192,
		PutDispProperty = 16384,
		PutRefDispProperty = 32768,
		ExactBinding = 65536,
		SuppressChangeType = 131072,
		OptionalParamBinding = 262144,
		IgnoreReturn = 16777216,
		DoNotWrapExceptions = 33554432
	};

	enum class EventType : int {
		MouseDown = 0,
		MouseUp = 1,
		MouseDrag = 3,
		KeyDown = 4,
		KeyUp = 5,
		Repaint = 7
	};

	enum class KeyCode : int
	{
		Backspace = 8,
		Delete = 127,
		Tab = 9,
		Clear = 12,
		Return = 13,
		Pause = 19,
		Escape = 27,
		Space = 32,
		Keypad0 = 256,
		Keypad1 = 257,
		Keypad2 = 258,
		Keypad3 = 259,
		Keypad4 = 260,
		Keypad5 = 261,
		Keypad6 = 262,
		Keypad7 = 263,
		Keypad8 = 264,
		Keypad9 = 265,
		KeypadPeriod = 266,
		KeypadDivide = 267,
		KeypadMultiply = 268,
		KeypadMinus = 269,
		KeypadPlus = 270,
		KeypadEnter = 271,
		KeypadEquals = 272,
		UpArrow = 273,
		DownArrow = 274,
		RightArrow = 275,
		LeftArrow = 276,
		Insert = 277,
		Home = 278,
		End = 279,
		PageUp = 280,
		PageDown = 281,
		F1 = 282,
		F2 = 283,
		F3 = 284,
		F4 = 285,
		F5 = 286,
		F6 = 287,
		F7 = 288,
		F8 = 289,
		F9 = 290,
		F10 = 291,
		F11 = 292,
		F12 = 293,
		F13 = 294,
		F14 = 295,
		F15 = 296,
		Alpha0 = 48,
		Alpha1 = 49,
		Alpha2 = 50,
		Alpha3 = 51,
		Alpha4 = 52,
		Alpha5 = 53,
		Alpha6 = 54,
		Alpha7 = 55,
		Alpha8 = 56,
		Alpha9 = 57,
		Exclaim = 33,
		DoubleQuote = 34,
		Hash = 35,
		Dollar = 36,
		Percent = 37,
		Ampersand = 38,
		Quote = 39,
		LeftParen = 40,
		RightParen = 41,
		Asterisk = 42,
		Plus = 43,
		Comma = 44,
		Minus = 45,
		Period = 46,
		Slash = 47,
		Colon = 58,
		Semicolon = 59,
		Less = 60,
		Equals = 61,
		Greater = 62,
		Question = 63,
		At = 64,
		LeftBracket = 91,
		Backslash = 92,
		RightBracket = 93,
		Caret = 94,
		Underscore = 95,
		BackQuote = 96,
		A = 97,
		B = 98,
		C = 99,
		D = 100,
		E = 101,
		F = 102,
		G = 103,
		H = 104,
		I = 105,
		J = 106,
		K = 107,
		L = 108,
		M = 109,
		N = 110,
		O = 111,
		P = 112,
		Q = 113,
		R = 114,
		S = 115,
		T = 116,
		U = 117,
		V = 118,
		W = 119,
		X = 120,
		Y = 121,
		Z = 122,
		LeftCurlyBracket = 123,
		Pipe = 124,
		RightCurlyBracket = 125,
		Tilde = 126,
		Numlock = 300,
		CapsLock = 301,
		ScrollLock = 302,
		RightShift = 303,
		LeftShift = 304,
		RightControl = 305,
		LeftControl = 306,
		RightAlt = 307,
		LeftAlt = 308,
		LeftCommand = 310,
		LeftApple = 310,
		LeftWindows = 311,
		RightCommand = 309,
		RightApple = 309,
		RightWindows = 312,
		AltGr = 313,
		Help = 315,
		Pr = 316,
		SysReq = 317,
		Break = 318,
		Menu = 319,
		Mouse0 = 323,
		Mouse1 = 324,
		Mouse2 = 325,
		Mouse3 = 326,
		Mouse4 = 327,
		Mouse5 = 328,
		Mouse6 = 329
	};


	inline BindingFlags operator|(BindingFlags a, BindingFlags b) {
		return static_cast<BindingFlags>(static_cast<int>(a) | static_cast<int>(b));
	}

	inline BindingFlags& operator|=(BindingFlags& a, BindingFlags b) {
		a = a | b;
		return a;
	}

	inline BindingFlags operator&(BindingFlags a, BindingFlags b) {
		return static_cast<BindingFlags>(static_cast<int>(a) & static_cast<int>(b));
	}

	inline BindingFlags& operator&=(BindingFlags& a, BindingFlags b) {
		a = a & b;
		return a;
	}

	inline BindingFlags operator~(BindingFlags a) {
		return static_cast<BindingFlags>(~static_cast<int>(a));
	}


	class Color {
	public:
		float r;
		float g;
		float b;
		float a;

		Color();
		Color(float r, float g, float b, float a);
		Color Rainbow();
		Color GetUnityColor();
		Color GetBrightColor();
		Color Zero();
	};

	class Rect {
	public:
		float x; // 0x10
		float y; // 0x14
		float wid; // 0x18
		float hei; // 0x1C
		Rect(float x, float y/*top left*/, float x_rightsize, float y_downsize);
		Rect();
		bool Contains(Vector2 point);
	};


	template<typename T>
	class Array {
	public:
		inline T Get(uint32_t idx)
		{
			const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}
		inline T GetValue(uint32_t idx) {
			const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
			const auto internal_list = list + 0x20;
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}
		inline T operator[](uint32_t idx) { return Get(idx); }
		inline const uint32_t GetSize() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }

	};

	namespace Methods {

		static auto Contains = reinterpret_cast<bool(*)(String*, String)>(0);
		static auto FindObjectsOfType = reinterpret_cast<Array<Object*>*(*)(Type*)>(0);
		static auto Internal_CreateGameObject = reinterpret_cast<void(*)(Object*, String)>(0);
		static auto Internal_AddComponentWithType = reinterpret_cast<Component * (*)(GameObject*, Type*)>(0);
		static auto DontDestroyOnLoad = reinterpret_cast<void(*)(Object*)>(0);
		static auto get_time = reinterpret_cast<float(*)()>(0);
		static auto FindObjectOfType = reinterpret_cast<Object*(*)(Type*)>(0);
		static auto get_main = reinterpret_cast<Camera*(*)()>(0);
		static auto get_position = reinterpret_cast<Vector3(*)(Transform*)>(0);
		static auto get_transform = reinterpret_cast<Transform*(*)(Component*)>(0);
		static auto GetType = reinterpret_cast<Type*(*)(uintptr_t)>(0);
		static auto get_FullNameOrDefault = reinterpret_cast<String* (*)(Type*)>(0);
		static auto GetFields = reinterpret_cast<Array<RuntimeFieldInfo*>*(*)(RuntimeType*, BindingFlags)>(0);
		static auto get_Name = reinterpret_cast<String * (*)(RuntimeFieldInfo*)>(0);
		static auto get_FieldType = reinterpret_cast<Type*(*)(RuntimeFieldInfo*)>(0);
		static auto GetFieldOffset = reinterpret_cast<int(*)(RuntimeFieldInfo*)>(0);
		static auto GetComponentsInChildren = reinterpret_cast<Array<uintptr_t>*(*)(Component*, Type*)>(0);
		static auto get_material = reinterpret_cast<Material*(*)(Renderer*)>(0);
		static auto get_shader = reinterpret_cast<Shader*(*)(Material*)>(0);
		static auto ShaderFind = reinterpret_cast<Shader*(*)(String)>(0);
		static auto set_shader = reinterpret_cast<void(*)(Material*, Shader*)>(0);
		static auto SetColor = reinterpret_cast<void(*)(Material*, String, Color)>(0);
		static auto SetInt = reinterpret_cast<void(*)(Material*, String, int)>(0);
		static auto get_Attributes = reinterpret_cast<FieldAttributes(*)(RuntimeFieldInfo*)>(0);
		static auto PushMatrix = reinterpret_cast<void(*)()>(0);
		static auto PopMatrix = reinterpret_cast<void(*)()>(0);
		static auto Begin = reinterpret_cast<void(*)(int)>(0);
		static auto GLColor = reinterpret_cast<void(*)(Color)>(0);
		static auto Vertex = reinterpret_cast<void(*)(Vector3)>(0);
		static auto End = reinterpret_cast<void(*)()>(0);
		static auto CreateWithShader = reinterpret_cast<void(*)(Material*, Shader*)>(0);
		static auto SetPass = reinterpret_cast<bool(*)(Material*, int)>(0);
		static auto get_width = reinterpret_cast<int(*)()>(0);
		static auto get_height = reinterpret_cast<int(*)()>(0);
		static auto get_skin = reinterpret_cast<GUISkin*(*)()>(0);
		static auto set_alignment = reinterpret_cast<void(*)(GUIStyle*, int)>(0);
		static auto set_color = reinterpret_cast<void(*)(Color)>(0);
		static auto set_fontSize = reinterpret_cast<void(*)(GUIStyle*, int)>(0);
		static auto Label = reinterpret_cast<void(*)(Rect, GUIContent*, GUIStyle*)>(0);
		static auto content_temp = reinterpret_cast<GUIContent*(*)(String*)>(0);
		static auto get_current = reinterpret_cast<Event * (*)()>(0);
		static auto get_type = reinterpret_cast<EventType (*)(Event*)>(0);
		static auto GetKeyDown = reinterpret_cast<bool(*)(KeyCode)>(0);
		static auto GetSceneAt = reinterpret_cast<uintptr_t(*)(int)>(0);
		static auto GetRootGameObjects = reinterpret_cast<Array<GameObject*>*(*)(uint32_t*)>(0);
		static auto get_object_name = reinterpret_cast<String * (*)(Object*)>(0);
		static auto get_gameobject_transform = reinterpret_cast<Transform * (*)(GameObject*)>(0);
		static auto get_sceneCount = reinterpret_cast<int (*)()>(0);
		static auto GameObjectGetComponent = reinterpret_cast<uintptr_t(*)(GameObject*, Type*)>(0);

		void Init();
	}


	class String {
		char zpad[0x10];
	public:

		int size;
		wchar_t str[MAX_STRING_LEN + 1];

		String(const wchar_t* st);
		bool Contains(String value);
		const wchar_t* str_wcsstr(const wchar_t* str, const wchar_t* substr);
		int find(const wchar_t* substr);

		static inline constexpr auto npos{ static_cast<size_t>(-1) };
	};

	class Time {
	public:
		static float get_time();
	};

	class RuntimeFieldInfo {
	public:
		String* get_Name();
		Type* get_FieldType();
		int GetFieldOffset();
		FieldAttributes get_Attributes();
	};

	class RuntimeType {
	public:
		Array<RuntimeFieldInfo*>* GetFields(BindingFlags bindingAttr);
	};

	class Type : public RuntimeType {
	public:
		String* get_FullNameOrDefault();
	};

	class Object {
	public:
		static void DontDestroyOnLoad(Object* target);
		static Array<Object*>* FindObjectsOfType(Type* type);
		static Object* FindObjectOfType(Type* type);
		static Type* GetType(uintptr_t object);
		String* get_name();
	};

	class Shader : public Object {
	public:
		static Shader* Find(String name);
	};

	class Material : public Object {
	public:
		Shader* get_shader();
		void set_shader(Shader* value);
		void SetColor(String name, Color value);
		void SetInt(String name, int value);
		static void CreateWithShader(Material* self, Shader* shader);
		bool SetPass(int pass);
	public:
		static inline Material* material = nullptr;
	};

	class Renderer {
	public:
		Material* get_material();
	};

	class Component : public Object {
	public:
		Transform* get_transform();
		Array<uintptr_t>* GetComponentsInChildren(Type* type);
	};

	class Transform : public Component {
	public:
		Vector3 get_position();
	};

	class GameObject : public Object {
	public:
		static void Internal_CreateGameObject(GameObject* self, String name);
		Component* Internal_AddComponentWithType(Type* componentType);
		Transform* get_transform();
		uintptr_t GetComponent(Type* type);
	};

	class Camera : public Component {
	public:
		static Camera* get_main();
	};

	class Screen {
	public:
		static int get_width();
		static int get_height();
	};

	class GL {
	public:
		static void PushMatrix();
		static void PopMatrix();
		static void Begin(int mode);
		static void GLColor(Color color);
		static void Vertex(Vector3 value);
		static void End();
	};

	class GUIContent {
	public:
		static GUIContent* Temp(String* t);
	};

	class GUIStyle {
	public:
		void set_alignment(int anchor);
		void set_fontSize(int size);
	};

	class GUISkin {
	public:

	public:
		static inline GUIStyle* label = 0;
	};

	class GUI {
	public:
		static GUISkin* get_skin();
		static void set_color(Color color);
		static void Label(Rect pos, GUIContent* content, GUIStyle* style);
	};

	class Event {
	public:
		EventType get_type();
		static Event* get_current();
	};

	class Input {
	public:
		static bool GetKeyDown(KeyCode key);
	};

	class SceneManager {
	public:
		static Array<GameObject*>* GetRootGameObjects(uint32_t* scene);
		static uintptr_t GetSceneAt(int idx);
		static int get_sceneCount();
	};

}

namespace FieldHelper {

	inline uint32_t GetEncryptedFieldAddrByFirstObjectDataType(const char* TypeClass, const wchar_t* DataType, int skipType = 0, bool checkAttr = false, Unity::FieldAttributes TargetAttr = Unity::FieldAttributes::PrivateScope) {

		int Counter = 0;

		auto type = (Unity::Type*)il2cpp::TypeGetObject(_(""), TypeClass);
 		if (!MemUtils::IsValidCheck(type))
			return 0;

		Unity::BindingFlags flags = Unity::BindingFlags::Public | Unity::BindingFlags::NonPublic | Unity::BindingFlags::Instance | Unity::BindingFlags::Static;
		auto fields = type->GetFields(flags);
		if (!MemUtils::IsValidCheck(fields))
			return 0;

 		for (int i = 0; i < fields->GetSize(); i++) {

			auto field = fields->Get(i);
			if (!MemUtils::IsValidCheck(field))
				continue;

			auto fieldType = field->get_FieldType();
			if (!MemUtils::IsValidCheck(fieldType))
				continue;

			auto attr = field->get_Attributes();
			if (checkAttr && attr != TargetAttr)
				continue;

			auto addr = field->GetFieldOffset() + 0x10;
			auto className = fieldType->get_FullNameOrDefault();
			if (className->Contains(DataType)) {
				if (Counter >= skipType)
					return addr;
				else Counter++;
			}
			
		}

		return 0;
	}

	inline uintptr_t GetDecryptedFieldInsideObject(Unity::Component* component, const wchar_t* FieldClass) {

		if (!MemUtils::IsValidCheck(component))
			return 0;

		auto components = component->GetComponentsInChildren((Unity::Type*)il2cpp::TypeGetObject(_("UnityEngine"), _("Component")));
		if (!MemUtils::IsValidCheck(components))
			return 0;

		for (int i = 0; i < components->GetSize(); i++) {

			auto obj = components->Get(i);
			if (!MemUtils::IsValidCheck((void*)obj))
				continue;
			
			auto type = Unity::Object::GetType(obj);
			if (!MemUtils::IsValidCheck(type))
				continue;

			auto className = type->get_FullNameOrDefault();
			if (className->Contains(FieldClass))
				return obj;

		}

		return 0;
	}

	inline const wchar_t* FindEncryptedClassNameByFirstObjectDataType(const char* TypeClass, const wchar_t* DataType, int skipType = 0, bool checkAttr = false, Unity::FieldAttributes TargetAttr = Unity::FieldAttributes::PrivateScope) {

		int Counter = 0;

		auto type = (Unity::Type*)il2cpp::TypeGetObject(_(""), TypeClass);
		if (!MemUtils::IsValidCheck(type))
			return _(L"");

		Unity::BindingFlags flags = Unity::BindingFlags::Public | Unity::BindingFlags::NonPublic | Unity::BindingFlags::Instance | Unity::BindingFlags::Static;
		auto fields = type->GetFields(flags);
		if (!MemUtils::IsValidCheck(fields))
			return _(L"");

		for (int i = 0; i < fields->GetSize(); i++) {

			auto field = fields->Get(i);
			if (!MemUtils::IsValidCheck(field))
				continue;

			auto fieldType = field->get_FieldType();
			if (!MemUtils::IsValidCheck(fieldType))
				continue;

			auto attr = field->get_Attributes();
			if (checkAttr && attr != TargetAttr)
				continue;

			auto addr = field->GetFieldOffset() + 0x10;
			auto className = fieldType->get_FullNameOrDefault();
			if (className->Contains(DataType)) {
				if (Counter >= skipType)
					return className->str;
				else Counter++;
			}

		}

		return _(L"");
	}

}

#endif // !ENGINE_H

