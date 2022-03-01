add_library(data_structures
        bitset/bitset.c
        vector/vector.c
        matrix/matrix.c
        matrix/matrixTest.c
        string/string_.c
        string/string_test.c
        string/string_tasks.c
        )

target_link_libraries(data_structures algorithms)