#include "sqlite3ext.h"
SQLITE_EXTENSION_INIT1
#include <assert.h>
#include <h3/h3api.h>

static void sql_latLngToCell(sqlite3_context *context, int argc, sqlite3_value **argv) {
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

#ifdef _WIN32
__declspec(dllexport)
#endif
int sqlite3_hext_init(sqlite3 *db,  char **pzErrMsg, const sqlite3_api_routines *pApi) {
    int rc = SQLITE_OK;
    SQLITE_EXTENSION_INIT2(pApi);
    (void)pzErrMsg;  /* Unused parameter */
    rc = sqlite3_create_function(db, "latLngToCell", 3,
                     SQLITE_UTF8|SQLITE_INNOCUOUS|SQLITE_DETERMINISTIC,
                     0, sql_latLngToCell, 0, 0);
    return rc;
}
