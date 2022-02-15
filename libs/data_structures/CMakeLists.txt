add_library(data_structures
        bitset/bitset.c
        vector/vector.c
        matrix/matrix.c
        matrix/matrixTest.c
        )

target_link_libraries(data_structures algorithms)