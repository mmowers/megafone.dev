jQuery(document).ready(function() {
    jQuery('#'+form_id).sisyphus({
        timeout: time,

        onSave: function() {
            jQuery.jnotify('Data are saved to Local Storage', 500);
        },
        onRestore: function() {
            jQuery.jnotify('Data are restored from Local Storage', 500);
        },
        onRelease: function() {
            jQuery.jnotify('Data are removed from Local Storage', 'warning', 500);
        }
    });
});