#include "pch.h"
#include "FontManager.h"
#include "Engine.h"

namespace hm
{
	FontManager::FontManager()
	{

	}

	FontManager::~FontManager()
	{
		for (auto& font : mFontMap)
		{
			font.second->Release();
		}
		mFontMap.clear();

		for (auto& color : mColorMap)
		{
			color.second->Release();
		}
		mColorMap.clear();

		if (nullptr != mpWriteFactory)
		{
			mpWriteFactory->Release();
			mpWriteFactory = nullptr;
		}
	}

	void FontManager::Initialize()
	{
		HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(mpWriteFactory), (IUnknown**)&mpWriteFactory);

		AssertEx(SUCCEEDED(hr), L"FontManager::Initialize() - Font Factory 생성 실패");

		CreateTextFormat("Gungseo", TEXT("궁서체"),
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_ULTRA_EXPANDED,
			20.f, TEXT("ko"));

		CreateTextFormat("FreshGothic", TEXT("맑은 고딕"),
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_ULTRA_EXPANDED,
			20.f, TEXT("ko"));
	}

	void FontManager::CreateTextFormat(const string& _name, const TCHAR* _pFontName,
		int _weight, int _style, int _stretch, float _size,
		const TCHAR* _pLocalName)
	{
		IDWriteTextFormat* pFont = FindTextFormat(_name);
		AssertEx(pFont == nullptr, L"FontManager::CreateTextFormat() - 이미 존재하는 TextFormat에 대한 생성 시도");

		// Text Format을 설정한다.
		// 1번인자 : 폰트 이름을 입력한다. 
		// 2번인자 : 특정 폰트는 컬렉션을 가지고 있다. 예 Arial 은 Arial Black 이런식
		// 3번인자 : 폰트 굵기 4번인자 : 기울기
		// 5번인자 : 자간 6번인자 : 폰트 크기
		// 7번인자 : 언어 지역 이름을 설정한다. 한국은 ko - KR 미국은 en - us 
		// 8번인자 : 텍스트 인터페이스
		HRESULT hr = mpWriteFactory->CreateTextFormat(_pFontName,
			nullptr,
			(DWRITE_FONT_WEIGHT)_weight,
			(DWRITE_FONT_STYLE)_style,
			(DWRITE_FONT_STRETCH)_stretch,
			_size, _pLocalName, &pFont);

		AssertEx(SUCCEEDED(hr), L"FontManager::CreateTextFormat() - TextFormat 생성 실패");
		mFontMap.insert(make_pair(_name, pFont));
	}

	ID2D1SolidColorBrush* FontManager::CreateColor(float _r, float _g, float _b, float _a)
	{
		// RGB 값 생성
		ID2D1SolidColorBrush* pColor = FindColor(_r, _g, _b, _a);

		if (nullptr != pColor)
		{
			return pColor;
		}

		// 0 ~ 1 사이의 값을 색상값으로 이용해야 한다.
		HRESULT hr = RENDERTARGET_2D->CreateSolidColorBrush(
			D2D1::ColorF(_r, _g, _b, _a), &pColor);

		AssertEx(SUCCEEDED(hr), L"FontManager::CreateColor() - 컬러 생성 실패");
		mColorMap.insert(std::make_pair(CreateColorKey(_r, _g, _b, _a), pColor));

		return pColor;
	}

	ID2D1SolidColorBrush* FontManager::CreateColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		// 컬러값을 받아온다.
		ID2D1SolidColorBrush* pColor = FindColor(_r, _g, _b, _a);

		// 컬러값이 존재하는 경우
		if (nullptr != pColor)
		{
			return pColor;
		}

		// 0 ~ 1 사이의 값을 색상값으로 이용해야 한다.
		HRESULT hr = RENDERTARGET_2D->CreateSolidColorBrush(
			D2D1::ColorF(_r / 255.f, _g / 255.f, _b / 255.f, _a / 255.f),
			&pColor);

		AssertEx(SUCCEEDED(hr), L"FontManager::CreateColor() - 컬러 생성 실패");

		mColorMap.insert(std::make_pair(CreateColorKey(_r, _g, _b, _a), pColor));

		return pColor;
	}

	ID2D1SolidColorBrush* FontManager::CreateColor(const Vec4& _color)
	{
		ID2D1SolidColorBrush* pColor = FindColor(_color);

		if (nullptr != pColor)
		{
			return pColor;
		}

		// 0 ~ 1 사이의 값을 색상값으로 이용해야 한다.
		HRESULT hr = RENDERTARGET_2D->CreateSolidColorBrush(
			D2D1::ColorF(_color.x, _color.y, _color.z, _color.w),
			&pColor);

		AssertEx(SUCCEEDED(hr), L"FontManager::CreateColor() - 컬러 생성 실패");

		mColorMap.insert(std::make_pair(CreateColorKey(_color), pColor));

		return pColor;
	}

	ID2D1SolidColorBrush* FontManager::CreateColor(UINT32 _color)
	{
		ID2D1SolidColorBrush* pColor = FindColor(_color);

		if (nullptr != pColor)
		{
			return pColor;
		}

		float	r, g, b, a;

		// 8비트에대한 int 값 / 255.f (0 ~ 1 사이의 값)
		b = (_color & 0x000000ff) / 255.f;
		g = ((_color >> 8) & 0x000000ff) / 255.f;
		r = ((_color >> 16) & 0x000000ff) / 255.f;
		a = ((_color >> 24) & 0x000000ff) / 255.f;

		// 0 ~ 1 사이의 값을 색상값으로 이용해야 한다.
		HRESULT hr = RENDERTARGET_2D->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &pColor);
		AssertEx(SUCCEEDED(hr), L"FontManager::CreateColor() - 컬러 생성 실패");

		mColorMap.insert(std::make_pair(_color, pColor));

		return pColor;
	}

	IDWriteTextLayout* FontManager::CreateTextLayout(const TCHAR* _pText, IDWriteTextFormat* _pFormat, float _width, float _height)
	{
		IDWriteTextLayout* pLayout = nullptr;

		// 레이아웃 생성
		HRESULT hr = mpWriteFactory->CreateTextLayout(_pText, lstrlen(_pText),
			_pFormat, _width, _height, &pLayout);

		AssertEx(SUCCEEDED(hr), L"FontManager::CreateTextLayout() - TextLayout 생성 실패");

		return pLayout;
	}

	IDWriteTextLayout* FontManager::CreateTextLayout(const TCHAR* _pText, const string& _fontKey, float _width, float _height)
	{
		IDWriteTextFormat* pFormat = FindTextFormat(_fontKey);

		if (!pFormat)
		{
			return nullptr;
		}

		IDWriteTextLayout* pLayout = nullptr;

		HRESULT hr = mpWriteFactory->CreateTextLayout(_pText, lstrlen(_pText),
			pFormat, _width, _height, &pLayout);

		AssertEx(SUCCEEDED(hr), L"FontManager::CreateTextLayout() - TextLayout 생성 실패");

		return pLayout;
	}

	ID2D1SolidColorBrush* FontManager::FindColor(float _r, float _g, float _b, float _a)
	{
		unsigned int	color = 0;

		unsigned char	r1, g1, b1, a1;

		// 0 - 255 unsigned Char를 이용
		r1 = (unsigned char)(_r * 255);
		g1 = (unsigned char)(_g * 255);
		b1 = (unsigned char)(_b * 255);
		a1 = (unsigned char)(_a * 255);

		// 8 비트 씩 시프트 연산을 통해 
		// 4Byte Unsigned int에 값을 삽입한다.
		color = a1;
		color = (color << 8) | r1;
		color = (color << 8) | g1;
		color = (color << 8) | b1;

		return FindColor(color);
	}

	ID2D1SolidColorBrush* FontManager::FindColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		unsigned int	color = 0;

		color = _a;
		color = (color << 8) | _r;
		color = (color << 8) | _g;
		color = (color << 8) | _b;

		return FindColor(color);
	}

	ID2D1SolidColorBrush* FontManager::FindColor(const Vec4& _color)
	{
		unsigned int	color = 0;
		unsigned char	r, g, b, a;
		r = (unsigned char)(_color.x * 255);
		g = (unsigned char)(_color.y * 255);
		b = (unsigned char)(_color.z * 255);
		a = (unsigned char)(_color.w * 255);

		color = a;
		color = (color << 8) | r;
		color = (color << 8) | g;
		color = (color << 8) | b;

		return FindColor(color);
	}

	ID2D1SolidColorBrush* FontManager::FindColor(UINT32 _color)
	{
		std::unordered_map<UINT32, ID2D1SolidColorBrush*>::iterator	iter = mColorMap.find(_color);

		if (iter == mColorMap.end())
		{
			return nullptr;
		}

		return iter->second;
	}

	UINT32 FontManager::CreateColorKey(float _r, float _g, float _b, float _a)
	{
		UINT32	color = 0;
		unsigned char	r1, g1, b1, a1;
		r1 = (unsigned char)(_r * 255);
		g1 = (unsigned char)(_g * 255);
		b1 = (unsigned char)(_b * 255);
		a1 = (unsigned char)(_a * 255);

		color = a1;
		color = (color << 8) | r1;
		color = (color << 8) | g1;
		color = (color << 8) | b1;

		return color;
	}

	UINT32 FontManager::CreateColorKey(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		unsigned int	color = 0;

		color = _a;
		color = (color << 8) | _r;
		color = (color << 8) | _g;
		color = (color << 8) | _b;

		return color;
	}

	UINT32 FontManager::CreateColorKey(const Vec4& _color)
	{
		unsigned int	color = 0;
		unsigned char	r, g, b, a;
		r = (unsigned char)(_color.x * 255);
		g = (unsigned char)(_color.y * 255);
		b = (unsigned char)(_color.z * 255);
		a = (unsigned char)(_color.w * 255);

		color = a;
		color = (color << 8) | r;
		color = (color << 8) | g;
		color = (color << 8) | b;

		return color;
	}

	IDWriteTextFormat* FontManager::FindTextFormat(const string& _name)
	{
		std::unordered_map<std::string, IDWriteTextFormat*>::iterator	iter = mFontMap.find(_name);

		if (iter == mFontMap.end())
			return nullptr;

		return iter->second;
	}

}
