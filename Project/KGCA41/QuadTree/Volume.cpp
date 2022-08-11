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
	_roughVolume.Resize(radius);
}

void Volume::Reposition(float centerX, float centerY)
{
	_roughVolume.Reposition(centerX, centerY);
}

bool Volume::IsIn(const Point& p) const
{
	return _roughVolume.IsIn(p);
}

bool Volume::IsCollide(const Volume& volume) const
{
	const std::vector<Point*>& checkVolumeVectexes = volume.GetVertexes();
	for (auto iter = checkVolumeVectexes.begin(); iter != checkVolumeVectexes.end(); ++iter)
	{
		if (IsIn(**iter))
		{
			return true;
		}
	}
	return false;
}

bool Volume::RoughVolume::IsIn(const Point& p) const
{
	return _center.Distance(p) <= _radius;
}
