#include "Project7a.hpp"

void ParticleSystem::ResetParticles()
{
	glBindBuffer(GL_ARRAY_BUFFER, GLParticlePosition);
	float4 * points = (float4 *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		// Particle points are generated 1000 units from origin.
		float distanceFromOrigin = 9000;
		float theta = ParticleSystem::Ranf(0, 2 * (float)M_PI);
		float phi = ParticleSystem::Ranf(0, (float)M_PI);
		points[i] = ParticleSystem::GetXYZfromPolar(distanceFromOrigin, theta, phi);

		float4 currentVelocity = ParticleSystem::GetXYZfromPolar(1, theta, phi);
		GLParticleVelocity[i].x = currentVelocity.x * VMAX * 5;
		GLParticleVelocity[i].y = currentVelocity.y * VMAX * 5;
		GLParticleVelocity[i].z = currentVelocity.z * VMAX * 5;
		GLParticleVelocity[i].w = 0.0f;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);


	glBindBuffer(GL_ARRAY_BUFFER, GLParticleColor);
	float4 * colors = (float4 *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		colors[i].x = Ranf(.3f, 1.);
		colors[i].y = Ranf(.3f, 1.);
		colors[i].z = Ranf(.3f, 1.);
		colors[i].w = 1.;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

float ParticleSystem::Ranf(float low, float high)
{
	long random();		// returns integer 0 - TOP

	float r = (float)rand();
	return(low + r * (high - low) / (float)RAND_MAX);
}
