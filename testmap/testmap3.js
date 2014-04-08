(function ($) {
  Drupal.behaviors.custom_redirect = {
    attach: function() {
      // Replace he form id and the select id in selecotor below.
      $("form#add select#add").change(function(e) {
        e.stopPropagation();
        // Path where you want to redirect.
        var redirect_url = 'testmap/list';
        window.location.pathname = redirect_url;
      });
    }
  };
}(jQuery));