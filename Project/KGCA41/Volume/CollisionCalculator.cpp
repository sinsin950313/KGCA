#include "CollisionCalculator.h"
#include "Common.h"
#include "HCCalculator.h"

namespace SSB
{
	static DefaultCollisionCalculator kDefaultCollisionCalculator;

	bool DefaultCollisionCalculator::IsCollide(RayData lData, PlaneData rData)
	{
		float distance = rData.A * lData.Origin.GetX() + rData.B * lData.Origin.GetY() + rData.C * lData.Origin.GetZ() + rData.D;
		float dot = rData.A * lData.Direction.GetX() + rData.B * lData.Direction.GetY() + rData.C * lData.Direction.GetZ();

		if (abs(dot) < FDelta)
		{
			if (abs(distance) < FDelta)
				return true;
			else
				return false;
		}

		return distance * dot < 0;
	}

	bool DefaultCollisionCalculator::IsIn(RayData lData, PlaneData rData)
	{
		return false;
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(RayData lData, PlaneData rData)
	{
		std::vector<Vector3> ret;

		float distance = lData.Direction.Dot(rData.NormalVector) + rData.D;
		float dotProduct = lData.Direction.Dot(rData.NormalVector);
		if (abs(dotProduct) < FDelta)
		{
			 //The ray is parallel to the plane
			if (abs(distance - FDelta) < FDelta)
			{
				ret.push_back(lData.Origin);
			}
			return ret;
		}

		float t = -distance / dotProduct;
		if (t >= 0)
		{
			 //The intersection point is in front of the ray origin
			Vector3 intersection = lData.Origin + lData.Direction * t;
			ret.push_back(intersection);
		}

		return ret;
	}

	bool DefaultCollisionCalculator::IsCollide(RayData lData, TriangleData rData)
	{
		Vector3 e1 = rData.Vertice[1] - rData.Vertice[0];
		Vector3 e2 = rData.Vertice[2] - rData.Vertice[0];

		Vector3 pVec = lData.Direction.Cross(e2);
		float det = e1.Dot(pVec);

		Vector3 tVec;
		if (det > 0)
		{
			tVec = lData.Origin - rData.Vertice[0];
		}
		else
		{
			tVec = rData.Vertice[0] - lData.Origin;
			det = -det;
		}

		if (det < 0.0001f)
			return false;

		float u = tVec.Dot(pVec);
		if (u < 0.0f)
			return false;

		Vector3 qVec = tVec.Cross(e1);

		float v = lData.Direction.Dot(qVec);
		if (v < 0.0f)
			return false;

		if (u + v > det)
			return false;

		return true;
	}

	bool DefaultCollisionCalculator::IsIn(RayData lData, TriangleData rData)
	{
		return false;
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(RayData lData, TriangleData rData)
	{
		Vector3 e1 = rData.Vertice[1] - rData.Vertice[0];
		Vector3 e2 = rData.Vertice[2] - rData.Vertice[0];

		Vector3 pVec = lData.Direction.Cross(e2);
		float det = e1.Dot(pVec);

		Vector3 tVec;
		if (det > 0)
		{
			tVec = lData.Origin - rData.Vertice[0];
		}
		else
		{
			tVec = rData.Vertice[0] - lData.Origin;
			det = -det;
		}

		Vector3 qVec = tVec.Cross(e1);

		float t = e2.Dot(qVec);
		Vector3 ret = lData.Origin + lData.Direction * t;

		return { ret };
	}

	bool DefaultCollisionCalculator::IsCollide(RayData lData, AABBData rData)
	{
		Vector3 tmin;
		{
			float x = (rData.Min.GetX() - lData.Origin.GetX()) / (lData.Direction.GetX() + FDelta);
			float y = (rData.Min.GetY() - lData.Origin.GetY()) / (lData.Direction.GetY() + FDelta);
			float z = (rData.Min.GetZ() - lData.Origin.GetZ()) / (lData.Direction.GetZ() + FDelta);
			tmin = Vector3(x, y,z);
		}

		Vector3 tmax;
		{
			float x = (rData.Max.GetX() - lData.Origin.GetX()) / (lData.Direction.GetX() + FDelta);
			float y = (rData.Max.GetY() - lData.Origin.GetY()) / (lData.Direction.GetY() + FDelta);
			float z = (rData.Max.GetZ() - lData.Origin.GetZ()) / (lData.Direction.GetZ() + FDelta);
			tmax = Vector3(x, y,z);
		}

		Vector3 real_min(min(tmin.GetX(), tmax.GetX()), min(tmin.GetY(), tmax.GetY()), min(tmin.GetZ(), tmax.GetZ()));
		Vector3 real_max(max(tmin.GetX(), tmax.GetX()), max(tmin.GetY(), tmax.GetY()), max(tmin.GetZ(), tmax.GetZ()));

		float minmax = min(min(real_max.GetX(), real_max.GetY()), real_max.GetZ());
		float maxmin = max(max(real_min.GetX(), real_min.GetY()), real_min.GetZ());

		if (minmax >= maxmin)
		{
			return true;
		}
		return false;
	}

	bool DefaultCollisionCalculator::IsIn(RayData lData, AABBData rData)
	{
		return false;
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(RayData lData, AABBData rData)
	{
		Vector3 tmin;
		{
			float x = (rData.Min.GetX() - lData.Origin.GetX()) / (lData.Direction.GetX() + FDelta);
			float y = (rData.Min.GetY() - lData.Origin.GetY()) / (lData.Direction.GetY() + FDelta);
			float z = (rData.Min.GetZ() - lData.Origin.GetZ()) / (lData.Direction.GetZ() + FDelta);
			tmin = Vector3(x, y,z);
		}

		Vector3 tmax;
		{
			float x = (rData.Max.GetX() - lData.Origin.GetX()) / (lData.Direction.GetX() + FDelta);
			float y = (rData.Max.GetY() - lData.Origin.GetY()) / (lData.Direction.GetY() + FDelta);
			float z = (rData.Max.GetZ() - lData.Origin.GetZ()) / (lData.Direction.GetZ() + FDelta);
			tmax = Vector3(x, y,z);
		}

		Vector3 real_min(min(tmin.GetX(), tmax.GetX()), min(tmin.GetY(), tmax.GetY()), min(tmin.GetZ(), tmax.GetZ()));
		Vector3 real_max(max(tmin.GetX(), tmax.GetX()), max(tmin.GetY(), tmax.GetY()), max(tmin.GetZ(), tmax.GetZ()));

		float minmax = min(min(real_max.GetX(), real_max.GetY()), real_max.GetZ());
		float maxmin = max(max(real_min.GetX(), real_min.GetY()), real_min.GetZ());

		std::vector<Vector3> ret;
		if (minmax >= maxmin)
		{
			ret.push_back(lData.Origin + lData.Direction * maxmin);
		}
		return ret;
	}

	bool DefaultCollisionCalculator::IsCollide(RayData lData, OBBData rData)
	{
		float t_min = (std::numeric_limits<float>::min)();
		float t_max = (std::numeric_limits<float>::max)();
		float f[3], fa[3], s[3], sa[3];

		Vector3 vR = lData.Origin - rData.Position;

		float extent[3]{ rData.Width, rData.Height, rData.Depth };
		for (int v = 0; v < 3; v++)
		{
			f[v] = rData.Rotation.GetRow(v).Dot(lData.Direction);
			s[v] = rData.Rotation.GetRow(v).Dot(vR);
			fa[v] = fabs(f[v]);
			sa[v] = fabs(s[v]);

			if (sa[v] > extent[v] && s[v] * f[v] >= 0.0f)
				return false;

			float t1 = (-s[v] - extent[v]) / f[v];
			float t2 = (-s[v] + extent[v]) / f[v];
			if (t1 > t2)
			{
				float tmp = t1;
				t1 = t2;
				t2 = tmp;
			}
			t_min = max(t_min, t1);
			t_max = min(t_max, t2);
			if (t_min > t_max)
				return false;
		}

		float  fCross[3], fRhs;
		Vector3 vDxR;
		vR = vDxR.Cross(lData.Direction);
		 //D X pBox->vAxis[0]  분리축
		fCross[0] = fabs(vDxR.Dot(rData.Rotation.GetRow(0)));
		float fAxis2 = extent[1] * fa[2];
		float fAxis1 = extent[2] * fa[1];
		fRhs = fAxis2 + fAxis1;
		if (fCross[0] > fRhs)
		{
			return false;
		}
		 //D x pBox->vAxis[1]  분리축
		fCross[1] = fabs(vDxR.Dot(rData.Rotation.GetRow(1)));
		fRhs = extent[0] * fa[2] + extent[2] * fa[0];
		if (fCross[1] > fRhs)
		{
			return false;
		}
		 //D x pBox->vAxis[2]  분리축
		fCross[2] = fabs(vDxR.Dot(rData.Rotation.GetRow(2)));
		fRhs = extent[0] * fa[1] + extent[1] * fa[0];
		if (fCross[2] > fRhs)
		{
			return false;
		}

		return true;
	}

	bool DefaultCollisionCalculator::IsIn(RayData lData, OBBData rData)
	{
		return false;
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(RayData lData, OBBData rData)
	{
		std::vector<Vector3> ret;

		float t_min = (std::numeric_limits<float>::min)();
		float t_max = (std::numeric_limits<float>::max)();
		float f[3], fa[3], s[3], sa[3];

		Vector3 vR = lData.Origin - rData.Position;

		float extent[3]{ rData.Width, rData.Height, rData.Depth };
		for (int v = 0; v < 3; v++)
		{
			f[v] = rData.Rotation.GetRow(v).Dot(lData.Direction);
			s[v] = rData.Rotation.GetRow(v).Dot(vR);
			fa[v] = fabs(f[v]);
			sa[v] = fabs(s[v]);

			if (sa[v] > extent[v] && s[v] * f[v] >= 0.0f)
				return ret;

			float t1 = (-s[v] - extent[v]) / f[v];
			float t2 = (-s[v] + extent[v]) / f[v];
			if (t1 > t2)
			{
				float tmp = t1;
				t1 = t2;
				t2 = tmp;
			}
			t_min = max(t_min, t1);
			t_max = min(t_max, t2);
			if (t_min > t_max)
				return ret;
		}

		float  fCross[3], fRhs;
		Vector3 vDxR;
		vR = vDxR.Cross(lData.Direction);
		 //D X pBox->vAxis[0]  분리축
		fCross[0] = fabs(vDxR.Dot(rData.Rotation.GetRow(0)));
		float fAxis2 = extent[1] * fa[2];
		float fAxis1 = extent[2] * fa[1];
		fRhs = fAxis2 + fAxis1;
		if (fCross[0] > fRhs)
		{
			//m_vDxR = vDxR;
			return ret;
		}
		 //D x pBox->vAxis[1]  분리축
		fCross[1] = fabs(vDxR.Dot(rData.Rotation.GetRow(1)));
		fRhs = extent[0] * fa[2] + extent[2] * fa[0];
		if (fCross[1] > fRhs)
		{
			//m_vDxR = vDxR;
			return ret;
		}
		 //D x pBox->vAxis[2]  분리축
		fCross[2] = fabs(vDxR.Dot(rData.Rotation.GetRow(2)));
		fRhs = extent[0] * fa[1] + extent[1] * fa[0];
		if (fCross[2] > fRhs)
		{
			//m_vDxR = vDxR;
			return ret;
		}

		ret.push_back(lData.Origin + lData.Direction * t_min);
		return ret;
	}

	bool DefaultCollisionCalculator::IsCollide(TriangleData lData, RayData rData)
	{
		return IsCollide(rData, lData);
	}

	bool DefaultCollisionCalculator::IsIn(TriangleData lData, RayData rData)
	{
		return false;
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(TriangleData lData, RayData rData)
	{
		return GetIntersections(rData, lData);
	}

	bool DefaultCollisionCalculator::IsCollide(TriangleData lData, SegmentData rData)
	{
		return IsCollide(rData, lData);
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(TriangleData lData, SegmentData rData)
	{
		return GetIntersections(rData, lData);
	}

	bool DefaultCollisionCalculator::IsCollide(VolumeData lData, TriangleData rData)
	{
		Vector3 e0, e1, e2, iInter, vNormal;
		e0 = rData.Vertice[1] - rData.Vertice[0];
		e1 = rData.Vertice[2] - rData.Vertice[1];
		e2 = rData.Vertice[0] - rData.Vertice[2];
		Vector3 faceNormal = e0.Cross(rData.Vertice[2] - rData.Vertice[0]);

		{
			iInter = lData.Position - rData.Vertice[0];
			vNormal = e0.Cross(iInter);
			vNormal.Normalize();
			float fDot = faceNormal.Dot(vNormal);
			if (fDot < 0.0f) return false;
		}

		{
			iInter = lData.Position - rData.Vertice[1];
			vNormal = e1.Cross(iInter);
			vNormal.Normalize();
			float fDot = faceNormal.Dot(vNormal);
			if (fDot < 0.0f) return false;
		}

		{
			iInter = lData.Position - rData.Vertice[2];
			vNormal = e2.Cross(iInter);
			vNormal.Normalize();
			float fDot = faceNormal.Dot(vNormal);
			if (fDot < 0.0f) return false;
		}

		return true;
	}

	bool DefaultCollisionCalculator::IsIn(VolumeData lData, TriangleData rData)
	{
		return IsCollide(lData, rData);
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(VolumeData lData, TriangleData rData)
	{
		std::vector<Vector3> ret;
		Vector3 e0, e1, e2, iInter, vNormal;
		e0 = rData.Vertice[1] - rData.Vertice[0];
		e1 = rData.Vertice[2] - rData.Vertice[1];
		e2 = rData.Vertice[0] - rData.Vertice[2];
		Vector3 faceNormal = e0.Cross(rData.Vertice[2] - rData.Vertice[0]);

		{
			iInter = lData.Position - rData.Vertice[0];
			vNormal = e0.Cross(iInter);
			vNormal.Normalize();
			float fDot = faceNormal.Dot(vNormal);
			if (fDot < 0.0f) return ret;
		}

		{
			iInter = lData.Position - rData.Vertice[1];
			vNormal = e1.Cross(iInter);
			vNormal.Normalize();
			float fDot = faceNormal.Dot(vNormal);
			if (fDot < 0.0f) return ret;
		}

		{
			iInter = lData.Position - rData.Vertice[2];
			vNormal = e2.Cross(iInter);
			vNormal.Normalize();
			float fDot = faceNormal.Dot(vNormal);
			if (fDot < 0.0f) return ret;
		}

		ret.push_back(lData.Position);
		return ret;
	}

	bool DefaultCollisionCalculator::IsCollide(VolumeData lData, AABBData rData)
	{
		return (lData.Position.GetX() - rData.Min.GetX() >= FDelta && lData.Position.GetX() - rData.Max.GetX() <= -FDelta &&
			lData.Position.GetY() - rData.Min.GetY() >= FDelta && lData.Position.GetY() - rData.Max.GetY() <= -FDelta &&
			lData.Position.GetZ() - rData.Min.GetZ() >= FDelta && lData.Position.GetZ() - rData.Max.GetZ() <= -FDelta);
	}

	bool DefaultCollisionCalculator::IsIn(VolumeData lData, AABBData rData)
	{
		return IsCollide(lData, rData);
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(VolumeData lData, AABBData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{lData.Position} : std::vector<Vector3>{};
	}

	bool DefaultCollisionCalculator::IsCollide(VolumeData lData, OBBData rData)
	{
		// change to inner product
		 //Transform the given VolumeData into OBB space
		Vector3 localPos = (lData.Position - rData.Position) * rData.Rotation.Transpose();

		 //Check if the transformed VolumeData is within the OBB
		return (
			abs(localPos.GetX()) - rData.Width <= FDelta&&
			abs(localPos.GetY()) - rData.Height <= FDelta &&
			abs(localPos.GetZ()) - rData.Depth <= FDelta
			);
	}

	bool DefaultCollisionCalculator::IsIn(VolumeData lData, OBBData rData)
	{
		return IsCollide(lData, rData);
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(VolumeData lData, OBBData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{lData.Position} : std::vector<Vector3>{};
	}

	bool DefaultCollisionCalculator::IsCollide(VolumeData lData, BoxData rData)
	{
		 //Check if the line intersects with all 6 plane of the box
		for (int i = 0; i < 6; i++)
		{
			PlaneData plane = rData.Plane[i];
			float dot = lData.Position.Dot(plane.NormalVector) + plane.D;

			if (FDelta < dot)
			{
				return false;
			}
		}
		return true;
	}

	bool DefaultCollisionCalculator::IsIn(VolumeData lData, BoxData rData)
	{
		return IsCollide(lData, rData);
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(VolumeData lData, BoxData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{lData.Position} : std::vector<Vector3>{};
	}

	bool DefaultCollisionCalculator::IsCollide(VolumeData lData, SphereData rData)
	{
		 //Calculate distance between the center of sphere and the volume
		Vector3 diff = rData.Position - lData.Position;
		float distance = diff.Length();

		 //Check if the distance is within the radius of the sphere
		if (abs(distance - rData.Radius) <= FDelta)
			return true;
		else
			return false;
	}

	bool DefaultCollisionCalculator::IsIn(VolumeData lData, SphereData rData)
	{
		return IsCollide(lData, rData);
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(VolumeData lData, SphereData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{lData.Position} : std::vector<Vector3>{};
	}

	bool DefaultCollisionCalculator::IsCollide(LineData lData, VolumeData rData)
	{
		return IsCollide(rData, lData);
	}

	bool DefaultCollisionCalculator::IsIn(LineData lData, VolumeData rData)
	{
		return false;
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(LineData lData, VolumeData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{rData.Position} : std::vector<Vector3>{};
	}

	bool DefaultCollisionCalculator::IsCollide(LineData lData, LineData rData)
	{
		 //Calculate the cross product of two direction vectors
		Vector3 cross = lData.Direction.Cross(rData.Direction);

		 //Check if the lines are parallel
		if (cross.LengthSquare() < FDelta)
		{
			 //Check if the two lines are colinear
			Vector3 lToR = rData.Position - lData.Position;
			float dot = lToR.Dot(lData.Direction);
			if (abs(abs(dot) - lToR.Length()) < FDelta)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			 //Calculate the distance between two lines
			Vector3 lToR = rData.Position - lData.Position;
			float distance = lToR.Dot(cross) / cross.Length();
			return fabs(distance) < 1e-6f;
		}
	}

	bool DefaultCollisionCalculator::IsIn(LineData lData, LineData rData)
	{
		if (IsCollide(lData, rData))
		{
			 //Calculate the cross product of two direction vectors
			Vector3 cross = lData.Direction.Cross(rData.Direction);

			 //Check if the lines are parallel
			if (cross.LengthSquare() < FDelta)
			{
				return true;
			}
		}
		return false;
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(LineData lData, LineData rData)
	{
		std::vector<Vector3> ret;
		if (IsIn(lData, rData))
		{
			ret.push_back(lData.Vertex);
			ret.push_back(rData.Vertex);
		}
		else
		{
			if (IsCollide(lData, rData))
			{
				
			}
		}
		return ret;
	}

	bool DefaultCollisionCalculator::IsCollide(RayData lData, SphereData rData)
	{
		 //p0 - c
		Vector3 vDir = lData.Origin - rData.Position;
		 //B = 2(u dot (p0 - c ))
		float  fProj = lData.Direction.Dot(vDir);
		 //what the hell?
		 //제한된 길이(세그먼트) 제외처리
		//if (pRay->fExtent > -1.0f && pRay->fExtent < fabs(fProj)) return false;

		float b = 2.0f * fProj;
		 //C= (p0-c) dot (p0-c) - r*r
		float c = vDir.Dot(vDir) - (rData.Radius * rData.Radius);
		 //D = B*B - 4*AC;
		float fDiscriminant = (b * b) - (4.0f * c);
		if (fDiscriminant < 0.0f)
		{
			return false;
		}
		fDiscriminant = sqrtf(fDiscriminant);
		float t0 = (-b + fDiscriminant) / 2.0f;
		float t1 = (-b - fDiscriminant) / 2.0f;

		if (t0 >= 0.0f)
		{
			return true;
		}
		if (t1 >= 0.0f)
		{
			return true;
		}
		return false;
	}

	bool DefaultCollisionCalculator::IsIn(RayData lData, SphereData rData)
	{
		return false;
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(RayData lData, SphereData rData)
	{
		std::vector<Vector3> ret;

		 //p0 - c
		Vector3 vDir = lData.Origin - rData.Position;
		 //B = 2(u dot (p0 - c ))
		float  fProj = lData.Direction.Dot(vDir);
		 //what the hell?
		 //제한된 길이(세그먼트) 제외처리
		//if (pRay->fExtent > -1.0f && pRay->fExtent < fabs(fProj)) return false;

		float b = 2.0f * fProj;
		 //C= (p0-c) dot (p0-c) - r*r
		float c = vDir.Dot(vDir) - (rData.Radius * rData.Radius);
		 //D = B*B - 4*AC;
		float fDiscriminant = (b * b) - (4.0f * c);
		if (fDiscriminant < 0.0f)
		{
			return ret;
		}
		fDiscriminant = sqrtf(fDiscriminant);
		float t0 = (-b + fDiscriminant) / 2.0f;
		float t1 = (-b - fDiscriminant) / 2.0f;

		if (t0 >= 0.0f)
		{
			ret.push_back(lData.Origin + lData.Direction * t0);
		}
		if (t1 >= 0.0f)
		{
			ret.push_back(lData.Origin + lData.Direction * t1);
		}
		return ret;
	}

	bool DefaultCollisionCalculator::IsCollide(SegmentData lData, VolumeData rData)
	{
		return IsCollide(rData, lData);
	}

	bool DefaultCollisionCalculator::IsIn(SegmentData lData, VolumeData rData)
	{
		return IsCollide(lData, rData);
	}

	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(SegmentData lData, VolumeData rData)
	{
		return GetIntersections(rData, lData);
	}

	bool DefaultCollisionCalculator::IsCollide(OBBData lData, AABBData rData)
	{
		return IsCollide(rData, lData);
	}

	bool DefaultCollisionCalculator::IsCollide(OBBData lData, OBBData rData)
	{
		Vector3 D(rData.Position.GetX() - lData.Position.GetX(), rData.Position.GetY() - lData.Position.GetY(), rData.Position.GetZ() - lData.Position.GetZ());
		float C[3][3];
		float absC[3][3];
		float AD[3];
		float R0, R1, R;
		float R01;
		//A0
		C[0][0] = lData.Rotation.GetRow(0).Dot(rData.Rotation.GetRow(0));
		C[0][1] = lData.Rotation.GetRow(0).Dot(rData.Rotation.GetRow(1));
		C[0][2] = lData.Rotation.GetRow(0).Dot(rData.Rotation.GetRow(2));
		AD[0] = lData.Rotation.GetRow(0).Dot(D);
		absC[0][0] = (float)fabs(C[0][0]);
		absC[0][1] = (float)fabs(C[0][1]);
		absC[0][2] = (float)fabs(C[0][2]);
		R = (float)fabs(AD[0]);
		R1 = rData.Width * absC[0][0] + rData.Height * absC[0][1] + rData.Depth * absC[0][2];
		R01 = lData.Width + R1;
		if (R > R01)return false;
		//A1
		C[1][0] = lData.Rotation.GetRow(1).Dot(rData.Rotation.GetRow(0));
		C[1][1] = lData.Rotation.GetRow(1).Dot(rData.Rotation.GetRow(1));
		C[1][2] = lData.Rotation.GetRow(1).Dot(rData.Rotation.GetRow(2));
		AD[1] = lData.Rotation.GetRow(1).Dot(D);
		absC[1][0] = (float)fabs(C[1][0]);
		absC[1][1] = (float)fabs(C[1][1]);
		absC[1][2] = (float)fabs(C[1][2]);
		R = (float)fabs(AD[1]);
		R1 = rData.Width * absC[1][0] + rData.Height * absC[1][1] + rData.Depth * absC[1][2];
		R01 = lData.Height + R1;
		if (R > R01)return false;
		//A2
		C[2][0] = lData.Rotation.GetRow(2).Dot(rData.Rotation.GetRow(0));
		C[2][1] = lData.Rotation.GetRow(2).Dot(rData.Rotation.GetRow(1));
		C[2][2] = lData.Rotation.GetRow(2).Dot(rData.Rotation.GetRow(2));
		AD[2] = lData.Rotation.GetRow(2).Dot(D);
		absC[2][0] = (float)fabs(C[2][0]);
		absC[2][1] = (float)fabs(C[2][1]);
		absC[2][2] = (float)fabs(C[2][2]);
		R = (float)fabs(AD[2]);
		R1 = rData.Width * absC[2][0] + rData.Height * absC[2][1] + rData.Depth * absC[2][2];
		R01 = lData.Depth + R1;
		if (R > R01)return false;
		//B0
		R = (float)fabs(rData.Rotation.GetRow(0).Dot(D));
		R0 = lData.Width * absC[0][0] + lData.Height * absC[1][0] + lData.Depth * absC[2][0];
		R01 = R0 + rData.Width;
		if (R > R01)return false;
		//B1
		R = (float)fabs(rData.Rotation.GetRow(1).Dot(D));
		R0 = lData.Width * absC[0][1] + lData.Height * absC[1][1] + lData.Depth * absC[2][1];
		R01 = R0 + rData.Height;
		if (R > R01)return false;
		//B2
		R = (float)fabs(rData.Rotation.GetRow(2).Dot(D));
		R0 = lData.Width * absC[0][2] + lData.Height * absC[1][2] + lData.Depth * absC[2][2];
		R01 = R0 + rData.Depth;
		if (R > R01)return false;
		//A0xB0
		R = (float)fabs(AD[2] * C[1][0] - AD[1] * C[2][0]);
		R0 = lData.Height * absC[2][0] + lData.Depth * absC[1][0];
		R1 = rData.Height * absC[0][2] + rData.Depth * absC[0][1];
		R01 = R0 + R1;
		if (R > R01)return false;
		//A0xB1
		R = (float)fabs(AD[2] * C[1][1] - AD[1] * C[2][1]);
		R0 = lData.Height * absC[2][1] + lData.Depth * absC[1][1];
		R1 = rData.Width * absC[0][2] + rData.Depth * absC[0][0];
		R01 = R0 + R1;
		if (R > R01)return false;
		//A0xB2
		R = (float)fabs(AD[2] * C[1][2] - AD[1] * C[2][2]);
		R0 = lData.Height * absC[2][2] + lData.Depth * absC[1][2];
		R1 = rData.Width * absC[0][1] + rData.Height * absC[0][0];
		R01 = R0 + R1;
		if (R > R01)return false;
		//A1xB0
		R = (float)fabs(AD[0] * C[2][0] - AD[2] * C[0][0]);
		R0 = lData.Width * absC[2][0] + lData.Depth * absC[0][0];
		R1 = rData.Height * absC[1][2] + rData.Depth * absC[1][1];
		R01 = R0 + R1;
		if (R > R01)return false;
		//A1xB1
		R = (float)fabs(AD[0] * C[2][1] - AD[2] * C[0][1]);
		R0 = lData.Width * absC[2][1] + lData.Depth * absC[0][1];
		R1 = rData.Width * absC[1][2] + rData.Depth * absC[1][0];
		R01 = R0 + R1;
		if (R > R01)return false;
		//A1xB2
		R = (float)fabs(AD[0] * C[2][2] - AD[2] * C[0][2]);
		R0 = lData.Width * absC[2][2] + lData.Depth * absC[0][2];
		R1 = rData.Width * absC[1][1] + rData.Height * absC[1][0];
		R01 = R0 + R1;
		if (R > R01)return false;
		//A2xB0
		R = (float)fabs(AD[1] * C[0][0] - AD[0] * C[1][0]);
		R0 = lData.Width * absC[1][0] + lData.Height * absC[0][0];
		R1 = rData.Height * absC[2][2] + rData.Depth * absC[2][1];
		R01 = R0 + R1;
		if (R > R01)return false;
		//A2xB1
		R = (float)fabs(AD[1] * C[0][1] - AD[0] * C[1][1]);
		R0 = lData.Width * absC[1][1] + lData.Height * absC[0][1];
		R1 = rData.Width * absC[2][2] + rData.Depth * absC[2][0];
		R01 = R0 + R1;
		if (R > R01)return false;
		//A2xB2
		R = (float)fabs(AD[1] * C[0][2] - AD[0] * C[1][2]);
		R0 = lData.Width * absC[1][2] + lData.Height * absC[0][2];
		R1 = rData.Width * absC[2][1] + rData.Height * absC[2][0];
		R01 = R0 + R1;
		if (R > R01)return false;
		return true;
	}
	bool DefaultCollisionCalculator::IsCollide(SegmentData lData, TriangleData rData)
	{
		Vector3 e0 = rData.Vertice[1] - rData.Vertice[0];
		Vector3 e1 = rData.Vertice[2] - rData.Vertice[0];
		Vector3 vNormal = e0.Cross(e1);

		Vector3 vDirection = lData.A - lData.B;
		float D = vNormal.Dot(vDirection);
		float a0 = vNormal.Dot(rData.Vertice[0] - lData.A);
		float fT = a0 / D;
		if (fT < 0.0f || fT > 1.0f)
		{
			return false;
		}
		return true;
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(SegmentData lData, TriangleData rData)
	{
		std::vector<Vector3> ret;
		Vector3 e0 = rData.Vertice[1] - rData.Vertice[0];
		Vector3 e1 = rData.Vertice[2] - rData.Vertice[0];
		Vector3 vNormal = e0.Cross(e1);

		Vector3 vDirection = lData.A - lData.B;
		float D = vNormal.Dot(vDirection);
		float a0 = vNormal.Dot(rData.Vertice[0] - lData.A);
		float fT = a0 / D;
		if (fT < 0.0f || fT > 1.0f)
		{
			return ret;
		}
		ret.push_back(lData.A + vDirection * fT);
		return ret;
	}
	bool DefaultCollisionCalculator::IsCollide(AABBData lData, RayData rData)
	{
		return IsCollide(rData, lData);
	}
	bool DefaultCollisionCalculator::IsIn(AABBData lData, RayData rData)
	{
		return false;
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(AABBData lData, RayData rData)
	{
		return GetIntersections(rData, lData);
	}
	bool DefaultCollisionCalculator::IsCollide(OBBData lData, RayData rData)
	{
		return IsCollide(rData, lData);
	}
	bool DefaultCollisionCalculator::IsIn(OBBData lData, RayData rData)
	{
		return false;
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(OBBData lData, RayData rData)
	{
		return GetIntersections(rData, lData);
	}
	bool DefaultCollisionCalculator::IsCollide(SphereData lData, RayData rData)
	{
		return IsCollide(rData, lData);
	}
	bool DefaultCollisionCalculator::IsIn(SphereData lData, RayData rData)
	{
		return false;
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(SphereData lData, RayData rData)
	{
		return GetIntersections(rData, lData);
	}
	bool DefaultCollisionCalculator::IsCollide(VolumeData lData, VolumeData rData)
	{
		Vector3 lPos = lData.Position;
		Vector3 rPos = rData.Position;

		float xDiff = lPos.GetX() - rPos.GetX();
		float yDiff = lPos.GetY() - rPos.GetY();
		float zDiff = lPos.GetZ() - rPos.GetZ();

		return (xDiff * xDiff + yDiff * yDiff + zDiff * zDiff) < FDelta;
	}
	bool DefaultCollisionCalculator::IsIn(VolumeData lData, VolumeData rData)
	{
		return IsCollide(lData, rData);
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(VolumeData lData, VolumeData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{lData.Position} : std::vector<Vector3>{};
	}
	bool DefaultCollisionCalculator::IsCollide(VolumeData lData, LineData rData)
	{
		float distance = (lData.Position - rData.Vertex).Dot(rData.Direction);
		Vector3 perpendicularVertex = rData.Position + rData.Direction * distance;
		Vector3 PerpendicularVector = lData.Position - perpendicularVertex;

		return PerpendicularVector.LengthSquare() < FDelta;
	}
	bool DefaultCollisionCalculator::IsIn(VolumeData lData, LineData rData)
	{
		return IsCollide(lData, rData);
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(VolumeData lData, LineData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{lData.Position} : std::vector<Vector3>{};
	}
	bool DefaultCollisionCalculator::IsCollide(VolumeData lData, RayData rData)
	{
		 //get the vector from the ray's origin to the volume's position
		Vector3 toVolume = lData.Position - rData.Origin;

		 //calculate the dot product between toVolume and ray direction
		float dot = toVolume.Dot(rData.Direction);

		 //if the dot product is negative, the volume is not on the ray
		if (dot < -FDelta)
		{
			return false;
		}

		 //calculate the distance between the ray's origin and the volume's position
		float distance = toVolume.Length();

		 //if the distance is greater than the dot product, the volume is not on the ray
		if (distance - dot > FDelta)
		{
			return false;
		}

		 //if both checks pass, the volume is on the ray
		return true;
	}
	bool DefaultCollisionCalculator::IsIn(VolumeData lData, RayData rData)
	{
		return IsCollide(lData, rData);
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(VolumeData lData, RayData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{lData.Position} : std::vector<Vector3>{};
	}
	bool DefaultCollisionCalculator::IsCollide(VolumeData lData, SegmentData rData)
	{
		float len = (rData.Position - rData.Position).Length();
		float dis1 = (rData.Position - lData.Position).Length();
		float dis2 = (rData.Position - lData.Position).Length();

		return (dis1 + dis2 - len) < FDelta;
	}
	bool DefaultCollisionCalculator::IsIn(VolumeData lData, SegmentData rData)
	{
		return IsCollide(lData, rData);
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(VolumeData lData, SegmentData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{lData.Position} : std::vector<Vector3>{};
	}
	bool DefaultCollisionCalculator::IsCollide(VolumeData lData, PlaneData rData)
	{
		float dotProduct = lData.Position.GetX() * rData.A + lData.Position.GetY() * rData.B + lData.Position.GetZ() * rData.C + rData.D;
		return abs(dotProduct) < FDelta;
	}
	bool DefaultCollisionCalculator::IsIn(VolumeData lData, PlaneData rData)
	{
		return IsCollide(lData, rData);
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(VolumeData lData, PlaneData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{lData.Position} : std::vector<Vector3>{};
	}
	bool DefaultCollisionCalculator::IsCollide(RayData lData, VolumeData rData)
	{
		return IsCollide(rData, lData);
	}
	bool DefaultCollisionCalculator::IsIn(RayData lData, VolumeData rData)
	{
		return false;
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(RayData lData, VolumeData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{rData.Position} : std::vector<Vector3>{};
	}
	bool DefaultCollisionCalculator::IsCollide(RayData lData, RayData rData)
	{
		float dotProduct = lData.Direction.Dot(rData.Direction);
		if (abs(dotProduct - 1.0f) < FDelta)
		{
			Vector3 direction = rData.Position - rData.Position;
			direction.Normalize();

			float dotProduct = lData.Direction.Dot(rData.Direction);
			if (abs(dotProduct - 1.0f) < FDelta)
			{
				return true;
			}
		}
		else
			return false;
	}
	bool DefaultCollisionCalculator::IsIn(RayData lData, RayData rData)
	{
		if (abs((lData.Origin - rData.Origin).LengthSquare()) < FDelta)
		{
			if (abs(lData.Direction.Cross(rData.Direction).LengthSquare()) < FDelta)
			{
				return true;
			}
		}
		return false;
	}
	bool DefaultCollisionCalculator::IsCollide(AABBData lData, VolumeData rData)
	{
		return IsCollide(rData, lData);
	}
	bool DefaultCollisionCalculator::IsIn(AABBData lData, VolumeData rData)
	{
		return IsCollide(lData, rData);
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(AABBData lData, VolumeData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{rData.Position} : std::vector<Vector3>{};
	}
	bool DefaultCollisionCalculator::IsCollide(AABBData lData, AABBData rData)
	{
		if (lData.Max.GetX() < rData.Min.GetX() || lData.Min.GetX() > rData.Max.GetX())
			return false;
		if (lData.Max.GetY() < rData.Min.GetY() || lData.Min.GetY() > rData.Max.GetY())
			return false;
		if (lData.Max.GetZ() < rData.Min.GetZ() || lData.Min.GetZ() > rData.Max.GetZ())
			return false;
		return true;
	}
	bool DefaultCollisionCalculator::IsIn(AABBData lData, AABBData rData)
	{
		if (rData.Min.GetX() >= lData.Min.GetX() && rData.Max.GetX() <= lData.Max.GetX() &&
			rData.Min.GetY() >= lData.Min.GetY() && rData.Max.GetY() <= lData.Max.GetY() &&
			rData.Min.GetZ() >= lData.Min.GetZ() && rData.Max.GetZ() <= lData.Max.GetZ())
			return true;

		return false;
	}
	bool DefaultCollisionCalculator::IsCollide(AABBData lData, OBBData rData)
	{
		// Calculate the eight vertices of the OBB
		Vector3 vertices[8];
		vertices[0] = rData.Position + Vector3(-rData.Width / 2, -rData.Height / 2, rData.Depth / 2) * rData.Rotation;
		vertices[1] = rData.Position + Vector3(rData.Width / 2, -rData.Height / 2, rData.Depth / 2) * rData.Rotation;
		vertices[2] = rData.Position + Vector3(rData.Width / 2, rData.Height / 2, rData.Depth / 2) * rData.Rotation;
		vertices[3] = rData.Position + Vector3(-rData.Width / 2, rData.Height / 2, rData.Depth / 2) * rData.Rotation;
		vertices[4] = rData.Position + Vector3(-rData.Width / 2, -rData.Height / 2, -rData.Depth / 2) * rData.Rotation;
		vertices[5] = rData.Position + Vector3(rData.Width / 2, -rData.Height / 2, -rData.Depth / 2) * rData.Rotation;
		vertices[6] = rData.Position + Vector3(rData.Width / 2, rData.Height / 2, -rData.Depth / 2) * rData.Rotation;
		vertices[7] = rData.Position + Vector3(-rData.Width / 2, rData.Height / 2, -rData.Depth / 2) * rData.Rotation;

		// Check if any of the vertices of the OBB are outside the AABB
		for (int i = 0; i < 8; i++) {
			if (vertices[i].GetX() < lData.Min.GetX() || vertices[i].GetX() > lData.Max.GetX() ||
				vertices[i].GetY() < lData.Min.GetY() || vertices[i].GetY() > lData.Max.GetY() ||
				vertices[i].GetZ() < lData.Min.GetZ() || vertices[i].GetZ() > lData.Max.GetZ()) {
				return false;
			}
		}

		// All vertices of the OBB are inside the AABB
		return true;
	}
	bool DefaultCollisionCalculator::IsIn(AABBData lData, OBBData rData)
	{
		Vector3 lMin = lData.Min;
		Vector3 lMax = lData.Max;
		Vector3 rPos = rData.Position;
		Matrix33 rRot = rData.Rotation;
		float rWidth = rData.Width;
		float rHeight = rData.Height;
		float rDepth = rData.Depth;

		Vector3 rCorners[8];
		rCorners[0] = Vector3(-rWidth / 2.0f, -rHeight / 2.0f, -rDepth / 2.0f);
		rCorners[1] = Vector3(-rWidth / 2.0f, -rHeight / 2.0f, rDepth / 2.0f);
		rCorners[2] = Vector3(-rWidth / 2.0f, rHeight / 2.0f, -rDepth / 2.0f);
		rCorners[3] = Vector3(-rWidth / 2.0f, rHeight / 2.0f, rDepth / 2.0f);
		rCorners[4] = Vector3(rWidth / 2.0f, -rHeight / 2.0f, -rDepth / 2.0f);
		rCorners[5] = Vector3(rWidth / 2.0f, -rHeight / 2.0f, rDepth / 2.0f);
		rCorners[6] = Vector3(rWidth / 2.0f, rHeight / 2.0f, -rDepth / 2.0f);
		rCorners[7] = Vector3(rWidth / 2.0f, rHeight / 2.0f, rDepth / 2.0f);

		for (int i = 0; i < 8; i++) {
			Vector3 corner = rCorners[i];
			Vector3 rotatedCorner = corner * rRot + rPos;
			if (rotatedCorner.GetX() < lMin.GetX() || rotatedCorner.GetX() > lMax.GetX() ||
				rotatedCorner.GetY() < lMin.GetY() || rotatedCorner.GetY() > lMax.GetY() ||
				rotatedCorner.GetZ() < lMin.GetZ() || rotatedCorner.GetZ() > lMax.GetZ()) {
				return false;
			}
		}

		return true;
	}
	bool DefaultCollisionCalculator::IsCollide(AABBData lData, SphereData rData)
	{
		if (rData.Position.GetX() - lData.Min.GetX() > rData.Radius || lData.Max.GetX() - rData.Position.GetX() > rData.Radius)
			return false;
		if (rData.Position.GetY() - lData.Min.GetY() > rData.Radius || lData.Max.GetY() - rData.Position.GetY() > rData.Radius)
			return false;
		if (rData.Position.GetZ() - lData.Min.GetZ() > rData.Radius || lData.Max.GetZ() - rData.Position.GetZ() > rData.Radius)
			return false;

		return true;
	}
	bool DefaultCollisionCalculator::IsIn(AABBData lData, SphereData rData)
	{
		Vector3 vec = rData.Position - lData.Position;
		if (
			vec.GetX() - rData.Radius < lData.Min.GetX() || lData.Max.GetX() < vec.GetX() + rData.Radius ||
			vec.GetY() - rData.Radius < lData.Min.GetY() || lData.Max.GetY() < vec.GetY() + rData.Radius ||
			vec.GetZ() - rData.Radius < lData.Min.GetZ() || lData.Max.GetZ() < vec.GetZ() + rData.Radius
			)
		{
			return false;
		}
		return true;
	}
	bool DefaultCollisionCalculator::IsCollide(OBBData lData, VolumeData rData)
	{
		return IsCollide(rData, lData);
	}
	bool DefaultCollisionCalculator::IsIn(OBBData lData, VolumeData rData)
	{
		return IsCollide(lData, rData);
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(OBBData lData, VolumeData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{rData.Position} : std::vector<Vector3>{};
	}
	bool DefaultCollisionCalculator::IsCollide(OBBData lData, SphereData rData)
	{
		Vector3 vDiff = rData.Position - lData.Position;

		float halfValue[3]{ lData.Depth / 2.0f, lData.Height / 2.0f, lData.Width / 2.0f };

		Matrix33 matOBBRotation = lData.Rotation;
		matOBBRotation = matOBBRotation.Transpose();

		for (int i = 0; i < 3; ++i)
		{
			float fProj = vDiff.Dot(matOBBRotation.GetRow(i));
			if (abs(fProj) < rData.Radius + halfValue[i])
			{
				return false;
			}
		}
		return true;
	}
	bool DefaultCollisionCalculator::IsCollide(SphereData lData, VolumeData rData)
	{
		return IsCollide(rData, lData);
	}
	bool DefaultCollisionCalculator::IsIn(SphereData lData, VolumeData rData)
	{
		return IsCollide(lData, rData);
	}
	std::vector<Vector3> DefaultCollisionCalculator::GetIntersections(SphereData lData, VolumeData rData)
	{
		return IsCollide(lData, rData) ? std::vector<Vector3>{rData.Position} : std::vector<Vector3>{};
	}
	bool DefaultCollisionCalculator::IsCollide(SphereData lData, AABBData rData)
	{
		return IsCollide(rData, lData);
	}
	bool DefaultCollisionCalculator::IsIn(SphereData lData, AABBData rData)
	{
		Vector3 lCenter = lData.Position;
		float lRadius = lData.Radius;

		Vector3 rMin = rData.Min;
		Vector3 rMax = rData.Max;

		float d = 0.0f;
		d = max(d, fabs(lCenter.GetX() - rMin.GetX()));
		d = max(d, fabs(lCenter.GetY() - rMin.GetY()));
		d = max(d, fabs(lCenter.GetZ() - rMin.GetZ()));
		d = max(d, fabs(rMax.GetX() - lCenter.GetX()));
		d = max(d, fabs(rMax.GetY() - lCenter.GetY()));
		d = max(d, fabs(rMax.GetZ() - lCenter.GetZ()));

		return d <= lRadius;
	}
	bool DefaultCollisionCalculator::IsCollide(SphereData lData, SphereData rData)
	{
		Vector3 vec = lData.Position - rData.Position;
		return vec.Length() < lData.Radius + rData.Radius;
	}
	bool DefaultCollisionCalculator::IsIn(SphereData lData, SphereData rData)
	{
		Vector3 vec = lData.Position - rData.Position;
		float distance = vec.Length();

		return distance + rData.Radius < lData.Radius;
	}
}
