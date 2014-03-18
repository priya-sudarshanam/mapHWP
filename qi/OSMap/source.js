
function initialize(){

	// the number of address entries
	var len = Drupal.settings['OSMap'].length;
	var lat;
	var lng;
	var title;
	var addr;
	//var markers = new Array();
	//var infowindows = new Array();
	var infowindow = new google.maps.InfoWindow();
	
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
		title = String(Drupal.settings['OSMap'][i]['title']);
		addr = new google.maps.LatLng(lat,lng);
		
		var marker = new google.maps.Marker({position:addr, 
											 map: map,
											 title:title,
											 animation:google.maps.Animation.DROP});
							
		google.maps.event.addListener(marker, 'mouseover', function() {
							// here we should use 'this' instead of marker
							infowindow.setContent(this.title);
							infowindow.open(map,this);
							});
							
		google.maps.event.addListener(marker, 'mouseout', function() {
							infowindow.close(map,this);
							});
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


