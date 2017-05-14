
if(WIN32 AND NOT WINCE)
 add_subdirectory(create_hash_table)
endif()


if (MINGW)
  add_subdirectory(mt)
endif()
if(BUILD_PNG2ICO)
    add_subdirectory(png2ico)
endif()
if(WIN32)
    add_subdirectory(svg2ico)
    add_subdirectory(realpath)
endif()
