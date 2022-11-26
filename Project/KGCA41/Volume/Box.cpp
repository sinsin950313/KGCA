#include "Box.h"

namespace SSB
{
    BoxVertexFactory::BoxVertexFactory(float width, float height, float depth)
        : _width(width), _height(height), _depth(depth)
    {
    }

    std::vector<Vector3D*> BoxVertexFactory::operator()()
    {
        std::vector<Vector3D*> ret;

        //   5----6
        //  /|   /|
        // 4----7 |
        // | |  | |
        // | 1--+-2
        // |/   |/
        // 0----3
        int x[8]{ -1, -1, 1, 1, -1, -1, 1, 1 };
        int y[8]{ -1, -1, -1, -1, 1, 1, 1, 1 };
        int z[8]{ -1, 1, 1, -1, -1, 1, 1, -1 };

        for (int i = 0; i < 8; ++i)
        {
            Vector3D* vec = new Vector3D(Vector3DData{ x[i] * (_width / 2), y[i] * (_height / 2), z[i] * (_depth / 2) });
            ret.push_back(vec);
        }

        return ret;
    }

    BoxVolume::BoxVolume(Vector3D&& center, float width, float height, float depth)
        //Perfect Forwarding problem
        : Volume(std::forward<Vector3D>(center), sqrt(width* width + height * height + depth * depth) / 2, BoxVertexFactory(width, height, depth))
        , _ltf(Vector3DData{ -width / 2, height / 2, -depth / 2 })
        , _rbb(Vector3DData{ width / 2, -height / 2, depth / 2 })
    {
    }

    void BoxVolume::Resize(float width, float height, float depth)
    {
        Volume::Resize(sqrt(width * width + height * height + depth * depth) / 2);
        *_ltf[0] = -width / 2;
        *_ltf[1] = height / 2;
        *_ltf[2] = -depth / 2;

        *_rbb[0] = width / 2;
        *_rbb[1] = -height / 2;
        *_rbb[2] = depth / 2;
    }

    bool BoxVolume::IsIn(const Vector3D& coordinate, const Vector3D& v) const
    {
        if (Volume::IsIn(coordinate, v))
        {
            Vector3D absolute = v + coordinate;
            Vector3D relative = absolute - GetCenter();

            float x = relative.Get(0);
            float y = relative.Get(1);
            float z = relative.Get(2);
            return _ltf.Get(0) <= x && x <= _rbb.Get(0) && _rbb.Get(1) <= y && y <= _ltf.Get(1) && _ltf.Get(2) <= z && z <= _rbb.Get(2);
        }

        return false;
    }

    void BoxVolume::Print() const
    {
        auto vertexes = GetVertexes();
        auto center = GetCenter();
        int i = 0;
        for (auto vertex = vertexes.begin(); vertex != vertexes.end(); ++vertex)
        {
            std::cout << "( ";
            for (int i = 0; i < 3; ++i)
            {
                std::cout << (*vertex)->Get(i) + center.Get(i) << " ";
            }
            std::cout << ") ";
            ++i;
            if (i == 4)
            {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl << std::endl;
    }
}
