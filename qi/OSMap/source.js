
function initialize(){

	var len = Drupal.settings['OSMap'].length;
	var lat;
	var lng;
	var addr;
	var markers = new Array();
	var infowindows = new Array();
	
	var mapProp = {
		center:new google.maps.LatLng(42.394450, -71.093227),
		zoom:12,
		mapTypeId:google.maps.MapTypeId.ROADMAP,
		
		// disable the default map UI
		disableDefaultUI: true,
		
		// prevents map from being dragged
        draggable: false,
		
		// prevents map from being double click zoomed
		disableDoubleClickZoom: true,
		
		zoomControl: false,
	};
	
	map = new google.maps.Map(document.getElementById("googleMap"), mapProp);
	
	for (var i=0; i<len; i++) {
		lat = Drupal.settings['OSMap'][i]['lat'];
		lng = Drupal.settings['OSMap'][i]['lng'];
		addr = new google.maps.LatLng(lat,lng);
		markers[i] = new google.maps.Marker({position:addr, 
										animation:google.maps.Animation.DROP});
		markers[i].setMap(map);
	}
	
	/*
	var infowindow = new google.maps.InfoWindow({
							content:"Hello World!"
							});

	google.maps.event.addListener(marker1, 'mouseover', function() {
							infowindow.open(map,marker1);
							});
	google.maps.event.addListener(marker1, 'mouseout', function() {
							infowindow.close(map,marker1);
							});
	*/
}

google.maps.event.addDomListener(window, 'load', initialize);


