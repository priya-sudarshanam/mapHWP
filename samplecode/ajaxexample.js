(function ($) {
    Drupal.behaviors.ajaxexample = {
            attach:function(context, settings){
                    $("#ajax-example-link").click(function()  {
                      $("#ajax-display").text('thank you');
      });;
            }
    };
})(jQuery);
