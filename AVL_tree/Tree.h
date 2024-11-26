#pragma once

#include <string>
#include <iostream>

/**
* @brief ����� "���-������"
*/
class Tree
{
private:

public:
	/*
	* @brief ����������� �� ���������
	*/
	Tree();

	/*
	* @brief ����������� �����������
	* @param other ������, ������ ��������
	*/
	Tree(const Tree& other);

	/*
	* @brief ����������
	*/
	~Tree();

	/*
	* @brief ����������
	* @param other ������, ������ ��������
	* @return ������, ���� �����������
	*/
	Tree& operator=(const Tree& other);

	/*
	* @brief ������� �������� � ������
	* @param value �������� ��� �������
	*/
	void insert(int value);

	/*
	* @brief ����� �������� � ������
	* @param value �������� ��� �������
	* @return ���������� � ���, ������ �� �������
	*/
	bool find(int value) const;

	/*
	* @brief ���������� ������ � ������
	* @return ��������� ������������� ������
	*/
	std::string toString() const;

	/*
	* @brief ����� ������ � �����
	* @param out ����� ������
	* @param tree ������
	* @return ����� ������ ��� ����������� ������
	*/
	friend std::ostream& operator<<(std::ostream& out, const Tree& tree);
};

