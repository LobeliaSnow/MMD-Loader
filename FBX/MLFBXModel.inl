#pragma once
namespace ML::Data::FBX {
	__forceinline DWORD Model::TakeMeshCount() { return scene->GetSrcObjectCount<FbxMesh>(); }
	__forceinline MeshBase* Model::TakeMeshOrder(UINT order_index) {
		if (order_index >= TakeMeshCount())STRICT_THROW("�͈͊O�̒l�ł�");
		Utility::ResourceManager<FBX::Mesh, UINT>::Factory(order_index, scene->GetSrcObject<FbxMesh>(order_index));
		return Utility::ResourceManager<FBX::Mesh, UINT>::Get(order_index);
	}

	__forceinline Model::Model(std::string file_path) {
		TRY{
			manager = fbxsdk::FbxManager::Create();

			fbxsdk::FbxImporter* importer = fbxsdk::FbxImporter::Create(manager, "Importer");
			scene = fbxsdk::FbxScene::Create(manager, "Scene");
			//Fbx�t�@�C�����J��
			if (!importer->Initialize(file_path.c_str()))	STRICT_THROW("Fbx�t�@�C�����J���܂���ł���");
			//�V�[�������o��
			if (!importer->Import(scene))STRICT_THROW("�V�[���̎��o���Ɏ��s");
			importer->Destroy();
			fbxsdk::FbxGeometryConverter converter(manager);

			//�S�ĎO�p��
			if (!converter.Triangulate(scene, true))	STRICT_THROW("�O�p���Ɏ��s");
			converter.RemoveBadPolygonsFromMeshes(scene);
			//�}�e���A�����ƂɃ��b�V���𕪗�
			if (!converter.SplitMeshesPerMaterial(scene, true))STRICT_THROW("���b�V���̕����Ɏ��s");
		}CATCH(...) { 
			manager->Destroy();
			THROW;
		}
	}
	__forceinline Model::~Model() { manager->Destroy(); }
}