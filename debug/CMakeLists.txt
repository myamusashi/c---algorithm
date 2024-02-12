cmake_minimum_required (VERSION 3.11)
 
set(CMAKE_BUILD_TYPE Debug)
# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0
  # Important: Specify a GIT_TAG XXXXX here.
)
 
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
 
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
# find_package(libssl REQUIRED)
# find_package(libcrypto REQUIRED)
find_package(OpenSSL REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
#[[ include_directories(${OPENSSL_INCLUDE_DIR}) ]]
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")
include_directories("/usr/local/include/bsoncxx/v_noabi/bsoncxx/third_party/mnmlstc")

# ------------------------------------------------------------------------------
 
project(tlm
  LANGUAGES CXX
  VERSION 1.0.0
)
 
add_executable(tlm ../src/main.cpp ../src/credentials.cpp ../src/processes.cpp)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
target_include_directories(tlm PRIVATE src)
 
# target_link_libraries(ftxui-starter ${LIBMONGOCXX_LIBRARIES})
# target_link_libraries(ftxui-starter ${LIBBSONCXX_LIBRARIES})

target_link_libraries(tlm
  PRIVATE OpenSSL::SSL 
  PRIVATE OpenSSL::Crypto
  PRIVATE ${LIBMONGOCXX_LIBRARIES}
  PRIVATE ${LIBBSONCXX_LIBRARIES}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
)
