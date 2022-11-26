//#include "PhysicsVector.h"
//#include <iostream>
//#include "Vector.h"
//#include "Matrix.h"
//#include "HCCalculator.h"
//
//using namespace SSB;
//
//int main()
//{
//	//SSB::Vector2D vec;
//	//*vec[0] = 10;
//	//*vec[1] = 20;
//	//std::cout << vec.LengthSquare() << std::endl;
//	//std::cout << vec.Length() << std::endl;
//	//std::cout << vec.Dot(vec) << std::endl;
//
//	//SSB::Vector2D tmp = vec + vec;
//	//tmp = tmp - vec;
//	//tmp = tmp * 4;
//	//tmp = tmp / 2;
//	//tmp = SSB::Vector2D();
//
//	//vec.Normalize();
//	//SSB::Vector2D identity = vec.Identity();
//	//vec.Clear();
//
//	//SSB::Vector2D varVec(2, 1.0f, 2.0f);
//
//	//SSB::Vector3DData aVecData{ 1, 1, 0 };
//	//SSB::Vector3D aVec(std::move(aVecData));
//	//SSB::Vector3DData bVecData{ 0, 1, 1 };
//	//SSB::Vector3D bVec(std::move(bVecData));
//	//auto crossResult = bVec.Cross(aVec);
//
//	{
//		Vector2 v2(1, 2);
//		auto plus = v2 + v2;
//		auto minus = v2 - v2;
//		auto sMul = v2 * 10;
//		auto sDiv = v2 / 10;
//		auto dot = v2.Dot(v2);
//		auto length = v2.Length();
//		auto normal = v2.Normal();
//		v2.Normalize();
//		auto tmp = v2;
//		v2 += v2;
//		v2 -= tmp;
//		Float2 f = v2;
//		v2.Clear();
//		int i = 0;
//	}
//	{
//		Vector3 v3(1, 2, 3);
//		auto plus = v3 + v3;
//		auto minus = v3 - v3;
//		auto sMul = v3 * 10;
//		auto sDiv = v3 / 10;
//		auto dot = v3.Dot(v3);
//		auto length = v3.Length();
//		auto normal = v3.Normal();
//		auto cross = Vector3(1, 0, 0).Cross(Vector3(0, 1, 0));
//		v3.Normalize();
//		auto tmp = v3;
//		v3 += v3;
//		v3 -= tmp;
//		Float3 f = v3;
//		v3.Clear();
//		int i = 0;
//	}
//	{
//		HVector3 hv3(1, 2, 3);
//		auto dot = hv3.Dot(hv3);
//		auto normal = hv3.Normal();
//		Float2 f = hv3;
//		Vector2 v = hv3;
//		hv3.Normalize();
//		int i = 0;
//	}
//	{
//		HVector4 hv4(1, 2, 3, 4);
//		auto dot = hv4.Dot(hv4);
//		//auto cross = HVector4(1, 0, 0, 0).Cross(HVector4(0, 1, 0, 0));
//		auto normal = hv4.Normal();
//		Float3 f = hv4;
//		Vector3 v = hv4;
//		hv4.Normalize();
//		int i = 0;
//	}
//	{
//		Matrix22 m22{
//			1, 2,
//			3, 4
//		};
//		auto plus = m22 + m22;
//		auto minus = m22 - m22;
//		auto sMul = m22 * 10;
//		auto mMul = m22 * m22;
//		auto tmp = m22;
//		m22 += tmp;
//		m22 -= tmp;
//		auto trans = m22.Transpose();
//		auto inverse = m22.Inverse();
//		auto row = m22.GetRow(0);
//		auto col = m22.GetColumn(0);
//		Float22 f = m22;
//		m22.Identity();
//		int i = 0;
//	}
//	{
//		Matrix33 m33{
//			1, 2, 3,
//			4, 5, 6,
//			7, 8, 9
//		};
//
//		auto plus = m33 + m33;
//		auto minus = m33 - m33;
//		auto sMul = m33 * 10;
//		auto mMul = m33 * m33;
//		auto tmp = m33;
//		m33 += tmp;
//		m33 -= tmp;
//		auto trans = m33.Transpose();
//		auto row = m33.GetRow(0);
//		auto col = m33.GetColumn(0);
//		Float33 f = m33;
//		m33.Identity();
//		int i = 0;
//	}
//	{
//		HMatrix33 hm33{
//			1, 2, 3,
//			4, 5, 6,
//			7, 8, 9
//		};
//
//		auto mMul = hm33 * hm33;
//		auto inverse = hm33.Inverse();
//		auto row = hm33.GetRow(0);
//		auto col = hm33.GetColumn(0);
//		Float22 f22 = hm33;
//		Float2 f2 = hm33;
//		Matrix22 m22 = hm33;
//		Vector2 v2 = hm33;
//		hm33.Identity();
//		HMatrix33::Translate({ 10, 20 });
//		HMatrix33::Rotate(3.14 / 2);
//		HMatrix33::Scale({ 1, 2 });
//		int i = 0;
//	}
//	{
//		HMatrix44 hm44{
//			1, 2, 3, 4,
//			5, 6, 7, 8,
//			9, 10, 11, 12,
//			13, 14, 15, 16
//		};
//
//		auto mMul = hm44 * hm44;
//		auto inverse = hm44.Inverse();
//		auto row = hm44.GetRow(0);
//		auto col = hm44.GetColumn(0);
//		Float33 f22 = hm44;
//		Float3 f2 = hm44;
//		Matrix33 m22 = hm44;
//		Vector3 v2 = hm44;
//		hm44.Identity();
//		HMatrix44::Translate({ 10, 20 });
//		HMatrix44::RotateFromXAxis(3.14 / 2);
//		HMatrix44::RotateFromYAxis(3.14 / 2);
//		HMatrix44::RotateFromZAxis(3.14 / 2);
//		HMatrix44::Scale({ 1, 2, 3 });
//		auto lookAt = HMatrix44::LookAtMatrix({ 0, 0, 0 }, { 10, 10, 10 }, { 0, 1, 0 });
//		int i = 0;
//	}
//	{
//		auto v2m22 = Vector2(1, 2) * Matrix22(1, 2, 3, 4);
//		auto v3m33 = Vector3(1, 2, 3) * Matrix33(1, 2, 3, 4, 5, 6, 7, 8, 9);
//		auto hv3hm33 = HVector3(1, 2, 3) * HMatrix33(1, 2, 3, 4, 5, 6, 7, 8, 9);
//		auto hv4hm44 = HVector4(1, 2, 3, 4) * HMatrix44(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
//		int i = 0;
//	}
//	{
//		Vector3 xVector{ 10, 0, 0 };
//		Vector3 zVector = Rotate(xVector, { 0, 10, 0 }, 3.14f / 2.0f);
//
//		Vector3 vec{ 1, 0, 1 };
//		Vector3 newVec = Rotate(vec, { 0, 1, 0 }, 3.14f / 2.0f);
//		int i = 0;
//	}
//	{
//		Quaternion quaternion = Quaternion::GetRotateQuaternion({ 1, 0, 0 }, { 0, 1, 0 });
//		auto to = quaternion * Vector3{ 1, 0, 0 } * quaternion.Conjugate();
//		int i = 0;
//	}
//}