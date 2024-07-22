# 19/07/2024 - Group
We have discarded the idea of using WASAPI for our drum machine as it is too low level for our purposes and would take ages to create an audio engine
# 22/07/2024 - Ben.A
Have been researching the 'playsound' function native to the windows.h library. I've found that using one thread to play sounds leads to irregular timing and occasional culling of sound tasks
For a drum machine, users should expect that the timing of their sounds is constant.
One solution to this is to create a thread pool which assigns a new 'playsound' task in a round robin manner. this way, multiple sounds can overlap each other and play hopefully in constant time
I'd want to test a prototype to see if this is the move first. If it doesn't improve the timing consistency, We may have to use a different audio library such as Xaudio2.
This library is higher level than WASAPI but unlike the 'playsound' function. only reads audio buffer data meaning we would need to make a WAV file reader helper function to open WAV files. 
However, this library should be more reliable than playsound.

# 23/08/2024
We plan on using TDD once we start properly producing the application, [this link](https://learn.microsoft.com/en-us/visualstudio/test/writing-unit-tests-for-c-cpp?view=vs-2022) may be useful.
