//-----------------------------------------------------------------------------
// SAVE_CPP
// 
// �Լ� save�� ���� �̸��� �˷��ָ� ���Ǹ� �����ϴ� 
// "2022�� 1�б� STL ��910��56 ��������.txt"�� ���ٿ� ����Ѵ�.
// 
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "save.h"

void save( std::string_view fname)
{
	// ���� ������ ����
	std::ifstream in{ fname.data() };
	// in.close();��� �ڵ�� �ʿ䰡 ���� �ڵ����� ��

	// �� ���ϵ� ����
	std::ofstream out{"2023 C++ Study.txt", std::ios::app};

	out << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;

	// ������ ������ �̸��� ���Ͽ� ����Ѵ�
	// out << "���� �̸�: " << fname << std::endl;

	// ������ ������ ũ�⸦ ���Ͽ� ����Ѵ�(C++17)
	// out << "���� ũ��: " << std::filesystem::file_size(fname) << std::endl;

	// ���� ��¥�� �ð��� ����Ѵ�(C++20)
	auto time = floor<std::chrono::seconds>(std::chrono::system_clock::now());
	out  << std::chrono::zoned_time("Asia/Seoul", time) << std::endl;
	std::cout << "\n\n\n" << std::chrono::zoned_time("Asia/Seoul", time) << std::endl;
	out << std::endl;

	// ���� ������ ������ �о� �� ���Ͽ� ���ٿ� ����
	// 1. �����̳�(�ڷᱸ��) ������ ������ ���ͷ� �о�´�
	std::vector<char> v{ std::istreambuf_iterator<char>{in}, {} }; // ó������ ������ �о����� ��

	// 2. �˰����� ����Ͽ� ���Ϳ� �ִ� ������ ���Ͽ� ����(copy �˰���)�Ѵ�
	copy(v.begin(), v.end(), std::ostream_iterator<char>{out});
}

void saveCpp()
{
	std::cout << "�����ϰ� �ʹٸ� s �� �Է��ϰ� ���͸� ���� �ּ���. " << std::endl;
	
	char input;
	std::cin >> input;

	if (input == 's') {
		save("�ҽ�.cpp");
		std::cout << "������ �Ϸ�Ǿ����ϴ�." << std::endl;
	}
	else {
		return;
	}
}