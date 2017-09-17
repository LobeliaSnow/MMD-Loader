#pragma once
namespace ML::Data::FBX {
	__forceinline Vertex::Position Mesh::LocalTakeOrderVertex(UINT order_index) {
		if (vertexPoints.empty()) {
			fbxsdk::FbxVector4* _vertexPoints;
			_vertexPoints = mesh->GetControlPoints();
			DWORD _vertexCount = TakeOrderVertexCount();
			if (_vertexCount <= 0)STRICT_THROW("���_�����݂��Ȃ��\��������܂�");
			vertexPoints.resize(_vertexCount);
			Vertex::Position* _temp = vertexPoints.data();
			for (DWORD _i = 0; _i < _vertexCount; _i++) {
				//vector3������3
				for (int _j = 0; _j < 3; _j++) {
					_temp[_i].v[_j] = static_cast<float>(_vertexPoints[_i][_j]);
				}
			}
		}
		return vertexPoints[order_index];
	}
	__forceinline Vertex::Normal Mesh::LocalTakeOrderNormal(UINT order_index) {
		if (normalDirections.empty()) {
			fbxsdk::FbxArray<FbxVector4> _normalDirections;
			mesh->GetPolygonVertexNormals(_normalDirections);
			DWORD _vertexCount = TakeOrderVertexCount();
			if (_vertexCount <= 0)STRICT_THROW("���_�����݂��Ȃ��\��������܂�");
			normalDirections.resize(_vertexCount);
			Vertex::Normal* _temp = normalDirections.data();
			for (DWORD _i = 0; _i < _vertexCount; _i++) {
				//vector3������3
				for (int _j = 0; _j < 3; _j++) {
					_temp[_i].v[_j] = static_cast<float>(_normalDirections[_i][_j]);
				}
			}
		}
		return normalDirections[order_index];
	}
	__forceinline Vertex::UV Mesh::LocalTakeOrderUV(UINT order_index) {
		if (uvPositions.empty()) {
			fbxsdk::FbxStringList _uvNames;
			fbxsdk::FbxArray<FbxVector2> _uvPositions;
			mesh->GetUVSetNames(_uvNames);
			mesh->GetPolygonVertexUVs(_uvNames.GetStringAt(0), _uvPositions);
			DWORD _vertexCount = TakeOrderVertexCount();
			DWORD _uvCount = _uvPositions.Size();
			if (_vertexCount <= 0)STRICT_THROW("���_�����݂��Ȃ��\��������܂�");
			uvPositions.resize(_vertexCount);
			if (_uvCount > 0) {
				Vertex::UV* _temp = uvPositions.data();
				//FIXME: �A�E�g�I�u�����W
				//TODO: ���̂܂܂ł̓A�E�g�I�u�����W���N�����A�C���f�b�N�X�o�b�t�@�ɓW�J���Ȃ��Ɠ���͌��󖳗�
				//��֍�Ƃ��ăV�m�j�����R�[�h�݂����Ȋ����ŁA�C���f�b�N�X�o�b�t�@����Q�Ƃ��Ă��̒��_�ɂ������UV���W���ŏ�����q�b�g���鏇�ɕۑ�����悤�ɂ���
				for (DWORD _i = 0; _i < _vertexCount; _i++) {
					//vector2������2
					for (int _j = 0; _j < 2; _j++) {
						_temp[_i].v[_j] = static_cast<float>(_uvPositions[_i][_j]);
					}
				}
			}
		}
		return uvPositions[order_index];
	}
	__forceinline Material::TexturePath Mesh::LocalTakeOrderTexturePath(UINT order_index) {
		if (!texturePath) {
			fbxsdk::FbxNode* _node = mesh->GetNode();
			int materialCount = TakeOrderMaterialCount();
			if (order_index >= static_cast<UINT>(materialCount)) STRICT_THROW("�}�e���A�����𒴂����C���f�b�N�X�Ń}�e���A���̗v��������܂���");
			if (materialCount <= 0) STRICT_THROW("�}�e���A�������݂��Ȃ��\��������܂�");

			fbxsdk::FbxSurfaceMaterial* _material = _node->GetMaterial(order_index);
			fbxsdk::FbxProperty _property = _material->FindProperty(fbxsdk::FbxSurfaceMaterial::sDiffuse);
			int textureCount = _property.GetSrcObjectCount<FbxTexture>();
			//�e�N�X�`�����Ȃ��Ƃ�
			if (textureCount < 0) texturePath = std::make_unique<Material::TexturePath>("");
			else {
				//ML�̓s���ヌ�C���[�h�e�N�X�`���͔�Ή��B
				fbxsdk::FbxFileTexture* _texture = _property.GetSrcObject<fbxsdk::FbxFileTexture>(0);
				if (!_texture) texturePath = std::make_unique<Material::TexturePath>("");
				else {
					std::string _textureName = _texture->GetRelativeFileName();
					_textureName = _textureName.substr(_textureName.rfind('\\') + 1, _textureName.length());
					texturePath = std::make_unique<Material::TexturePath>(_textureName);
				}
			}
		}
		return *texturePath.get();
	}
	__forceinline Material::VertexColor Mesh::LocalTakeOrderVertexColor(UINT order_index) {
		if (!vertexColor) {
			fbxsdk::FbxNode* _node = mesh->GetNode();
			int _materialCount = TakeOrderMaterialCount();
			if (order_index >= static_cast<UINT>(_materialCount)) STRICT_THROW("�}�e���A�����𒴂����C���f�b�N�X�Ń}�e���A���̗v��������܂���");
			if (_materialCount <= 0) STRICT_THROW("�}�e���A�������݂��Ȃ��\��������܂�");

			fbxsdk::FbxSurfaceMaterial* _material = _node->GetMaterial(order_index);

			FbxSurfacePhong* _phong = nullptr;
			if (_material->FindProperty(FbxSurfaceMaterial::sAmbient).IsValid())_phong = (FbxSurfacePhong*)_material;
			vertexColor = std::make_unique<Material::VertexColor>();
			if (_phong) {
				for (int _i = 0; _i < 3; _i++) {
					vertexColor->v[_i] = static_cast<float>(_phong->Diffuse.Get()[_i]);
				}
			}
		}
		return *vertexColor.get();
	}
	__forceinline Mesh::Mesh(FbxMesh* mesh) :mesh(mesh), vertexPoints{}, normalDirections{}, uvPositions{} {}
	__forceinline Mesh::~Mesh() {}
	__forceinline DWORD Mesh::TakeOrderVertexCount() { return mesh->GetControlPointsCount(); }
	__forceinline DWORD Mesh::TakeOrderMaterialCount() { return mesh->GetNode()->GetMaterialCount(); }
	__forceinline DWORD Mesh::TakeOrderIndexCount() { return mesh->GetPolygonCount() * 3; }
	__forceinline Vertex Mesh::TakeOrderVertex(UINT order_index) { return Vertex(LocalTakeOrderVertex(order_index), LocalTakeOrderNormal(order_index), LocalTakeOrderUV(order_index)); }
	__forceinline Material Mesh::TakeOrderMaterial(UINT order_index) { return Material(LocalTakeOrderTexturePath(order_index), Material::VertexColor()); }
	__forceinline IndexRow Mesh::TakeOrderIndex(UINT order_index) { return IndexRow(); }

}
