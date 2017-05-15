add_executable(png2ico png2ico.cpp qicohandler.cpp qicohandler.h qcurhandler.cpp qcurhandler.h qanihandler.cpp qanihandler.h)
target_link_libraries(png2ico ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS png2ico EXPORT targets DESTINATION bin)
