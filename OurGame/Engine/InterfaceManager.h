#pragma once
#include "Interface.h"

namespace hm
{
	using FontIndex = int;
	using FontSize = int;
	class InterfaceManager
	{
		DECLARE_SINGLE(InterfaceManager);

	public:
		void Initialize();
		void Update();
		void Render();

		void AddInterface(Interface* _interface);
		Interface* GetInterface(const string& _name);
		ImFont* LoadFont(const string& _fontPath, int _fontSize);
		void SetFont(const string& _fontPath, int _fontSize);

	private:
		std::map<InterfaceInfo, Interface*> mInterfaceMap;
		std::map<string, std::map<FontSize, FontIndex>> mFontMap;
	};
}


