#include "pch.h"
#include "UIText.h"
#include "GameObject.h"
#include "FontManager.h"
#include "Engine.h"
#include "Transform.h"
#include "SceneManager.h"
#include "Camera.h"

namespace hm
{
	UIText::UIText()
		: Component(ComponentType::UI)
		, mbShadow(false)
		, mSize(20.f)
		, meAlignH(TextAlignH::Center)
		, meAlignV(TextAlignV::Top)
		, meRenderType(TextRenderType::TextUI)
		, mbAlpha(false)
		, mbAlphaShadow(false)
		, mOpacity(1.f)
		, mShadowOpacity(1.f)
	{
		mFont = L"맑은 고딕";
		mFont.resize(64);

		mColor = Vec4(1.f, 1.f, 1.f, 1.f);
		mShadowColor = Vec4(0.f, 0.f, 0.f, 1.f);

		mpTextFormat = GET_SINGLE(FontManager)->FindTextFormat("FreshGothic");
		mpTextLayout = GET_SINGLE(FontManager)->CreateTextLayout(L"", mpTextFormat, 100.f, 100.f);

		mpColor = GET_SINGLE(FontManager)->CreateColor(mColor);
		mpShadowColor = GET_SINGLE(FontManager)->CreateColor(mShadowColor);

		mMaxCount = 256;
		mText.resize(mMaxCount);
		mText += L"Text";

		mRenderArea = {};
	}
	UIText::~UIText()
	{
		mpTextLayout->Release();
	}
	Component* UIText::Clone(GameObject* _pGameObject)
	{
		UIText* pUIText = _pGameObject->AddComponent(new UIText);
		return pUIText;
	}
	void UIText::Initialize()
	{
	}
	void UIText::Render()
	{
		// 그리기 호출은 BeginDraw 호출과 EndDraw 호출 사이에서만 발행 될 수 있습니다.
		RENDERTARGET_2D->BeginDraw();

		Vec3 pos = GetTransform()->GetPosition();

		float height = mRenderArea.bottom - mRenderArea.top;

		// UI가 아닌 월드카메라에 영향받는 타입인 경우
		// 월드 카메라값을 적용해주어야 한다.
		if (meRenderType != TextRenderType::TextUI)
		{
			// 월드 카메라 Transform을 얻어온다.
			Transform* pCameraTr = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetTransform();

			// 해당 오브젝트는 카메라 값만큼 빼서 클라이언트 영역 내에 존재하는것처럼 위장시킨다.
			pos -= pCameraTr->GetPosition();
		}

		// 폰트에 그림자가 존재하는 경우
		if (true == mbShadow)
		{
			// 그림자는 보통 현재 폰트의 오프셋 값만큼 떨어져서
			// 마치 그림자처럼 보이게끔 하는것이므로...
			Vec3 shadowPos = pos + mShadowOffset;

			// 그림자에 알파값이 존재하는 경우
			if (true == mbAlphaShadow)
			{
				// 해당 투명도 만큼 설정해준다 (0 ~ 1)
				mpShadowColor->SetOpacity(mShadowOpacity);
			}
			else
			{
				// 불투명
				mpShadowColor->SetOpacity(1.f);
			}

			// 그림자가 현재 폰트보다 위로 가도록
			// 해당 구문이 없으면 현재 폰트보다 아래로 갈 것이다.
			shadowPos.y = RESOLUTION.y - shadowPos.y - height + RESOLUTION.y / 2.f - 20.f;
			// 그림자를 그린다.
			// 1. 그림자 출력 위치
			// 2. 그림자 레이아웃
			// 3. 그림자 컬러
			RENDERTARGET_2D->DrawTextLayout(D2D1::Point2F(shadowPos.x, shadowPos.y),
				mpTextLayout, mpShadowColor);
		}

		// 폰트에 알파가 존재하는 경우
		if (mbAlpha)
		{
			// 알파값 적용
			mpColor->SetOpacity(mOpacity);
		}
		else
		{
			// 불투명
			mpColor->SetOpacity(1.f);
		}
		pos.y = RESOLUTION.y - pos.y - height + RESOLUTION.y / 2.f - 20.f;

		// 텍스트를 그린다.
		// 1. 텍스트 출력 위치
		// 2. 텍스트 레이아웃
		// 3. 텍스트 컬러
		RENDERTARGET_2D->DrawTextLayout(D2D1::Point2F(pos.x, pos.y),
			mpTextLayout, mpColor);

		RENDERTARGET_2D->EndDraw();
	}
	void UIText::SetRenderType(TextRenderType _eType)
	{
		meRenderType = _eType;
	}
	void UIText::SetTextCount(int _maxCount)
	{
		if (_maxCount < mText.size())
			return;

		mText.resize(_maxCount);
	}
	void UIText::SetText(const wstring& _text)
	{
		mText = _text;
	}
	void UIText::AddText(const wstring& _text)
	{
		mText += _text;
	}
	void UIText::SetFont(const std::string& _name, const wstring& _fontName, int _weight, int _style, int _stretch, float _size, const TCHAR* _pLocalName)
	{
		mSize = _size;
		mFont = _fontName;

		GET_SINGLE(FontManager)->CreateTextFormat(_name, _fontName.c_str(), _weight, _style, _stretch, _size, _pLocalName);

		mpTextFormat = GET_SINGLE(FontManager)->FindTextFormat(_name);
		CreateTextLayout();
	}
	void UIText::SetFont(const string& _name)
	{
		mpTextFormat = GET_SINGLE(FontManager)->FindTextFormat(_name);
		CreateTextLayout();
	}
	void UIText::SetSize(float _size)
	{
		mSize = _size;
		CreateTextLayout();
	}
	void UIText::SetAlignH(TextAlignH _eAlign)
	{
		meAlignH = _eAlign;

		if (nullptr == mpTextLayout)
			CreateTextLayout();

		switch (_eAlign)
		{
		case hm::TextAlignH::Left:
			mpTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			break;
		case hm::TextAlignH::Center:
			mpTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			break;
		case hm::TextAlignH::Right:
			mpTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			break;
		}
	}
	void UIText::SetAlignV(TextAlignV _eAlign)
	{
		meAlignV = _eAlign;

		if (nullptr == mpTextLayout)
			CreateTextLayout();

		switch (_eAlign)
		{
		case hm::TextAlignV::Top:
			mpTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			break;
		case hm::TextAlignV::Mid:
			mpTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			break;
		case hm::TextAlignV::Bottom:
			mpTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
			break;
		}
	}
	void UIText::Shadow(bool _bShadow)
	{
		mbShadow = _bShadow;
	}
	void UIText::SetOffset(const Vec3& _offset)
	{
		mOffset = _offset;
	}
	void UIText::SetShadowOffset(const Vec3& _shadowOffset)
	{
		mShadowOffset = _shadowOffset;
	}
	void UIText::SetShadowColor(float _r, float _g, float _b, float _a)
	{
		mShadowColor = Vec4(_r, _g, _b, _a);
		mpShadowColor = GET_SINGLE(FontManager)->CreateColor(_r, _g, _b, _a);
	}
	void UIText::SetShadowColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		mShadowColor = Vec4(_r / 255.f, _g / 255.f, _b / 255.f, _a / 255.f);

		// 포인터로 가지는 그림자 컬러 값
		mpShadowColor = GET_SINGLE(FontManager)->CreateColor(_r, _g, _b, _a);
	}
	void UIText::SetShadowColor(const Vec4& _color)
	{
		mShadowColor = _color;
		mpShadowColor = GET_SINGLE(FontManager)->CreateColor(mShadowColor);
	}
	void UIText::SetShadowColor(UINT32 _color)
	{
		mShadowColor.z = (_color & 0x000000ff) / 255.f;
		mShadowColor.y = ((_color >> 8) & 0x000000ff) / 255.f;
		mShadowColor.x = ((_color >> 16) & 0x000000ff) / 255.f;
		mShadowColor.w = ((_color >> 24) & 0x000000ff) / 255.f;

		mpShadowColor = GET_SINGLE(FontManager)->CreateColor(_color);
	}
	void UIText::AlphaBlend(bool _bAlpha)
	{
		mbAlpha = _bAlpha;
	}
	void UIText::ShadowAlphaBlend(bool _bAlpha)
	{
		mbAlphaShadow = _bAlpha;
	}
	void UIText::SetOpacity(float _opacity)
	{
		mOpacity = _opacity;
	}
	void UIText::SetShadowOpacity(float _opacity)
	{
		mShadowOpacity = _opacity;
	}
	void UIText::SetColor(float _r, float _g, float _b, float _a)
	{
		mColor = Vec4(_r, _g, _b, _a);
		mpColor = GET_SINGLE(FontManager)->CreateColor(_r, _g, _b, _a);
	}
	void UIText::SetColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		mColor = Vec4(_r / 255.f, _g / 255.f, _b / 255.f, _a / 255.f);
		mpColor = GET_SINGLE(FontManager)->CreateColor(_r, _g, _b, _a);
	}
	void UIText::SetColor(const Vec4& _color)
	{
		mColor = _color;
		mpColor = GET_SINGLE(FontManager)->CreateColor(mColor);
	}
	void UIText::SetColor(UINT32 _color)
	{
		mColor.z = (_color & 0x000000ff) / 255.f;
		mColor.y = ((_color >> 8) & 0x000000ff) / 255.f;
		mColor.x = ((_color >> 16) & 0x000000ff) / 255.f;
		mColor.w = ((_color >> 24) & 0x000000ff) / 255.f;

		mpColor = GET_SINGLE(FontManager)->CreateColor(_color);
	}
	void UIText::SetRenderArea(float _left, float _top, float _right, float _bottom)
	{
		mRenderArea = D2D1::RectF(_left, RESOLUTION.y - _bottom,
			_right, RESOLUTION.y - _top);

		CreateTextLayout();
	}
	void UIText::CreateTextLayout()
	{
		// 현재 설정된 텍스트 폰트가 존재하지 않은 경우
		if (!mpTextFormat)
		{
			return;
		}
		AssertEx(mpTextFormat, L"UIText::CreateTextLayout() - 텍스트 폰트가 설정되지 않음");
		
		if (nullptr != mpTextLayout)
		{
			mpTextLayout->Release();
			mpTextLayout = nullptr;
		}

		// 텍스트 레이아웃 생성
		// 1. 텍스트
		// 2. 텍스트 포맷
		// 3. 가로 너비
		// 4. 세로 너비
		mpTextLayout = GET_SINGLE(FontManager)->CreateTextLayout(
			mText.c_str(), mpTextFormat, mRenderArea.right - mRenderArea.left,
			mRenderArea.bottom - mRenderArea.top);

		// 텍스트 길이에 대한 설정 (0번째부터 해당 텍스트 전체 길이까지)
		DWRITE_TEXT_RANGE	range;
		range.startPosition = 0;
		range.length = static_cast<UINT32>(mText.size());

		// 레이아웃에 텍스트길이 및 텍스트 사이즈 지정
		mpTextLayout->SetFontSize(mSize, range);
	}
}

