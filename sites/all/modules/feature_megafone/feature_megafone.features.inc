<?php
/**
 * @file
 * feature_megafone.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function feature_megafone_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_views_api().
 */
function feature_megafone_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function feature_megafone_node_info() {
  $items = array(
    'article' => array(
      'name' => t('Blog Post'),
      'base' => 'node_content',
      'description' => t('Use <em>articles</em> for announcements, news, press releases or blog posts.'),
      'has_title' => '1',
      'title_label' => t('Headline'),
      'help' => '',
    ),
    'coupon_special' => array(
      'name' => t('Coupon/Special'),
      'base' => 'node_content',
      'description' => t('For online coupons or special offers.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'event' => array(
      'name' => t('Calendar Event'),
      'base' => 'node_content',
      'description' => t('Calendar Events are for promoting happening that will take place on a future date. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
