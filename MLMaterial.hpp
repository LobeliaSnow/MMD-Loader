#pragma once
namespace ML::Data {
	/**
	*@brief ���p�̌^�A���ۂɂ����ǂݍ��ނ̂�Mesh�N���X
	*/
	class Material {
	public:
		//TODO: ���擾���@�𑽂���
		/**@brief �e�N�X�`���t�@�C���p�X*/
		class TexturePath final{
		private:
			/**@brief �{��*/
			std::string path;
		public:
			/**
			*@brief �R���X�g���N�^
			*@param[in] ���f�[�^
			*/
			TexturePath(std::string path) :path(path) {}
			/**@brief ���̌^��std::string�Ƃ��Ĉ������߂̃L���X�g���Z�q*/
			operator std::string() { return path; }
		};
		/**@brief ���_�F*/
		class VertexColor :public Math::Vector3 { 
		public:
			/**@brief ���̌^��Math::Vector3�Ƃ��Ĉ������߂̃L���X�g���Z�q*/
			operator Math::Vector3() { return *this; } 
		};
	private:
		/**@brief �e�N�X�`���p�X*/
		TexturePath filePath;
		/**@brief ���_�F*/
		VertexColor vertexColor;
	public:
		/**
		*@brief �R���X�g���N�^
		*@param[in] �e�N�X�`���p�X
		*@param[in] ���_�F
		*/
		Material(TexturePath file_path, VertexColor vertex_color);
		/**@brief �f�X�g���N�^*/
		~Material();
		/**
		*@brief �e�N�X�`���p�X�擾
		*@return �e�N�X�`���p�X
		*/
		TexturePath GetTexturePath();
		/**
		*@brief ���_�F�擾
		*@return ���_�F
		*/
		VertexColor GetVertexColor();
		/**
		*@brief ML::Data::Material::TexturePath�Ńe�N�X�`���p�X<br>
		*@brief ML::Data::Material::VertexColor�Œ��_�F<br>
		*@param[in] template ML::Data::Material::TexturePath or ML::Data::Material::VertexColor
		*@return template�����̌^
		*/
		template<typename T> T GetOrder();
	};
}
#include "MLMaterial.inl"