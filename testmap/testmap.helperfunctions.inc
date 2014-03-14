<?php
/**
 * Returns the latitude of a location
 */
function get_latitude_longitude($add){
        $prepAddr = str_replace(' ','+',$add);
        $geocode=file_get_contents('http://maps.google.com/maps/api/geocode/json?address='.$prepAddr.'&sensor=false');
        $output= json_decode($geocode);
  		$lat_lng = array (
		 'lat' => $output->results[0]->geometry->location->lat,
		 'lng' => $output->results[0]->geometry->location->lng,
			);
        return $lat_lng;
}
/**
 * Updates the selected location in the table = 'osmap'. 
 */
function id_to_arg($variable){
  if ($variable == '%') {
 	// drupal_set_message(t('Please choose a location to update'));
	 return 'none';
//	 drupal_goto('testmap/list');
	}
  else {
    return $variable;
  
  }
 } 
/**
* Returns type list for colored markers on the map. 
*/
function type_list(){
  return array("university" => 'university', 
               "business" => 'business', 
			   "office" =>'office', 
			   "library" => 'library');
}

function create_form($form, $form_type){
 $typeOptions = type_list();
  $form[$form_type] = array(
    '#type' => 'fieldset', //container for multiple fields
	'#title' => t('Add new Location'),
  );
  $form[$form_type]['name'] = array(
    '#type' => 'textfield' ,
	'#title' =>'Name',
	'#required' => TRUE,
	'#attributes' =>array('placeholder' => t('Harvard Web Publishing')),
	'#size' => 40,
  );
  $form[$form_type]['address'] = array(
    '#type' => 'textfield',
	'#title' => 'Address',
	'#required' => TRUE,
	'#attributes' =>array('placeholder' => t('125 Mount Auburn Street, Cambridge, MA')),
	'#size' => 50,
  ); 
  $form[$form_type]['type'] = array(
   '#type' => 'select',
   '#title' => 'Type',
   '#options' => $typeOptions,
   '#required' => TRUE,
   '#default_value' => $typeOptions['university'],
  );
  if ($form_type == 'add'){
    $form[$form_type]['submit'] =array (
       '#type' => 'submit',
	   '#value' => 'ADD'
	   );
	 }
	else {
	   $form[$form_type]['submit'] =array (
           '#type' => 'submit',
	       '#value' => 'Update'
		   );
	   } 
  
return $form;
}

/**
 * Updates the selected location in the table = 'osmap'. 
 */
function testmap_form_update($form, &$form_state, $variable){
      $mapValue = map_select_data_id($variable);
	  $rows = array();
	  $header = array(t('Name'),t('Address'),t('Type'));
	  $rows[] = array(
				  'name' => $mapValue['name'],
                  'address' => $mapValue['address'],
			      'type' => $mapValue['type'], 
                );
     $form['table'] = array(
	   '#theme' => 'table',
	   '#empty' => t('No users found'),
	   '#header' => $header,
	   '#rows' => $rows,
	   '#id' => $variable,
	   );
	  	
    $typeOptions = type_list();  
	return create_form($form, 'update');
}
function return_map_values($name,$address,$type,$lat,$lng){
  return $mapValue = array (
	    'name' => $name,
		'address' => $address,
		'type' => $type,
		'lat' => $lat,
		'lng' => $lng
		);
}
