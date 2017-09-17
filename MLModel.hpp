#pragma once
namespace ML::Data {
	class ModelBase abstract {
	private:
		template<typename T>
		std::vector<T> _CollectData(UINT mesh_index);
	private:
		//MeshBase�̐����擾���邽�߂̊֐�
		//MeshBase�̐��͂ǂ����Ă������łƂ�K�v�����邽�ߋ���̍�
		virtual DWORD TakeMeshCount() = 0;
		virtual MeshBase* TakeMeshOrder(UINT order_index) = 0;
	public:
		/**@brief �R���X�g���N�^*/
		ModelBase();
		/**@brief �f�X�g���N�^*/
		virtual ~ModelBase();
		//�ȉ����b�V���ȊO�̊֘A�擾
		/**
		*@brief �Ώۏ��̑��݂��鐔��Ԃ�
		*@param[in] template �~�������̌^
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@return DWORD ���̌^�̐�
		*@attention ML::Data::MeshBase�̏ꍇ�͈����͖�������܂�
		*/
		template<typename T> DWORD TakeOrderCount(UINT mesh_index);
		/**
		*@brief ��񂪒P��łق����ꍇ�Ɏg�p�����
		*@param[in] template �~�������̌^
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@param[in] �擾�Ώۂ̏��̃C���f�b�N�X
		*@return template�����̌^
		*@attention ML::Data::MeshBase�̏ꍇ�͑������͖�������܂�
		*/
		template<typename T> T TakeOrder(UINT mesh_index, UINT order_index);
		/**
		*@brief ��񂪓Z�߂Ăق����ꍇ�Ɏg�p�����
		*@param[in] template �~�������̌^
		*@param[in] �Ώۃ��b�V���̃C���f�b�N�X
		*@return std::vector<template�����̌^>
		*@attention ML::Data::MeshBase�̏ꍇ�͈����͖�������܂�
		*@attention ML::Data::MeshBase���~�����ꍇ�́AML::Data::MeshBase*��template�����ɓn���Ă�������
		*/
		template<typename T> std::vector<T> TakeOrder(UINT mesh_index);
	};
}
#define NO_USE_ARGUMENT 0

#include "MLModel.inl"