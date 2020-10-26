#include "background.h"
#include "../../render/render.h"

Background::Background(const char* src, IDirect3DDevice9* device) {
	//Load texture
	bkg_texture = new Texture(src, device);

	//Create sprite
	bkg_sprite = new Background_Sprite(device, -1.0f, -1.0f, 1.0f, 1.0f, bkg_texture);
}

void Background::SetFollow(MobileObject* obj) {
	bkg_sprite->SetFollow(obj);
}

void Background::Draw() {
	bkg_sprite->Draw();
}

void Background::Release() {
	if (bkg_sprite != nullptr)
		delete bkg_sprite;
	if (bkg_texture != nullptr)
		delete bkg_texture;
}

Background_Sprite::Background_Sprite(IDirect3DDevice9* device, float x1, float y1, float x2, float y2, Texture* texture) :
	Sprite(device, x1, y1, x2, y2, texture) {}

void Background_Sprite::SetFollow(MobileObject* obj) {
	follow_obj = obj;
}

void Background_Sprite::UpdateUV(Camera* cam) {

	if (follow_obj != nullptr) {
		//Move background
		float y = -(follow_obj->GetMaxHeight() / 2) / cam->GetDist();

		SetUV(0.0f, y, 1.0f, y - 1.0f);
	}
}

void Background_Sprite::Draw() {
	BackgroundPush(this);
}

void Background_Sprite::DrawImpl(IDirect3DDevice9* device, VertexShader* vShader, PixelShader* pShader, Camera* cam) {
	//Update UV
	UpdateUV(cam);

	//Set raw drawing and draw background
	if (vShader->SetVertexProc(device, VPROC_RAW)) {
		//Set raw drawing
		Sprite::DrawImpl(device, vShader, pShader);
		vShader->SetVertexProc(device, VPROC_DEF);
	}
}