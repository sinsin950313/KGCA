#pragma once

#include "DXDrawableInterface.h"
#include "Matrix.h"
#include "Model.h"
#include "Volume1.h"
#include "VolumeType.h"

namespace SSB
{
	struct ObjectToWorldTransformData
	{
		Float44 World;
	};

	class DXObject : public DXDrawableInterface
	{
	private:
		Vertex1Volume DefaultVolume;

	private:
		//For debug direction
		//Model* _direction;

		Model* _model;
		Volume1* _volume;
		ID3D11Buffer* _objectToWorldTransformBuffer;
		ObjectToWorldTransformData _objectToWorldTransformData;

		DXObject* _parent;
		std::vector<DXObject*> _childObjectList;

	public:
		DXObject();
		virtual ~DXObject();

	private:
		bool CreateObjectTransformBuffer();
		void UpdateObjectTransformBuffer();

	private:
		void SetParent(DXObject* object);

	public:
		void SetModel(Model* model);
		void AddChildObject(DXObject* child);
		void SetVolume(Volume1* volume);
		void Move(Vector3 vec);
		void SetPosition(Vector3 vec);
		//void Rotate(float yaw, float pitch, float roll);
		Vector3 GetPosition();
		Vector3 GetDirection();
		HMatrix44 GetWorldMatrix();

	public:
		operator OBBData();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void Draw(ID3D11DeviceContext* dc) override;
	};
}
