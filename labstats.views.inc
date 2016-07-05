<?php

/**
 * Implements hook_views_plugins().
 */
function labstats_views_plugins() {
  $plugin = array();
  $plugin['query']['labstats_plugin_query'] = array(
    'title' => t('Labstats Query'),
    'help' => t('Labstats query object.'),
    'handler' => 'labstats_plugin_query',
  );
  return $plugin;
}

/**
 * Implements hook_views_data().
 */
function labstats_views_data() {
  $data = array();

  //Base data
  $data['labstats']['table']['group'] = t('Labstats Stats');
  $data['labstats']['table']['base'] = array(
    'title' => t('Labstats Stats'),
    'help' => t('Query Labstats Stats'),
    'query class' => 'labstats_plugin_query'
  );

  //Fields
  $data['labstats']['title'] = array(
    'title' => t('Title'),
    'help' => t('The title of this report'),
    'field' => array(
      'handler' => 'labstats_handler_field',
    ),
  );

  return $data;
}