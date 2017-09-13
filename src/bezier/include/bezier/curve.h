// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#if defined (__cplusplus)
extern "C" {
#elif !defined (_MSC_VER)
#include <stdbool.h>
#endif

#if !defined (__cplusplus) && defined (_MSC_VER)
#  if !defined (FALSE)
#    define FALSE (0)
#  endif
#  if !defined (TRUE)
#    define TRUE (!FALSE)
#  endif
#  if _MSC_VER >= 1800
#    include <stdbool.h>
#  else
#    define bool int
#    define true TRUE
#    define false FALSE
#  endif
#endif

void evaluate_curve_barycentric(
    int *degree, int *dimension, double *nodes, int *num_vals,
    double *lambda1, double *lambda2, double *evaluated);
void evaluate_multi(
    int *degree, int *dimension, double *nodes,
    int *num_vals, double *s_vals, double *evaluated);
void specialize_curve_generic(
    int *degree, int *dimension, double *nodes,
    double *start, double *end, double *new_nodes);
void specialize_curve_quadratic(
    int *dimension, double *nodes, double *start,
    double *end, double *new_nodes);
void specialize_curve(
    int *degree, int *dimension, double *nodes, double *start, double *end,
    double *curve_start, double *curve_end, double *new_nodes,
    double *true_start, double *true_end);
void evaluate_hodograph(
    double *s, int *degree, int *dimension, double *nodes, double *hodograph);
void subdivide_nodes(
    int *num_nodes, int *dimension, double *nodes,
    double *left_nodes, double *right_nodes);
void newton_refine(
    int *num_nodes, int *dimension, double *nodes,
    double *point, double *s, double *updated_s);
void locate_point(
    int *num_nodes, int *dimension, double *nodes,
    double *point, double *s_approx);
void elevate_nodes(
    int *num_nodes, int *dimension, double *nodes, double *elevated);
void get_curvature(
    int *num_nodes, int *dimension, double *nodes, double *tangent_vec,
    double *s, double *curvature);
void reduce_pseudo_inverse(
    int *num_nodes, int *dimension, double *nodes, double *reduced,
    bool *not_implemented);

#if defined (__cplusplus)
}
#endif

#endif /* BEZIER_CURVE_H */
