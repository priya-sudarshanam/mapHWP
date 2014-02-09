<?php
/**
 * @file
 * OSMAP for displaying locations on the map
 */
//osmap_insert for inserting values into the osmap table
  drupal_add_http_header('Content-Type', 'application/xml; charset=utf-8');
	
function create_xml(){

    $xml = new DOMDocument('1.0');
    $element = $xml->createElement('markers');
    $parnode = $xml->appendChild($element);
	$uid = 1;
	$table = 'osmap';
 
    $query = ('SELECT * FROM '. $table);
    $result = db_query($query);
	
    if (!$result) {  
       die('Invalid query: ' . mysql_error());
} 
    
// Iterate through the rows, adding XML nodes for each
     while ($row=$result->fetchAssoc()){
        $element = $xml->createElement('marker');
        $newnode = $parnode->appendChild($element);
	     $newnode->setAttribute('name',$row['name']);
         $newnode->setAttribute('address', $row['address']);
         $newnode->setAttribute('lat', $row['lat']);
         $newnode->setAttribute('lng', $row['lng']);
         $newnode->setAttribute('type', $row['type']);
	  
	     }
	echo $xml->saveXML();
	}
	

   




