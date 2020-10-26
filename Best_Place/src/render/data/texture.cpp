#include "texture.h"

Texture::Texture(const char* src, IDirect3DDevice9* device) {
	//Try to load the texture
	if (!Load(src, device)) {
		//If failed, load missiong texture
		Load(MISSING_TEXTURE, device);
	}
}

void Texture::Release() {
	if (_texture != nullptr) {
		//Release texture
		_texture->Release();
		_texture = nullptr;
	}
}

Texture::~Texture() {
	if (_texture != nullptr) {
		//Release all data
		Release();
	}
}

bool Texture::Load(const char* src, IDirect3DDevice9* device) {

	//Create new texture
	if (FAILED(D3DXCreateTextureFromFile(device, src, &_texture)))
		return false;

	//Get width and heigh
	D3DXIMAGE_INFO desc;
	D3DXGetImageInfoFromFile(src, &desc);
	_width = desc.Width;
	_height = desc.Height;

	return true;
}