#include "Agent.h"
#include <Vladgine/ResourceManager.h>
#include "Level.h"
#include <algorithm>

Agent::Agent()
{
}

Agent::~Agent()
{
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePositions;

	
	checkTilePosition(levelData, collideTilePositions, _position.x, _position.y);
	checkTilePosition(levelData, collideTilePositions, _position.x + AGENT_WIDTH, _position.y);
	checkTilePosition(levelData, collideTilePositions, _position.x, _position.y + AGENT_WIDTH);
	checkTilePosition(levelData, collideTilePositions, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);

	if (collideTilePositions.size() == 0) {
		return false;
	}

	for (int i = 0; i < collideTilePositions.size(); i++) {
		collideWithTile(collideTilePositions[i]);
	}
	return true;
}

bool Agent::collideWithAgent(Agent* agent)
{
	const float MIN_DISTANCE = AGENT_RADIUS * 2;

	glm::vec2 centerPosA = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth > 0) {

		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

		_position += collisionDepthVec / 2.0f;
		agent->_position -= collisionDepthVec / 2.0f;
		return true;
	}

	return false;


}

void Agent::draw(Vladgine::SpriteBatch& _spriteBatch)
{
	static int textureID = Vladgine::ResourceManager::getTexture("Textures/PNG/CharacterLeft_Jump.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	_spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}

bool Agent::applyDamage(float Damage)
{
	_health -= Damage;
	if (_health <= 0) {
		return true;
	} else {
		return false;
	}
}

void Agent::checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions, float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
									floor(y / (float)TILE_WIDTH));

	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].length() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size()) {
		return;
	}

	if (levelData[cornerPos.y][cornerPos.x] != '.') {
		collideTilePositions.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH/2));
	}
}
//aabb collision
void Agent::collideWithTile(glm::vec2 tilePos)
{
	
	const float TILE_RADIUS = (float)TILE_WIDTH / 2;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPlayerPos - tilePos;

	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	float absXDEpth = abs(xDepth);
	float absYDEpth = abs(yDepth);

	if (xDepth > 0 || yDepth > 0) 
	{
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)){
			if (distVec.x < 0) {
				_position.x -= xDepth;
			}
			else {
				_position.x += xDepth;
			}
		} else {
			if (distVec.y < 0) {
				_position.y -= yDepth;
			}
			else {
				_position.y += yDepth;
			}
		}
	}


}