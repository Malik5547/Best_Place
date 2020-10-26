#include "comand.h"

namespace DebugMenu {

	Comand::Comand(Vector size, void (*comand)(Vector), const char* src, IDirect3DDevice9* device) {
		_width = size.x;
		_height = size.y;

		_comand = comand;
		//Load texture
		_texture = new Texture(src, device);

		_sprite = new Sprite(device, _texture);
	}

	void Comand::SetPos(Vector pos) {
		_pos = pos;
		_sprite->SetPos(_pos.x, _pos.y, _pos.x + _width, _pos.y + _height);

	}

	void Comand::Draw() {
		_sprite->Draw();
	}

	void Comand::Execute(Vector pos) {
		_comand(pos);	//Execute comand
	}

	Comand::~Comand() {
		delete _sprite;
		delete _texture;
	}
}