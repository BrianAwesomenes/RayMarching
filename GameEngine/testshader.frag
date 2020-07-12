#version 330

#define MAX_STEPS 1000
#define COLLISION_RADIUS .0001
#define MAX_DIST 1000.
#define NORMAL_APPROX .01
#define PI 3.14159265359
#define SOFT_SHADOW_RADIUS 0.02

//1 MB of data for object storage
uniform int data[262144];

uniform vec3 lightPos = vec3(0,10,25);
uniform vec3 objColor = vec3(1, 1, 1);
uniform vec3 diffuseColor = vec3(1, 1, 1);
uniform vec3 ambientColor = vec3(1, 1, 1);
uniform vec3 spherePos = vec3(0, 0, 20);
uniform vec3 camPos = vec3(0, 1, 0);
uniform vec3 camRot = vec3(0, 0, 0);
uniform vec3 boxPos = vec3(5, 5, 20);
uniform vec3 boxRot = vec3(0, 0, 0);

uniform float sphereRadius = 2;
uniform float floorPlane = 0;
uniform float ambientStrength = 0.1;
uniform float width;
uniform float height;
uniform float fov = 75;

vec3 rotate(vec3 v, vec3 r) {
	float pitch = r.x;
	float yaw = r.y;
	float roll = r.z;

	mat3x3 m = mat3x3(
		1, 0, 0,
		0, cos(pitch), -sin(pitch),
		0, sin(pitch), cos(pitch)
	) * mat3x3(
		cos(yaw), 0, -sin(yaw),
		0, 1, 0,
		sin(yaw), 0, cos(yaw)
	) * mat3x3(
		cos(roll), -sin(roll), 0,
		sin(roll), cos(roll), 0,
		0, 0, 1
	);

	return v * m;
}

float cubeDist(vec3 point, vec3 pos, vec3 rotation, float size) {
	float dist = 0;

	vec3 r = rotate(vec3(1, 0, 0), rotation);
	vec3 u = rotate(vec3(0, 1, 0), rotation);
	vec3 f = rotate(vec3(0, 0, 1), rotation);


	vec3 Q = vec3(0);
	vec3 v = vec3(0);
	vec3 n = vec3(0);

	//Top plane
	n = u;

	Q = pos + n * size;
	v = point - Q;
	dist = dot(v, n);

	//Bottom plane
	n = -u;

	Q = pos + n * size;
	v = point - Q;
	dist = max(dist, dot(v, n));

	//Right plane
	n = r;

	Q = pos + n * size;
	v = point - Q;
	dist = max(dist, dot(v, n));

	//Left plane
	n = -r;

	Q = pos + n * size;
	v = point - Q;
	dist = max(dist, dot(v, n));

	//Front plane
	n = f;

	Q = pos + n * size;
	v = point - Q;
	dist = max(dist, dot(v, n));

	//Back plane
	n = -f;

	Q = pos + n * size;
	v = point - Q;
	dist = max(dist, dot(v, n));

	return dist;
}

float getDist(vec3 point) {
	float sR = length(spherePos - point) - sphereRadius;
	float pR = point.y - floorPlane + sin(point.x) / 4 + cos(point.z) / 4;
	float bR = cubeDist(point, boxPos, boxRot, 2);

	return min(bR, min(sR, pR));
}

vec2 rayMarch(vec3 ro, vec3 rd) {
	float dist = 0;
	float closest = getDist(ro);

	int steps = 0;
	for (int i = 0; i < MAX_STEPS; i++) {
		vec3 p = ro + rd * dist;
		float d = getDist(p);

		if (d < closest)
			closest = d;

		dist += d;
		if (dist > MAX_DIST || d < COLLISION_RADIUS) {
			steps = i;
			break;
		}
	}

	if (steps == MAX_STEPS || dist > MAX_DIST)
		dist = -1;

	return vec2(dist, closest);
}

vec3 getNormal(vec3 pos) {
	float d = getDist(pos);
	vec2 e = vec2(NORMAL_APPROX, 0);

	vec3 n = d - vec3(
		getDist(pos - e.xyy),
		getDist(pos - e.yxy),
		getDist(pos - e.yyx));

	return normalize(n);
}

vec3 diffuse(vec3 point) {
	vec3 norm = getNormal(point);
	vec3 lightDir = lightPos - point;
	float lightDist = length(lightDir);
	lightDir = lightDir / lightDist;

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * diffuseColor;

	vec3 p = point + lightDir * COLLISION_RADIUS * 4;
	vec2 shadow = rayMarch(p, lightDir);

	if (shadow.x <= lightDist && shadow.x >= 0)
		diffuse = vec3(0);

	return diffuse;
}

void main()
{
	vec3 ambient = ambientStrength * ambientColor;
	vec3 camFwd = rotate(vec3(0, 0, 1), camRot);
	vec3 camRgt = rotate(vec3(1, 0, 0), camRot);
	vec3 camUp = rotate(vec3(0, 1, 0), camRot);

	vec2 screen = vec2(gl_FragCoord.x - 0.5 * width, gl_FragCoord.y - 0.5 * height) / height;

	float offset = (1 / tan(fov * (PI / 360)));
	vec3 o = camPos - camFwd * offset;
	vec3 dir = normalize(camFwd * offset + camRgt * screen.x + camUp * screen.y);
	
	float dist = rayMarch(o, dir).x;

	vec3 hitPoint = o + dir * dist;

	vec3 diffuse = diffuse(hitPoint);
	float intensity = 10000 / (4 * PI * dist * dist);

	vec3 result = (diffuse * intensity + ambient) * objColor;

	if (dist < 0)
		result = vec3(0, 0, 0);
	
	gl_FragColor = vec4(result, 1);
}