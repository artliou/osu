typedef float4 point;
typedef float4 vector;
typedef float4 color;
typedef float4 sphere;

vector Bounce(vector in, vector n)
{
	vector out = in - n*(vector)(2.05f * dot(in.xyz, n.xyz));
	out.w = 0.;
	return out;
}

vector BounceSphere(point p, vector v, sphere s)
{
	vector n;
	n.xyz = fast_normalize(p.xyz - s.xyz);
	n.w = 0.;
	return Bounce(v, n);
}


bool IsInsideSphere(point p, sphere s)
{
	float r = fast_length(p.xyz - s.xyz);
	return  (r < s.w);
}

color GenerateColorFromBounce(float angle)
{
	color particleColor;
	particleColor.x = clamp((float)cos(angle), 0.0f, 1.0f);
	particleColor.y = clamp((float)cos(angle + ((2 * M_PI) / 3)), 0.0f, 1.0f);
	particleColor.z = clamp((float)cos(angle + ((4 * M_PI) / 3)), 0.0f, 1.0f);
	return particleColor;
}

kernel void Particle(global point *dPobj, global vector *dVel, global color *dCobj)
{
	const float4 G       = (float4) (0., -1.5, 0., 1.);
	const float  DT = .5;
	const sphere Sphere1 = (sphere)(0, 0., 0., 50000.);
	int gid = get_global_id(0);

	point  p = dPobj[gid];
	vector v = dVel[gid];
	float colorAngle = v.w;

	point  pp = p + v*DT + G*(point)(.5*DT*DT);
	vector vp = v + G*DT;
	pp.w = 1.;

	if(!IsInsideSphere(pp, Sphere1))
	{
		colorAngle += (M_PI / 3);
		vp = BounceSphere(p, v, Sphere1);
		pp = p + vp*DT + G*(point)(.5*DT*DT);
		dCobj[gid] = GenerateColorFromBounce(colorAngle);
	}

	vp.w = colorAngle;

	dPobj[gid] = pp;
	dVel[gid]  = vp;
}
