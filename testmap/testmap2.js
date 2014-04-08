(function ($) {
    Drupal.ajax['#delete'].beforeSerialize = function () {  

          if(confirm('Are you sure?'))
              return true;
          else
              return false;

      }

})(jQuery); 

