#pragma once
namespace ML {
	/**@brief ML API�ɂ��Ă̏��i�[�ꏊ*/
	class Information :public Utility::Singleton<Information> {
		friend class Utility::Singleton<Information>;
	private:
		/**@brief API�̖��O�̒萔*/
		const std::string apiName = "ML API";
		/**@brief API�̃��C���o�[�W����*/
		const int mainVersion = 0;
		/**@brief API�̃T�u�o�[�W����*/
		const int subVersion = 1;
		/**@brief ���݂�API�̏�Ԃ�\��*/
		std::string type = "��";
	private:
		/**@brief �R���X�g���N�^*/
		Information();
		/**@brief �f�X�g���N�^*/
		~Information();
	public:
		/**
		*@brief API�̖��O��Ԃ��܂�
		*@return API��
		*/
		const std::string& GetAPIName();
		/**
		*@brief API�̃o�[�W������Ԃ��܂�
		*@return API�̃o�[�W����
		*/
		std::string GetAPIVersion();
		/**
		*@brief API�̃R�����g��Ԃ��܂�
		*@return API�̃R�����g
		*/
		const std::string& GetAPIComment();
		/**
		*@brief API�̃��C���o�[�W������Ԃ��܂�
		*@return API���C���o�[�W����
		*/
		const int GetAPIMainVersion();
		/**
		*@brief API�̃T�u�o�[�W������Ԃ��܂�
		*@return API�T�u�o�[�W����
		*/
		const int GetAPISubVersion();
		/**
		*@brief API�̏�Ԃ�Ԃ��܂�
		*@return API�̏��(����)
		*/
		const std::string& GetType();
	};
}
#include "MLInformation.inl"