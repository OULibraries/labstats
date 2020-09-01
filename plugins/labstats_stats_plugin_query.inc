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
    $labstatsAuthID = variable_get('labstats_stats_authID', "");
    if ($labstatsAuthID == '') {
      return;
    }

    drupal_add_js(array('labstats_stats' => array('authID' => $labstatsAuthID)), array
    ('type' => 'setting'));

    // Disabled Cache to ensure the data is current. could result in slower load times
    $ini = ini_set("soap.wsdl_cache_enabled", "0");


    $url = 'http://labstats.ou.edu/api/public/GetPublicApiData/1001';

    $opts = array(
      'http' =>
        array(
          'method' => 'GET',
          'header' => 'Authorization: ' . $labstatsAuthID
        )
    );

    $context = stream_context_create($opts);

    $newfile = file_get_contents($url, false, $context);

    $jsondump = json_decode($newfile);

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

//    //loop through results...we don't want what they don't ask for
//    //so if it's not what they entered in the query settings
//    //then we just continue on to the next one
    foreach ($jsondump->Groups as $entry){
      $row = new stdClass();
      $row->groupName = isset($entry->Label) ? $entry->Label : '';
      $row->offCount = isset($entry->Offline) ? $entry->Offline : '-';
      $row->availableCount = isset($entry->Available) ? $entry->Available : '-';
      $row->inUseCount = isset($entry->InUse) ? $entry->InUse : '-';
      $row->totalCount = isset($entry->Total) ? $entry->Total : '-';
      $row->percentInUse = floor(($entry->InUse/$entry->Total)*100);
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
  }
}