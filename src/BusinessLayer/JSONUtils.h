# pragma once

#include <vector>
#include <string>
#include <Preset.h>
#include <Config.h>

std::string PresetToJSONString(std::vector<Preset> presets);
std::string PlateListToJSONString(std::vector<Plate> plates, PlateList type);
