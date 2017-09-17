#pragma once
namespace ML::Data::PMD {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//					PMD::Mesh
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//private:
	__forceinline bool Mesh::ModelLinkCheck() { return filer.expired(); }
	//TODO: ���̉��œK���̗]�n����A�����₦�Ă���Ƃ��ɒ�������
	DWORD Mesh::_LocalTakeOrderCount(int seek_size, int read_size) {
		if (ModelLinkCheck())STRICT_THROW("Model�Ƃ̃����N���؂�Ă��܂�");
		DWORD _count = 0;
		if (std::shared_ptr<Filer> _filer = filer.lock()) {
			if (!_filer->Seek(seek_size, Filer::SeekMode::FRONT))return 0;
			if (_filer->Read(&_count, read_size, 1) == SIZE_T_MAX)return 0;
			_filer->Rewind();
		}
		return _count;
	}
	template<typename T> __forceinline T Mesh::_LocalTakeOrder(UINT index, int seek_size, int read_size) {
		if (index >= TakeOrderCount<T>())STRICT_THROW("�f�[�^���𒴂����C���f�b�N�X���w�肳��Ă��܂�");
		if (ModelLinkCheck())STRICT_THROW("Model�Ƃ̃����N���؂�Ă��܂�");
		T _ret = {};
		if (std::shared_ptr<Filer> _filer = filer.lock()) {
			if (!_filer->Seek(seek_size, Filer::SeekMode::FRONT))STRICT_THROW("�V�[�N�Ɏ��s���܂���");
			if (_filer->Read(&_ret, read_size, 1) == SIZE_T_MAX)STRICT_THROW("�ǂݍ��݂Ɏ��s���܂���");
			_filer->Rewind();
		}
		return _ret;
	}
	//std::string�̂��߂̓��ꉻ
	template<> std::string Mesh::_LocalTakeOrder(UINT index, int seek_size, int read_size) {
		if (ModelLinkCheck())STRICT_THROW("Model�Ƃ̃����N���؂�Ă��܂�");
		std::unique_ptr<char[]> _orderData = {};
		if (std::shared_ptr<Filer> _filer = filer.lock()) {
			//�t�@�C���̓ǂݍ��ݏꏊ��擪���猩�āA��񂪍ڂ��Ă���ʒu�܂ŃV�[�N
			if (!_filer->Seek(seek_size, Filer::SeekMode::FRONT))return false;
			//�ǂݎ��T�C�Y+'\0'���̃������m��
			_orderData = std::make_unique<char[]>(read_size + 1);
			if (_filer->Read(_orderData.get(), read_size, 1) == SIZE_T_MAX)return std::string("�ǂݍ��݃G���[");
			_orderData.get()[read_size] = '\0';
			if (!_filer->Rewind())STRICT_THROW("�����ʒu�ɖ߂��܂���ł����A�t�@�C�����J����Ă��Ȃ��\��������܂�");
		}
		return std::string(_orderData.get()) + "\0";
	}
	//IndexRow�̂��߂̓��ꉻ
	template<> __forceinline IndexRow Mesh::_LocalTakeOrder(UINT index, int seek_size, int read_size) {
		if (index >= TakeOrderCount<IndexRow>())STRICT_THROW("�f�[�^���𒴂����C���f�b�N�X���w�肳��Ă��܂�");
		if (ModelLinkCheck())STRICT_THROW("Model�Ƃ̃����N���؂�Ă��܂�");
		WORD _ret = {};
		if (std::shared_ptr<Filer> _filer = filer.lock()) {
			if (!_filer->Seek(seek_size, Filer::SeekMode::FRONT))STRICT_THROW("�V�[�N�Ɏ��s���܂���");
			if (_filer->Read(&_ret, read_size, 1) == SIZE_T_MAX)STRICT_THROW("�ǂݍ��݂Ɏ��s���܂���");
			_filer->Rewind();
		}
		return IndexRow(static_cast<UINT>(_ret));
	}

	template<typename T> __forceinline std::vector<T> Mesh::_LocalTakeOrder() {
		std::vector<T> ret = {};
		if (ModelLinkCheck())STRICT_THROW("Model�Ƃ̃����N���؂�Ă��܂�");
		DWORD count = TakeOrderCount<T>();
		if (count == 0)STRICT_THROW("�f�[�^��������܂���");
		for (UINT index = 0; index < count; index++) {
			ret.push_back(TakeOrderSingle<T>(index));
		}
		return ret;
	}
	//private:
	__forceinline DWORD Mesh::TakeOrderVertexCount() { return _LocalTakeOrderCount(283, 4); }
	__forceinline DWORD Mesh::TakeOrderMaterialCount() { return _LocalTakeOrderCount(287 + 38 * TakeOrderCount<Vertex>() + 4 + 2 * TakeOrderCount<IndexRow>(), 4); }
	__forceinline DWORD Mesh::TakeOrderIndexCount() { return _LocalTakeOrderCount(287 + 38 * TakeOrderCount<Vertex>(), 4); }

	__forceinline Vertex Mesh::TakeOrderVertex(UINT order_index) {
		Vertex::Position _p = _LocalTakeOrder<Vertex::Position>(order_index, 287 + 38 * order_index, 12);
		Vertex::Normal _n = _LocalTakeOrder<Vertex::Normal>(order_index, 287 + 38 * order_index + 12, 12);
		Vertex::UV _u = _LocalTakeOrder<Vertex::UV>(order_index, 287 + 38 * order_index + 12 + 12, 8);
		return Vertex(_p, _n, _u);
	}
	__forceinline Material Mesh::TakeOrderMaterial(UINT order_index) {
		Material::TexturePath _path = _LocalTakeOrder<std::string>(order_index, 287 + 38 * TakeOrderCount<Vertex>() + 4 + 2 * TakeOrderCount<IndexRow>() + 4 + 70 * order_index + 50, 20);
		Material::VertexColor _vc = _LocalTakeOrder<Material::VertexColor>(order_index, 287 + 38 * TakeOrderCount<Vertex>() + 4 + 2 * TakeOrderCount<IndexRow>() + 4 + 70 * order_index, 12);
		return Material(_path, _vc);
	}
	__forceinline IndexRow Mesh::TakeOrderIndex(UINT order_index) { return _LocalTakeOrder<IndexRow>(order_index, 287 + 38 * TakeOrderCount<Vertex>() + 4 + 2 * order_index, 2); }
	//public:
	__forceinline Mesh::Mesh(std::weak_ptr<Utility::Filer> filer) :filer(filer) {}
	__forceinline Mesh::~Mesh() = default;

}