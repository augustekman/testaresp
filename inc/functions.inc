<?php

// function initiates everything
function boot() {
  
}

$devices = array();

$handle = opendir('devices');
while ($file = readdir($handle)) {
  if (preg_match('/^[a-z0-9\-]+\.device$/', $file)) {
    
    require_once("devices/$file");
    $class_name = deviceNameFromFilename($file);
    $devices[] = new $class_name;
    
  }
  
}

foreach ($devices as $device) {
  print $device->name();
}