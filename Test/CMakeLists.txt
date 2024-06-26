include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b73f27fd164456fea9aba56163f5511355a03272.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  Test
  src/pch.cpp src/pch.h
  src/signals_test.cpp src/event_test.cpp
        src/vector_test.cpp src/scene_test.cpp src/texture_manager_test.cpp src/component_test.cpp src/window_test.cpp src/application_test.cpp src/mocks.h src/input_test.cpp)

target_precompile_headers( Test PRIVATE src/pch.h )


target_link_libraries(
		Test
	PRIVATE GTest::gtest_main
	PRIVATE GTest::gmock_main
	PRIVATE Ugine::Ugine-test
)


include(GoogleTest)
gtest_discover_tests(Test)

