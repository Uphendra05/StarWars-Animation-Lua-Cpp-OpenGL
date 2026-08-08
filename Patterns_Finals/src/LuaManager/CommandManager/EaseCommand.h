#pragma once

#include "../../Utilities/EasingHelper.h"

class EaseCommand
{
public:
	float easeInTime = 0;
	float easeOutTime = 0;

	float easeInRatio = 0;
	float easeOutRatio = 0;

	float easeInStart = 0;
	float easeOutStart = 0;

	Ease_Mode easeInMode;
	Ease_Mode easeOutMode;

};

