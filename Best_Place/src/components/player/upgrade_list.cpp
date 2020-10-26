#include "upgrade_list.h"

namespace PlayerSp {

	//Global upgrade list
	Upgrade_ListC* upgradeList;

	//Player upgrades
	UpgradesStruct upgrades;
	
	void InitUpgradeList(IDirect3DDevice9* device) {
		upgradeList = new Upgrade_ListC;

		Upgrade* up1 = new Upgrade("src/data/up1.png", &(upgrades.jump_boots), device);
		Upgrade* up2 = new Upgrade("src/data/up2.png", &(upgrades.levitation), device);
		Upgrade* up3 = new Upgrade("src/data/up3.png", &(upgrades.shield), device);
		Upgrade* up4 = new Upgrade("src/data/up4.png", &(upgrades.super_strenght), device);
		Upgrade* up5 = new Upgrade("src/data/up5.png", &(upgrades.super_strenght), device);

		upgradeList->AddUpgrade(up1);
		upgradeList->AddUpgrade(up2);
		upgradeList->AddUpgrade(up3);
		upgradeList->AddUpgrade(up4);
		upgradeList->AddUpgrade(up5);

		upgradeList->SetPos({ 100, 200 });

		upgradeList->SetCurrent(0);
	}

	UpgradesStruct* GetUpgradeList() {
		return &upgrades;
	}

	void DrawUpgradeList(IDirect3DDevice9* device, PixelShader* pShader) {
		upgradeList->Draw();
	}

	void UpdateUpgradeList(){
		upgradeList->Update();
		upgradeList->Draw();
	}

	void Upgrade_ListC::SetPos(Vector pos){
		_pos = pos;

		for (unsigned int i = 0; i < upgrades.size(); i++) {
			upgrades[i]->SetPos({ _pos.x, _pos.y + _height - (UPGRADE_HEIGHT + UPGRADE_DIST)* i });
		}
	}

	void Upgrade_ListC::AddUpgrade(Upgrade* up) {
		upgradeList->upgrades.push_back(up);

		_height += UPGRADE_HEIGHT;
	}

	void Upgrade_ListC::SetCurrent(unsigned int current) {
		//Clean select from last upgrade
		upgrades[_current]->Selected(false);
		//Set select for current upgrade;
		upgrades[current]->Selected(true);
		_current = current;
	}

	void Upgrade_ListC::Update() {
		if (IS_HOLDED(Input::W)) {
			if (_current > 0) {
				//Change current selected upgrade
				SetCurrent(_current - 1);
				if (_offset > 0 && (_offset > _current - (unsigned int)(UPGRADE_LIST_SIZE / 2))) {
					//Update offset and positions of upgrades
					_offset--;
					UpdatePos();
				}
			}
		}else if (IS_HOLDED(Input::S)) {
			if (_current < upgrades.size() - 1) {
				//Change current selected upgrade
				SetCurrent(_current + 1);
				if (_offset <= upgrades.size() - UPGRADE_LIST_SIZE - 1 && (_offset < _current - (unsigned int)(UPGRADE_LIST_SIZE / 2))) {
					//Update offset and positions of upgrades
					_offset++;
					UpdatePos();
				}
			}
		}
	}

	void Upgrade_ListC::UpdatePos() {
		for (unsigned int i = _offset; i < _offset + UPGRADE_LIST_SIZE; i++) {
			upgrades[i]->SetPos({ _pos.x, _pos.y + _height - (UPGRADE_HEIGHT + UPGRADE_DIST) * (i - _offset) });
		}
	}

	void Upgrade_ListC::Draw() {
		for (unsigned int i = _offset; i < _offset + UPGRADE_LIST_SIZE; i++) {
			upgrades[i]->Draw();
		}
	}

	void Upgrade_ListC::Release() {
		for (unsigned int i = 0; i < upgrades.size(); i++) {
			upgrades[i]->Release();
			delete upgrades[i];
		}
	}

	Upgrade_ListC::~Upgrade_ListC() {
		Release();
	}

}