<?php
//drupal_add_http_header('Content-Type', 'application/xml; charset=utf-8');
function parseToXML($htmlStr) 
{ 
$xmlStr=str_replace('<','&lt;',$htmlStr); 
$xmlStr=str_replace('>','&gt;',$xmlStr); 
$xmlStr=str_replace('"','&quot;',$xmlStr); 
$xmlStr=str_replace("'",'&#39;',$xmlStr); 
$xmlStr=str_replace("&",'&amp;',$xmlStr); 
return $xmlStr; 
} 

function create_xml(){
    $table = 'osmap';
	$osmap_true = 1;
    
    $query = ('SELECT * FROM '. $table. ' WHERE ' . $osmap_true);
    $result = db_query($query);
	
    if (!$result) {  
       die('Invalid query: ' . mysql_error());
     }     
// Iterate through the rows, adding XML nodes for each
    echo '<markers>';

// Iterate through the rows, printing XML nodes for each
while ($row = @mysql_fetch_assoc($result)){
  // ADD TO XML DOCUMENT NODE
  echo '<marker ';
  echo 'name="' . parseToXML($row['name']) . '" ';
  echo 'address="' . parseToXML($row['address']) . '" ';
  echo 'lat="' . $row['lat'] . '" ';
  echo 'lng="' . $row['lng'] . '" ';
  echo 'type="' . $row['type'] . '" ';
  echo '/>';
}

// End XML file
echo '</markers>';
