#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Vladgine {

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenW, int screenH);

		void update();
		glm::vec2 converScreenToWorld(glm::vec2 screenCoords);

		//setters
		void setPos(const glm::vec2& newPos) { _position = newPos; 	_needsMatrixUpdate = true; }
		void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true;}

		//getters
		glm::vec2 getPos() { return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix;  }

	private:
		int _screenWidth, _screenHeight;
		bool _needsMatrixUpdate;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;

	};

}