#pragma once
#include <cmath>  

static class ColorSpace {
public:
	static float* RGBtoHSB(int p_red, int p_green, int p_blue) {
		static int sortedValues[3];
		static float result[3];

		float red = (float)p_red;
		float green = (float)p_green;
		float blue = (float)p_blue;

		sortedValues[0] = red;
		sortedValues[1] = green;
		sortedValues[2] = blue;
		std::sort(sortedValues, sortedValues + 3);

		float max = sortedValues[2];
		float min = sortedValues[0];
		float delta = max - min;

		float hue;
		if (delta == 0.0f)
			hue = 0.0f;
		else if (max == red)
			hue = ((green - blue) / delta) * 60.0f;
		else if (max == green)
			hue = ((blue - red) / delta + 2.0f) * 60.0f;
		else if (max == blue)
			hue = ((red - green) / delta + 4.0f) * 60.0f;
		else
			std::cerr << "ColorSpace::RGBtoHSB : Max not found" << std::endl;

		if (hue < 0) {
			hue += 360.0f;
		}

		float saturation;
		if (max == 0.0f)
			saturation = 0.0f;
		else {
			saturation = delta / max;
		}

		float brightness = max / 255.0f;

		result[0] = hue;
		result[1] = saturation;
		result[2] = brightness;

		return result;
	}

	static int* HSBtoRGB(float hue, float saturation, float value) {
		float c = value * saturation;
		float x = c * (1 - std::abs(fmod(hue / 60.0f, 2.0f) - 1));
		float m = value - c;

		static float temp[3];
		if (hue >= 0 && hue < 60) {
			temp[0] = c;
			temp[1] = x;
			temp[2] = 0.0f;
		}
		else if (hue >= 60 && hue < 120) {
			temp[0] = x;
			temp[1] = c;
			temp[2] = 0.0f;
		}
		else if (hue >= 120 && hue < 180) {
			temp[0] = 0.0f;
			temp[1] = c;
			temp[2] = x;
		}
		else if (hue >= 180 && hue < 240) {
			temp[0] = 0.0f;
			temp[1] = x;
			temp[2] = c;
		}
		else if (hue >= 240 && hue < 300) {
			temp[0] = x;
			temp[1] = 0.0f;
			temp[2] = c;
		}
		else if (hue >= 300 && hue <= 360) {
			temp[0] = c;
			temp[1] = 0.0f;
			temp[2] = x;
		}
		else
			std::cerr << "ColorSpace::HSBtoRGB : hue value is not valid : hue = " << hue << std::endl;

		static int result[3];
		result[0] = int((temp[0] + m) * 255.0f);
		result[1] = int((temp[1] + m) * 255.0f);
		result[2] = int((temp[2] + m) * 255.0f);
		return result;
			
	}
};
