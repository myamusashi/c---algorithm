cmake_minimum_required (VERSION 3.11)
 
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
include_directories("/usr/include/mongocxx/v_noabi")
include_directories("/usr/include/bsoncxx/v_noabi")
include_directories("/usr/include/libmongoc-1.0")
include_directories("/usr/include/libbson-1.0")
include_directories("/usr/lib")

# ------------------------------------------------------------------------------
 
project(ftxui-starter
  LANGUAGES CXX
  VERSION 1.0.0
)
 
add_executable(ftxui-starter src/credentials.cpp src/processes.cpp src/main.cpp)
target_include_directories(ftxui-starter PRIVATE src)
 
# target_link_libraries(ftxui-starter ${LIBMONGOCXX_LIBRARIES})
# target_link_libraries(ftxui-starter ${LIBBSONCXX_LIBRARIES})

target_link_libraries(ftxui-starter
  PRIVATE OpenSSL::SSL 
  PRIVATE OpenSSL::Crypto
  PRIVATE ${LIBMONGOCXX_LIBRARIES}
  PRIVATE ${LIBBSONCXX_LIBRARIES}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
)

