#include "Volume.h"

Volume::~Volume()
{
	for (auto iter = _vertexes.begin(); iter != _vertexes.end(); ++iter)
	{
		delete (*iter);
	}
}

void Volume::Resize(float radius)
{
	float ratio = radius / _roughVolume.GetRadius();
	for (auto iter = _vertexes.begin(); iter != _vertexes.end(); ++iter)
	{
		Vector2D tmp = (*(*iter) * ratio);
		(*iter)->Repoint(tmp.GetX(), tmp.GetY());
	}

	_roughVolume.Resize(radius);
}

void Volume::Reposition(float centerX, float centerY)
{
	_roughVolume.Reposition(centerX, centerY);
}

bool Volume::IsIn(const Vector2D& coordinate, const Vector2D& v) const
{
	Vector2D absolute = v + coordinate;
	Vector2D relative = absolute - GetCenter();
	return _roughVolume.IsIn(relative);
}

bool Volume::IsCollide(const Volume& volume) const
{
	const std::vector<Vector2D*>& checkVolumeVectexes = volume.GetVertexes();
	for (auto iter = checkVolumeVectexes.begin(); iter != checkVolumeVectexes.end(); ++iter)
	{
		if (IsIn(volume.GetCenter(), **iter))
		{
			return true;
		}
	}
	return false;
}

bool Volume::RoughVolume::IsIn(const Vector2D& v) const
{
	return v.Length() <= _radius;
}
