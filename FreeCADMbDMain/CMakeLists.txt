set(FREECADMBD_MAIN_SRC
	FreeCADMbD.cpp
)
set(FREECADMBD_MAIN_HEADERS
	FreeCADMbD.h
)

add_executable(FreeCADMbDMain ${FREECADMBD_MAIN_SRC} ${FREECADMBD_MAIN_HEADERS})
target_link_libraries(FreeCADMbDMain FreeCADMbD)
