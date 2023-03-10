//-----------------------------------------------------------------------------
// SAVE_CPP
// 
// 함수 save에 파일 이름을 알려주면 강의를 저장하는 
// "2022년 1학기 STL 수910목56 강의저장.txt"에 덧붙여 기록한다.
// 
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "save.h"

void save( std::string_view fname)
{
	// 읽을 파일을 연다
	std::ifstream in{ fname.data() };
	// in.close();라는 코드는 필요가 없음 자동으로 됨

	// 쓸 파일도 연다
	std::ofstream out{"2023 C++ Study.txt", std::ios::app};

	out << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;

	// 저장할 파일의 이름을 파일에 출력한다
	// out << "파일 이름: " << fname << std::endl;

	// 저장할 파일의 크기를 파일에 출력한다(C++17)
	// out << "파일 크기: " << std::filesystem::file_size(fname) << std::endl;

	// 현재 날짜와 시간을 출력한다(C++20)
	auto time = floor<std::chrono::seconds>(std::chrono::system_clock::now());
	out  << std::chrono::zoned_time("Asia/Seoul", time) << std::endl;
	std::cout << "\n\n\n" << std::chrono::zoned_time("Asia/Seoul", time) << std::endl;
	out << std::endl;

	// 읽을 파일의 정보를 읽어 쓸 파일에 덧붙여 쓴다
	// 1. 컨테이너(자료구조) 파일의 내용을 벡터로 읽어온다
	std::vector<char> v{ std::istreambuf_iterator<char>{in}, {} }; // 처음부터 끝까지 읽어오라는 것

	// 2. 알고리즘을 사용하여 벡터에 있는 내용을 파일에 복사(copy 알고리즘)한다
	copy(v.begin(), v.end(), std::ostream_iterator<char>{out});
}

void saveCpp()
{
	std::cout << "저장하고 싶다면 s 를 입력하고 엔터를 눌러 주세요. " << std::endl;
	
	char input;
	std::cin >> input;

	if (input == 's') {
		save("소스.cpp");
		std::cout << "저장이 완료되었습니다." << std::endl;
	}
	else {
		return;
	}
}