    cmake_minimum_required(VERSION 3.15)

    project(discord-bot VERSION 1.0 DESCRIPTION "A discord bot to add custom leaderboards and ELO to CTF discord challenges")

    add_subdirectory(libs/DPP)

    add_executable(${PROJECT_NAME}
            src/main.cpp
    )

    target_link_libraries(${PROJECT_NAME}
            dpp
    )

    target_include_directories(${PROJECT_NAME} PRIVATE
            libs/DPP/include
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
    )