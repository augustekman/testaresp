<?php

/**
 * 
 */

class device {
  
  protected $width;
  protected $height;
  
  protected $dX;
  protected $dY;
  
  protected $screenshot;
  protected $name;
  
  protected $description;
  
  public function render () {
    
  }
  
  public function name () {
    return $this->name;
  }

  
}


function deviceNameFromFilename($filename) {
  return str_replace(array('.device', '-'), array('', '_'), $filename);
}