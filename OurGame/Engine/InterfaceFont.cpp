#include "pch.h"
#include "InterfaceFont.h"
#include "InterfaceManager.h"

namespace hm
{
	InterfaceFont::InterfaceFont(const string& _fontPath, int _fontSize)
	{
		GET_SINGLE(InterfaceManager)->SetFont(_fontPath, _fontSize);
	}

	InterfaceFont::~InterfaceFont()
	{
		ImGui::PopFont();
	}
}

