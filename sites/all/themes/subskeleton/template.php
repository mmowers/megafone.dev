<?php

function subskeleton_preprocess_html(&$variables,$hook) {
  $path = drupal_get_destination();
  $path_cur = current_path();
  $request_path = request_path();
  $path_components_array = explode('/', $path_cur);
  $path_comp_0 = !empty($path_components_array[0]) ? $path_components_array[0] : NULL;
  $path_comp_1 = !empty($path_components_array[1]) ? $path_components_array[1] : NULL;
  $path_comp_2 = !empty($path_components_array[2]) ? $path_components_array[2] : NULL;
  $path_comp_3 = !empty($path_components_array[3]) ? $path_components_array[3] : NULL;
  if($variables['is_front']){
  }
  elseif($path_comp_0=='node' && ($path_comp_1 == 'add' || $path_comp_2=='edit')){
    drupal_add_css(path_to_theme() . '/css/sub-node-add.css', array('weight' => CSS_THEME));
    //drupal_add_js(path_to_theme() . '/js/sub-node-add.js',array('type' => 'file', 'scope' => 'footer', 'weight' => 100, 'group' => JS_THEME));
  }
  elseif($path_cur=='user' || preg_match('#^user/[1-9][0-9]*$#', $path_cur)){
    drupal_add_css(path_to_theme() . '/css/sub-user.css', array('weight' => CSS_THEME));
    //drupal_add_js(path_to_theme() . '/js/sub-user.js',array('type' => 'file', 'scope' => 'footer', 'weight' => 100, 'group' => JS_THEME));
  }
}