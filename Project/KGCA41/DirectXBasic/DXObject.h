#pragma once

#include "DXDrawableInterface.h"
#include "Matrix.h"
#include "Model.h"
#include "Volume1.h"
#include "VolumeType.h"
#include "Serializeable.h"

namespace SSB
{
	struct ObjectToWorldTransformData
	{
		Float44 World;
	};

	class DXObject : public DXDrawableInterface/*, public Serializeable*/
	{
	private:
		Vertex1Volume DefaultVolume;

	private:
		//For debug direction
		//Model* _direction;

		Model* _model = nullptr;
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
		void SetMatrix(HMatrix44 mat);
		//void Rotate(float yaw, float pitch, float roll);
		Vector3 GetPosition();
		Vector3 GetDirection();
		HMatrix44 GetWorldMatrix();
		HMatrix44 GetSocketCurrentMatrix(SocketName name);

	public:
		operator OBBData();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void Draw(ID3D11DeviceContext* dc) override;
		//std::string Serialize(int tabCount) override;
		//void Deserialize() override;
	};
}
