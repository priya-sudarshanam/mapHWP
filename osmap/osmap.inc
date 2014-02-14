<?php
drupal_add_http_header('Content-Type', 'application/xml; charset=utf-8');
function create_xml(){
    //declare variables
    $myfile = 'myxml.xml';
    $myfile = realpath($myfile);

    $dom = new DOMDocument('1.0','utf-8');
    $element = $dom->createElement('markers');
    $parnode = $dom->appendChild($element);
    $table = 'osmap';
    $osmap_true = 1;
    
    //Query the table
    $query = ('SELECT * FROM '. $table. ' WHERE ' . $osmap_true);
    $result = db_query($query);

    //table cannot be reached and results queried	
    if (!$result) {  
       die('Invalid query: ' . mysql_error());
     }
     
// Iterate through the rows, adding XML nodes for each and while table has data
     while ($row=$result->fetchAssoc()){
         $element = $dom->createElement('marker');
         $newnode = $parnode->appendChild($element);
	 $newnode->setAttribute('name',$row['name']);
         $newnode->setAttribute('address', $row['address']);
         $newnode->setAttribute('lat', $row['lat']);
         $newnode->setAttribute('lng', $row['lng']);
         $newnode->setAttribute('type', $row['type']);
         $newnode->setAttribute('title', $row['title']);
	    }
		
	$dom->formatOutput = true;
	//save the xml to the browser
	$strxml = $dom->saveXML();
	//save it to a file
	$dom->save('osmap.xml');

    //return the formed xml		
    return $strxml;
	}
