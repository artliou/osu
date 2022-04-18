#include "Project7a.hpp"

float4 ParticleSystem::GetXYZfromPolar(float distanceFromOrigin, float theta, float phi)
{
	float4 point;

	point.x = distanceFromOrigin * sinf(theta) * cosf(phi);
	point.y = distanceFromOrigin * sinf(theta) * sinf(phi);
	point.z = distanceFromOrigin * cosf(theta);
	point.w = 1.;

	return point;
}
