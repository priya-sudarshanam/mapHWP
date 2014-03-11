<?php
/**
 * Retrieve data from the table = 'osmap'
 */
 function map_select_data(){
    $table = 'osmap';
	$osmap_true = 1;
	$query = ('SELECT * FROM '. $table. ' WHERE ' . $osmap_true);
	try {
         $result = db_query($query);
	}
	catch(Exception $e)
	{
	  drupal_set_message(t('db_query failed. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
	}
	return $result->fetchAll();
	}
	

	/**
 * Insert location values into the table
 */
function map_insert_data($mapValues){
  $dataInsert = NULL;
  $table = 'osmap';
  try {
        $dataInsert = db_insert($table)
	                ->fields($mapValues)
					->execute();
     }
  catch(Exception $e)
  {
    drupal_set_message(t('db_insert failed. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
  }
 return $dataInsert;
}

function map_update_data($mapValues){
  try {
     $updated = db_update('osmap')
	          ->fields($mapValues)
			  ->condition('id',$mapValues['id'])
			  ->execute();  
  }
  catch (Exception $e){
     drupal_set_message(t('db_update failed. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
  }
  return $updated;

}
