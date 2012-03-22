<?php

$plugin = array(
  'provider' => 'LimelightVideoProvider',
);

require_once('AbstractVideoProvider.class.php');

class LimelightVideoProvider extends AbstractVideoProvider {
  
  public function process_url(&$url, &$settings) {
    $parts = drupal_parse_url($url);
    extract(drupal_parse_url($url));
    
    // TODO: determine a real way to identify this provider.
    if (strpos($path, '/') == '0') {
      $settings['#streamer'] = variable_get('jw_player_limelight_streamer_url');
    }
  }
  
  public function global_settings() {
    $form['streamer_url'] = array(
      '#type' => 'textfield',
      '#title' => 'Streamer URL',
    );
    return $form;
  }
  
}
