#include "pch.h"
#include "PaperBurnScript.h"
#include "Timer.h"
#include "MeshRenderer.h"
#include "Material.h"

namespace hm
{
	PaperBurnScript::PaperBurnScript()
		: mAccTime(0.f)
	{
	}

	void PaperBurnScript::FixedUpdate()
	{
		mAccTime += DELTA_TIME;
		GetMeshRenderer()->GetMaterial()->SetFloat(0, mAccTime);
	}
}


