if(BUILD_TESTS)

    add_executable(EmbedTests
        test_codegenerator.cpp
    )
    
    target_link_libraries(EmbedTests PRIVATE
    EmbedLib
    Catch2::Catch2WithMain
    )

    include(CTest)
    
    include(Catch)
    catch_discover_tests(EmbedTests)
endif()