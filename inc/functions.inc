<?php

// function initiates everything
function boot() {
  global $devices;
  // in this area, we should see what the user's actually up to. In some cases, we wouldn't even want to use the base html output.
  
  $full_document_flag = true;
  
  $html = new wireframe('html');
  $html->set('title', 'Responsive tester');
  
  switch (arg(0)) {
    case 'ajax':
      
      $full_document_flag = false;
      break;
    
    case 'device':
      
      $device_id = arg(1, true);
      
      $html->append('body', $devices[$device_id]->render());
      
      break;
    
  }
  
  // make full document if wanted
  if ($full_document_flag) {
    
    $device_list = array();
    
    foreach ($devices as $id => $device) {
      
      $device_list[] = array(
        'content' => $device->name(),
        'link' => array(
          'href' => "/device/$id"
        ),
      );
      
    }
    
    $select_device = new wireframe('item-list', array('items' => $device_list));
    
    $html->append('body', $select_device->render());
    unset($select_device);
    
    print $html->render();
  }
  
}

/**
 * Give requested part of the url.
 */
function arg($n, $int = false) {
  static $args;
  
  if (!isset($args)) {
    $args = explode('/', $_GET['q']);
  }
  
  if (!isset($args[$n])) { return false; }
  if ($int) {
    return intval($args[$n]);
  }
  return $args[$n];
}

// load devices
$devices = array();
$handle = opendir('devices');
while ($file = readdir($handle)) {
  if (preg_match('/^[a-z0-9\-]+\.device$/', $file)) {
    
    require_once("devices/$file");
    $class_name = deviceNameFromFilename($file);
    $devices[] = new $class_name;
  }
}