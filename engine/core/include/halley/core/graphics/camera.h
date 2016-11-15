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

#pragma once

#include "halley/maths/vector2.h"
#include "halley/maths/angle.h"
#include "halley/maths/rect.h"
#include "halley/maths/matrix4.h"
#include "halley/data_structures/maybe.h"

namespace Halley {

	class RenderTarget;

	class Camera {
	public:
		Camera();
		Camera(Vector2f pos, Angle1f angle=Angle1f::fromDegrees(0));

		void setPosition(Vector2f pos);
		void setAngle(Angle1f angle);
		void setZoom(float zoom);

		void resetRenderTarget();
		void setRenderTarget(RenderTarget& target);

		void resetViewPort();
		void setViewPort(Rect4i viewPort);

		Vector2f getPosition() const { return pos; }
		Angle1f getAngle() const { return angle; }
		float getZoom() const { return zoom; }

		Vector2f screenToWorld(Vector2f p, Rect4f viewport) const;
		Vector2f worldToScreen(Vector2f p, Rect4f viewport) const;

		Matrix4f getProjection() const { return projection; }

		void updateProjection(Vector2i viewSize, bool flipVertical = true);

		RenderTarget* getRenderTarget() const;
		Maybe<Rect4i> getViewPort() const;

	private:
		Vector2f pos;
		Matrix4f projection;
		Angle1f angle;
		float zoom;

		RenderTarget* renderTarget;
		Maybe<Rect4i> viewPort;
	};
}
