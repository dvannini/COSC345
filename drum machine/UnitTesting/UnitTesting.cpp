#include "pch.h"
#include "CppUnitTest.h"
#include "../drum machine/Sequence.cpp"
#include "../drum machine/Audio_Engine.cpp"
#include "../drum machine/Interface.cpp"
#include "../drum machine/Keyboard.cpp"
#include "../drum machine/Timeline.cpp"
#include "../drum machine/Utils.cpp"
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
