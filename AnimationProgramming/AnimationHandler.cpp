#include "AnimationHandler.h"
#include "Engine.h"

void drawLine(LibMath::Vector3 const& pStart, LibMath::Vector3 const& pEnd, LibMath::Vector3 const& pColor, LibMath::Vector3 const& pOffset)
{
		DrawLine(
		pStart.x + pOffset.x, pStart.y + pOffset.y, pStart.z + pOffset.z,
		pEnd.x + pOffset.x, pEnd.y + pOffset.y, pEnd.z + pOffset.z,
		pColor.x, pColor.y, pColor.z);
}

