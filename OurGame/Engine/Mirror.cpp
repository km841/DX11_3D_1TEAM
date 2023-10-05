#include "pch.h"
#include "Mirror.h"
#include "GameObject.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Engine.h"

namespace hm
{
	Mirror::Mirror()
		: Component(ComponentType::Mirror)
	{
	}

	Mirror::~Mirror()
	{
	}

	void Mirror::Initialize()
	{
		CreateReflectPlane();
	}

	void Mirror::Update()
	{
		CreateReflectPlane();
	}

	void Mirror::FinalUpdate()
	{

	}

	void Mirror::Render()
	{

	}

	Component* Mirror::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new Mirror);
	}

	void Mirror::CreateReflectPlane()
	{
		Vec3 pos = GetTransform()->GetPosition();
		mReflectPlane = Plane(pos, Vec3(-1.f, 0.f, 0.f));
		//mReflectMatrix = Matrix::CreateReflection(mReflectPlane);
		mReflectMatrix = Matrix::Identity;
	}
	void Mirror::RenderMasking(Camera* _pCamera)
	{
		shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Material>(L"Masking")->GetShader();
		GetMeshRenderer()->RenderExceptForShader(_pCamera, pShader);
	}
	void Mirror::RenderReflect(Camera* _pCamera)
	{
		ReflectParams param = {};
		param.reflectMatrix = mReflectMatrix;
		CONST_BUFFER(ConstantBufferType::Reflect)->PushData(&param, sizeof(ReflectParams));
		CONST_BUFFER(ConstantBufferType::Reflect)->Mapping();

		shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Material>(L"Mirror")->GetShader();
		_pCamera->RenderReflect(pShader);

		param.reflectMatrix = Matrix::Identity;
		CONST_BUFFER(ConstantBufferType::Reflect)->PushData(&param, sizeof(ReflectParams));
		CONST_BUFFER(ConstantBufferType::Reflect)->Mapping();
	}
}

