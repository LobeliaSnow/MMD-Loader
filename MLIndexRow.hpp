#pragma once
namespace ML::Data {
	/**
	*@brief ���p�̌^�A���ۂɂ����ǂݍ��ނ̂�Mesh�N���X
	*/
	class IndexRow {
	private:
		UINT index;
	public:
		/**
		*@brief ���̌^���̂��̂�UINT�Ƃ��Ĉ����ׂ̃L���X�g���Z�q
		*@return UINT
		*/
		__forceinline operator UINT()const noexcept { return index; }
		/**@brief �R���X�g���N�^*/
		IndexRow();
		/**
		*@brief �R���X�g���N�^
		*@param[in] ���f�[�^
		*/
		IndexRow(UINT index);
		/**@brief �f�X�g���N�^*/
		~IndexRow();
	};
}
#include "MLIndexRow.inl"