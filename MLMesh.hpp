#pragma once

namespace ML::Data {
	//TODO: ���Ԗڂ̃��b�V���Ƃ�����Ȃ��ˁH
	/**
	*@brief ���b�V���A���ۂɏ���ǂݍ��ނ̂͑�̂�����
	*/
	class MeshBase abstract {
	private:
		/**
		@brief �P��̏����W�߂�std::vector�ɂ���
		*@param[in] template �W�߂�Ώۂ̌^
		*@return std::vector<�w�肵���^>
		*/
		template<typename T>  std::vector<T> _CollectData();
		/**
		@brief �P��̏����W�߂�std::vector�ɂ���
		*@param[in] template ��񌹂̌^�̌^
		*@param[in] template �W�߂�Ώۂ̌^
		*@param[in] ���
		*@return std::vector<�w�肵���^>
		*/
		template<typename T, typename U> __forceinline std::vector<U> _CollectData(std::vector<T>& _input_data);
	protected:
	public:
		/**
		*@brief �R���X�g���N�^
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*/
		MeshBase();
		/**@brief �f�X�g���N�^*/
		~MeshBase();
		/**
		*@brief ���_���擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@return ���_��
		*/
		virtual DWORD TakeOrderVertexCount() = 0;
		/**
		*@brief �}�e���A�����擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@return �}�e���A����
		*/
		virtual DWORD TakeOrderMaterialCount() = 0;
		/**
		*@brief �C���f�b�N�X���擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@return �C���f�b�N�X��
		*/
		virtual DWORD TakeOrderIndexCount() = 0;
		/**
		*@brief ���_�擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@param[in] �ق������ւ̃C���f�b�N�X
		*@return ���_
		*/
		virtual Vertex TakeOrderVertex(UINT order_index) = 0;
		/**
		*@brief �}�e���A���擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@param[in] �ق������ւ̃C���f�b�N�X
		*@return �}�e���A��
		*/
		virtual Material TakeOrderMaterial(UINT order_index) = 0;
		/**
		*@brief �C���f�b�N�X�擾
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@param[in] �ق������ւ̃C���f�b�N�X
		*@return �C���f�b�N�X
		*/
		virtual IndexRow TakeOrderIndex(UINT order_index) = 0;
		/**
		*@brief �w�肳�ꂽ�^�̑��ݐ����擾
		*@param[in] template ������肵�������̌^
		*@return �w�肳�ꂽ�^�̑��ݐ�
		*/
		template<typename T> DWORD TakeOrderCount();
		/**
		*@brief �w�肳�ꂽ�^�̑��ݐ����擾
		*@param[in] template ���肵�������̌^
		*@return �w�肳�ꂽ�^���
		*/
		template<typename T> T TakeOrder(UINT order_index);
		/**
		*@brief �w�肳�ꂽ�^�̑��ݐ����܂Ƃ߂Ď擾
		*@param[in] template ���肵�������̌^
		*@return �w�肳�ꂽ�^�����܂Ƃ߂�����
		*/
		template<typename T> std::vector<T> TakeOrder();
	};
}

#include "MLMesh.inl"