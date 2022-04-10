#pragma once
#include <graphics/ofImage.h>

enum LutName {
	Arabica,
	Ava,
	Azrael,
	Bourbon,
	Byers,
	Chemical,
	Clayton,
	Clouseau,
	Cobi,
	Contrail,
	Cubicle,
	Django,
	Domingo,
	Faded,
	Folger,
	Fusion,
	Hyla,
	Korben,
	Lenox,
	Lucky,
	McKinnon,
	Milo,
	Neon,
	Paladin,
	Pasadena,
	Pitaya,
	Reeve,
	Remy,
	Sprocket,
	Teigen,
	Trent,
	Tweed,
	Vireo,
	Zed,
	Zeke
};

class Lut {
public:

	Lut(LutName name);
	ofColor getColor(int red, int green, int blue) const;
private:
	std::vector<ofColor> m_lut;
	int m_power = 0;

	std::string getFilename(LutName name);
};
