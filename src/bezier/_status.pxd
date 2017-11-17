# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Cython wrapper for ``status.f90``."""


cdef extern from "bezier/status.h":
    cpdef enum Status:
        SUCCESS = 0
        PARALLEL = 1
        WIGGLE_FAIL = 2
        NO_CONVERGE = 3
        TOO_SMALL = 4
        SAME_CURVATURE = 5
        BAD_TANGENT = 6
        EDGE_END = 7
