#pragma once
#include <string_view>

#include <iostream>    // ��ó����. �츮 �ڵ尡 ����Ǳ� ���� ���� ����ȴ�.
#include <fstream>
#include <filesystem>
#include <chrono>

void save(std::string_view fname);

void saveCpp();