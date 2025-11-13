.load ./libh3ext
select printf('%x', h3_latlng_to_cell(0,0,0));
select printf('%f', h3_cell_to_lat(h3_latlng_to_cell(0,0,0)));
select printf('%f', h3_cell_to_lng(h3_latlng_to_cell(0,0,0)));
select printf('%x', h3_cell_to_parent(h3_latlng_to_cell(0,0,5), 3));
select printf('%x', h3_cell_to_parent(h3_latlng_to_cell(0,0,5)));
select printf('%d', h3_get_resolution(h3_latlng_to_cell(0,0,5)));
select printf('%d', h3_get_base_cell_number(h3_latlng_to_cell(0,0,5)));
select printf('%s', h3_h3_to_string(h3_latlng_to_cell(0,0,5)));
select printf('%x', h3_string_to_h3(h3_h3_to_string(h3_latlng_to_cell(0,0,5))));
select printf('%d', h3_is_valid_cell(0));
select printf('%d', h3_is_valid_cell(h3_latlng_to_cell(0,0,5)));
select printf('%d', h3_is_res_class_iii(h3_latlng_to_cell(0,0,5)));
select printf('%d', h3_is_res_class_iii(h3_latlng_to_cell(0,0,6)));
select printf('%d', h3_is_pentagon(h3_latlng_to_cell(0,0,5)));
