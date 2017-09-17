#pragma once
namespace ML::Data::FBX {
	class Mesh :public MeshBase {
	private:
		fbxsdk::FbxMesh* mesh;
		std::vector<Vertex::Position> vertexPoints;
		std::vector<Vertex::Normal> normalDirections;
		std::vector<Vertex::UV> uvPositions;
		//vector
		std::unique_ptr<Material::TexturePath> texturePath;
		std::unique_ptr<Material::VertexColor> vertexColor;
	private:
		Vertex::Position LocalTakeOrderVertex(UINT order_index);
		Vertex::Normal LocalTakeOrderNormal(UINT order_index);
		Vertex::UV LocalTakeOrderUV(UINT order_index);
		Material::TexturePath LocalTakeOrderTexturePath(UINT order_index);
		Material::VertexColor LocalTakeOrderVertexColor(UINT order_index);
	public:
		Mesh(FbxMesh* mesh);
		~Mesh();
		/**
		*@brief ���_���擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@return ���_��
		*/
		DWORD TakeOrderVertexCount()override;
		/**
		*@brief �}�e���A�����擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@return �}�e���A����
		*/
		DWORD TakeOrderMaterialCount()override;
		/**
		*@brief �C���f�b�N�X���擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@return �C���f�b�N�X��
		*/
		DWORD TakeOrderIndexCount()override;
		/**
		*@brief ���_�擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@param[in] �ق������ւ̃C���f�b�N�X
		*@return ���_
		*/
		Vertex TakeOrderVertex(UINT order_index)override;
		/**
		*@brief �}�e���A���擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@param[in] �ق������ւ̃C���f�b�N�X
		*@return �}�e���A��
		*/
		Material TakeOrderMaterial(UINT order_index)override;
		/**
		*@brief �C���f�b�N�X�擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@param[in] �ق������ւ̃C���f�b�N�X
		*@return �C���f�b�N�X
		*/
		IndexRow TakeOrderIndex(UINT order_index)override;

	};
}
#include "MLFBXMesh.inl"