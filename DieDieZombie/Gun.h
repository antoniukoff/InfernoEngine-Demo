#pragma once
#include <string>
#include <GLEW/glm/glm.hpp>
#include <InfernoEngine/AudioEngine.h>
#include <vector>
#include "Bullet.h"

class Gun
{
public:
	Gun(std::string name, 
		int firerate,
		int bulletspershot,
		float spread,
		float _bulletDamage, 
		float bulleSpeed,
		Inferno::SoundEffect fireEffect);
	~Gun();
	void update(bool isMouseDown,
		const glm::vec2& position,
		const glm::vec2& direction, 
		std::vector<Bullet>& bullets,
		float deltaTime);
private:
	void fire(glm::vec2 direction, const glm::vec2& position, std::vector<Bullet>& bullets);

	Inferno::SoundEffect m_fireEffect;
	std::string _name;
	/// <summary>
	/// Gun Attributes
	/// </summary>
	int _fireRate; // in terms of frames
	int _bulletPerShot; //how many bullets are fired at a time
	float _spread; // accuracy
	float _bulletSpeed; 
	float _bulletDamage;
	float _frameCounter;
};

