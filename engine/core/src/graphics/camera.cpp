/*****************************************************************\
           __
          / /
		 / /                     __  __
		/ /______    _______    / / / / ________   __       __
	   / ______  \  /_____  \  / / / / / _____  | / /      / /
	  / /      | / _______| / / / / / / /____/ / / /      / /
	 / /      / / / _____  / / / / / / _______/ / /      / /
	/ /      / / / /____/ / / / / / / |______  / |______/ /
   /_/      /_/ |________/ / / / /  \_______/  \_______  /
                          /_/ /_/                     / /
			                                         / /
		       High Level Game Framework            /_/

  ---------------------------------------------------------------

  Copyright (c) 2007-2011 - Rodrigo Braz Monteiro.
  This file is subject to the terms of halley_license.txt.

\*****************************************************************/

#include "halley/core/graphics/camera.h"

using namespace Halley;


Camera::Camera()
	: zoom(1.0f)
{
	pos = Vector2f(640, 360);
}


Camera::Camera(Vector2f _pos, Angle1f _angle)
	: pos(_pos)
	, angle(_angle)
	, zoom(1.0f)
{
}


void Camera::setPosition(Vector2f _pos)
{
	pos = _pos;
}


void Camera::setAngle(Angle1f _angle)
{
	angle = _angle;
}


void Camera::setZoom(float _zoom)
{
	zoom = _zoom;
}


void Camera::updateProjection(Vector2i area, bool flipVertical)
{
	// Setup projection
	float w = float(area.x);
	float h = float(area.y);
	projection = Matrix4f::makeOrtho2D(-w/2, w/2, flipVertical ? h/2 : -h/2, flipVertical ? -h/2 : h/2, -1000, 1000);

	// Camera properties
	if (zoom != 1.0f) {
		projection.scale2D(zoom, zoom);
	}
	if (angle.getRadians() != 0) {
		projection.rotateZ(-angle);
	}
	if (pos != Vector2f()) {
		projection.translate2D(-pos.x, -pos.y);
	}
}

Vector2f Camera::screenToWorld(Vector2f p, Rect4f viewport) const
{
	Vector2f p2 = ((p - viewport.getTopLeft()) - viewport.getSize() * 0.5f) / zoom;

	p2 = p2.rotate(angle);

	return p2 + pos;
}

Vector2f Camera::worldToScreen(Vector2f p, Rect4f) const
{
	// TODO
	return p;
}
