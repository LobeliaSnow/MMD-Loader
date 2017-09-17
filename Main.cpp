//ML�w�b�_�[
#include "ML.hpp"

#ifdef _DEBUG	
//���������[�N���m�p
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

__forceinline void ConsoleWait() {
	//���̓o�b�t�@�̃N���A
	rewind(stdin);
	//���͑ҋ@
	getchar();
}

template<typename T>
__forceinline void SafeRelease(T* p) {
	if (p) {
		delete p;
		p = nullptr;
	}
}

__forceinline void PrintPath(ML::Data::MeshBase* mesh) {
	using Material = ML::Data::Material;
	std::vector<Material> _materials = mesh->TakeOrder<Material>();

	size_t _materialCount = _materials.size();
	if (_materialCount <= 0)std::cout << "�}�e���A�������݂��܂���" << std::endl;
	for (size_t _i = 0; _i < _materialCount; _i++) {
		std::cout << _i << " -TexturePath- : " << static_cast<std::string>(_materials[_i].GetOrder<Material::TexturePath>()) << std::endl;
	}
}

__forceinline void PrintVertexColor(ML::Data::MeshBase* mesh) {
	using Material = ML::Data::Material;
	std::vector<Material> _material = mesh->TakeOrder<Material>();

	size_t _materialCount = _material.size();
	for (size_t _i = 0; _i < _materialCount; _i++) {
		Material::VertexColor _vc = _material[_i].GetOrder<Material::VertexColor>();
		std::cout << _i << " -Color- x : " << _vc.x << " y : " << _vc.y << " z : " << _vc.z << std::endl;
	}
}

__forceinline void PrintVertex(ML::Data::MeshBase* mesh) {
	using Vertex = ML::Data::Vertex;
	std::vector<Vertex> _vertices = mesh->TakeOrder<Vertex>();

	size_t _vertexCount = _vertices.size();
	for (size_t _i = 0; _i < _vertexCount; _i++) {
		Vertex::Position _vp = _vertices[_i].GetOrder<Vertex::Position>();
		Vertex::Normal _n = _vertices[_i].GetOrder<Vertex::Normal>();
		Vertex::UV _uv = _vertices[_i].GetOrder<Vertex::UV>();
		std::cout << _i << " -Position- x : " << _vp.x << " y : " << _vp.y << " z : " << _vp.z << std::endl;
		std::cout << _i << " -Normal- x : " << _n.x << " y : " << _n.y << " z : " << _n.z << std::endl;
		std::cout << _i << " -UV- x : " << _uv.x << " y : " << _uv.y << std::endl;
	}
}

__forceinline void PrintIndex(ML::Data::MeshBase* mesh) {
	using IndexRow = ML::Data::IndexRow;
	std::vector<IndexRow> indices = mesh->TakeOrder<IndexRow>();

	size_t indexCount = indices.size();
	for (size_t i = 0; i < indexCount; i++) {
		std::cout << " -index- " << i << " : " << indices[i] << std::endl;
	}
}

int main() {
#ifdef _DEBUG
	//���������[�N���m�p
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_crtBreakAlloc = 521;
#endif	//_DEBUG
	//API�ɂ��Ă̏��擾&�\��
	std::cout << "API Name " << ML::Information::GetInstance()->GetAPIName() << std::endl;
	std::cout << "Version " << ML::Information::GetInstance()->GetAPIVersion() << std::endl;
	std::cout << "Comment\n" << ML::Information::GetInstance()->GetAPIComment() << std::endl;
	std::cout << "ProjectName " << "ML Sample Program for FBX" << std::endl;
	std::cout << "author Lobelia.Snow\n" << std::endl;
	//�t�@�C�����̓���
	std::cout << "Please Input FilePath ->";
	char filePath[256] = {};
	std::cin >> filePath;
	//�ȉ��ǂݍ��ݓ��e
	//���f���̊��N���X�|�C���^�錾
	ML::Data::ModelBase* _model = nullptr;
	try {
		//�����MMD�̌`���̈��Apmd�`���̓ǂݍ��݁B�ق��̌`���͖��O��Ԃ̕ύX�����ł悢
		//root = new ML::Data::PMD::Model("�������J_nanami_gra.pmd");
		std::cout << "\nStart Load Model" << std::endl;

		_model = new ML::Data::PMD::Model(filePath);

		//���b�V�����擾
		DWORD _meshCount = _model->TakeOrderCount<ML::Data::MeshBase*>(NO_USE_ARGUMENT);
		for (DWORD _i = 0; _i < _meshCount; _i++) {
			std::cout << "No." << _i << " mesh" << std::endl;
			ML::Data::MeshBase* _mesh = _model->TakeOrder<ML::Data::MeshBase*>(_i, NO_USE_ARGUMENT);
			PrintVertex(_mesh);
			//PrintPath(_mesh);
			//PrintIndex(_mesh);
			//PrintVertexColor(_mesh);
		}
	}
	catch (ML::Error::Exception& e) {
		SafeRelease(_model);
		std::cout << e.CreateExceptionMessage() << std::endl;
		ConsoleWait();
		return -1;
	}
	//���
	SafeRelease(_model);
	ConsoleWait();

	return 0;
}