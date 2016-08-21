#pragma once

enum class FadeTarget {
	GAIN,
	PITCH
};

struct FadeData {

	FadeData() {};
	FadeData(FadeTarget fadeTarget, float start, float target, float time): fadeTarget(fadeTarget), target(target), time(time), t(0), slope((target - start) / time)  {}

	FadeTarget fadeTarget;
	float slope;
	float target;
	float time;
	float t;
};