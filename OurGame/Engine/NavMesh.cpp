#include "pch.h"
#include "NavMesh.h"

namespace hm
{
	NavMesh::NavMesh()
		: mPolyCount(0)
		, mMin(Vec3(1000000.f, 1000000.f, 1000000.f))
		, mMax(Vec3(-1000000.f, -1000000.f, -1000000.f))
	{

	}

	NavMesh::~NavMesh()
	{
	}

	void NavMesh::CreatePolygonInfo()
	{
		size_t count = mIndexVec.size();
		int polyIndex = 0;
		for (size_t i = 0; i < count; i += 3)
		{
			int index1 = mIndexVec[i];
			int index2 = mIndexVec[i + 1];
			int index3 = mIndexVec[i + 2];

			Vec3 vertex1 = mVertexPosVec[index1];
			Vec3 vertex2 = mVertexPosVec[index2];
			Vec3 vertex3 = mVertexPosVec[index3];

			NavMeshPolygon poly;
			poly.mIndex = polyIndex;
			poly.mVertexPosVec.push_back(vertex1);
			poly.mVertexPosVec.push_back(vertex2);
			poly.mVertexPosVec.push_back(vertex3);

			poly.mVertexOriginPosVec.push_back(vertex1);
			poly.mVertexOriginPosVec.push_back(vertex2);
			poly.mVertexOriginPosVec.push_back(vertex3);

			mNavMeshPolygonVec.push_back(poly);

			++polyIndex;
		}
	}

	void NavMesh::CheckAdjacentInfo()
	{
		size_t count = mNavMeshPolygonVec.size();

		for (int i = 0; i < count; ++i)
		{
			for (int j = 0; j < count; ++j)
			{
				for (int p = 0; p < 3; ++p)
				{
					for (int q = 0; q < 3; ++q)
					{
						if (i != j && Vec3::Distance(mNavMeshPolygonVec[i].mVertexPosVec[p], mNavMeshPolygonVec[j].mVertexPosVec[q]) < 0.001f)
						{
							if (false == CheckAdjVector(i, j))
							{
								mNavMeshPolygonVec[i].mAdjIndexVec.push_back(j);
								mNavMeshPolygonVec[j].mAdjIndexVec.push_back(i);
							}
						}
					}
				}
			}
		}
	}
	bool NavMesh::CheckAdjVector(int _polyIndex, int _checkIndex)
	{
		size_t count = mNavMeshPolygonVec[_polyIndex].mAdjIndexVec.size();

		for (size_t i = 0; i < count; ++i)
		{
			if (mNavMeshPolygonVec[_polyIndex].mAdjIndexVec[i] == _checkIndex)
				return true;
		}

		return false;
	}
}


