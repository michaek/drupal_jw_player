<?php

/**
 * @file
 *   Provides admin settings form(s)
 */

/**
 * General settings form
 */
function jw_player_settings_form($form) {

  drupal_set_title(t('JW Player general settings'));

  $form['jw_player_inline_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use inline javascript'),
    '#description' => t('With this option enabled JW Player configuration will be printed inline directly after the player markup. This can be useful if the player markup is cached as otherwise JW Player will not be loaded. The downside is that the player itself will be loaded on all pages.'),
    '#default_value' => variable_get('jw_player_inline_js', TRUE),
  );

  $provider_options = array();
  $providers = jw_player_provider_load();
  foreach($providers as $name => $provider) {
    $provider_options[$name] = $name;
  }
  
  $form['jw_player_active_providers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Active providers'),
    '#options' => $provider_options,
    '#default_value' => variable_get('jw_player_active_providers', array()),
    '#description' => 'Choose the providers you\'d like your site to support.',
  );

  foreach ($providers as $name => $provider) {
    $fields = $provider->global_settings();
    if (!empty($fields)) {
      $form[$name.'_global_settings'] = array(
        '#type' => 'fieldset',
        '#title' => t('%name Settings', array('%name' => $name)),
      );
      foreach ($fields as $field_name => $field) {
        $key = 'jw_player_'.$name.'_'.$field_name;
        $field['#default_value'] = variable_get($key, '');
        $form[$name.'_global_settings'][$key] = $field;
      }
    }
  }

  return system_settings_form($form);
}