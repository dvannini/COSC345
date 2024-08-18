# 19/07/2024 - Group
We have discarded the idea of using WASAPI for our drum machine as it is too low level for our purposes and would take ages to create an audio engine
# 22/07/2024 - Ben.A
Have been researching the 'playsound' function native to the windows.h library. I've found that using one thread to play sounds leads to irregular timing and occasional culling of sound tasks
For a drum machine, users should expect that the timing of their sounds is constant.
One solution to this is to create a thread pool which assigns a new 'playsound' task in a round robin manner. this way, multiple sounds can overlap each other and play hopefully in constant time
I'd want to test a prototype to see if this is the move first. If it doesn't improve the timing consistency, We may have to use a different audio library such as Xaudio2.
This library is higher level than WASAPI but unlike the 'playsound' function. only reads audio buffer data meaning we would need to make a WAV file reader helper function to open WAV files. 
However, this library should be more reliable than playsound.

# 23/07/2024 - alex
We plan on using TDD once we start properly producing the application, [this link](https://learn.microsoft.com/en-us/visualstudio/test/writing-unit-tests-for-c-cpp?view=vs-2022) may be useful.

# 7/08/2024 - ben
We've established some more branches for different development componenets for our project. I'm still in the process of setting continuous integration up

# 19/08/2024 - ben
The audio engine is ready to be presented in an alpha release with placeholder code for improved functionality later down the track. We have separted most components into classes and still develeping the way these classes interact together. We have a basic CI pipeline, local and cloud doxygen generation and implementing tests into each class in our program.
