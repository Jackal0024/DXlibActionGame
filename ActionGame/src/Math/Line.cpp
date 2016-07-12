#include "Line.h"

Line::Line(const Vector3 start, const Vector3 end):
	mStartPos(start),
	mEndPos(end)
{
	mV = mEndPos - mStartPos;
}

Line::Line():
	mStartPos(Vector3(0.0f,0.0f,0.0f)),
	mEndPos(Vector3(0.0f, 0.0f, 0.0f))
{
}

Line::~Line()
{
}

//ì_Ç∆[íºê¸]ÇÃç≈íZãóó£
float Line::PointRayDistance(const Vector3 &point, const Line & Ray,Vector3& out_point,float& out_coefficient)
{
	Vector3 v = Ray.mEndPos - Ray.mStartPos;
	float len = VSquareSize(v);
	out_coefficient = 0.0f;
	if (len > 0.0f) out_coefficient = VDot(v,point - Ray.mStartPos) / len;
	out_point = Ray.mStartPos + (out_coefficient * v);
	return VSize((out_point - point));
}

//ê¸ï™Ç∆ì_ÇÃç≈íZãóó£
float Line::PointLineDistance(const Vector3 & point, const Line & line, Vector3& out_point, float& out_coefficient)
{
	float len = PointRayDistance(point, line,out_point,out_coefficient);

	if (isSharpAngle(point, line.mStartPos, line.mEndPos))
	{
		out_point = line.mStartPos;
		return VSize(line.mStartPos - point);
	}
	else if(isSharpAngle(point, line.mEndPos, line.mStartPos))
	{
		out_point = line.mEndPos;
		return VSize(line.mEndPos - point);
	}
	return len;
}

float Line::RayRayDistance(const Line & line1, const Line & line2, Vector3& out_point1,Vector3& out_point2,float& out_t1,float& out_t2)
{
	if (Line::isParallel(line1, line2))
	{
		float len = Line::PointLineDistance(line1.mStartPos, line2,out_point2,out_t2);
		out_point1 = line1.mStartPos;
		out_t1 = 0.0f;
		return len;
	}

	Vector3 v1 = line1.mEndPos - line1.mStartPos;
	Vector3 v2 = line2.mEndPos - line2.mStartPos;

	float DV1V2 = VDot(v1, v2);
	float DV1V1 = VSquareSize(v1);
	float DV2V2 = VSquareSize(v2);
	Vector3 P21P11 = line1.mStartPos - line2.mStartPos;
	out_t1 = (DV1V2 * VDot(v2, P21P11) - DV2V2 * VDot(v1, P21P11))
		/ (DV1V1 * DV2V2 - DV1V2 * DV1V2);
	out_point1 = line1.mStartPos + (v1 * out_t1);
	out_t2 = VDot(v2,out_point1 - line2.mStartPos) / DV2V2;
	out_point2 = line2.mStartPos + (v2 * out_t2);

	return VSize(out_point2 - out_point1);


}

float Line::LineLineDistance(const Line & line1, const Line & line2, Vector3 & out_point1, Vector3 & out_point2, float & out_t1, float & out_t2)
{
	Vector3 v1 = line1.mEndPos - line1.mStartPos;
	Vector3 v2 = line2.mEndPos - line2.mStartPos;
	if (VSquareSize(v1) < 0.000001f)
	{
		if (VSquareSize(v2) < 0.000001f)
		{
			float len = VSize(line2.mStartPos - line1.mStartPos);
			out_point1 = line1.mStartPos;
			out_point2 = line2.mStartPos;
			out_t1 = out_t2 = 0.0f;
			return len;
		}
		else
		{
			float len = PointLineDistance(line1.mStartPos, line2, out_point2, out_t2);
			out_point1 = line1.mStartPos;
			out_t1 = 0.0f;
			clamp01(out_t2);
			return len;
		}
	}
	else if(VSquareSize(v2) < 0.000001f)
	{
		float len = PointLineDistance(line2.mStartPos, line1, out_point1, out_t1);
		out_point2 = line2.mStartPos;
		clamp01(out_t1);
		out_t2 = 0.0f;
		return len;
	}

	//ê¸ï™ìØém

	if (isParallel(line1, line2))
	{
		out_t1 = 0.0f;
		out_point1 = line1.mStartPos;
		float len = PointLineDistance(line1.mStartPos, line2, out_point2, out_t2);
		if (0.0f <= out_t2 && out_t2 <= 1.0f) return len;
	}
	else
	{
		float len = RayRayDistance(line1, line2, out_point1, out_point2, out_t1, out_t2);
		if (0.0f <= out_t1 && out_t1 <= 1.0f &&
			0.0f <= out_t2 && out_t2 <= 1.0f
			)
		{
			return len;
		}
	}

	//êÇíºÇ™äOÇ…Ç†ÇÈ
	clamp01(out_t1);
	out_point1 = line1.mStartPos + (v1 * out_t1);
	float len = PointLineDistance(out_point1, line2, out_point2, out_t2);
	if (0.0f <= out_t2 && out_t2 <= 1.0f) return len;

	clamp01(out_t2);
	out_point2 = line2.mStartPos + (v2 * out_t2);
	len = PointLineDistance(out_point2, line1, out_point1, out_t1);
	if (0.0f <= out_t1 && out_t1 <= 1.0f) return len;

	clamp01(out_t1);
	out_point1 = line1.mStartPos + (v1 * out_t1);
	return VSize(out_point2 - out_point1);


}

//ÉxÉNÉgÉãÇ™âsäpÇ©Ç«Ç§Ç©ÇÃîªíË
bool Line::isSharpAngle(const Vector3 & p1, const Vector3 & p2, const Vector3 & p3)
{
	auto dot = VDot(p1 - p2, p2 - p3);
	if (dot > 0)
	{
		return true;
	}
	else if(dot < 0)
	{
		return false;
	}
	return false;
}

bool Line::isParallel(const Line & line1, const Line & line2)
{
	Vector3 v1 = line1.mStartPos - line1.mEndPos;
	Vector3 v2 = line2.mStartPos - line2.mEndPos;
	return VCross(v1, v2).x == 0 && VCross(v1, v2).y == 0 && VCross(v1, v2).z == 0;
}

void Line::clamp01(float & v)
{
	v = min(max(v, 0), 1);
}
