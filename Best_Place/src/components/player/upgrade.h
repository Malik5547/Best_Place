#pragma once

#include "../../render/data/sprite.h"

namespace PlayerSp {

#define UPGRADE_WIDTH	100
#define UPGRADE_HEIGHT	30
#define UPGRADE_DIST	10	//Distance betwen upgrades

#define UPGRADE_SELECT_SIZE	{1.5f, 1.1f}

	//Upgrade sprite
	class UpgradeSprite : public Sprite {
	public:
		UpgradeSprite(IDirect3DDevice9* device, Texture* texture); //Constructor

		virtual void DrawImpl(IDirect3DDevice9* device, VertexShader* vShader, PixelShader* pShader) override; //Draw implimentation
	};

	//Class of an upgrade for drawing and interacting 
	class Upgrade {
		UpgradeSprite* _sprite;
		Texture* _texture;
		Vector _pos;
		bool* _up_ptr;				//Pointer to upgrade state
		bool _selected = false;		//Is the upgrade selected now
	public:
		Upgrade(const char* src, bool* upgr_ptr, IDirect3DDevice9* device);

		void SetPos(Vector pos);		//Set position
		void Selected(bool val);		//Set selected state

		void Draw();

		void Activate();		//Activate upgrade

		void Release();

		~Upgrade();
	};

}