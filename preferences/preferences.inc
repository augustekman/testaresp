<?php

/**
 *
 *** @preferences.inc
 *
 * preferences for hu25.
 *
 * By August Ekman Öhrn and Snick-Snack AB
 *
 */


// the default settings in the preferences class can be overridden by different preference methods that might be implemented or read at a later stage.

class preferences {
  
  private $preferences;
  private $locked;
  private $type;
  private $dbh;
    
  function __construct() {
    
    $this->preferences = Array( // these are the preset preferences
      "content_type" => "text/html; charset=utf-8",
      'charset' => 'UTF-8',
      'css_dir' => 'skin/',
      'js_dir' => 'script/',
      'timezone' => 'Europe/Stockholm',
    );
    
    $this->locked = Array( // these preferences are locked and cannot be changed
      'charset'
    );
    
    $this->type = Array(); // special type preferences.
  }
  
  // activate database connection
  public function db_ready ($db) {
    $this->dbh = $db;
  }
  
  // get a preference
  public function get ($key, $default = false) {
    
    if (isset($this->preferences[$key])) {
      return $this->preferences[$key];
    }
    else {
      
      if (isset($this->dbh)) { // check if database is initialized
        
        $sth = $this->dbh->prepare('SELECT value FROM preferences WHERE `key`=?');
        
        $sth->execute(array($key));
        $this->preferences[$key] = unserialize($sth->fetchColumn());
        $sth->closeCursor();
        $this->type[$key] = 'db';
        
        if (empty($this->preferences[$key])) {
          $this->preferences[$key] = $default;
          
          $this->set($key, $default); // if unset, define!
        }
        
        return $this->preferences[$key];
      }
      
      return false;
    }
  }
  
  // set a preference
  public function set ($key, $value) {
    
    // initializes database handling of preference if this one isn't set.
    if (!isset($this->preferences[$key])) {
      $this->type[$key] = 'db';
    }
    
    // don't set locked preferences
    if (!in_array($key, $this->locked)) {
      $this->preferences[$key] = $value;
    }
    else {
      return false;
    }
    
    // write setting to database if applicable.
    if (!empty($this->type[$key])) {
      
      switch ($this->type[$key]) {
        
        case 'db':
          
          $sth = $this->dbh->prepare('SELECT COUNT(*) FROM preferences WHERE `key`=?');
          $sth->execute(array($key));
          $num_rows = $sth->fetchColumn();
          $sth->closeCursor();
          
          $data = serialize($this->preferences[$key]);
          
          if ($num_rows > 0) {
            $sql = 'UPDATE preferences SET value=? WHERE `key`=?';
          }
          else {
            $sql = 'INSERT INTO preferences (value, `key`) VALUES (?, ?)';
          }
          
          $sth = $this->dbh->prepare($sql);
          $sth->execute(array($data, $key));
          
          $sth->closeCursor();
          
          break;
        
      }
      
    }
  }
}