#pragma once

#include "VolumeInterface1.h"
#include "Matrix.h"
#include "Vector.h"

namespace SSB
{
	//template<typename HMatrix, typename Vector>
	//class Volume1 : public VolumeInterface1<HMatrix, Vector>
	//{
	//protected:
	//	Volume1<HMatrix, Vector>* _parent;
	//	float _radius;
	//	HMatrix* _matrix;

	//public:
	//	bool IsIn(const Vector& v) const;
	//	bool IsCollide(const Volume1& volume) const;
	//	const std::vector<Vector*>& GetVertexes() const { return _vertexes; }
	//	const Vector GetCenter() const { return _matrix->GetRow(); }

	//protected:
	//	const Vector& GetCenter() const { return _parent->GetMatrix().GetRow(0); }
	//	float GetRadius() const { return _radius; }

	//public:
	//	virtual void Print() const = 0;
	//	virtual void Resize(float radius) { _radius = radius; }
	//	virtual void Reposition(Vector pos) { _center = pos; }
	//};
}
