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

		const Vec3& GetGravity() { return mGravity; }
		PxPhysics* GetPhysics() { return mpPhysics; }
		PxCooking* GetCooking() { return mpCooking; }

		static PxFilterFlags PlayerFilterShader(
			PxFilterObjectAttributes _attributes0, PxFilterData _filterData0,
			PxFilterObjectAttributes _attributes1, PxFilterData _filterData1,
			PxPairFlags& _pairFlags, const void* _pConstantBlock, PxU32 _constantBlockSize);

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

		Vec3 mGravity;
	};

}

