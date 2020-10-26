#pragma once

#include "upgrade.h"
#include "../../input/input.h"

namespace PlayerSp {

#define UPGRADE_LIST_SIZE	3


	//Player upgrades struct
	struct UpgradesStruct{
		bool jump_boots = false;
		bool super_strenght = false;
		bool shield = false;
		bool levitation = false;
	};

	class Upgrade_ListC {
	public:
		Upgrade_ListC(){}
		
		void SetPos(Vector pos);			//Set position
		void AddUpgrade(Upgrade* upg);		//Add upgrade

		void SetCurrent(unsigned int current);	//Set current selected upgrade
		void Update();						//Update list

		void Draw();		//Draw

		void Release();			//Release

		~Upgrade_ListC();

	private:
		void UpdatePos();				//Update positions aftec changing offset
		
		std::vector<Upgrade*>  upgrades;	//Upgrade list
		Vector _pos;						//Position
		float _height = 0.0f;						//Height of list
		unsigned int _offset = 0;					//Offset of upgrades when are drawed
		unsigned int _current = 0;					//Current selected upgrade
	};

	void InitUpgradeList(IDirect3DDevice9* device);						//Init upgrade list

	UpgradesStruct* GetUpgradeList();									//Get the bool list of upgrades

	void DrawUpgradeList(IDirect3DDevice9* device, PixelShader* pShader);	//Draw upgrade list

	void UpdateUpgradeList();					//Update list
}