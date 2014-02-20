/* (function($) {
  Drupal.behaviors.ajaxexample = {
    attach: function (context, settings) {
	  $('#ajax-display').text('thank you');
    }
	};
})(jQuery); */

(function ($) {
Drupal.behaviors.osmap = {
attach: function (context, settings) {

$('#ajax-display', context).once('ajaxexample', function() {

  $('#ajax-display').text('hello');
 });

// Define functions here

};
})(jQuery);
