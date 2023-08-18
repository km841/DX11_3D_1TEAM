#pragma once
namespace hm
{
	class FontManager
	{
		DECLARE_SINGLE(FontManager);

	public:
		void Initialize();
		void CreateTextFormat(const string& _name, const TCHAR* _pFontName,
			int _weight, int _style, int _stretch, float _size,
			const TCHAR* _pLocalName);

		ID2D1SolidColorBrush* CreateColor(float _r, float _g, float _b, float _a);
		ID2D1SolidColorBrush* CreateColor(unsigned char _r, unsigned char _g, unsigned char _b,
			unsigned char _a);
		ID2D1SolidColorBrush* CreateColor(const Vec4& _color);
		ID2D1SolidColorBrush* CreateColor(UINT32 _color);
		IDWriteTextLayout* CreateTextLayout(const TCHAR* _pText,
			IDWriteTextFormat* _pFormat, float _width, float _height);
		IDWriteTextLayout* CreateTextLayout(const TCHAR* _pText,
			const string& _fontKey, float _width, float _height);

		ID2D1SolidColorBrush* FindColor(float _r, float _g, float _b, float _a);
		ID2D1SolidColorBrush* FindColor(unsigned char _r, unsigned char _g, unsigned char _b,
			unsigned char _a);
		ID2D1SolidColorBrush* FindColor(const Vec4& _color);
		ID2D1SolidColorBrush* FindColor(UINT32 _color);

		UINT32 CreateColorKey(float _r, float _g, float _b, float _a);
		UINT32 CreateColorKey(unsigned char _r, unsigned char _g, unsigned char _b,
			unsigned char _a);
		UINT32 CreateColorKey(const Vec4& _color);

		IDWriteTextFormat* FindTextFormat(const string& _name);

	private:
		IDWriteFactory* mpWriteFactory;
		std::unordered_map<string, IDWriteTextFormat*> mFontMap;
		std::unordered_map<UINT32, ID2D1SolidColorBrush*> mColorMap;
	};
}


