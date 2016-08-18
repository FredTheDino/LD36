#pragma once

enum class FadeTarget {
	GAIN,
	PITCH
};

struct FadeData {

	FadeData() {};
	FadeData(FadeTarget fadeTarget, float target, float time): fadeTarget(fadeTarget), target(target), time(time), t(0) {}

	FadeTarget fadeTarget;
	float target;
	float time;
	float t;
};