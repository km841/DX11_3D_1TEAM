#pragma once
#include "Component.h"
namespace hm
{
	enum class TextRenderType
	{
		TextUI,
		Text2D,
		Text3D,
	};

	enum class TextAlignH
	{
		Left,
		Center,
		Right
	};

	enum class TextAlignV
	{
		Top,
		Mid,
		Bottom
	};

	class UIText :
		public Component
	{
	public:
		UIText();
		virtual ~UIText();
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void Initialize() override;
		virtual void Render() override;

	public:
		void SetRenderType(TextRenderType _eType);
		void SetTextCount(int _maxCount);
		void SetText(const wstring& _text);
		void AddText(const wstring& _text);

		void SetFont(const std::string& _name, const wstring& _fontName,
			int _weight, int _style, int _stretch, float _size,
			const TCHAR* _pLocalName);

		void SetFont(const string& _name);
		void SetSize(float _size);
		void SetAlignH(TextAlignH _eAlign);
		void SetAlignV(TextAlignV _eAlign);
		void Shadow(bool _bShadow);
		void SetOffset(const Vec3& _offset);
		void SetShadowOffset(const Vec3& _shadowOffset);
		void SetShadowColor(float _r, float _g, float _b, float _a);
		void SetShadowColor(unsigned char _r, unsigned char _g,
			unsigned char _b, unsigned char _a);
		void SetShadowColor(const Vec4& _color);
		void SetShadowColor(UINT32 _color);
		void AlphaBlend(bool _bAlpha);
		void ShadowAlphaBlend(bool _bAlpha);
		void SetOpacity(float _opacity);
		void SetShadowOpacity(float _opacity);
		void SetColor(float _r, float _g, float _b, float _a);
		void SetColor(unsigned char _r, unsigned char _g,
			unsigned char _b, unsigned char _a);
		void SetColor(const Vec4& _color);
		void SetColor(UINT32 _color);
		void SetRenderArea(float _l, float _t, float _r, float _b);

	private:
		void CreateTextLayout();

	private:
		IDWriteTextFormat* mpTextFormat;
		IDWriteTextLayout* mpTextLayout;

		ID2D1SolidColorBrush* mpColor;
		ID2D1SolidColorBrush* mpShadowColor; // 그림자용

		// 텍스트 오프셋 (YDJ)
		Vec3 mOffset;

		// 그림자 사용여부
		bool	mbShadow;

		// 텍스트
		wstring mText;

		// 텍스트 총 길이
		int mMaxCount;

		// 폰트 명
		wstring mFont;

		// 폰트 크기
		float mSize;

		// 가로 정렬 기준
		TextAlignH meAlignH;
		// 세로 정렬 기준
		TextAlignV meAlignV;

		// 랜더 타입(2D, 3D, UI) 
		TextRenderType meRenderType;

		// 알파 적용 여부
		bool mbAlpha;
		// 그림자 알파 적용 여부
		bool mbAlphaShadow;

		// 투명도
		float mOpacity;

		// 그림자 투명도
		float mShadowOpacity;

		// 폰트 색상
		Vec4 mColor;
		// 그림자 색상
		Vec4 mShadowColor;

		// 그림자 오프셋
		Vec3 mShadowOffset;

		// 폰트를 그려낼 영역
		D2D1_RECT_F mRenderArea;
	};
}


