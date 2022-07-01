# h3-sqlite3

[![Coverage Status](https://coveralls.io/repos/github/isaacbrodsky/h3-sqlite3/badge.svg?branch=master)](https://coveralls.io/github/isaacbrodsky/h3-sqlite3?branch=master)
[![test-linux](https://github.com/isaacbrodsky/h3-sqlite3/workflows/test-linux/badge.svg)](https://github.com/isaacbrodsky/h3-sqlite3/actions)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](LICENSE)

h3-sqlite3 provides bindings for the [H3](https://github.com/uber/h3) library to [SQLite3](https://sqlite.org/).

# Compile

Install `libsqlite3-dev` on Debian like systems.

To compile:

```bash
mkdir build
cd build
cmake ..
make
```

TODO: You must compile H3 with `-fPIC` too - this should all be in a single build script!

# Example

Install `sqlite3` on Debian like systems and run `sqlite3`.

```sqlite
.load ./libh3ext
select printf('%x', latLngToCell(0,0,0));
```

You should see `8075fffffffffff` as the output.

# TODO

* Better build and CI system, including testing, coverage, etc.
* All H3 functions supported
* Support for [Spatialite](https://www.gaia-gis.it/fossil/libspatialite/index)
* Support for [DuckDB](https://github.com/duckdb/duckdb/issues/1792)

# License

Copyright 2022 Isaac Brodsky. Licensed under the [Apache 2 License](./LICENSE).

H3 Copyright 2016 Uber Technologies, Inc.

DGGRID Copyright 2015 Southern Oregon University.
