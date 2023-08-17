#pragma once
#include "FW1FontWrapper.h"

/*
* 폰트 관련해서 다른 라이브러리를 사용할 예정이니 이 라이브러리는 사용하지 마세요
*/
namespace hm
{
	enum class FONT_WEIGHT
	{
		LIGHT,
		NORMAL,
		BOLD,
		ULTRA_BOLD,
		END,
	};

	enum class FONT_ALIGN
	{
		LEFT,
		CENTER,
		RIGHT,
	};

	enum
	{
		FONT_WEIGHT_COUNT = FONT_WEIGHT::END,
	};

	struct FontInfo
	{
		wstring szText;
		float fFontSize;
		Vec3 vFontPos;
		FONT_WEIGHT eFontWeight;
		UINT32 iFontColor;
		FONT_ALIGN eFontAlign;

	};

/*
* 폰트 관련해서 다른 라이브러리를 사용할 예정이니 이 라이브러리는 사용하지 마세요
*/
	class Font
	{
	public:
		Font();
		~Font();

	public:
		// Font를 오브젝트 단위로 관리할 필요가 없다!
		void Initialize(const WindowInfo& windowInfo, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
		void DrawString(const wstring& szText, float fFontSize, const Vec3& vPos, FONT_WEIGHT eWeight = FONT_WEIGHT::NORMAL, UINT32 iColor = 0xffffffff, FONT_ALIGN eFontAlign = FONT_ALIGN::CENTER);
		void Render();

	private:
		void CreateFontWrapperGroup();

	private:
		std::array<ComPtr<IFW1FontWrapper>, FONT_WEIGHT_COUNT> m_arrFontWrapperGroup;
		std::queue<FontInfo> m_qFontQueue;
		int m_iWindowHeight;

		ComPtr<IDWriteFactory> m_pWriteFactory;
		ComPtr<IFW1Factory> m_pFontFactory;
		ComPtr<ID3D11Device> m_pDevice;
		ComPtr<ID3D11DeviceContext> m_pContext;

	};

}

