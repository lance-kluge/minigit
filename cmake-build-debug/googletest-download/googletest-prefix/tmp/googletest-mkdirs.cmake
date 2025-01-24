# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/human/Desktop/final-project-team-plz-work/cmake-build-debug/googletest-src"
  "/Users/human/Desktop/final-project-team-plz-work/cmake-build-debug/googletest-build"
  "/Users/human/Desktop/final-project-team-plz-work/cmake-build-debug/googletest-download/googletest-prefix"
  "/Users/human/Desktop/final-project-team-plz-work/cmake-build-debug/googletest-download/googletest-prefix/tmp"
  "/Users/human/Desktop/final-project-team-plz-work/cmake-build-debug/googletest-download/googletest-prefix/src/googletest-stamp"
  "/Users/human/Desktop/final-project-team-plz-work/cmake-build-debug/googletest-download/googletest-prefix/src"
  "/Users/human/Desktop/final-project-team-plz-work/cmake-build-debug/googletest-download/googletest-prefix/src/googletest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/human/Desktop/final-project-team-plz-work/cmake-build-debug/googletest-download/googletest-prefix/src/googletest-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/human/Desktop/final-project-team-plz-work/cmake-build-debug/googletest-download/googletest-prefix/src/googletest-stamp${cfgdir}") # cfgdir has leading slash
endif()
