<!DOCTYPE html >
  <head>
    <meta name="viewport" content="initial-scale=1.0, user-scalable=no" />
    <meta http-equiv="content-type" content="text/html; charset=UTF-8"/>
    <title>PHP/MySQL & Google Maps Example</title>
    <script type="text/javascript" src="http://maps.googleapis.com/maps/api/js?sensor=false"></script>
    <script type="text/javascript">
    //<![CDATA[

    var customIcons = {
      university: {icon: 'http://labs.google.com/ridefinder/images/mm_20_white.png'},
        business: {icon: 'http://labs.google.com/ridefinder/images/mm_20_orange.png'},
        office: {icon: 'http://labs.google.com/ridefinder/images/mm_20_blue.png'},	
    };

    function load() {
	  var mLat = 42.373573;
	  var mLng = -71.122887;
	  var center = new google.maps.LatLng(mLat, mLng);
	  var mapTypeId = 'roadmap';
	  var mId="map";
	  var animation = google.maps.Animation.DROP;
	  var mZoom = 13;
	  
      var map = new google.maps.Map(document.getElementById(mId), {
        center: center,
        zoom: mZoom,
        mapTypeId: mapTypeId,
      });
      var infoWindow = new google.maps.InfoWindow({
	       map: map,
		   position: center,		
	    });
      downloadUrl("osmap.xml", function(data) {
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
      var request = window.ActiveXObject ?
          new ActiveXObject('Microsoft.XMLHTTP') :
          new XMLHttpRequest;

      request.onreadystatechange = function() {
        if (request.readyState == 4) {
          request.onreadystatechange = {};
          callback(request, request.status);
        }
      };
      request.open('GET', url, true);
      request.send(null);
    }
  </script>
  </head>
  <body onload="load()">
    <div id="map" style="width: 500px; height: 300px"></div>
  </body>

</html>
