add_executable(create_hash_table create_hash_table.cpp lookup.cpp)
target_link_libraries(create_hash_table ${QT_QTCORE_LIBRARY} )

install(TARGETS create_hash_table EXPORT targets DESTINATION bin)
