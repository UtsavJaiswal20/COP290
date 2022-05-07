#pragma once

struct Animated
{
	int index;
	int frames;
	int delay;

	Animated() {}
	Animated(int id, int nf, int nd) {
		index = id;
		frames = nf;
		delay = nd;

	}
};