#ifndef LINE_H_
#define LINE_H_

#include"Vector3.h"

class Line
{
public:
	Line(const Vector3 start, const Vector3 end);
	Line();
	~Line();
	static float PointRayDistance(const Vector3 &point, const Line & Ray, Vector3& out_point, float& out_coefficient);
	static float PointLineDistance(const Vector3 &point, const Line & line, Vector3& out_point, float& out_coefficient);
	static float RayRayDistance(const Line& line1, const Line& line2, Vector3& out_point1, Vector3& out_point2, float& out_t1, float& out_t2);
	static float LineLineDistance(const Line& line1, const Line& line2, Vector3& out_point1, Vector3& out_point, float& out_t1, float& out_t2);
	static bool isSharpAngle(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3);
	static bool isParallel(const Line& line1, const Line& line2);
	static void clamp01(float &v);

public:
	Vector3 mStartPos;
	Vector3 mEndPos;
	Vector3 mV;

};

#endif