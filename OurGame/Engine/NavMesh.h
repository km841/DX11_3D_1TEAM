#pragma once
#include "Mesh.h"

namespace hm
{
    class NavMesh :
        public Mesh
    {
        friend class NavMeshComponent;
    public:
        NavMesh();
        virtual ~NavMesh();

    public:
        void CreatePolygonInfo();
        void CheckAdjacentInfo();
        bool CheckAdjVector(int _polyIndex, int _checkIndex);

        size_t GetNavMeshPolygonCount() { return mNavMeshPolygonVec.size(); }
        NavMeshPolygon& GetNavMeshPolygon(int _index) { return mNavMeshPolygonVec[_index]; }

    private:
        std::vector<NavMeshPolygon> mNavMeshPolygonVec;
        std::vector<Vec3>			mVertexPosVec;
        std::vector<Vec3>			mVecOriginVertexPos;
        std::vector<int>			mIndexVec;
        Vec3						mMin;
        Vec3						mMax;
        Vec3						mOriginMin;
        Vec3						mOriginMax;
        int                         mPolyCount;
    };
}


