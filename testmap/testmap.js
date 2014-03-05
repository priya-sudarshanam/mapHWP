(function ($) {
  Drupal.behaviors.map_sample = {
    attach: function(context,settings) {
        // Map options.
		function init(){
		     var centerLat=42.373573;
			 var centerLng=-71.122887;
			 var center= new google.maps.LatLng(centerLat,centerLng);
			 var content = 'HWP';
			 var zoom = 13;
			 var mapTypeId = 'roadmap';
			 var animation = google.maps.Animation.DROP;
			 var customIcons = {
			     center: {icon: 'http://labs.google.com/ridefinder/images/mm_20_.png'},
                 university: {icon: 'http://labs.google.com/ridefinder/images/mm_20_white.png'},
                 business: {icon: 'http://labs.google.com/ridefinder/images/mm_20_orange.png'},
                 office: {icon: 'http://labs.google.com/ridefinder/images/mm_20_blue.png'},	
              };
			 var infoWindow = new google.maps.InfoWindow({
			        content: content});
     	     var mapProp = {
					center:new google.maps.LatLng(centerLat,centerLng),
					zoom:zoom,
					center: center,
					mapTypeId:mapTypeId
			};
			 var map=new google.maps.Map(document.getElementById("googleMap"),mapProp);
			 var settingArray=Drupal.settings['testmap'];
			 var settingLen = settingArray.length;
			 for (var i = 0; i < settingLen; i++) {
                 var name = settingArray[i]['name'];
                 var address = settingArray[i]['address'];
                 var type = settingArray[i]['type'];
			     var icon = customIcons[settingArray[i]['type']] || {};
                 var point = new google.maps.LatLng(parseFloat(settingArray[i]['lat']),parseFloat(settingArray[i]['lng']));
                 var html = "<b>" + name + "</b> <br/>" + address; 
                 var title = settingArray[i]['title'];
                 var marker = new google.maps.Marker({
											map: map,
											position: point,
											icon: icon.icon,
											animation: animation		                               
                        });
                      bindInfoWindow(marker, map, infoWindow,type,html); 
				 	}
			 
				}

		      function bindInfoWindow(marker, map, infoWindow, type, html) {
					google.maps.event.addListener(marker, 'click', function() {
							infoWindow.setContent(html);
							infoWindow.open(map, marker);
					});
					google.maps.event.addListener(marker, 'mouseover', function() {
						infoWindow.setContent(type);
						infoWindow.open(map, marker);
					});
				}

            

			google.maps.event.addDomListener(window, 'load', init);
    }
  };
})(jQuery);
