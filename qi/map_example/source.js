function initialize()
{
var mapProp = {
  center:new google.maps.LatLng(42.373573,-71.122887),
  zoom:13,
  mapTypeId:google.maps.MapTypeId.ROADMAP
  };
var map=new google.maps.Map(document.getElementById("googleMap"),mapProp);
}

google.maps.event.addDomListener(window, 'load', initialize);