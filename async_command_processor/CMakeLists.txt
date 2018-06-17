#CmakeList.txt for command_processor library in OTUS Homework #10

# set library name and content
add_library(async SHARED
  async.h async.cpp
  async_worker.h
  command_processor_instance.h
  broadcasters.h
  listeners.h
  async_command_processor.h  
  input_processor.h input_processor.cpp
  input_reader.h input_reader.cpp
  logger_mt.h
  smart_buffer_mt.h
  publisher_mt.h publisher_mt.cpp
  weak_ptr_less.h
  thread_metrics.h
  worker_state.h
)

target_link_libraries(async pthread)

install(TARGETS async LIBRARY DESTINATION lib)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alexandr_kudinov@mail.ru)

include(CPack)
