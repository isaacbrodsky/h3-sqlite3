# h3-sqlite3

[![test-linux](https://github.com/isaacbrodsky/h3-sqlite3/workflows/test-linux/badge.svg)](https://github.com/isaacbrodsky/h3-sqlite3/actions)
[![H3 Version](https://img.shields.io/static/v1?label=h3&message=v4.4.1&color=blue)](https://github.com/uber/h3/releases/tag/v4.4.1)
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

* h3_latlng_to_cell
* h3_cell_to_lat
* h3_cell_to_lng
* h3_cell_to_parent
* h3_get_resolution
* h3_get_base_cell_number​
* h3_string_to_h3​
* h3_h3_to_string​
* h3_is_valid_cell
* h3_is_res_class_iii
* h3_is_pentagon

# TODO

* Better build and CI system, including testing, coverage, etc.
* All H3 functions supported
* Support for [Spatialite](https://www.gaia-gis.it/fossil/libspatialite/index)

# License

Copyright 2022 Isaac Brodsky. Licensed under the [Apache 2 License](./LICENSE).

H3 Copyright 2016 Uber Technologies, Inc.

DGGRID Copyright 2015 Southern Oregon University.
