
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.41 COMPONENTS unit_test_framework
                                   filesystem)
