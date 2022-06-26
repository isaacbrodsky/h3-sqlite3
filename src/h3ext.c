/**
 * h3-sqlite3
 * Copyright 2022 Isaac Brodsky
 */

#include "h3ext.h"
#include "sqlite3ext.h"
SQLITE_EXTENSION_INIT1
#include <assert.h>
#include <h3/h3api.h>

static void sql_latLngToCell(sqlite3_context *context, int argc,
                             sqlite3_value **argv) {
  assert(argc == 3);
  // Set to 0 if not a double
  double lat = sqlite3_value_double(argv[0]);
  double lng = sqlite3_value_double(argv[1]);
  LatLng ll = {.lat = lat, .lng = lng};
  int res = sqlite3_value_double(argv[2]);
  H3Index out;
  H3Error err = latLngToCell(&ll, res, &out);
  if (err == E_SUCCESS) {
    sqlite3_result_int64(context, out);
  } else {
    sqlite3_result_error(context, "H3 function call failed", -1);
  }
}

static void sql_cellToLat(sqlite3_context *context, int argc,
                          sqlite3_value **argv) {
  assert(argc == 1);
  H3Index index = sqlite3_value_int64(argv[0]);
  LatLng ll;
  H3Error err = cellToLatLng(index, &ll);
  if (err == E_SUCCESS) {
    sqlite3_result_double(context, ll.lat);
  } else {
    sqlite3_result_error(context, "H3 function call failed", -1);
  }
}

static void sql_cellToLng(sqlite3_context *context, int argc,
                          sqlite3_value **argv) {
  assert(argc == 1);
  H3Index index = sqlite3_value_int64(argv[0]);
  LatLng ll;
  H3Error err = cellToLatLng(index, &ll);
  if (err == E_SUCCESS) {
    sqlite3_result_double(context, ll.lng);
  } else {
    sqlite3_result_error(context, "H3 function call failed", -1);
  }
}

static void sql_cellToParent(sqlite3_context *context, int argc,
                             sqlite3_value **argv) {
  assert(argc == 2 || argc == 1);
  int res;
  H3Index index = sqlite3_value_int64(argv[0]);
  if (argc == 1) {
    res = getResolution(index) - 1;
  } else {
    res = sqlite3_value_int(argv[1]);
  }
  H3Index parent;
  H3Error err = cellToParent(index, res, &parent);
  if (err == E_SUCCESS) {
    sqlite3_result_int64(context, parent);
  } else {
    sqlite3_result_error(context, "H3 function call failed", -1);
  }
}

static void sql_getResolution(sqlite3_context *context, int argc,
                              sqlite3_value **argv) {
  assert(argc == 1);
  H3Index index = sqlite3_value_int64(argv[0]);
  int res = getResolution(index);
  sqlite3_result_int(context, res);
}

#ifdef _WIN32
__declspec(dllexport)
#endif
    int sqlite3_hext_init(sqlite3 *db, char **pzErrMsg,
                          const sqlite3_api_routines *pApi) {
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  (void)pzErrMsg; /* Unused parameter */
  rc = sqlite3_create_function(db, "latLngToCell", 3,
                               SQLITE_UTF8 | SQLITE_INNOCUOUS |
                                   SQLITE_DETERMINISTIC,
                               0, sql_latLngToCell, 0, 0);
  if (rc == SQLITE_OK) {
    rc = sqlite3_create_function(db, "cellToLat", 1,
                                 SQLITE_UTF8 | SQLITE_INNOCUOUS |
                                     SQLITE_DETERMINISTIC,
                                 0, sql_cellToLat, 0, 0);
  }
  if (rc == SQLITE_OK) {
    rc = sqlite3_create_function(db, "cellToLng", 1,
                                 SQLITE_UTF8 | SQLITE_INNOCUOUS |
                                     SQLITE_DETERMINISTIC,
                                 0, sql_cellToLng, 0, 0);
  }
  if (rc == SQLITE_OK) {
    // Infer resolution
    rc = sqlite3_create_function(db, "cellToParent", 1,
                                 SQLITE_UTF8 | SQLITE_INNOCUOUS |
                                     SQLITE_DETERMINISTIC,
                                 0, sql_cellToParent, 0, 0);
  }
  if (rc == SQLITE_OK) {
    rc = sqlite3_create_function(db, "cellToParent", 2,
                                 SQLITE_UTF8 | SQLITE_INNOCUOUS |
                                     SQLITE_DETERMINISTIC,
                                 0, sql_cellToParent, 0, 0);
  }
  if (rc == SQLITE_OK) {
    rc = sqlite3_create_function(db, "getResolution", 1,
                                 SQLITE_UTF8 | SQLITE_INNOCUOUS |
                                     SQLITE_DETERMINISTIC,
                                 0, sql_getResolution, 0, 0);
  }
  return rc;
}
