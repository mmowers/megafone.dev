<?php

function subskeleton_preprocess_html(&$variables,$hook) {
  $path = drupal_get_destination();
  $path_cur = current_path();
  $request_path = request_path();
  $path_components = explode('/', $path_cur);
  if($variables['is_front']){
  }
  elseif($path_components[0]=='node' && ($path_components[1] == 'add' || $path_components[2]=='edit')){
    drupal_add_css(path_to_theme() . '/css/sub-node-add.css', array('weight' => CSS_THEME));
    //drupal_add_js(path_to_theme() . '/js/sub-node-add.js',array('type' => 'file', 'scope' => 'footer', 'weight' => 100, 'group' => JS_THEME));
  }
}