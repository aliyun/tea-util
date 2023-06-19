find_package(darabonba_core QUIET)

if(darabonba_core_FOUND)
  message(STATUS "Found darabonba_core version ${darabonba_core_VERSION}")
else()
  message(STATUS "darabonba_core could not be located, download darabonba_core instead.")
  function(download_file url filename)
    message(STATUS "Download ${url} to ${filename} ...")
    file(DOWNLOAD
            ${url}
            ${filename}
            TIMEOUT 50000
            STATUS ERR
            SHOW_PROGRESS )
    IF(ERR EQUAL 0)
      #如果下载无错误则设置压缩包名称标记下载成功
      MESSAGE(STATUS "Download darabonba_core success")
    ELSE()
      #下载错误输出相关的提示信息
      MESSAGE(STATUS "Download failed, error: ${ERR}")
      MESSAGE(FATAL_ERROR
              "using curl/wget or a similar tool"
              )
    ENDIF()
  endfunction()

  function(extract_file filename extract_dir)
    message(STATUS "Extract ${filename} to ${extract_dir} ...")

    # 创建临时目录，用来解压，如果已经存在，则删除
    # 这里用的解压命令，是 cmake 内部实现的解压命令，可以实现跨平台解压：
    # cmake -E tar -xf filename.tgz
    set(temp_dir ${CMAKE_BINARY_DIR}/tmp_for_extract.dir)
    if(EXISTS ${temp_dir})
      file(REMOVE_RECURSE ${temp_dir})
    endif()
    file(MAKE_DIRECTORY ${temp_dir})
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${CMAKE_BINARY_DIR}/${filename}
            WORKING_DIRECTORY ${temp_dir})

    # 这里比较关键，解压之后的临时目录中，可能是单个文件夹，里面包含着我们需要的内容，
    # 也可能是直接就包含着我们需要的内容，因此，这里就统一处理，如果包含单独的文件夹
    # 则将安装源目录设置为临时目录的下级目录
    file(GLOB contents "${temp_dir}/*")
    list(LENGTH contents n)
    if(NOT n EQUAL 1 OR NOT IS_DIRECTORY "${contents}")
      set(contents "${temp_dir}")
    endif()

    get_filename_component(contents ${contents} ABSOLUTE)
    # 这里选择 INSTALL 而不是 COPY，因为可以打印出文件拷贝的状态
    file(INSTALL "${contents}/" DESTINATION ${extract_dir})

    # 别忘删除临时目录
    file(REMOVE_RECURSE ${temp_dir})
  endfunction()

  download_file("http://alibabaclou-cpp-package.oss-cn-shanghai.aliyuncs.com/darabonba/darabonba_core_build.zip" "darabonba_core.zip")
  extract_file("darabonba_core.zip" "${PROJECT_SOURCE_DIR}/deps")
  target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/deps/include")
endif()
