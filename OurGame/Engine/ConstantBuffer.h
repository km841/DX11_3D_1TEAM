#pragma once

namespace hm
{
	/*
	* ConstantBuffer를 관리하는 클래스
	* Engine에서는 이 클래스의 인스턴스를 배열로 가지고 있고,
	* ConstantBufferType이라는 Enum값으로 접근해서 Transform, Material, Light와 같은 종류에 접근할 수 있다.
	*/
	class ConstantBuffer
	{
	public:
		ConstantBuffer();
		~ConstantBuffer();

	public:
		/* ConstantBuffer를 생성하는 함수
		* _eReg : 몇 번 레지스터를 사용할 것인지 결정하는 인자
		* _size : 사용할 구조체의 크기
		*/
		void Create(RegisterCBV _eReg, int _size);

		/*mpBuffer에 인자로 전달 받은 데이터를 삽입하는 함수
		* _pData : 버퍼에 담길 값 (실제로는 ConstantBufferType에 맞는 구조체의 포인터가 들어감)
		* _size : _pData의 크기
		*/
		void PushData(void* _pData, int _size);

		// mpBuffer에 담긴 값을 실제로 GPU에 매핑하는 함수
		void Mapping();

	private:
		RegisterCBV				 meReg;
		ComPtr<ID3D11Buffer>	 mpBuffer;

	};
}

