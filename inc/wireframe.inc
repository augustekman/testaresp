<?php

/**
 *
 *** @wireframe.inc
 *
 * template handling class.
 *
 * By August Ekman Öhrn
 *
 */

class wireframe {
  
  private $wireframe_file;
  private $variables;
  private $pre_render;
  
  // constructor, selects wireframe file and initiates variables.
  function __construct($name, $init_variables = array()) {
    $this->variables = array();
    $this->pre_render = array();
    if (!empty($init_variables)) $this->multi_set($init_variables);
    $this->wireframe_file = "wireframes/$name.tpl.php";
  }
  
  // set single variable value
  public function set ($key, $value) {
    $this->variables[$key] = $value;
  }
  
  // prepend variable value
  public function prepend ($key, $value) {
    if (isset($this->variables[$key])) {
      $this->variables[$key] = $value . $this->variables[$key];
    }
    else {
      $this->variables[$key] = $value;
    }
  }
  
  // append variable value
  public function append ($key, $value) {
    if (isset($this->variables[$key])) {
      $this->variables[$key] .= $value;
    }
    else {
      $this->variables[$key] = $value;
    }
  }
  
  // set multiple variable values.
  public function multi_set ($new_variables = array()) {
    $this->variables = array_merge($this->variables, $new_variables);
  }
  
  // render wireframe!
  public function render () {
    if (isset($this->pre_render)) {
      foreach ($this->pre_render as $preprocess) {
        $this->$preprocess();
      }
    }
    extract($this->variables, EXTR_SKIP);
    ob_start();
    include($this->wireframe_file);
    return ob_get_clean();
  }
  
}