#include "pch.h"
#include "CppUnitTest.h"
#include "../drum machine/Sequence.cpp"
#include "../drum machine/Audio_Engine.cpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <assert.h>
#include <vector>
#include <chrono>
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <unordered_map>
#pragma comment(lib, "winmm.lib")

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(UnitTesting)
	{
	public:
		
		TEST_METHOD(TestSequence)
		{
			Assert::AreEqual(0, Sequence::test_());
		}
	};
}
