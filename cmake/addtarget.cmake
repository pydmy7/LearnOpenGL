macro(addExecutable target)
    aux_source_directory(./src src)
    message("-------${target}_src-------")
    foreach(file ${src})
        message("${file}")
    endforeach()
    message("-------${target}_src-------")

    file(GLOB_RECURSE include ./include/${target}/*.hpp)
    message("-------${target}_include-------")
    foreach(file ${include})
        message("${file}")
    endforeach()
    message("-------${target}_include-------")

    add_executable(
        ${target}
        ${src}
    )

    target_include_directories(${target} PRIVATE include)
    target_compile_features(${target} PRIVATE cxx_std_20)

    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()

endmacro(addExecutable)


macro(addLibrary target)
    aux_source_directory(./src src)
    message("-------${target}_src-------")
    foreach(file ${src})
        message("${file}")
    endforeach()
    message("-------${target}_src-------")

    file(GLOB_RECURSE include ./include/*.hpp)
    message("-------${target}_include-------")
    foreach(file ${include})
        message("${file}")
    endforeach()
    message("-------${target}_include-------")

    add_library(
        ${target}
        STATIC
        ${src}
    )

    target_include_directories(${target} PUBLIC include)
    target_compile_features(${target} PRIVATE cxx_std_20)

    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()

endmacro(addLibrary)
