<?php
/**
* This file is for database functions like retrieving, 
* adding, deleting functions
*/

/**
 * Retrieve data from the table('osmap')
 */
 function map_select_data(){
    $table = 'osmap';
	$osmap_true = 1;
	$query = ('SELECT * FROM '. $table. ' WHERE ' . $osmap_true);
	
	try {
         $result = db_query($query);
	    }
	catch(Exception $e)	{
	           drupal_set_message(t('Issue in retrieving the location data. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
	    }
	 return $result->fetchAll();
}

/**
 * Creating paging and sorting in the data table by extending 'pagerdefault' and 'sort'
 */
function paging_map_data(){
   $header = create_table_header();
   $table = 'osmap';
   try {
         $select = db_select($table)
                 ->fields($table, array('id','name', 'address','type'))
                 ->extend('PagerDefault')
				 ->limit(5)
                 ->extend('TableSort')
				 ->orderByHeader($header);
      }
	catch (Exception $e) {
	   drupal_set_message(t('Issue in retrieving the location data. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');	
	}
   
   return $select->execute();
}

/**
 * Retrieve data from the table('osmap') for a given id
 */
 function map_select_data_id($id){
    $table = 'osmap';
	try {
         $selected = db_select('osmap','os')
	               ->fields('os')
			       ->condition('id',$id)
			       ->execute()
			       ->fetchAssoc();
	}
	catch(Exception $e)	{
	     drupal_set_message(t('Issue in retrieving the location data for location id= '.$id.'. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
	}
	return $selected;
}
	

/**
 * Insert new location values into the table
 */
function map_insert_data($mapValues){
  $dataInsert = NULL;
  $table = 'osmap';
  
  try {
        $dataInsert = db_insert($table)
	                ->fields($mapValues)
					->execute();
     }
  catch(Exception $e) {
        drupal_set_message(t('Adding the new location failed. Message = %message, query=%query', 
	    array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
  }
  return $dataInsert;
}

/**
 * Update location values in the table for the given location id
 */
function map_update_data($mapValues,$id){
  try {
       $updated = db_update('osmap')
	            ->fields($mapValues)
	  		    ->condition('id',$id)
			    ->execute();  
  }
  catch (Exception $e){
     drupal_set_message(t('Issue in updating the location information  with location id:'.$id.' . Message = %message, query=%query', 
	 array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
  }
  return $updated;
}

/**
 * Delete location in the table for the given location id
 */
function map_delete_data($id){
    try {
         $success = db_delete('osmap')
		       	  ->condition('id', $id)
		       	  ->execute();
		}
	catch(Exception $e){
	     drupal_set_message(t('Issue in deleting location: '.$id.'. Message = %message, query=%query', 
	     array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
	   }
	return $success;
 }