``bezier``
==========

    Helper for B |eacute| zier Curves, Triangles, and Higher Order Objects

|linux-build| |macos-build| |windows-build| |coverage|

|pypi| |versions|

|zenodo| |JOSS|

.. |eacute| unicode:: U+000E9 .. LATIN SMALL LETTER E WITH ACUTE
   :trim:

.. toctree::
   :hidden:
   :maxdepth: 4

   python/index
   abi/index
   algorithms/index
   development
   releases/index

This library provides:

* Support for B |eacute| zier :mod:`Curves <bezier.curve>`
* Support for B |eacute| zier :mod:`Triangles <bezier.triangle>`

Dive in and take a look!

.. image:: images/triangles6Q_and_7Q.png
   :align: center

Why B |eacute| zier?
--------------------

A B |eacute| zier curve (and triangle, etc.) is a parametric curve
that uses the `Bernstein basis`_:

.. math::

   b_{j, n} = \binom{n}{j} s^j (1 - s)^{n - j}

to define a curve as a linear combination:

.. math::

   B(s) = \sum_{j = 0}^n b_{j, n} \cdot v_j.

This comes from the fact that the weights sum to one:

.. math::

   b_{0, n} + b_{1, n} + \cdots + b_{n, n} =
       \left(s + (1 - s)\right)^n = 1.

This can be generalized to higher order by considering three, four, etc.
non-negative weights that sum to one (in the above we have the two
non-negative weights :math:`s` and :math:`1 - s`).

Due to their simple form, B |eacute| zier curves:

* can easily model geometric objects as parametric curves, triangles, etc.
* can be computed in an efficient and numerically stable way via
  `de Casteljau's algorithm`_
* can utilize convex optimization techniques for many algorithms (such as
  curve-curve intersection), since curves (and triangles, etc.)
  are convex combinations of the basis

Many applications -- as well as the history of their development --
are described in
"The Bernstein polynomial basis: A centennial `retrospective`_",
for example;

* aids physical analysis using finite element methods (`FEM`_) on
  isogeometric models by using geometric shape functions called
  `NURBS`_ to represent data
* used in robust control of dynamic systems; utilizes convexity to
  create a hull of curves

.. _retrospective: https://dx.doi.org/10.1016/j.cagd.2012.03.001
.. _Bernstein basis: https://en.wikipedia.org/wiki/Bernstein_polynomial
.. _de Casteljau's algorithm: https://en.wikipedia.org/wiki/De_Casteljau%27s_algorithm
.. _FEM: https://en.wikipedia.org/wiki/Finite_element_method
.. _NURBS: https://en.wikipedia.org/wiki/Non-uniform_rational_B-spline

Installing
----------

The ``bezier`` Python package can be installed with `pip`_:

.. code-block:: console

   $ python     -m pip install --upgrade bezier
   $ python3.10 -m pip install --upgrade bezier
   $ # To install optional dependencies, e.g. SymPy
   $ python     -m pip install --upgrade bezier[full]

To install a pure Python version (i.e. with no binary extension):

.. code-block:: console

   $ BEZIER_NO_EXTENSION=true \
   >   python   -m pip install --upgrade bezier --no-binary=bezier

``bezier`` is open-source, so you can alternatively grab the source
code from `GitHub`_ and install from source.

.. _pip: https://pip.pypa.io
.. _GitHub: https://github.com/dhermes/bezier/

Getting Started
---------------

For example, to create a curve:

.. testsetup:: getting-started

   import sys
   import unittest.mock

   import numpy as np

   import bezier

   try:
       import matplotlib
       import matplotlib.pyplot as plt
       mpl_installed = True
   except ImportError:
       mpl_installed = False
       # Fake the matplotlib imports.
       plt_mod = unittest.mock.Mock(
           name="matplotlib.pyplot", spec=["figure", "show"])
       plt_mod.show.return_value = None
       sys.modules["matplotlib.pyplot"] = plt_mod
       mpl_mod = unittest.mock.Mock(
           name="matplotlib", pyplot=plt_mod, spec=[])
       sys.modules["matplotlib"] = mpl_mod

   try:
       import seaborn
       seaborn_installed = True
   except ImportError:
       seaborn_installed = False
       # Fake the seaborn imports.
       seaborn_mod = unittest.mock.Mock(name="seaborn", spec=["set"])
       seaborn_mod.set.return_value = None
       sys.modules["seaborn"] = seaborn_mod

.. doctest:: getting-started

   >>> import bezier
   >>> import numpy as np
   >>> nodes1 = np.asfortranarray([
   ...     [0.0, 0.5, 1.0],
   ...     [0.0, 1.0, 0.0],
   ... ])
   >>> curve1 = bezier.Curve(nodes1, degree=2)

The intersection (points) between two curves can
also be determined:

.. doctest:: getting-started
   :options: +NORMALIZE_WHITESPACE

   >>> nodes2 = np.asfortranarray([
   ...     [0.0, 0.25,  0.5, 0.75, 1.0],
   ...     [0.0, 2.0 , -2.0, 2.0 , 0.0],
   ... ])
   >>> curve2 = bezier.Curve.from_nodes(nodes2)
   >>> intersections = curve1.intersect(curve2)
   >>> intersections
   array([[0.31101776, 0.68898224, 0. , 1. ],
          [0.31101776, 0.68898224, 0. , 1. ]])
   >>> s_vals = np.asfortranarray(intersections[0, :])
   >>> points = curve1.evaluate_multi(s_vals)
   >>> points
   array([[0.31101776, 0.68898224, 0. , 1. ],
          [0.42857143, 0.42857143, 0. , 0. ]])

and then we can plot these curves (along with their
intersections):

.. doctest:: getting-started

   >>> import seaborn
   >>> seaborn.set()
   >>>
   >>> ax = curve1.plot(num_pts=256)
   >>> _ = curve2.plot(num_pts=256, ax=ax)
   >>> lines = ax.plot(
   ...     points[0, :], points[1, :],
   ...     marker="o", linestyle="None", color="black")
   >>> _ = ax.axis("scaled")
   >>> _ = ax.set_xlim(-0.125, 1.125)
   >>> _ = ax.set_ylim(-0.0625, 0.625)

.. testcleanup:: getting-started

   if not mpl_installed:
       sys.modules.pop("matplotlib")
       sys.modules.pop("matplotlib.pyplot")
   if not seaborn_installed:
       sys.modules.pop("seaborn")

.. image:: images/curves1_and_13.png
   :align: center

For API-level documentation, check out the B |eacute| zier Python
:doc:`package <python/reference/bezier>` documentation.

Development
-----------

To work on adding a feature or to run the functional tests, see the
:doc:`DEVELOPMENT doc <development>` for more information on how to get
started.

Citation
--------

For publications that use ``bezier``, there is a `JOSS paper`_ that can be
cited. The following BibTeX entry can be used:

.. code-block:: rest

   @article{Hermes2017,
     doi = {10.21105/joss.00267},
     url = {https://doi.org/10.21105%2Fjoss.00267},
     year = {2017},
     month = {Aug},
     publisher = {The Open Journal},
     volume = {2},
     number = {16},
     pages = {267},
     author = {Danny Hermes},
     title = {Helper for B{\'{e}}zier Curves, Triangles, and Higher Order Objects},
     journal = {The Journal of Open Source Software}
   }

A **particular** version of this library can be cited via a Zenodo DOI; see
a full `list by version`_.

.. _JOSS paper: https://joss.theoj.org/papers/10.21105/joss.00267
.. _list by version: https://zenodo.org/search?page=1&size=20&q=conceptrecid:%22838307%22&sort=-version&all_versions=True

License
-------

``bezier`` is made available under the Apache 2.0 License. For more
details, see `the LICENSE`_.

.. _the LICENSE: https://github.com/dhermes/bezier/blob/main/LICENSE

.. |linux-build| image:: https://github.com/dhermes/bezier/workflows/Linux/badge.svg?branch=main&event=push
   :target: https://github.com/dhermes/bezier/actions?query=workflow%3ALinux
   :alt: Linux Build (GitHub Actions)
.. |macos-build| image:: https://github.com/dhermes/bezier/workflows/macOS/badge.svg?branch=main&event=push
   :target: https://github.com/dhermes/bezier/actions?query=workflow%3AmacOS
   :alt: macOS Build (GitHub Actions)
.. |windows-build| image:: https://github.com/dhermes/bezier/workflows/Windows/badge.svg?branch=main&event=push
   :target: https://github.com/dhermes/bezier/actions?query=workflow%3AWindows
   :alt: Windows Build (GitHub Actions)
.. |pypi| image:: https://img.shields.io/pypi/v/bezier.svg
   :target: https://pypi.org/project/bezier/
   :alt: PyPI Latest
.. |versions| image:: https://img.shields.io/pypi/pyversions/bezier.svg
   :target: https://pypi.org/project/bezier/
   :alt: Package Versions
.. |coverage| image:: https://coveralls.io/repos/github/dhermes/bezier/badge.svg
   :target: https://coveralls.io/github/dhermes/bezier
   :alt: Code Coverage
.. |zenodo| image:: https://zenodo.org/badge/73047402.svg
   :target: https://zenodo.org/badge/latestdoi/73047402
   :alt: Zenodo DOI for ``bezier``
.. |JOSS| image:: https://joss.theoj.org/papers/10.21105/joss.00267/status.svg
   :target: https://dx.doi.org/10.21105/joss.00267
   :alt: "Journal of Open Source Science" DOI for ``bezier``
