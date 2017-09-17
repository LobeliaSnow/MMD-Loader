#pragma once
#ifndef __ML_UTILITY__
#define __ML_UTILITY__
///////////////////////////////////////////////////
//		�ėpinclude
///////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <intsafe.h>
#include <unordered_map>
///////////////////////////////////////////////////
///////////////////////////////////////////////////

#define Interface abstract
namespace ML {
	namespace Error {
#ifdef _DEBUG
		//����͗�O�������Ɏw�肳�ꂽ�����ŏ���\������
#define __EXCEPTION_ON__
#else
		//����̓��O���͂��悤�ɂ���
#define __EXCEPTION_LOG_ON__
#endif
//�w�肳�ꂽ��O�ƃ��O�t�@�C���𗼕��͂�����
//#define __STRICT_EXCEPTION_ON__
//������`�����Exception�̓��O�t�@�C������O�������Ȃ�
//��ԗD��x������ �ق��̃R�}���h�����ׂĖ�������
//#define __NO_EXCEPTION__
	/**
	*@brief ��O�N���X
	*@brief �ꉞ�n�k�Ŏ��̂�����Ďg�p���邱�Ƃ��\
	*@attention ���̃N���X�͎����Ŏ��̂𐶐�����̂ł͂Ȃ��A<br>
	*���Œ�`����Ă���}�N���ɂ���Đ���������B<br>
	*���b�Z�[�W��\������ɂ́ACATCH���ł��̃N���X��߂܂��ă����o�֐��ɂ���ĕ\��
	*@attention ���O�o�͓��̐���͏�ɂ���R�����g�Q��
	*/
		class Exception {
		private:
			/**@brief �\�[�X�t�@�C����*/
			std::string _filename;
			/**@brief ���s���ꂽ�֐���*/
			std::string _functionName;
			/**@brief ��O���o���s*/
			int _executeLine;
			/**@brief �C�ӂ̃��b�Z�[�W*/
			std::string _msg;
		private:
			/**
			*@brief �G���[���b�Z�[�W�\�z
			*@return �G���[����
			*/
			std::string CreateMessage()const noexcept;
			/**
			*@brief ���O�o��
			*/
			void OutputLog()const noexcept;
		public:
			/**
			*@brief �R���X�g���N�^
			*@param[in] �\�[�X�t�@�C����
			*@param[in] �֐���
			*@param[in] ���s�s�ԍ�
			*/
			Exception(std::string filename, std::string func_name, int exe_line) noexcept;
			/**
			*@brief �R���X�g���N�^
			*@param[in] �\�[�X�t�@�C����
			*@param[in] �֐���
			*@param[in] ���s�s�ԍ�
			*@param[in] �C�ӂ̃��b�Z�[�W
			*/
			Exception(std::string filename, std::string func_name, int exe_line, std::string msg) noexcept;
			/**@brief �f�X�g���N�^*/
			virtual ~Exception() noexcept = default;
			/**@brief ���b�Z�[�W�{�b�N�X�ɂ��o��*/
			void BoxMessage()const noexcept;
			/**@brief �G���[���͂��擾*/
			const std::string CreateExceptionMessage()const noexcept;
		};
		//���̐�}�N����`
		/**@def �\�[�X�t�@�C�����擾*/
#define FILE_NAME __FILE__
	/**@def �֐����擾*/
#define FUNCTION_NAME __func__
	/**@def ���s���Ă���s�擾*/
#define EXECUTE_LINE __LINE__
	/**@def �ϐ����擾*/
#define VARIABLE_NAME(variable) # variable
	/**@def ��O�N���X���̐���*/
#define STRICT_EXCEPTION_FACTORY(msg) ML::Error::Exception(FILE_NAME,FUNCTION_NAME,EXECUTE_LINE,msg)
	/**@def ��O�N���X���̐���*/
#define EXCEPTION_FACTORY STRICT_EXCEPTION_FACTORY("")
	/**@def try*/
#define TRY try
	/**@def throw Exception�����b�Z�[�W�t���œ�����*/
#define STRICT_THROW(msg) throw STRICT_EXCEPTION_FACTORY(msg)
	/**@def throw Exception�𓊂���*/
#define THROW_E STRICT_THROW("");
	/**@def catch*/
#define CATCH catch
	/**@def throw*/
#define THROW throw
	/**@def �A���C�����g*/
#define ALIGN(n) __declspec(align(n))

	}
	namespace Utility {
		//�v����
		class Filer {
		public:
			enum class OpenMode;
			enum class SeekMode;
		private:
			OpenMode mode;
			FILE* fp;
		private:
			std::string ModePurse(OpenMode m);
		public:
			Filer()noexcept;
			~Filer()noexcept;
			bool IsAppendMode()const noexcept;
			bool IsWriteMode()const noexcept;
			bool IsReadMode()const noexcept;
			bool IsBinaryMode()const noexcept;
			bool IsTextMode()const noexcept;
			bool IsOpen()const noexcept;
			OpenMode GetMode()const noexcept;
			__forceinline void Open(std::string filename, OpenMode m);
			__forceinline void Close()noexcept;
			template<typename T> __forceinline size_t Write(T* pointer, size_t count) noexcept;
			template<typename T> __forceinline size_t Read(T* pointer, size_t buffer_size, size_t count) noexcept;
			template <typename ... Args> __forceinline size_t Print(const char *format, Args const & ... args) noexcept;
			template <typename ... Args> __forceinline size_t Scan(const char* pointer, Args const & ... args) noexcept;
			__forceinline bool Seek(int offset, SeekMode mode);
			__forceinline bool Rewind();
		};
		/**
		*@brief ���\�[�X�}�l�[�W���[
		*@param �Ǘ��Ώۂ̌^
		*@param ���ƂȂ�^ �f�t�H���g�ł�std::string
		*/
		template<typename T, typename Key = std::string>
		class ResourceManager final {
		protected:
			/**
			*@brief ���\�[�X�Ǘ��p�A�z�z��
			*/
			static std::unordered_map<Key, std::shared_ptr<T>>resource;
		public:
			/**@brief �R���X�g���N�^*/
			ResourceManager() noexcept;
			/**@brief �f�X�g���N�^*/
			~ResourceManager() noexcept;
			/**
			*@brief �t�@�N�g���֐�
			*@brief �C���X�^���X������Ă���Ί����̂��̂��A����Ă��Ȃ���ΐV�K�ō쐬���ĕԂ��܂��B
			*@param <template>�C���X�^���X�쐬���ɓ��ꂽ�^�ƌp���֌W�̂��̂��Ǘ��������ꍇ�Ɏw��A���Ȃ���΂��̂܂܂̌^
			*@param <template>�C���X�^���X�쐬���Ɏg�p����������X�g
			*@param[in] ��
			*@param[in] �C���X�^���X�����ɕK�v�Ȉ���
			*@return �C���X�^���X�ւ̃|�C���^
			*/
			template<typename U = T, typename... Args>
			static T* Factory(Key key, Args... args)noexcept;
			/**
			*@brief �o�^�֐�
			*@brief �t�@�N�g�����g�p�������ڃC���X�^���X��a�������Ƃ��Ɏg�p
			*@param[in] ��
			*@param[in] �C���X�^���X�ւ̃|�C���^
			*/
			static void Register(Key key, std::shared_ptr<T> p)noexcept;
			/**
			*@brief �C���X�^���X�����݂��邩�Ԃ�
			*@param[in] ��
			*@return ���݂��Ă��邩�ۂ���bool�l
			*/
			static bool IsExist(Key key) noexcept;
			static void Clear() noexcept;
			static T* Get(Key key) noexcept;
		};
		template<typename T>
		class Singleton {
		protected:
			__forceinline Singleton()noexcept;
			__forceinline virtual ~Singleton()noexcept;
		public:
			static T* GetInstance();
		};
	}
}
#include "MLCommon.inl"
#endif
