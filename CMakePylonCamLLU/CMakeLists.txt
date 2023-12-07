# CMakeList.txt : CMake project for CMakePylonCamLLU, include source and define
# project specific logic here.
#
#set (LLU_ROOT "D:/VS2022/LLU/out/install/x64-Debug/cmake")
set  (LLU_ROOT "C:/Users/ikke/source/repos/LibraryLinkUtilities/out/install/x64-Debug")
#set  (wxWidgets_DIR "D:/Packages/vcpkg/packages/wxwidgets_x64-windows-static/share/wxwidgets")
#set  (wxWidgets_DIR "D:/VS2022/wxWidgets/out/install/x64-Debug")
 set (wxWidgets_DIR $ENV{WXWIN})
#set  (NanoSVG_DIR "D:/Packages/vcpkg/packages/nanosvg_x64-windows-static/share/NanoSVG")
#set  (Pylon_DIR "C:/Program Files/Basler/pylon 7/Development/CMake/pylon")
#set (CMAKE_MODULE_PATH "D:/VS2022/CMakePylonCamLLU/CMakePylonCamLLU")

find_package(wxWidgets REQUIRED COMPONENTS net core base)
set(CMAKE_FIND_DEBUG_MODE ON)
find_package (pylon 7.3.0 REQUIRED)
#find_package  (pylon 7.4.0 REQUIRED)
find_package(LLU NO_MODULE REQUIRED PATH_SUFFIXES LLU)

include(${wxWidgets_USE_FILE})
include_directories(
        #add other includes directories 
        ${Pylon_INCLUDE_DIRS}
)
message ("Debug==>> ${Pylon_INCLUDE_DIRS}")
# Add source to this project's executable.
file (GLOB sources 
            src/CamApp.h
            src/CamApp.cpp
            src/GUI_generated/CamAppMainFrame.h
            src/GUI_generated/CamAppMainFrame.cpp
            src/OutputCamImages/OutputCamImages.h
            src/OutputCamImages/OutputCamImages.cpp
            src/Pylon/PylonCam.h 
            src/Pylon/PylonCam.cpp 
            src/LLU/WolframEngine.h 
            src/LLU/WolframENgine.cpp 
            src/Utils/ItCGrabResultPtr.h 
            src/Utils/ItCGrabResultPtr.cpp 
            )
#include_directories(include)
add_executable (CMakePylonCamLLU WIN32 ${sources})
target_link_libraries(CMakePylonCamLLU PRIVATE LLU::LLU ${wxWidgets_LIBRARIES} pylon::pylon)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakePylonCamLLU PROPERTY CXX_STANDARD 17)
endif()
install(FILES "${LLU_ROOT}/share/LibraryLinkUtilities.wl"
  DESTINATION "${PACLET_NAME}/LibraryResources"
)
# TODO: Add tests and install targets if needed.
