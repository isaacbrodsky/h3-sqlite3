.load ./libh3ext
select printf('%x', latLngToCell(0,0,0));
select printf('%f', cellToLat(latLngToCell(0,0,0)));
select printf('%f', cellToLng(latLngToCell(0,0,0)));
select printf('%x', cellToParent(latLngToCell(0,0,5), 3));
select printf('%x', cellToParent(latLngToCell(0,0,5)));
select printf('%d', getResolution(latLngToCell(0,0,5)));

