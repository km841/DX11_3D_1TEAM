#pragma once
namespace hm
{
	/*
	* 클라이언트의 중추적인 역할을 하는 클래스
	* 엔진의 생명주기 함수들을 사용해서 렌더링한다
	*/
	class Application
	{
	public:
		/*
		* 엔진을 초기화를 위한 함수
		*/
		void Initialize(const WindowInfo& _windowInfo);
		void Start();
		void Update();
		void Destroy();

	public:

	};
}


