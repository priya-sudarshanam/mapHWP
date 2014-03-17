(function ($) {
  Drupal.behaviors.simple_gmap = {
    attach: function(context,settings) {
        // Map options.
             var map;
             function initialize() {
			 var mapOptions = {
                    zoom: 8,
                    center: new google.maps.LatLng(-34.397, 150.644),
					mapTypeId:google.maps.MapTypeId.ROADMAP
              };
             map = new google.maps.Map(document.getElementById("googleMap"),mapOptions);
            }

           google.maps.event.addDomListener(window, 'load', initialize);
    }
  };
})(jQuery);
