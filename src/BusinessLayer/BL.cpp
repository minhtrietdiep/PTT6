#include <iostream>
#include "Headers/Preset.h"
#include "Headers/Control.h"
#include "Headers/Order.h"
#include "Headers/Config.h"
#include "Headers/Move.h"
#include "Headers/Plate.h"

Control *control;

void init()
{
    Plate *p1 = new Plate(1,1,0,2,5);
    std::vector<Plate> *plates = new std::vector<Plate>();
    plates->push_back(*p1);
    Preset *preset1 = new Preset(1,*plates);
    std::vector<Preset> *presets = new std::vector<Preset>(1, *preset1);
    control = new Control(*presets);
}

int main(int argc, char** argv)
{
	init();
	std::cout <<"ddd" << std::endl;
//    std::cout << control->GetPresets()[0].GetPlatelist()[0].GetThickness() << std::endl; //just to test
    return 0;
}

