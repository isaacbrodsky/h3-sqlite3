# h3-sqlite3

h3-sqlite3 provides bindings for the [H3](https://github.com/uber/h3) library to SQLite3.

# Compile

Install `libsqlite3-dev` on Debian like systems.

To compile:

```bash
cc -g -fPIC -shared h3ext.c -lh3 -o h3ext.so
```

TODO: You must compile H3 with `-fPIC` too - this should all be in a single build script!

# Example

Install `sqlite3` on Debian like systems and run `sqlite3`.

```sqlite
.load ./h3ext
select printf('%X', latLngToCell(0,0,0));
```

You should see `8075FFFFFFFFFFF` as the output.

# TODO

* Better build and CI system
* All H3 functions supported
* Support for [Spatialite](https://www.gaia-gis.it/fossil/libspatialite/index)
* Support for [DuckDB](https://github.com/duckdb/duckdb/issues/1792)

# License

Copyright 2022 Isaac Brodsky. Licensed under the [Apache 2 License](./LICENSE).

H3 Copyright 2016 Uber Technologies, Inc.

DGGRID Copyright 2015 Southern Oregon University.
