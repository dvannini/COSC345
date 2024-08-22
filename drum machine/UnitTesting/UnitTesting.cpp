#include "pch.h"
#include "CppUnitTest.h"
#include "../drum machine/Sequence.cpp"
#include "../drum machine/Audio_Engine.cpp"

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
			Audio_Engine engine = Audio_Engine::Audio_Engine();
			Assert::AreEqual(0, engine._test());
		}
	};
}
