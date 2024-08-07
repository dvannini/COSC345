# Specify the MSBuild path
MSBUILD = "C:\Program Files\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe"

# Specify the solution file
SOLUTION_FILE = "drum machine/drum machine.sln"

# Build configuration (Debug/Release)
CONFIGURATION = Release

# Target executable
TARGET = "drum machine/drum machine/Release/CMDrum.exe"

all: build

build:
	$(MSBUILD) $(SOLUTION_FILE) /p:Configuration=$(CONFIGURATION)

clean:
	$(MSBUILD) $(SOLUTION_FILE) /t:Clean /p:Configuration=$(CONFIGURATION)

run:
	./$(TARGET)
