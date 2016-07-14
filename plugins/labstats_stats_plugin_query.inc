<?php

/**
 * @file
 *   Views query plugin for labstats stats.
 */
class labstats_stats_plugin_query extends views_plugin_query {

  function query($get_count = FALSE) {
  }

  /**
   * @param view $view
   * gets number live counts from labstats
   */
  function execute(&$view) {
    // Disabled Cache to ensure the data is current. could result in slower load times
    $ini = ini_set("soap.wsdl_cache_enabled", "0");

    //Creates a SOAP Connection (Change URL to match your installation
    $client = new SoapClient("http://labstats.ou.edu/WebServices/Statistics.asmx?WSDL");

    // Sets variable results to equal the results from our XML request
    $results = $client->GetGroupedCurrentStats()->GetGroupedCurrentStatsResult->GroupStat;

    $parentGroup = $this->options['parentGroupName'];
    $group = $this->options['groupName'];

    //loop through results...we don't want what they don't ask for
    //so if it's not what they entered in the query settings
    //then we just continue on to the next one
    foreach ($results as $entry){
      $row = new stdClass();
      if ($entry->parentGroupName !== $parentGroup){
        continue;
      }
      if ($entry->groupName !== $group && $group !== '') {
        continue;
      }
      $row->groupName = $entry->groupName;
      $row->parentGroupName = $entry->parentGroupName;
      $row->offCount = $entry->offCount;
      $row->availableCount = $entry->availableCount;
      $row->inUseCount = $entry->inUseCount;
      $row->totalCount = $entry->totalCount;
      $row->percentInUse = floor(($entry->percentInUse)*100);
      $row->groupDescription = $entry->goupDescription;
      $row->unavailableCount = $entry->unavailableCount;
      $view->result[] = $row;
    }
  }

  /**
   * @return array
   *
   * option defaults for query settings
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['groupName'] = array(
      'default' => '',
    );
    $options['parentGroupName'] = array(
      'default' => '',
    );

    return $options;
  }

  /**
   * @param $form
   * @param $form_state
   *
   * Creating the fields for the query settings view
   */
  function options_form(&$form, &$form_state) {
    $form = parent::options_form($form, $form_state);

    $form['groupName'] = array(
      '#type' => 'textfield',
      '#title' => t('Group Name'),
      '#description' => t('The specific name of the group'),
      '#default_value' => $this->options['groupName'],
      '#size' => 20,
    );
    $form['parentGroupName'] = array(
      '#type' => 'textfield',
      '#title' => t('Parent Group Name'),
      '#description' => t('The Parent name of the group. (This is required if you want results)'),
      '#default_value' => $this->options['parentGroupName'],
      '#size' => 20,
    );
  }
}