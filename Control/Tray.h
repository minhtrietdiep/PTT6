#pragma once

class Tray {
	enum class Material {
		Iron,
		Copper,
		Uranium,
		Gold,
		Material_SIZE
	}
	
	public:
	Tray(int id, Material m);
	~Tray();
	bool IsPlatePresent();
	void Toggle();
	
	private:
	int id;
	Material m;
	bool platePresent;
}
