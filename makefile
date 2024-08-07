# Specify the MSBuild path
MSBUILD = $(MSBUILD_PATH)

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
