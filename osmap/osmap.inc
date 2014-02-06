//This is a file for xml related code for osmap.inc
//This is a file for xml related code for osmap.inc

<?php
/**
 * @file
 * OSMAP for displaying locations on the map
 */
//osmap_insert for inserting values into the osmap table

/*function osmap_insert($entry) {
    $return_value = NULL;
    try {
        $return_value = db_insert('osmap')
            ->fields($entry)
            ->execute();
    }
    catch (Exception $e) {
        drupal_set_message(t('osmap_insert failed. Message = %message, query= %query',
            array('%message' => $e->getMessage(), '%query' => $e->query_string)), 'error');
    }
    return $return_value;
}*/
//osmap_update for updating values in the osmap table
/*function osmap_update($entry) {
    try {
        // db_update()...->execute() returns the number of rows updated.
        $count = db_update('osmap')
            ->fields($entry)
            ->condition('id', $entry['id'])
            ->execute();
    }
    catch (Exception $e) {
        drupal_set_message(t('osmap_update failed. Message = %message, query= %query',
            array('%message' => $e->getMessage(), '%query' => $e->query_string)), 'error');
    }
    return $count;
}
//osmap_delete for deleting values from the osmap table
function osmap_delete($entry) {
    db_delete('osmap')
        ->condition('id', $entry['id'])
        ->execute();

}*/
$dom = new DOMDocument("1.0");
$node = $dom->createElement("markers");
$parnode = $dom->appendChild($node);

//osmap_entry_load loads the data from the osmap table
function osmap_entry_load($entry = array()) {
    // Read all fields from the osmap table.
    $select = db_select('osmap', 'os');
    $select->fields('os');

    // Add each field and value as a condition to this query.
    foreach ($entry as $field => $value) {
        $select->condition($field, $value);
    }
    // Return the result in object format.
    return $select->execute()->fetchAll();
}

header("Content-type: text/xml");

// Iterate through the rows, adding XML nodes for each

while ($row = @mysql_fetch_assoc($result)){
    // ADD TO XML DOCUMENT NODE
    $node = $dom->createElement("marker");
    $newnode = $parnode->appendChild($node);
    $newnode->setAttribute("name",$row['name']);
    $newnode->setAttribute("address", $row['address']);
    $newnode->setAttribute("lat", $row['lat']);
    $newnode->setAttribute("lng", $row['lng']);
    $newnode->setAttribute("type", $row['type']);
}

echo $dom->saveXML();

?>
