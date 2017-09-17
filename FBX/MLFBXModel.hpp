#pragma once
namespace ML::Data::FBX {
	class Model :public ModelBase{
	private:
		/**@brief fbx�}�l�[�W���[*/
		fbxsdk::FbxManager* manager;
		/**@brief fbx�V�[��*/
		fbxsdk::FbxScene* scene;
	private:
		DWORD TakeMeshCount()override;
		MeshBase* TakeMeshOrder(UINT order_index)override;
	public:
		Model(std::string file_path);
		~Model();
	};
}
#include "MLFBXModel.inl"