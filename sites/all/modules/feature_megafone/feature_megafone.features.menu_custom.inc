<?php
/**
 * @file
 * feature_megafone.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function feature_megafone_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-biz-nav.
  $menus['menu-biz-nav'] = array(
    'menu_name' => 'menu-biz-nav',
    'title' => 'Biz Nav',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Biz Nav');


  return $menus;
}
