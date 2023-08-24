#pragma once

namespace hm
{
	class Material;
	class Texture;
	class Mesh;
	class ImageFilter
	{
	public:
		ImageFilter(shared_ptr<Material> _pMaterial, UINT _width, UINT _height);
		virtual ~ImageFilter() = default;

		virtual void Render();

		void SetTexture(shared_ptr<Texture> _pTexture) { mpTexture = _pTexture; }
		shared_ptr<Texture> GetTexture() { return mpTexture; }
		void SetSRV(int _index, shared_ptr<Texture> _pTexture);

	protected:
		UINT mWidth;
		UINT mHeight;
		D3D11_VIEWPORT mViewport;
		shared_ptr<Texture> mpTexture;
		shared_ptr<Texture> mpDepthTexture;
		shared_ptr<Material> mpMaterial;
		shared_ptr<Mesh> mpMesh;
	};
}


