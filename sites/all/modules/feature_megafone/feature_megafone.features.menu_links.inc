<?php
/**
 * @file
 * feature_megafone.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function feature_megafone_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-biz-nav:menutoken/51e6fea2d0067
  $menu_links['menu-biz-nav:menutoken/51e6fea2d0067'] = array(
    'menu_name' => 'menu-biz-nav',
    'link_path' => 'menutoken/51e6fea2d0067',
    'router_path' => 'menutoken/%',
    'link_title' => 'Connections',
    'options' => array(
      'menu_token_link_path' => 'user/[current-user:uid]/connections',
      'menu_token_data' => array(
        'user' => array(
          'type' => 'user',
          'plugin' => 'user_context',
          'options' => array(),
        ),
      ),
      'menu_token_options' => array(
        'clear' => 0,
      ),
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
  );
  // Exported menu link: menu-biz-nav:node/add
  $menu_links['menu-biz-nav:node/add'] = array(
    'menu_name' => 'menu-biz-nav',
    'link_path' => 'node/add',
    'router_path' => 'node/add',
    'link_title' => 'Post',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
  );
  // Exported menu link: menu-biz-nav:user
  $menu_links['menu-biz-nav:user'] = array(
    'menu_name' => 'menu-biz-nav',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'Me',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
  );
  // Exported menu link: menu-biz-nav:user/logout
  $menu_links['menu-biz-nav:user/logout'] = array(
    'menu_name' => 'menu-biz-nav',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Logout',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Connections');
  t('Logout');
  t('Me');
  t('Post');


  return $menu_links;
}
