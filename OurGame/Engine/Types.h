#pragma once
struct WindowInfo
{
	HWND hwnd;
	int width;
	int height;
};

struct Vertex
{
	Vertex() {}
	Vertex(Vec3 _pos, Vec2 _uv, Vec3 _normal, Vec3 _tangent)
		: pos(_pos), uv(_uv), normal(_normal), tangent(_tangent)
	{}
	Vertex(Vec3 _pos)
		: pos(_pos)
	{}

	Vec3 pos = Vec3::Zero;
	Vec2 uv = Vec2::Zero;
	Vec3 normal = Vec3::Zero;
	Vec3 tangent = Vec3::Zero;
	Vec4 weights = Vec4::Zero;
	Vec4 indices = Vec4::Zero;
};

struct alignas(16) TransformParams
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProjection;
	Matrix matWV;
	Matrix matWVP;
	Matrix matViewInv;
	Matrix matWVPInv;
	Matrix matOldWorld;
	Matrix matOldView;
};

enum
{
	MATERIAL_VALUE_COUNT = 4,
	TEXTURE_VALUE_COUNT = 16,
};

struct alignas(16) AnimFrameParams
{
	Vec4 scale;
	Vec4 rotation; // ���ʹϾ�
	Vec4 translation;
};

struct alignas(16) BloomParams
{
	int bloomEnable = 0;
	float bloomPower = 0.f;
	float padding1 = 0.f;
	float padding2 = 0.f;
	Vec4 bloomColor = {};
	Vec4 bloomFilter = {};
};

struct alignas(16) MaterialParams
{
	MaterialParams()
	{
		memset(this, 0, sizeof(MaterialParams));
	}

public:
	void SetInt(int _index, int _value) { intParams[_index] = _value; }
	void SetFloat(int _index, float _value) { floatParams[_index] = _value; }
	void SetTexOn(int _index, int _value) { texOnParams[_index] = _value; }
	void SetVec2(int _index, Vec2 _value) { vec2Params[_index] = _value; }
	void SetVec4(int _index, Vec4 _value) { vec4Params[_index] = _value; }
	void SetMatrix(int _index, Matrix _value) { matParams[_index] = _value; }

public:
	std::array<int, MATERIAL_VALUE_COUNT> intParams; // 16
	std::array<float, MATERIAL_VALUE_COUNT> floatParams; // 16
	std::array<int, TEXTURE_VALUE_COUNT> texOnParams; // 64
	std::array<Vec2, MATERIAL_VALUE_COUNT> vec2Params; // 4 * 8 = 32
	std::array<Vec4, MATERIAL_VALUE_COUNT> vec4Params; // 4 * 16 = 64
	std::array<Matrix, MATERIAL_VALUE_COUNT> matParams;
};

struct MassProperties
{
	MassProperties(float _staticFriction = 0.5f, float _dynamicFriction = 0.2f, float _restitution = 0.603f)
		: staticFriction(_staticFriction)
		, dynamicFriction(_dynamicFriction)
		, restitution(_restitution)
	{ }

	float staticFriction;
	float dynamicFriction;
	float restitution;
};

struct Geometries
{
	Geometries(GeometryType eGeometryType, Vec3 vBoxHalfSize)
		: eGeomType(GeometryType::Box)
	{
		if (GeometryType::Box == eGeometryType)
		{
			boxGeom = PxBoxGeometry(vBoxHalfSize);
		}
	}

	Geometries(GeometryType eGeometryType, float fRadius, float fHalfHeight)
		: eGeomType(GeometryType::Capsule)
	{
		if (GeometryType::Capsule == eGeometryType)
		{
			capsuleGeom = PxCapsuleGeometry(fRadius, fHalfHeight);
		}
	}

	Geometries(GeometryType eGeometryType, float fRadius)
		: eGeomType(GeometryType::Sphere)
	{
		if (GeometryType::Sphere == eGeometryType)
		{
			sphereGeom = PxSphereGeometry(fRadius);
		}
	}

	Geometries(GeometryType eGeometryType)
		: eGeomType(GeometryType::Plane)
	{
		// RigidStatic�� ��,
		if (GeometryType::Plane == eGeometryType)
		{
			planeGeom = PxPlaneGeometry();
		}
	}

	Geometries(GeometryType eGeometryType, PxTriangleMesh* _pTriangleMesh, Vec3 _size)
		: eGeomType(GeometryType::Mesh)
	{
		// RigidStatic�� ��,
		if (GeometryType::Mesh == eGeometryType)
		{
			triangleGeom = PxTriangleMeshGeometry(_pTriangleMesh, PxMeshScale(_size));
		}
	}

	Geometries(GeometryType eGeometryType, PxConvexMesh* _pTriangleMesh, Vec3 _size)
		: eGeomType(GeometryType::Convex)
	{
		if (GeometryType::Convex == eGeometryType)
		{
			convexGeom = PxConvexMeshGeometry(_pTriangleMesh, PxMeshScale(_size));
		}
	}

	PxBoxGeometry boxGeom;
	PxCapsuleGeometry capsuleGeom;
	PxPlaneGeometry planeGeom;
	PxSphereGeometry sphereGeom;
	PxTriangleMeshGeometry triangleGeom;
	PxConvexMeshGeometry convexGeom;
	GeometryType eGeomType;
};

struct PhysicsInfo
{
	PhysicsInfo()
		: eActorType(ActorType::Static)
		, eGeometryType(GeometryType::Box)
		, size(Vec3(1.f, 1.f, 1.f))
		, massProperties(MassProperties())
		, pGeometries(nullptr)
		, filterData{}
	{
	}

	ActorType eActorType;
	GeometryType eGeometryType;
	Vec3 size;
	MassProperties massProperties;
	Geometries* pGeometries;
	PxFilterData filterData;
};

union InstanceID
{
	struct
	{
		UINT32 meshID;
		UINT32 materialID;
	};
	UINT64 id;
};

struct alignas(16) InstancingParams
{
	Matrix matWorld;
	Matrix matWV;
	Matrix matWVP;
};

struct alignas(16) DistortionParams
{
	Vec2 distortion1;
	Vec2 distortion2;
	Vec2 distortion3;
	float distortionScale;
	float distortionBias;
};

struct alignas(16) NoiseParams
{
	float frameTime;
	Vec3 scrollSpeeds;
	Vec3 scales;
	float padding;
};

struct alignas(16) ReflectParams
{
	Matrix reflectMatrix;
	Matrix reflectRVPMatrix;
	int use;
	Vec3 padding;
};

struct ScreenEffectInfo
{
	ScreenEffectType eEffectType;
	float endTime;
	float curTime = 0.f;
	Vec4 param1 = Vec4::Zero;
	Vec4 param2 = Vec4::Zero;
	std::function<void()> startCallback;
	std::function<void()> endCallback;
};

#include "Transform.h"
struct NavWorkData
{
	std::function<void(const std::list<Vec3>&)> callback;
	hm::Transform* pTransform;
	Vec3 end;
};

struct NavResultData
{
	std::function<void(const std::list<Vec3>&)> callback;
	std::list<Vec3> pathList;
};

struct NavMeshPolygon
{
	std::vector<Vec3>		mVertexPosVec;
	std::vector<Vec3>		mVertexOriginPosVec;
	std::vector<int>		mAdjIndexVec;
	int                     mIndex;
	Vec3                    mMin;
	Vec3                    mMax;
};

struct NavigationCell
{
	NavigationCell()
	{
		eType = NaviMeshCellType::None;
		parentIdx = -1;
		g = 0.f;
		h = 0.f;
		f = 0.f;
		bEnable = true;
	}

	void Clear()
	{
		eType = NaviMeshCellType::None;
		parentIdx = -1;
		g = -1.f;
		h = -1.f;
		f = -1.f;
	}

	NavigationCell operator+ (const NavigationCell& _cell)
	{
		NavigationCell cell;
		return cell;
	}

	NaviMeshCellType eType;
	NavMeshPolygon polygon;
	Vec3 center;
	int parentIdx;
	float g;
	float h;
	float f;
	bool bEnable;
};

#include "Texture.h"
struct ButtonInfo
{
	shared_ptr<hm::Texture> pNonHoveredTexture;
	shared_ptr<hm::Texture> pHoveredTexture;
	shared_ptr<hm::Texture> pClickedTexture;

	std::function<void()> nonHoveredCallback;
	std::function<void()> hoveredCallback;
	std::function<void()> clickedCallback;
};

struct PlayerKeyInfo
{
	void SetLeftKey(KeyType _eKeyType) 
	{ 
		eLeftKey = _eKeyType; 
		if (KeyType::LEFT == eLeftKey)
			eRightKey = KeyType::RIGHT;

		if (KeyType::RIGHT == eLeftKey)
			eRightKey = KeyType::LEFT;
	}
	void SetForwardKey(KeyType _eKeyType) 
	{ 
		eForwardKey = _eKeyType; 

		if (KeyType::UP == eForwardKey)
			eBackwardKey = KeyType::DOWN;

		if (KeyType::DOWN == eForwardKey)
			eBackwardKey = KeyType::UP;
	}

	KeyType eLeftKey;
	KeyType eForwardKey;
	KeyType eRightKey;
	KeyType eBackwardKey;
};
