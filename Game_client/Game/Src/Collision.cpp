#include "Collision.h"
#include "EntityComponentSystem/Collider.h"

bool Collision::iscollision(const SDL_Rect &ra, const SDL_Rect &rb) {
	if ((ra.x + ra.w >= rb.x) && (rb.x + rb.w >= ra.x) && (ra.y + ra.h >= rb.y) && (rb.y + rb.h >= ra.y)) {
		return true;
	}
	return false;
}
bool Collision::iscollision(const Collider& colA, const Collider& colB) {
	if (iscollision(colA.wall, colB.wall)) {
		return true;
	}
	return false;
}