#pragma once
#include "../Models/Model.h"
#include "../Helper/MkImporter.h"

class PBR_Model : public Model {
public:
	PBR_Model(const std::string& filename);
	PBR_Model(const PBR_Model& model);

	std::string getClassName() override;
	void update() override;
	void draw(const Window& window, const Camera& camera) override;
};
