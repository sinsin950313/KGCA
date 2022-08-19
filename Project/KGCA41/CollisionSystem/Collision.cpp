#include "Collision.h"
#include "Volume.h"
#include "Rectangle.h"

//template<int dimension>
//bool Collision::IsCollide(const Volume<dimension>& r1, const Volume<dimension>& r2)
//{
//	return (r1.IsCollide(r2)) || (r2.IsCollide(r1));
//}

//bool Collision::IsOverlap(const Rectangle& r1, const Rectangle& r2)
//{
//	Rectangle tmp = (r1 & r2);
//	return tmp == r1 || tmp == r2;
//}
//
//Rectangle Collision::GetCollision(const Rectangle& r1, const Rectangle& r2)
//{
//	return r1 & r2;
//}
//
//bool Collision::IsCollide(const Circle& cir1, const Circle& cir2)
//{
//	return cir1 && cir2;
//}
