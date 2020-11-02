#include "simpleAI.h"

namespace SimpleAI {

	void Handle(Enemy* enemy) {
		Vector platformPos, platformSize;

		if (enemy->GetPlatform()->GetType() != ObjType::NOTHING) {

			platformPos = enemy->GetPlatform()->GetPos();
			platformSize = enemy->GetPlatform()->GetSize();

			if (enemy->GetDir() == ENEMY_DIR_RIGHT) {
				if (enemy->GetPosition().x + enemy->GetSize().x >= platformPos.x + platformSize.x) {
					enemy->SetDir(ENEMY_DIR_LEFT);
				}
			}
			else {
				if (enemy->GetPosition().x <= platformPos.x) {
					enemy->SetDir(ENEMY_DIR_RIGHT);
				}
			}

		}

	}

}