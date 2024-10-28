cmake_minimum_required(VERSION 3.16)

project(ASCIIPaint LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main # Important: Specify a version or a commit hash here.
)
FetchContent_MakeAvailable(ftxui)

add_executable(ASCIIPaint src/main.cpp


    src/draw_canvas/draw_canvas.hpp
    src/draw_canvas/draw_canvas.cpp
    src/screens/screen_manager.hpp
    src/screens/tool_menu_screen.hpp
    src/screens/screen_base.hpp
    src/screens/drawing_screen.hpp
    src/draw_canvas/canvas_tool.hpp
    src/draw_canvas/tool_base.hpp
    src/draw_canvas/pencil_tool.h
    src/constants.hpp
    src/draw_canvas/characters.hpp
        src/screens/screen_helper.hpp
        src/screens/file_menu_screen_copy.hpp

)

target_link_libraries(ASCIIPaint
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
)

include(GNUInstallDirs)
install(TARGETS ASCIIPaint
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
