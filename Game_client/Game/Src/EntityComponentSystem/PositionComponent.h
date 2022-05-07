#pragma once

#include "Components.h"
#include "../Vector2.h"

class PositionComponent : public Component
{
public:
	Vector2 pos;
	Vector2 movement;
	int score, popularity, energy,  hygiene;
	double money;
	int spending = 0;
	int speed = 5;
	int height = 32;
	int width = 32;
	int scale = 1;

	PositionComponent() {
		pos.Zero();
		score = popularity = 0;
		energy = money = hygiene = 100;
	}
	PositionComponent(int scalee) {
		pos.x = 200*2;
		pos.y = 448*4;
		scale = scalee;
		score = popularity = 0;
		energy = money = hygiene = 100;
	}
	PositionComponent(float x, float y) {
		pos.x = x;
		pos.y = y;
		score = popularity = 0;
		energy = money = hygiene = 100;
	}
	PositionComponent(float x, float y, int scalee) {
		pos.x = x;
		pos.y = y;
		scale = scalee;
		score = popularity = 0;
		energy = money = hygiene = 100;
	}
	PositionComponent(float x, float y, int h, int w, int scalee) {
		pos.x = x;
		pos.y = y;
		height = h;
		width = w;
		scale = scalee;
		score = popularity = 0;
		energy = money = hygiene = 100;
	}
	
	void initialize() override {
		movement.Zero();
	}

	void update() override {
		pos.x += movement.x * speed;
		pos.y += movement.y * speed;
		if (speed == 15) {
			money -= 0.0025;
		}
		if (money <= 0) {
			money = 0;
			speed = 5;
		}
	}
};