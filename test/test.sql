.load ./libh3ext
select printf('%x', latLngToCell(0,0,0));
select printf('%f', cellToLat(latLngToCell(0,0,0)));
select printf('%f', cellToLng(latLngToCell(0,0,0)));
select printf('%x', cellToParent(latLngToCell(0,0,5), 3));
select printf('%x', cellToParent(latLngToCell(0,0,5)));
select printf('%d', getResolution(latLngToCell(0,0,5)));
select printf('%d', getBaseCellNumber(latLngToCell(0,0,5)));
select printf('%s', h3ToString(latLngToCell(0,0,5)));
select printf('%x', stringToH3(h3ToString(latLngToCell(0,0,5))));
select printf('%d', isValidCell(0));
select printf('%d', isValidCell(latLngToCell(0,0,5)));
select printf('%d', isResClassIII(latLngToCell(0,0,5)));
select printf('%d', isResClassIII(latLngToCell(0,0,6)));
select printf('%d', isPentagon(latLngToCell(0,0,5)));
