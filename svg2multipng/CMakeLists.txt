find_package(ZLIB)

include_directories(${ZLIB_INCLUDE_DIR})

add_executable(svg2multipng
    svg2multipng.cpp
    ../lib/helper.cpp
)
target_link_libraries(svg2multipng ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSVG_LIBRARY} ${ZLIB_LIBRARY})

install(TARGETS svg2multipng EXPORT targets DESTINATION bin)
