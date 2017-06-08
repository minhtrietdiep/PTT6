# pragma once

#include <vector>
#include <string>
#include <Preset.h>
#include <Plate.h>
#include <PlateList.h>

std::string PresetToJSONString(std::vector<Preset> presets);
std::string PlateListToJSONString(std::vector<Plate> plates, PlateList type);
