    // declare icons for various types like university/business etc
    var customIcons = {
      university: {icon: 'http://labs.google.com/ridefinder/images/mm_20_white.png'},
        business: {icon: 'http://labs.google.com/ridefinder/images/mm_20_orange.png'},
        office: {icon: 'http://labs.google.com/ridefinder/images/mm_20_blue.png'},	
    };

    function load() {
	  // declare variables 
	  var mLat = 42.373573;
	  var mLng = -71.122887;
	  var center = new google.maps.LatLng(mLat, mLng);
	  var mapTypeId = 'roadmap';
	  var mId="map";
	  var animation = google.maps.Animation.DROP;
	  var mZoom = 13;
	  // create new map with center at a particular latitude and longitude, zoom and maptype
      var map = new google.maps.Map(document.getElementById(mId), {
        center: center,
        zoom: mZoom,
        mapTypeId: mapTypeId,
      });
	   // create new infoWindow which opens up on hover and on click
      var infoWindow = new google.maps.InfoWindow({
	       map: map,
		   position: center,		
	    });
	  // extract the data from the xml and put it on the map
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
  
