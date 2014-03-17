(function ($) {
  Drupal.behaviors.simple_gmap = {
    attach: function(context,settings) {
        // Map options.
             var map;
			 var centerLat=42.373573;
			 var centerLng=-71.122887;
			 var center= new google.maps.LatLng(centerLat,centerLng);
			 var content = 'HWP';
			 var zoom = 13;
			 var infoWindow = new google.maps.InfoWindow({
			        content: content});
			 var mapTypeId = 'roadmap';
			 var animation = google.maps.Animation.DROP;
			 var customIcons = {
                 university: {icon: 'http://labs.google.com/ridefinder/images/mm_20_white.png'},
                 business: {icon: 'http://labs.google.com/ridefinder/images/mm_20_orange.png'},
                 office: {icon: 'http://labs.google.com/ridefinder/images/mm_20_blue.png'},	
              };
			 
             function initialize() {
			    var mapOptions = {
                    zoom: zoom,
                    center: center,
					mapTypeId:mapTypeId
              };
             map = new google.maps.Map(document.getElementById("googleMap"),mapOptions);
			 
			 downloadUrl("sample_map/xml", function(data) {
                var xml = data.responseXML;
                var markers = xml.documentElement.getElementsByTagName("marker");
                   for (var i = 0; i < markers.length; i++) {
                        var name = markers[i].getAttribute("name");
                        var address = markers[i].getAttribute("address");
                        var type = markers[i].getAttribute("type");
                        var point = new google.maps.LatLng(parseFloat(markers[i].getAttribute("lat")),parseFloat(markers[i].getAttribute("lng")));
                        var html = "<b>" + name + "</b> <br/>" + address;
                        var icon = customIcons[type] || {};
		                var title = markers[i].getAttribute("title");
                        var marker = new google.maps.Marker({
											map: map,
											position: point,
											icon: icon.icon,
											animation: animation		                               
                        });
                      bindInfoWindow(marker, map, infoWindow,title,html);
				 	}
              });
			 					
            }
			// open the infoWindow on mouseover, mouseclick and mouseout
				function bindInfoWindow(marker, map, infoWindow, title, html) {
					google.maps.event.addListener(marker, 'click', function() {
							infoWindow.setContent(html);
							infoWindow.open(map, marker);
					});
					google.maps.event.addListener(marker, 'mouseover', function() {
						infoWindow.setContent(title);
						infoWindow.open(map, marker);
					});
					/* google.maps.event.addListener(marker, 'mouseout', function() {
						infoWindow.close();
					}); */
				}

				function downloadUrl(url, callback) {
					var request = window.ActiveXObject ? new ActiveXObject('Microsoft.XMLHTTP') : new XMLHttpRequest;

					request.onreadystatechange = function() {
					if (request.readyState == 4) {
							request.onreadystatechange = {};
							callback(request, request.status);
				  	    }
					};
                   request.open('GET', url, true);
                   request.send(null);
                }

           google.maps.event.addDomListener(window, 'load', initialize);
    }
  };
})(jQuery);