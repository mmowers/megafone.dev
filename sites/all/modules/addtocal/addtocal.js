(function($) {
  Drupal.behaviors.addtocal = {
    attach: function(context) {
      // Handle toggle event to position the menu properly
      jQuery('#addtocal').toggle(function(e) {
        var offset = jQuery(this).position();
        
        jQuery('#addtocal_menu').css({
          'top': offset.top + 20,
          'left': offset.left
        });
        
        //Clicking outside the menu will hide it
        jQuery(document).bind('click', function() {
          jQuery('#addtocal_menu').hide();
        });
      }, function() {
        
      });
      
      // Toggle the menu when the button is clicked
      jQuery('#addtocal').click(function(e) {
        jQuery('#addtocal_menu').toggle();
      });
    }
  } 
})(jQuery);