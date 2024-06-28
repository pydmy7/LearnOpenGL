function(useSanitize target_name)
    isMSVCBackend(msvcbackend)
    isMinGWBackend(mingwbackend)
    isGNUBackend(gnubackend)
    if(${gnubackend} OR ${mingwbackend})
        target_compile_options(${target_name} PRIVATE
            -Wall -Wextra -Weffc++ -Wpedantic
            -Werror=uninitialized
            -Werror=return-type
            -Werror=unused-result
            -Werror=suggest-override
            -Wzero-as-null-pointer-constant
            -Wmissing-declarations
            -Wold-style-cast
            -Wnon-virtual-dtor
        )
    elseif(${msvcbackend})
        target_compile_options(${target_name} PRIVATE /W4)
    endif()

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        if(${gnubackend})
            target_compile_options(
                ${target_name}
                PRIVATE
                -fsanitize=address
                # -fsanitize=thread
                # -fsanitize=memory
                # -fsanitize=undefined
            )
            target_link_options(
                ${target_name}
                PRIVATE
                -fsanitize=address
                # -fsanitize=thread
                # -fsanitize=memory
                # -fsanitize=undefined
            )
        endif()

        if(${mingwbackend})
        endif()

        if(${msvcbackend})
        endif()
    endif()    
endfunction(useSanitize)
