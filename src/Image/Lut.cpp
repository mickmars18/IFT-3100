#include "Lut.h"

Lut::Lut(LutName name) {
	ofFile file;
	file.open(ofToDataPath(getFilename(name)), ofFile::ReadOnly, false);
	ofBuffer buff = file.readToBuffer();

	std::string line;
	buff.getFirstLine();
	while (buff.getNextLine() != "#LUT data points" && !buff.isLastLine()) {
		line = buff.getNextLine();
	}

	line = buff.getNextLine();


	while (!buff.isLastLine()) {
		int red = round(std::stof(line.substr(0, 8)) * 255.0f);
		int green = round(std::stof(line.substr(9, 8)) * 255.0f);
		int blue = round(std::stof(line.substr(18, 8)) * 255.0f);

		m_lut.push_back(ofColor(red, green, blue));

		line = buff.getNextLine();
	}
}

ofColor Lut::getColor(int red, int green, int blue) const {
	int r = round((float)red / 255.0f * 31.0f);
	int g = round((float)green / 255.0f * 31.0f);
	int b = round((float)blue / 255.0f * 31.0f);

	return m_lut[r + g * 32 + b * 1024];
}

std::string Lut::getFilename(LutName name) {
	switch (name)
	{
	case Arabica:
		return "LUTs/Arabica 12.CUBE";
	case Ava:
		return "LUTs/Ava 614.CUBE";
	case Azrael:
		return "LUTs/Azrael 93.CUBE";
	case Bourbon:
		return "LUTs/Bourbon 64.CUBE";
	case Byers:
		return "LUTs/Byers 11.CUBE";
	case Chemical:
		return "LUTs/Chemical 168.CUBE";
	case Clayton:
		return "LUTs/Clayton 33.CUBE";
	case Clouseau:
		return "LUTs/Clouseau 54.CUBE";
	case Cobi:
		return "LUTs/Cobi 3.CUBE";
	case Contrail:
		return "LUTs/Contrail 35.CUBE";
	case Cubicle:
		return "LUTs/Cubicle 99.CUBE";
	case Django:
		return "LUTs/Django 25.CUBE";
	case Domingo:
		return "LUTs/Domingo 145.CUBE";
	case Faded:
		return "LUTs/Faded 47.CUBE";
	case Folger:
		return "LUTs/Folger 50.CUBE";
	case Fusion:
		return "LUTs/Fusion 88.CUBE";
	case Hyla:
		return "LUTs/Hyla 68.CUBE";
	case Korben:
		return "LUTs/Korben 214.CUBE";
	case Lenox:
		return "LUTs/Lenox 340.CUBE";
	case Lucky:
		return "LUTs/Lucky 64.CUBE";
	case McKinnon:
		return "LUTs/McKinnon 75.CUBE";
	case Milo:
		return "LUTs/Milo 5.CUBE";
	case Neon:
		return "LUTs/Neon 770.CUBE";
	case Paladin:
		return "LUTs/Paladin 1875.CUBE";
	case Pasadena:
		return "LUTs/Pasadena 21.CUBE";
	case Pitaya:
		return "LUTs/Pitaya 15.CUBE";
	case Reeve:
		return "LUTs/Reeve 38.CUBE";
	case Remy:
		return "LUTs/Remy 24.CUBE";
	case Sprocket:
		return "LUTs/Sprocket 231.CUBE";
	case Teigen:
		return "LUTs/Teigen 28.CUBE";
	case Trent:
		return "LUTs/Trent 18.CUBE";
	case Tweed:
		return "LUTs/Tweed 71.CUBE";
	case Vireo:
		return "LUTs/Vireo 37.CUBE";
	case Zed:
		return "LUTs/Zed 32.CUBE";
	case Zeke:
		return "LUTs/Zeke 39.CUBE";
	default:
		return "";
	}
}



