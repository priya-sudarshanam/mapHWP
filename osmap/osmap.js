//This is a file for javascript code for osmap
    <script type="text/javascript" src="http://maps.googleapis.com/maps/api/js?sensor=false"></script>
    <script type="text/javascript">
 
     var customIcons = {
	    university: {icon: 'http://labs.google.com/ridefinder/images/mm_20_white.png'},
        business: {icon: 'http://labs.google.com/ridefinder/images/mm_20_orange.png'},
        office: {icon: 'http://labs.google.com/ridefinder/images/mm_20_blue.png'},	  
       };

    function load() {
	  var center = new google.maps.LatLng(42.373573, -71.122886);
	  var mapTypeId = 'roadmap';
	  var xmlFile = "phpsqlajax_genxml3.php";
	  var zoom = 13;
	  var animation = google.maps.Animation.DROP;
	  
          var map = new google.maps.Map(document.getElementById("map"), {
              center: center,
              zoom: zoom;
              mapTypeId: mapTypeId
	    });
	   
          var infoWindow = new google.maps.InfoWindow({
	       map: map,
	       position: center,
	    });
	    
	  function toggleBounce() {
            if (marker.getAnimation() != null) {
				marker.setAnimation(null);
				} else {
				marker.setAnimation(google.maps.Animation.BOUNCE);
				}
			}

       downloadUrl(xmlFile, function(data) {
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
		                animation: animation,
                     });
                    bindInfoWindow(marker, map, infoWindow, title, html);
                }
        });
    }

    function bindInfoWindow(marker, map, infoWindow, title, html) {
		google.maps.event.addListener(marker, 'click', function() {
			infoWindow.setContent(html);
			infoWindow.open(map, marker);
        });
	    google.maps.event.addListener(marker, 'mouseover', function() {
			infoWindow.setContent(title);
			infoWindow.open(map, marker);
        });
	    google.maps.event.addListener(marker, 'mouseout', function() {
			infoWindow.close();
        });
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
    google.maps.event.addDomListener(window, 'load', load);
 
  </script>

  
