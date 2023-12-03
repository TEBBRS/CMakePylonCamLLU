# CMakeList.txt : CMake project for CMakePylonCamLLU, include source and define
# project specific logic here.
#
#set (LLU_ROOT "D:/VS2022/LLU/out/install/x64-Debug/cmake")
set (LLU_ROOT "C:/Users/ikke/source/repos/LibraryLinkUtilities/out/install/x64-Debug")
find_package(wxWidgets REQUIRED COMPONENTS net core base)
find_package(pylon 7.1.0 REQUIRED)
find_package(LLU NO_MODULE REQUIRED PATH_SUFFIXES LLU)
# Add source to this project's executable.
file (GLOB src src/*.cpp)
file (GLOB inc src/*.h)
#include_directories(include)
add_executable (CMakePylonCamLLU ${src} ${inc})
target_link_libraries(CMakePylonCamLLU PRIVATE LLU::LLU)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakePylonCamLLU PROPERTY CXX_STANDARD 20)
endif()
install(FILES "${LLU_ROOT}/share/LibraryLinkUtilities.wl"
  DESTINATION "${PACLET_NAME}/LibraryResources"
)
# TODO: Add tests and install targets if needed.
