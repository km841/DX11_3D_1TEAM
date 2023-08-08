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
		: pos(_pos), uv(Vec2::Zero), normal(Vec3::Zero), tangent(Vec3::Zero)
	{}

	Vec3 pos = Vec3::Zero;
	Vec2 uv = Vec2::Zero;
	Vec3 normal = Vec3::Zero;
	Vec3 tangent = Vec3::Zero;
};

struct TransformParams
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProjection;
	Matrix matWV;
	Matrix matWVP;
	Matrix matWVPInv;
};

enum
{
	MATERIAL_VALUE_COUNT = 4,
};

struct MaterialParams
{
	MaterialParams()
	{
		memset(this, 0, sizeof(MaterialParams));
	}

	std::array<int, MATERIAL_VALUE_COUNT> intParams;
	std::array<float, MATERIAL_VALUE_COUNT> floatParams;
	std::array<int, MATERIAL_VALUE_COUNT> texOnParams;
	std::array<Vec2, MATERIAL_VALUE_COUNT> vec2Params;
	std::array<Vec3, MATERIAL_VALUE_COUNT> vec3Params;
	std::array<Vec4, MATERIAL_VALUE_COUNT> vec4Params;

	void SetInt(int _index, int _value) { intParams[_index] = _value; }
	void SetFloat(int _index, float _value) { floatParams[_index] = _value; }
	void SetTexOn(int _index, int _value) { texOnParams[_index] = _value; }
	void SetVec2(int _index, Vec2 _value) { vec2Params[_index] = _value; }
	void SetVec3(int _index, Vec3 _value) { vec3Params[_index] = _value; }
	void SetVec4(int _index, Vec4 _value) { vec4Params[_index] = _value; }
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
		// RigidStatic¿œ ãö,
		if (GeometryType::Plane == eGeometryType)
		{
			planeGeom = PxPlaneGeometry();
		}
	}

	PxBoxGeometry boxGeom;
	PxCapsuleGeometry capsuleGeom;
	PxPlaneGeometry planeGeom;
	PxSphereGeometry sphereGeom;
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

struct InstancingParams
{
	Matrix matWorld;
	Matrix matWV;
	Matrix matWVP;
};
