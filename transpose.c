#include <stdio.h>
#include <math.h>

void naive_transpose( data_t* A, int A_lda, int current_lda, int index, int level) {
    if (current_lda == 1) {
    return;
    } else {
    // set new matrix size to half of current
        int new_lda = current_lda / 2;
    // calculate new indices for recursive call and split the current matrix
        // we're looking at into four submatrices, with half the LDA and the
    // correct new index, then recurse on each of those matrices.
    int width = (2 << (level - 1));
    int row_index = level > 0 ? index / width : index;
        int j_offset = level > 0 ? index %  width : index;
        int new_index = row_index * (2 << (level + 1)) + 2 * j_offset;
    for (int i = 0; i < 2; i++) {
        naive_transpose(A, A_lda, new_lda, new_index + i, level + 1);
            naive_transpose(A, A_lda, new_lda, new_index + (2 << level) + i, level + 1);
    }
    // perform the transposition. We only transpose the submatrix in A that we are
        // looking at in this call.
        int starting_i = row_index * current_lda;
        int starting_j = j_offset * current_lda;
    // we only have to iterate through half of the matrix to transpose: indices 1 and 2 if A'
    // has indices [0 1]
    //             [2 3]
    // these indices are half by half elements wide in A
    int ending_i = starting_i + new_lda;
        for (int i = starting_i; i < ending_i; i++) {
            int row_offset0 = i * A_lda;
            int row_offset1 = (i + new_lda) * A_lda;
        int ending_j = starting_j + new_lda;
            for (int j = starting_j; j < ending_j; j++) {
        int temp = A[row_offset0 + (j + new_lda)];
                A[row_offset0 + (j + new_lda)] = A[row_offset1 + j];
                A[row_offset1 + j] = temp;
            }
        }
    }
}

int main(int argc, char** argv) {
    naive_transpose(argv[0], argv[1], argv[1], 0, 0);
    return 0;
}
