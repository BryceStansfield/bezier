# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Helper for Bezier Curves, Triangles, and Higher Order Objects.

Intended to perform basic operations on Bezier objects such
as intersections, length/area/etc. computations, subdivision,
implicitization and other relevant information.

Plotting utilities will also be provided.
"""

from bezier.curve import Curve


__all__ = [
    'Curve',
]
