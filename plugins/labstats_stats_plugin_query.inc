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

    //@todo add better error handling here
    //setting server variable
    $myLabstats = variable_get('labstats_stats_server', "");
    if ($myLabstats == '') {
      return;
    }
    // Disabled Cache to ensure the data is current. could result in slower load times
    $ini = ini_set("soap.wsdl_cache_enabled", "0");


    $url = 'http://labstats.ou.edu/api/public/GetPublicApiData/1001';

    $opts = array(
      'http' =>
        array(
          'method' => 'GET',
          'header' => 'Authorization: acf442ce-27d8-406e-bbf5-98a438d13b68'
        )
    );

    $context = stream_context_create($opts);
//    $stream = fopen($url, 'r', FALSE, $context);

    $newfile = file_get_contents($url, false, $context);

    $jsondump = json_decode($newfile);


//    var_dump(stream_get_contents($stream));
//    $objecttry = stream_get_contents($stream);
//    $count = 0;
//
//    $object = new stdClass();
//    foreach ($stream as $key => $value) {
//      $object->$key = $value;
//      $count =+ 1;
//    }
//
//
//    dpm($object);
//    dpm($count);
//    fclose($stream);


//
//    //Creates a SOAP Connection (Change URL to match your installation
//    $client = new SoapClient(variable_get('labstats_stats_server') . '/WebServices/Statistics.asmx?WSDL');
//
//    // Sets variable results to equal the results from our XML request
//    $results = $client->GetGroupedCurrentStats()->GetGroupedCurrentStatsResult->GroupStat;
//
    $parentGroup = $this->options['parentGroupName'];
    $group = $this->options['groupName'];
//
    $totalInUse = 0;
    $totalAvailable = 0;
    $totalOff = 0;
    $totalTotal = 0;
    $totalUnavailable = 0;


    $totalInUse = $jsondump->InUse;
    $totalAvailable = $jsondump->Available;
    $totalOff = $jsondump->Offline;
    $totalTotal = $jsondump->Total;
    $totalUnavailable = 0;
//
//    //loop through results...we don't want what they don't ask for
//    //so if it's not what they entered in the query settings
//    //then we just continue on to the next one
    foreach ($jsondump->Groups as $entry){
      $row = new stdClass();
//      if ($entry->parentGroupName !== $parentGroup){
//        continue;
//      }
//      if ($entry->groupName !== $group && $group !== '') {
//        continue;
//      }
//      $totalInUse += $entry->inUseCount;
//      $totalAvailable += $entry->availableCount;
//      $totalOff += $entry->offCount;
//      $totalTotal += $entry->totalCount;
//      $totalUnavailable += $entry->unavailableCount;
//
      $row->groupName = isset($entry->Label) ? $entry->Label : '';
//      $row->parentGroupName = isset($entry->parentGroupName) ? $entry->parentGroupName : '';
      $row->offCount = isset($entry->Offline) ? $entry->Offline : '-';
      $row->availableCount = isset($entry->Available) ? $entry->Available : '-';
      $row->inUseCount = isset($entry->InUse) ? $entry->InUse : '-';
      $row->totalCount = isset($entry->Total) ? $entry->Total : '-';
      $row->percentInUse = floor(($entry->InUse/$entry->Total)*100);
//      $row->groupDescription = isset($entry->goupDescription) ? $entry->groupDescription : '';
//      $row->unavailableCount = isset($entry->unavailableCount) ? $entry->unavailableCount : '-';
      $view->result[] = $row;
    }
    $row = new stdClass();
    $row->totalInUse = $totalInUse;
    $row->totalAvailable = $totalAvailable;
    $row->totalOff = $totalOff;
    $row->totalTotal = $totalTotal;
    $row->totalUnavailable = $totalUnavailable;
    $row->totalPercent = floor(($totalInUse/$totalTotal) * 100);
    $view->result[] = $row;
//  }
//
//  /**
//   * @return array
//   *
//   * option defaults for query settings
//   */
//  function option_definition() {
//    $options = parent::option_definition();
//
//    $options['groupName'] = array(
//      'default' => '',
//    );
//    $options['parentGroupName'] = array(
//      'default' => '',
//    );
//
//    return $options;
//  }
//
//  /**
//   * @param $form
//   * @param $form_state
//   *
//   * Creating the fields for the query settings view
//   */
//  function options_form(&$form, &$form_state) {
//    $form = parent::options_form($form, $form_state);
//
//    $form['groupName'] = array(
//      '#type' => 'textfield',
//      '#title' => t('Group Name'),
//      '#description' => t('The specific name of the group'),
//      '#default_value' => $this->options['groupName'],
//      '#size' => 20,
//    );
//    $form['parentGroupName'] = array(
//      '#type' => 'textfield',
//      '#title' => t('Parent Group Name'),
//      '#description' => t('The Parent name of the group. (This is required if you want results)'),
//      '#default_value' => $this->options['parentGroupName'],
//      '#size' => 20,
//    );
//  }
  }
}