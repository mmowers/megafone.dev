<?php

/**
 * Implementation of hook_views_data_alter().
 */
function views_autorefresh_views_data_alter(&$data) {
  // Add our autorefresh area to Global.
  $data['views']['autorefresh'] = array(
    'title' => t('Autorefresh config'),
    'help' => t('Enable autorefresh for this view.'),
    'area' => array(
      'handler' => 'views_autorefresh_handler_area_autorefresh',
    ),
  );

  foreach ($data as $table_name => $table_info) {
    foreach ($table_info as $field_name => $field_info) {
      // Add an operator-based date handler to all date arguments.
      if (!empty($field_info['field']['handler']) && $field_info['field']['handler'] == 'views_handler_field_date') {
        $date = $field_info;
        $date['title'] = $field_info['title'] . ' (with operator)';
        $date['argument']['handler'] = 'views_autorefresh_handler_argument_date';
        $date['argument']['field'] = empty($date['field']['field']) ? $field_name : $date['field']['field'];
        unset($date['filter'], $date['field'], $date['relationship'], $date['sort']);
        $data[$table_name][$field_name . '_operator'] = $date;
      }
    }

    // Add an operator-based argument on the primary field of each base table.
    $field_name = @$table_info['table']['base']['field'];
    if (!empty($field_name) && is_string($field_name) && !empty($table_info[$field_name])) {
      $field_info = $table_info[$field_name];
      if (!empty($field_info['argument']['handler'])) {
        $base = $field_info;
        $base['title'] = $field_info['title'] . ' (with operator)';
        $base['argument']['handler'] = 'views_autorefresh_handler_argument_base';
        $base['argument']['field'] = $field_name;
        unset($base['filter'], $base['field'], $base['relationship'], $base['sort']);
        $data[$table_name][$field_name . '_operator'] = $base;
      }
    }
  }
}

