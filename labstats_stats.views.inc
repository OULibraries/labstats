<?php
drupal_add_js(drupal_get_path('module', 'labstats_stats') . '/labstats_stats.js');
drupal_add_css('https://labstats.ou.edu/Content/MapViewer.css', 'external');
drupal_add_js('https://cdn.jsdelivr.net/excanvas/r3/excanvas.compiled.js', 'external');
drupal_add_js('https://labstats.ou.edu/Scripts/MapViewer.js', 'external');
drupal_add_css(drupal_get_path('module', 'labstats_stats') . '/labstats_style.css');

/**
 * Implements hook_views_plugins().
 */
function labstats_stats_views_plugins() {
  $plugin = array();
  $plugin['query']['labstats_stats_plugin_query'] = array(
    'title' => t('Labstats Query'),
    'help' => t('Labstats query object.'),
    'handler' => 'labstats_stats_plugin_query',
  );
  return $plugin;
}

/**
 * Implements hook_views_data().
 *
 * The fields that the user gets to choose from to display
 */
function labstats_stats_views_data() {
  $data = array();

  //Base data
  $data['labstats_stats']['table']['group'] = t('Labstats Stats');
  $data['labstats_stats']['table']['base'] = array(
    'title' => t('Labstats Stats'),
    'help' => t('Query Labstats Stats'),
    'query class' => 'labstats_stats_plugin_query'
  );

  //Fields
  $data['labstats_stats']['groupName'] = array(
    'title' => t('Group Name'),
    'help' => t('The Group Name of this area'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['groupDescription'] = array(
    'title' => t('Group Description'),
    'help' => t('The Group Description of this area'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['availableCount'] = array(
    'title' => t('Available'),
    'help' => t('The number of available units'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['unavailableCount'] = array(
    'title' => t('Unavailable'),
    'help' => t('The number of unavailable units'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['inUseCount'] = array(
    'title' => t('In Use'),
    'help' => t('The number of in use units'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['totalCount'] = array(
    'title' => t('Total'),
    'help' => t('The total number of units in this area'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['totalInUse'] = array(
    'title' => t('Total In Use'),
    'help' => t('The total number of units in use in all areas'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['totalAvailable'] = array(
    'title' => t('Total Available'),
    'help' => t('The total number of units available in all areas'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['totalOff'] = array(
    'title' => t('Total Off'),
    'help' => t('The total number of units off in all areas'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['totalTotal'] = array(
    'title' => t('Total of Totals'),
    'help' => t('The total of all the totals in all areas'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['totalUnavailable'] = array(
    'title' => t('Total Unavailable'),
    'help' => t('The total number of units unavailable in all areas'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['totalPercent'] = array(
    'title' => t('Total Percent In Use'),
    'help' => t('The percent of all in use'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['percentInUse'] = array(
    'title' => t('Percent in Use'),
    'help' => t('The percent of total number of units in this area that are in use'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['parentGroupName'] = array(
    'title' => t('Parent Group Name'),
    'help' => t('Name of the Parent Group'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );
  $data['labstats_stats']['offCount'] = array(
    'title' => t('Off Count'),
    'help' => t('The number of units turned off'),
    'field' => array(
      'handler' => 'labstats_stats_handler_field',
    ),
  );

  return $data;
}