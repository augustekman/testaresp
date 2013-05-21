<?php

// function initiates everything
function boot() {
  
  
  
}



$devices = array();

$handle = opendir('devices');
while ($file = readdir($handle)) {
  
  if (preg_match('/^[a-z0-9_]+\.device$/', $file)) {
    echo "$file\n";
  }
  
}