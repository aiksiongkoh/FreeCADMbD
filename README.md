# FreeCADMbD
Assembly Constraints and Multibody Dynamics code

Install freecad9a.exe from ar-cad.com. Run program and read Explain menu items for documentations. (edited) 

The MbD theory is at
https://github.com/Ondsel-Development/MbDTheory

**Build & Run FreeCADMbD on Windows 11**
```plaintext
In Windows 11
    Launch Visual Studio
In Visual Studio
    Clone a Repository
    Enter
        Repository Location https://github.com/aiksiongkoh/FreeCADMbD
        Path C:\Users\...\FreeCADMbD
    Click/Clone
    Close Visual Studio
In Windows 11
    Launch CMake (cmake-gui)
In CMake
    Click/File/Delete Cache/
    Where is the source code: C:\Users\...\FreeCADMbD
    Where to build the binaries: C:\Users\...\FreeCADMbD\build
    Click/Configure
        Select
            Visual Studio 17 2022
            x64
            Use default native compiler
            Finish
        Wait for Configuring done
    Click/Generate
        Wait for Generating done
    Click/Open Project
        This will launch "C:\Users\...\FreeCADMbD\build\FreeCADMbD.sln".

In Visual Studio
    In Solution Explorer
        Select/ALL BUILD/
    Click/Build/Build Solution/
        Wait for Build succeeded
    Click/Test/Test Explorer/
        Select runSinglePendulum
        RightClick/Run/
            Should run and turn green
        RightClick/Debug/
            Step through code to learn the solver

Additionally, In Visual Studio
    In Solution Explorer
        Select/FreeCADMbDMain/
		RightClick/Set as Startup Project/
		Click/Local Windows Debugger/
			to start main program in FreeCADMbD.cpp
			Output is to a separate terminal window

When new *.cpp and *.h files are added in the directory
	C:\Users\...\FreeCADMbD\FreeCADMbD
	In Solution Explorer treeview
        Select/FreeCADMbD/Source Files/CmakeLists.txt
			Edit CMakeLists.txt to include *.cpp and *.h files
	Save CMakeLists.txt
Do the converse when *.cpp and *.h files are removed.

Shutdown any Visual Studio window.
Repeat CMake procedure above to create new Visual Studio *.sln which have the files changes.

For GUI version and documentation
    Download at
        https://www.ar-cad.com/freecad/download.html
    Inside freecad9a.exe
        Follow instrutions of Explain/Quick Start/
```
	
