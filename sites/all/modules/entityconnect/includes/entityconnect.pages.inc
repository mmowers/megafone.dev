<?php

/**
 * @file
 * Page callbacks.
 */

/**
 * Returns HTML for a list of available taxonomy vocabularies for term creation.
 *
 * @param array $variables
 *   An associative array containing:
 *   - content: An array of content types.
 *
 * @ingroup themeable
 */
function theme_entityconnect_taxonomy_term_add_list($variables) {
  $output = '';
  $vocabularies = $variables['items'];
  $output = '';
  if ($vocabularies) {
    $output = '<ul class="admin-list">';
    foreach ($vocabularies as $item) {
      $output .= '<li class="clearfix"><span class="label">' . l($item->name, $item->href) . '</span>';
      $output .= '<div class="description">' . filter_xss_admin($item->description) . '</div></li>';
    }
    $output .= '</ul>';
  }
  else {
    $output = '<p>' . t('You have not created any vocabularies yet. Go to the <a href="@create-vocab">vocabularies creation page</a> to add a new vocabulary.', array('@create-vocab' => url('admin/structure/taxonomy/add'))) . '</p>';
  }
  return $output;
}
