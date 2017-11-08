# C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD LESS 11)
  set(CMAKE_CXX_STANDARD 11)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)

    # Warnings
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

    if(CMAKE_BUILD_TYPE MATCHES Release)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3") 
    elseif(CMAKE_BUILD_TYPE MATCHES Debug)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    endif()
    
    if(WITH_MPI)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-literal-suffix")
    endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)

    add_definitions(-DBOOST_ALL_DYN_LINK)

endif()
