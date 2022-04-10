#include "LightsController.h"

LightsController::LightsController() {
}

void LightsController::addLight(Light* light) {
    if (light->getMode() == LightMode::Ambient)
        addAmbientLight(light);
    else if (light->getMode() == LightMode::Directional)
        addDirectionalLight(light);
    else if (light->getMode() == LightMode::Point)
        addPointLight(light);
    else if (light->getMode() == LightMode::Spot)
        addSpotLight(light);
}

void LightsController::removeLight(Light* light) {
    if (light->getMode() == LightMode::Ambient)
        removeAmbientLight(light);
    else if (light->getMode() == LightMode::Directional)
        removeDirectionalLight(light);
    else if (light->getMode() == LightMode::Point)
        removePointLight(light);
    else if (light->getMode() == LightMode::Spot)
        removeSpotLight(light);
}

void LightsController::removeAmbientLight(Light* light) {
    for (size_t i = 0; i < m_ambientLights.size(); i++) {
        if (m_ambientLights[i] == light) {
            m_ambientLights.erase(m_ambientLights.begin() + i);
            break;
        }
    }
}

void LightsController::removeDirectionalLight(Light* light) {
    for (size_t i = 0; i < m_directionalLights.size(); i++) {
        if (m_directionalLights[i] == light) {
            m_directionalLights.erase(m_directionalLights.begin() + i);
            break;
        }
    }
}

void LightsController::removePointLight(Light* light) {
    for (size_t i = 0; i < m_pointLights.size(); i++) {
        if (m_pointLights[i] == light) {
            m_pointLights.erase(m_pointLights.begin() + i);
            break;
        }
    }
}

void LightsController::removeSpotLight(Light* light) {
    for (size_t i = 0; i < m_spotLights.size(); i++) {
        if (m_spotLights[i] == light) {
            m_spotLights.erase(m_spotLights.begin() + i);
            break;
        }
    }
}

glm::vec3 LightsController::getAmbiantLights() {
    glm::vec3 result(0.0f, 0.0f, 0.0f);
    for (size_t i = 0; i < m_ambientLights.size(); i++) {
        result += m_ambientLights[i]->getDiffuseColor();
    }
    return result;
}

void LightsController::addAmbientLight(Light* light) {
    m_ambientLights.push_back(light);
}

void LightsController::addDirectionalLight(Light* light) {
    m_directionalLights.push_back(light);
}

void LightsController::addPointLight(Light* light) {
    m_pointLights.push_back(light);
}

void LightsController::addSpotLight(Light* light) {
    m_spotLights.push_back(light);
}

std::vector<Light*> LightsController::getPointLights() {
    return m_pointLights;
}

std::vector<Light*> LightsController::getDirectionalLights() {
    return m_directionalLights;
}

std::vector<Light*> LightsController::getSpotLights() {
    return m_spotLights;
}

void LightsController::changeLightMode(Light* light, LightMode newLightMode) {
    LightMode oldLightMode = light->getMode();

    if (oldLightMode == newLightMode)
        return;

    if (oldLightMode == LightMode::Ambient) {
        for (size_t i = 0; i < m_ambientLights.size(); i++) {
            if (m_ambientLights[i] == light) {
                m_ambientLights.erase(m_ambientLights.begin() + i);
                break;
            }
        }
    }
    if (oldLightMode == LightMode::Directional) {
        for (size_t i = 0; i < m_directionalLights.size(); i++) {
            if (m_directionalLights[i] == light) {
                m_directionalLights.erase(m_directionalLights.begin() + i);
                break;
            }
        }
    }
    if (oldLightMode == LightMode::Point) {
        for (size_t i = 0; i < m_pointLights.size(); i++) {
            if (m_pointLights[i] == light) {
                m_pointLights.erase(m_pointLights.begin() + i);
                break;
            }
        }
    }
    if (oldLightMode == LightMode::Spot) {
        for (size_t i = 0; i < m_spotLights.size(); i++) {
            if (m_spotLights[i] == light) {
                m_spotLights.erase(m_spotLights.begin() + i);
                break;
            }
        }
    }
    
    light->changeLightMode(newLightMode);
    addLight(light);
}

void LightsController::clear() {
    m_ambientLights.clear();
    m_directionalLights.clear();
    m_pointLights.clear();
    m_spotLights.clear();
}