// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#define WIN32_LEAN_AND_MEAN

#define VERSION "0.0.1"
#pragma comment(lib,"ws2_32.lib")

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <future>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <thread>
#include <mutex>

#include <ctime>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#include <ws2tcpip.h>
#include <Windows.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/reader.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>


namespace fs = std::filesystem;
namespace json = rapidjson;

namespace chrono = std::chrono;
using namespace std::chrono_literals;

// Добавьте сюда заголовочные файлы для предварительной компиляции

#endif //PCH_H
