<?php
drupal_add_http_header('Content-Type', 'application/xml; charset=utf-8');
function create_xml(){
    $xml = new DOMDocument('1.0');
    $element = $xml->createElement('markers');
    $parnode = $xml->appendChild($element);
	$table = 'osmap';
	$osmap_true = 1;
    
    $query = ('SELECT * FROM '. $table. ' WHERE ' . $osmap_true);
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
	return $xml->saveXML();
	}
