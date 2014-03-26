(function ($) {
  Drupal.behaviors.testmap = {
    attach: function(context,settings) {
        // Map options.
		$("#delete").click(function(){
           $if(confirm("Do you want to delete?")) {
            this.click;
                  alert("Ok");
              }
           else
           {
               alert("Cancel");
            }       
              });
		
		
		
		

    };

  };
})(jQuery);
