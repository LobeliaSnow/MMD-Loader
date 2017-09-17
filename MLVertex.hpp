#pragma once
namespace ML::Data {
	/**
	*@brief ���p�̌^�A���ۂɂ����ǂݍ��ނ̂�Mesh�N���X
	*/
	class Vertex final {
	public:
		//TODO: ���擾���@�𑽂���
		class Position :public Math::Vector3 { public:	operator Math::Vector3() { return *this; } };
		class Normal :public Math::Vector3 { public:	operator Math::Vector3() { return *this; } };
		class UV :public Math::Vector2 { public:	operator Math::Vector2() { return *this; } };
	private:
		/**@brief ���_�ʒu*/
		Position position;
		/**@brief �@������*/
		Normal normal;
		/**@brief UV���W*/
		UV uv;
	public:
		/**@brief �R���X�g���N�^*/
		Vertex();
		/**
		*@breif �R���X�g���N�^
		*@param[in] �ʒu
		*@param[in] �@��
		*@param[in] �t�u
		*@attention Mesh�p�B���ۂɂ��̏�����肵�����Ƃ��́A�eModel����Mesh�������B
		*/
		Vertex(Position position, Normal normal, UV uv);
		/**@brief �f�X�g���N�^*/
		~Vertex();
		/**
		*@brief ���_�ʒu���擾
		*@return ���_�ʒu
		*/
		Position GetOrderPosition();
		/**
		*@brief �@���������擾
		*@return �@������
		*/
		Normal GetOrderNormal();
		/**
		*@brief UV���W���擾
		*@return UV���W
		*/
		UV GetOrderUV();
		/**
		*@brief ML::Data::Vertex::Position�Œ��_�ʒu<br>
		*@brief ML::Data::Vertex::Normal�Ŗ@������<br>
		*@brief ML::Data::Vertex::UV��UV���W<br>
		*@param[in] template ML::Data::Vertex::Position or ML::Data::Vertex::Normal or ML::Data::Vertex::UV
		*@return template�����̌^
		*/
		template<typename T> T GetOrder();
	};
}

#include "MLVertex.inl"