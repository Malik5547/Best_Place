#include "upgrade.h"

namespace PlayerSp {

	Upgrade::Upgrade(const char* src, bool* upgr_ptr, IDirect3DDevice9* device) {
		//Load texture
		_texture = new Texture(src, device);
		//Create sprite
		_sprite = new UpgradeSprite(device, _texture);

		_up_ptr = upgr_ptr;
	}

	void Upgrade::SetPos(Vector pos) {
		_pos = pos;
		_sprite->SetPos(pos.x, pos.y, pos.x + UPGRADE_WIDTH, pos.y + UPGRADE_HEIGHT);
	}

	void Upgrade::Selected(bool val) {
		_selected = val;
		
		if (val)
			_sprite->SetSize(UPGRADE_SELECT_SIZE);
		else
			_sprite->SetSize({ 1.0f, 1.0f });
	}

	void Upgrade::Draw() {
		_sprite->Draw();
	}

	void Upgrade::Activate() {
		*_up_ptr = true;
	}

	void Upgrade::Release() {
		if (_sprite != nullptr) {
			delete _sprite;
			delete _texture;
			_sprite = nullptr;
			_texture = nullptr;
		}
	}

	Upgrade::~Upgrade() {
		Release();
	}

	UpgradeSprite::UpgradeSprite(IDirect3DDevice9* device, Texture* texture) :
		Sprite(device, texture) {}

	void UpgradeSprite::DrawImpl(IDirect3DDevice9* device, VertexShader* vShader, PixelShader* pShader) {
		//Set raw drawing
		if (vShader->SetVertexProc(device, VPROC_WND)) {
			Sprite::DrawImpl(device, vShader, pShader);
			vShader->SetVertexProc(device, VPROC_DEF);
		}
	}

}