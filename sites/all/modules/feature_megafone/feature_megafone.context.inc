<?php
/**
 * @file
 * feature_megafone.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function feature_megafone_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'business_page';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'user_page' => array(
      'values' => array(
        'view' => 'view',
      ),
      'options' => array(
        'mode' => 'all',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-user_content-block' => array(
          'module' => 'views',
          'delta' => 'user_content-block',
          'region' => 'content',
          'weight' => '15',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;
  $export['business_page'] = $context;

  return $export;
}
