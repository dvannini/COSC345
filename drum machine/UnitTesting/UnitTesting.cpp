#include "pch.h"
#include "CppUnitTest.h"
#include "../drum machine/Sequence.cpp"
#include "../drum machine/Audio_Engine.cpp"
#include "../drum machine/Interface.cpp"
#include "../drum machine/Keyboard.cpp"
#include "../drum machine/Timeline.cpp"
#include "../drum machine/Utils.cpp"
#include "../drum machine/Clock.cpp"
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
		TEST_METHOD(TestAudioEngine)
		{
			Assert::AreEqual(0, Audio_Engine::_test());
		}
		TEST_METHOD(TestKeyboard)
		{
			Assert::AreEqual(0, Keyboard::test_());
		}
		TEST_METHOD(TestClock)
		{
			Assert::AreEqual(0, Clock::test_());
		}
		TEST_METHOD(TestInterface)
		{
			Assert::AreEqual(0, Interface::_test());

		}
	};
}
