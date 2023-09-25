#pragma once
#include "Component.h"

namespace hm
{
	class NavAgent :
		public Component
	{
	public:
		NavAgent();
		virtual ~NavAgent();
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void Initialize() override;
		virtual void Update() override;

	public:
		bool Move(const Vec3& _endPos);
		bool MoveOnNavMesh(const Vec3& _endPos);
		bool MoveOnNavMesh(const Vec3& _dir, float _speed);
		void SetMoveSpeed(float _speed) { mMoveSpeed = _speed; }
		void SetRotationSpeed(float _speed) { mRotationSpeed = _speed; }
		void SetApplyNavMesh(bool _bFlag) { mbApplyNavMesh = _bFlag; }
		bool GetApplyNavMesh() { return mbApplyNavMesh; }
		const Vec3& GetTargetPos();
		std::list<Vec3>& GetPathList() { return mPathList; }
		void DeleteTargetPos() { mPathList.pop_back(); }

	public:
		void AddTargetPos(const Vec3& _targetPos) { mPathList.push_back(_targetPos); }
		void ClearPathList() { mPathList.clear(); }
		bool IsEmptyPathList() { return mPathList.empty(); }
		bool IsRotating() { return mbRotating; }
		size_t GetPathListCount() { return mPathList.size(); }

	private:
		float mMoveSpeed;
		float mRotationSpeed;
		bool mbApplyNavMesh;
		bool mbRotating;
		Vec3 mCurFaceDir;

	protected:
		std::list<Vec3> mPathList;

	};
}


