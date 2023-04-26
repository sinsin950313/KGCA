#include "CollisionTree.h"

namespace SSB
{
	//std::vector<Volume<2>*> QuadTreeDivider::Divide(const Volume<2>& volume)
	//{
	//	auto center = volume.GetCenter();
	//	auto vertexes = volume.GetVertexes();

	//	float left = vertexes[0]->Get(0) + center.Get(0);
	//	float top = vertexes[0]->Get(1) + center.Get(1);
	//	float right = vertexes[0]->Get(0) + center.Get(0);
	//	float bottom = vertexes[0]->Get(1) + center.Get(1);

	//	for (auto vertex : vertexes)
	//	{
	//		left = fminf(left, vertex->Get(0) + center.Get(0));
	//		top = fmaxf(top, vertex->Get(1) + center.Get(1));
	//		right = fmaxf(right, vertex->Get(0) + center.Get(0));
	//		bottom = fminf(bottom, vertex->Get(1) + center.Get(1));
	//	}

	//	float newWidth = (right - left) / 2;
	//	float newHeight = (top - bottom) / 2;

	//	// ---------
	//	// | 0 | 1 |
	//	// ---------
	//	// | 2 | 3 |
	//	// ---------
	//	std::vector<Volume<2>*> ret;
	//	{
	//		float centerX = center.Get(0) - newWidth / 2;
	//		float centerY = center.Get(1) + newHeight / 2;
	//		ret.push_back(new SSB::Rectangle(centerX, centerY, newWidth, newHeight));
	//	}
	//	{
	//		float centerX = center.Get(0) + newWidth / 2;
	//		float centerY = center.Get(1) + newHeight / 2;
	//		ret.push_back(new SSB::Rectangle(centerX, centerY, newWidth, newHeight));
	//	}
	//	{
	//		float centerX = center.Get(0) - newWidth / 2;
	//		float centerY = center.Get(1) - newHeight / 2;
	//		ret.push_back(new SSB::Rectangle(centerX, centerY, newWidth, newHeight));
	//	}
	//	{
	//		float centerX = center.Get(0) + newWidth / 2;
	//		float centerY = center.Get(1) - newHeight / 2;
	//		ret.push_back(new SSB::Rectangle(centerX, centerY, newWidth, newHeight));
	//	}

	//	return ret;
	//}

	//std::vector<Volume<3>*> OctTreeDivider::Divide(const Volume<3>& volume)
	//{
	//	auto vertexes = volume.GetVertexes();
	//	auto center = volume.GetCenter();

	//	float left = vertexes[0]->Get(0) + center.Get(0);
	//	float top = vertexes[0]->Get(1) + center.Get(1);
	//	float front = vertexes[0]->Get(2) + center.Get(2);
	//	float right = vertexes[0]->Get(0) + center.Get(0);
	//	float bottom = vertexes[0]->Get(1) + center.Get(1);
	//	float back = vertexes[0]->Get(2) + center.Get(2);

	//	for (auto vertex : vertexes)
	//	{
	//		left = fminf(left, vertex->Get(0) + center.Get(0));
	//		top = fmaxf(top, vertex->Get(1) + center.Get(1));
	//		front = fminf(front, vertex->Get(2) + center.Get(2));
	//		right = fmaxf(right, vertex->Get(0) + center.Get(0));
	//		bottom = fminf(bottom, vertex->Get(1) + center.Get(1));
	//		back = fmaxf(back, vertex->Get(2) + center.Get(2));
	//	}

	//	float newWidth = (right - left) / 2;
	//	float newHeight = (top - bottom) / 2;
	//	float newDepth = (back - front) / 2;

	//	//   5----6
	//	//  /|   /|
	//	// 4----7 |
	//	// | |  | |
	//	// | 1--+-2
	//	// |/   |/
	//	// 0----3
	//	std::vector<Volume<3>*> ret;
	//	{
	//		float x = center.Get(0) - newWidth / 2;
	//		float y = center.Get(1) - newHeight / 2;
	//		float z = center.Get(2) - newDepth / 2;
	//		ret.push_back(new Box(Vector3D(Vector3DData{ x, y, z }), newWidth, newHeight, newDepth));
	//	}
	//	{
	//		float x = center.Get(0) - newWidth / 2;
	//		float y = center.Get(1) - newHeight / 2;
	//		float z = center.Get(2) + newDepth / 2;
	//		ret.push_back(new Box(Vector3D(Vector3DData{ x, y, z }), newWidth, newHeight, newDepth));
	//	}
	//	{
	//		float x = center.Get(0) + newWidth / 2;
	//		float y = center.Get(1) - newHeight / 2;
	//		float z = center.Get(2) + newDepth / 2;
	//		ret.push_back(new Box(Vector3D(Vector3DData{ x, y, z }), newWidth, newHeight, newDepth));
	//	}
	//	{
	//		float x = center.Get(0) + newWidth / 2;
	//		float y = center.Get(1) - newHeight / 2;
	//		float z = center.Get(2) - newDepth / 2;
	//		ret.push_back(new Box(Vector3D(Vector3DData{ x, y, z }), newWidth, newHeight, newDepth));
	//	}
	//	{
	//		float x = center.Get(0) - newWidth / 2;
	//		float y = center.Get(1) + newHeight / 2;
	//		float z = center.Get(2) - newDepth / 2;
	//		ret.push_back(new Box(Vector3D(Vector3DData{ x, y, z }), newWidth, newHeight, newDepth));
	//	}
	//	{
	//		float x = center.Get(0) - newWidth / 2;
	//		float y = center.Get(1) + newHeight / 2;
	//		float z = center.Get(2) + newDepth / 2;
	//		ret.push_back(new Box(Vector3D(Vector3DData{ x, y, z }), newWidth, newHeight, newDepth));
	//	}
	//	{
	//		float x = center.Get(0) + newWidth / 2;
	//		float y = center.Get(1) + newHeight / 2;
	//		float z = center.Get(2) + newDepth / 2;
	//		ret.push_back(new Box(Vector3D(Vector3DData{ x, y, z }), newWidth, newHeight, newDepth));
	//	}
	//	{
	//		float x = center.Get(0) + newWidth / 2;
	//		float y = center.Get(1) + newHeight / 2;
	//		float z = center.Get(2) - newDepth / 2;
	//		ret.push_back(new Box(Vector3D(Vector3DData{ x, y, z }), newWidth, newHeight, newDepth));
	//	}
	//	return ret;
	//}
}
