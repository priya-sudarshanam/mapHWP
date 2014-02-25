function initialize(){

	var mapProp = {
		center:new google.maps.LatLng(42.373573,-71.122887),
		zoom:13,
		mapTypeId:google.maps.MapTypeId.ROADMAP
	};
	var map=new google.maps.Map(document.getElementById("googleMap"),mapProp);
	
	var addr1=new google.maps.LatLng(42.373573,-71.122887);
	var marker1=new google.maps.Marker({position:addr1, 
										animation:google.maps.Animation.DROP});
	
	var infowindow = new google.maps.InfoWindow({
							content:"Hello World!"
							});

	google.maps.event.addListener(marker1, 'mouseover', function() {
							infowindow.open(map,marker1);
							});
	google.maps.event.addListener(marker1, 'mouseout', function() {
							infowindow.close(map,marker1);
							});
	
	marker1.setMap(map);
}

google.maps.event.addDomListener(window, 'load', initialize);