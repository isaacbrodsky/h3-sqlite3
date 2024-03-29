# h3-sqlite3

[![test-linux](https://github.com/isaacbrodsky/h3-sqlite3/workflows/test-linux/badge.svg)](https://github.com/isaacbrodsky/h3-sqlite3/actions)
[![H3 Version](https://img.shields.io/static/v1?label=h3&message=v4.0.0&color=blue)](https://github.com/uber/h3/releases/tag/v4.0.0)
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

# Implemented functions

* latLngToCell
* cellToLat
* cellToLng
* cellToParent
* getResolution
* getBaseCellNumber​
* stringToH3​
* h3ToString​
* isValidCell
* isResClassIII​
* isPentagon

# TODO

* Better build and CI system, including testing, coverage, etc.
* All H3 functions supported
* Support for [Spatialite](https://www.gaia-gis.it/fossil/libspatialite/index)

# License

Copyright 2022 Isaac Brodsky. Licensed under the [Apache 2 License](./LICENSE).

H3 Copyright 2016 Uber Technologies, Inc.

DGGRID Copyright 2015 Southern Oregon University.
