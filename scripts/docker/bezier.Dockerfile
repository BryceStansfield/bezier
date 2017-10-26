FROM dhermes/python-multi

# Install the current versions of nox and NumPy.
RUN pip install --no-cache-dir \
  colorlog==2.10.0 \
  nox-automation==0.18.2 \
  numpy==1.13.3 \
  py==1.4.34 \
  six==1.11.0 \
  virtualenv==15.1.0

# Install `gfortran` (for Fortran extensions), `libatlas-dev`,
# `libblas-dev`, `liblapack-dev` (for SciPy) and `lcov` for
# Fortran code coverage.
RUN apt-get update \
  && apt-get install -y --no-install-recommends \
    gfortran \
    libatlas-dev \
    libblas-dev \
    liblapack-dev \
    lcov \
  && apt-get clean autoclean \
  && apt-get autoremove -y \
  && rm -rf /var/lib/apt/lists/* \
  && rm -f /var/cache/apt/archives/*.deb

# Build NumPy and SciPy wheels for PyPy since it takes a bit of time
RUN virtualenv --python=pypy pypy-env \
  && pypy-env/bin/pip install --upgrade pip wheel \
  && mkdir /wheelhouse \
  && pypy-env/bin/pip wheel --wheel-dir=/wheelhouse numpy==1.13.3 \
  && pypy-env/bin/pip install /wheelhouse/*.whl \
  && pypy-env/bin/pip wheel --wheel-dir=/wheelhouse scipy==1.0.0 \
  && rm -fr pypy-env
