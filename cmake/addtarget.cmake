function(addExecutable target)
    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" src)

    add_executable(
        ${target}
        ${src}
    )

    target_include_directories(${target} PRIVATE include)
    target_compile_features(${target} PRIVATE cxx_std_20)

    useSanitize(${target})
endfunction(addExecutable)


function(addLibrary target)
    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" src)

    add_library(
        ${target}
        OBJECT
        ${src}
    )

    target_include_directories(${target} PUBLIC include)
    target_compile_features(${target} PRIVATE cxx_std_20)

    useSanitize(${target})
endfunction(addLibrary)
