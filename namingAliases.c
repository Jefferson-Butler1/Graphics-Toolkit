// clang-format off
#ifndef NAMING_ALIASES
#define NAMING_ALIASES
#include "M3d_matrix_tools.c"

// Utils
int printMatrix (double a  [4][4]) { return M3d_print_mat(a); }
int copyMatrix  (double out[4][4],
                 double in [4][4]) { return M3d_copy_mat(out, in); }
int makeIdentity(double a  [4][4]) { return M3d_make_identity(a); }

//Transformations


#endif