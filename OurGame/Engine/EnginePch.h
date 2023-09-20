#pragma once
//#define _HAS_STD_BYTE 0 
#pragma warning(disable: 28020)
#pragma warning(disable: 6011)

#include <windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <functional>
#include <mutex>
#include <queue>
#include <type_traits>
#include <optional>
#include <bitset>
#include <numeric>
#include <filesystem>
#include <algorithm>
#include <typeinfo>
#include <typeindex>

#include "imgui_internal.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "ImGuizmo.h"

// DirectX11 Library
#include "d3d11.h"

#include <d3d12.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
#include <dwrite.h>
#include <d2d1.h>



#include "SimpleMath.h"

// FBX SDK Library
#include "FBX/fbxsdk.h"
// PhysX Library

// FMod Library
#include "FMod\\fmod_studio.hpp"
#include "FMod\\fmod.hpp"
#include "FMod\\fmod_common.h"
#include "FMod\\fmod_codec.h"

#include <Assimp\\Importer.hpp>
#include <Assimp\\postprocess.h>
#include <Assimp\\scene.h>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_debug.lib")
#pragma comment(lib, "PhysX\\debug\\PhysX_64.lib")
#pragma comment(lib, "PhysX\\debug\\PhysXFoundation_64.lib")
#pragma comment(lib, "PhysX\\debug\\PhysXCommon_64.lib")
#pragma comment(lib, "PhysX\\debug\\PhysXCooking_64.lib")
#pragma comment(lib, "PhysX\\debug\\PhysXExtensions_static_64.lib")
#pragma comment(lib, "PhysX\\debug\\PhysXPvdSDK_static_64.lib")
#pragma comment(lib, "PhysX\\debug\\PhysXCharacterKinematic_static_64.lib")
#pragma comment(lib, "FMod\\debug\\fmodL_vc.lib")
#pragma comment(lib, "FMod\\debug\\fmodstudioL_vc.lib")
#pragma comment(lib, "FBX\\debug\\libfbxsdk-md.lib")
#pragma comment(lib, "FBX\\debug\\libxml2-md.lib")
#pragma comment(lib, "FBX\\debug\\zlib-md.lib")
#pragma comment(lib, "Assimp\\assimp-vc143-mt.lib")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex.lib")
#pragma comment(lib, "PhysX\\release\\PhysX_64.lib")
#pragma comment(lib, "PhysX\\release\\PhysXFoundation_64.lib")
#pragma comment(lib, "PhysX\\release\\PhysXCommon_64.lib")
#pragma comment(lib, "PhysX\\release\\PhysXCooking_64.lib")
#pragma comment(lib, "PhysX\\release\\PhysXExtensions_static_64.lib")
#pragma comment(lib, "PhysX\\release\\PhysXPvdSDK_static_64.lib")
#pragma comment(lib, "PhysX\\release\\PhysXCharacterKinematic_static_64.lib")
#pragma comment(lib, "FMod\\release\\fmod_vc.lib")
#pragma comment(lib, "FMod\\release\\fmodstudio_vc.lib")
#pragma comment(lib, "FBX\\release\\libfbxsdk-md.lib")
#pragma comment(lib, "FBX\\release\\libxml2-md.lib")
#pragma comment(lib, "FBX\\release\\zlib-md.lib")
#pragma comment(lib, "Assimp\\assimp-vc143-mt.lib")
#endif

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "FW1FontWrapper\\FW1FontWrapper.lib")

namespace fs = std::filesystem;
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;
using namespace physx;

using Vec2 = DirectX::SimpleMath::Vector2;
using Vec3 = DirectX::SimpleMath::Vector3;
using Vec4 = DirectX::SimpleMath::Vector4;
using Matrix = DirectX::SimpleMath::Matrix;
using Quaternion = DirectX::SimpleMath::Quaternion;
using std::shared_ptr;
using std::unique_ptr;
using std::static_pointer_cast;
using std::dynamic_pointer_cast;
using std::make_shared;
using std::make_unique;
using std::wstring;
using std::string;

#define DECLARE_SINGLE(type)  \
private:					  \
	type();				  \
	~type();				  \
							  \
public:						  \
	static type* GetInstance()\
	{						  \
		static type instance; \
		return &instance;	  \
	}						  \

#define GET_SINGLE(type) type::GetInstance()
#define CONTEXT gpEngine->GetGraphicsCore()->GetContext()
#define DXGI gpEngine->GetGraphicsCore()->GetDxgi()
#define DEVICE gpEngine->GetGraphicsCore()->GetDevice()
#define CONST_BUFFER(type) gpEngine->GetConstantBuffer(type)
#define PHYSICS gpEngine->GetPhysics()->GetPhysics()
#define FONT gpEngine->GetFont()
#define TOOL gpEngine->GetTool()
#define GLOBAL_GRAVITY gpEngine->GetPhysics()->GetGravity()
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) {if(p)	{ delete[] p; (p)=NULL; }}
#define IS_PRESS(key) GET_SINGLE(Input)->GetButtonPress(key)
#define IS_HOT_PRESS(key) GET_SINGLE(Input)->GetHotKeyPress(key)
#define IS_DOWN(key) GET_SINGLE(Input)->GetButtonDown(key)
#define IS_UP(key) GET_SINGLE(Input)->GetButtonUp(key)
#define IS_HOT_UP(key) GET_SINGLE(Input)->GetHotKeyUp(key)
#define IS_NONE(key) GET_SINGLE(Input)->GetButtonNone(key)
#define DELTA_TIME GET_SINGLE(Timer)->GetDeltaTime()
#define ACTIVE_SCENE GET_SINGLE(SceneManager)->GetActiveScene()
#define RESOLUTION gpEngine->GetResolution()
#define RENDERTARGET_2D gpEngine->GetGraphicsCore()->GetRenderTarget2D()
#define LARGE_RESOURCE(path) wstring(L"..\\..\\..\\LargeResource\\") + path

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
/*
* 기존 assert 함수를 확장한 함수.
* 메시지 박스를 통해 어떤 이유로 에러가 발생했는지 확인할 수 있다.
*/
static void AssertEx(bool _expression, const std::wstring& _message)
{
	if (_expression)
		return;

	MessageBoxW(NULL, _message.c_str(), L"Assert", MB_OK);
	assert(_expression);
}

template <typename T>
inline void hash_combine(std::size_t& seed, const T& value) 
{
	seed ^= std::hash<T>{}(value)+0x9e3779b9 + (seed << 6) + (seed >> 2);
}

static wstring ChangeFileExt(const wstring& _srcPath, const wstring& _dstExt)
{
	AssertEx(fs::is_regular_file(_srcPath), L"ChangeFileExt() - 파일이 아닌 폴더가 입력으로 들어옴");

	fs::path parentPath = fs::path(_srcPath).parent_path();
	wstring fileName = fs::path(_srcPath).filename();

	size_t idx = fileName.rfind(L'.');
	fileName = fileName.substr(0, idx);
	fileName += L"." + _dstExt;

	return parentPath.wstring() + L"\\" + fileName;
}

namespace hm { 
	class Engine;
}
using namespace hm;
extern unique_ptr<Engine> gpEngine;

#include "EnumDefine.h"
#include "Types.h"

wstring s2ws(const string& s);
string ws2s(const wstring& ws);