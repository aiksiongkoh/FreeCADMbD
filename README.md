# FreeCADMbD

Assembly Constraints and Multibody Dynamics code.

## Build on Windows with the Microsoft toolchain

1. Install **Visual Studio 2026** or **Build Tools 2026**. In the installer,
   select **Desktop development with C++**, including the **v145 x64 toolset**
   and a **Windows SDK**.
2. Install **CMake 4.2 or newer** and add it to `PATH` so `cmake` and `ctest`
   work in your terminal.
3. Clone or download this repository. Open PowerShell in the **repository root**:
   the folder containing `CMakePresets.json` and the top-level `CMakeLists.txt`.
4. Run these commands in order:

   ```powershell
   cmake --preset windows-vs
   cmake --build --preset windows-vs-debug
   ctest --preset windows-vs-debug
   ```

The first command configures the project, the second builds the library,
executable, and tests, and the third runs the tests. Build output goes into
`build-vs`. The first configuration needs internet access to download GoogleTest.
The project uses C++20; Boost and vcpkg are not required.

To run the standalone executable from the same PowerShell window:

```powershell
& .\build-vs\FreeCADMbDMain\Debug\FreeCADMbDMain.exe
```

For Release, keep the same configure command and use `windows-vs-release`
in the build and test commands. The executable then goes into the `Release`
folder instead of `Debug`.

If configuration reports that `build-vs` uses a different Visual Studio
version, run `cmake --fresh --preset windows-vs`, then build again.

## Use VS Code or Visual Studio

For **VS Code**, install VS Code with its `code` command on `PATH`, plus the
**C/C++** and **CMake Tools** extensions. From the repository root, run:

```powershell
.\VSCodeFreeCADMbD.cmd
```

The launcher opens this repository in VS Code with the Microsoft x64 compiler
environment. Open **Terminal > New Terminal** and use the build and test
commands above. **Ctrl+Shift+B** configures and builds only `FreeCADMbDMain`;
use the full build command above before running tests.

For the **Visual Studio IDE**, configure with the command above, then open
the generated `.sln` or `.slnx` file inside `build-vs`. Select **Debug | x64**
and choose **Build > Build Solution**. To debug the executable, set
`FreeCADMbDMain` as the startup project and press **F5**.

When adding or removing source files, update the corresponding `CMakeLists.txt`,
then configure and build again.

## Notes and documentation

Tests run serially because some write shared temporary output filenames.
The standalone executable writes to the current directory when given an ASMT
input; run it in a separate output directory to retain those files.

`ExactPendulum` uses standard elliptic integrals and a local arithmetic-geometric
mean implementation of Jacobi functions, which C++20 does not supply.
Its public interface is unchanged.

The MbD theory is at https://github.com/Ondsel-Development/MbDTheory.

For the GUI version, download `freecad9a.exe` from
https://www.ar-cad.com/freecad/download.html. In the program, open
**Explain > Quick Start** for instructions.
