cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
	GIT_REPOSITORY    https://github.com/google/googletest.git
	GIT_TAG           release-1.10.0
	SOURCE_DIR        "/Users/human/Desktop/final-project-team-plz-work/cmake-build-debug/googletest-src"
	BINARY_DIR        "/Users/human/Desktop/final-project-team-plz-work/cmake-build-debug/googletest-build"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND     ""
	INSTALL_COMMAND   ""
	TEST_COMMAND      ""
)
