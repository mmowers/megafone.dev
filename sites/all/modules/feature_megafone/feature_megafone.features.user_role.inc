<?php
/**
 * @file
 * feature_megafone.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function feature_megafone_user_default_roles() {
  $roles = array();

  // Exported role: guest.
  $roles['guest'] = array(
    'name' => 'guest',
    'weight' => 3,
  );

  return $roles;
}
