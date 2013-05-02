<?php


/**
 * Form callback for general settings.
 */
function fb_stream_admin_settings() {
  $form = array();

  $token = variable_get(FB_STREAM_VAR_TOKEN, '');

  if ($token && empty($_POST) && empty($_REQUEST['code'])) {
    try {
      // TODO: consolodate graph api, use batch.
      $from = fb_graph('me', array('access_token' => $token));
      $via = fb_graph('app', array('access_token' => $token));
      // Show helpful messages about the current access token.
      $form['fb_stream_current_token'] = array(
        '#type' => 'fieldset',
        '#title' => t('Current token'),
        '#description' => t('The current token allows posting by %user_name via the %app_name application.', array(
                              '%app_name' => $via['name'],
                             '%user_name' => $from['name'],
                             '%token' => $token,
                            )),
      );
      $form['fb_stream_current_token']['token'] = array(
        '#type' => 'fieldset',
        '#title' => t("Show current token"),
        '#description' => $token,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      try {
        $accounts = fb_graph('me/accounts', array('access_token' => $token));
        if (!empty($accounts) && !empty($accounts['data'])) {
          // TODO: support pagination if not all accounts returned.
          $form['fb_stream_accounts'] = array(
            '#title' => t('Page-specific Tokens'),
            '#type' => 'fieldset',
            '#collapsible' => TRUE,
            '#description' => t('These tokens are derived from the current token.  Choose a page-specific token to limit this server to posting on just one page.  To do so, copy and paste the token into the form field below.'),
          );
          // TODO: perhaps a radio button would be better then forcing user to copy and paste.
          foreach ($accounts['data'] as $account_data) {
            $rows[] = array(t('%fb_page_title (%fb_page_type)', array(
                                '%fb_page_title' => $account_data['name'],
                                '%fb_page_type' => $account_data['category'],
                              )),
                            $account_data['access_token'],
            );
          }
          $form['fb_stream_accounts']['detail'] = array(
            '#type' => 'markup',
            '#markup' => theme('table', array(
                'header' => array(t('Page'), t('Access token')),
                'rows' => $rows,
              )),
          );
        }
      }
      catch (Exception $e) {
        // If me/accounts fails, it probably just means the token is already an account token and not a user token.  Nothing to do here.
      }
    }
    catch (Exception $e) {
      fb_log_exception($e, t('Unable to query graph with fb_stream token.'));
      drupal_set_message(t('There was an error using the current access token, %token.  Consider generating a new token.', array(
                             '%token' => $token,
                           )), 'error');
    }
  }

  if (!empty($_REQUEST['code']) && empty($_POST)) {
    // Send user to this URL after token is generated.
    $redirect_uri = url(request_path(), array(
                          'absolute' => TRUE,
                          'query' => array(
                            'client_id' => $_REQUEST['client_id'],
                          ),
                        ));

    $token = fb_stream_admin_code_to_token($_REQUEST['code'], $_REQUEST['client_id'], $redirect_uri);
    if ($token) {
      drupal_set_message(t('Generated a new access token, but not yet saved, %token .  Note you must press the save button to use this value!', array('%token' => $token)), 'warning');
    }
    else {
      drupal_set_message(t('Failed to generate a token from code returned by facebook.'), 'warning');
    }
  }

  $form['fb_stream_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Access Token'),
    '#default_value' => $token,
    '#description' => t('Use <a href=!url target=_blank>Facebook\'s Graph Explorer</a> to generate a token you can copy and paste into this form. <br/><em>For best results your token should include the publish_stream, manage_pages, and offline_access extended permissions</em>.', array(
                          '!url' => 'https://developers.facebook.com/tools/explorer',
                        )),
    '#required' => TRUE,
    '#maxlength' => 255, // Drupal defaults to 128.
  );

  $form['fb_stream_token_prefer_long'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prefer longer-lived tokens.'),
    '#description' => t('Some Facebook access tokens expire in minutes, or when user logs out of facebook.com. Longer lived tokens can last weeks before expiring.  Facebook no longer offers access that never expire.'),
    '#default_value' => variable_get('fb_stream_token_prefer_long', TRUE),
  );


  // TODO: show user what permissions and pages their token can access.

  $form['fb_stream_apps'] = array(
    '#type' => 'fieldset',
    '#title' => t('Access Token Generator'),
    '#description' => t('Generate a token for a local application.  The new token will be placed in the form field above.'),
  );

  foreach (fb_get_all_apps() as $fb_app) {
    // Send user to this URL after token is generated.
    $redirect_uri = url(request_path(), array(
                          'absolute' => TRUE,
                          'query' => array(
                            'client_id' => $fb_app->id,
                          ),
                        ));

    $form['fb_stream_apps'][$fb_app->id] = array(
      '#type' => 'markup',
      '#markup' => l(t('post via the %title application', array(
                        '%title' => $fb_app->title,
                      )),
                    // Important to get the scope right
                    url("https://www.facebook.com/dialog/oauth", array(
                          'query' => array(
                            'scope' => 'publish_stream,offline_access,manage_pages',
                            'client_id' => $fb_app->id,
                            'redirect_uri' => $redirect_uri,
                          ),
                        )), array('html' => TRUE)),
      '#prefix' => '<p>', '#suffix' => '</p>',
    );
  }

  // Our validate hook gives us a way to swap long-lived tokens for shorter ones.
  $form['#validate'][] = '_fb_stream_validate_token';

  return system_settings_form($form);
}

function _fb_stream_validate_token($form, &$form_state) {
  $values = $form_state['values'];
  $token = $values['fb_stream_token'];
  try {
    $via = fb_graph('app', array('access_token' => $token));

    if ($values['fb_stream_token_prefer_long']) {
      $app = fb_get_app(array('id' => $via['id']));

      if ($app && $app->secret) {
        try {
          $result = fb_graph('oauth/access_token', array(
                               'client_id' => $app->id,
                               'client_secret' => $app->secret,
                               'grant_type' => 'fb_exchange_token',
                               'fb_exchange_token' => $token,
                             ));
          if (!empty($result['access_token'])) {
            if ($result['access_token'] != $token) {
              form_set_value($form['fb_stream_token'], $result['access_token'], $form_state);
              drupal_set_message(t('Using longer-lived token %token , which is set to expire in %duration.', array(
                    '%token' => $result['access_token'],
                    '%duration' => format_interval($result['expires']),
                  )));
            }
            else {
              drupal_set_message(t('Token is long-lived, set to expire in %duration.', array(
                                     '%token' => $result['access_token'],
                                     '%duration' => format_interval($result['expires']),
                                   )));
            }
          }
        }
        catch (Exception $e) {
          // This is reached whenever token belongs to an account instead of a user.  So we don't need to be verbose about it.
          drupal_set_message(t('Could not convert the token into a longer-lived token.  This is expected when token belongs to a page rather than a user.'));
          //fb_log_exception($e, t('Failed to convert token to longer-lived token.'));
        }
      }
    }
  }
  catch (Exception $e) {
    fb_log_exception($e, t('Unable to validate fb_stream token (%token).',array('%token' => $token)));
    form_set_error('fb_stream_token', $e->getMessage());
  }
}


function fb_stream_admin_code_to_token($code, $app_id, $redirect_uri) {
  $fb_app = fb_get_app(array('id' => $app_id));
  $path = url("https://graph.facebook.com/oauth/access_token", array(
                'query' => array(
                  'client_id' => $app_id,
                  'client_secret' => $fb_app->secret,
                  'code' => $code,
                  'redirect_uri' =>$redirect_uri,
                ),
              ));
  $http = drupal_http_request($path);
  if ($http->code == 200 && isset($http->data)) {
    $data = array();
    parse_str($http->data, $data);
    return $data['access_token'];
  }
}
