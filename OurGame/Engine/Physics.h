#pragma once
namespace hm
{
	class GameObject;
	class Physics
	{
	public:
		Physics();
		~Physics();

	public:
		void Initialize();
		void Update();
		void Render();

	public:
		void AddActor(GameObject* _pGameObject);
		void RemoveActor(GameObject* _pGameObject);

		void SetGravity(Vec3 _g)
		{ 
			mGravity = _g;
			mpScene->setGravity(mGravity);
		}

		const Vec3& GetGravity() { return mGravity; }
		PxPhysics* GetPhysics() { return mpPhysics; }
		PxCooking* GetCooking() { return mpCooking; }
		PxScene* GetScene() { return mpScene; }

		static PxFilterFlags PlayerFilterShader(
			PxFilterObjectAttributes _attributes0, PxFilterData _filterData0,
			PxFilterObjectAttributes _attributes1, PxFilterData _filterData1,
			PxPairFlags& _pairFlags, const void* _pConstantBlock, PxU32 _constantBlockSize);

		PxControllerManager* GetControllerManager() { return mpControllerMgr; }
		class ContactCallback* GetCallback() { return mpCallback; }

		bool IsOverlapped(GameObject* _pFirstObject, GameObject* _pSecondObject);

	private:
		PxDefaultAllocator		mAllocCallback;
		PxDefaultErrorCallback  mErrorCallback;
		PxFoundation* mpFoundation;
		PxPhysics* mpPhysics;
		PxCooking* mpCooking;

		PxPvdTransport* mpTransfort;
		PxPvd* mpPvd;
		PxPvdSceneClient* mpSceneClient;
		PxScene* mpScene;
		PxControllerManager* mpControllerMgr;

		PxDefaultCpuDispatcher* mpCpuDispatcher;
		class ContactCallback* mpCallback;

		PxOverlapBuffer mOverlapBuffer;

		Vec3 mGravity;
	};

}

