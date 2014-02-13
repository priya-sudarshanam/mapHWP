<?php
drupal_add_http_header('Content-Type', 'application/xml; charset=utf-8');
function create_xml(){
    $myfile = 'myxml.xml';
    $myfile = realpath($myfile);

    $dom = new DOMDocument('1.0','utf-8');
//	$dom->load($myfile);
    $element = $dom->createElement('markers');
    $parnode = $dom->appendChild($element);
	$table = 'osmap';
	$osmap_true = 1;
    
    $query = ('SELECT * FROM '. $table. ' WHERE ' . $osmap_true);
    $result = db_query($query);
	
    if (!$result) {  
       die('Invalid query: ' . mysql_error());
     }     
// Iterate through the rows, adding XML nodes for each
     while ($row=$result->fetchAssoc()){
        $element = $dom->createElement('marker');
         $newnode = $parnode->appendChild($element);
	     $newnode->setAttribute('name',$row['name']);
         $newnode->setAttribute('address', $row['address']);
         $newnode->setAttribute('lat', $row['lat']);
         $newnode->setAttribute('lng', $row['lng']);
         $newnode->setAttribute('type', $row['type']);
	    }
		
	$dom->formatOutput = true;
	
	$strxml = $dom->saveXML();
	$dom->save('osmap.xml');
		
    return $strxml;
	}
