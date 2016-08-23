#include "camera.h"

using namespace Jam;

Camera::Camera(glm::mat4 projection, Transform transform)
	: _projection(projection), transform(transform)
{

}