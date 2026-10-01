# FreeCADMbD
Assembly Constraints and Multibody Dynamics code

Install freecad9a.exe from ar-cad.com. Run program and read Explain menu items for documentations. (edited) 

The MbD theory is at
https://github.com/Ondsel-Development/MbDTheory

**Build & Run FreeCADMbD on Windows 11**

Install Visual Studio 2026 (or Build Tools 2026) with **Desktop development
with C++**, the Microsoft v145 x64 toolset, a Windows SDK, and CMake 4.2 or
newer. The project uses C++20. Boost and vcpkg are not required. Tests fetch
the pinned GoogleTest source from GitHub on first configuration.

From the repository root:

```powershell
cmake --preset windows-vs
cmake --build --preset windows-vs-debug
ctest --preset windows-vs-debug
& ./build-vs/FreeCADMbDMain/Debug/FreeCADMbDMain.exe
```

Use `windows-vs-release` for Release builds and tests. The generated solution
is in `build-vs`; open the generated `.sln` or `.slnx` file in VS 2026.
If `build-vs` already contains a VS 2022 cache, configure with
`cmake --fresh --preset windows-vs`. The old `windows-vs-vcpkg*` presets have
been replaced by `windows-vs*`.

For Ninja, use the VS 2026 **x64 Native Tools Command Prompt** and the
`windows-ninja-debug` configure, build, and test presets. `VSCodeFreeCADMbD.cmd`
locates VS 2026 and opens this checkout in its x64 Microsoft compiler environment.
Tests run serially because some write shared temporary output filenames.
The standalone executable writes to the current directory when given an ASMT
input; run it in a separate output directory to retain those files.

`ExactPendulum` uses standard elliptic integrals and a local arithmetic-geometric
mean implementation of Jacobi functions, which C++20 does not supply.
Its public interface is unchanged.

The equivalent manual CMake GUI workflow is:
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
            Visual Studio 18 2026
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
        Follow instructions of Explain/Quick Start/
```
	
