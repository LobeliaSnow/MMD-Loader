#pragma once

namespace ML::Data::PMD {
	//���擾�p�֐�
	template<typename T> T Model::_LocalTakeOrder(int seek_size, size_t read_size) {
		//�t�@�C���̓ǂݍ��ݏꏊ��擪���猩�āA�ړI���ʒu�܂ŃV�[�N
		if (!filer->Seek(seek_size, Filer::SeekMode::FRONT))return false;
		T orderData = {};
		//�f�[�^�̓ǂݍ���
		if (filer->Read(&orderData, read_size, 1) == SIZE_T_MAX)	return T();
		//�ǂݍ��݈ʒu��擪�ɖ߂�
		if (!filer->Rewind())STRICT_THROW("�����ʒu�ɖ߂��܂���ł����A�t�@�C�����J����Ă��Ȃ��\��������܂�");
		return orderData;
	}
	//std::string�̂��߂̓��ꉻ
	template<> std::string Model::_LocalTakeOrder(int seek_size, size_t read_size) {
		//�t�@�C���̓ǂݍ��ݏꏊ��擪���猩�āA�o�[�W������񂪍ڂ��Ă���ʒu�܂ŃV�[�N
		if (!filer->Seek(seek_size, Filer::SeekMode::FRONT))return false;
		std::unique_ptr<char[]> orderData = {};
		orderData = std::make_unique<char[]>(read_size + 1);
		if (filer->Read(orderData.get(), read_size, 1) == SIZE_T_MAX)return std::string("�ǂݍ��݃G���[");
		orderData.get()[read_size] = '\0';
		if (!filer->Rewind())STRICT_THROW("�����ʒu�ɖ߂��܂���ł����A�t�@�C�����J����Ă��Ȃ��\��������܂�");
		return std::string(orderData.get()) + "\0";
	}
	//�w�b�_�[���`�F�b�N
	__forceinline bool Model::CheckHeader() { return (_LocalTakeOrder<std::string>(0, static_cast<size_t>(3)) == "Pmd"); }
	//�o�[�W�������擾
	__forceinline float Model::TakeVersion() { return _LocalTakeOrder<float>(3, static_cast<size_t>(4)); }
	//���f�����擾
	__forceinline std::string Model::TakeModelName() { return _LocalTakeOrder<std::string>(7, static_cast<size_t>(20)); }
	//�R�����g�擾
	__forceinline std::string Model::TakeComment() { return _LocalTakeOrder<std::string>(27, static_cast<size_t>(256)); }
	//Mesh���擾�����ǁAPMD�ɂ͂����炭1���������Ƃ����O��
	__forceinline DWORD Model::TakeMeshCount() { return MAX_MESH_COUNT; }

	__forceinline MeshBase* Model::TakeMeshOrder(UINT order_index) {
		if (order_index >= MAX_MESH_COUNT)STRICT_THROW("�͈͊O�̒l�ł�");
		Utility::ResourceManager<PMD::Mesh, UINT>::Factory(order_index, filer);
		return Utility::ResourceManager<PMD::Mesh, UINT>::Get(order_index);
	}

	Model::Model(std::string file_path) :filer(std::make_shared<Filer>()) {
		TRY{
			//�t�@�C�����J����Ă��邩�ǂ��������āA�J����Ă��Ȃ���ΊJ��
			if (!filer->IsOpen())filer->Open(file_path, Filer::OpenMode::ReadBinary);
			//�w�b�_�[�`�F�b�N
			if (!CheckHeader())STRICT_THROW("�w�b�_�[��񂪈�v���܂���ł����A�t�@�C���`�����Ⴄ�\��������܂�");
			//�o�[�W�����`�F�b�N
			if (TakeVersion() != 1.0f)STRICT_THROW("�o�[�W������񂪈�v���܂���A�t�@�C�������Ă���\��������܂�");
		}
		CATCH(...) { THROW; }
	}

}